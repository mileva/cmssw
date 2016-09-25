/***************************************
Original Author: 
Camilo Carrillo
Universidad de los Andes Bogota Colombia
camilo.carrilloATcern.ch
Modified for GEM:
Roumyana Hadjiiska
****************************************/

#include "DQM/GEMResoModule/interface/GEMMuonSegmentPseudo.h"
#include <memory>
#include "FWCore/Framework/interface/MakerMacros.h"
#include <DataFormats/GEMDigi/interface/GEMDigiCollection.h>
#include "DataFormats/GEMRecHit/interface/GEMRecHitCollection.h"
#include <DataFormats/MuonDetId/interface/GEMDetId.h>
#include <DataFormats/CSCRecHit/interface/CSCSegmentCollection.h>
#include <Geometry/CommonDetUnit/interface/GeomDet.h>
#include <Geometry/Records/interface/MuonGeometryRecord.h>
#include <Geometry/CommonTopologies/interface/TrapezoidalStripTopology.h>
#include "Geometry/GEMGeometry/interface/GEMEtaPartitionSpecs.h"
#include "DataFormats/GeometrySurface/interface/LocalError.h"

#include <cmath>
#include "TFile.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "TString.h"

#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/Utilities/interface/EDGetToken.h"

void GEMMuonSegmentPseudo::beginJob(){
  firstbook=true;
}

GEMMuonSegmentPseudo::GEMMuonSegmentPseudo(const edm::ParameterSet& iConfig){
  debug=iConfig.getUntrackedParameter<bool>("debug",true);
  inves=iConfig.getUntrackedParameter<bool>("inves");

  cscSegments = consumes<CSCSegmentCollection>(iConfig.getUntrackedParameter < edm::InputTag > ("cscSegments"));
  gemRecHitsLabel = consumes<GEMRecHitCollection>(iConfig.getUntrackedParameter < edm::InputTag > ("gemRecHits"));
  gemCSCPointsLabel = consumes<GEMRecHitCollection>(iConfig.getUntrackedParameter < edm::InputTag > ("gemCSCPoints"));
  
  nameInLog = iConfig.getUntrackedParameter<std::string>("moduleLogName", "GEM_CSCseg");
  EffSaveRootFile  = iConfig.getUntrackedParameter<bool>("EffSaveRootFile", false); 
  EffRootFileName  = iConfig.getUntrackedParameter<std::string>("EffRootFileName", "GEMMuonSegmentPseudo.root"); 
    
  //Interface
  dbe = edm::Service<DQMStore>().operator->();
  std::string folder = "Muons/MuonSegEff/";
  dbe->setCurrentFolder(folder);

  stationstatistics = dbe->book1D("StationStatistics","All Statistics by Station",5,0.5,5.5);
  statistics = dbe->book1D("Statistics","All Statistics",17,0.5,17.5);

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
  stationstatistics->setBinLabel(4,"Events with GE22 rechits",1);
  stationstatistics->setBinLabel(5,"Events with RE41 rechits",1);
  
  if(debug) std::cout<<"booking Global histograms Change statistics"<<std::endl;

  folder = "Muons/MuonSegEff/Investigation";
  dbe->setCurrentFolder(folder);

  //Ang Dependence
  AngSigma1Endcaps = dbe->book1D("AngSigma1Endcaps","Angle of incident Muon Endcaps 1*recHitErrorX",100,0.,360.);
  AngSigma2Endcaps = dbe->book1D("AngSigma2Endcaps","Angle of incident Muon Endcaps 2*recHitErrorX",100,0.,360.); 
  AngSigma3Endcaps = dbe->book1D("AngSigma3Endcaps","Angle of incident Muon Endcaps 3*recHitErrorX",100,0.,360.); 
  AngSigmaAnyEndcaps = dbe->book1D("AngSigmaAnyEndcaps","Angle of incident Muon Endcaps > 3*recHitErrorX",100,0.,360.); 

  if(debug) std::cout<<"Booking Residuals for EndCap"<<std::endl;
  folder = "Muons/MuonSegEff/Residuals/GE11";
  dbe->setCurrentFolder(folder);

  //Endcap GE11
  hGlobalResAllClsGE11_1 = dbe->book1D("GlobalResidualsAllClsGE11_1","GEM Residuals GE11 Roll 1",50000, -2.5, 2.5);
  hGlobalResAllClsGE11_2 = dbe->book1D("GlobalResidualsAllClsGE11_2","GEM Residuals GE11 Roll 2",50000, -2.5, 2.5);
  hGlobalResAllClsGE11_3 = dbe->book1D("GlobalResidualsAllClsGE11_3","GEM Residuals GE11 Roll 3",50000, -2.5, 2.5);
  hGlobalResAllClsGE11_4 = dbe->book1D("GlobalResidualsAllClsGE11_4","GEM Residuals GE11 Roll 4",50000, -2.5, 2.5);
  hGlobalResAllClsGE11_5 = dbe->book1D("GlobalResidualsAllClsGE11_5","GEM Residuals GE11 Roll 5",50000, -2.5, 2.5);
  hGlobalResAllClsGE11_6 = dbe->book1D("GlobalResidualsAllClsGE11_6","GEM Residuals GE11 Roll 6",50000, -2.5, 2.5);
  hGlobalResAllClsGE11_7 = dbe->book1D("GlobalResidualsAllClsGE11_7","GEM Residuals GE11 Roll 7",50000, -2.5, 2.5);
  hGlobalResAllClsGE11_8 = dbe->book1D("GlobalResidualsAllClsGE11_8","GEM Residuals GE11 Roll 8",50000, -2.5, 2.5);

  folder = "Muons/MuonSegEff/Residuals/GE21";
  dbe->setCurrentFolder(folder);

  //Endcap GE21
  hGlobalResAllClsGE21_1 = dbe->book1D("GlobalResidualsAllClsGE21_1","GEM Residuals GE21 Roll 1",50000, -2.5, 2.5);
  hGlobalResAllClsGE21_2 = dbe->book1D("GlobalResidualsAllClsGE21_2","GEM Residuals GE21 Roll 2",50000, -2.5, 2.5);
  hGlobalResAllClsGE21_3 = dbe->book1D("GlobalResidualsAllClsGE21_3","GEM Residuals GE21 Roll 3",50000, -2.5, 2.5);
  hGlobalResAllClsGE21_4 = dbe->book1D("GlobalResidualsAllClsGE21_4","GEM Residuals GE21 Roll 4",50000, -2.5, 2.5);
  hGlobalResAllClsGE21_5 = dbe->book1D("GlobalResidualsAllClsGE21_5","GEM Residuals GE21 Roll 5",50000, -2.5, 2.5);
  hGlobalResAllClsGE21_6 = dbe->book1D("GlobalResidualsAllClsGE21_6","GEM Residuals GE21 Roll 6",50000, -2.5, 2.5);
  hGlobalResAllClsGE21_7 = dbe->book1D("GlobalResidualsAllClsGE21_7","GEM Residuals GE21 Roll 7",50000, -2.5, 2.5);
  hGlobalResAllClsGE21_8 = dbe->book1D("GlobalResidualsAllClsGE21_8","GEM Residuals GE21 Roll 8",50000, -2.5, 2.5);

  folder = "Muons/MuonSegEff/Residuals/GE22DeltaX";
  dbe->setCurrentFolder(folder);

  //Endcap GE22
  hGlobalResAllClsGE22_1 = dbe->book1D("GlobalResidualsAllClsGE22_1","GEM Residuals GE22 Roll 1",50000, -2.5, 2.5);
  hGlobalResAllClsGE22_2 = dbe->book1D("GlobalResidualsAllClsGE22_2","GEM Residuals GE22 Roll 2",50000, -2.5, 2.5);
  hGlobalResAllClsGE22_3 = dbe->book1D("GlobalResidualsAllClsGE22_3","GEM Residuals GE22 Roll 3",50000, -2.5, 2.5);
  hGlobalResAllClsGE22_4 = dbe->book1D("GlobalResidualsAllClsGE22_4","GEM Residuals GE22 Roll 4",50000, -2.5, 2.5);
  hGlobalResAllClsGE22_5 = dbe->book1D("GlobalResidualsAllClsGE22_5","GEM Residuals GE22 Roll 5",50000, -2.5, 2.5);
  hGlobalResAllClsGE22_6 = dbe->book1D("GlobalResidualsAllClsGE22_6","GEM Residuals GE22 Roll 6",50000, -2.5, 2.5);
  hGlobalResAllClsGE22_7 = dbe->book1D("GlobalResidualsAllClsGE22_7","GEM Residuals GE22 Roll 7",50000, -2.5, 2.5);
  hGlobalResAllClsGE22_8 = dbe->book1D("GlobalResidualsAllClsGE22_8","GEM Residuals GE22 Roll 8",50000, -2.5, 2.5);
  hGlobalResAllClsGE22_9 = dbe->book1D("GlobalResidualsAllClsGE22_9","GEM Residuals GE22 Roll 9",50000, -2.5, 2.5);
  hGlobalResAllClsGE22_10 = dbe->book1D("GlobalResidualsAllClsGE22_10","GEM Residuals GE22 Roll 10",50000, -2.5, 2.5);
  hGlobalResAllClsGE22_11 = dbe->book1D("GlobalResidualsAllClsGE22_11","GEM Residuals GE22 Roll 11",50000, -2.5, 2.5);
  hGlobalResAllClsGE22_12 = dbe->book1D("GlobalResidualsAllClsGE22_12","GEM Residuals GE22 Roll 12",50000, -2.5, 2.5);

  folder = "Muons/MuonSegEff/Residuals/GE22DeltaPhi";
  dbe->setCurrentFolder(folder);

  //Endcap GE22
  hGlobphiResAllGE22_1 = dbe->book1D("GlobphiResAllGE22_1","GEM #Delta #phi GE22 Roll 1",40000, -2., 2.);
  hGlobphiResAllGE22_2 = dbe->book1D("GlobphiResAllGE22_2","GEM #Delta #phi GE22 Roll 2",40000, -2., 2.);
  hGlobphiResAllGE22_3 = dbe->book1D("GlobphiResAllGE22_3","GEM #Delta #phi GE22 Roll 3",40000, -2., 2.);
  hGlobphiResAllGE22_4 = dbe->book1D("GlobphiResAllGE22_4","GEM #Delta #phi GE22 Roll 4",40000, -2., 2.);
  hGlobphiResAllGE22_5 = dbe->book1D("GlobphiResAllGE22_5","GEM #Delta #phi GE22 Roll 5",40000, -2., 2.);
  hGlobphiResAllGE22_6 = dbe->book1D("GlobphiResAllGE22_6","GEM #Delta #phi GE22 Roll 6",40000, -2., 2.);
  hGlobphiResAllGE22_7 = dbe->book1D("GlobphiResAllGE22_7","GEM #Delta #phi GE22 Roll 7",40000, -2., 2.);
  hGlobphiResAllGE22_8 = dbe->book1D("GlobphiResAllGE22_8","GEM #Delta #phi GE22 Roll 8",40000, -2., 2.);
  hGlobphiResAllGE22_9 = dbe->book1D("GlobphiResAllGE22_9","GEM #Delta #phi GE22 Roll 9",40000, -2., 2.);
  hGlobphiResAllGE22_10 = dbe->book1D("GlobphiResAllGE22_10","GEM #Delta #phi GE22 Roll 10",40000, -2., 2.);
  hGlobphiResAllGE22_11 = dbe->book1D("GlobphiResAllGE22_11","GEM #Delta #phi GE22 Roll 11",40000, -2., 2.);
  hGlobphiResAllGE22_12 = dbe->book1D("GlobphiResAllGE22_12","GEM #Delta #phi GE22 Roll 12",40000, -2., 2.);


//XY_view plots
  folder = "Muons/MuonSegEff/xyViews";
  dbe->setCurrentFolder(folder);

  XY_globalGE21 = dbe->book2D("globalXY_GE21", "globalXY_GE21", 1400, -350, 350, 1400, -350, 350);
  XY_globalGEm21 = dbe->book2D("globalXY_GEm21", "globalXY_GE-21", 1400, -350, 350, 1400, -350, 350);
  XY_globalGE11 = dbe->book2D("globalXY_GE11", "globalXY_GE11", 1400, -350, 350, 1400, -350, 350);
  XY_globalGEm11 = dbe->book2D("globalXY_GEm11", "globalXY_GE-11", 1400, -350, 350, 1400, -350, 350);
  XY_globalGE22 = dbe->book2D("globalXY_GE22", "globalXY_GE22", 1400, -350, 350, 1400, -350, 350);
  XY_globalGEm22 = dbe->book2D("globalXY_GEm22", "globalXY_GE-22", 1400, -350, 350, 1400, -350, 350);
  
  XY_globalGE21_extra = dbe->book2D("globalXY_extrapolated_GE21", "globalXY_extrapolated_GE21", 1400, -350, 350, 1400, -350, 350);
  XY_globalGEm21_extra = dbe->book2D("globalXY_extrapolated_GEm21", "globalXY_extrapolated_GE-21", 1400, -350, 350, 1400, -350, 350);
  XY_globalGE11_extra = dbe->book2D("globalXY_extrapolated_GE11", "globalXY_extrapolated_GE11", 1400, -350, 350, 1400, -350, 350);
  XY_globalGEm11_extra = dbe->book2D("globalXY_extrapolated_GEm11", "globalXY_extrapolated_GE-11", 1400, -350, 350, 1400, -350, 350);
  XY_globalGE22_extra = dbe->book2D("globalXY_extrapolated_GE22", "globalXY_extrapolated_GE22", 1400, -350, 350, 1400, -350, 350);
  XY_globalGEm22_extra = dbe->book2D("globalXY_extrapolated_GEm22", "globalXY_extrapolated_GE-22", 1400, -350, 350, 1400, -350, 350);

  if(debug) ofrej.open("rejected.txt");
  if(debug) std::cout<<"Rejected done"<<std::endl;

}

void GEMMuonSegmentPseudo::beginRun(const edm::Run& run, const edm::EventSetup& iSetup){

  if(firstbook)
  {
    std::cout<<"bbooking all histograms"<<std::endl;
    iSetup.get<MuonGeometryRecord>().get(gemGeo);
    iSetup.get<MuonGeometryRecord>().get(cscGeo);

    for (TrackingGeometry::DetContainer::const_iterator it=gemGeo->dets().begin();it<gemGeo->dets().end();it++)
    {
      if(dynamic_cast< const GEMChamber* >( *it ) != 0 )
      {
	const GEMChamber* ch = dynamic_cast< const GEMChamber* >( *it ); 
	std::vector< const GEMEtaPartition*> roles = (ch->etaPartitions());
	for(std::vector<const GEMEtaPartition*>::const_iterator r = roles.begin();r != roles.end(); ++r)
        {
	  GEMDetId gemId = (*r)->id();
	  int region=gemId.region();

//rumi: make GEM_names:
          std::string nameRoll = GEMname(gemId);
	  if(region==0)
          {
            std::cout << "I found a GEM eta partition in the Barrel - should be wrong!" << std::endl;
            continue;
	  }
          else
          {
//	    const TrapezoidalStripTopology* topE_=dynamic_cast<const TrapezoidalStripTopology*>(&((*r)->topology()));
//pseudo granularity case
	    auto& parameters((*r)->specs()->parameters());
	    float bottomLength(parameters[0]); bottomLength = 2*bottomLength;
	    float topLength(parameters[1]);    topLength    = 2*topLength;
	    float height(parameters[2]);       height       = 2*height;
            float rsize = (topLength + bottomLength) / 2.0;
	    meCollection[nameRoll] = bookDetUnitSegPseu(gemId, rsize, height);
	  }
	}
      }
    }
    firstbook = false;
  }
}//beginRun


GEMMuonSegmentPseudo::~GEMMuonSegmentPseudo()
{
}

std::string GEMMuonSegmentPseudo::GEMname(const GEMDetId& _id)
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

void GEMMuonSegmentPseudo::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{

  if(debug) std::cout << "echo from analyze" << std::endl;
  statistics->Fill(1);
  stationstatistics->Fill(1);
  using namespace edm;

  char layerLabel[128];
  char meIdGEM [128];
  char meIdCSC [128];

  if(debug) std::cout <<"\t Getting the CSC Segments"<<std::endl;
  edm::Handle<CSCSegmentCollection> allCSCSegments;
  iEvent.getByToken(cscSegments, allCSCSegments);
  if(debug) std::cout<<"I got the segments"<<std::endl;
  
  if (debug && allCSCSegments->size() == 0)
    std::cout << "event without CSC segments" << iEvent.id() << std::endl;

  if(allCSCSegments->size()!=0 && allCSCSegments->size()<=16){
    statistics->Fill(2);
    statistics->Fill(allCSCSegments->size()+1);
  }
  
  if(debug) std::cout <<"\t Getting the GEM RecHits"<<std::endl;
  Handle<GEMRecHitCollection> gemHits;
  iEvent.getByToken(gemRecHitsLabel,gemHits);

  if(debug) std::cout <<"\t Getting the GEM CSC Points"<<std::endl;
  edm::Handle<GEMRecHitCollection> gemCSCPoints;
  iEvent.getByToken(gemCSCPointsLabel,gemCSCPoints);

  GEMRecHitCollection::const_iterator recHit;
  
  for(recHit = gemHits->begin(); recHit != gemHits->end(); recHit++){ //Filling DQMOccupancies
    
    GEMDetId gemId = recHit->gemId();
    std::string nameRoll = GEMname(gemId);

    if(debug) std::cout<<nameRoll<<std::endl;

    int gemRegion = gemId.region();
    int gemStation = gemId.station();
    if(gemRegion==0)
    {
      std::cout << "I found a GEM in Barrel - check for something wrong" << std::endl;
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

  if(gemCSCPoints.isValid() && (gemCSCPoints->begin()!=gemCSCPoints->end())){//No Empty Predictions
    GEMRecHitCollection::const_iterator gemPoint;
  
    for(gemPoint = gemCSCPoints->begin(); gemPoint != gemCSCPoints->end(); gemPoint++){
      LocalPoint PointExtrapolatedGEMFrame = gemPoint->localPosition();
      GEMDetId  gemId = gemPoint->gemId();

      if(debug)
        std::cout<<gemId.rawId()<<" "<<PointExtrapolatedGEMFrame.x()<<" "<<PointExtrapolatedGEMFrame.y()<<std::endl;

      double dx=0;
      double dy=0;
      double dz=0;

      CSCSegmentCollection::const_iterator segment;  

      CSCDetId CSCId;
      for (segment = allCSCSegments->begin();segment!=allCSCSegments->end(); ++segment)
      {
	CSCId = segment->cscDetId();
	int gemRegion = 1;
        if(CSCId.endcap()==2)
          gemRegion= -1;//Relacion entre las endcaps
	int gemRing = CSCId.ring();
//	int gemStation = CSCId.station();
        int newGemStation = gemId.station();
        if (newGemStation == 2) newGemStation = 999;	//reject eventual gemId.station() == 2 -> GE21 short ?
        if (newGemStation == 3) newGemStation = 2; // gemId.station() == 3 -> GE21 long
	if(gemRing==4) gemRing =1;

	if(gemRegion==gemId.region() && CSCId.station()==gemId.station() && gemRing == gemId.ring() && CSCId.chamber()==gemId.chamber())
        {
	  LocalVector segmentDirection=segment->localDirection();
	  dx=segmentDirection.x();
	  dy=segmentDirection.y();
	  dz=segmentDirection.z();
	  continue;
	}
//	if(gemStation==1) stationstatistics->Fill(2);
//	if(gemStation==2) stationstatistics->Fill(3);
//	if(gemStation==3) stationstatistics->Fill(4);
//	if(gemStation==4) stationstatistics->Fill(5);
      }
      
      const GEMEtaPartition* rollasociated = gemGeo->etaPartition(gemId);

        GlobalPoint ExtraHitPosGlob = rollasociated->toGlobal(PointExtrapolatedGEMFrame);
        float ExtraHitPosGlobPhi = ExtraHitPosGlob.phi();
        if(rollasociated->id().region() == 1)
        {
          if(rollasociated->id().station()==1) XY_globalGE11_extra->Fill(ExtraHitPosGlob.x(), ExtraHitPosGlob.y());
          if(rollasociated->id().station()==2) XY_globalGE21_extra->Fill(ExtraHitPosGlob.x(), ExtraHitPosGlob.y());
          if(rollasociated->id().station()==3) XY_globalGE22_extra->Fill(ExtraHitPosGlob.x(), ExtraHitPosGlob.y());
        }

        if(rollasociated->id().region() == -1)
        {
          if(rollasociated->id().station()==1) XY_globalGEm11_extra->Fill(ExtraHitPosGlob.x(), ExtraHitPosGlob.y());
          if(rollasociated->id().station()==2) XY_globalGEm21_extra->Fill(ExtraHitPosGlob.x(), ExtraHitPosGlob.y());
          if(rollasociated->id().station()==3) XY_globalGEm22_extra->Fill(ExtraHitPosGlob.x(), ExtraHitPosGlob.y());
        }
      
      const TrapezoidalStripTopology* top_=dynamic_cast<const TrapezoidalStripTopology*>(&(rollasociated->topology()));
      auto& parameters((rollasociated)->specs()->parameters());
      float bottomLength(parameters[0]); bottomLength = 2*bottomLength;
      float topLength(parameters[1]);    topLength    = 2*topLength;
      float height(parameters[2]);       height       = 2*height;
      float rsize = (topLength + bottomLength) / 2.0;


      LocalPoint xmin = top_->localPosition(0.);
      if(debug) std::cout << "CSC \t \t \t xmin of this  Roll " << xmin << " cm" << std::endl;
      if(debug) std::cout << "CSC \t \t \t Roll Size in the middle " << rsize << " cm" << std::endl;
      
      std::string nameRoll = GEMname(gemId);
      if(debug) std::cout << "CSC \t \t \t \t The GEMName is " << nameRoll << std::endl;
      
      //--------- HISTOGRAM - PREDICTED FROM CSC  -------------------
      
      char detUnitLabel[128];
      sprintf(detUnitLabel ,"%s",nameRoll.c_str());
      sprintf(layerLabel ,"%s",nameRoll.c_str());
      std::map<std::string, MonitorElement*> meMap=meCollection[nameRoll];
      bool prediction=false;

      if(fabs(PointExtrapolatedGEMFrame.x()) < rsize*0.5 &&  fabs(PointExtrapolatedGEMFrame.y()) < height*0.5)
      {
	if(debug) std::cout << "CSC \t \t \t \t Filling Expected for " << meIdCSC << " with PointExtrapolatedGEMFrame.x() = " << PointExtrapolatedGEMFrame.x() << "  and PointExtrapolatedGEMFrame.y() = " << PointExtrapolatedGEMFrame.y() << std::endl;
	prediction = true;
      }
      else
      {
	if(debug) std::cout<<"CSC \t \t \t \t In fact the extrapolation goes outside the roll was done just for 2D histograms"<<std::endl;
      }
	    		
      //-------RecHitPart Just For Residual--------
//      float pstof = 0;
      int countRecHits = 0;
      float minres = 3000.;
      float recHitErrorX = 0.;
      float resPhi = 0.;
      float resPhiDegree = 999.;
      
      if(debug) std::cout<<"CSC  \t \t \t \t \t Getting RecHits in Roll Asociated"<<std::endl;

      typedef std::pair<GEMRecHitCollection::const_iterator, GEMRecHitCollection::const_iterator> rangeRecHits;
      rangeRecHits recHitCollection =  gemHits->get(rollasociated->id());
      GEMRecHitCollection::const_iterator recHit;
      
      for (recHit = recHitCollection.first; recHit != recHitCollection.second ; recHit++)
      {
	countRecHits++;
	LocalPoint recHitPos=recHit->localPosition();

//take the local error of the pseudodigi
        LocalError recHitError = recHit->localPositionError();

	float res=PointExtrapolatedGEMFrame.x()- recHitPos.x();

        GlobalPoint recHitPosGlob = rollasociated->toGlobal(recHitPos);
        float recHitPosPhi = recHitPosGlob.phi();
        resPhi = ExtraHitPosGlobPhi - recHitPosPhi;
        resPhiDegree = resPhi*180/3.1415926;
        if(rollasociated->id().region()==1)
        {
          if(rollasociated->id().station()==1) XY_globalGE11->Fill(recHitPosGlob.x(), recHitPosGlob.y());
          if(rollasociated->id().station()==2) XY_globalGE21->Fill(recHitPosGlob.x(), recHitPosGlob.y());
          if(rollasociated->id().station()==3) XY_globalGE22->Fill(recHitPosGlob.x(), recHitPosGlob.y());
        }

        if(rollasociated->id().region()==-1)
        {
          if(rollasociated->id().station()==1) XY_globalGEm11->Fill(recHitPosGlob.x(), recHitPosGlob.y());
          if(rollasociated->id().station()==2) XY_globalGEm21->Fill(recHitPosGlob.x(), recHitPosGlob.y());
          if(rollasociated->id().station()==3) XY_globalGEm22->Fill(recHitPosGlob.x(), recHitPosGlob.y());
        }

	if(debug) std::cout<<"CSC  \t \t \t \t \t \t Found Rec Hit at "<<res<<"cm of the prediction."<<std::endl;
	if(fabs(res)<fabs(minres))
        {
	  minres=res;
          recHitErrorX = recHitError.xx();
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
	
	if(debug) std::cout<<"CSC \t \t \t \t \t PointExtrapolatedGEMFrame.x="<<PointExtrapolatedGEMFrame.x()<<" Minimal Residual"<<minres << "\tand local error xx = " << recHitErrorX <<std::endl;
        if(fabs(minres) <= 3.*recHitErrorX)
        {
	  if(debug) std::cout << "CSC  \t \t \t \t \t \t True!" << std::endl;
	  anycoincidence=true;
	}
      }
      if(debug) std::cout<<"CSC  \t \t \t \t \t prediction\t"<< prediction << "\tanycoincidence\t" << anycoincidence << std::endl;
      
//      if(prediction && anycoincidence)
      if(prediction)
      {
	float distobottom = height*0.5 + PointExtrapolatedGEMFrame.y();
	if(debug)
        {
          std::cout << "prediction and coincidence: distobottom = " << distobottom << std::endl;
          std::cout<<"CSC  \t \t \t \t \t At least one RecHit inside the range, PointExtrapolatedGEMFrame.x() = "<<PointExtrapolatedGEMFrame.x()<<" minres="<<minres<<"cm"<<std::endl;
          std::cout<<"CSC  \t \t \t \t \t Norm of Cosine Directors="<<dx*dx+dy*dy+dz*dz<<"~1?"<<std::endl;
        }
	
	//----RESIDUALS----

	if(inves){
	  float cosal = dx/sqrt(dx*dx+dz*dz);
	  float angle = acos(cosal)*180/3.1415926;

          if(minres<=1*recHitErrorX) AngSigma1Endcaps->Fill(angle);
          else if(minres<=2*recHitErrorX) AngSigma2Endcaps->Fill(angle);
          else if(minres<=3*recHitErrorX) AngSigma3Endcaps->Fill(angle);
          else AngSigmaAnyEndcaps->Fill(angle);

	  if(debug) std::cout<<"CSC \t \t \t \t \t Angle = "<<angle<<" degree"<<std::endl;

	  //Filling Residuals
            if(!(gemId.ring()==1)) {std::cout << "something is wrong - GEM is on the ring = " << gemId.ring() << std::endl; continue;}
            if(gemId.station() == 1)
            {
              if(gemId.roll() == 1)  hGlobalResAllClsGE11_1->Fill(minres);
              else if(gemId.roll() == 2) hGlobalResAllClsGE11_2->Fill(minres);
              else if(gemId.roll() == 3) hGlobalResAllClsGE11_3->Fill(minres);
              else if(gemId.roll() == 4) hGlobalResAllClsGE11_4->Fill(minres);
              else if(gemId.roll() == 5) hGlobalResAllClsGE11_5->Fill(minres);
              else if(gemId.roll() == 6) hGlobalResAllClsGE11_6->Fill(minres);
              else if(gemId.roll() == 7) hGlobalResAllClsGE11_7->Fill(minres);
              else if(gemId.roll() == 8) hGlobalResAllClsGE11_8->Fill(minres);
              else std::cout << "more than 8 rolls in a GEM chamber, please fix the hardcoded values" << std::endl;
            }
            if(gemId.station() == 2)
            {
              if(gemId.roll() == 1)  hGlobalResAllClsGE21_1->Fill(minres);
              else if(gemId.roll() == 2) hGlobalResAllClsGE21_2->Fill(minres);
              else if(gemId.roll() == 3) hGlobalResAllClsGE21_3->Fill(minres);
              else if(gemId.roll() == 4) hGlobalResAllClsGE21_4->Fill(minres);
              else if(gemId.roll() == 5) hGlobalResAllClsGE21_5->Fill(minres);
              else if(gemId.roll() == 6) hGlobalResAllClsGE21_6->Fill(minres);
              else if(gemId.roll() == 7) hGlobalResAllClsGE21_7->Fill(minres);
              else if(gemId.roll() == 8) hGlobalResAllClsGE21_8->Fill(minres);
              else std::cout << "more than 8 rolls in a GEM chamber, please fix the hardcoded values" << std::endl;
            }
            if(gemId.station() == 3)
            {
              if(gemId.roll() == 1)  {hGlobalResAllClsGE22_1->Fill(minres); hGlobphiResAllGE22_1->Fill(resPhiDegree);}
              else if(gemId.roll() == 2) {hGlobalResAllClsGE22_2->Fill(minres); hGlobphiResAllGE22_2->Fill(resPhiDegree);}
              else if(gemId.roll() == 3) {hGlobalResAllClsGE22_3->Fill(minres); hGlobphiResAllGE22_3->Fill(resPhiDegree);}
              else if(gemId.roll() == 4) {hGlobalResAllClsGE22_4->Fill(minres); hGlobphiResAllGE22_4->Fill(resPhiDegree);}
              else if(gemId.roll() == 5) {hGlobalResAllClsGE22_5->Fill(minres); hGlobphiResAllGE22_5->Fill(resPhiDegree);}
              else if(gemId.roll() == 6) {hGlobalResAllClsGE22_6->Fill(minres); hGlobphiResAllGE22_6->Fill(resPhiDegree);}
              else if(gemId.roll() == 7) {hGlobalResAllClsGE22_7->Fill(minres); hGlobphiResAllGE22_7->Fill(resPhiDegree);}
              else if(gemId.roll() == 8) {hGlobalResAllClsGE22_8->Fill(minres); hGlobphiResAllGE22_8->Fill(resPhiDegree);}
              else if(gemId.roll() == 9) {hGlobalResAllClsGE22_9->Fill(minres); hGlobphiResAllGE22_9->Fill(resPhiDegree);}
              else if(gemId.roll() == 10){hGlobalResAllClsGE22_10->Fill(minres); hGlobphiResAllGE22_10->Fill(resPhiDegree);}
              else if(gemId.roll() == 11){hGlobalResAllClsGE22_11->Fill(minres); hGlobphiResAllGE22_11->Fill(resPhiDegree);}
              else if(gemId.roll() == 12){hGlobalResAllClsGE22_12->Fill(minres); hGlobphiResAllGE22_12->Fill(resPhiDegree);}
              else std::cout << "more than 12 rolls in a GEM chamber, please fix the hardcoded values" << std::endl;
            }
	}
	
	  sprintf(meIdGEM,"GEMResiduals_pseudo_%s",detUnitLabel);
	  meMap[meIdGEM]->Fill(minres);

	
	sprintf(meIdGEM,"GEMDataOccupancy_pseudo_%s",detUnitLabel);
	meMap[meIdGEM]->Fill(PointExtrapolatedGEMFrame.x());
	
	if(debug) std::cout <<"CSC \t \t \t \t \t \t COINCEDENCE!!! Event="<<iEvent.id()<<"Filling Filling GEM Data Occupancy for "<<meIdGEM<<" with PointExtrapolatedGEMFrame.x() = "<<PointExtrapolatedGEMFrame.x()<<std::endl;
      }//prediction && anycoincidence
      
      if(anycoincidence)
      {
	if(debug) std::cout<<"CSC \t \t \t \t \t \t Filling 2D histo for GEM Occupancy "<<meIdGEM<<std::endl; 	
	sprintf(meIdGEM,"GEMDataOccupancy2D_pseudo_%s",detUnitLabel);
	meMap[meIdGEM]->Fill(PointExtrapolatedGEMFrame.x(),PointExtrapolatedGEMFrame.y());
      }//anycoincidence
      else if(prediction)
      {
        std::string nameRoll = GEMname(gemId);
	if(debug)
        {
          std::cout<<"CSC \t \t \t \t \t \t A roll was ineficient in event"<<iEvent.id().event()<<std::endl;
	  ofrej<<"CSC \t EndCap " << gemId.region() <<"\t Roll "<<nameRoll <<"\t CSCId "<<CSCId <<"\t Event " <<iEvent.id().event() << "\t Run " << iEvent.id().run() << std::endl;
        }
      }
      else
      {
	if(debug) std::cout << "CSC \t \t \t \t No the prediction is outside of this roll" << std::endl;
      }//Condition for the right match
    }
  }
}

void GEMMuonSegmentPseudo::endRun(const edm::Run& r, const edm::EventSetup& iSetup){
}


void GEMMuonSegmentPseudo::endJob()
{
  std::cout<<"saving root file"<<std::endl;
  if (EffSaveRootFile){
    dbe->save(EffRootFileName);
  }
  dbe = 0;
}

DEFINE_FWK_MODULE(GEMMuonSegmentPseudo);
