// -*- C++ -*-
//
// Package:    ratevslumi/RateVsLumi
// Class:      RateVsLumi
//
/**\class RateVsLumi RateVsLumi.cc ratevslumi/RateVsLumi/plugins/RateVsLumi.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Roumyana Mileva Hadjiiska
//         Created:  Thu, 05 Jul 2018 18:47:21 GMT
//
//

// system include files
#include <memory>
// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"
// #include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/ESTransientHandle.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/PluginManager/interface/ModuleDef.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/RPCDigi/interface/DataRecord.h"
#include "DataFormats/RPCDigi/interface/ReadoutError.h"
#include "DataFormats/RPCDigi/interface/RPCRawSynchro.h"
#include "DataFormats/RPCDigi/interface/RecordBX.h"
#include "DataFormats/RPCDigi/interface/RecordSLD.h"
#include "DataFormats/RPCDigi/interface/RecordCD.h"
#include "DataFormats/RPCRecHit/interface/RPCRecHitCollection.h"
#include <DataFormats/MuonDetId/interface/RPCDetId.h>
#include "DataFormats/RPCDigi/interface/RPCDigi.h"
// user include files
#include "CondFormats/RPCObjects/interface/RPCReadOutMapping.h"
#include "CondFormats/RPCObjects/interface/LinkBoardSpec.h"
#include "CondFormats/RPCObjects/interface/RPCEMap.h"
#include "CondFormats/RPCObjects/interface/DccSpec.h"
#include "CondFormats/RPCObjects/interface/LinkBoardElectronicIndex.h"
#include "CondFormats/RPCObjects/interface/LinkBoardPackedStrip.h"
#include "CondFormats/RPCObjects/interface/TriggerBoardSpec.h"
#include "CondFormats/RPCObjects/interface/LinkBoardSpec.h"
#include "CondFormats/DataRecord/interface/RPCEMapRcd.h"
#include "EventFilter/RPCRawToDigi/interface/RPCRecordFormatter.h"
#include "EventFilter/RPCRawToDigi/interface/EventRecords.h"
#include "EventFilter/RPCRawToDigi/interface/DebugDigisPrintout.h"
#include "DataFormats/MuonDetId/interface/CSCDetId.h"
#include "DataFormats/MuonDetId/interface/DTChamberId.h"
#include "DataFormats/CSCDigi/interface/CSCCorrelatedLCTDigi.h"
#include "DataFormats/CSCDigi/interface/CSCCorrelatedLCTDigiCollection.h"
#include "DataFormats/L1DTTrackFinder/interface/L1MuDTChambPhContainer.h"
#include "DataFormats/L1DTTrackFinder/interface/L1MuDTChambThContainer.h"
#include "DataFormats/L1TMuon/interface/RegionalMuonCand.h"
#include "DataFormats/L1TMuon/interface/RegionalMuonCandFwd.h"


#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TTree.h"

#include "Geometry/Records/interface/MuonGeometryRecord.h"
#include "Geometry/RPCGeometry/interface/RPCGeometry.h"
#include "Geometry/RPCGeometry/interface/RPCGeomServ.h"
#include "Geometry/CommonTopologies/interface/RectangularStripTopology.h"
#include "Geometry/CommonTopologies/interface/TrapezoidalStripTopology.h"
#include "DataFormats/GeometryVector/interface/GlobalPoint.h"
#include "DataFormats/GeometryVector/interface/LocalPoint.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/Utilities/interface/EDGetToken.h"

#include "DataFormats/Scalers/interface/LumiScalers.h"
#include "FWCore/Framework/interface/LuminosityBlock.h"
#include <cmath> 
#include <map>

#include "TGraph.h"
#include "TGraphErrors.h"


//
// class declaration
//
using namespace std;
using namespace edm;

struct RPCEvent{


  // event information
  int nRun;
  int nEv;
  int nLumi;
  int nBX;	

  int Ls;
  double Lumi;
  double Rate;

  double RB1inHits;
  double RB1outHits;
  double RB2inHits;
  double RB2outHits;
  double RB3Hits;
  double RB4Hits;
  double BHits;
  double Wp2Hits;
  double Wp1Hits;
  double W0Hits;
  double Wm1Hits;
  double Wm2Hits;
  double REpHits;
  double REmHits;
  double REp1Hits;
  double REp2Hits;
  double REp3Hits;
  double REp4Hits;
  double REm1Hits;
  double REm2Hits;
  double REm3Hits;
  double REm4Hits;

  double areaRB1in ;
  double areaRB1out ;
  double areaRB2in ;
  double areaRB2out ;
  double areaRB3 ;
  double areaRB4 ;
  double areaB ;
  double areaWp2 ;
  double areaWp1 ;
  double areaW0 ;
  double areaWm1 ;
  double areaWm2 ;

  double areaREp ;
  double areaREm ;
  double areaREp1 ;
  double areaREp2 ;
  double areaREp3 ;
  double areaREp4 ;
  double areaREm1 ;
  double areaREm2 ;
  double areaREm3 ;
  double areaREm4 ;



	// int myScale;

};


class RateVsLumi : public edm::one::EDAnalyzer<edm::one::SharedResources>  
// class RateVsLumi : public edm::EDAnalyzer  
{
   public:
      explicit RateVsLumi(const edm::ParameterSet&);
      ~RateVsLumi();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

      // ----------member data ---------------------------
  
      edm::EDGetTokenT<RPCRecHitCollection> rpcRecHitsLabel;
      edm::InputTag scalersSource_;
      edm::EDGetTokenT<LumiScalersCollection> scalersSourceToken_;
      int lumiblock;
      double lumiperblock;
      std::map<int, double> pairLsLumi;
/////test Lumi counts
      std::map<int, int> pairLsCounts;


/////

      std::map<int, double> pairLsRate;
      //map Ls to counts
      std::map<int, double> pairLsRateRB1in;
      std::map<int, double> pairLsRateRB1out;
      std::map<int, double> pairLsRateRB2in;
      std::map<int, double> pairLsRateRB2out;
      std::map<int, double> pairLsRateRB3;
      std::map<int, double> pairLsRateRB4;
      std::map<int, double> pairLsRateB;
      std::map<int, double> pairLsRateWp2;
      std::map<int, double> pairLsRateWp1;
      std::map<int, double> pairLsRateW0;
      std::map<int, double> pairLsRateWm1;
      std::map<int, double> pairLsRateWm2;

      std::map<int, double> pairLsRateREp;
      std::map<int, double> pairLsRateREm;

      std::map<int, double> pairLsRateREp1;
      std::map<int, double> pairLsRateREp2;
      std::map<int, double> pairLsRateREp3;
      std::map<int, double> pairLsRateREp4;

      std::map<int, double> pairLsRateREm1;
      std::map<int, double> pairLsRateREm2;
      std::map<int, double> pairLsRateREm3;
      std::map<int, double> pairLsRateREm4;

//number of events
  TH1F *numbEvents;

  TGraphErrors *LumiVsLs;

/// test lumi conts
  TGraphErrors *LumiNum_LumiCount;

//////

//hits vs Inst. Lumi
  TGraphErrors *Barrel_InstLumi, *RB1in_InstLumi, *RB1out_InstLumi, *RB2in_InstLumi, *RB2out_InstLumi, *RB3_InstLumi, *RB4_InstLumi, *Wp2_InstLumi, *Wp1_InstLumi, *W0_InstLumi, *Wm1_InstLumi, *Wm2_InstLumi;
  TGraphErrors *REp_InstLumi, *REm_InstLumi, *REp1_InstLumi, *REp2_InstLumi, *REp3_InstLumi, *REp4_InstLumi, *REm1_InstLumi, *REm2_InstLumi, *REm3_InstLumi, *REm4_InstLumi;

//rate in hz vs inst. lumi
  TGraphErrors *Barrel_toHz, *RB1in_toHz, *RB1out_toHz, *RB2in_toHz, *RB2out_toHz, *RB3_toHz, *RB4_toHz, *Wp2_toHz, *Wp1_toHz, *W0_toHz, *Wm1_toHz, *Wm2_toHz;
  TGraphErrors *REp_toHz, *REm_toHz, *REp1_toHz, *REp2_toHz, *REp3_toHz, *REp4_toHz, *REm1_toHz, *REm2_toHz, *REm3_toHz, *REm4_toHz;

//rate in hz/cm2 vs inst. lumi
  TGraphErrors *Barrel_toHzcm2, *RB1in_toHzcm2, *RB1out_toHzcm2, *RB2in_toHzcm2, *RB2out_toHzcm2, *RB3_toHzcm2, *RB4_toHzcm2, *Wp2_toHzcm2, *Wp1_toHzcm2, *W0_toHzcm2, *Wm1_toHzcm2, *Wm2_toHzcm2;
  TGraphErrors *REp_toHzcm2, *REm_toHzcm2, *REp1_toHzcm2, *REp2_toHzcm2, *REp3_toHzcm2, *REp4_toHzcm2, *REm1_toHzcm2, *REm2_toHzcm2, *REm3_toHzcm2, *REm4_toHzcm2;

  bool debug;
  bool doAllBXs_;
  bool doAllBXno0_;
  bool doOnlyOneBX_;
  int numbBXs_;
  int bxInvest_;

//areas
  double areaRB1in, areaRB1out, areaRB2in, areaRB2out, areaRB3, areaRB4, areaB, areaWp2, areaWp1, areaW0, areaWm1, areaWm2;
  double areaREp, areaREm, areaREp1, areaREp2, areaREp3, areaREp4, areaREm1, areaREm2, areaREm3, areaREm4;

	edm::Service<TFileService> fs;


	bool debug1;
  TTree * RPCTree_;
  RPCEvent rpcev_;


};

RateVsLumi::RateVsLumi(const edm::ParameterSet& iConfig)
{
  debug=iConfig.getUntrackedParameter<bool>("debug",false);
  doAllBXs_=iConfig.getUntrackedParameter<bool>("doAllBXs",true);
  doAllBXno0_=iConfig.getUntrackedParameter<bool>("doAllBXno0",false);
  doOnlyOneBX_=iConfig.getUntrackedParameter<bool>("doOnlyOneBX",false);
  numbBXs_ = iConfig.getParameter<int>("numbBXs");
  bxInvest_ = iConfig.getParameter<int>("bxInvest");
  rpcRecHitsLabel = consumes<RPCRecHitCollection>(iConfig.getUntrackedParameter < edm::InputTag > ("rpcRecHits_tag"));
  scalersSource_ = iConfig.getParameter<edm::InputTag>("scalersResults");
  scalersSourceToken_ = consumes<LumiScalersCollection>(edm::InputTag(scalersSource_));
  usesResource("TFileService");

}

RateVsLumi::~RateVsLumi()
{}

// ------------ method called for each event  ------------
void
RateVsLumi::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{

  memset(&rpcev_,0,sizeof rpcev_);
	debug1=true;
  //  cout <<"Got data"<<endl;
  rpcev_.nEv = (int)iEvent.id().event();
  rpcev_.nRun = (int)iEvent.id().run();
  rpcev_.nLumi = (int)iEvent.luminosityBlock();
  rpcev_.nBX = (int)iEvent.bunchCrossing();


  numbEvents->Fill(1);
  using namespace edm;
//areas
  double area = 0.0;
  double stripArea = 0.0;

  areaRB1in = 0.;
  areaRB1out = 0.;
  areaRB2in = 0.;
  areaRB2out = 0.;
  areaRB3 = 0.;
  areaRB4 = 0.;
  areaB = 0.;
  areaWp2 = 0.;
  areaWp1 = 0.;
  areaW0 = 0.;
  areaWm1 = 0.;
  areaWm2 = 0.;

  areaREp = 0.;
  areaREm = 0.;
  areaREp1 = 0.;
  areaREp2 = 0.;
  areaREp3 = 0.;
  areaREp4 = 0.;
  areaREm1 = 0.;
  areaREm2 = 0.;
  areaREm3 = 0.;
  areaREm4 = 0.;

//get the luminosity block
  lumiperblock = 0.;
  lumiblock = 0;
  edm::Handle<LumiScalersCollection> lumiScalers;
  iEvent.getByToken(scalersSourceToken_, lumiScalers);
  LumiScalersCollection::const_iterator lumiIt = lumiScalers->begin();
  lumiperblock = lumiIt->instantLumi();	//10^30
  lumiblock = iEvent.getLuminosityBlock().luminosityBlock();
  lumiperblock = lumiperblock*1./1000.;	//10^33
//  lumiperblock = std::floor((lumiperblock * 100.) + 0.5) / 100.;

	rpcev_.Ls= lumiblock;
	rpcev_.Lumi=lumiperblock;


	if(debug1) cout<<"Ls = "<<lumiblock<<" , Lumi = "<<lumiperblock<<endl;

  if (debug) std::cout << "lumi section = " << lumiblock << "\tinst. lumi = " << lumiperblock << " x 10^33 Hz/cm^2" << std::endl;
  pairLsLumi.insert ( std::pair<int,double>(lumiblock,lumiperblock));

/////////// test lumi counts
//  int mylumicount = 1;
//pairLsCounts
  std::map<int, int>::iterator cc = pairLsCounts.find(lumiblock);
  if(cc != pairLsCounts.end()) cc->second += 1;
  else pairLsCounts.insert ( std::pair<int,int>(lumiblock,1));
  if (debug) std::cout << "lumiblock: " << lumiblock << "\tcounts: " << cc->second << std::endl;

/////////////

  // Get the RPC Geometry
  edm::ESHandle < RPCGeometry > rpcGeom;
  iSetup.get<MuonGeometryRecord>().get(rpcGeom);

  if(debug) std::cout <<"\t Getting the RPC RecHits"<<std::endl;
  Handle<RPCRecHitCollection> rpcHits_handle;
  iEvent.getByToken(rpcRecHitsLabel,rpcHits_handle);

  const std::vector<  const RPCRoll * > rls = rpcGeom->rolls();

  for (int i = 0; i < (int) rls.size() ; ++i)
  {
    RPCDetId rpcId =  rls[i]->id();

    const RPCRoll* roll = dynamic_cast<const RPCRoll*>(rpcGeom->roll(rpcId));
    if(debug) std::cout<<"roll"<<roll<<std::endl;
    //take the global coordiantes of the center of the rpc roll (eta partition)
    const int nstrips = roll->nstrips();
    float middleStrip = nstrips/2.;
    const LocalPoint& middleOfRoll = roll->centreOfStrip(middleStrip);
    const GlobalPoint& globMiddleRol = roll->toGlobal(middleOfRoll);

    if(debug) std::cout << "eta " << globMiddleRol.eta() << "\tphi " << globMiddleRol.phi() << std::endl;

    area = 0.0;
    float myPitch = 0.0;
    float xmin = 0.0;
    float xmax = 0.0;
    float striplength;



   if ( rpcId.region() == 0 )
     {
       const RectangularStripTopology* top_ = dynamic_cast<const RectangularStripTopology*>(&(roll->topology()));
       xmin = (top_->localPosition(0.)).x();
       xmax = (top_->localPosition((float)roll->nstrips())).x();
       striplength = (top_->stripLength());
       myPitch = top_->pitch();
     }
   else
     {
       const TrapezoidalStripTopology* top_=dynamic_cast<const TrapezoidalStripTopology*>(&(roll->topology()));
       xmin = (top_->localPosition(0.)).x();
       xmax = (top_->localPosition((float)roll->nstrips())).x();
       striplength = (top_->stripLength());
       myPitch = top_->pitch();
     }

     area = striplength*(xmax-xmin);
     stripArea = striplength*myPitch;

    RPCRecHitCollection::range rpcRecHitRange = rpcHits_handle->get(rpcId);
    RPCRecHitCollection::const_iterator recHit_2itrat;   
    int countRecHits = 0;

    RPCGeomServ RPCname(rpcId);
    if (debug) std::cout << RPCname.name() << "\tarea: " << area << "\tstrips: " << roll->nstrips() << "\tstripArea: "<< stripArea << "\tarea: " << (roll->nstrips())*stripArea << std::endl;

    for(recHit_2itrat = rpcRecHitRange.first; recHit_2itrat!=rpcRecHitRange.second; ++recHit_2itrat)
    {
      int  cluSize = recHit_2itrat->clusterSize();    
      int bx=recHit_2itrat->BunchX();
      if(debug) std::cout << "bx: " << bx << "\tcls: "<< cluSize << std::endl;
//FIXME cluster size selection
//      if(cluSize != 2) continue;

      if (doAllBXs_)
      {
        countRecHits++;
//        countRecHits +=cluSize;
        if (debug) cout<<"rechits cout if all BX"<<countRecHits<<endl;
      }
      if (doAllBXno0_ && bx!=0)
      {
        countRecHits++;
//        countRecHits +=cluSize;
      }
      if (doOnlyOneBX_)
      {
        if (!(bx == bxInvest_)) continue;       
        countRecHits++;
//        countRecHits +=cluSize;
        if (debug) cout<<"rechits count if not  all BX"<<countRecHits<<endl;
     }      
    }//loop over rechits in a given roll

   if (rpcId.region() == -1)
      {
        areaREm+=area;
        std::map<int, double>::iterator lb = pairLsRateREm.find(lumiblock);
				rpcev_.REmHits+=countRecHits;
        if(lb != pairLsRateREm.end()) lb->second += countRecHits;
        else pairLsRateREm.insert ( std::pair<int,double>(lumiblock,countRecHits));
        if (rpcId.station() == 1)
        {
          areaREm1+=area;
          std::map<int, double>::iterator lb = pairLsRateREm1.find(lumiblock);
					rpcev_.REm1Hits+=countRecHits;
          if(lb != pairLsRateREm1.end()) lb->second += countRecHits;
          else pairLsRateREm1.insert ( std::pair<int,double>(lumiblock,countRecHits));
        }
        if (rpcId.station() == 2)
        {
          areaREm2+=area;
          std::map<int, double>::iterator lb = pairLsRateREm2.find(lumiblock);
					rpcev_.REm2Hits+=countRecHits;
          if(lb != pairLsRateREm2.end()) lb->second += countRecHits;
          else pairLsRateREm2.insert ( std::pair<int,double>(lumiblock,countRecHits));
        }
        if (rpcId.station() == 3)
        {
          areaREm3+=area;
          std::map<int, double>::iterator lb = pairLsRateREm3.find(lumiblock);
					rpcev_.REm3Hits+=countRecHits;
          if(lb != pairLsRateREm3.end()) lb->second += countRecHits;
          else pairLsRateREm3.insert ( std::pair<int,double>(lumiblock,countRecHits));
        }
        if (rpcId.station() == 4)
        {
          areaREm4+=area;
          std::map<int, double>::iterator lb = pairLsRateREm4.find(lumiblock);
					rpcev_.REm4Hits+=countRecHits;
          if(lb != pairLsRateREm4.end()) lb->second += countRecHits;
          else pairLsRateREm4.insert ( std::pair<int,double>(lumiblock,countRecHits));
        }
      }//end endcap negative

      if (rpcId.region() == 1)
      {
        areaREp+=area;
        std::map<int, double>::iterator lb = pairLsRateREp.find(lumiblock);
				rpcev_.REpHits+=countRecHits;
        if(lb != pairLsRateREp.end()) lb->second += countRecHits;
        else pairLsRateREp.insert ( std::pair<int,double>(lumiblock,countRecHits));
        if (rpcId.station() == 1)
        {
          areaREp1+=area;
          std::map<int, double>::iterator lb = pairLsRateREp1.find(lumiblock);
					rpcev_.REp1Hits+=countRecHits;
          if(lb != pairLsRateREp1.end()) lb->second += countRecHits;
          else pairLsRateREp1.insert ( std::pair<int,double>(lumiblock,countRecHits));
        }
        if (rpcId.station() == 2)
        {
          areaREp2+=area;
          std::map<int, double>::iterator lb = pairLsRateREp2.find(lumiblock);
					rpcev_.REp2Hits+=countRecHits;
          if(lb != pairLsRateREp2.end()) lb->second += countRecHits;
          else pairLsRateREp2.insert ( std::pair<int,double>(lumiblock,countRecHits));
        }
        if (rpcId.station() == 3)
        {
          areaREp3+=area;
          std::map<int, double>::iterator lb = pairLsRateREp3.find(lumiblock);
					rpcev_.REp3Hits+=countRecHits;
          if(lb != pairLsRateREp3.end()) lb->second += countRecHits;
          else pairLsRateREp3.insert ( std::pair<int,double>(lumiblock,countRecHits));
        }
        if (rpcId.station() == 4)
        {
          areaREp4+=area;
          std::map<int, double>::iterator lb = pairLsRateREp4.find(lumiblock);
					rpcev_.REp4Hits+=countRecHits;
          if(lb != pairLsRateREp4.end()) lb->second += countRecHits;
          else pairLsRateREp4.insert ( std::pair<int,double>(lumiblock,countRecHits));
        }
      }// end endcap positive

      if (rpcId.region() == 0)
      {
        areaB +=area;
        std::map<int, double>::iterator lb = pairLsRateB.find(lumiblock);
				rpcev_.BHits+=countRecHits;
        if(lb != pairLsRateB.end()) lb->second += countRecHits;
        else pairLsRateB.insert ( std::pair<int,double>(lumiblock,countRecHits));
        if(rpcId.station() == 1)
        {
          if(rpcId.layer() == 1)
          {
            areaRB1in +=area;
            std::map<int, double>::iterator lb = pairLsRateRB1in.find(lumiblock);
						rpcev_.RB1inHits+=countRecHits;
						// cout<<"rpcev_.RB1inHits = "<<rpcev_.RB1inHits<<" , countRecHits = "<<countRecHits<<endl;
            if(lb != pairLsRateRB1in.end()) lb->second += countRecHits;
            else pairLsRateRB1in.insert ( std::pair<int,double>(lumiblock,countRecHits));
          }
          if(rpcId.layer() == 2)
          {
            areaRB1out +=area;
            std::map<int, double>::iterator lb = pairLsRateRB1out.find(lumiblock);
						rpcev_.RB1outHits+=countRecHits;
            if(lb != pairLsRateRB1out.end()) lb->second += countRecHits;
            else pairLsRateRB1out.insert ( std::pair<int,double>(lumiblock,countRecHits));
          }
        }//end RB1in and RB1out

        if(rpcId.station() == 2)
        {
          if(rpcId.layer() == 1)
          {
            areaRB2in +=area;
            std::map<int, double>::iterator lb = pairLsRateRB2in.find(lumiblock);
						rpcev_.RB2inHits+=countRecHits;
            if(lb != pairLsRateRB2in.end()) lb->second += countRecHits;
            else pairLsRateRB2in.insert ( std::pair<int,double>(lumiblock,countRecHits));
          }
          if(rpcId.layer() == 2)
          {
            areaRB2out +=area;
            std::map<int, double>::iterator lb = pairLsRateRB2out.find(lumiblock);
						rpcev_.RB2outHits+=countRecHits;
            if(lb != pairLsRateRB2out.end()) lb->second += countRecHits;
            else pairLsRateRB2out.insert ( std::pair<int,double>(lumiblock,countRecHits));
          }
        }//end RB2in and RB2out

        if(rpcId.station() == 3)
        {
          areaRB3 +=area;
          std::map<int, double>::iterator lb = pairLsRateRB3.find(lumiblock);
					rpcev_.RB3Hits+=countRecHits;
          if(lb != pairLsRateRB3.end()) lb->second += countRecHits;
          else pairLsRateRB3.insert ( std::pair<int,double>(lumiblock,countRecHits));
        }//end RB3
        if(rpcId.station() == 4)
        {
          areaRB4 +=area;
          std::map<int, double>::iterator lb = pairLsRateRB4.find(lumiblock);
					rpcev_.RB4Hits+=countRecHits;
          if(lb != pairLsRateRB4.end()) lb->second += countRecHits;
          else pairLsRateRB4.insert ( std::pair<int,double>(lumiblock,countRecHits));
        }//end RB4
        if (abs(rpcId.ring()) == 2)
        {
          if (rpcId.ring() == 2)
          {
            areaWp2 +=area;
            std::map<int, double>::iterator lb = pairLsRateWp2.find(lumiblock);
						rpcev_.Wp2Hits+=countRecHits;
            if(lb != pairLsRateWp2.end()) lb->second += countRecHits;
            else pairLsRateWp2.insert ( std::pair<int,double>(lumiblock,countRecHits));
          }//W+2
          else
          {
            areaWm2 +=area;
            std::map<int, double>::iterator lb = pairLsRateWm2.find(lumiblock);
						rpcev_.Wm2Hits+=countRecHits;
            if(lb != pairLsRateWm2.end()) lb->second += countRecHits;
            else pairLsRateWm2.insert ( std::pair<int,double>(lumiblock,countRecHits));
          }//W-2
        }
        else
        {
          if (rpcId.ring() == -1)
          {
            areaWm1 +=area;
            std::map<int, double>::iterator lb = pairLsRateWm1.find(lumiblock);
						rpcev_.Wm1Hits+=countRecHits;
            if(lb != pairLsRateWm1.end()) lb->second += countRecHits;
            else pairLsRateWm1.insert ( std::pair<int,double>(lumiblock,countRecHits));
          }//Wm1
          else if (rpcId.ring() == 0)
          {
            areaW0 +=area;
            std::map<int, double>::iterator lb = pairLsRateW0.find(lumiblock);
						rpcev_.W0Hits+=countRecHits;
            if(lb != pairLsRateW0.end()) lb->second += countRecHits;
            else pairLsRateW0.insert ( std::pair<int,double>(lumiblock,countRecHits));
          }//W0
          else if (rpcId.ring() == 1)
          {
            areaWp1 +=area;
            std::map<int, double>::iterator lb = pairLsRateWp1.find(lumiblock);
						rpcev_.Wp1Hits+=countRecHits;
            if(lb != pairLsRateWp1.end()) lb->second += countRecHits;
            else pairLsRateWp1.insert ( std::pair<int,double>(lumiblock,countRecHits));
          }//W+1
        }
      }//end barrel
  }//loop over rolls

  rpcev_.areaRB1in  =  areaRB1in ;   
  rpcev_.areaRB1out =  areaRB1out;
  rpcev_.areaRB2in  =  areaRB2in ;
  rpcev_.areaRB2out =  areaRB2out;
  rpcev_.areaRB3    =  areaRB3 ; 
  rpcev_.areaRB4    =  areaRB4  ;
  rpcev_.areaB      =  areaB  ;
  rpcev_.areaWp2    =  areaWp2 ; 
  rpcev_.areaWp1    =  areaWp1  ;
  rpcev_.areaW0     =  areaW0  ;
  rpcev_.areaWm1    =  areaWm1  ;
  rpcev_.areaWm2    =  areaWm2  ;
  rpcev_.areaREp    =  areaREp  ;
  rpcev_.areaREm    =  areaREm ; 
  rpcev_.areaREp1   =  areaREp1  ;
  rpcev_.areaREp2   =  areaREp2  ;
  rpcev_.areaREp3   =  areaREp3  ;
  rpcev_.areaREp4   =  areaREp4  ;
  rpcev_.areaREm1   =  areaREm1  ;
  rpcev_.areaREm2   =  areaREm2  ;
  rpcev_.areaREm3   =  areaREm3  ;
  rpcev_.areaREm4   =  areaREm4  ;








	// cout<<"areaRB1in = "<<areaRB1in<<endl;
	// cout<<"rpcev_.RB1inHits = "<<rpcev_.RB1inHits<<endl;

  //std::map<int, double>::iterator lb = pairLsRateRB1in.find(lumiblock);
	// for (auto &it : pairLsRateRB1in){
		// cout<<"pairLsRate first (LS) "<<it.first<<"pairLsRateRB1in second (RB1in)"<<it.second<<endl;
	// }

  RPCTree_->Fill();
  memset(&rpcev_,0,sizeof rpcev_);

} // end RateVsLumi:analyzer


// ------------ method called once each job just before starting event loop  ------------
void
RateVsLumi::beginJob()
{
  // edm::Service <TFileService> fs;
// number of events

  RPCTree_ = fs->make<TTree>("nt","");

  // event
  RPCTree_->Branch("nEv",&rpcev_.nEv,"nEv/I");
  RPCTree_->Branch("nLumi",&rpcev_.nLumi,"nLumi/I");
  RPCTree_->Branch("nBX",&rpcev_.nBX,"nBX/I");
  RPCTree_->Branch("nRun",&rpcev_.nRun,"nRun/I");

	//
  RPCTree_->Branch("Ls",&rpcev_.Ls,"Ls/I");
  RPCTree_->Branch("Lumi",&rpcev_.Lumi,"Lumi/D");
  RPCTree_->Branch("Rate",&rpcev_.Rate,"Rate/D");

  RPCTree_->Branch("RB1inHits",&rpcev_.RB1inHits,"RB1inHits/D");
  // RPCTree_->Branch("areaRB1in",&rpcev_.areaRB1in,"areaRB1in/D");


  RPCTree_->Branch("RB1outHits",&rpcev_.RB1outHits,"RB1outHits/D");
  RPCTree_->Branch("RB2inHits",&rpcev_.RB2inHits,"RB2inHits/D");
  RPCTree_->Branch("RB2outHits",&rpcev_.RB2outHits,"RB2outHits/D");
  RPCTree_->Branch("RB3Hits",&rpcev_.RB3Hits,"RB3Hits/D");
  RPCTree_->Branch("RB4Hits",&rpcev_.RB4Hits,"RB4Hits/D");
  RPCTree_->Branch("BHits",&rpcev_.BHits,"BHits/D");
  RPCTree_->Branch("Wp2Hits",&rpcev_.Wp2Hits,"Wp2Hits/D");
  RPCTree_->Branch("Wp1Hits",&rpcev_.Wp1Hits,"Wp1Hits/D");
  RPCTree_->Branch("W0Hits",&rpcev_.W0Hits,"W0Hits/D");
  RPCTree_->Branch("Wm1Hits",&rpcev_.Wm1Hits,"Wm1Hits/D");
  RPCTree_->Branch("Wm2Hits",&rpcev_.Wm2Hits,"Wm2Hits/D");
  RPCTree_->Branch("REpHits",&rpcev_.REpHits,"REpHits/D");
  RPCTree_->Branch("REmHits",&rpcev_.REmHits,"REmHits/D");
  RPCTree_->Branch("REp1Hits",&rpcev_.REp1Hits,"REp1Hits/D");
  RPCTree_->Branch("REp2Hits",&rpcev_.REp2Hits,"REp2Hits/D");
  RPCTree_->Branch("REp3Hits",&rpcev_.REp3Hits,"REp3Hits/D");
  RPCTree_->Branch("REp4Hits",&rpcev_.REp4Hits,"REp4Hits/D");
  RPCTree_->Branch("REm1Hits",&rpcev_.REm1Hits,"REm1Hits/D");
  RPCTree_->Branch("REm2Hits",&rpcev_.REm2Hits,"REm2Hits/D");
  RPCTree_->Branch("REm3Hits",&rpcev_.REm3Hits,"REm3Hits/D");
  RPCTree_->Branch("REm4Hits",&rpcev_.REm4Hits,"REm4Hits/D");

  RPCTree_->Branch("areaRB1in",&rpcev_.areaRB1in,"areaRB1in/D");
  RPCTree_->Branch("areaRB1out",&rpcev_.areaRB1out,"areaRB1out/D");
  RPCTree_->Branch("areaRB2in",&rpcev_.areaRB2in,"areaRB2in/D");
  RPCTree_->Branch("areaRB2out",&rpcev_.areaRB2out,"areaRB2out/D");
  RPCTree_->Branch("areaRB3",&rpcev_.areaRB3,"areaRB3/D");
  RPCTree_->Branch("areaRB4",&rpcev_.areaRB4,"areaRB4/D");
  RPCTree_->Branch("areaB",&rpcev_.areaB,"areaB/D");
  RPCTree_->Branch("areaWp2",&rpcev_.areaWp2,"areaWp2/D");
  RPCTree_->Branch("areaWp1",&rpcev_.areaWp1,"areaWp1/D");
  RPCTree_->Branch("areaW0",&rpcev_.areaW0,"areaW0/D");
  RPCTree_->Branch("areaWm1",&rpcev_.areaWm1,"areaWm1/D");
  RPCTree_->Branch("areaWm2",&rpcev_.areaWm2,"areaWm2/D");
  RPCTree_->Branch("areaREp",&rpcev_.areaREp,"areaREp/D");
  RPCTree_->Branch("areaREm",&rpcev_.areaREm,"areaREm/D");
  RPCTree_->Branch("areaREp1",&rpcev_.areaREp1,"areaREp1/D");
  RPCTree_->Branch("areaREp2",&rpcev_.areaREp2,"areaREp2/D");
  RPCTree_->Branch("areaREp3",&rpcev_.areaREp3,"areaREp3/D");
  RPCTree_->Branch("areaREp4",&rpcev_.areaREp4,"areaREp4/D");
  RPCTree_->Branch("areaREm1",&rpcev_.areaREm1,"areaREm1/D");
  RPCTree_->Branch("areaREm2",&rpcev_.areaREm2,"areaREm2/D");
  RPCTree_->Branch("areaREm3",&rpcev_.areaREm3,"areaREm3/D");
  RPCTree_->Branch("areaREm4",&rpcev_.areaREm4,"areaREm4/D");






//  RPCTree_->Branch("myScale",&rpcev_.myScale,"myScale/D");

  numbEvents =fs->make<TH1F>("numbEvents", "numbEvents", 2, 0., 2.);

/////////// test lumi counts
  LumiNum_LumiCount = fs->make<TGraphErrors> (1130);
  LumiNum_LumiCount->SetName("LumiNum_LumiCount");
  LumiNum_LumiCount->SetTitle("Number of counted lumi section");


///////////////

  LumiVsLs = fs->make<TGraphErrors> (1130);
  LumiVsLs->SetName("LumiVsLs");
  LumiVsLs->SetTitle("Inst Lumi vs Lumi Section");

//digis vs lumi
  Barrel_InstLumi = fs->make<TGraphErrors> (1130);
  Barrel_InstLumi->SetName("Barrel_InstLumi");
  Barrel_InstLumi->SetTitle("Barrel hits vs Inst. lumi");

  RB1in_InstLumi = fs->make<TGraphErrors> (1130);
  RB1in_InstLumi->SetName("RB1in_InstLumi");
  RB1in_InstLumi->SetTitle("RB1in hits vs Inst. lumi");

  RB1out_InstLumi = fs->make<TGraphErrors> (1130);
  RB1out_InstLumi->SetName("RB1out_InstLumi");
  RB1out_InstLumi->SetTitle("RB1out hits vs Inst. lumi");

  RB2in_InstLumi = fs->make<TGraphErrors> (1130);
  RB2in_InstLumi->SetName("RB2in_InstLumi");
  RB2in_InstLumi->SetTitle("RB2in hits vs Inst. lumi");

  RB2out_InstLumi = fs->make<TGraphErrors> (1130);
  RB2out_InstLumi->SetName("RB2out_InstLumi");
  RB2out_InstLumi->SetTitle("RB2out hits vs Inst. lumi");

  RB3_InstLumi = fs->make<TGraphErrors> (1130);
  RB3_InstLumi->SetName("RB3_InstLumi");
  RB3_InstLumi->SetTitle("RB3 hits vs Inst. lumi");

  RB4_InstLumi = fs->make<TGraphErrors> (1130);
  RB4_InstLumi->SetName("RB4_InstLumi");
  RB4_InstLumi->SetTitle("RB4 hits vs Inst. lumi");

  Wp2_InstLumi = fs->make<TGraphErrors> (1130);
  Wp2_InstLumi->SetName("Wp2_InstLumi");
  Wp2_InstLumi->SetTitle("W+2 hits vs Inst. lumi");

  Wp1_InstLumi = fs->make<TGraphErrors> (1130);
  Wp1_InstLumi->SetName("Wp1_InstLumi");
  Wp1_InstLumi->SetTitle("W+1 hits vs Inst. lumi");

  W0_InstLumi = fs->make<TGraphErrors> (1130);
  W0_InstLumi->SetName("W0_InstLumi");
  W0_InstLumi->SetTitle("W0 hits vs Inst. lumi");

  Wm1_InstLumi = fs->make<TGraphErrors> (1130);
  Wm1_InstLumi->SetName("Wm1_InstLumi");
  Wm1_InstLumi->SetTitle("W-1 hits vs Inst. lumi");

  Wm2_InstLumi = fs->make<TGraphErrors> (1130);
  Wm2_InstLumi->SetName("Wm2_InstLumi");
  Wm2_InstLumi->SetTitle("W-2 hits vs Inst. lumi");


  REp_InstLumi = fs->make<TGraphErrors> (1130);
  REp_InstLumi->SetName("REp_InstLumi");
  REp_InstLumi->SetTitle("RE positive hits vs Inst. lumi");

  REp1_InstLumi = fs->make<TGraphErrors> (1130);
  REp1_InstLumi->SetName("REp1_InstLumi");
  REp1_InstLumi->SetTitle("RE+1 hits vs Inst. lumi");

  REp2_InstLumi = fs->make<TGraphErrors> (1130);
  REp2_InstLumi->SetName("REp2_InstLumi");
  REp2_InstLumi->SetTitle("RE+2 hits vs Inst. lumi");

  REp3_InstLumi = fs->make<TGraphErrors> (1130);
  REp3_InstLumi->SetName("REp3_InstLumi");
  REp3_InstLumi->SetTitle("RE+3 hits vs Inst. lumi");

  REp4_InstLumi = fs->make<TGraphErrors> (1130);
  REp4_InstLumi->SetName("REp4_InstLumi");
  REp4_InstLumi->SetTitle("RE+4 hits vs Inst. lumi");

  REm_InstLumi = fs->make<TGraphErrors> (1130);
  REm_InstLumi->SetName("REm_InstLumi");
  REm_InstLumi->SetTitle("RE Negative hits vs Inst. lumi");

  REm1_InstLumi = fs->make<TGraphErrors> (1130);
  REm1_InstLumi->SetName("REm1_InstLumi");
  REm1_InstLumi->SetTitle("RE-1 hits vs Inst. lumi");

  REm2_InstLumi = fs->make<TGraphErrors> (1130);
  REm2_InstLumi->SetName("REm2_InstLumi");
  REm2_InstLumi->SetTitle("RE-2 hits vs Inst. lumi");

  REm3_InstLumi = fs->make<TGraphErrors> (1130);
  REm3_InstLumi->SetName("REm3_InstLumi");
  REm3_InstLumi->SetTitle("RE-3 hits vs Inst. lumi");

  REm4_InstLumi = fs->make<TGraphErrors> (1130);
  REm4_InstLumi->SetName("REm4_InstLumi");
  REm4_InstLumi->SetTitle("RE-4 hits vs Inst. lumi");


//rate in Hz
  Barrel_toHz = fs->make<TGraphErrors> (1130);
  Barrel_toHz->SetName("Barrel_toHz");
  Barrel_toHz->SetTitle("Barrel rate [Hz] vs Inst. lumi");

  RB1in_toHz = fs->make<TGraphErrors> (1130);
  RB1in_toHz->SetName("RB1in_toHz");
  RB1in_toHz->SetTitle("RB1in rate [Hz] vs Inst. lumi");

  RB1out_toHz = fs->make<TGraphErrors> (1130);
  RB1out_toHz->SetName("RB1out_toHz");
  RB1out_toHz->SetTitle("RB1out rate [Hz] vs Inst. lumi");

  RB2in_toHz = fs->make<TGraphErrors> (1130);
  RB2in_toHz->SetName("RB2in_toHz");
  RB2in_toHz->SetTitle("RB2in rate [Hz] vs Inst. lumi");

  RB2out_toHz = fs->make<TGraphErrors> (1130);
  RB2out_toHz->SetName("RB2out_toHz");
  RB2out_toHz->SetTitle("RB2out rate [Hz] vs Inst. lumi");

  RB3_toHz = fs->make<TGraphErrors> (1130);
  RB3_toHz->SetName("RB3_toHz");
  RB3_toHz->SetTitle("RB3 rate [Hz] vs Inst. lumi");

  RB4_toHz = fs->make<TGraphErrors> (1130);
  RB4_toHz->SetName("RB4_toHz");
  RB4_toHz->SetTitle("RB4 rate [Hz] vs Inst. lumi");

  Wp2_toHz = fs->make<TGraphErrors> (1130);
  Wp2_toHz->SetName("Wp2_toHz");
  Wp2_toHz->SetTitle("W+2 rate [Hz] vs Inst. lumi");

  Wp1_toHz = fs->make<TGraphErrors> (1130);
  Wp1_toHz->SetName("Wp1_toHz");
  Wp1_toHz->SetTitle("W+1 rate [Hz] vs Inst. lumi");

  W0_toHz = fs->make<TGraphErrors> (1130);
  W0_toHz->SetName("W0_toHz");
  W0_toHz->SetTitle("W0 rate [Hz] vs Inst. lumi");

  Wm1_toHz = fs->make<TGraphErrors> (1130);
  Wm1_toHz->SetName("Wm1_toHz");
  Wm1_toHz->SetTitle("W-1 rate [Hz] vs Inst. lumi");

  Wm2_toHz = fs->make<TGraphErrors> (1130);
  Wm2_toHz->SetName("Wm2_toHz");
  Wm2_toHz->SetTitle("W-2 rate [Hz] vs Inst. lumi");


  REp_toHz = fs->make<TGraphErrors> (1130);
  REp_toHz->SetName("REp_toHz");
  REp_toHz->SetTitle("RE positive rate [Hz] vs Inst. lumi");

  REp1_toHz = fs->make<TGraphErrors> (1130);
  REp1_toHz->SetName("REp1_toHz");
  REp1_toHz->SetTitle("RE+1 rate [Hz] vs Inst. lumi");

  REp2_toHz = fs->make<TGraphErrors> (1130);
  REp2_toHz->SetName("REp2_toHz");
  REp2_toHz->SetTitle("RE+2 rate [Hz] vs Inst. lumi");

  REp3_toHz = fs->make<TGraphErrors> (1130);
  REp3_toHz->SetName("REp3_toHz");
  REp3_toHz->SetTitle("RE+3 rate [Hz] vs Inst. lumi");

  REp4_toHz = fs->make<TGraphErrors> (1130);
  REp4_toHz->SetName("REp4_toHz");
  REp4_toHz->SetTitle("RE+4 rate [Hz] vs Inst. lumi");

  REm_toHz = fs->make<TGraphErrors> (1130);
  REm_toHz->SetName("REm_toHz");
  REm_toHz->SetTitle("RE Negative rate [Hz] vs Inst. lumi");

  REm1_toHz = fs->make<TGraphErrors> (1130);
  REm1_toHz->SetName("REm1_toHz");
  REm1_toHz->SetTitle("RE-1 rate [Hz] vs Inst. lumi");

  REm2_toHz = fs->make<TGraphErrors> (1130);
  REm2_toHz->SetName("REm2_toHz");
  REm2_toHz->SetTitle("RE-2 rate [Hz] vs Inst. lumi");

  REm3_toHz = fs->make<TGraphErrors> (1130);
  REm3_toHz->SetName("REm3_toHz");
  REm3_toHz->SetTitle("RE-3 rate [Hz] vs Inst. lumi");

  REm4_toHz = fs->make<TGraphErrors> (1130);
  REm4_toHz->SetName("REm4_toHz");
  REm4_toHz->SetTitle("RE-4 rate [Hz] vs Inst. lumi");

//rate in Hz/cm2
  Barrel_toHzcm2 = fs->make<TGraphErrors> (1130);
  Barrel_toHzcm2->SetName("Barrel_toHzcm2");
  Barrel_toHzcm2->SetTitle("Barrel rate [Hz/cm^{2}] vs Inst. lumi");

  RB1in_toHzcm2 = fs->make<TGraphErrors> (1130);
  RB1in_toHzcm2->SetName("RB1in_toHzcm2");
  RB1in_toHzcm2->SetTitle("RB1in rate [Hz/cm^{2}] vs Inst. lumi");

  RB1out_toHzcm2 = fs->make<TGraphErrors> (1130);
  RB1out_toHzcm2->SetName("RB1out_toHzcm2");
  RB1out_toHzcm2->SetTitle("RB1out rate [Hz/cm^{2}] vs Inst. lumi");

  RB2in_toHzcm2 = fs->make<TGraphErrors> (1130);
  RB2in_toHzcm2->SetName("RB2in_toHzcm2");
  RB2in_toHzcm2->SetTitle("RB2in rate [Hz/cm^{2}] vs Inst. lumi");

  RB2out_toHzcm2 = fs->make<TGraphErrors> (1130);
  RB2out_toHzcm2->SetName("RB2out_toHzcm2");
  RB2out_toHzcm2->SetTitle("RB2out rate [Hz/cm^{2}] vs Inst. lumi");

  RB3_toHzcm2 = fs->make<TGraphErrors> (1130);
  RB3_toHzcm2->SetName("RB3_toHzcm2");
  RB3_toHzcm2->SetTitle("RB3 rate [Hz/cm^{2}] vs Inst. lumi");

  RB4_toHzcm2 = fs->make<TGraphErrors> (1130);
  RB4_toHzcm2->SetName("RB4_toHzcm2");
  RB4_toHzcm2->SetTitle("RB4 rate [Hz/cm^{2}] vs Inst. lumi");

  Wp2_toHzcm2 = fs->make<TGraphErrors> (1130);
  Wp2_toHzcm2->SetName("Wp2_toHzcm2");
  Wp2_toHzcm2->SetTitle("W+2 rate [Hz/cm^{2}] vs Inst. lumi");

  Wp1_toHzcm2 = fs->make<TGraphErrors> (1130);
  Wp1_toHzcm2->SetName("Wp1_toHzcm2");
  Wp1_toHzcm2->SetTitle("W+1 rate [Hz/cm^{2}] vs Inst. lumi");

  W0_toHzcm2 = fs->make<TGraphErrors> (1130);
  W0_toHzcm2->SetName("W0_toHzcm2");
  W0_toHzcm2->SetTitle("W0 rate [Hz/cm^{2}] vs Inst. lumi");

  Wm1_toHzcm2 = fs->make<TGraphErrors> (1130);
  Wm1_toHzcm2->SetName("Wm1_toHzcm2");
  Wm1_toHzcm2->SetTitle("W-1 rate [Hz/cm^{2}] vs Inst. lumi");

  Wm2_toHzcm2 = fs->make<TGraphErrors> (1130);
  Wm2_toHzcm2->SetName("Wm2_toHzcm2");
  Wm2_toHzcm2->SetTitle("W-2 rate [Hz/cm^{2}] vs Inst. lumi");


  REp_toHzcm2 = fs->make<TGraphErrors> (1130);
  REp_toHzcm2->SetName("REp_toHzcm2");
  REp_toHzcm2->SetTitle("RE positive rate [Hz/cm^{2}] vs Inst. lumi");

  REp1_toHzcm2 = fs->make<TGraphErrors> (1130);
  REp1_toHzcm2->SetName("REp1_toHzcm2");
  REp1_toHzcm2->SetTitle("RE+1 rate [Hz/cm^{2}] vs Inst. lumi");

  REp2_toHzcm2 = fs->make<TGraphErrors> (1130);
  REp2_toHzcm2->SetName("REp2_toHzcm2");
  REp2_toHzcm2->SetTitle("RE+2 rate [Hz/cm^{2}] vs Inst. lumi");

  REp3_toHzcm2 = fs->make<TGraphErrors> (1130);
  REp3_toHzcm2->SetName("REp3_toHzcm2");
  REp3_toHzcm2->SetTitle("RE+3 rate [Hz/cm^{2}] vs Inst. lumi");

  REp4_toHzcm2 = fs->make<TGraphErrors> (1130);
  REp4_toHzcm2->SetName("REp4_toHzcm2");
  REp4_toHzcm2->SetTitle("RE+4 rate [Hz/cm^{2}] vs Inst. lumi");

  REm_toHzcm2 = fs->make<TGraphErrors> (1130);
  REm_toHzcm2->SetName("REm_toHzcm2");
  REm_toHzcm2->SetTitle("RE Negative rate [Hz/cm^{2}] vs Inst. lumi");

  REm1_toHzcm2 = fs->make<TGraphErrors> (1130);
  REm1_toHzcm2->SetName("REm1_toHzcm2");
  REm1_toHzcm2->SetTitle("RE-1 rate [Hz/cm^{2}] vs Inst. lumi");

  REm2_toHzcm2 = fs->make<TGraphErrors> (1130);
  REm2_toHzcm2->SetName("REm2_toHzcm2");
  REm2_toHzcm2->SetTitle("RE-2 rate [Hz/cm^{2}] vs Inst. lumi");

  REm3_toHzcm2 = fs->make<TGraphErrors> (1130);
  REm3_toHzcm2->SetName("REm3_toHzcm2");
  REm3_toHzcm2->SetTitle("RE-3 rate [Hz/cm^{2}] vs Inst. lumi");

  REm4_toHzcm2 = fs->make<TGraphErrors> (1130);
  REm4_toHzcm2->SetName("REm4_toHzcm2");
  REm4_toHzcm2->SetTitle("RE-4 rate [Hz/cm^{2}] vs Inst. lumi");
}

// ------------ method called once each job just after ending the event loop  ------------
void
RateVsLumi::endJob()
{
  double myTime = 25.e-9 * numbBXs_;	//don't forget to divide in the end to the number of all events
//  double myTime = 25. * 1.0e-9 * numbBXs_;	//don't forget to divide in the end to the number of all events
//  double myTime = 23.8;		//suppose that one lumi section is 23.8 seconds

  int i = 0;
  int jb = 0, jrb1in = 0, jrb1out = 0, jrb2in = 0, jrb2out = 0, jrb3 = 0, jrb4 = 0;
  int jwp2 = 0, jwp1 = 0, jw0 = 0, jwm1 = 0, jwm2 = 0;
  int jrem = 0, jrem1 = 0, jrem2 = 0, jrem3 = 0, jrem4 = 0;
  int jrep = 0, jrep1 = 0, jrep2 = 0, jrep3 = 0, jrep4 = 0;

  int myscale = 1;

  std::map<int,int>::iterator cc = pairLsCounts.begin();
  int ii = 0;
  for (cc=pairLsCounts.begin(); cc!=pairLsCounts.end(); ++cc)
  {
    LumiNum_LumiCount->SetPoint(ii, cc->first, cc->second);
    ii++;
  }

  std::map<int,double>::iterator itLumi = pairLsLumi.begin();
  for (itLumi=pairLsLumi.begin(); itLumi!=pairLsLumi.end(); ++itLumi)
  {
    if (debug) std::cout << itLumi->first << " " << itLumi->second << std::endl;
    LumiVsLs->SetPoint(i, itLumi->first, itLumi->second);
    i++;

//find how many times the lumi section was analyzed
   std::map<int, int>::iterator itr = pairLsCounts.find(itLumi->first);
   if(itr != pairLsCounts.end()) myscale = itr->second;
   else std::cout << "no scale was found for luminosity: " << itLumi->first << " " << itLumi->second << std::endl;


//barrel
    std::map<int,double>::iterator itRateB = pairLsRateB.find(itLumi->first);
    if(itRateB != pairLsRateB.end())
    {
      if (debug) std::cout << "Found " << itRateB->first << " " << itRateB->second << std::endl;
      Barrel_InstLumi->SetPoint(jb, itLumi->second, itRateB->second);
      Barrel_toHz->SetPoint(jb, itLumi->second, (itRateB->second)/(myTime*myscale*1.));
      Barrel_toHzcm2->SetPoint(jb, itLumi->second, (itRateB->second)/(areaB*myTime*myscale*1.));
      jb++;
    }
    else std::cout << "Not found Barrel" << std::endl;
//rb1in
    std::map<int,double>::iterator itRateRB1in = pairLsRateRB1in.find(itLumi->first);
    if(itRateRB1in != pairLsRateRB1in.end())
    {
      if (debug) std::cout << "Found " << itRateRB1in->first << " " << itRateRB1in->second << std::endl;
      RB1in_InstLumi->SetPoint(jrb1in, itLumi->second, itRateRB1in->second);
      RB1in_toHz->SetPoint(jrb1in, itLumi->second, (itRateRB1in->second)/(myTime*myscale*1.));
      RB1in_toHzcm2->SetPoint(jrb1in, itLumi->second, (itRateRB1in->second)/(areaRB1in*myTime*myscale*1.));
      jrb1in++;
    }
    else std::cout << "Not found RB1in" << std::endl;
//rb1out
    std::map<int,double>::iterator itRateRB1out = pairLsRateRB1out.find(itLumi->first);
    if(itRateRB1out != pairLsRateRB1out.end())
    {
      if (debug) std::cout << "Found " << itRateRB1out->first << " " << itRateRB1out->second << std::endl;
      RB1out_InstLumi->SetPoint(jrb1out, itLumi->second, itRateRB1out->second);
      RB1out_toHz->SetPoint(jrb1out, itLumi->second, (itRateRB1out->second)/(myTime*myscale*1.));
      RB1out_toHzcm2->SetPoint(jrb1out, itLumi->second, (itRateRB1out->second)/(areaRB1out*myTime*myscale*1.));
      jrb1out++;
    }
    else std::cout << "Not found RB1out" << std::endl;
//RB2in
    std::map<int,double>::iterator itRateRB2in = pairLsRateRB2in.find(itLumi->first);
    if(itRateRB2in != pairLsRateRB2in.end())
    {
      if (debug) std::cout << "Found " << itRateRB2in->first << " " << itRateRB2in->second << std::endl;
      RB2in_InstLumi->SetPoint(jrb2in, itLumi->second, itRateRB2in->second);
      RB2in_toHz->SetPoint(jrb2in, itLumi->second, (itRateRB2in->second)/(myTime*myscale*1.));
      RB2in_toHzcm2->SetPoint(jrb2in, itLumi->second, (itRateRB2in->second)/(areaRB2in*myTime*myscale*1.));
      jrb2in++;
    }
    else std::cout << "Not found RB2in" << std::endl;
//RB2out
    std::map<int,double>::iterator itRateRB2out = pairLsRateRB2out.find(itLumi->first);
    if(itRateRB2out != pairLsRateRB2out.end())
    {
      if (debug) std::cout << "Found " << itRateRB2out->first << " " << itRateRB2out->second << std::endl;
      RB2out_InstLumi->SetPoint(jrb2out, itLumi->second, itRateRB2out->second);
      RB2out_toHz->SetPoint(jrb2out, itLumi->second, (itRateRB2out->second)/(myTime*myscale*1.));
      RB2out_toHzcm2->SetPoint(jrb2out, itLumi->second, (itRateRB2out->second)/(areaRB2out*myTime*myscale*1.));
      jrb2out++;
    }
    else std::cout << "Not found RB2out" << std::endl;
//RB3
    std::map<int,double>::iterator itRateRB3 = pairLsRateRB3.find(itLumi->first);
    if(itRateRB3 != pairLsRateRB3.end())
    {
      if (debug) std::cout << "Found " << itRateRB3->first << " " << itRateRB3->second << std::endl;
      RB3_InstLumi->SetPoint(jrb3, itLumi->second, itRateRB3->second);
      RB3_toHz->SetPoint(jrb3, itLumi->second, (itRateRB3->second)/(myTime*myscale*1.));
      RB3_toHzcm2->SetPoint(jrb3, itLumi->second, (itRateRB3->second)/(areaRB3*myTime*myscale*1.));
      jrb3++;
    }
    else std::cout << "Not found RB3" << std::endl;
//RB4
    std::map<int,double>::iterator itRateRB4 = pairLsRateRB4.find(itLumi->first);
    if(itRateRB4 != pairLsRateRB4.end())
    {
      if (debug) std::cout << "Found " << itRateRB4->first << " " << itRateRB4->second << std::endl;
      RB4_InstLumi->SetPoint(jrb4, itLumi->second, itRateRB4->second);
      RB4_toHz->SetPoint(jrb4, itLumi->second, (itRateRB4->second)/(myTime*myscale*1.));
      RB4_toHzcm2->SetPoint(jrb4, itLumi->second, (itRateRB4->second)/(areaRB4*myTime*myscale*1.));
      jrb4++;
    }
    else std::cout << "Not found RB4" << std::endl;
//Wp2
    std::map<int,double>::iterator itRateWp2 = pairLsRateWp2.find(itLumi->first);
    if(itRateWp2 != pairLsRateWp2.end())
    {
      if (debug) std::cout << "Found " << itRateWp2->first << " " << itRateWp2->second << std::endl;
      Wp2_InstLumi->SetPoint(jwp2, itLumi->second, itRateWp2->second);
      Wp2_toHz->SetPoint(jwp2, itLumi->second, (itRateWp2->second)/(myTime*myscale*1.));
      Wp2_toHzcm2->SetPoint(jwp2, itLumi->second, (itRateWp2->second)/(areaWp2*myTime*myscale*1.));
      jwp2++;
    }
    else std::cout << "Not found Wp2" << std::endl;
//Wp1
    std::map<int,double>::iterator itRateWp1 = pairLsRateWp1.find(itLumi->first);
    if(itRateWp1 != pairLsRateWp1.end())
    {
      if (debug) std::cout << "Found " << itRateWp1->first << " " << itRateWp1->second << std::endl;
      Wp1_InstLumi->SetPoint(jwp1, itLumi->second, itRateWp1->second);
      Wp1_toHz->SetPoint(jwp1, itLumi->second, (itRateWp1->second)/(myTime*myscale*1.));
      Wp1_toHzcm2->SetPoint(jwp1, itLumi->second, (itRateWp1->second)/(areaWp1*myTime*myscale*1.));
      jwp1++;
    }
    else std::cout << "Not found Wp1" << std::endl;
//W0
    std::map<int,double>::iterator itRateW0 = pairLsRateW0.find(itLumi->first);
    if(itRateW0 != pairLsRateW0.end())
    {
      if (debug) std::cout << "Found " << itRateW0->first << " " << itRateW0->second << std::endl;
      W0_InstLumi->SetPoint(jw0, itLumi->second, itRateW0->second);
      W0_toHz->SetPoint(jw0, itLumi->second, (itRateW0->second)/(myTime*myscale*1.));
      W0_toHzcm2->SetPoint(jw0, itLumi->second, (itRateW0->second)/(areaW0*myTime*myscale*1.));
      jw0++;
    }
    else std::cout << "Not found W0" << std::endl;
//Wm1
    std::map<int,double>::iterator itRateWm1 = pairLsRateWm1.find(itLumi->first);
    if(itRateWm1 != pairLsRateWm1.end())
    {
      if (debug) std::cout << "Found " << itRateWm1->first << " " << itRateWm1->second << std::endl;
      Wm1_InstLumi->SetPoint(jwm1, itLumi->second, itRateWm1->second);
      Wm1_toHz->SetPoint(jwm1, itLumi->second, (itRateWm1->second)/(myTime*myscale*1.));
      Wm1_toHzcm2->SetPoint(jwm1, itLumi->second, (itRateWm1->second)/(areaWm1*myTime*myscale*1.));
      jwm1++;
    }
    else std::cout << "Not found Wm1" << std::endl;
//Wm2
    std::map<int,double>::iterator itRateWm2 = pairLsRateWm2.find(itLumi->first);
    if(itRateWm2 != pairLsRateWm2.end())
    {
      if (debug) std::cout << "Found " << itRateWm2->first << " " << itRateWm2->second << std::endl;
      Wm2_InstLumi->SetPoint(jwm2, itLumi->second, itRateWm2->second);
      Wm2_toHz->SetPoint(jwm2, itLumi->second, (itRateWm2->second)/(myTime*myscale*1.));
      Wm2_toHzcm2->SetPoint(jwm2, itLumi->second, (itRateWm2->second)/(areaWm2*myTime*myscale*1.));
      jwm2++;
    }
    else std::cout << "Not found Wm2" << std::endl;
//REp
    std::map<int,double>::iterator itRateREp = pairLsRateREp.find(itLumi->first);
    if(itRateREp != pairLsRateREp.end())
    {
      if (debug) std::cout << "Found " << itRateREp->first << " " << itRateREp->second << std::endl;
      REp_InstLumi->SetPoint(jrep, itLumi->second, itRateREp->second);
      REp_toHz->SetPoint(jrep, itLumi->second, (itRateREp->second)/(myTime*myscale*1.));
      REp_toHzcm2->SetPoint(jrep, itLumi->second, (itRateREp->second)/(areaREp*myTime*myscale*1.));
      jrep++;
    }
    else std::cout << "Not found REp" << std::endl;
//REp1
    std::map<int,double>::iterator itRateREp1 = pairLsRateREp1.find(itLumi->first);
    if(itRateREp1 != pairLsRateREp1.end())
    {
      if (debug) std::cout << "Found " << itRateREp1->first << " " << itRateREp1->second << std::endl;
      REp1_InstLumi->SetPoint(jrep1, itLumi->second, itRateREp1->second);
      REp1_toHz->SetPoint(jrep1, itLumi->second, (itRateREp1->second)/(myTime*myscale*1.));
      REp1_toHzcm2->SetPoint(jrep1, itLumi->second, (itRateREp1->second)/(areaREp1*myTime*myscale*1.));
      jrep1++;
    }
    else std::cout << "Not found REp1" << std::endl;
//REp2
    std::map<int,double>::iterator itRateREp2 = pairLsRateREp2.find(itLumi->first);
    if(itRateREp2 != pairLsRateREp2.end())
    {
      if (debug) std::cout << "Found " << itRateREp2->first << " " << itRateREp2->second << std::endl;
      REp2_InstLumi->SetPoint(jrep2, itLumi->second, itRateREp2->second);
      REp2_toHz->SetPoint(jrep2, itLumi->second, (itRateREp2->second)/(myTime*myscale*1.));
      REp2_toHzcm2->SetPoint(jrep2, itLumi->second, (itRateREp2->second)/(areaREp2*myTime*myscale*1.));
      jrep2++;
    }
    else std::cout << "Not found REp2" << std::endl;
//REp3
    std::map<int,double>::iterator itRateREp3 = pairLsRateREp3.find(itLumi->first);
    if(itRateREp3 != pairLsRateREp3.end())
    {
      if (debug) std::cout << "Found " << itRateREp3->first << " " << itRateREp3->second << std::endl;
      REp3_InstLumi->SetPoint(jrep3, itLumi->second, itRateREp3->second);
      REp3_toHz->SetPoint(jrep3, itLumi->second, (itRateREp3->second)/(myTime*myscale*1.));
      REp3_toHzcm2->SetPoint(jrep3, itLumi->second, (itRateREp3->second)/(areaREp3*myTime*myscale*1.));
      jrep3++;
    }
    else std::cout << "Not found REp3" << std::endl;
//REp4
    std::map<int,double>::iterator itRateREp4 = pairLsRateREp4.find(itLumi->first);
    if(itRateREp4 != pairLsRateREp4.end())
    {
      if (debug) std::cout << "Found " << itRateREp4->first << " " << itRateREp4->second << std::endl;
      REp4_InstLumi->SetPoint(jrep4, itLumi->second, itRateREp4->second);
      REp4_toHz->SetPoint(jrep4, itLumi->second, (itRateREp4->second)/(myTime*myscale*1.));
      REp4_toHzcm2->SetPoint(jrep4, itLumi->second, (itRateREp4->second)/(areaREp4*myTime*myscale*1.));
      jrep4++;
    }
    else std::cout << "Not found REp4" << std::endl;
//REm
    std::map<int,double>::iterator itRateREm = pairLsRateREm.find(itLumi->first);
    if(itRateREm != pairLsRateREm.end())
    {
      if (debug) std::cout << "Found " << itRateREm->first << " " << itRateREm->second << std::endl;
      REm_InstLumi->SetPoint(jrem, itLumi->second, itRateREm->second);
      REm_toHz->SetPoint(jrem, itLumi->second, (itRateREm->second)/(myTime*myscale*1.));
      REm_toHzcm2->SetPoint(jrem, itLumi->second, (itRateREm->second)/(areaREm*myTime*myscale*1.));
      jrem++;
    }
    else std::cout << "Not found REm" << std::endl;
//REm1
    std::map<int,double>::iterator itRateREm1 = pairLsRateREm1.find(itLumi->first);
    if(itRateREm1 != pairLsRateREm1.end())
    {
      if (debug) std::cout << "Found " << itRateREm1->first << " " << itRateREm1->second << std::endl;
      REm1_InstLumi->SetPoint(jrem1, itLumi->second, itRateREm1->second);
      REm1_toHz->SetPoint(jrem1, itLumi->second, (itRateREm1->second)/(myTime*myscale*1.));
      REm1_toHzcm2->SetPoint(jrem1, itLumi->second, (itRateREm1->second)/(areaREm1*myTime*myscale*1.));
      jrem1++;
    }
    else std::cout << "Not found REm1" << std::endl;
//REm2
    std::map<int,double>::iterator itRateREm2 = pairLsRateREm2.find(itLumi->first);
    if(itRateREm2 != pairLsRateREm2.end())
    {
      if (debug) std::cout << "Found " << itRateREm2->first << " " << itRateREm2->second << std::endl;
      REm2_InstLumi->SetPoint(jrem2, itLumi->second, itRateREm2->second);
      REm2_toHz->SetPoint(jrem2, itLumi->second, (itRateREm2->second)/(myTime*myscale*1.));
      REm2_toHzcm2->SetPoint(jrem2, itLumi->second, (itRateREm2->second)/(areaREm2*myTime*myscale*1.));
      jrem2++;
    }
    else std::cout << "Not found REm2" << std::endl;
//REm3
    std::map<int,double>::iterator itRateREm3 = pairLsRateREm3.find(itLumi->first);
    if(itRateREm3 != pairLsRateREm3.end())
    {
      if (debug) std::cout << "Found " << itRateREm3->first << " " << itRateREm3->second << std::endl;
      REm3_InstLumi->SetPoint(jrem3, itLumi->second, itRateREm3->second);
      REm3_toHz->SetPoint(jrem3, itLumi->second, (itRateREm3->second)/(myTime*myscale*1.));
      REm3_toHzcm2->SetPoint(jrem3, itLumi->second, (itRateREm3->second)/(areaREm3*myTime*myscale*1.));
      jrem3++;
    }
    else std::cout << "Not found REm3" << std::endl;
//REm4
    std::map<int,double>::iterator itRateREm4 = pairLsRateREm4.find(itLumi->first);
    if(itRateREm4 != pairLsRateREm4.end())
    {
      if (debug) std::cout << "Found " << itRateREm4->first << " " << itRateREm4->second << std::endl;
      REm4_InstLumi->SetPoint(jrem4, itLumi->second, itRateREm4->second);
      REm4_toHz->SetPoint(jrem4, itLumi->second, (itRateREm4->second)/(myTime*myscale*1.));
      REm4_toHzcm2->SetPoint(jrem4, itLumi->second, (itRateREm4->second)/(areaREm4*myTime*myscale*1.));
      jrem4++;
    }
    else std::cout << "Not found REm4" << std::endl;
  }
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
RateVsLumi::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);

  //Update this part according to the rpc digi analysis
  //Specify that only 'tracks' is allowed
  //To use, remove the default given above and uncomment below
  //ParameterSetDescription desc;
  //desc.addUntracked<edm::InputTag>("tracks","ctfWithMaterialTracks");
  //descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(RateVsLumi);
