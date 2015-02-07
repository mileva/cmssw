// -*- C++ -*-
//
// Package:    AnaTime
// Class:      AnaTime
//
/**\class AnaTime AnaTime.cc anaTime/AnaTime/plugins/AnaTime.cc

 Description: [one line class summary]

 Implementation:
 [Notes on implementation]
 */
//
// Original Author:  Roumyana Mileva Hadjiiska
//         Created:  Thu, 08 Jan 2015 13:29:56 GMT
// $Id$
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

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "TH2F.h"
#include "TH1F.h"

#include "DataFormats/MuonReco/interface/Muon.h"

//
// class declaration
//

class AnaTime: public edm::EDAnalyzer
{
public:
  explicit AnaTime(const edm::ParameterSet&);
  ~AnaTime();

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
  edm::InputTag muons_;
  double muonPtCut_;
  double muonMinEtaCut_;
  double muonMaxEtaCut_;
  bool debug;

  TH1F *allMuonsTimeInOut, *allMuonsTimeOutIn, *allMuonsTimeDirection, *allMuonsTimeInOutUndef, *allMuonsTimeOutInUndef;
  TH1F *allMuonsTimeInOutPos, *allMuonsTimeOutInPos, *allMuonsTimeInOutNeg, *allMuonsTimeOutInNeg;
  TH1F *allMuonsTimeDirectionValid, *allMuonsTimeDirectionNoValid;
  TH1F *allMuonsTimeInOutPosValid, *allMuonsTimeOutInPosValid;

  TH1F *rpcMuonsTimeDirection, *rpcMuonsTimeInOut, *rpcMuonsTimeInOutPos, *rpcMuonsTimeInOutNeg, *rpcMuonsTimeInOutUndef;
  TH1F *staMuonsTimeDirection, *staMuonsTimeInOut, *staMuonsTimeInOutPos, *staMuonsTimeInOutNeg, *staMuonsTimeInOutUndef;
  TH1F *globMuonsTimeDirection, *globMuonsTimeInOut, *globMuonsTimeInOutPos, *globMuonsTimeInOutNeg, *globMuonsTimeInOutUndef;
  TH1F *trackMuonsTimeDirection, *trackMuonsTimeInOutPos, *trackMuonsTimeInOutNeg, *trackMuonsTimeInOutUndef;

  TH2F *allMuTimeInOutPosVsPt, *allMuTimeInOutPosVsEta, *allMuTimeInOutPosVsPhi;
  TH2F *allMuTimeInOutNegVsPt, *allMuTimeInOutNegVsEta, *allMuTimeInOutNegVsPhi;
  TH2F *allMuTimeInOutUndefVsPt, *allMuTimeInOutUndefVsEta, *allMuTimeInOutUndefVsPhi;

  TH1F *staMuonsGemValHitEndcapPos, *staMuonsMuonValHitEndcapPos, *staMuonsRPCValHitEndcapPos, *staMuonsCSCValHitEndcapPos;
  TH1F *staMuonsGemValHitEndcapNeg, *staMuonsMuonValHitEndcapNeg, *staMuonsRPCValHitEndcapNeg, *staMuonsCSCValHitEndcapNeg;
  TH1F *staMuonsGemValHitEndcapUndef, *staMuonsMuonValHitEndcapUndef, *staMuonsRPCValHitEndcapUndef, *staMuonsCSCValHitEndcapUndef;

  TH2F *gemValidHitvsTimeInOutPos, *rpcValidHitvsTimeInOutPos, *cscValidHitvsTimeInOutPos;
  TH2F *gemValidHitvsTimeInOutNeg, *rpcValidHitvsTimeInOutNeg, *cscValidHitvsTimeInOutNeg;
  TH2F *gemValidHitvsTimeInOutUndef, *rpcValidHitvsTimeInOutUndef, *cscValidHitvsTimeInOutUndef;

  TH1F *gemcscValidHitvsTimeInOutPos, *gemrpcValidHitvsTimeInOutPos, *cscrpcValidHitvsTimeInOutPos;
  TH1F *gemcscValidHitvsTimeInOutNeg, *gemrpcValidHitvsTimeInOutNeg, *cscrpcValidHitvsTimeInOutNeg;
  TH1F *gemcscValidHitvsTimeInOutUndef, *gemrpcValidHitvsTimeInOutUndef, *cscrpcValidHitvsTimeInOutUndef;



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
AnaTime::AnaTime(const edm::ParameterSet& iConfig) :
    muons_(iConfig.getParameter < edm::InputTag > ("muonLabel")) //
        , muonPtCut_(iConfig.getParameter<double>("muonPtCut")) //
        , muonMinEtaCut_(iConfig.getParameter<double>("muonMinEtaCut")) //
        , muonMaxEtaCut_(iConfig.getParameter<double>("muonMaxEtaCut")) //

{
  debug = false;
}

AnaTime::~AnaTime()
{

  // do anything here that needs to be done at desctruction time
  // (e.g. close files, deallocate resources etc.)

}

//
// member functions
//

// ------------ method called for each event  ------------
void AnaTime::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
//  std::cout << "event number\t" << (iEvent.id()).event() << "\tlumi number\t" << (iEvent.id()).luminosityBlock() << "\trun\t" << (iEvent.id()).run() << std::endl;

  using namespace edm;
  using namespace std;
  using namespace reco;
  if (debug)
  {
    std::cout << "in MuonMCClassifAndAna !" << std::endl;
  }
  //getting muon collection
  edm::Handle < edm::View<reco::Muon> > myMuons;
  iEvent.getByLabel(muons_, myMuons);
  size_t nmu = myMuons->size();

  for (size_t i = 0, n = nmu; i < n; ++i)
  {
    allMuonsTimeInOut->Fill((*myMuons)[i].time().timeAtIpInOut);
    allMuonsTimeOutIn->Fill((*myMuons)[i].time().timeAtIpOutIn);

    if ((*myMuons)[i].time().direction() > 0)
    {
      allMuonsTimeDirection->Fill(1);
      allMuonsTimeInOutPos->Fill((*myMuons)[i].time().timeAtIpInOut);
      allMuonsTimeOutInPos->Fill((*myMuons)[i].time().timeAtIpOutIn);
      allMuTimeInOutPosVsPt->Fill((*myMuons)[i].time().timeAtIpInOut, (*myMuons)[i].pt());
      allMuTimeInOutPosVsEta->Fill((*myMuons)[i].time().timeAtIpInOut, (*myMuons)[i].eta());
      allMuTimeInOutPosVsPhi->Fill((*myMuons)[i].time().timeAtIpInOut, (*myMuons)[i].phi());

      if ((*myMuons)[i].isTimeValid())
      {
        allMuonsTimeDirectionValid->Fill(1);
        allMuonsTimeInOutPosValid->Fill((*myMuons)[i].time().timeAtIpInOut);
        allMuonsTimeOutInPosValid->Fill((*myMuons)[i].time().timeAtIpOutIn);
      }
      else allMuonsTimeDirectionNoValid->Fill(1);
    }
    else if ((*myMuons)[i].time().direction() < 0)
    {
      allMuonsTimeDirection->Fill(-1);
      allMuonsTimeInOutNeg->Fill((*myMuons)[i].time().timeAtIpInOut);
      allMuonsTimeOutInNeg->Fill((*myMuons)[i].time().timeAtIpOutIn);
      allMuTimeInOutNegVsPt->Fill((*myMuons)[i].time().timeAtIpInOut, (*myMuons)[i].pt());
      allMuTimeInOutNegVsEta->Fill((*myMuons)[i].time().timeAtIpInOut, (*myMuons)[i].eta());
      allMuTimeInOutNegVsPhi->Fill((*myMuons)[i].time().timeAtIpInOut, (*myMuons)[i].phi());

      if ((*myMuons)[i].isTimeValid()) allMuonsTimeDirectionValid->Fill(-1);
      else allMuonsTimeDirectionNoValid->Fill(-1);
    }
    else if ((*myMuons)[i].time().direction() == 0)
    {
      allMuonsTimeDirection->Fill(0);
      allMuonsTimeInOutUndef->Fill((*myMuons)[i].time().timeAtIpInOut);
      allMuonsTimeOutInUndef->Fill((*myMuons)[i].time().timeAtIpOutIn);
      allMuTimeInOutUndefVsPt->Fill((*myMuons)[i].time().timeAtIpInOut, (*myMuons)[i].pt());
      allMuTimeInOutUndefVsEta->Fill((*myMuons)[i].time().timeAtIpInOut, (*myMuons)[i].eta());
      allMuTimeInOutUndefVsPhi->Fill((*myMuons)[i].time().timeAtIpInOut, (*myMuons)[i].phi());

      if ((*myMuons)[i].isTimeValid()) allMuonsTimeDirectionValid->Fill(0);
      else allMuonsTimeDirectionNoValid->Fill(0);
    }
    else
      std::cout << "no direction estimation for muon" << std::endl;

    if((*myMuons)[i].isRPCMuon())
    {
      rpcMuonsTimeInOut->Fill((*myMuons)[i].time().timeAtIpInOut);
      if ((*myMuons)[i].time().direction() > 0)
      {
        rpcMuonsTimeDirection->Fill(1);
        rpcMuonsTimeInOutPos->Fill((*myMuons)[i].time().timeAtIpInOut);
      }
      else if ((*myMuons)[i].time().direction() < 0)
      {
        rpcMuonsTimeDirection->Fill(-1);
        rpcMuonsTimeInOutNeg->Fill((*myMuons)[i].time().timeAtIpInOut);
      }
      else if ((*myMuons)[i].time().direction() == 0)
      {
        rpcMuonsTimeDirection->Fill(0);
        rpcMuonsTimeInOutUndef->Fill((*myMuons)[i].time().timeAtIpInOut);
      }
      else
        std::cout << "no direction estimation for RPC muon" << std::endl;
    }//end rpc muon

    if((*myMuons)[i].isStandAloneMuon())
    {
      staMuonsTimeInOut->Fill((*myMuons)[i].time().timeAtIpInOut);
      if ((*myMuons)[i].time().direction() > 0)
      {
        staMuonsTimeDirection->Fill(1);
        staMuonsTimeInOutPos->Fill((*myMuons)[i].time().timeAtIpInOut);
        if(((*myMuons)[i].eta())>=1.5 && ((*myMuons)[i].eta())<=2.2 && (*myMuons)[i].outerTrack().isNonnull())
        {
          reco::TrackRef statrackref = (*myMuons)[i].outerTrack();
/*
          staMuonsGemValHitEndcapPos->Fill(statrackref->hitPattern().gemStationsWithValidHits());
          staMuonsMuonValHitEndcapPos->Fill(statrackref->hitPattern().muonStationsWithValidHits());
          staMuonsRPCValHitEndcapPos->Fill(statrackref->hitPattern().rpcStationsWithValidHits());
          staMuonsCSCValHitEndcapPos->Fill(statrackref->hitPattern().cscStationsWithValidHits());
*/
          staMuonsGemValHitEndcapPos->Fill(statrackref->hitPattern().numberOfValidMuonGEMHits());
          staMuonsMuonValHitEndcapPos->Fill(statrackref->hitPattern().numberOfValidMuonHits());
          staMuonsRPCValHitEndcapPos->Fill(statrackref->hitPattern().numberOfValidMuonRPCHits());
          staMuonsCSCValHitEndcapPos->Fill(statrackref->hitPattern().numberOfValidMuonCSCHits());

          gemcscValidHitvsTimeInOutPos->Fill(statrackref->hitPattern().numberOfValidMuonGEMHits() + statrackref->hitPattern().numberOfValidMuonCSCHits());
          gemrpcValidHitvsTimeInOutPos->Fill(statrackref->hitPattern().numberOfValidMuonGEMHits() + statrackref->hitPattern().numberOfValidMuonRPCHits());
          cscrpcValidHitvsTimeInOutPos->Fill(statrackref->hitPattern().numberOfValidMuonCSCHits() + statrackref->hitPattern().numberOfValidMuonRPCHits());

          gemValidHitvsTimeInOutPos->Fill((*myMuons)[i].time().timeAtIpInOut, statrackref->hitPattern().numberOfValidMuonGEMHits());
          rpcValidHitvsTimeInOutPos->Fill((*myMuons)[i].time().timeAtIpInOut, statrackref->hitPattern().numberOfValidMuonRPCHits());
          cscValidHitvsTimeInOutPos->Fill((*myMuons)[i].time().timeAtIpInOut, statrackref->hitPattern().numberOfValidMuonCSCHits());

        }
      }
      else if ((*myMuons)[i].time().direction() < 0)
      {
        staMuonsTimeDirection->Fill(-1);
        staMuonsTimeInOutNeg->Fill((*myMuons)[i].time().timeAtIpInOut);
        if (((*myMuons)[i].eta()) >= 1.5 && ((*myMuons)[i].eta()) <= 2.2 && (*myMuons)[i].outerTrack().isNonnull())
        {
          reco::TrackRef statrackref = (*myMuons)[i].outerTrack();
/*
          staMuonsGemValHitEndcapNeg->Fill(statrackref->hitPattern().gemStationsWithValidHits());
          staMuonsMuonValHitEndcapNeg->Fill(statrackref->hitPattern().muonStationsWithValidHits());
          staMuonsRPCValHitEndcapNeg->Fill(statrackref->hitPattern().rpcStationsWithValidHits());
          staMuonsCSCValHitEndcapNeg->Fill(statrackref->hitPattern().cscStationsWithValidHits());
*/
          staMuonsGemValHitEndcapNeg->Fill(statrackref->hitPattern().numberOfValidMuonGEMHits());
          staMuonsMuonValHitEndcapNeg->Fill(statrackref->hitPattern().numberOfValidMuonHits());
          staMuonsRPCValHitEndcapNeg->Fill(statrackref->hitPattern().numberOfValidMuonRPCHits());
          staMuonsCSCValHitEndcapNeg->Fill(statrackref->hitPattern().numberOfValidMuonCSCHits());

          gemcscValidHitvsTimeInOutNeg->Fill(statrackref->hitPattern().numberOfValidMuonGEMHits() + statrackref->hitPattern().numberOfValidMuonCSCHits());
          gemrpcValidHitvsTimeInOutNeg->Fill(statrackref->hitPattern().numberOfValidMuonGEMHits() + statrackref->hitPattern().numberOfValidMuonRPCHits());
          cscrpcValidHitvsTimeInOutNeg->Fill(statrackref->hitPattern().numberOfValidMuonCSCHits() + statrackref->hitPattern().numberOfValidMuonRPCHits());

          gemValidHitvsTimeInOutNeg->Fill((*myMuons)[i].time().timeAtIpInOut, statrackref->hitPattern().numberOfValidMuonGEMHits());
          rpcValidHitvsTimeInOutNeg->Fill((*myMuons)[i].time().timeAtIpInOut, statrackref->hitPattern().numberOfValidMuonRPCHits());
          cscValidHitvsTimeInOutNeg->Fill((*myMuons)[i].time().timeAtIpInOut, statrackref->hitPattern().numberOfValidMuonCSCHits());

        }
      }
      else if ((*myMuons)[i].time().direction() == 0)
      {
        staMuonsTimeDirection->Fill(0);
        staMuonsTimeInOutUndef->Fill((*myMuons)[i].time().timeAtIpInOut);
        if (((*myMuons)[i].eta()) >= 1.5 && ((*myMuons)[i].eta()) <= 2.2 && (*myMuons)[i].outerTrack().isNonnull())
        {
          reco::TrackRef statrackref = (*myMuons)[i].outerTrack();
/*
          staMuonsGemValHitEndcapUndef->Fill(statrackref->hitPattern().gemStationsWithValidHits());
          staMuonsMuonValHitEndcapUndef->Fill(statrackref->hitPattern().muonStationsWithValidHits());
          staMuonsRPCValHitEndcapUndef->Fill(statrackref->hitPattern().rpcStationsWithValidHits());
          staMuonsCSCValHitEndcapUndef->Fill(statrackref->hitPattern().cscStationsWithValidHits());
*/
          staMuonsGemValHitEndcapUndef->Fill(statrackref->hitPattern().numberOfValidMuonGEMHits());
          staMuonsMuonValHitEndcapUndef->Fill(statrackref->hitPattern().numberOfValidMuonHits());
          staMuonsRPCValHitEndcapUndef->Fill(statrackref->hitPattern().numberOfValidMuonRPCHits());
          staMuonsCSCValHitEndcapUndef->Fill(statrackref->hitPattern().numberOfValidMuonCSCHits());
          gemcscValidHitvsTimeInOutUndef->Fill(statrackref->hitPattern().numberOfValidMuonGEMHits() + statrackref->hitPattern().numberOfValidMuonCSCHits());
          gemrpcValidHitvsTimeInOutUndef->Fill(statrackref->hitPattern().numberOfValidMuonGEMHits() + statrackref->hitPattern().numberOfValidMuonRPCHits());
          cscrpcValidHitvsTimeInOutUndef->Fill(statrackref->hitPattern().numberOfValidMuonCSCHits() + statrackref->hitPattern().numberOfValidMuonRPCHits());

          gemValidHitvsTimeInOutUndef->Fill((*myMuons)[i].time().timeAtIpInOut, statrackref->hitPattern().numberOfValidMuonGEMHits());
          rpcValidHitvsTimeInOutUndef->Fill((*myMuons)[i].time().timeAtIpInOut, statrackref->hitPattern().numberOfValidMuonRPCHits());
          cscValidHitvsTimeInOutUndef->Fill((*myMuons)[i].time().timeAtIpInOut, statrackref->hitPattern().numberOfValidMuonCSCHits());
        }
      }
      else
        std::cout << "no direction estimation for StandAlone muon" << std::endl;
    }//end sta muon

    if((*myMuons)[i].isGlobalMuon())
    {
      globMuonsTimeInOut->Fill((*myMuons)[i].time().timeAtIpInOut);
      if ((*myMuons)[i].time().direction() > 0)
      {
        globMuonsTimeDirection->Fill(1);
        globMuonsTimeInOutPos->Fill((*myMuons)[i].time().timeAtIpInOut);
      }
      else if ((*myMuons)[i].time().direction() < 0)
      {
        globMuonsTimeDirection->Fill(-1);
        globMuonsTimeInOutNeg->Fill((*myMuons)[i].time().timeAtIpInOut);
      }
      else if ((*myMuons)[i].time().direction() == 0)
      {
        globMuonsTimeDirection->Fill(0);
        globMuonsTimeInOutUndef->Fill((*myMuons)[i].time().timeAtIpInOut);
      }
      else
        std::cout << "no direction estimation for Global muon" << std::endl;
    }//end global muon

    if((*myMuons)[i].isTrackerMuon())
    {
      if ((*myMuons)[i].time().direction() > 0)
      {
        trackMuonsTimeDirection->Fill(1);
        trackMuonsTimeInOutPos->Fill((*myMuons)[i].time().timeAtIpInOut);
      }
      else if ((*myMuons)[i].time().direction() < 0)
      {
        trackMuonsTimeDirection->Fill(-1);
        trackMuonsTimeInOutNeg->Fill((*myMuons)[i].time().timeAtIpInOut);
      }
      else if ((*myMuons)[i].time().direction() == 0)
      {
        trackMuonsTimeDirection->Fill(0);
        trackMuonsTimeInOutUndef->Fill((*myMuons)[i].time().timeAtIpInOut);
      }
      else
        std::cout << "no direction estimation for Tracker muon" << std::endl;
    }//end traker muon

  }//end muon loop
}//end analyze

// ------------ method called once each job just before starting event loop  ------------
void AnaTime::beginJob()
{
  edm::Service < TFileService > fs;

  allMuonsTimeInOut = fs->make < TH1F > ("allMuonsTimeInOut", "allMuonsTimeInOut", 20000, -100, 100);
  allMuonsTimeOutIn = fs->make < TH1F > ("allMuonsTimeOutIn", "allMuonsTimeOutIn", 20000, -100, 100);
  allMuonsTimeDirection = fs->make < TH1F > ("allMuonsTimeDirection", "allMuonsTimeDirection", 5, -2.5, 2.5);
  allMuonsTimeDirectionValid = fs->make < TH1F > ("allMuonsTimeDirectionValid", "allMuonsTimeDirectionValid", 5, -2.5, 2.5);
  allMuonsTimeDirectionNoValid = fs->make < TH1F > ("allMuonsTimeDirectionNoValid", "allMuonsTimeDirectionNoValid", 5, -2.5, 2.5);
  allMuonsTimeInOutUndef = fs->make < TH1F > ("allMuonsTimeInOutUndef", "allMuonsTimeInOutUndef", 20000, -100, 100);
  allMuonsTimeOutInUndef = fs->make < TH1F > ("allMuonsTimeOutInUndef", "allMuonsTimeOutInUndef", 20000, -100, 100);
  allMuonsTimeInOutPos = fs->make < TH1F > ("allMuonsTimeInOutPos", "allMuonsTimeInOutPos", 20000, -100, 100);
  allMuonsTimeOutInPos = fs->make < TH1F > ("allMuonsTimeOutInPos", "allMuonsTimeOutInPos", 20000, -100, 100);
  allMuonsTimeInOutPosValid = fs->make < TH1F > ("allMuonsTimeInOutPosValid", "allMuonsTimeInOutPosValid", 20000, -100, 100);
  allMuonsTimeOutInPosValid = fs->make < TH1F > ("allMuonsTimeOutInPosValid", "allMuonsTimeOutInPosValid", 20000, -100, 100);
  allMuonsTimeInOutNeg = fs->make < TH1F > ("allMuonsTimeInOutNeg", "allMuonsTimeInOutNeg", 20000, -100, 100);
  allMuonsTimeOutInNeg = fs->make < TH1F > ("allMuonsTimeOutInNeg", "allMuonsTimeOutInNeg", 20000, -100, 100);

  rpcMuonsTimeDirection = fs->make < TH1F > ("rpcMuonsTimeDirection", "rpcMuonsTimeDirection", 5, -2.5, 2.5);
  rpcMuonsTimeInOut = fs->make < TH1F > ("rpcMuonsTimeInOut", "rpcMuonsTimeInOut", 20000, -100, 100);
  rpcMuonsTimeInOutPos = fs->make < TH1F > ("rpcMuonsTimeInOutPos", "rpcMuonsTimeInOutPos", 20000, -100, 100);
  rpcMuonsTimeInOutNeg = fs->make < TH1F > ("rpcMuonsTimeInOutNeg", "rpcMuonsTimeInOutNeg", 20000, -100, 100);
  rpcMuonsTimeInOutUndef = fs->make < TH1F > ("rpcMuonsTimeInOutUndef", "rpcMuonsTimeInOutUndef", 20000, -100, 100);

  staMuonsTimeDirection = fs->make < TH1F > ("staMuonsTimeDirection", "staMuonsTimeDirection", 5, -2.5, 2.5);
  staMuonsTimeInOut = fs->make < TH1F > ("staMuonsTimeInOut", "staMuonsTimeInOut", 20000, -100, 100);
  staMuonsTimeInOutPos = fs->make < TH1F > ("staMuonsTimeInOutPos", "staMuonsTimeInOutPos", 20000, -100, 100);
  staMuonsTimeInOutNeg = fs->make < TH1F > ("staMuonsTimeInOutNeg", "staMuonsTimeInOutNeg", 20000, -100, 100);
  staMuonsTimeInOutUndef = fs->make < TH1F > ("staMuonsTimeInOutUndef", "staMuonsTimeInOutUndef", 20000, -100, 100);

  globMuonsTimeDirection = fs->make < TH1F > ("globMuonsTimeDirection", "globMuonsTimeDirection", 5, -2.5, 2.5);
  globMuonsTimeInOut = fs->make < TH1F > ("globMuonsTimeInOut", "globMuonsTimeInOut", 20000, -100, 100);
  globMuonsTimeInOutPos = fs->make < TH1F > ("globMuonsTimeInOutPos", "globMuonsTimeInOutPos", 20000, -100, 100);
  globMuonsTimeInOutNeg = fs->make < TH1F > ("globMuonsTimeInOutNeg", "globMuonsTimeInOutNeg", 20000, -100, 100);
  globMuonsTimeInOutUndef = fs->make < TH1F > ("globMuonsTimeInOutUndef", "globMuonsTimeInOutUndef", 20000, -100, 100);

  trackMuonsTimeDirection = fs->make < TH1F > ("trackMuonsTimeDirection", "trackMuonsTimeDirection", 5, -2.5, 2.5);
  trackMuonsTimeInOutPos = fs->make < TH1F > ("trackMuonsTimeInOutPos", "trackMuonsTimeInOutPos", 20000, -100, 100);
  trackMuonsTimeInOutNeg = fs->make < TH1F > ("trackMuonsTimeInOutNeg", "trackMuonsTimeInOutNeg", 20000, -100, 100);
  trackMuonsTimeInOutUndef = fs->make < TH1F > ("trackMuonsTimeInOutUndef", "trackMuonsTimeInOutUndef", 20000, -100, 100);

  allMuTimeInOutPosVsPt = fs->make<TH2F>("allMuTimeInOutPosVsPt", "allMuTimeInOutPosVsPt", 2000, -100, 100, 3000, 0, 150);
  allMuTimeInOutPosVsEta = fs->make<TH2F>("allMuTimeInOutPosVsEta", "allMuTimeInOutPosVsEta", 2000, -100, 100, 700, -3.5, 3.5);
  allMuTimeInOutPosVsPhi = fs->make<TH2F>("allMuTimeInOutPosVsPhi", "allMuTimeInOutPosVsPhi", 2000, -100, 100, 1260, -6.3, 6.3);

  allMuTimeInOutNegVsPt = fs->make<TH2F>("allMuTimeInOutNegVsPt", "allMuTimeInOutNegVsPt", 2000, -100, 100, 3000, 0, 150);
  allMuTimeInOutNegVsEta = fs->make<TH2F>("allMuTimeInOutNegVsEta", "allMuTimeInOutNegVsEta", 2000, -100, 100, 700, -3.5, 3.5);
  allMuTimeInOutNegVsPhi = fs->make<TH2F>("allMuTimeInOutNegVsPhi", "allMuTimeInOutNegVsPhi", 2000, -100, 100, 1260, -6.3, 6.3);

  allMuTimeInOutUndefVsPt = fs->make<TH2F>("allMuTimeInOutUndefVsPt", "allMuTimeInOutUndefVsPt", 2000, -100, 100, 3000, 0, 150);
  allMuTimeInOutUndefVsEta = fs->make<TH2F>("allMuTimeInOutUndefVsEta", "allMuTimeInOutUndefVsEta", 2000, -100, 100, 700, -3.5, 3.5);
  allMuTimeInOutUndefVsPhi = fs->make<TH2F>("allMuTimeInOutUndefVsPhi", "allMuTimeInOutUndefVsPhi", 2000, -100, 100, 1260, -6.3, 6.3);

  staMuonsGemValHitEndcapPos = fs->make < TH1F > ("staMuonsGemValHitEndcapPos", "staMuonsGemValHitEndcapPos", 50, 0, 50);
  staMuonsMuonValHitEndcapPos = fs->make < TH1F > ("staMuonsMuonValHitEndcapPos", "staMuonsMuonValHitEndcapPos", 50, 0, 50);
  staMuonsRPCValHitEndcapPos = fs->make < TH1F > ("staMuonsRPCValHitEndcapPos", "staMuonsRPCValHitEndcapPos", 50, 0, 50);
  staMuonsCSCValHitEndcapPos = fs->make < TH1F > ("staMuonsCSCValHitEndcapPos", "staMuonsCSCValHitEndcapPos", 50, 0, 50);

  staMuonsGemValHitEndcapNeg = fs->make < TH1F > ("staMuonsGemValHitEndcapNeg", "staMuonsGemValHitEndcapNeg", 50, 0, 50);
  staMuonsMuonValHitEndcapNeg = fs->make < TH1F > ("staMuonsMuonValHitEndcapNeg", "staMuonsMuonValHitEndcapNeg", 50, 0, 50);
  staMuonsRPCValHitEndcapNeg = fs->make < TH1F > ("staMuonsRPCValHitEndcapNeg", "staMuonsRPCValHitEndcapNeg", 50, 0, 50);
  staMuonsCSCValHitEndcapNeg = fs->make < TH1F > ("staMuonsCSCValHitEndcapNeg", "staMuonsCSCValHitEndcapNeg", 50, 0, 50);

  staMuonsGemValHitEndcapUndef = fs->make < TH1F > ("staMuonsGemValHitEndcapUndef", "staMuonsGemValHitEndcapUndef", 50, 0, 50);
  staMuonsMuonValHitEndcapUndef = fs->make < TH1F > ("staMuonsMuonValHitEndcapUndef", "staMuonsMuonValHitEndcapUndef", 50, 0, 50);
  staMuonsRPCValHitEndcapUndef = fs->make < TH1F > ("staMuonsRPCValHitEndcapUndef", "staMuonsRPCValHitEndcapUndef", 50, 0, 50);
  staMuonsCSCValHitEndcapUndef = fs->make < TH1F > ("staMuonsCSCValHitEndcapUndef", "staMuonsCSCValHitEndcapUndef", 50, 0, 50);

  gemValidHitvsTimeInOutPos= fs->make<TH2F>("gemValidHitvsTimeInOutPos", "gemValidHitvsTimeInOutPos", 2000, -100, 100, 50, 0, 50);
  rpcValidHitvsTimeInOutPos= fs->make<TH2F>("rpcValidHitvsTimeInOutPos", "rpcValidHitvsTimeInOutPos", 2000, -100, 100, 50, 0, 50);
  cscValidHitvsTimeInOutPos= fs->make<TH2F>("cscValidHitvsTimeInOutPos", "cscValidHitvsTimeInOutPos", 2000, -100, 100, 50, 0, 50);

  gemValidHitvsTimeInOutNeg= fs->make<TH2F>("gemValidHitvsTimeInOutNeg", "gemValidHitvsTimeInOutNeg", 2000, -100, 100, 50, 0, 50);
  rpcValidHitvsTimeInOutNeg= fs->make<TH2F>("rpcValidHitvsTimeInOutNeg", "rpcValidHitvsTimeInOutNeg", 2000, -100, 100, 50, 0, 50);
  cscValidHitvsTimeInOutNeg= fs->make<TH2F>("cscValidHitvsTimeInOutNeg", "cscValidHitvsTimeInOutNeg", 2000, -100, 100, 50, 0, 50);

  gemValidHitvsTimeInOutUndef= fs->make<TH2F>("gemValidHitvsTimeInOutUndef", "gemValidHitvsTimeInOutUndef", 2000, -100, 100, 50, 0, 50);
  rpcValidHitvsTimeInOutUndef= fs->make<TH2F>("rpcValidHitvsTimeInOutUndef", "rpcValidHitvsTimeInOutUndef", 2000, -100, 100, 50, 0, 50);
  cscValidHitvsTimeInOutUndef= fs->make<TH2F>("cscValidHitvsTimeInOutUndef", "cscValidHitvsTimeInOutUndef", 2000, -100, 100, 50, 0, 50);

  gemcscValidHitvsTimeInOutPos = fs->make < TH1F > ("gemcscValidHitvsTimeInOutPos", "gemcscValidHitvsTimeInOutPos", 50, 0, 50);
  gemrpcValidHitvsTimeInOutPos = fs->make < TH1F > ("gemrpcValidHitvsTimeInOutPos", "gemrpcValidHitvsTimeInOutPos", 50, 0, 50);
  cscrpcValidHitvsTimeInOutPos = fs->make < TH1F > ("cscrpcValidHitvsTimeInOutPos", "cscrpcValidHitvsTimeInOutPos", 50, 0, 50);

  gemcscValidHitvsTimeInOutNeg = fs->make < TH1F > ("gemcscValidHitvsTimeInOutNeg", "gemcscValidHitvsTimeInOutNeg", 50, 0, 50);
  gemrpcValidHitvsTimeInOutNeg = fs->make < TH1F > ("gemrpcValidHitvsTimeInOutNeg", "gemrpcValidHitvsTimeInOutNeg", 50, 0, 50);
  cscrpcValidHitvsTimeInOutNeg = fs->make < TH1F > ("cscrpcValidHitvsTimeInOutNeg", "cscrpcValidHitvsTimeInOutNeg", 50, 0, 50);

  gemcscValidHitvsTimeInOutUndef = fs->make < TH1F > ("gemcscValidHitvsTimeInOutUndef", "gemcscValidHitvsTimeInOutUndef", 50, 0, 50);
  gemrpcValidHitvsTimeInOutUndef = fs->make < TH1F > ("gemrpcValidHitvsTimeInOutUndef", "gemrpcValidHitvsTimeInOutUndef", 50, 0, 50);
  cscrpcValidHitvsTimeInOutUndef = fs->make < TH1F > ("cscrpcValidHitvsTimeInOutUndef", "cscrpcValidHitvsTimeInOutUndef", 50, 0, 50);

}

// ------------ method called once each job just after ending the event loop  ------------
void AnaTime::endJob()
{
}

// ------------ method called when starting to processes a run  ------------
/*
 void
 AnaTime::beginRun(edm::Run const&, edm::EventSetup const&)
 {
 }
 */

// ------------ method called when ending the processing of a run  ------------
/*
 void
 AnaTime::endRun(edm::Run const&, edm::EventSetup const&)
 {
 }
 */

// ------------ method called when starting to processes a luminosity block  ------------
/*
 void
 AnaTime::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
 {
 }
 */

// ------------ method called when ending the processing of a luminosity block  ------------
/*
 void
 AnaTime::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
 {
 }
 */

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void AnaTime::fillDescriptions(edm::ConfigurationDescriptions& descriptions)
{
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE (AnaTime);

