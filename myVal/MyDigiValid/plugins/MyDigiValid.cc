// -*- C++ -*-
//
// Package:    myVal/MyDigiValid
// Class:      MyDigiValid
// 
/**\class MyDigiValid MyDigiValid.cc myVal/MyDigiValid/plugins/MyDigiValid.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Roumyana Mileva Hadjiiska
//         Created:  Mon, 02 Mar 2015 17:30:55 GMT
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

// user include files
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "TH2F.h"
#include "TH1F.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include <string>

#include "FWCore/Utilities/interface/EDGetToken.h"
#include "DataFormats/RPCDigi/interface/RPCDigiCollection.h"
#include "SimDataFormats/TrackingHit/interface/PSimHitContainer.h"

#include "Geometry/RPCGeometry/interface/RPCGeometry.h"

#include "FWCore/Utilities/interface/InputTag.h"
#include "SimDataFormats/CrossingFrame/interface/MixCollection.h"

#include "Geometry/Records/interface/MuonGeometryRecord.h"
#include "Geometry/RPCGeometry/interface/RPCGeometry.h"
#include "Geometry/CommonTopologies/interface/RectangularStripTopology.h"
#include "Geometry/CommonTopologies/interface/TrapezoidalStripTopology.h"
#include "DataFormats/GeometryVector/interface/GlobalPoint.h"
#include "DataFormats/GeometryVector/interface/LocalPoint.h"
#include "DataFormats/MuonDetId/interface/RPCDetId.h"

#include <cmath>

//
// class declaration
//

class MyDigiValid : public edm::EDAnalyzer {
   public:
      explicit MyDigiValid(const edm::ParameterSet&);
      ~MyDigiValid();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

      //virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void endRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
      //virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;

     // ----------member data ---------------------------
/*
  TH2F* xyview;
  TH2F* rzview;
  TH1F* Res;
  TH1F* ResWmin2;
  TH1F* ResWmin1;
  TH1F* ResWzer0;
  TH1F* ResWplu1;
  TH1F* ResWplu2;

  //barrel layers residuals
  TH1F* ResLayer1_barrel;
  TH1F* ResLayer2_barrel;
  TH1F* ResLayer3_barrel;
  TH1F* ResLayer4_barrel;
  TH1F* ResLayer5_barrel;
  TH1F* ResLayer6_barrel;

  //members for EndCap's disks:
  TH1F* ResDmin1;
  TH1F* ResDmin2;
  TH1F* ResDmin3;
  TH1F* ResDplu1;
  TH1F* ResDplu2;
  TH1F* ResDplu3;

  //endcap layters residuals
  TH1F* Res_Endcap1_Ring2_A;
  TH1F* Res_Endcap1_Ring2_B;
  TH1F* Res_Endcap1_Ring2_C;

  TH1F* Res_Endcap23_Ring2_A;
  TH1F* Res_Endcap23_Ring2_B;
  TH1F* Res_Endcap23_Ring2_C;

  TH1F* Res_Endcap123_Ring3_A;
  TH1F* Res_Endcap123_Ring3_B;
  TH1F* Res_Endcap123_Ring3_C;

  //new member for cls
  TH1F* noiseCLS;
  TH1F* noiseCLSBarrel;
  TH1F* noiseCLSEndcaps;

  TH1F* clsBarrel;

  //CLS Validation
  //ring2, disk +- 1
  TH1F* CLS_Endcap_1_Ring2_A;
  TH1F* CLS_Endcap_1_Ring2_B;
  TH1F* CLS_Endcap_1_Ring2_C;

  TH1F* CLS_Endcap_23_Ring2_A;
  TH1F* CLS_Endcap_23_Ring2_B;
  TH1F* CLS_Endcap_23_Ring2_C;

  //ring 3
  TH1F* CLS_Endcap_123_Ring3_A;
  TH1F* CLS_Endcap_123_Ring3_B;
  TH1F* CLS_Endcap_123_Ring3_C;
  //CLS Validation

  //4 endcap
  TH1F *ResDmin4;
  TH1F *ResDplu4;
  TH1F *BxDisc_4Plus;
  TH1F *BxDisc_4Min;
  TH2F *xyvDplu4;
  TH2F *xyvDmin4;
  TH1F *CLS_Endcap_4;
*/
//  std::string outputFile_;

  TH1F* BxDist;
  TH1F* StripProf;
  TH1F* hltBxDist;
  TH1F* hltStripProf;

//  std::string digiLabel;

  //Tokens for accessing run data. Used for passing to edm::Event. - stanislav
  edm::EDGetTokenT<edm::PSimHitContainer> simHitToken;
  edm::EDGetTokenT<RPCDigiCollection> rpcDigiToken;
  edm::EDGetTokenT<RPCDigiCollection> rpcDigiTokenHLT;

  bool debug;

};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
MyDigiValid::MyDigiValid(const edm::ParameterSet& iConfig)

{
   //now do what ever initialization is needed
  simHitToken = consumes<edm::PSimHitContainer>(iConfig.getUntrackedParameter<edm::InputTag >("simHitTag", edm::InputTag("g4SimHits:MuonRPCHits")));
  rpcDigiToken    = consumes<RPCDigiCollection>(iConfig.getUntrackedParameter<edm::InputTag>("rpcDigiTag", edm::InputTag("simMuonRPCDigis")));
  rpcDigiTokenHLT    = consumes<RPCDigiCollection>(iConfig.getUntrackedParameter<edm::InputTag>("rpcDigiTag", edm::InputTag("hltMuonRPCDigis")));
  debug = false;

}


MyDigiValid::~MyDigiValid()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
MyDigiValid::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
  // Get the RPC Geometry
  edm::ESHandle<RPCGeometry> rpcGeom;
  iSetup.get<MuonGeometryRecord> ().get(rpcGeom);

  edm::Handle<PSimHitContainer> simHit;
  edm::Handle<RPCDigiCollection> rpcDigis;
  edm::Handle<RPCDigiCollection> rpcDigisHLT;
  iEvent.getByToken(simHitToken, simHit);
  iEvent.getByToken(rpcDigiToken, rpcDigis);
  iEvent.getByToken(rpcDigiTokenHLT, rpcDigisHLT);


//test loop over hltsimhits
/*
  if(rpcDigis.isValid())
  {
    const RPCDigiCollection *myRPCdigis = rpcDigis.product();
    LogDebug("DigiInfo") << "total # rpcDigis: " << rpcDigis->size() ;
  }
  else
    std::cout << "not valid RPCDigiCollection" << std::endl;
*/
/*
  for (unsigned int mydigi = 0; mydigi < rpcDigis->size(); ++mydigi)
  {
    std::cout << i << std::endl;
    const RPCDetId myRpcId = ((*myRPCdigis)[mydigi]).id();
    std::cout << myRpcId << std::endl;
  }
*/
//loop over hltdigis
  RPCDigiCollection::DigiRangeIterator hltdetUnitIt;
  for (hltdetUnitIt = rpcDigisHLT->begin(); hltdetUnitIt != rpcDigisHLT->end(); ++hltdetUnitIt)
  {
//    const RPCDetId hltRsid = (*hltdetUnitIt).first;
//    const RPCRoll* hltroll = dynamic_cast<const RPCRoll*> (rpcGeom->roll(hltRsid));
    const RPCDigiCollection::Range& rangeHlt = (*hltdetUnitIt).second;

    for (RPCDigiCollection::const_iterator digiItHlt = rangeHlt.first; digiItHlt != rangeHlt.second; ++digiItHlt)
    {
      hltStripProf->Fill(digiItHlt->strip());
      hltBxDist->Fill(digiItHlt->bx());
    }

  }

//loop over MC digis
  RPCDigiCollection::DigiRangeIterator detUnitIt;
  for (detUnitIt = rpcDigis->begin(); detUnitIt != rpcDigis->end(); ++detUnitIt)
  {
    const RPCDigiCollection::Range& range = (*detUnitIt).second;

    for (RPCDigiCollection::const_iterator digiIt = range.first; digiIt != range.second; ++digiIt)
    {
      StripProf->Fill(digiIt->strip());
      BxDist->Fill(digiIt->bx());
    }

  }

//end test loop

/*
  // Loop on simhits
  PSimHitContainer::const_iterator simIt;

  //loop over Simhit
  std::map<RPCDetId, std::vector<double> > allsims;

  for (simIt = simHit->begin(); simIt != simHit->end(); simIt++)
  {
    RPCDetId Rsid = (RPCDetId)(*simIt).detUnitId();
    const RPCRoll* soll = dynamic_cast<const RPCRoll*> (rpcGeom->roll(Rsid));
    int ptype = simIt->particleType();

    if (ptype == 13 || ptype == -13)
    {

      std::vector<double> buff;
      if (allsims.find(Rsid) != allsims.end())
      {
        buff = allsims[Rsid];
      }

      buff.push_back(simIt->localPosition().x());

      allsims[Rsid] = buff;
    }
    GlobalPoint p = soll->toGlobal(simIt->localPosition());

    double sim_x = p.x();
    double sim_y = p.y();

    xyview->Fill(sim_x, sim_y);

    if (Rsid.region() == (+1))
    {
      if (Rsid.station() == 4)
      {
        xyvDplu4->Fill(sim_x, sim_y);
      }
    }
    else if (Rsid.region() == (-1))
    {
      if (Rsid.station() == 4)
      {
        xyvDmin4->Fill(sim_x, sim_y);
      }
    }
    rzview->Fill(p.z(), p.perp());
  }

  //loop over Digis
  RPCDigiCollection::DigiRangeIterator detUnitIt;
  for (detUnitIt = rpcDigis->begin(); detUnitIt != rpcDigis->end(); ++detUnitIt)
  {
    const RPCDetId Rsid = (*detUnitIt).first;
    const RPCRoll* roll = dynamic_cast<const RPCRoll*> (rpcGeom->roll(Rsid));

    const RPCDigiCollection::Range& range = (*detUnitIt).second;
    std::vector<double> sims;
    if (allsims.find(Rsid) != allsims.end())
    {
      sims = allsims[Rsid];
    }
    else 
      {
        if(debug) std::cout << "no simhit is found" << std::endl;
      }

    int ndigi=0;
    for (RPCDigiCollection::const_iterator digiIt = range.first; digiIt != range.second; ++digiIt)
    {
      StripProf->Fill(digiIt->strip());
      BxDist->Fill(digiIt->bx());
      //bx for 4 endcaps
      if (Rsid.region() == (+1))
      {
        if (Rsid.station() == 4)
          BxDisc_4Plus->Fill(digiIt->bx());
      }
      else if (Rsid.region() == (-1))
      {
        if (Rsid.station() == 4)
          BxDisc_4Min->Fill(digiIt->bx());
      }
      ndigi++;
    }

    if (sims.size() == 0)
    {
      noiseCLS->Fill(ndigi);
      if (Rsid.region() == 0)
      {
        noiseCLSBarrel->Fill(ndigi);
      }
      if (Rsid.region() == +1 || Rsid.region() == 1)
      {
        noiseCLSEndcaps->Fill(ndigi);
      }
    }
    //CLS histos
    if (Rsid.region() == 0)
    {
      clsBarrel->Fill(ndigi);
    }
    //endcap 
    if (Rsid.region() != 0)
    {
      if (Rsid.ring() == 2)
      {
        if (abs(Rsid.station()) == 1)
        {
          if (Rsid.roll() == 1)
            CLS_Endcap_1_Ring2_A->Fill(ndigi);
          if (Rsid.roll() == 2)
            CLS_Endcap_1_Ring2_B->Fill(ndigi);
          if (Rsid.roll() == 3)
            CLS_Endcap_1_Ring2_C->Fill(ndigi);
        }
        if (abs(Rsid.station()) == 2 || abs(Rsid.station()) == 3)
        {
          if (Rsid.roll() == 1)
            CLS_Endcap_23_Ring2_A->Fill(ndigi);
          if (Rsid.roll() == 2)
            CLS_Endcap_23_Ring2_B->Fill(ndigi);
          if (Rsid.roll() == 3)
            CLS_Endcap_23_Ring2_C->Fill(ndigi);
        }
      }
      if (Rsid.ring() == 3)
      {
        if (Rsid.roll() == 1)
          CLS_Endcap_123_Ring3_A->Fill(ndigi);
        if (Rsid.roll() == 2)
          CLS_Endcap_123_Ring3_B->Fill(ndigi);
        if (Rsid.roll() == 3)
          CLS_Endcap_123_Ring3_C->Fill(ndigi);
      }
      if (abs(Rsid.station()) == 4)
        CLS_Endcap_4->Fill(ndigi);
    }

    if (sims.size() == 1 && ndigi == 1)
    {
      double dis = roll->centreOfStrip(range.first->strip()).x() - sims[0];
      Res->Fill(dis);

      if (Rsid.region() == 0)
      {
        if (Rsid.ring() == -2)
          ResWmin2->Fill(dis);
        else if (Rsid.ring() == -1)
          ResWmin1->Fill(dis);
        else if (Rsid.ring() == 0)
          ResWzer0->Fill(dis);
        else if (Rsid.ring() == 1)
          ResWplu1->Fill(dis);
        else if (Rsid.ring() == 2)
          ResWplu2->Fill(dis);
        //barrel layers
        if (Rsid.station() == 1 && Rsid.layer() == 1)
          ResLayer1_barrel->Fill(dis);
        if (Rsid.station() == 1 && Rsid.layer() == 2)
          ResLayer2_barrel->Fill(dis);
        if (Rsid.station() == 2 && Rsid.layer() == 1)
          ResLayer3_barrel->Fill(dis);
        if (Rsid.station() == 2 && Rsid.layer() == 2)
          ResLayer4_barrel->Fill(dis);
        if (Rsid.station() == 3)
          ResLayer5_barrel->Fill(dis);
        if (Rsid.station() == 4)
          ResLayer6_barrel->Fill(dis);
      }
      //endcap layers residuals
      if (Rsid.region() != 0)
      {
        if (Rsid.ring() == 2)
        {
          if (abs(Rsid.station()) == 1)
          {
            if (Rsid.roll() == 1)
              Res_Endcap1_Ring2_A->Fill(dis);
            if (Rsid.roll() == 2)
              Res_Endcap1_Ring2_B->Fill(dis);
            if (Rsid.roll() == 3)
              Res_Endcap1_Ring2_C->Fill(dis);
          }
          if (abs(Rsid.station()) == 2 || abs(Rsid.station()) == 3)
          {
            if (Rsid.roll() == 1)
              Res_Endcap23_Ring2_A->Fill(dis);
            if (Rsid.roll() == 2)
              Res_Endcap23_Ring2_B->Fill(dis);
            if (Rsid.roll() == 3)
              Res_Endcap23_Ring2_C->Fill(dis);
          }
        }
        if (Rsid.ring() == 3)
        {
          if (Rsid.roll() == 1)
            Res_Endcap123_Ring3_A->Fill(dis);
          if (Rsid.roll() == 2)
            Res_Endcap123_Ring3_B->Fill(dis);
          if (Rsid.roll() == 3)
            Res_Endcap123_Ring3_C->Fill(dis);
        }
      }

      if (Rsid.region() == (+1))
      {

        if (Rsid.station() == 1)
          ResDplu1->Fill(dis);
        else if (Rsid.station() == 2)
          ResDplu2->Fill(dis);
        else if (Rsid.station() == 3)
          ResDplu3->Fill(dis);
        else if (Rsid.station() == 4)
          ResDplu4->Fill(dis);
      }
      if (Rsid.region() == (-1))
      {

        if (Rsid.station() == 1)
          ResDmin1->Fill(dis);
        else if (Rsid.station() == 2)
          ResDmin2->Fill(dis);
        else if (Rsid.station() == 3)
          ResDmin3->Fill(dis);
        else if (Rsid.station() == 4)
          ResDmin4->Fill(dis);
      }
    }
  }



#ifdef THIS_IS_AN_EVENT_EXAMPLE
   Handle<ExampleData> pIn;
   iEvent.getByLabel("example",pIn);
#endif
   
#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
   ESHandle<SetupData> pSetup;
   iSetup.get<SetupRecord>().get(pSetup);
#endif
*/
}


// ------------ method called once each job just before starting event loop  ------------
void 
MyDigiValid::beginJob()
{
  edm::Service < TFileService > fs;
  BxDist = fs->make < TH1F > ("Bunch_Crossing", "Bunch_Crossing", 20, -10., 10.);
  StripProf = fs->make < TH1F > ("Strip_Profile", "Strip_Profile", 100, 0, 100);
  hltBxDist = fs->make < TH1F > ("hltBunch_Crossing", "hltBunch_Crossing", 20, -10., 10.);
  hltStripProf = fs->make < TH1F > ("hltStrip_Profile", "hltStrip_Profile", 100, 0, 100);

/*
  xyview = fs->make < TH2F > ("X_Vs_Y_View", "X_Vs_Y_View", 155, -775., 775., 155, -775., 775.);

  xyvDplu4 = fs->make < TH2F > ("Dplu4_XvsY", "Dplu4_XvsY", 155, -775., 775., 155, -775., 775.);
  xyvDmin4 = fs->make < TH2F > ("Dmin4_XvsY", "Dmin4_XvsY", 155, -775., 775., 155, -775., 775.);

  rzview = fs->make < TH2F > ("R_Vs_Z_View", "R_Vs_Z_View", 216, -1080., 1080., 52, 260., 780.);
  Res = fs->make < TH1F > ("Digi_SimHit_difference", "Digi_SimHit_difference", 300, -8, 8);
  ResWmin2 = fs->make < TH1F > ("W_Min2_Residuals", "W_Min2_Residuals", 400, -8, 8);
  ResWmin1 = fs->make < TH1F > ("W_Min1_Residuals", "W_Min1_Residuals", 400, -8, 8);
  ResWzer0 = fs->make < TH1F > ("W_Zer0_Residuals", "W_Zer0_Residuals", 400, -8, 8);
  ResWplu1 = fs->make < TH1F > ("W_Plu1_Residuals", "W_Plu1_Residuals", 400, -8, 8);
  ResWplu2 = fs->make < TH1F > ("W_Plu2_Residuals", "W_Plu2_Residuals", 400, -8, 8);

  ResLayer1_barrel = fs->make < TH1F > ("ResLayer1_barrel", "ResLayer1_barrel", 400, -8, 8);
  ResLayer2_barrel = fs->make < TH1F > ("ResLayer2_barrel", "ResLayer2_barrel", 400, -8, 8);
  ResLayer3_barrel = fs->make < TH1F > ("ResLayer3_barrel", "ResLayer3_barrel", 400, -8, 8);
  ResLayer4_barrel = fs->make < TH1F > ("ResLayer4_barrel", "ResLayer4_barrel", 400, -8, 8);
  ResLayer5_barrel = fs->make < TH1F > ("ResLayer5_barrel", "ResLayer5_barrel", 400, -8, 8);
  ResLayer6_barrel = fs->make < TH1F > ("ResLayer6_barrel", "ResLayer6_barrel", 400, -8, 8);

  BxDisc_4Plus = fs->make < TH1F > ("BxDisc_4Plus", "BxDisc_4Plus", 20, -10., 10.);
  BxDisc_4Min = fs->make < TH1F > ("BxDisc_4Min", "BxDisc_4Min", 20, -10., 10.);

  //cls histos
  noiseCLS = fs->make < TH1F > ("noiseCLS", "noiseCLS", 10, 0.5, 10.5);
  noiseCLSBarrel = fs->make < TH1F > ("noiseCLSBarrel", "noiseCLSBarrel", 10, 0.5, 10.5);
  noiseCLSEndcaps = fs->make < TH1F > ("noiseCLSEndcaps", "noiseCLSEndcaps", 10, 0.5, 10.5);

  clsBarrel = fs->make < TH1F > ("clsBarrel", "clsBarrel", 10, 0.5, 10.5);

  //endcap CLS
  CLS_Endcap_1_Ring2_A = fs->make < TH1F > ("CLS_Endcap_1_1Ring2_A", "CLS_Endcap_1_Ring2_A", 10, 0.5, 10.5);
  CLS_Endcap_1_Ring2_B = fs->make < TH1F > ("CLS_Endcap_1_1Ring2_B", "CLS_Endcap_1_Ring2_B", 10, 0.5, 10.5);
  CLS_Endcap_1_Ring2_C = fs->make < TH1F > ("CLS_Endcap_1_1Ring2_C", "CLS_Endcap_1_Ring2_C", 10, 0.5, 10.5);

  CLS_Endcap_23_Ring2_A = fs->make < TH1F > ("CLS_Endcap_23_Ring2_A", "CLS_Endcap_23_Ring2_A", 10, 0.5, 10.5);
  CLS_Endcap_23_Ring2_B = fs->make < TH1F > ("CLS_Endcap_23_Ring2_B", "CLS_Endcap_23_Ring2_B", 10, 0.5, 10.5);
  CLS_Endcap_23_Ring2_C = fs->make < TH1F > ("CLS_Endcap_23_Ring2_C", "CLS_Endcap_23_Ring2_C", 10, 0.5, 10.5);

  CLS_Endcap_123_Ring3_A = fs->make < TH1F > ("CLS_Endcap_123_Ring3_A", "CLS_Endcap_123_Ring3_A", 10, 0.5, 10.5);
  CLS_Endcap_123_Ring3_B = fs->make < TH1F > ("CLS_Endcap_123_Ring3_B", "CLS_Endcap_123_Ring3_B", 10, 0.5, 10.5);
  CLS_Endcap_123_Ring3_C = fs->make < TH1F > ("CLS_Endcap_123_Ring3_C", "CLS_Endcap_123_Ring3_C", 10, 0.5, 10.5);

  CLS_Endcap_4 = fs->make < TH1F > ("CLS_Endcap_4", "CLS_Endcap_4", 10, 0.5, 10.5);

  //endcap residuals
  ResDmin1 = fs->make < TH1F > ("Disk_Min1_Residuals", "Disk_Min1_Residuals", 400, -8, 8);
  ResDmin2 = fs->make < TH1F > ("Disk_Min2_Residuals", "Disk_Min2_Residuals", 400, -8, 8);
  ResDmin3 = fs->make < TH1F > ("Disk_Min3_Residuals", "Disk_Min3_Residuals", 400, -8, 8);
  ResDplu1 = fs->make < TH1F > ("Disk_Plu1_Residuals", "Disk_Plu1_Residuals", 400, -8, 8);
  ResDplu2 = fs->make < TH1F > ("Disk_Plu2_Residuals", "Disk_Plu2_Residuals", 400, -8, 8);
  ResDplu3 = fs->make < TH1F > ("Disk_Plu3_Residuals", "Disk_Plu3_Residuals", 400, -8, 8);

  ResDmin4 = fs->make < TH1F > ("Disk_Min4_Residuals", "Disk_Min4_Residuals", 400, -8, 8);
  ResDplu4 = fs->make < TH1F > ("Disk_Plu4_Residuals", "Disk_Plu4_Residuals", 400, -8, 8);

  Res_Endcap1_Ring2_A = fs->make < TH1F > ("Res_Endcap1_Ring2_A", "Res_Endcap1_Ring2_A", 400, -8, 8);
  Res_Endcap1_Ring2_B = fs->make < TH1F > ("Res_Endcap1_Ring2_B", "Res_Endcap1_Ring2_B", 400, -8, 8);
  Res_Endcap1_Ring2_C = fs->make < TH1F > ("Res_Endcap1_Ring2_C", "Res_Endcap1_Ring2_C", 400, -8, 8);

  Res_Endcap23_Ring2_A = fs->make < TH1F > ("Res_Endcap23_Ring2_A", "Res_Endcap23_Ring2_A", 400, -8, 8);
  Res_Endcap23_Ring2_B = fs->make < TH1F > ("Res_Endcap23_Ring2_B", "Res_Endcap23_Ring2_B", 400, -8, 8);
  Res_Endcap23_Ring2_C = fs->make < TH1F > ("Res_Endcap23_Ring2_C", "Res_Endcap23_Ring2_C", 400, -8, 8);

  Res_Endcap123_Ring3_A = fs->make < TH1F > ("Res_Endcap123_Ring3_A", "Res_Endcap123_Ring3_A", 400, -8, 8);
  Res_Endcap123_Ring3_B = fs->make < TH1F > ("Res_Endcap123_Ring3_B", "Res_Endcap123_Ring3_B", 400, -8, 8);
  Res_Endcap123_Ring3_C = fs->make < TH1F > ("Res_Endcap123_Ring3_C", "Res_Endcap123_Ring3_C", 400, -8, 8);
*/

}

// ------------ method called once each job just after ending the event loop  ------------
void 
MyDigiValid::endJob() 
{
}

// ------------ method called when starting to processes a run  ------------
/*
void 
MyDigiValid::beginRun(edm::Run const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when ending the processing of a run  ------------
/*
void 
MyDigiValid::endRun(edm::Run const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when starting to processes a luminosity block  ------------
/*
void 
MyDigiValid::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when ending the processing of a luminosity block  ------------
/*
void 
MyDigiValid::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
MyDigiValid::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(MyDigiValid);
