/***************************************
Original Author: 
Camilo Carrillo
Universidad de los Andes Bogota Colombia
camilo.carrilloATcern.ch
Modified for GEM:
Roumyana Hadjiiska
****************************************/

//#include "DQM/RPCMonitorModule/interface/MuonSegmentEff.h"
#include "DQM/GEMResoModule/interface/GEMMuonSegment.h"
#include <memory>
#include "FWCore/Framework/interface/MakerMacros.h"
//#include <DataFormats/RPCDigi/interface/RPCDigiCollection.h>
#include <DataFormats/GEMDigi/interface/GEMDigiCollection.h>
//#include "DataFormats/RPCRecHit/interface/RPCRecHitCollection.h"
#include "DataFormats/GEMRecHit/interface/GEMRecHitCollection.h"
//#include <DataFormats/MuonDetId/interface/RPCDetId.h>
#include <DataFormats/MuonDetId/interface/GEMDetId.h>
#include <DataFormats/CSCRecHit/interface/CSCSegmentCollection.h>
//#include <Geometry/RPCGeometry/interface/RPCGeomServ.h>
#include <Geometry/CommonDetUnit/interface/GeomDet.h>
#include <Geometry/Records/interface/MuonGeometryRecord.h>
//#include <Geometry/CommonTopologies/interface/RectangularStripTopology.h>
#include <Geometry/CommonTopologies/interface/TrapezoidalStripTopology.h>


#include <cmath>
#include "TFile.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "TString.h"

#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/Utilities/interface/EDGetToken.h"

/*
double straighter(RPCDetId rpcId){ 	 
  
  bool ok = true; 	 
  RPCGeomServ rpcsrv(rpcId); 	 
  
  if( ((rpcId.station()==2) || (rpcId.station()==1)) && (rpcId.ring()==2) && (rpcsrv.segment()%2==0) ){ 	 
    ok=false; 	 
  } 	 
  
  if(ok == false){ 	 
    return -1.; 	 
  }else{ 	 
    return 1.; 	 
  } 	 
}
*/

void GEMMuonSegment::beginJob(){
  firstbook=true;
}

/*
int distsector(int sector1,int sector2){
  if(sector1==13) sector1=4;
  if(sector1==14) sector1=10;
  
  if(sector2==13) sector2=4;
  if(sector2==14) sector2=10;
  
  int distance = abs(sector1 - sector2);
  if(distance>6) distance = 12-distance;
  return distance;
}
*/

/*
int distwheel(int wheel1,int wheel2){
  int distance = abs(wheel1 - wheel2);
  return distance;
}
*/

GEMMuonSegment::GEMMuonSegment(const edm::ParameterSet& iConfig){
  debug=iConfig.getUntrackedParameter<bool>("debug",true);
  inves=iConfig.getUntrackedParameter<bool>("inves");
  manualalignment=iConfig.getUntrackedParameter<bool>("manualalignment",false);
 
  rangestrips = iConfig.getUntrackedParameter<double>("rangestrips",1.);
  dupli = iConfig.getUntrackedParameter<int>("DuplicationCorrection",1); 

  cscSegments = consumes<CSCSegmentCollection>(iConfig.getUntrackedParameter < edm::InputTag > ("cscSegments"));
//  dt4DSegments = consumes<DTRecSegment4DCollection>(iConfig.getUntrackedParameter < edm::InputTag > ("dt4DSegments"));
//  rpcRecHitsLabel = consumes<RPCRecHitCollection>(iConfig.getUntrackedParameter < edm::InputTag > ("rpcRecHits"));
  gemRecHitsLabel = consumes<GEMRecHitCollection>(iConfig.getUntrackedParameter < edm::InputTag > ("gemRecHits"));
//  rpcDTPointsLabel = consumes<RPCRecHitCollection>(iConfig.getUntrackedParameter < edm::InputTag > ("rpcDTPoints"));
//  rpcCSCPointsLabel = consumes<RPCRecHitCollection>(iConfig.getUntrackedParameter < edm::InputTag > ("rpcCSCPoints"));
  gemCSCPointsLabel = consumes<GEMRecHitCollection>(iConfig.getUntrackedParameter < edm::InputTag > ("gemCSCPoints"));
  
//  nameInLog = iConfig.getUntrackedParameter<std::string>("moduleLogName", "RPC_Eff");
  nameInLog = iConfig.getUntrackedParameter<std::string>("moduleLogName", "GEM_CSCseg");
  EffSaveRootFile  = iConfig.getUntrackedParameter<bool>("EffSaveRootFile", false); 
  EffRootFileName  = iConfig.getUntrackedParameter<std::string>("EffRootFileName", "GEMMuonSegment.root"); 
  AlignmentinfoFile  = iConfig.getUntrackedParameter<std::string>("AliFileName","/afs/cern.ch/user/c/carrillo/segments/CMSSW_2_2_10/src/DQM/RPCMonitorModule/data/Alignment.dat"); 
    
  //Interface
  
  dbe = edm::Service<DQMStore>().operator->();
  
  std::string folder = "Muons/MuonSegEff/";
  dbe->setCurrentFolder(folder);

//  unixeventtime = dbe->bookInt("unixTimeEvt");  
//  rnNumber = dbe->bookInt("runNumber");  
  statistics = dbe->book1D("Statistics","All Statistics",5,0.5,5.5);
  stationstatistics = dbe->book1D("StationStatistics","All Statistics by Station",17,0.5,17.5);

  if(debug) std::cout<<"booking Global histograms"<<std::endl;
  
  statistics->setBinLabel(1,"Events ",1);
  statistics->setBinLabel(2,"Events with CSC segments",1);
  statistics->setBinLabel(3,"Events with 1 CSC segment",1);
  statistics->setBinLabel(4,"Events with 2 CSC segments",1);
  statistics->setBinLabel(5,"Events with 3 CSC segments",1);
  statistics->setBinLabel(6,"Events with 4 CSC segments",1);
  statistics->setBinLabel(7,"Events with 5 CSC segments",1);
  statistics->setBinLabel(8,"Events with 6 CSC segments",1);
  statistics->setBinLabel(9,"Events with 7 CSC segments",1);
  statistics->setBinLabel(10,"Events with 8 CSC segments",1);
  statistics->setBinLabel(11,"Events with 9 CSC segments",1);
  statistics->setBinLabel(12,"Events with 10 CSC segments",1);
  statistics->setBinLabel(13,"Events with 11 CSC segments",1);
  statistics->setBinLabel(14,"Events with 12 CSC segments",1);
  statistics->setBinLabel(15,"Events with 13 CSC segments",1);
  statistics->setBinLabel(16,"Events with 14 CSC segments",1);
  statistics->setBinLabel(17,"Events with 15 CSC segments",1);

  stationstatistics->setBinLabel(1,"Events ",1);
  stationstatistics->setBinLabel(2,"Events with GE11 rechits",1);
  stationstatistics->setBinLabel(3,"Events with GE21 rechits",1);
  stationstatistics->setBinLabel(4,"Events with RE31 rechits",1);
  stationstatistics->setBinLabel(5,"Events with RE41 rechits",1);
  
  if(debug) std::cout<<"booking Global histograms Change statistics"<<std::endl;

  folder = "Muons/MuonSegEff/Residuals/Investigation";
  dbe->setCurrentFolder(folder);

  //Ang Dependence
  AngClu1Endcaps = dbe->book1D("AngClu1Endcaps","Angle of incident Muon Endcaps Cluster Size 1",100,0.,360.);
  AngClu2Endcaps = dbe->book1D("AngClu2Endcaps","Angle of incident Muon Endcaps Cluster Size 2",100,0.,360.); 
  AngClu3Endcaps = dbe->book1D("AngClu3Endcaps","Angle of incident Muon Endcaps Cluster Size 3",100,0.,360.); 
  ScatterPlotAngCLSEndcaps = dbe->book2D("ScatterPlotAngCLSEndcaps","Scatter Plot Incident  Angle and Cluster Size Endcaps",100,0.,360.,7,0.5,7.5);

  if(debug) std::cout<<"Booking Residuals for EndCap"<<std::endl;
  folder = "Muons/MuonSegEff/Residuals/EndCap";
  dbe->setCurrentFolder(folder);

  //Endcap GE11
  hGlobalResClu1GE11_1 = dbe->book1D("GlobalResidualsClu1GE11_1","GEM Residuals GE11 Roll 1 Cluster Size 1",101,-10.,10.);
  hGlobalResClu1GE11_2 = dbe->book1D("GlobalResidualsClu1GE11_2","GEM Residuals GE11 Roll 2 Cluster Size 1",101,-10.,10.);
  hGlobalResClu1GE11_3 = dbe->book1D("GlobalResidualsClu1GE11_3","GEM Residuals GE11 Roll 3 Cluster Size 1",101,-10.,10.);
  hGlobalResClu1GE11_4 = dbe->book1D("GlobalResidualsClu1GE11_4","GEM Residuals GE11 Roll 4 Cluster Size 1",101,-10.,10.);
  hGlobalResClu1GE11_5 = dbe->book1D("GlobalResidualsClu1GE11_5","GEM Residuals GE11 Roll 5 Cluster Size 1",101,-10.,10.);
  hGlobalResClu1GE11_6 = dbe->book1D("GlobalResidualsClu1GE11_6","GEM Residuals GE11 Roll 6 Cluster Size 1",101,-10.,10.);
  hGlobalResClu1GE11_7 = dbe->book1D("GlobalResidualsClu1GE11_7","GEM Residuals GE11 Roll 7 Cluster Size 1",101,-10.,10.);
  hGlobalResClu1GE11_8 = dbe->book1D("GlobalResidualsClu1GE11_8","GEM Residuals GE11 Roll 8 Cluster Size 1",101,-10.,10.);

  hGlobalResClu2GE11_1 = dbe->book1D("GlobalResidualsClu2GE11_1","GEM Residuals GE11 Roll 1 Cluster Size 2",101,-10.,10.);
  hGlobalResClu2GE11_2 = dbe->book1D("GlobalResidualsClu2GE11_2","GEM Residuals GE11 Roll 2 Cluster Size 2",101,-10.,10.);
  hGlobalResClu2GE11_3 = dbe->book1D("GlobalResidualsClu2GE11_3","GEM Residuals GE11 Roll 3 Cluster Size 2",101,-10.,10.);
  hGlobalResClu2GE11_4 = dbe->book1D("GlobalResidualsClu2GE11_4","GEM Residuals GE11 Roll 4 Cluster Size 2",101,-10.,10.);
  hGlobalResClu2GE11_5 = dbe->book1D("GlobalResidualsClu2GE11_5","GEM Residuals GE11 Roll 5 Cluster Size 2",101,-10.,10.);
  hGlobalResClu2GE11_6 = dbe->book1D("GlobalResidualsClu2GE11_6","GEM Residuals GE11 Roll 6 Cluster Size 2",101,-10.,10.);
  hGlobalResClu2GE11_7 = dbe->book1D("GlobalResidualsClu2GE11_7","GEM Residuals GE11 Roll 7 Cluster Size 2",101,-10.,10.);
  hGlobalResClu2GE11_8 = dbe->book1D("GlobalResidualsClu2GE11_8","GEM Residuals GE11 Roll 8 Cluster Size 2",101,-10.,10.);

  hGlobalResClu3GE11_1 = dbe->book1D("GlobalResidualsClu3GE11_1","GEM Residuals GE11 Roll 1 Cluster Size 3",101,-10.,10.);
  hGlobalResClu3GE11_2 = dbe->book1D("GlobalResidualsClu3GE11_2","GEM Residuals GE11 Roll 2 Cluster Size 3",101,-10.,10.);
  hGlobalResClu3GE11_3 = dbe->book1D("GlobalResidualsClu3GE11_3","GEM Residuals GE11 Roll 3 Cluster Size 3",101,-10.,10.);
  hGlobalResClu3GE11_4 = dbe->book1D("GlobalResidualsClu3GE11_4","GEM Residuals GE11 Roll 4 Cluster Size 3",101,-10.,10.);
  hGlobalResClu3GE11_5 = dbe->book1D("GlobalResidualsClu3GE11_5","GEM Residuals GE11 Roll 5 Cluster Size 3",101,-10.,10.);
  hGlobalResClu3GE11_6 = dbe->book1D("GlobalResidualsClu3GE11_6","GEM Residuals GE11 Roll 6 Cluster Size 3",101,-10.,10.);
  hGlobalResClu3GE11_7 = dbe->book1D("GlobalResidualsClu3GE11_7","GEM Residuals GE11 Roll 7 Cluster Size 3",101,-10.,10.);
  hGlobalResClu3GE11_8 = dbe->book1D("GlobalResidualsClu3GE11_8","GEM Residuals GE11 Roll 8 Cluster Size 3",101,-10.,10.);

  //Endcap GE21
  hGlobalResClu1GE21_1 = dbe->book1D("GlobalResidualsClu1GE21_1","GEM Residuals GE21 Roll 1 Cluster Size 1",101,-10.,10.);
  hGlobalResClu1GE21_2 = dbe->book1D("GlobalResidualsClu1GE21_2","GEM Residuals GE21 Roll 2 Cluster Size 1",101,-10.,10.);
  hGlobalResClu1GE21_3 = dbe->book1D("GlobalResidualsClu1GE21_3","GEM Residuals GE21 Roll 3 Cluster Size 1",101,-10.,10.);
  hGlobalResClu1GE21_4 = dbe->book1D("GlobalResidualsClu1GE21_4","GEM Residuals GE21 Roll 4 Cluster Size 1",101,-10.,10.);
  hGlobalResClu1GE21_5 = dbe->book1D("GlobalResidualsClu1GE21_5","GEM Residuals GE21 Roll 5 Cluster Size 1",101,-10.,10.);
  hGlobalResClu1GE21_6 = dbe->book1D("GlobalResidualsClu1GE21_6","GEM Residuals GE21 Roll 6 Cluster Size 1",101,-10.,10.);
  hGlobalResClu1GE21_7 = dbe->book1D("GlobalResidualsClu1GE21_7","GEM Residuals GE21 Roll 7 Cluster Size 1",101,-10.,10.);
  hGlobalResClu1GE21_8 = dbe->book1D("GlobalResidualsClu1GE21_8","GEM Residuals GE21 Roll 8 Cluster Size 1",101,-10.,10.);

  hGlobalResClu2GE21_1 = dbe->book1D("GlobalResidualsClu2GE21_1","GEM Residuals GE21 Roll 1 Cluster Size 2",101,-10.,10.);
  hGlobalResClu2GE21_2 = dbe->book1D("GlobalResidualsClu2GE21_2","GEM Residuals GE21 Roll 2 Cluster Size 2",101,-10.,10.);
  hGlobalResClu2GE21_3 = dbe->book1D("GlobalResidualsClu2GE21_3","GEM Residuals GE21 Roll 3 Cluster Size 2",101,-10.,10.);
  hGlobalResClu2GE21_4 = dbe->book1D("GlobalResidualsClu2GE21_4","GEM Residuals GE21 Roll 4 Cluster Size 2",101,-10.,10.);
  hGlobalResClu2GE21_5 = dbe->book1D("GlobalResidualsClu2GE21_5","GEM Residuals GE21 Roll 5 Cluster Size 2",101,-10.,10.);
  hGlobalResClu2GE21_6 = dbe->book1D("GlobalResidualsClu2GE21_6","GEM Residuals GE21 Roll 6 Cluster Size 2",101,-10.,10.);
  hGlobalResClu2GE21_7 = dbe->book1D("GlobalResidualsClu2GE21_7","GEM Residuals GE21 Roll 7 Cluster Size 2",101,-10.,10.);
  hGlobalResClu2GE21_8 = dbe->book1D("GlobalResidualsClu2GE21_8","GEM Residuals GE21 Roll 8 Cluster Size 2",101,-10.,10.);

  hGlobalResClu3GE21_1 = dbe->book1D("GlobalResidualsClu3GE21_1","GEM Residuals GE21 Roll 1 Cluster Size 3",101,-10.,10.);
  hGlobalResClu3GE21_2 = dbe->book1D("GlobalResidualsClu3GE21_2","GEM Residuals GE21 Roll 2 Cluster Size 3",101,-10.,10.);
  hGlobalResClu3GE21_3 = dbe->book1D("GlobalResidualsClu3GE21_3","GEM Residuals GE21 Roll 3 Cluster Size 3",101,-10.,10.);
  hGlobalResClu3GE21_4 = dbe->book1D("GlobalResidualsClu3GE21_4","GEM Residuals GE21 Roll 4 Cluster Size 3",101,-10.,10.);
  hGlobalResClu3GE21_5 = dbe->book1D("GlobalResidualsClu3GE21_5","GEM Residuals GE21 Roll 5 Cluster Size 3",101,-10.,10.);
  hGlobalResClu3GE21_6 = dbe->book1D("GlobalResidualsClu3GE21_6","GEM Residuals GE21 Roll 6 Cluster Size 3",101,-10.,10.);
  hGlobalResClu3GE21_7 = dbe->book1D("GlobalResidualsClu3GE21_7","GEM Residuals GE21 Roll 7 Cluster Size 3",101,-10.,10.);
  hGlobalResClu3GE21_8 = dbe->book1D("GlobalResidualsClu3GE21_8","GEM Residuals GE21 Roll 8 Cluster Size 3",101,-10.,10.);

//XY_view plots
  folder = "Muons/MuonSegEff/Residuals/xyViews";
  dbe->setCurrentFolder(folder);

  XY_globalGE2 = dbe->book2D("globalXY_GE21", "globalXY_GE21", 1600, -800, 800, 1600, -800, 800);
  XY_globalGEm2 = dbe->book2D("globalXY_GEm21", "globalXY_GEm21", 1600, -800, 800, 1600, -800, 800);
  XY_globalGE1 = dbe->book2D("globalXY_GE11", "globalXY_GE11", 1600, -800, 800, 1600, -800, 800);
  XY_globalGEm1 = dbe->book2D("globalXY_GEm11", "globalXY_GEm11", 1600, -800, 800, 1600, -800, 800);
  
  XY_globalGE2_extra = dbe->book2D("globalXY_extrapolated_GE21", "globalXY_extrapolated_GE21", 1600, -800, 800, 1600, -800, 800);
  XY_globalGEm2_extra = dbe->book2D("globalXY_extrapolated_GEm21", "globalXY_extrapolated_GEm21", 1600, -800, 800, 1600, -800, 800);
  XY_globalGE1_extra = dbe->book2D("globalXY_extrapolated_GE11", "globalXY_extrapolated_GE11", 1600, -800, 800, 1600, -800, 800);
  XY_globalGEm1_extra = dbe->book2D("globalXY_extrapolated_GEm11", "globalXY_extrapolated_GEm11", 1600, -800, 800, 1600, -800, 800);

  if(debug) ofrej.open("rejected.txt");
  if(debug) std::cout<<"Rejected done"<<std::endl;

}

void GEMMuonSegment::beginRun(const edm::Run& run, const edm::EventSetup& iSetup){
  std::ifstream ifin(AlignmentinfoFile.c_str());

  if(manualalignment)
  {
    int rawId;
    std::string name;
    float offset;
    float rms;
    while (ifin.good()){
      ifin >>name >>rawId >> offset >> rms;
      alignmentinfo[rawId]=offset;

      if(debug) std::cout<<"rawId ="<<rawId<<" offset="<<offset<<std::endl;
    }
  }
  
  if(firstbook)
  {
    std::cout<<"bbooking all histograms"<<std::endl;
//    iSetup.get<MuonGeometryRecord>().get(rpcGeo);
    iSetup.get<MuonGeometryRecord>().get(gemGeo);
//    iSetup.get<MuonGeometryRecord>().get(dtGeo);
    iSetup.get<MuonGeometryRecord>().get(cscGeo);

//    for (TrackingGeometry::DetContainer::const_iterator it=rpcGeo->dets().begin();it<rpcGeo->dets().end();it++)
    for (TrackingGeometry::DetContainer::const_iterator it=gemGeo->dets().begin();it<gemGeo->dets().end();it++)
    {
//      if(dynamic_cast< const RPCChamber* >( *it ) != 0 )
      if(dynamic_cast< const GEMChamber* >( *it ) != 0 )
      {
//	const RPCChamber* ch = dynamic_cast< const RPCChamber* >( *it ); 
	const GEMChamber* ch = dynamic_cast< const GEMChamber* >( *it ); 
//	std::vector< const RPCRoll*> roles = (ch->rolls());
	std::vector< const GEMEtaPartition*> roles = (ch->etaPartitions());
//	for(std::vector<const RPCRoll*>::const_iterator r = roles.begin();r != roles.end(); ++r)
	for(std::vector<const GEMEtaPartition*>::const_iterator r = roles.begin();r != roles.end(); ++r)
        {
//	  RPCDetId rpcId = (*r)->id();
	  GEMDetId gemId = (*r)->id();
//	  int region=rpcId.region();
	  int region=gemId.region();

	  //booking all histograms
//	  RPCGeomServ rpcsrv(rpcId);
//	  std::string nameRoll = rpcsrv.name();
//rumi: make GEM_names:
          std::string nameRoll = GEMname(gemId);
	  if(region==0)
          {
            std::cout << "I found a GEM eta partition in the Barrel - should be wrong!" << std::endl;
            continue;
	  }
          else
          {
	    const TrapezoidalStripTopology* topE_=dynamic_cast<const TrapezoidalStripTopology*>(&((*r)->topology()));
	    float stripl = topE_->stripLength();
	    float stripw = topE_->pitch();
	    meCollection[nameRoll] = bookDetUnitSeg(gemId,(*r)->nstrips(),stripw,stripl);
	  }
	}
      }
    }
    firstbook = false;
  }
}//beginRun


GEMMuonSegment::~GEMMuonSegment()
{

}

std::string GEMMuonSegment::GEMname(const GEMDetId& _id)
{
   std::string _n = "";
   int station = _id.station();
   int region = _id.region();
   int roll = _id.roll();
   int ring = _id.ring();
   int layer = _id.layer();
   int chamber = _id.chamber();
   std::stringstream os;

   if( _n.size() < 1 )
   {
    if( region == 0 )
    {
       return "I found a GEM eta partition in the Barrel - should be wrong!";
    }
    else
    {
      os << "GE";
      os << std::setw(2) << std::setfill('+') << station * region << std::setfill(' ') << "_";
      os << "R" << ring;
      os << "_CH" << std::setw(2) << std::setfill('0') << chamber << "_L" << layer;

      if( roll == 1 )
    os << "_A";
      else if( roll == 2 )
    os << "_B";
      else if( roll == 3 )
    os << "_C";
      else if( roll == 4 )
    os << "_D";
      else if( roll == 5 )
    os << "_E";
      else if( roll == 6 )
    os << "_F";
      else if( roll == 7 )
    os << "_G";
      else if( roll == 8 )
    os << "_H";
      else if( roll == 9 )
    os << "_I";
      else if( roll == 10 )
    os << "_J";
      else if( roll == 11 )
    os << "_K";
      else if( roll == 12 )
    os << "_L";
    }
    _n = os.str();
  }
  return _n;
}

void GEMMuonSegment::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  std::cout << "echo from analyze" << std::endl;
  statistics->Fill(1);
  stationstatistics->Fill(1);
  using namespace edm;

  char layerLabel[128];
//  char meIdRPC [128];
//  char meIdRPCbx [128];
  char meIdGEM [128];
  char meIdGEMbx [128];
//  char meIdDT [128];
  char meIdCSC [128];

/*
   Event Info (Event Auxiliary)
   int evNum  = (iEvent.id()).event();
   int lumNum = (iEvent.id()).luminosityBlock();
   int rnNum  = (iEvent.id()).run();
   if(debug) std::cout<<"--------------- Run: "<<std::setw(6)<<rnNum<<" LumiSection: "<<std::setw(4)<<lumNum<<" Event: "<<std::setw(6)<<evNum<<" ---------------"<<std::endl;
   if(debug) std::cout<<"--------------- Time: "<<std::setw(12)<<(iEvent.time()).value()<<" = "<<std::setw(12)<<(iEvent.time()).unixTime()<<" s since Jan 1, 1970---------------"<<std::endl;

  rnNumber->Fill(rnNum);
  unixeventtime->Fill((iEvent.time()).unixTime());
*/
  //-------------Filling Other Histograms for correlations -----------
/*
  if(debug) std::cout<<"\t Getting the DT Segments"<<std::endl;
  edm::Handle<DTRecSegment4DCollection> all4DSegments;
  iEvent.getByToken(dt4DSegments, all4DSegments);
  if(debug) std::cout<<"I got the segments"<<std::endl;
*/  
  if(debug) std::cout <<"\t Getting the CSC Segments"<<std::endl;
  edm::Handle<CSCSegmentCollection> allCSCSegments;
  iEvent.getByToken(cscSegments, allCSCSegments);
  if(debug) std::cout<<"I got the segments"<<std::endl;
  
//  if(debug && all4DSegments->size()==0)
//      std::cout<<"event without DT segments"<<iEvent.id()<<std::endl;

  if (debug && allCSCSegments->size() == 0)
    std::cout << "event without CSC segments" << iEvent.id() << std::endl;

/*
  if(all4DSegments->size()!=0 && all4DSegments->size()<=16)
  {
    statistics->Fill(2);
    statistics->Fill(all4DSegments->size()+2);
  }
*/

  if(allCSCSegments->size()!=0 && allCSCSegments->size()<=16){
    statistics->Fill(2);
    statistics->Fill(allCSCSegments->size()+1);
  }
  
//  if(debug) std::cout <<"\t Getting the RPC RecHits"<<std::endl;
  if(debug) std::cout <<"\t Getting the GEM RecHits"<<std::endl;
//  Handle<RPCRecHitCollection> rpcHits;
//  iEvent.getByToken(rpcRecHitsLabel,rpcHits);
  Handle<GEMRecHitCollection> gemHits;
  iEvent.getByToken(gemRecHitsLabel,gemHits);

/*
  if(debug) std::cout <<"\t Getting the RPC DT Points"<<std::endl;
  edm::Handle<RPCRecHitCollection> rpcDTPoints;
  iEvent.getByToken(rpcDTPointsLabel,rpcDTPoints);
*/

//  if(debug) std::cout <<"\t Getting the RPC CSC Points"<<std::endl;
//  edm::Handle<RPCRecHitCollection> rpcCSCPoints;
//  iEvent.getByToken(rpcCSCPointsLabel,rpcCSCPoints);
  if(debug) std::cout <<"\t Getting the GEM CSC Points"<<std::endl;
  edm::Handle<GEMRecHitCollection> gemCSCPoints;
  iEvent.getByToken(gemCSCPointsLabel,gemCSCPoints);

//  RPCRecHitCollection::const_iterator recHit;
  GEMRecHitCollection::const_iterator recHit;
  
//  for(recHit = rpcHits->begin(); recHit != rpcHits->end(); recHit++){ //Filling DQMOccupancies
  for(recHit = gemHits->begin(); recHit != gemHits->end(); recHit++){ //Filling DQMOccupancies
    
    int cls = recHit->clusterSize();
    int firststrip = recHit->firstClusterStrip();
    int bx = recHit->BunchX();

//    RPCDetId rpcId = recHit->rpcId();
    GEMDetId gemId = recHit->gemId();

//    RPCGeomServ rpcsrv(rpcId);
//    std::string nameRoll = rpcsrv.name();
      std::string nameRoll = GEMname(gemId);

    if(debug) std::cout<<nameRoll<<std::endl;
    
//    sprintf(meIdRPCbx,"BXDistribution_%s",nameRoll.c_str());
    sprintf(meIdGEMbx,"BXDistribution_%s",nameRoll.c_str());

//    sprintf(meIdRPC,"RealDetectedOccupancy_%s",nameRoll.c_str());
    sprintf(meIdGEM,"RealDetectedOccupancy_%s",nameRoll.c_str());
    
    if(debug) std::cout<<"Filling "<<nameRoll<<" with bx="<<bx<<" and cls="<<cls<<std::endl;

    std::map<std::string, MonitorElement*> meMap=meCollection[nameRoll];
//    meMap[meIdRPCbx]->Fill(bx,cls);
    meMap[meIdGEMbx]->Fill(bx,cls);
    for(int stripDetected = firststrip; stripDetected <= firststrip+cls; stripDetected++)
    {
//      meMap[meIdRPC]->Fill(stripDetected-0.5); 
      meMap[meIdGEM]->Fill(stripDetected-0.5); 
    }
//    int rpcRegion = rpcId.region();
//    int rpcStation = rpcId.station();
    int gemRegion = gemId.region();
    int gemStation = gemId.station();
//    if(rpcRegion==0)
    if(gemRegion==0)
    {
      std::cout << "I found a GEM in Barrel - check for something wrong" << std::endl;
/*
      if(rpcStation==1)
        stationstatistics->Fill(6);
      if(rpcStation==2)
        stationstatistics->Fill(7);
      if(rpcStation==3)
        stationstatistics->Fill(8);
      if(rpcStation==4)
        stationstatistics->Fill(9);
*/
    }
    else
    {
      if(gemStation==1)
        stationstatistics->Fill(2);
      if(gemStation==2)
        stationstatistics->Fill(3);
      if(gemStation==3)
        stationstatistics->Fill(4);
      if(gemStation==4)
        stationstatistics->Fill(5);
    }
  }

/*  
  if(rpcDTPoints.isValid() && rpcDTPoints->begin()!=rpcDTPoints->end())
  { //No Empty Predictions
  
    RPCRecHitCollection::const_iterator rpcPoint;
  
    for(rpcPoint = rpcDTPoints->begin(); rpcPoint != rpcDTPoints->end(); rpcPoint++)
    {
      LocalPoint PointExtrapolatedRPCFrame = rpcPoint->localPosition();
      RPCDetId  rpcId = rpcPoint->rpcId();
      
      if(debug) std::cout << rpcId.rawId() << " " << PointExtrapolatedRPCFrame.x() << " " << PointExtrapolatedRPCFrame.y() << std::endl;
            
      double dx=0;
      double dy=0;
      double dz=0;

      DTRecSegment4DCollection::const_iterator segment;  
      for (segment = all4DSegments->begin();segment!=all4DSegments->end(); ++segment)
      {
	DTChamberId DTId = segment->chamberId();
	int dtSector = DTId.sector(); 
	if(dtSector==13)
          dtSector=4;
	if(dtSector==14)
          dtSector=10;
	int rpcStation = DTId.station();
	if(DTId.wheel()==rpcId.ring() && DTId.station()==rpcId.station() && dtSector==rpcId.sector())
        {
	  if(debug) std::cout<<DTId<<std::endl;
	  LocalVector segmentDirection=segment->localDirection();
	  dx=segmentDirection.x();
	  dy=segmentDirection.y();
	  dz=segmentDirection.z();
	  continue;
	}
	if(rpcStation==1)
          stationstatistics->Fill(2);
	if(rpcStation==2)
          stationstatistics->Fill(3);
	if(rpcStation==3)
          stationstatistics->Fill(4);
	if(rpcStation==4)
          stationstatistics->Fill(5);
      }
      
      const RPCRoll * rollasociated = rpcGeo->roll(rpcId);
      GlobalPoint ExtraHitPosGlob = rollasociated->toGlobal(PointExtrapolatedRPCFrame);
      
      const RectangularStripTopology* top_= dynamic_cast<const RectangularStripTopology*> (&(rollasociated->topology()));
      LocalPoint xmin = top_->localPosition(0.);
      if(debug) std::cout<<"DT  \t \t \t xmin of this  Roll "<<xmin<<"cm"<<std::endl;
      LocalPoint xmax = top_->localPosition((float)rollasociated->nstrips());
      if(debug) std::cout<<"DT  \t \t \t xmax of this  Roll "<<xmax<<"cm"<<std::endl;
      float rsize = fabs( xmax.x()-xmin.x() );
      if(debug) std::cout<<"DT  \t \t \t Roll Size "<<rsize<<"cm"<<std::endl;
      float stripl = top_->stripLength();
      float stripw = top_->pitch();

      RPCGeomServ rpcsrv(rpcId);
      std::string nameRoll = rpcsrv.name();
      
      if(debug) std::cout<<"DT  \t \t \t \t The RPCName is "<<nameRoll<<std::endl;		    
      const float stripPredicted = rollasociated->strip(LocalPoint(PointExtrapolatedRPCFrame.x(),PointExtrapolatedRPCFrame.y(),0.)); 
      
      if(debug) std::cout<<"DT  \t \t \t \t Candidate (from DT Segment) STRIP---> "<<stripPredicted<< std::endl;		  
      //---- HISTOGRAM STRIP PREDICTED FROM DT ----
      char detUnitLabel[128];
      sprintf(detUnitLabel ,"%s",nameRoll.c_str());
      sprintf(layerLabel ,"%s",nameRoll.c_str());
      
      std::map<std::string, MonitorElement*> meMap=meCollection[nameRoll];
      
      bool prediction=false;
      
      if(fabs(PointExtrapolatedRPCFrame.x()) < rsize*0.5 &&  fabs(PointExtrapolatedRPCFrame.y()) < stripl*0.5)
      {
	if(fabs(stripPredicted-rollasociated->nstrips())<1.)
          if(debug)
            std::cout<<"DT \t \t \t \t Extrapolating near last strip, Event"<<iEvent.id()<<" stripPredicted="<<stripPredicted<<" Number of strips="<<rollasociated->nstrips()<<std::endl;
	if(fabs(stripPredicted)<1.)
          if(debug) std::cout<<"DT \t \t \t \t Extrapolating near first strip, Event"<<iEvent.id()<<" stripPredicted="<<stripPredicted<<" Number of strips="<<rollasociated->nstrips()<<std::endl;
	
	sprintf(meIdDT,"ExpectedOccupancy_%s",detUnitLabel);
	if(debug)
          std::cout<<"DT \t \t \t \t Filling Expected for "<<meIdDT<<" with "<<stripPredicted<<std::endl;
	meMap[meIdDT]->Fill(stripPredicted);
	prediction = true;
      }
      else
      {
	if(debug)
          std::cout<<"DT \t \t \t \t In fact the extrapolation goes outside the roll was done just for 2D histograms"<<std::endl;
      }
		  
      sprintf(meIdDT,"ExpectedOccupancy2D_%s",detUnitLabel);
      meMap[meIdDT]->Fill(PointExtrapolatedRPCFrame.x(),PointExtrapolatedRPCFrame.y());
      
      //-----------------------------------------------------
      
      
      //-------RecHitPart Just For Residual--------
      int countRecHits = 0;
      int cluSize = 0;
      int bx = 100;
      float minres = 3000.;
      float distbord = 0;
      
      if(debug) std::cout<<"DT  \t \t \t \t Getting RecHits in Roll Asociated"<<std::endl;

      typedef std::pair<RPCRecHitCollection::const_iterator, RPCRecHitCollection::const_iterator> rangeRecHits;
      rangeRecHits recHitCollection =  rpcHits->get(rpcId);
      RPCRecHitCollection::const_iterator recHit;
		  
      for(recHit = recHitCollection.first; recHit != recHitCollection.second ; recHit++) {
	countRecHits++;
	LocalPoint recHitPos=recHit->localPosition();
	float res=PointExtrapolatedRPCFrame.x()- recHitPos.x();
        GlobalPoint recHitPosGlob = rollasociated->toGlobal(recHitPos);

	if(manualalignment)
          res = res - alignmentinfo[rpcId.rawId()];
	if(debug)
          std::cout<<"DT  \t \t \t \t \t Found Rec Hit at "<<res<<"cm of the prediction."<<std::endl;
	if(fabs(res)<fabs(minres))
        {
	  minres=res;
	  cluSize = recHit->clusterSize();
	  bx=recHit->BunchX(); 
	  if(debug)
            std::cout<<"DT  \t \t \t \t \t \t New Min Res "<<res<<"cm. cluSize= "<<cluSize<<std::endl;
	}
      }
      
      bool anycoincidence=false;
      
      if(countRecHits==0){
	  if(debug) std::cout <<"DT \t \t \t \t \t THIS ROLL DOESN'T HAVE ANY RECHIT"<<std::endl;
      }
      else
      {
	assert(minres!=3000);     
	
	if(debug)
          std::cout<<"DT  \t \t \t \t \t PointExtrapolatedRPCFrame.x="<<PointExtrapolatedRPCFrame.x()<<" Minimal Residual="<<minres<<std::endl;
	if(debug)
          std::cout<<"DT  \t \t \t \t \t Minimal Residual less than stripw*rangestrips? minres="<<minres<<" range="<<rangestrips<<" stripw="<<stripw<<" cluSize"<<cluSize<<" <=compare minres with"<<(rangestrips+cluSize*0.5)*stripw<<std::endl;
	
	if(fabs(minres)<=(rangestrips+cluSize*0.5)*stripw)
        {
	  if(debug)
            std::cout<<"DT  \t \t \t \t \t \t True!"<<std::endl;
	  anycoincidence=true;
	}
      }
      
      if(debug)
        std::cout<<"DT  \t \t \t \t \t "<< prediction << anycoincidence << std::endl;

      if(prediction && anycoincidence)
      {
	float distobottom = stripl * 0.5 + PointExtrapolatedRPCFrame.y();

	sprintf(meIdDT,"BXYDistribution_%s",detUnitLabel);
	meMap[meIdDT]->Fill(bx,distobottom);

	//std::cout<<"Filling SIGNAL "<<detUnitLabel<<" with bx="<<bx<<" and cls="<<cluSize<<std::endl;
	sprintf(meIdDT,"Signal_BXDistribution_%s",detUnitLabel);
	meMap[meIdDT]->Fill(bx,cluSize);

	sprintf(meIdDT,"CLSDistribution_%s",detUnitLabel);
	meMap[meIdDT]->Fill(cluSize);
		  
	if(debug)
          std::cout << "DT  \t \t \t \t \t At least one RecHit inside the range, Predicted=" << stripPredicted << " minres=" << minres << "cm range=" << rangestrips << "strips stripw=" << stripw << "cm" << std::endl;
	if(debug)
          std::cout << "DT  \t \t \t \t \t Norm of Cosine Directors=" << dx*dx+dy*dy+dz*dz << "~1?" << std::endl;
		    
	//-----RESIDUALS----------
	if(inves)
        {
	  float cosal = dx/sqrt(dx*dx+dz*dz);
	  float cosalp = dy/sqrt(dy*dy+dz*dz);

	  if(rpcId.station()==4)
          {
	    cosalp = 0;
	  }

	  float angle = acos(cosal)*180/3.1415926;
	  float anglep = acos(cosalp)*180/3.1415926;

	  if(debug) std::cout<<"DT \t \t \t \t \t Angle="<<angle<<" degree"<<std::endl;
		      
	  //Filling Residuals
	  //Filling High Resolution Histograms
	  if(cluSize == 1*dupli)
          {
	    distbord = minres/stripw + 0.5;
	  }
          else if(cluSize == 2*dupli)
          {
	    distbord = minres/stripw;				
	  }
          else if(cluSize == 3*dupli)
          {
	    distbord = minres/stripw + 0.5;
	  }
		      
	  if(debug) std::cout<<"DT \t \t \t \t \t Filling high resolution histograms with distbord="<<distbord
			     <<" cosal="<<cosal
			     <<" cls="<<cluSize<<std::endl;
	}
		    
	if(cluSize == 1*dupli)
        {
	  sprintf(meIdRPC,"RPCResiduals_Clu1_%s",detUnitLabel);
	  meMap[meIdRPC]->Fill(minres);
	}
        else if(cluSize == 2*dupli)
        {
	  sprintf(meIdRPC,"RPCResiduals_Clu2_%s",detUnitLabel);
	  meMap[meIdRPC]->Fill(minres);
	}
        else if(cluSize == 3*dupli)
        {
	  sprintf(meIdRPC,"RPCResiduals_Clu3_%s",detUnitLabel);
	  meMap[meIdRPC]->Fill(minres);
	}
        else
        {
	  sprintf(meIdRPC,"RPCResiduals_Other_%s",detUnitLabel);
	  meMap[meIdRPC]->Fill(minres);
	}
      
	if(debug) std::cout<<"DT \t \t \t \t \t Filling Residuals "<<meIdRPC<<std::endl;

	sprintf(meIdRPC,"RPCDataOccupancy_%s",detUnitLabel);
	meMap[meIdRPC]->Fill(stripPredicted);
		    
	if(debug) std::cout<<"DT \t \t \t \t \t COINCIDENCE!!! Event="<<iEvent.id()<<" Filling RPC Data Occupancy for "<<meIdRPC<<" with "<<stripPredicted<<std::endl;
	
      }
		  
      if(anycoincidence)
      {
	if(debug)
          std::cout<<"DT \t \t \t \t \t Filling 2D histo for RPC Occupancy "<<meIdRPC<<std::endl; 		    
	sprintf(meIdRPC,"RPCDataOccupancy2D_%s",detUnitLabel);
	meMap[meIdRPC]->Fill(PointExtrapolatedRPCFrame.x(),PointExtrapolatedRPCFrame.y());
      }
      else if(prediction)
      {
	RPCGeomServ rpcsrv(rpcId);
	std::string nameRoll = rpcsrv.name();
	
	sprintf(meIdRPC,"Inefficiency2D_%s",detUnitLabel);
	meMap[meIdRPC]->Fill(PointExtrapolatedRPCFrame.x(),PointExtrapolatedRPCFrame.y());
	
	if(debug) std::cout<<"DT \t \t \t \t \t A roll was ineficient in event "<<iEvent.id().event()<<std::endl;
	if(debug) ofrej<<"DTs \t Wh "<<rpcId.ring()
		       <<"\t St "<<rpcId.station()
		       <<"\t Se "<<rpcId.sector()
		       <<"\t Roll "<<nameRoll
		       <<"\t Event "
		       <<iEvent.id().event()
		       <<"\t Run "	
		       <<iEvent.id().run()	
		       <<std::endl;
      }
    }
  }
  else
  {
    if(debug)
      std::cout<<"DT This Event doesn't have any DT4DDSegment"<<std::endl; //is there more than 1 segment in this event?
  }
*/
  

//  if(rpcCSCPoints.isValid() && (rpcCSCPoints->begin()!=rpcCSCPoints->end())){//No Empty Predictions
//    RPCRecHitCollection::const_iterator rpcPoint;
  if(gemCSCPoints.isValid() && (gemCSCPoints->begin()!=gemCSCPoints->end())){//No Empty Predictions
    GEMRecHitCollection::const_iterator gemPoint;
  
//    for(rpcPoint = rpcCSCPoints->begin(); rpcPoint != rpcCSCPoints->end(); rpcPoint++){
    for(gemPoint = gemCSCPoints->begin(); gemPoint != gemCSCPoints->end(); gemPoint++){
//      LocalPoint PointExtrapolatedRPCFrame = rpcPoint->localPosition();
      LocalPoint PointExtrapolatedGEMFrame = gemPoint->localPosition();

//      RPCDetId  rpcId = rpcPoint->rpcId();
      GEMDetId  gemId = gemPoint->gemId();
//      RPCGeomServ rpcsrv(rpcId);

      if(debug)
//        std::cout<<rpcId.rawId()<<" "<<PointExtrapolatedRPCFrame.x()<<" "<<PointExtrapolatedRPCFrame.y()<<std::endl;
        std::cout<<gemId.rawId()<<" "<<PointExtrapolatedGEMFrame.x()<<" "<<PointExtrapolatedGEMFrame.y()<<std::endl;

      double dx=0;
      double dy=0;
      double dz=0;

      CSCSegmentCollection::const_iterator segment;  

      CSCDetId CSCId;
      for (segment = allCSCSegments->begin();segment!=allCSCSegments->end(); ++segment)
      {
	CSCId = segment->cscDetId();
//	int rpcRegion = 1;
	int gemRegion = 1;
        if(CSCId.endcap()==2)
//          rpcRegion= -1;//Relacion entre las endcaps
          gemRegion= -1;//Relacion entre las endcaps
//	int rpcRing = CSCId.ring();
	int gemRing = CSCId.ring();
//	int rpcStation = CSCId.station();
	int gemStation = CSCId.station();
//	if(rpcRing==4) rpcRing =1;
	if(gemRing==4) gemRing =1;

//	if(rpcRegion==rpcId.region() && CSCId.station()==rpcId.station() && rpcRing == rpcId.ring() && CSCId.chamber()==rpcsrv.segment())
	if(gemRegion==gemId.region() && CSCId.station()==gemId.station() && gemRing == gemId.ring() && CSCId.chamber()==gemId.chamber())	//change this gem chamber is 20 degree, CSC chamber is 10 degree
        {
	  LocalVector segmentDirection=segment->localDirection();
	  dx=segmentDirection.x();
	  dy=segmentDirection.y();
	  dz=segmentDirection.z();
	  continue;
	}
//	if(rpcStation==1) stationstatistics->Fill(10);
//	if(rpcStation==2) stationstatistics->Fill(11);
//	if(rpcStation==3) stationstatistics->Fill(12);
//	if(rpcStation==4) stationstatistics->Fill(13);
	if(gemStation==1) stationstatistics->Fill(2);
	if(gemStation==2) stationstatistics->Fill(3);
	if(gemStation==3) stationstatistics->Fill(4);
	if(gemStation==4) stationstatistics->Fill(5);
      }
      
//      const RPCRoll * rollasociated = rpcGeo->roll(rpcId);
      const GEMEtaPartition* rollasociated = gemGeo->etaPartition(gemId);

//        GlobalPoint ExtraHitPosGlob = rollasociated->toGlobal(PointExtrapolatedRPCFrame);
        GlobalPoint ExtraHitPosGlob = rollasociated->toGlobal(PointExtrapolatedGEMFrame);
        if(rollasociated->id().region() == 1)
        {
          if(rollasociated->id().station()==1) XY_globalGE1_extra->Fill(ExtraHitPosGlob.x(), ExtraHitPosGlob.y());
          if(rollasociated->id().station()==2) XY_globalGE2_extra->Fill(ExtraHitPosGlob.x(), ExtraHitPosGlob.y());
        }

        if(rollasociated->id().region() == -1)
        {
          if(rollasociated->id().station()==1) XY_globalGEm1_extra->Fill(ExtraHitPosGlob.x(), ExtraHitPosGlob.y());
          if(rollasociated->id().station()==2) XY_globalGEm2_extra->Fill(ExtraHitPosGlob.x(), ExtraHitPosGlob.y());
        }
      
      const TrapezoidalStripTopology* top_=dynamic_cast<const TrapezoidalStripTopology*>(&(rollasociated->topology()));
      LocalPoint xmin = top_->localPosition(0.);
      if(debug)
        std::cout << "CSC \t \t \t xmin of this  Roll " << xmin << "cm" << std::endl;
      LocalPoint xmax = top_->localPosition((float)rollasociated->nstrips());
      if(debug)
        std::cout << "CSC \t \t \t xmax of this  Roll " << xmax << "cm" << std::endl;
      float rsize = fabs( xmax.x()-xmin.x() );
      if(debug)
        std::cout << "CSC \t \t \t Roll Size " << rsize << "cm" << std::endl;
      float stripl = top_->stripLength();
      float stripw = top_->pitch();
      
//      std::string nameRoll = rpcsrv.name();
      std::string nameRoll = GEMname(gemId);
      if(debug)
//        std::cout << "CSC \t \t \t \t The RPCName is " << nameRoll << std::endl;
        std::cout << "CSC \t \t \t \t The GEMName is " << nameRoll << std::endl;
      
//      const float stripPredicted = rollasociated->strip(LocalPoint(PointExtrapolatedRPCFrame.x(),PointExtrapolatedRPCFrame.y(),0.)  );
      const float stripPredicted = rollasociated->strip(LocalPoint(PointExtrapolatedGEMFrame.x(),PointExtrapolatedGEMFrame.y(),0.)  );
       
//      if(debug) std::cout << "CSC  \t \t \t \t \t Candidate" << rpcId << " " << "(from CSC Segment) STRIP---> " << stripPredicted << std::endl;
      if(debug) std::cout << "CSC  \t \t \t \t \t Candidate" << gemId << " " << "(from CSC Segment) STRIP---> " << stripPredicted << std::endl;
      
      //--------- HISTOGRAM STRIP PREDICTED FROM CSC  -------------------
      
      char detUnitLabel[128];
      sprintf(detUnitLabel ,"%s",nameRoll.c_str());
      sprintf(layerLabel ,"%s",nameRoll.c_str());
      
      std::map<std::string, MonitorElement*> meMap=meCollection[nameRoll];
      
      bool prediction=false;
      
//      if(fabs(PointExtrapolatedRPCFrame.x()) < rsize*0.5 &&  fabs(PointExtrapolatedRPCFrame.y()) < stripl*0.5)
      if(fabs(PointExtrapolatedGEMFrame.x()) < rsize*0.5 &&  fabs(PointExtrapolatedGEMFrame.y()) < stripl*0.5)
     {
	if(fabs(stripPredicted-rollasociated->nstrips())<1.)
          if(debug) std::cout<<"CSC \t \t \t \t Extrapolating near last strip, Event"<<iEvent.id()<<" stripPredicted="<<stripPredicted<<" Number of strips="<<rollasociated->nstrips()<<std::endl;
	if(fabs(stripPredicted)<1.)
          if(debug) std::cout<<"CSC \t \t \t \t Extrapolating near first strip, Event"<<iEvent.id()<<" stripPredicted="<<stripPredicted<<" Number of strips="<<rollasociated->nstrips()<<std::endl;
	sprintf(meIdCSC,"ExpectedOccupancy_%s",detUnitLabel);
	if(debug) std::cout << "CSC \t \t \t \t Filling Expected for " << meIdCSC << " with " << stripPredicted << std::endl;
	meMap[meIdCSC]->Fill(stripPredicted);
	prediction = true;
      }
      else
      {
	if(debug) std::cout<<"CSC \t \t \t \t In fact the extrapolation goes outside the roll was done just for 2D histograms"<<std::endl;
      }
      
//      sprintf(meIdDT,"ExpectedOccupancy2D_%s",detUnitLabel);
//      meMap[meIdDT]->Fill(PointExtrapolatedRPCFrame.x(),PointExtrapolatedRPCFrame.y());
//      meMap[meIdDT]->Fill(PointExtrapolatedGEMFrame.x(),PointExtrapolatedGEMFrame.y());
      
      //--------------------------------------------------------------------
	    		
      //-------RecHitPart Just For Residual--------
      int cluSize = 0;
      int bx =0;
      int countRecHits = 0;
      float minres = 3000.;
      
      if(debug)
        std::cout<<"CSC  \t \t \t \t \t Getting RecHits in Roll Asociated"<<std::endl;

//      typedef std::pair<RPCRecHitCollection::const_iterator, RPCRecHitCollection::const_iterator> rangeRecHits;
      typedef std::pair<GEMRecHitCollection::const_iterator, GEMRecHitCollection::const_iterator> rangeRecHits;
//      rangeRecHits recHitCollection =  rpcHits->get(rollasociated->id());
      rangeRecHits recHitCollection =  gemHits->get(rollasociated->id());
//      RPCRecHitCollection::const_iterator recHit;
      GEMRecHitCollection::const_iterator recHit;
      
      for (recHit = recHitCollection.first; recHit != recHitCollection.second ; recHit++)
      {
	countRecHits++;
	LocalPoint recHitPos=recHit->localPosition();
//	float res=PointExtrapolatedRPCFrame.x()- recHitPos.x();
	float res=PointExtrapolatedGEMFrame.x()- recHitPos.x();

        GlobalPoint recHitPosGlob = rollasociated->toGlobal(recHitPos);
        if(rollasociated->id().region()==1)
        {
          if(rollasociated->id().station()==1) XY_globalGE1->Fill(recHitPosGlob.x(), recHitPosGlob.y());
          if(rollasociated->id().station()==2) XY_globalGE2->Fill(recHitPosGlob.x(), recHitPosGlob.y());
        }

        if(rollasociated->id().region()==-1)
        {
          if(rollasociated->id().station()==1) XY_globalGEm1->Fill(recHitPosGlob.x(), recHitPosGlob.y());
          if(rollasociated->id().station()==2) XY_globalGEm2->Fill(recHitPosGlob.x(), recHitPosGlob.y());
        }

        //*straighter(rollasociated->id());//Corrections to the wrong orientations
//rumi uncomment manualalignment
	if(manualalignment) res = res - alignmentinfo[gemId.rawId()];
	if(debug) std::cout<<"CSC  \t \t \t \t \t \t Found Rec Hit at "<<res<<"cm of the prediction."<<std::endl;
	if(fabs(res)<fabs(minres))
        {
	  minres=res;
	  cluSize = recHit->clusterSize();
	  bx = recHit->BunchX();
	  if(debug) std::cout<<"CSC  \t \t \t \t \t \t \t New Min Res "<<res<<"cm."<<std::endl;
	}
      }
      
      bool anycoincidence = false;
      
      if(countRecHits==0)
      {
	if(debug) std::cout <<"CSC \t \t \t \t \t THIS ROLL DOESN'T HAVE ANY RECHIT"<<std::endl;
      }
      else
      {  
	assert(minres!=3000); 
	
	if(debug)
//          std::cout<<"CSC \t \t \t \t \t PointExtrapolatedRPCFrame.x="<<PointExtrapolatedRPCFrame.x()<<" Minimal Residual"<<minres<<std::endl;
          std::cout<<"CSC \t \t \t \t \t PointExtrapolatedGEMFrame.x="<<PointExtrapolatedGEMFrame.x()<<" Minimal Residual"<<minres<<std::endl;
	if(debug)
          std::cout<<"CSC  \t \t \t \t \t Minimal Residual less than stripw*rangestrips? minres="<<minres<<" range="<<rangestrips<<" stripw="<<stripw<<" cluSize"<<cluSize<<" <=compare minres with"<<(rangestrips+cluSize*0.5)*stripw<<std::endl;
	if(fabs(minres)<=(rangestrips+cluSize*0.5)*stripw)
        {
	  if(debug) std::cout << "CSC  \t \t \t \t \t \t True!" << std::endl;
	  anycoincidence=true;
	}
      }
      
      if(debug) std::cout<<"CSC  \t \t \t \t \t "<< prediction << "\t" << anycoincidence << std::endl;
      
      if(prediction && anycoincidence)
      {
//	float distobottom = stripl*0.5 + PointExtrapolatedRPCFrame.y(); //For the endcaps we should check where are the CONTACTSSS!!!
	float distobottom = stripl*0.5 + PointExtrapolatedGEMFrame.y();
	
	sprintf(meIdCSC,"BXYDistribution_%s",detUnitLabel);
	meMap[meIdCSC]->Fill(bx,distobottom);
	
//	sprintf(meIdDT,"Signal_BXDistribution_%s",detUnitLabel);
//	meMap[meIdDT]->Fill(bx,cluSize);
		      
	sprintf(meIdCSC,"CLSDistribution_%s",detUnitLabel);
	meMap[meIdCSC]->Fill(cluSize);
	
	if(debug)
        {
          std::cout<<"CSC  \t \t \t \t \t At least one RecHit inside the range, Predicted="<<stripPredicted<<" minres="<<minres<<"cm range="<<rangestrips<<"strips stripw="<<stripw<<"cm"<<std::endl;
          std::cout<<"CSC  \t \t \t \t \t Norm of Cosine Directors="<<dx*dx+dy*dy+dz*dz<<"~1?"<<std::endl;
        }
	
	//----RESIDUALS----

	if(inves){
	  float cosal = dx/sqrt(dx*dx+dz*dz);
	  float angle = acos(cosal)*180/3.1415926;

          ScatterPlotAngCLSEndcaps->Fill(angle,cluSize);
              
          if(cluSize==1*dupli) AngClu1Endcaps->Fill(angle);
          if(cluSize==2*dupli) AngClu2Endcaps->Fill(angle);
          if(cluSize==3*dupli) AngClu3Endcaps->Fill(angle);

	  if(debug) std::cout<<"CSC \t \t \t \t \t Angle="<<angle<<" degree"<<std::endl;

	  //Filling Residuals
            if(!(gemId.ring()==1)) {std::cout << "something is wrong - GEM is on the ring = " << gemId.ring() << std::endl; continue;}
            if(gemId.station() == 1)
            {
              if (cluSize == 1 * dupli)
              {
                if(gemId.roll() == 1) hGlobalResClu1GE11_1->Fill(minres);
                else if(gemId.roll() == 2) hGlobalResClu1GE11_2->Fill(minres);
                else if(gemId.roll() == 3) hGlobalResClu1GE11_3->Fill(minres);
                else if(gemId.roll() == 4) hGlobalResClu1GE11_4->Fill(minres);
                else if(gemId.roll() == 5) hGlobalResClu1GE11_5->Fill(minres);
                else if(gemId.roll() == 6) hGlobalResClu1GE11_6->Fill(minres);
                else if(gemId.roll() == 7) hGlobalResClu1GE11_7->Fill(minres);
                else if(gemId.roll() == 8) hGlobalResClu1GE11_8->Fill(minres);
                else std::cout << "more than 8 rolls in a GEM chamber, please fix the hardcoded values" << std::endl;
              }
              if (cluSize == 2 * dupli)
              {
                if(gemId.roll() == 1) hGlobalResClu2GE11_1->Fill(minres);
                else if(gemId.roll() == 2) hGlobalResClu2GE11_2->Fill(minres);
                else if(gemId.roll() == 3) hGlobalResClu2GE11_3->Fill(minres);
                else if(gemId.roll() == 4) hGlobalResClu2GE11_4->Fill(minres);
                else if(gemId.roll() == 5) hGlobalResClu2GE11_5->Fill(minres);
                else if(gemId.roll() == 6) hGlobalResClu2GE11_6->Fill(minres);
                else if(gemId.roll() == 7) hGlobalResClu2GE11_7->Fill(minres);
                else if(gemId.roll() == 8) hGlobalResClu2GE11_8->Fill(minres);
                else std::cout << "more than 8 rolls in a GEM chamber, please fix the hardcoded values" << std::endl;
              }
              if (cluSize == 3 * dupli)
              {
                if(gemId.roll() == 1) hGlobalResClu3GE11_1->Fill(minres);
                else if(gemId.roll() == 2) hGlobalResClu3GE11_2->Fill(minres);
                else if(gemId.roll() == 3) hGlobalResClu3GE11_3->Fill(minres);
                else if(gemId.roll() == 4) hGlobalResClu3GE11_4->Fill(minres);
                else if(gemId.roll() == 5) hGlobalResClu3GE11_5->Fill(minres);
                else if(gemId.roll() == 6) hGlobalResClu3GE11_6->Fill(minres);
                else if(gemId.roll() == 7) hGlobalResClu3GE11_7->Fill(minres);
                else if(gemId.roll() == 8) hGlobalResClu3GE11_8->Fill(minres);
                else std::cout << "more than 8 rolls in a GEM chamber, please fix the hardcoded values" << std::endl;
              }
            }
            if(gemId.station() == 2)
            {
              if (cluSize == 1 * dupli)
              {
                if(gemId.roll() == 1) hGlobalResClu1GE21_1->Fill(minres);
                else if(gemId.roll() == 2) hGlobalResClu1GE21_2->Fill(minres);
                else if(gemId.roll() == 3) hGlobalResClu1GE21_3->Fill(minres);
                else if(gemId.roll() == 4) hGlobalResClu1GE21_4->Fill(minres);
                else if(gemId.roll() == 5) hGlobalResClu1GE21_5->Fill(minres);
                else if(gemId.roll() == 6) hGlobalResClu1GE21_6->Fill(minres);
                else if(gemId.roll() == 7) hGlobalResClu1GE21_7->Fill(minres);
                else if(gemId.roll() == 8) hGlobalResClu1GE21_8->Fill(minres);
                else std::cout << "more than 8 rolls in a GEM chamber, please fix the hardcoded values" << std::endl;
              }
              if (cluSize == 2 * dupli)
              {
                if(gemId.roll() == 1) hGlobalResClu2GE21_1->Fill(minres);
                else if(gemId.roll() == 2) hGlobalResClu2GE21_2->Fill(minres);
                else if(gemId.roll() == 3) hGlobalResClu2GE21_3->Fill(minres);
                else if(gemId.roll() == 4) hGlobalResClu2GE21_4->Fill(minres);
                else if(gemId.roll() == 5) hGlobalResClu2GE21_5->Fill(minres);
                else if(gemId.roll() == 6) hGlobalResClu2GE21_6->Fill(minres);
                else if(gemId.roll() == 7) hGlobalResClu2GE21_7->Fill(minres);
                else if(gemId.roll() == 8) hGlobalResClu2GE21_8->Fill(minres);
                else std::cout << "more than 8 rolls in a GEM chamber, please fix the hardcoded values" << std::endl;
              }
              if (cluSize == 3 * dupli)
              {
                if(gemId.roll() == 1) hGlobalResClu3GE21_1->Fill(minres);
                else if(gemId.roll() == 2) hGlobalResClu3GE21_2->Fill(minres);
                else if(gemId.roll() == 3) hGlobalResClu3GE21_3->Fill(minres);
                else if(gemId.roll() == 4) hGlobalResClu3GE21_4->Fill(minres);
                else if(gemId.roll() == 5) hGlobalResClu3GE21_5->Fill(minres);
                else if(gemId.roll() == 6) hGlobalResClu3GE21_6->Fill(minres);
                else if(gemId.roll() == 7) hGlobalResClu3GE21_7->Fill(minres);
                else if(gemId.roll() == 8) hGlobalResClu3GE21_8->Fill(minres);
                else std::cout << "more than 8 rolls in a GEM chamber, please fix the hardcoded values" << std::endl;
              }
            }
	  //------------------------
	}
	
	if(cluSize == 1*dupli)
        {
//	  sprintf(meIdRPC,"RPCResiduals_Clu1_%s",detUnitLabel);
//	  meMap[meIdRPC]->Fill(minres);
	  sprintf(meIdGEM,"GEMResiduals_Clu1_%s",detUnitLabel);
	  meMap[meIdGEM]->Fill(minres);
	}
        else if(cluSize == 2*dupli)
        {
//	  sprintf(meIdRPC,"RPCResiduals_Clu2_%s",detUnitLabel);
//	  meMap[meIdRPC]->Fill(minres);
	  sprintf(meIdGEM,"GEMResiduals_Clu2_%s",detUnitLabel);
	  meMap[meIdGEM]->Fill(minres);
	}
        else if(cluSize == 3*dupli)
        {
	  sprintf(meIdGEM,"GEMResiduals_Clu3_%s",detUnitLabel);
	  meMap[meIdGEM]->Fill(minres);
	}
        else
        {
	  sprintf(meIdGEM,"GEMResiduals_Other_%s",detUnitLabel);
	  meMap[meIdGEM]->Fill(minres);
	}
	
//	sprintf(meIdRPC,"RPCDataOccupancy_%s",detUnitLabel);
//	meMap[meIdRPC]->Fill(stripPredicted);
	sprintf(meIdGEM,"GEMDataOccupancy_%s",detUnitLabel);
	meMap[meIdGEM]->Fill(stripPredicted);
	
//	if(debug) std::cout <<"CSC \t \t \t \t \t \t COINCEDENCE!!! Event="<<iEvent.id()<<"Filling Filling RPC Data Occupancy for "<<meIdRPC<<" with "<<stripPredicted<<std::endl;
	if(debug) std::cout <<"CSC \t \t \t \t \t \t COINCEDENCE!!! Event="<<iEvent.id()<<"Filling Filling GEM Data Occupancy for "<<meIdGEM<<" with "<<stripPredicted<<std::endl;
      }//prediction && anycoincidence
      
      if(anycoincidence)
      {
//	if(debug) std::cout<<"CSC \t \t \t \t \t \t Filling 2D histo for RPC Occupancy "<<meIdRPC<<std::endl; 	
	if(debug) std::cout<<"CSC \t \t \t \t \t \t Filling 2D histo for GEM Occupancy "<<meIdGEM<<std::endl; 	
//	sprintf(meIdRPC,"RPCDataOccupancy2D_%s",detUnitLabel);
	sprintf(meIdGEM,"GEMDataOccupancy2D_%s",detUnitLabel);
//	meMap[meIdRPC]->Fill(PointExtrapolatedRPCFrame.x(),PointExtrapolatedRPCFrame.y());
	meMap[meIdGEM]->Fill(PointExtrapolatedGEMFrame.x(),PointExtrapolatedGEMFrame.y());
      }//anycoincidence
      else if(prediction)
      {
//	RPCGeomServ rpcsrv(rollasociated->id());
//	std::string nameRoll = rpcsrv.name();
        std::string nameRoll = GEMname(gemId);
	
//	sprintf(meIdRPC,"Inefficiency2D_%s",detUnitLabel);
	sprintf(meIdGEM,"Inefficiency2D_%s",detUnitLabel);
//	meMap[meIdRPC]->Fill(PointExtrapolatedRPCFrame.x(),PointExtrapolatedRPCFrame.y());
	meMap[meIdGEM]->Fill(PointExtrapolatedGEMFrame.x(),PointExtrapolatedGEMFrame.y());
	
	if(debug) std::cout<<"CSC \t \t \t \t \t \t A roll was ineficient in event"<<iEvent.id().event()<<std::endl;
//	if(debug) ofrej<<"CSC \t EndCap " << rpcId.region() <<"\t Roll "<<nameRoll <<"\t CSCId "<<CSCId <<"\t Event " <<iEvent.id().event() << "\t Run " << iEvent.id().run() << std::endl;
	if(debug) ofrej<<"CSC \t EndCap " << gemId.region() <<"\t Roll "<<nameRoll <<"\t CSCId "<<CSCId <<"\t Event " <<iEvent.id().event() << "\t Run " << iEvent.id().run() << std::endl;
      }
      else
      {
	if(debug)
          std::cout << "CSC \t \t \t \t No the prediction is outside of this roll" << std::endl;
      }//Condition for the right match
    }
  }
}

void GEMMuonSegment::endRun(const edm::Run& r, const edm::EventSetup& iSetup){
}


void GEMMuonSegment::endJob()
{
  std::cout<<"saving root file"<<std::endl;
  if (EffSaveRootFile){
    dbe->save(EffRootFileName);
  }
  dbe = 0;
}

DEFINE_FWK_MODULE(GEMMuonSegment);
