// -*- C++ -*-
//
// Package: MuonMCClassifAndAna
// Class: MuonMCClassifAndAna
//
/**\class MuonMCClassifAndAna MuonMCClassifAndAna.cc MuonAnalysis/MuonAssociators/src/MuonMCClassifAndAna.cc
 CLASSIFICATION: For each RECO Muon, match to SIM particle, and then:
 - If the SIM is not a Muon, label as Punchthrough (1)
 - If the SIM is a Muon, then look at it's provenance.
 A) the SIM muon is also a GEN muon, whose parent is NOT A HADRON AND NOT A TAU
 -> classify as "primary" (4).
 B) the SIM muon is also a GEN muon, whose parent is HEAVY FLAVOURED HADRON OR A TAU
 -> classify as "heavy flavour" (3)
 C) classify as "light flavour/decay" (2)
 In any case, if the TP is not preferentially matched back to the same RECO muon,
 label as Ghost (flip the classification)
 FLAVOUR:
 - for non-muons: 0
 - for primary muons: 13
 - for non primary muons: flavour of the mother: abs(pdgId) of heaviest quark, or 15 for tau
 */
//
//
// system include files
#include <memory>
#include <set>
// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/Common/interface/View.h"
#include "DataFormats/Common/interface/ValueMap.h"
#include "DataFormats/Common/interface/Association.h"
#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "SimMuon/MCTruth/interface/MuonAssociatorByHits.h"
#include "SimTracker/Records/interface/TrackAssociatorRecord.h"
#include <SimDataFormats/TrackingAnalysis/interface/TrackingVertex.h>
#include "CommonTools/Utils/interface/StringCutObjectSelector.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/MuonReco/interface/MuonSelectors.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "TH2F.h"
#include "TH1F.h"
//
// class decleration
class MuonMCClassifAndAna: public edm::EDAnalyzer
{
public:
  explicit MuonMCClassifAndAna(const edm::ParameterSet&);
  bool isTight(const edm::Event& iEvent, reco::Muon myMuon);
  bool isSoft(reco::Muon myMuon, reco::VertexCollection::const_iterator myPVit, const reco::VertexCollection myVertices);
  ~MuonMCClassifAndAna();
  void myClassification(size_t myNmu, edm::Handle<edm::View<reco::Muon> > myMuons_handle,
      edm::RefToBaseVector<reco::Muon> selMuons, MuonAssociatorByHits::MuonToSimCollection myRecSimColl,
      MuonAssociatorByHits::SimToMuonCollection mySimRecColl, std::vector<int> &myClassif, std::vector<int> &myExt,
      std::vector<int> &myHitsPdgId, std::vector<int> &myMomPdgId, std::vector<int> &myGmomPdgId,
      std::vector<int> &myMomStatus, std::vector<int> &myFlav, std::vector<int> &myMomFlav,
      std::vector<int> &myGmomFlav, std::vector<int> &myHmomFlav, std::vector<int> &myTpId,
      std::vector<float> &myProdRho, std::vector<float> &myProdZ, std::vector<float> &myMomRho,
      std::vector<float> &myMomZ, std::vector<float> &myTpAssoQuality,
      std::auto_ptr<reco::GenParticleCollection> &secondaries, std::vector<int> &muToPrimary,
      std::vector<int> &muToSecondary, edm::Handle<reco::GenParticleCollection> &genParticles, int &binp, int &binl,
      int &binh, int &binpr, int &binn, int &bingst, TH1F *histoPt_p, TH1F *histoPt_l, TH1F *histoPt_h,
      TH1F *histoPt_pr, TH1F *histoPt_n, TH1F *histoPt_gst, TH1F *histoEta_p, TH1F *histoEta_l, TH1F *histoEta_h,
      TH1F *histoEta_pr, TH1F *histoEta_n, TH1F *histoEta_gst, TH1F *histoPhi_p, TH1F *histoPhi_l, TH1F *histoPhi_h,
      TH1F *histoPhi_pr, TH1F *histoPhi_n, TH1F *histoPhi_gst, int myCase);
  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
private:
  virtual void beginJob() override;
  virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
  virtual void endJob() override;

  bool debug;
  int glb_pch, glb_l, glb_h, glb_prm, glb_n, glb_gst;
  int sta_pch, sta_l, sta_h, sta_prm, sta_n, sta_gst;
  int tight_pch, tight_l, tight_h, tight_prm, tight_n, tight_gst;
  int loose_pch, loose_l, loose_h, loose_prm, loose_n, loose_gst;

  TH1F *allMuonsTimeInOut, *allMuonsTimeOutIn, *allMuonsTimeDirection, *allMuonsTimeInOutUndef, *allMuonsTimeOutInUndef;
  TH1F *globMuonsTimeInOut, *globMuonsTimeOutIn;
  TH1F *staMuonsTimeInOut, *staMuonsTimeOutIn;

  TH1F *N_Muons;
  TH1F *N_Muons_norm;
  TH1F *totalevents_withMuons;
  TH1F *numb_MuPerEvent;
  TH1F *numb_PV;
  TH1F *numb_SimPV;
  TH1F *Pt_TrakingParticle;
  TH1F *PtMuons_TrakingParticle;

  TH1F *allMuonsPt, *allMuonsEta, *allMuonsPhi;
  TH1F *GlobalMuonsPt, *GlobalMuonsEta, *GlobalMuonsPhi;
  TH1F *StaMuonsPt, *StaMuonsEta, *StaMuonsPhi;
  TH1F *TightMuonsPt, *TightMuonsEta, *TightMuonsPhi;
  TH1F *LooseMuonsPt, *LooseMuonsEta, *LooseMuonsPhi;

//global
  TH1F *muPt_Glb_punch, *muPt_Glb_lightflv, *muPt_Glb_heavyflv, *muPt_Glb_primary, *muPt_Glb_noise, *muPt_Glb_ghost;
  TH1F *muEta_Glb_punch, *muEta_Glb_lightflv, *muEta_Glb_heavyflv, *muEta_Glb_primary, *muEta_Glb_noise, *muEta_Glb_ghost;
  TH1F *muPhi_Glb_punch, *muPhi_Glb_lightflv, *muPhi_Glb_heavyflv, *muPhi_Glb_primary, *muPhi_Glb_noise, *muPhi_Glb_ghost;
//sta
  TH1F *muPt_Sta_punch, *muPt_Sta_lightflv, *muPt_Sta_heavyflv, *muPt_Sta_primary, *muPt_Sta_noise, *muPt_Sta_ghost;
  TH1F *muEta_Sta_punch, *muEta_Sta_lightflv, *muEta_Sta_heavyflv, *muEta_Sta_primary, *muEta_Sta_noise, *muEta_Sta_ghost;
  TH1F *muPhi_Sta_punch, *muPhi_Sta_lightflv, *muPhi_Sta_heavyflv, *muPhi_Sta_primary, *muPhi_Sta_noise, *muPhi_Sta_ghost;
//tight
  TH1F *muPt_Tight_punch, *muPt_Tight_lightflv, *muPt_Tight_heavyflv, *muPt_Tight_primary, *muPt_Tight_noise, *muPt_Tight_ghost;
  TH1F *muEta_Tight_punch, *muEta_Tight_lightflv, *muEta_Tight_heavyflv, *muEta_Tight_primary, *muEta_Tight_noise, *muEta_Tight_ghost;
  TH1F *muPhi_Tight_punch, *muPhi_Tight_lightflv, *muPhi_Tight_heavyflv, *muPhi_Tight_primary, *muPhi_Tight_noise, *muPhi_Tight_ghost;
//loose
  TH1F *muPt_Loose_punch, *muPt_Loose_lightflv, *muPt_Loose_heavyflv, *muPt_Loose_primary, *muPt_Loose_noise, *muPt_Loose_ghost;
  TH1F *muEta_Loose_punch, *muEta_Loose_lightflv, *muEta_Loose_heavyflv, *muEta_Loose_primary, *muEta_Loose_noise, *muEta_Loose_ghost;
  TH1F *muPhi_Loose_punch, *muPhi_Loose_lightflv, *muPhi_Loose_heavyflv, *muPhi_Loose_primary, *muPhi_Loose_noise, *muPhi_Loose_ghost;

/// The RECO objects
  edm::InputTag trackingParticles_;
  edm::InputTag muons_;
  bool linkToGenParticles_;
  edm::InputTag genParticles_;
  std::string associatorLabel_;
  double decayRho_, decayAbsZ_;

/// Track to use
  int flavour(int pdgId) const;
  double muonPtCut_;
  double muonMinEtaCut_;
  double muonMaxEtaCut_;
  double isoCut_;
  edm::InputTag vxtTag;
//Get Mother of the tracking particle
  TrackingParticleRef getTpMother(TrackingParticleRef tp)
  {
    if (tp.isNonnull() && tp->parentVertex().isNonnull() && !tp->parentVertex()->sourceTracks().empty())
    {
      return tp->parentVertex()->sourceTracks()[0];
    }
    else
    {
      return TrackingParticleRef();
    }
  }
/// Convert TrackingParticle into GenParticle, save into output collection,
/// if mother is primary set reference to it,
/// return index in output collection
  int convertAndPush(const TrackingParticle &tp, reco::GenParticleCollection &out, const TrackingParticleRef &momRef,
      const edm::Handle<reco::GenParticleCollection> & genParticles) const;
};

bool MuonMCClassifAndAna::isTight(const edm::Event& iEvent, reco::Muon myMuon)
{
  bool results = false;
  if (myMuon.isGlobalMuon() && myMuon.isPFMuon())
  {
    if (myMuon.isIsolationValid() && (myMuon.isolationR03().sumPt) / myMuon.muonBestTrack()->pt() < isoCut_)
// if (myMuon.isIsolationValid() && (myMuon.isolationR03().sumPt) / myMuon.pt() < isoCut_)
    {
      reco::TrackRef trackRefGl = myMuon.globalTrack();
      reco::TrackRef trackRefIn = myMuon.innerTrack();
      reco::TrackRef trackRefBest = myMuon.muonBestTrack();
      if (trackRefGl.isNonnull() && trackRefIn.isNonnull() && trackRefBest.isNonnull())
      {
        edm::Handle < reco::VertexCollection > vertexHandle;
        iEvent.getByLabel(vxtTag, vertexHandle);
        const reco::VertexCollection* vertices = vertexHandle.product();
        if (myMuon.numberOfMatchedStations() > 1)
        {
          if (trackRefGl->hitPattern().numberOfValidMuonHits() > 0)
          {
            if (trackRefIn->hitPattern().pixelLayersWithMeasurement(3, 2) > 0)
            {
              if (trackRefIn->hitPattern().trackerLayersWithMeasurement() > 5)
              {
                if (myMuon.globalTrack()->normalizedChi2() < 10.)
// if (myMuon.track()->normalizedChi2() < 10.)
                {
                  if (vertices->size() != 0 && fabs(myMuon.muonBestTrack()->dxy((*vertices)[0].position())) < 0.2 && fabs(myMuon.muonBestTrack()->dz((*vertices)[0].position())) < 0.5)
                    results = true;
                }
              }
            }
          }
        }
      }
    }
  }
  return results;
}

bool MuonMCClassifAndAna::isSoft(reco::Muon myMuon, reco::VertexCollection::const_iterator myPVit,
    const reco::VertexCollection myVertices)
{
  bool results = false;
// if (myMuon.muonBestTrack().isNonnull() && myMuon.innerTrack().isNonnull())
  if (myMuon.innerTrack().isNonnull())
  {
    bool isGood = muon::isGoodMuon(myMuon, muon::TMOneStationTight);
    if (isGood)
    {
      bool trkLayMeas = myMuon.muonBestTrack()->hitPattern().trackerLayersWithMeasurement() > 5;
// bool trkLayMeas = myMuon.innerTrack()->hitPattern().trackerLayersWithMeasurement() > 5;
      bool pxlLayMeas = myMuon.innerTrack()->hitPattern().pixelLayersWithMeasurement() > 0;
      bool quality = myMuon.innerTrack()->quality(reco::Track::highPurity);
      if (trkLayMeas && pxlLayMeas && quality)
      {
        reco::Vertex pv = myVertices.front();
        if ((pv.isValid()) && !(pv.isFake())
            && (fabs(pv.position().z()) <= 24 && fabs(pv.position().rho()) <= 2 && pv.ndof() > 4))
        {
          if (fabs(myMuon.innerTrack()->dxy(pv.position())) < 0.3 && fabs(myMuon.innerTrack()->dz(pv.position())) < 20)
            results = true;
        }
      }
    }
  }
  return results;
}

MuonMCClassifAndAna::MuonMCClassifAndAna(const edm::ParameterSet &iConfig) :
    trackingParticles_(iConfig.getParameter < edm::InputTag > ("simLabel")) //
        , muons_(iConfig.getParameter < edm::InputTag > ("muonLabel")) //
        , linkToGenParticles_(iConfig.getParameter<bool>("linkToGenParticles")) //
        , genParticles_(linkToGenParticles_ ? iConfig.getParameter < edm::InputTag > ("genParticles") : edm::InputTag("NONE")) //
        , associatorLabel_(iConfig.getParameter < std::string > ("muAssocLabel")) //
        , decayRho_(iConfig.getParameter<double>("decayRho")) //
        , decayAbsZ_(iConfig.getParameter<double>("decayAbsZ")) //
        , muonPtCut_(iConfig.getParameter<double>("muonPtCut")) //
        , muonMinEtaCut_(iConfig.getParameter<double>("muonMinEtaCut")) //
        , muonMaxEtaCut_(iConfig.getParameter<double>("muonMaxEtaCut")) //
        , isoCut_(iConfig.getParameter<double>("isoCut")) //
        , vxtTag(iConfig.getParameter < edm::InputTag > ("vxtTag")) //
{
  debug = false;

  glb_pch = 4;
  glb_l = 5;
  glb_h = 6;
  glb_prm = 7;
  glb_n = 8;
  glb_gst = 9;

  sta_pch = 20;
  sta_l = 21;
  sta_h = 22;
  sta_prm = 23;
  sta_n = 24;
  sta_gst = 25;

  tight_pch = 36;
  tight_l = 37;
  tight_h = 38;
  tight_prm = 39;
  tight_n = 40;
  tight_gst = 41;

  loose_pch = 52;
  loose_l = 53;
  loose_h = 54;
  loose_prm = 55;
  loose_n = 56;
  loose_gst = 57;
}
MuonMCClassifAndAna::~MuonMCClassifAndAna()
{
}

void MuonMCClassifAndAna::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
 // std::cout << "event number\t" << (iEvent.id()).event() << "\tlumi number\t" << (iEvent.id()).luminosityBlock() << "\trun\t" << (iEvent.id()).run() << std::endl;

  using namespace edm;
  using namespace std;
  using namespace reco;
  if (debug)
  {
    std::cout << "in MuonMCClassifAndAna !" << std::endl;
  }
//getting primary vertices
  edm::Handle < reco::VertexCollection > pvHandle;
  iEvent.getByLabel("offlinePrimaryVertices", pvHandle);
  int numberOfVertices = pvHandle->size();
  numb_PV->Fill(numberOfVertices);
//  const reco::VertexCollection & vertices = *pvHandle.product();
  reco::VertexCollection::const_iterator myPV;

  //getting muon collection
  edm::Handle < edm::View<reco::Muon> > myMuons;
  iEvent.getByLabel(muons_, myMuons);
  size_t nmu = myMuons->size();
  numb_MuPerEvent->Fill(nmu);
  if (nmu > 0)
  {
    N_Muons->Fill(60);
    N_Muons_norm->Fill(60);
    N_Muons->Fill(62, numberOfVertices);
    N_Muons_norm->Fill(62, numberOfVertices);
  }

  edm::Handle < TrackingParticleCollection > trackingParticles;
  iEvent.getByLabel(trackingParticles_, trackingParticles);

  const TrackingParticleCollection& trackingParticleCollection = *(trackingParticles.product());
  for (TrackingParticleCollection::size_type i = 0; i < trackingParticleCollection.size(); ++i)
  {
    TrackingParticleRef tp(trackingParticles, i);
    Pt_TrakingParticle->Fill(tp->pt());
    if (abs(tp->pdgId()) == 13)
    {
      PtMuons_TrakingParticle->Fill(tp->pt());
    }
  }

  edm::Handle < reco::GenParticleCollection > genParticlesforGlb;
  edm::Handle < reco::GenParticleCollection > genParticlesforSta;
  edm::Handle < reco::GenParticleCollection > genParticlesforTight;
  edm::Handle < reco::GenParticleCollection > genParticlesforLoose;

  if (linkToGenParticles_)
  {
    iEvent.getByLabel(genParticles_, genParticlesforGlb);
    iEvent.getByLabel(genParticles_, genParticlesforSta);
    iEvent.getByLabel(genParticles_, genParticlesforTight);
    iEvent.getByLabel(genParticles_, genParticlesforLoose);
  }

  edm::ESHandle < TrackAssociatorBase > associatorBase;
  iSetup.get<TrackAssociatorRecord>().get(associatorLabel_, associatorBase);
  const MuonAssociatorByHits * assoByHits = dynamic_cast<const MuonAssociatorByHits *>(associatorBase.product());
  if (assoByHits == 0)
    throw cms::Exception("Configuration") << "The Track Associator with label '" << associatorLabel_
        << "' is not a MuonAssociatorByHits.\n";
  MuonAssociatorByHits::MuonToSimCollection recSimColl;
  MuonAssociatorByHits::SimToMuonCollection simRecColl;
//  edm::RefToBaseVector < reco::Muon > selAllMuons;
  edm::RefToBaseVector < reco::Muon > selGlbMuons;
  edm::RefToBaseVector < reco::Muon > selStaMuons;
  edm::RefToBaseVector < reco::Muon > selTightMuons;
  edm::RefToBaseVector < reco::Muon > selLooseMuons;

  for (size_t i = 0, n = myMuons->size(); i < n; ++i)
  {
    allMuonsTimeInOut->Fill((*myMuons)[i].time().timeAtIpInOut);
    allMuonsTimeOutIn->Fill((*myMuons)[i].time().timeAtIpOutIn);

    if ((*myMuons)[i].time().direction() > 0)
      allMuonsTimeDirection->Fill(1);
    else if ((*myMuons)[i].time().direction() < 0)
      allMuonsTimeDirection->Fill(-1);
    else if ((*myMuons)[i].time().direction() == 0)
    {
      allMuonsTimeDirection->Fill(0);
      allMuonsTimeInOutUndef->Fill((*myMuons)[i].time().timeAtIpInOut);
      allMuonsTimeOutInUndef->Fill((*myMuons)[i].time().timeAtIpOutIn);

    }
    else
      std::cout << "no direction estimation for muon" << std::endl;

    N_Muons->Fill(64); //all muons
    N_Muons_norm->Fill(64); //all muons

//        if ( ! ((*myMuons)[i].time().direction() > 0) )
//    if ( ! ((*myMuons)[i].isTimeValid()) )
//      continue;

    edm::RefToBase < reco::Muon > rmu = myMuons->refAt(i);
    if ((*myMuons)[i].pt() > muonPtCut_ && fabs((*myMuons)[i].eta()) >= muonMinEtaCut_ && fabs((*myMuons)[i].eta()) <= muonMaxEtaCut_)
    {
      N_Muons->Fill(1); //all selected muons
      N_Muons_norm->Fill(1); //all selected muons
      allMuonsEta->Fill((*myMuons)[i].eta());
      allMuonsPt->Fill((*myMuons)[i].pt());
      allMuonsPhi->Fill((*myMuons)[i].phi());

//      selAllMuons.push_back(rmu);
//      if (debug) std::cout << "event: run\t" << (iEvent.id()).run() << "\tevent #\t" << (iEvent.id()).event() << std::endl; //
//      if (debug) std::cout << "I am Selected muon!" << std::endl;
    }

//global muons
    if ((*myMuons)[i].isGlobalMuon())
    {
      globMuonsTimeInOut->Fill((*myMuons)[i].time().timeAtIpInOut);
      globMuonsTimeOutIn->Fill((*myMuons)[i].time().timeAtIpOutIn);

      if ((*myMuons)[i].globalTrack().isNonnull())
      {
        reco::TrackRef glbtrackref = (*myMuons)[i].globalTrack();

        if (glbtrackref->pt() > muonPtCut_ && fabs(glbtrackref->eta()) >= muonMinEtaCut_ && fabs(glbtrackref->eta()) <= muonMaxEtaCut_)
//            && fabs((*myMuons)[i].time().timeAtIpInOut) < 12.5)
//            && glbtrackref->hitPattern().numberOfValidMuonHits() > 0)
        {
          selGlbMuons.push_back(rmu);
          N_Muons->Fill(3);
          N_Muons_norm->Fill(3);
          GlobalMuonsEta->Fill(glbtrackref->eta());
          GlobalMuonsPt->Fill(glbtrackref->pt());
          GlobalMuonsPhi->Fill(glbtrackref->phi());
          if (debug) std::cout << "I am Global muon!" << std::endl; //
        }
      }
    }

//standalone
    if ((*myMuons)[i].isStandAloneMuon())
    {
      if ((*myMuons)[i].outerTrack().isNonnull())
      {
        reco::TrackRef statrackref = (*myMuons)[i].outerTrack();

        staMuonsTimeInOut->Fill((*myMuons)[i].time().timeAtIpInOut);
        staMuonsTimeOutIn->Fill((*myMuons)[i].time().timeAtIpOutIn);

        if (statrackref->pt() > muonPtCut_ && fabs(statrackref->eta()) >= muonMinEtaCut_ && fabs(statrackref->eta()) <= muonMaxEtaCut_)
        {
//          if ((*myMuons)[i].time().timeAtIpInOut == 0 && statrackref->hitPattern().numberOfValidMuonHits() > 1)
//          if ( ((*myMuons)[i].time().timeAtIpInOut) < 12.5 )
          {
            selStaMuons.push_back(rmu);
            N_Muons->Fill(19);
            N_Muons_norm->Fill(19);
            StaMuonsEta->Fill(statrackref->eta());
            StaMuonsPt->Fill(statrackref->pt());
            StaMuonsPhi->Fill(statrackref->phi());
            if (debug)
              std::cout << "I am Standalone muon!" << std::endl; //
          } //end muon time and hit number cuts
        } //end kinematikal cuts
      } //end has non null reference
    } //end if standalone

//tight muon
    bool tight = isTight(iEvent, (*myMuons)[i]);
    if (tight)
    {
//      if ((*myMuons)[i].outerTrack().isNonnull())
//      {
//        reco::TrackRef statrackref = (*myMuons)[i].outerTrack();
        if ((*myMuons)[i].pt() > muonPtCut_ && fabs((*myMuons)[i].eta()) >= muonMinEtaCut_ && fabs((*myMuons)[i].eta()) <= muonMaxEtaCut_)
//            && fabs((*myMuons)[i].time().timeAtIpInOut) < 12.5)
//            && statrackref->hitPattern().numberOfValidMuonHits() > 0)
        {
          N_Muons->Fill(35);
          N_Muons_norm->Fill(35);
          selTightMuons.push_back(rmu);
          TightMuonsEta->Fill((*myMuons)[i].eta());
          TightMuonsPt->Fill((*myMuons)[i].pt());
          TightMuonsPhi->Fill((*myMuons)[i].phi());
           if (debug)
            std::cout << "I am Tight muon!" << std::endl;  //
        }
//      }
    }  //end tight

    if (muon::isLooseMuon ((*myMuons)[i]))
    {
//      if ((*myMuons)[i].outerTrack().isNonnull())
//      {
//        reco::TrackRef statrackref = (*myMuons)[i].outerTrack();

        if ((*myMuons)[i].pt() > muonPtCut_ && fabs((*myMuons)[i].eta()) >= muonMinEtaCut_ && fabs((*myMuons)[i].eta()) <= muonMaxEtaCut_)
//m            && fabs((*myMuons)[i].time().timeAtIpInOut) < 25)
//            && statrackref->hitPattern().numberOfValidMuonHits() > 0)
        {
          N_Muons->Fill(51);
          N_Muons_norm->Fill(51);
          selLooseMuons.push_back(rmu);
          LooseMuonsEta->Fill((*myMuons)[i].eta());
          LooseMuonsPt->Fill((*myMuons)[i].pt());
          LooseMuonsPhi->Fill((*myMuons)[i].phi());
          if (debug)
            std::cout << "I am Loose muon!" << std::endl;
        }
//      }
    }  //end loose
  }//end mu handle size loop

//create tracking particle collection for all the muons
  edm::RefVector < TrackingParticleCollection > allTPs;
  for (size_t i = 0, n = trackingParticles->size(); i < n; ++i)
  {
    allTPs.push_back(TrackingParticleRef(trackingParticles, i));
    if (debug) std::cout << "In trackingParticles" << std::endl;
  }

//create reco to sim and sim to reco associations
  MuonAssociatorByHits::MuonToSimCollection recSimColl_glb;
  MuonAssociatorByHits::SimToMuonCollection simRecColl_glb;
  edm::LogVerbatim("MuonMCClassifAndAna") << "\n Global Muon association by global track"; //
  assoByHits->associateMuons(recSimColl_glb, simRecColl_glb, selGlbMuons, MuonAssociatorByHits::OuterTk, allTPs, &iEvent, &iSetup); //

//standalone muon
  MuonAssociatorByHits::MuonToSimCollection recSimColl_sta;
  MuonAssociatorByHits::SimToMuonCollection simRecColl_sta;
  edm::LogVerbatim("MuonMCClassifAndAna") << "\n Standalone Muon association by outer track "; //
  assoByHits->associateMuons(recSimColl_sta, simRecColl_sta, selStaMuons, MuonAssociatorByHits::OuterTk, allTPs, &iEvent, &iSetup); //

  //tight muon asso by global track
  MuonAssociatorByHits::MuonToSimCollection recSimColl_tight;
  MuonAssociatorByHits::SimToMuonCollection simRecColl_tight;
  edm::LogVerbatim("MuonMCClassifAndAna") << "\n Tight Muon association by global track "; //
  assoByHits->associateMuons(recSimColl_tight, simRecColl_tight, selTightMuons, MuonAssociatorByHits::OuterTk, allTPs, &iEvent, &iSetup); //
//  assoByHits->associateMuons(recSimColl_tight, simRecColl_tight, selTightMuons, MuonAssociatorByHits::GlobalTk, allTPs, &iEvent, &iSetup); //

//Loose
  MuonAssociatorByHits::MuonToSimCollection recSimColl_loose;
  MuonAssociatorByHits::SimToMuonCollection simRecColl_loose;
  edm::LogVerbatim("MuonMCClassifAndAna") << "\n Loose Muon association by inner track "; //
  assoByHits->associateMuons(recSimColl_loose, simRecColl_loose, selLooseMuons, MuonAssociatorByHits::OuterTk, allTPs, &iEvent, &iSetup); //

  if (debug) std::cout << "there are " << nmu << " reco::Muons" << std::endl;
  if (debug) std::cout << "=================================" << std::endl;
  edm::LogVerbatim("MuonMCClassifAndAna") << "\n There are " << nmu << " reco::Muons.";

  std::auto_ptr<reco::GenParticleCollection> secondariesforGlb;
  std::auto_ptr<reco::GenParticleCollection> secondariesforSta;
  std::auto_ptr<reco::GenParticleCollection> secondariesforTight;
  std::auto_ptr<reco::GenParticleCollection> secondariesforLoose;

  std::vector<int> muToPrimaryforGlb(nmu, -1), muToSecondaryforGlb(nmu, -1);
  std::vector<int> muToPrimaryforSta(nmu, -1), muToSecondaryforSta(nmu, -1);
  std::vector<int> muToPrimaryforTight(nmu, -1), muToSecondaryforTight(nmu, -1);
  std::vector<int> muToPrimaryforLoose(nmu, -1), muToSecondaryforLoose(nmu, -1);

  if (linkToGenParticles_)
  {
    secondariesforGlb.reset(new reco::GenParticleCollection());
    secondariesforSta.reset(new reco::GenParticleCollection());
    secondariesforTight.reset(new reco::GenParticleCollection());
    secondariesforLoose.reset(new reco::GenParticleCollection());
  }

 // std::cout << "start global muons" << std::endl;
//for Global MUONS
  std::vector<int> classifgl(nmu, 0), extgl(nmu, 0);
  std::vector<int> hitsPdgIdgl(nmu, 0), momPdgIdgl(nmu, 0), gmomPdgIdgl(nmu, 0), momStatusgl(nmu, 0);
  std::vector<int> flavgl(nmu, 0), momFlavgl(nmu, 0), gmomFlavgl(nmu, 0), hmomFlavgl(nmu, 0);
  std::vector<int> tpIdgl(nmu, -1);
  std::vector<float> prodRhogl(nmu, 0.0), prodZgl(nmu, 0.0), momRhogl(nmu, 0.0), momZgl(nmu, 0.0);
  std::vector<float> tpAssoQualitygl(nmu, -1);
  myClassification(nmu, myMuons, selGlbMuons, recSimColl_glb, simRecColl_glb, classifgl, extgl, hitsPdgIdgl, momPdgIdgl,
      gmomPdgIdgl, momStatusgl, flavgl, momFlavgl, gmomFlavgl, hmomFlavgl, tpIdgl, prodRhogl, prodZgl, momRhogl, momZgl,
      tpAssoQualitygl, secondariesforGlb, muToPrimaryforGlb, muToSecondaryforGlb, genParticlesforGlb, glb_pch, glb_l,
      glb_h, glb_prm, glb_n, glb_gst, muPt_Glb_punch, muPt_Glb_lightflv, muPt_Glb_heavyflv, muPt_Glb_primary,
      muPt_Glb_noise, muPt_Glb_ghost, muEta_Glb_punch, muEta_Glb_lightflv, muEta_Glb_heavyflv, muEta_Glb_primary,
      muEta_Glb_noise, muEta_Glb_ghost, muPhi_Glb_punch, muPhi_Glb_lightflv, muPhi_Glb_heavyflv, muPhi_Glb_primary,
      muPhi_Glb_noise, muPhi_Glb_ghost, 1);

 //  std::cout << "start standalone muons" << std::endl;
//for STANDALONE MUONS
  std::vector<int> classifs(nmu, 0), exts(nmu, 0);
  std::vector<int> hitsPdgIds(nmu, 0), momPdgIds(nmu, 0), gmomPdgIds(nmu, 0), momStatuss(nmu, 0);
  std::vector<int> flavs(nmu, 0), momFlavs(nmu, 0), gmomFlavs(nmu, 0), hmomFlavs(nmu, 0);
  std::vector<int> tpIds(nmu, -1);
  std::vector<float> prodRhos(nmu, 0.0), prodZs(nmu, 0.0), momRhos(nmu, 0.0), momZs(nmu, 0.0);
  std::vector<float> tpAssoQualitys(nmu, -1);
  myClassification(nmu, myMuons, selStaMuons, recSimColl_sta, simRecColl_sta, classifs, exts, hitsPdgIds, momPdgIds,
      gmomPdgIds, momStatuss, flavs, momFlavs, gmomFlavs, hmomFlavs, tpIds, prodRhos, prodZs, momRhos, momZs,
      tpAssoQualitys, secondariesforSta, muToPrimaryforSta, muToSecondaryforSta, genParticlesforSta, sta_pch, sta_l,
      sta_h, sta_prm, sta_n, sta_gst, muPt_Sta_punch, muPt_Sta_lightflv, muPt_Sta_heavyflv, muPt_Sta_primary,
      muPt_Sta_noise, muPt_Sta_ghost, muEta_Sta_punch, muEta_Sta_lightflv, muEta_Sta_heavyflv, muEta_Sta_primary,
      muEta_Sta_noise, muEta_Sta_ghost, muPhi_Sta_punch, muPhi_Sta_lightflv, muPhi_Sta_heavyflv, muPhi_Sta_primary,
      muPhi_Sta_noise, muPhi_Sta_ghost, 3);

//  std::cout << "start tight muons" << std::endl;
//for TIGHT MUONS
  std::vector<int> classift(nmu, 0), extt(nmu, 0);
  std::vector<int> hitsPdgIdt(nmu, 0), momPdgIdt(nmu, 0), gmomPdgIdt(nmu, 0), momStatust(nmu, 0);
  std::vector<int> flavt(nmu, 0), momFlavt(nmu, 0), gmomFlavt(nmu, 0), hmomFlavt(nmu, 0);
  std::vector<int> tpIdt(nmu, -1);
  std::vector<float> prodRhot(nmu, 0.0), prodZt(nmu, 0.0), momRhot(nmu, 0.0), momZt(nmu, 0.0);
  std::vector<float> tpAssoQualityt(nmu, -1);
  myClassification(nmu, myMuons, selTightMuons, recSimColl_tight, simRecColl_tight, classift, extt, hitsPdgIdt,
      momPdgIdt, gmomPdgIdt, momStatust, flavt, momFlavt, gmomFlavt, hmomFlavt, tpIdt, prodRhot, prodZt, momRhot, momZt,
      tpAssoQualityt, secondariesforTight, muToPrimaryforTight, muToSecondaryforTight, genParticlesforTight, tight_pch,
      tight_l, tight_h, tight_prm, tight_n, tight_gst, muPt_Tight_punch, muPt_Tight_lightflv, muPt_Tight_heavyflv,
      muPt_Tight_primary, muPt_Tight_noise, muPt_Tight_ghost, muEta_Tight_punch, muEta_Tight_lightflv,
      muEta_Tight_heavyflv, muEta_Tight_primary, muEta_Tight_noise, muEta_Tight_ghost, muPhi_Tight_punch,
      muPhi_Tight_lightflv, muPhi_Tight_heavyflv, muPhi_Tight_primary, muPhi_Tight_noise, muPhi_Tight_ghost, 5);

//  std::cout << "start loose muons" << std::endl;
//for LOOSe MUONS
  std::vector<int> classifls(nmu, 0), extls(nmu, 0);
  std::vector<int> hitsPdgIdls(nmu, 0), momPdgIdls(nmu, 0), gmomPdgIdls(nmu, 0), momStatusls(nmu, 0);
  std::vector<int> flavls(nmu, 0), momFlavls(nmu, 0), gmomFlavls(nmu, 0), hmomFlavls(nmu, 0);
  std::vector<int> tpIdls(nmu, -1);
  std::vector<float> prodRhosl(nmu, 0.0), prodZls(nmu, 0.0), momRhols(nmu, 0.0), momZls(nmu, 0.0);
  std::vector<float> tpAssoQualityls(nmu, -1);
  myClassification(nmu, myMuons, selLooseMuons, recSimColl_loose, simRecColl_loose, classifls, extls, hitsPdgIdls,
      momPdgIdls, gmomPdgIdls, momStatusls, flavs, momFlavls, gmomFlavls, hmomFlavls, tpIdls, prodRhosl, prodZls,
      momRhols, momZls, tpAssoQualityls, secondariesforLoose, muToPrimaryforLoose, muToSecondaryforLoose,
      genParticlesforLoose, loose_pch, loose_l, loose_h, loose_prm, loose_n, loose_gst, muPt_Loose_punch,
      muPt_Loose_lightflv, muPt_Loose_heavyflv, muPt_Loose_primary, muPt_Loose_noise, muPt_Loose_ghost,
      muEta_Loose_punch, muEta_Loose_lightflv, muEta_Loose_heavyflv, muEta_Loose_primary, muEta_Loose_noise,
      muEta_Loose_ghost, muPhi_Loose_punch, muPhi_Loose_lightflv, muPhi_Loose_heavyflv, muPhi_Loose_primary,
      muPhi_Loose_noise, muPhi_Loose_ghost, 7);

} //end Analyzer

void MuonMCClassifAndAna::myClassification(size_t myNmu, edm::Handle<edm::View<reco::Muon> > myMuons_handle,
    edm::RefToBaseVector<reco::Muon> selMuons, MuonAssociatorByHits::MuonToSimCollection myRecSimColl,
    MuonAssociatorByHits::SimToMuonCollection mySimRecColl, std::vector<int> &myClassif, std::vector<int> &myExt,
    std::vector<int> &myHitsPdgId, std::vector<int> &myMomPdgId, std::vector<int> &myGmomPdgId,
    std::vector<int> &myMomStatus, std::vector<int> &myFlav, std::vector<int> &myMomFlav, std::vector<int> &myGmomFlav,
    std::vector<int> &myHmomFlav, std::vector<int> &myTpId, std::vector<float> &myProdRho, std::vector<float> &myProdZ,
    std::vector<float> &myMomRho, std::vector<float> &myMomZ, std::vector<float> &myTpAssoQuality,
    std::auto_ptr<reco::GenParticleCollection> &secondaries, std::vector<int> &muToPrimary,
    std::vector<int> &muToSecondary, edm::Handle<reco::GenParticleCollection> &genParticles, int &binp, int &binl,
    int &binh, int &binpr, int &binn, int &bingst, TH1F *histoPt_p, TH1F *histoPt_l, TH1F *histoPt_h, TH1F *histoPt_pr,
    TH1F *histoPt_n, TH1F *histoPt_gst, TH1F *histoEta_p, TH1F *histoEta_l, TH1F *histoEta_h, TH1F *histoEta_pr,
    TH1F *histoEta_n, TH1F *histoEta_gst, TH1F *histoPhi_p, TH1F *histoPhi_l, TH1F *histoPhi_h, TH1F *histoPhi_pr,
    TH1F *histoPhi_n, TH1F *histoPhi_gst, int myCase)
{
  std::map<TrackingParticleRef, int> tpToSecondaries; // map from tp to (index+1) in output collection
  typedef MuonAssociatorByHits::MuonToSimCollection::const_iterator r2s_it;
  typedef MuonAssociatorByHits::SimToMuonCollection::const_iterator s2r_it;
  for (size_t i = 0; i < myNmu; ++i) //loop over reco::muons
  {
    //rumi
//    double myHMomRho = 0;
//    double myHMomZ = 0;
   //rumi end

    edm::LogVerbatim("MuonMCClassifAndAna") << "\n reco::Muons # " << i;
    edm::RefToBase < reco::Muon > mu = myMuons_handle->refAt(i);
    if (std::find(selMuons.begin(), selMuons.end(), mu) == selMuons.end())
    {
      edm::LogVerbatim("MuonMCClassifAndAna") << "\t muon didn't pass the selection. classified as -99 and skipped";
      myClassif[i] = -99;
      continue;
    }
//rumi    std::cout << "from MyClaccify: muon with pt = " << ((*myMuons_handle)[i]).pt() << std::endl;

    TrackingParticleRef tp;
    edm::RefToBase < reco::Muon > muMatchBack;
    r2s_it match = myRecSimColl.find(mu);
    s2r_it matchback;
    if (match != myRecSimColl.end()) //match reco to sim
    {
      edm::LogVerbatim("MuonMCClassifAndAna") << "\t Reco to Sim matched Ok...";
// match->second is vector, front is first element, first is the ref (second would be the quality)

      tp = match->second.front().first;
      myTpId[i] = tp.isNonnull() ? tp.key() : -1; // we check, even if null refs should not appear here at all;

//rumi
//      std::cout << "myTpId[" << i << "] = " << myTpId[i] << std::endl;

      myTpAssoQuality[i] = match->second.front().second; //quality
      matchback = mySimRecColl.find(tp); //sim to reco match;
      if (matchback != mySimRecColl.end())
      {
        muMatchBack = matchback->second.front().first; //ref kym tr. par.
      }
      else
      {
        edm::LogWarning("MuonMCClassifAndAna") << "\n***WARNING: This I do NOT understand: why no match back? *** \n";
      }
    } //end reco to sim match OK

    if (tp.isNonnull())
    {
      bool isGhost = muMatchBack != mu;
      if (isGhost) edm::LogVerbatim("MuonMCClassifAndAna") << "\t This seems a GHOST ! myClassif[i] will be < 0";
      myHitsPdgId[i] = tp->pdgId();
      myProdRho[i] = tp->vertex().Rho();	//vertex na traking particle
      myProdZ[i] = tp->vertex().Z();
      edm::LogVerbatim("MuonMCClassifAndAna") << "\t TP pdgId = " << myHitsPdgId[i] << ", vertex rho = " << myProdRho[i] << ", z = " << myProdZ[i];
// Try to extract mother and grand mother of this muon. Unfortunately, SIM and GEN histories require diffent code :-(
      if (!(tp->genParticles().empty()))
      {
// Muon is in GEN
        reco::GenParticleRef genp = tp->genParticles()[0];

//rumi
//std::cout << "tp barcode = " << tp->genParticles()[0]->genpartIndex() << std::endl;

        reco::GenParticleRef genMom = genp->numberOfMothers() > 0 ? genp->motherRef() : reco::GenParticleRef();	//majka ili sam si e majka
        if (genMom.isNonnull())
        {
          myMomPdgId[i] = genMom->pdgId();
          //std::cout << "If muon is in GEN then pdg id of genMOM= " << genMom->pdgId() << std::endl;
          myMomStatus[i] = genMom->status();
          myMomRho[i] = genMom->vertex().Rho();		//vertex na majkata
          myMomZ[i] = genMom->vz();
          edm::LogVerbatim("MuonMCClassifAndAna") << "\t Particle pdgId = " << myHitsPdgId[i] << " produced at rho = " << myProdRho[i] << ", z = " << myProdZ[i] << ", has GEN mother pdgId = " << myMomPdgId[i];
          reco::GenParticleRef genGMom = genMom->numberOfMothers() > 0 ? genMom->motherRef() : reco::GenParticleRef();	//baba ili samo majka
          if (genGMom.isNonnull())
          {
            myGmomPdgId[i] = genGMom->pdgId();
            edm::LogVerbatim("MuonMCClassifAndAna") << "\t\t mother prod. vertex rho = " << myMomRho[i] << ", z = " << myMomZ[i] << ", grand-mom pdgId = " << myGmomPdgId[i];
          }
// in this case, we might want to know the heaviest mom flavour
//loop stops when we're no longer looking at hadrons or mesons
          //rumi
          int numbMothers = 0;
// rumi         std::cout << "===========================" << std::endl;
//          std::cout << "for TP with Id " << myHitsPdgId[i] << "  and mother " << myMomPdgId[i] << std::endl;
          //rumi end
          for (reco::GenParticleRef nMom = genMom; nMom.isNonnull() && abs(nMom->pdgId()) >= 100; nMom = nMom->numberOfMothers() > 0 ? nMom->motherRef() : reco::GenParticleRef())
          {
            numbMothers++;
            int myFlav = flavour(nMom->pdgId());
            if (myHmomFlav[i] < myFlav)
              myHmomFlav[i] = myFlav;
              edm::LogVerbatim("MuonMCClassifAndAna") << "\t\t backtracking flavour: mom pdgId = " << nMom->pdgId() << ", flavour = " << myFlav << ", heaviest so far = " << myHmomFlav[i];
//            std::cout << "from Gen: backtracking flavour: mom pdgId = " << nMom->pdgId() << ", flavour = " << myFlav << ", heaviest so far = " << myHmomFlav[i] << std::endl;
              //rumi: vertex of the heaviest mom - do we need of that?
//              myHMomRho = nMom->vertex().Rho();
//              myHMomZ = nMom->vz();
              //if(debug)
// rumi             std::cout << "mother number\t" << numbMothers << "\tand vertex: Z = " << myHMomZ << "\t ,Ro = " << myHMomRho << std::endl;
//              std::cout << "((((((((((((((())))))))))))" << std::endl;
          }
        }
      }
      else
      {
// Muon is in SIM Only
        TrackingParticleRef simMom = getTpMother(tp);
        if (simMom.isNonnull())
        {
          myMomPdgId[i] = simMom->pdgId();
          //std::cout << "If muon is SIM only then pdg id of genMOM= " << simMom->pdgId() << std::endl;
          myMomRho[i] = simMom->vertex().Rho();
          myMomZ[i] = simMom->vertex().Z();
          edm::LogVerbatim("MuonMCClassifAndAna") << "\t Particle pdgId = " << myHitsPdgId[i] << " produced at rho = " << myProdRho[i] 
                                                  << ", z = " << myProdZ[i] << ", has SIM mother pdgId = " << myMomPdgId[i]
                                                  << " produced at rho = " << simMom->vertex().Rho() << ", z = " << simMom->vertex().Z();
          if (!(simMom->genParticles().empty()))
          {
            myMomStatus[i] = simMom->genParticles()[0]->status();
            reco::GenParticleRef genGMom = (
                simMom->genParticles()[0]->numberOfMothers() > 0 ? simMom->genParticles()[0]->motherRef() : reco::GenParticleRef());
            if (genGMom.isNonnull())
              myGmomPdgId[i] = genGMom->pdgId();
            edm::LogVerbatim("MuonMCClassifAndAna") << "\t\t SIM mother is in GEN (status " << myMomStatus[i] << "), grand-mom id = " << myGmomPdgId[i];
          }
          else
          {
            myMomStatus[i] = -1;
            TrackingParticleRef simGMom = getTpMother(simMom);
            if (simGMom.isNonnull())
              myGmomPdgId[i] = simGMom->pdgId();
              edm::LogVerbatim("MuonMCClassifAndAna") << "\t\t SIM mother is in SIM only, grand-mom id = " << myGmomPdgId[i];
          }
        }
        else
        {
          edm::LogVerbatim("MuonMCClassifAndAna") << "\t Particle pdgId = " << myHitsPdgId[i] << " produced at rho = " << myProdRho[i] << ", z = " << myProdZ[i] << ", has NO mother!";
        }
      } // Muon is in SIM Only
      myMomFlav[i] = flavour(myMomPdgId[i]);
      myGmomFlav[i] = flavour(myGmomPdgId[i]);
// Check first IF this is a muon at all
      if (abs(tp->pdgId()) != 13)
      {
        myClassif[i] = isGhost ? -1 : 1;
        myExt[i] = isGhost ? -1 : 1;
        edm::LogVerbatim("MuonMCClassifAndAna") << "\t This is not a muon. Sorry. myClassif[i] = " << myClassif[i];
      }
      else
      {
// Is this SIM muon also a GEN muon, with a mother?
        if (!tp->genParticles().empty() && (myMomPdgId[i] != 0))
        {
// original if (abs(myMomPdgId[i]) < 100 && (abs(myMomPdgId[i]) != 15)) //15 is tau, it will be considered later with b and c mothers
//if ((abs(myMomPdgId[i]) < 100 || abs(myMomPdgId[i]) == 443) && (abs(myMomPdgId[i]) != 15)) //add J/psi to prompt mothers
          if ((abs(myMomPdgId[i]) < 100) && (abs(myMomPdgId[i]) != 15)) // original
          {
            myClassif[i] = isGhost ? -4 : 4;
            myFlav[i] = (abs(myMomPdgId[i]) == 15 ? 15 : 13);
            edm::LogVerbatim("MuonMCClassifAndAna") << "\t This seems PRIMARY MUON ! myClassif[i] = " << myClassif[i];
            if (debug)
              std::cout << "\t This seems PRIMARY MUON ! myClassif[i] = " << myClassif[i] << std::endl;
            myExt[i] = 10;
          }
          else if (myMomFlav[i] == 4 || myMomFlav[i] == 5 || myMomFlav[i] == 15) //if b, c or tau decays. e.g. heavy decaus
          {
            myClassif[i] = isGhost ? -3 : 3;
            myFlav[i] = myMomFlav[i];
            if (myMomFlav[i] == 15)
              myExt[i] = 9; // tau->mu
            else if (myMomFlav[i] == 5)
              myExt[i] = 8; // b->mu
            else if (myHmomFlav[i] == 5)
              myExt[i] = 7; // b->c->mu
            else
              myExt[i] = 6; // c->mu
            edm::LogVerbatim("MuonMCClassifAndAna") << "\t This seems HEAVY FLAVOUR ! myClassif[i] = " << myClassif[i];
          }
          else
          {
            myClassif[i] = isGhost ? -2 : 2;
            myFlav[i] = myMomFlav[i];
            edm::LogVerbatim("MuonMCClassifAndAna") << "\t This seems LIGHT FLAVOUR ! myClassif[i] = " << myClassif[i];
          }
        } // Is this SIM muon also a GEN muon, with a mother?
        else
        {
          myClassif[i] = isGhost ? -2 : 2;
          myFlav[i] = myMomFlav[i];
          edm::LogVerbatim("MuonMCClassifAndAna") << "\t This seems LIGHT FLAVOUR ! myClassif[i] = " << myClassif[i];
          if (debug)
            std::cout << "\t This seems LIGHT FLAVOUR ! myClassif[i] = " << myClassif[i] << std::endl;
        }
// extended classification
        if (myMomPdgId[i] == 0)
          myExt[i] = 2; // if it has no mom, it's not a primary particle so it won't be in ppMuX
        else if (abs(myMomPdgId[i]) < 100)
          myExt[i] = (myMomFlav[i] == 15 ? 9 : 10); // primary mu (10), or tau->mu(9)
        else if (myMomFlav[i] == 5)
          myExt[i] = 8; // b->mu
        else if (myMomFlav[i] == 4)
          myExt[i] = (myHmomFlav[i] == 5 ? 7 : 6); // b->c->mu(b->c->...) and c->mu(6)
        else if (myMomStatus[i] != -1)
        {
// primary light particle
          int id = abs(myMomPdgId[i]);
          if (id != /*pi+*/211 && id != /*K+*/321 && id != 130 /*K0L*/)
            myExt[i] = 5; // other light particle, possibly short-lived
          else if (myProdRho[i] < decayRho_ && abs(myProdZ[i]) < decayAbsZ_)
            myExt[i] = 4; // decay a la ppMuX (primary pi/K within a cylinder)
          else
            myExt[i] = 3; // late decay that wouldn't be in ppMuX
        }
        else
          myExt[i] = 2; // decay of non-primary particle, would not be in ppMuX
        if (isGhost)
          myExt[i] = -myExt[i];
        if (linkToGenParticles_ && abs(myExt[i]) >= 2)
        {
// Link to the genParticle if possible, but not decays in flight (in ppMuX they're in GEN block, but they have wrong parameters)
          if (!tp->genParticles().empty() && abs(myExt[i]) >= 5)
          {
            if (genParticles.id() != tp->genParticles().id())
            {
              throw cms::Exception("Configuration") << "Product ID mismatch between the genParticle collection ("

              << genParticles_ << ", id " << genParticles.id() << ") and the references in the TrackingParticles (id "
                  << tp->genParticles().id() << ")\n";
            }
            muToPrimary[i] = tp->genParticles()[0].key();
          }
          else
          {
// Don't put the same trackingParticle twice!
            int &indexPlus1 = tpToSecondaries[tp]; // will create a 0 if the tp is not in the list already
            if (indexPlus1 == 0)
              indexPlus1 = convertAndPush(*tp, *secondaries, getTpMother(tp), genParticles) + 1;
            muToSecondary[i] = indexPlus1 - 1;
          }
        }
        edm::LogVerbatim("MuonMCClassifAndAna") << "\t Extended clasmyClassifion code = " << myExt[i];
//std::cout << "Extended clasmyClassifion code = " << myExt[i] << std::endl;
      } //else statement in place of continue

    } //ent tp is nonNull

//case == 1 global; case == 2 tracker; case == 3 standalone; case == 4 good; case == 5 tight; case == 6 soft; case == 7 loose
    reco::TrackRef trackref;
    if (!(myCase == 1 || myCase == 3)) //all cases that are not global or standalone, e.g. tracker, good, tight, soft, loose
    {
      if ((*myMuons_handle)[i].muonBestTrack().isNonnull())
        trackref = (*myMuons_handle)[i].muonBestTrack();
      else
        continue;
    }
    else if (myCase == 3) //standalone case
    {
      if ((*myMuons_handle)[i].outerTrack().isNonnull())
        trackref = (*myMuons_handle)[i].outerTrack();
      else
        continue;
    }
    else if (myCase == 1) //global case
    {
      if ((*myMuons_handle)[i].globalTrack().isNonnull())
        trackref = (*myMuons_handle)[i].globalTrack();
      else
        continue;
    }
// if(myExt[i] == 1 || myExt[i] == 3)
    if (myClassif[i] == 1)
    {
      N_Muons->Fill(binp);
      N_Muons_norm->Fill(binp);
      histoPt_p->Fill(trackref->pt());
      histoEta_p->Fill(trackref->eta());
      histoPhi_p->Fill(trackref->phi());
    }
// if(myExt[i] == 4 || myExt[i] == 5)
    if (myClassif[i] == 2)
    {
      N_Muons->Fill(binl);
      N_Muons_norm->Fill(binl);
      histoPt_l->Fill(trackref->pt());
      histoEta_l->Fill(trackref->eta());
      histoPhi_l->Fill(trackref->phi());
    }
//if(myExt[i] >=6 && myExt[i] <=9)
    if (myClassif[i] == 3)
    {
      N_Muons->Fill(binh);
      N_Muons_norm->Fill(binh);
      histoPt_h->Fill(trackref->pt());
      histoEta_h->Fill(trackref->eta());
      histoPhi_h->Fill(trackref->phi());
    }
// if(myExt[i] == 10)
    if (myClassif[i] == 4)
    {
      N_Muons->Fill(binpr);
      N_Muons_norm->Fill(binpr);
      histoPt_pr->Fill(trackref->pt());
      histoEta_pr->Fill(trackref->eta());
      histoPhi_pr->Fill(trackref->phi());
    }
//if (myExt[i] == 2)
    if (myClassif[i] == 0)
    {
      N_Muons->Fill(binn);
      N_Muons_norm->Fill(binn);
      histoPt_n->Fill(trackref->pt());
      histoEta_n->Fill(trackref->eta());
      histoPhi_n->Fill(trackref->phi());
    }
//if(myExt[i] < 0 && fabs(myExt[i])<11)
    if (myClassif[i] < 0 && fabs(myClassif[i]) < 5)
    {
      N_Muons->Fill(bingst);
      N_Muons_norm->Fill(bingst);
      histoPt_gst->Fill(trackref->pt());
      histoEta_gst->Fill(trackref->eta());
      histoPhi_gst->Fill(trackref->phi());
    }
  } //ent loop over myMuons_handle size
}

int MuonMCClassifAndAna::flavour(int pdgId) const
{
  int flav = abs(pdgId);
// for quarks, leptons and bosons except gluons, take their pdgId
// muons and taus have themselves as flavour
  if (flav <= 37 && flav != 21)
    return flav;
// look for barions
  int bflav = ((flav / 1000) % 10);
  if (bflav != 0)
    return bflav;
// look for mesons
  int mflav = ((flav / 100) % 10);
  if (mflav != 0)
    return mflav;
  return 0;
}
// push secondary in collection.
// if it has a primary mother link to it.

int MuonMCClassifAndAna::convertAndPush(const TrackingParticle &tp, reco::GenParticleCollection &out,
    const TrackingParticleRef & simMom, const edm::Handle<reco::GenParticleCollection> & genParticles) const
{
  out.push_back(reco::GenParticle(tp.charge(), tp.p4(), tp.vertex(), tp.pdgId(), tp.status(), true));
  if (simMom.isNonnull() && !simMom->genParticles().empty())
  {
    if (genParticles.id() != simMom->genParticles().id())
    {
      throw cms::Exception("Configuration") << "Product ID mismatch between the genParticle collection ("

      << genParticles_ << ", id " << genParticles.id() << ") and the references in the TrackingParticles (id "
          << simMom->genParticles().id() << ")\n";
    }
    out.back().addMother(simMom->genParticles()[0]);
  }
  return out.size() - 1;
}
void MuonMCClassifAndAna::beginJob()
{
  edm::Service < TFileService > fs;

  allMuonsTimeInOut = fs->make < TH1F > ("allMuonsTimeInOut", "allMuonsTimeInOut", 20000, -100, 100);
  allMuonsTimeOutIn = fs->make < TH1F > ("allMuonsTimeOutIn", "allMuonsTimeOutIn", 20000, -100, 100);
  allMuonsTimeDirection = fs->make < TH1F > ("allMuonsTimeDirection", "allMuonsTimeDirection", 5, -2.5, 2.5);
  allMuonsTimeInOutUndef = fs->make < TH1F > ("allMuonsTimeInOutUndef", "allMuonsTimeInOutUndef", 20000, -100, 100);
  allMuonsTimeOutInUndef = fs->make < TH1F > ("allMuonsTimeOutInUndef", "allMuonsTimeOutInUndef", 20000, -100, 100);

  staMuonsTimeInOut = fs->make < TH1F > ("staMuonsTimeInOut", "staMuonsTimeInOut", 20000, -100, 100);
  staMuonsTimeOutIn = fs->make < TH1F > ("staMuonsTimeOutIn", "staMuonsTimeOutIn", 20000, -100, 100);

  globMuonsTimeInOut = fs->make < TH1F > ("globMuonsTimeInOut", "globMuonsTimeInOut", 20000, -100, 100);
  globMuonsTimeOutIn = fs->make < TH1F > ("globMuonsTimeOutIn", "globMuonsTimeOutIn", 20000, -100, 100);

  N_Muons = fs->make < TH1F > ("N_muons", "Muon collections", 70, 0, 70);
  N_Muons->GetXaxis()->SetBinLabel(2, "All sel muons");
  N_Muons->GetXaxis()->SetBinLabel(4, "Glb muons");
  N_Muons->GetXaxis()->SetBinLabel(5, "Glb mu from punch");
  N_Muons->GetXaxis()->SetBinLabel(6, "Glb mu from light/decay");
  N_Muons->GetXaxis()->SetBinLabel(7, "Glb mu from heavy flv");
  N_Muons->GetXaxis()->SetBinLabel(8, "Glb mu from primary");
  N_Muons->GetXaxis()->SetBinLabel(9, "Glb mu from noise");
  N_Muons->GetXaxis()->SetBinLabel(10, "Glb mu from ghost");

  N_Muons->GetXaxis()->SetBinLabel(20, "Sta muons");
  N_Muons->GetXaxis()->SetBinLabel(21, "Sta mu from punch");
  N_Muons->GetXaxis()->SetBinLabel(22, "Sta mu from light/decay");
  N_Muons->GetXaxis()->SetBinLabel(23, "Sta mu from heavy flv");
  N_Muons->GetXaxis()->SetBinLabel(24, "Sta mu from primary");
  N_Muons->GetXaxis()->SetBinLabel(25, "Sta mu from noise");
  N_Muons->GetXaxis()->SetBinLabel(26, "Sta mu from ghost");

  N_Muons->GetXaxis()->SetBinLabel(36, "Tight muons");
  N_Muons->GetXaxis()->SetBinLabel(37, "Tight mu from punch");
  N_Muons->GetXaxis()->SetBinLabel(38, "Tight mu from light/decay");
  N_Muons->GetXaxis()->SetBinLabel(39, "Tight mu from heavy flv");
  N_Muons->GetXaxis()->SetBinLabel(40, "Tight mu from primary");
  N_Muons->GetXaxis()->SetBinLabel(41, "Tight mu from noise");
  N_Muons->GetXaxis()->SetBinLabel(42, "Tight mu from ghost");

  N_Muons->GetXaxis()->SetBinLabel(52, "Loose muons");
  N_Muons->GetXaxis()->SetBinLabel(53, "Loose mu from punch");
  N_Muons->GetXaxis()->SetBinLabel(54, "Loose mu from light/decay");
  N_Muons->GetXaxis()->SetBinLabel(55, "Loose mu from heavy flv");
  N_Muons->GetXaxis()->SetBinLabel(56, "Loose mu from primary");
  N_Muons->GetXaxis()->SetBinLabel(57, "Loose mu from noise");
  N_Muons->GetXaxis()->SetBinLabel(58, "Loose mu from ghost");
  N_Muons->GetXaxis()->SetBinLabel(61, "total muon evts");
  N_Muons->GetXaxis()->SetBinLabel(63, "number of PV");
  N_Muons->GetXaxis()->SetBinLabel(65, "total muons");


  N_Muons_norm = fs->make < TH1F > ("N_Muons_norm", "Muon collections Normalized to the #muons", 70, 0, 70);
  N_Muons_norm->GetXaxis()->SetBinLabel(2, "All sel muons");
  N_Muons_norm->GetXaxis()->SetBinLabel(4, "Glb muons");
  N_Muons_norm->GetXaxis()->SetBinLabel(5, "Glb mu from punch");
  N_Muons_norm->GetXaxis()->SetBinLabel(6, "Glb mu from light/decay");
  N_Muons_norm->GetXaxis()->SetBinLabel(7, "Glb mu from heavy flv");
  N_Muons_norm->GetXaxis()->SetBinLabel(8, "Glb mu from primary");
  N_Muons_norm->GetXaxis()->SetBinLabel(9, "Glb mu from noise");
  N_Muons_norm->GetXaxis()->SetBinLabel(10, "Glb mu from ghost");

  N_Muons_norm->GetXaxis()->SetBinLabel(20, "Sta muons");
  N_Muons_norm->GetXaxis()->SetBinLabel(21, "Sta mu from punch");
  N_Muons_norm->GetXaxis()->SetBinLabel(22, "Sta mu from light/decay");
  N_Muons_norm->GetXaxis()->SetBinLabel(23, "Sta mu from heavy flv");
  N_Muons_norm->GetXaxis()->SetBinLabel(24, "Sta mu from primary");
  N_Muons_norm->GetXaxis()->SetBinLabel(25, "Sta mu from noise");
  N_Muons_norm->GetXaxis()->SetBinLabel(26, "Sta mu from ghost");

  N_Muons_norm->GetXaxis()->SetBinLabel(36, "Tight muons");
  N_Muons_norm->GetXaxis()->SetBinLabel(37, "Tight mu from punch");
  N_Muons_norm->GetXaxis()->SetBinLabel(38, "Tight mu from light/decay");
  N_Muons_norm->GetXaxis()->SetBinLabel(39, "Tight mu from heavy flv");
  N_Muons_norm->GetXaxis()->SetBinLabel(40, "Tight mu from primary");
  N_Muons_norm->GetXaxis()->SetBinLabel(41, "Tight mu from noise");
  N_Muons_norm->GetXaxis()->SetBinLabel(42, "Tight mu from ghost");

  N_Muons_norm->GetXaxis()->SetBinLabel(52, "Loose muons");
  N_Muons_norm->GetXaxis()->SetBinLabel(53, "Loose mu from punch");
  N_Muons_norm->GetXaxis()->SetBinLabel(54, "Loose mu from light/decay");
  N_Muons_norm->GetXaxis()->SetBinLabel(55, "Loose mu from heavy flv");
  N_Muons_norm->GetXaxis()->SetBinLabel(56, "Loose mu from primary");
  N_Muons_norm->GetXaxis()->SetBinLabel(57, "Loose mu from noise");
  N_Muons_norm->GetXaxis()->SetBinLabel(58, "Loose mu from ghost");
  N_Muons_norm->GetXaxis()->SetBinLabel(61, "total muon evts");
  N_Muons_norm->GetXaxis()->SetBinLabel(63, "number of PV");
  N_Muons_norm->GetXaxis()->SetBinLabel(65, "total muons");
  totalevents_withMuons = fs->make < TH1F > ("totalevents_withMuons", "Number events with Muons", 100, 0, 100); //

  numb_MuPerEvent = fs->make < TH1F > ("numb_MuPerEvent", "Number of Reco Muons per Event", 500, 0, 500); //
  numb_PV = fs->make < TH1F > ("numb_PV", "Number of Reconstructed Primary Vertices", 100, 0, 100); //
  numb_SimPV = fs->make < TH1F > ("numb_SimPV", "Number of Simulated Primary Vertices", 100, 0, 100); //
  Pt_TrakingParticle = fs->make < TH1F > ("Pt_TrakingParticle", "p_{T} of Tracking Particles", 1000, 0., 500.);
  PtMuons_TrakingParticle = fs->make < TH1F > ("PtMuons_TrakingParticle", "p_{T} of muons from Tracking Particle collection", 1000, 0., 500.);

  allMuonsPt = fs->make < TH1F > ("allMuonsPt", "p_{T} for All Selected Reco Muons", 1000, 0., 500.);
  allMuonsPt->SetXTitle("p_{T} [GeV]");
  allMuonsPt->SetYTitle("# of muons");
  allMuonsEta = fs->make < TH1F > ("allMuonsEta", "#eta for All Selected Reco Muons", 70, -3.5, 3.5);
  allMuonsEta->SetXTitle("#eta");
  allMuonsEta->SetYTitle("# of muons");
  allMuonsPhi = fs->make < TH1F > ("allMuonsPhi", "#varphi for All Selected Reco Muons", 70, -3.5, 3.5);
  allMuonsPhi->SetXTitle("#varphi");
  GlobalMuonsPt = fs->make < TH1F > ("GlobalMuonsPt", "p_{T} for Global Reco Muons", 1000, 0., 500.);
  GlobalMuonsEta = fs->make < TH1F > ("GlobalMuonsEta", "#eta for Global Reco Muons", 70, -3.5, 3.5);
  GlobalMuonsPhi = fs->make < TH1F > ("GlobalMuonsPhi", "#varphi for Global Reco Muons", 70, -3.5, 3.5);

  StaMuonsPt = fs->make < TH1F > ("StaMuonsPt", "p_{T} for Stand alone Reco Muons", 1000, 0., 500.);
  StaMuonsEta = fs->make < TH1F > ("StaMuonsEta", "#eta for Stand alone Reco Muons", 70, -3.5, 3.5);
  StaMuonsPhi = fs->make < TH1F > ("StaMuonsPhi", "#varphi for Stand alone Reco Muons", 70, -3.5, 3.5);

  TightMuonsPt = fs->make < TH1F > ("TightMuonsPt", "p_{T} for Tight Reco Muons", 1000, 0., 500.);
  TightMuonsEta = fs->make < TH1F > ("TightMuonsEta", "#eta for Tight Reco Muons", 70, -3.5, 3.5);
  TightMuonsPhi = fs->make < TH1F > ("TightMuonsPhi", "#varphi for Tight Reco Muons", 70, -3.5, 3.5);

  LooseMuonsPt = fs->make < TH1F > ("LooseMuonsPt", "p_{T} for Loose Reco Muons", 1000, 0., 500.);
  LooseMuonsEta = fs->make < TH1F > ("LooseMuonsEta", "#eta for Loose Reco Muons", 70, -3.5, 3.5);
  LooseMuonsPhi = fs->make < TH1F > ("LooseMuonsPhi", "#varphi for Loose Reco Muons", 70, -3.5, 3.5);
  muPt_Glb_punch = fs->make < TH1F > ("muPt_Glb_punch", "p_{T} for Global punch thorugh Muons", 1000, 0., 500.);
  muPt_Glb_lightflv = fs->make < TH1F > ("muPt_Glb_lightflv", "p_{T} for Global light flavour Muons", 1000, 0., 500.);
  muPt_Glb_heavyflv = fs->make < TH1F > ("muPt_Glb_heavyflv", "p_{T} for Global heavy flavour Muons", 1000, 0., 500.);
  muPt_Glb_primary = fs->make < TH1F > ("muPt_Glb_primary", "p_{T} for Global primary Muons", 1000, 0., 500.);
  muPt_Glb_noise = fs->make < TH1F > ("muPt_Glb_noise", "p_{T} for Global noise", 1000, 0., 500.);
  muPt_Glb_ghost = fs->make < TH1F > ("muPt_Glb_ghost", "p_{T} for Global ghosts", 1000, 0., 500.);

  muPt_Sta_punch = fs->make < TH1F > ("muPt_Sta_punch", "p_{T} for Sta punch thorugh Muons", 1000, 0., 500.);
  muPt_Sta_lightflv = fs->make < TH1F > ("muPt_Sta_lightflv", "p_{T} for Sta light flavour Muons", 1000, 0., 500.);
  muPt_Sta_heavyflv = fs->make < TH1F > ("muPt_Sta_heavyflv", "p_{T} for Sta heavy flavour Muons", 1000, 0., 500.);
  muPt_Sta_primary = fs->make < TH1F > ("muPt_Sta_primary", "p_{T} for Sta primary Muons", 1000, 0., 500.);
  muPt_Sta_noise = fs->make < TH1F > ("muPt_Sta_noise", "p_{T} for Sta noise", 1000, 0., 500.);
  muPt_Sta_ghost = fs->make < TH1F > ("muPt_Sta_ghost", "p_{T} for Sta ghost", 1000, 0., 500.);

  muPt_Tight_punch = fs->make < TH1F > ("muPt_Tight_punch", "p_{T} for Tight punch thorugh Muons", 1000, 0., 500.);
  muPt_Tight_lightflv = fs->make < TH1F > ("muPt_Tight_lightflv", "p_{T} for Tight light flavour Muons", 1000, 0., 500.);
  muPt_Tight_heavyflv = fs->make < TH1F > ("muPt_Tight_heavyflv", "p_{T} for Tight heavy flavour Muons", 1000, 0., 500.);
  muPt_Tight_primary = fs->make < TH1F > ("muPt_Tight_primary", "p_{T} for Tight primary Muons", 1000, 0., 500.);
  muPt_Tight_noise = fs->make < TH1F > ("muPt_Tight_noise", "p_{T} for Tight noise", 1000, 0., 500.);
  muPt_Tight_ghost = fs->make < TH1F > ("muPt_Tight_ghost", "p_{T} for Tight ghosts", 1000, 0., 500.);

  muPt_Loose_punch = fs->make < TH1F > ("muPt_Loose_punch", "p_{T} for Loose punch thorugh Muons", 1000, 0., 500.);
  muPt_Loose_lightflv = fs->make < TH1F > ("muPt_Loose_lightflv", "p_{T} for Loose light flavour Muons", 1000, 0., 500.);
  muPt_Loose_heavyflv = fs->make < TH1F > ("muPt_Loose_heavyflv", "p_{T} for Loose heavy flavour Muons", 1000, 0., 500.);
  muPt_Loose_primary = fs->make < TH1F > ("muPt_Loose_primary", "p_{T} for Loose primary Muons", 1000, 0., 500.);
  muPt_Loose_noise = fs->make < TH1F > ("muPt_Loose_noise", "p_{T} for Loose noise", 1000, 0., 500.);
  muPt_Loose_ghost = fs->make < TH1F > ("muPt_Loose_ghost", "p_{T} for Loose ghosts", 1000, 0., 500.);

  muEta_Glb_punch = fs->make < TH1F > ("muEta_Glb_punch", "#eta for Global punch through Muons", 70, -3.5, 3.5);
  muEta_Glb_lightflv = fs->make < TH1F > ("muEta_Glb_lightflv", "#eta for Global light flavour Muons", 70, -3.5, 3.5);
  muEta_Glb_heavyflv = fs->make < TH1F > ("muEta_Glb_heavyflv", "#eta for Global heavy flavour Muons", 70, -3.5, 3.5);
  muEta_Glb_primary = fs->make < TH1F > ("muEta_Glb_primary", "#eta for Global primary Muons", 70, -3.5, 3.5);
  muEta_Glb_noise = fs->make < TH1F > ("muEta_Glb_noise", "#eta for Global noise", 70, -3.5, 3.5);
  muEta_Glb_ghost = fs->make < TH1F > ("muEta_Glb_ghost", "#eta for Global ghosts", 70, -3.5, 3.5);

  muEta_Sta_punch = fs->make < TH1F > ("muEta_Sta_punch", "#eta for Sta punch through Muons", 70, -3.5, 3.5);
  muEta_Sta_lightflv = fs->make < TH1F > ("muEta_Sta_lightflv", "#eta for Sta light flavour Muons", 70, -3.5, 3.5);
  muEta_Sta_heavyflv = fs->make < TH1F > ("muEta_Sta_heavyflv", "#eta for Sta heavy flavour Muons", 70, -3.5, 3.5);
  muEta_Sta_primary = fs->make < TH1F > ("muEta_Sta_primary", "#eta for Sta primary Muons", 70, -3.5, 3.5);
  muEta_Sta_noise = fs->make < TH1F > ("muEta_Sta_noise", "#eta for Sta noise", 70, -3.5, 3.5);
  muEta_Sta_ghost = fs->make < TH1F > ("muEta_Sta_ghost", "#eta for Sta ghosts", 70, -3.5, 3.5);

  muEta_Tight_punch = fs->make < TH1F > ("muEta_Tight_punch", "#eta for Tight punch through Muons", 70, -3.5, 3.5);
  muEta_Tight_lightflv = fs->make < TH1F > ("muEta_Tight_lightflv", "#eta for Tight light flavour Muons", 70, -3.5, 3.5);
  muEta_Tight_heavyflv = fs->make < TH1F > ("muEta_Tight_heavyflv", "#eta for Tight heavy flavour Muons", 70, -3.5, 3.5);
  muEta_Tight_primary = fs->make < TH1F > ("muEta_Tight_primary", "#eta for Tight primary Muons", 70, -3.5, 3.5);
  muEta_Tight_noise = fs->make < TH1F > ("muEta_Tight_noise", "#eta for Tight noise", 70, -3.5, 3.5);
  muEta_Tight_ghost = fs->make < TH1F > ("muEta_Tight_ghost", "#eta for Tight ghosts", 70, -3.5, 3.5);

  muEta_Loose_punch = fs->make < TH1F > ("muEta_Loose_punch", "#eta for Loose punch through Muons", 70, -3.5, 3.5);
  muEta_Loose_lightflv = fs->make < TH1F > ("muEta_Loose_lightflv", "#eta for Loose light flavour Muons", 70, -3.5, 3.5);
  muEta_Loose_heavyflv = fs->make < TH1F > ("muEta_Loose_heavyflv", "#eta for Loose heavy flavour Muons", 70, -3.5, 3.5);
  muEta_Loose_primary = fs->make < TH1F > ("muEta_Loose_primary", "#eta for Loose primary Muons", 70, -3.5, 3.5);
  muEta_Loose_noise = fs->make < TH1F > ("muEta_Loose_noise", "#eta for Loose noise", 70, -3.5, 3.5);
  muEta_Loose_ghost = fs->make < TH1F > ("muEta_Loose_ghost", "#eta for Loose ghosts", 70, -3.5, 3.5);

  muPhi_Glb_punch = fs->make < TH1F > ("muPhi_Glb_punch", "#varphi for Global punch through Muons", 70, -3.5, 3.5);
  muPhi_Glb_lightflv = fs->make < TH1F > ("muPhi_Glb_lightflv", "#varphi for Global light flavour Muons", 70, -3.5, 3.5); //
  muPhi_Glb_heavyflv = fs->make < TH1F > ("muPhi_Glb_heavyflv", "#varphi for Global heavy flavour Muons", 70, -3.5, 3.5); //
  muPhi_Glb_primary = fs->make < TH1F > ("muPhi_Glb_primary", "#varphi for Global primary Muons", 70, -3.5, 3.5);
  muPhi_Glb_noise = fs->make < TH1F > ("muPhi_Glb_noise", "#varphi for Global noise", 70, -3.5, 3.5);
  muPhi_Glb_ghost = fs->make < TH1F > ("muPhi_Glb_ghost", "#varphi for Global ghosts", 70, -3.5, 3.5);

  muPhi_Sta_punch = fs->make < TH1F > ("muPhi_Sta_punch", "#varphi for Sta punch through Muons", 70, -3.5, 3.5);
  muPhi_Sta_lightflv = fs->make < TH1F > ("muPhi_Sta_lightflv", "#varphi for Sta light flavour Muons", 70, -3.5, 3.5);
  muPhi_Sta_heavyflv = fs->make < TH1F > ("muPhi_Sta_heavyflv", "#varphi for Sta heavy flavour Muons", 70, -3.5, 3.5);
  muPhi_Sta_primary = fs->make < TH1F > ("muPhi_Sta_primary", "#varphi for Sta primary Muons", 70, -3.5, 3.5);
  muPhi_Sta_noise = fs->make < TH1F > ("muPhi_Sta_noise", "#varphi for Sta noise", 70, -3.5, 3.5);
  muPhi_Sta_ghost = fs->make < TH1F > ("muPhi_Sta_ghost", "#varphi for Sta ghosts", 70, -3.5, 3.5);

  muPhi_Tight_punch = fs->make < TH1F > ("muPhi_Tight_punch", "#varphi for Tight punch through Muons", 70, -3.5, 3.5);
  muPhi_Tight_lightflv = fs->make < TH1F > ("muPhi_Tight_lightflv", "#varphi for Tight light flavour Muons", 70, -3.5, 3.5); //
  muPhi_Tight_heavyflv = fs->make < TH1F > ("muPhi_Tight_heavyflv", "#varphi for Tight heavy flavour Muons", 70, -3.5, 3.5); //
  muPhi_Tight_primary = fs->make < TH1F > ("muPhi_Tight_primary", "#varphi for Tight primary Muons", 70, -3.5, 3.5);
  muPhi_Tight_noise = fs->make < TH1F > ("muPhi_Tight_noise", "#varphi for Tight noise", 70, -3.5, 3.5);
  muPhi_Tight_ghost = fs->make < TH1F > ("muPhi_Tight_ghost", "#varphi for Tight ghosts", 70, -3.5, 3.5);

  muPhi_Loose_punch = fs->make < TH1F > ("muPhi_Loose_punch", "#varphi for Loose punch through Muons", 70, -3.5, 3.5);
  muPhi_Loose_lightflv = fs->make < TH1F > ("muPhi_Loose_lightflv", "#varphi for Loose light flavour Muons", 70, -3.5, 3.5); //
  muPhi_Loose_heavyflv = fs->make < TH1F > ("muPhi_Loose_heavyflv", "#varphi for Loose heavy flavour Muons", 70, -3.5, 3.5); //
  muPhi_Loose_primary = fs->make < TH1F > ("muPhi_Loose_primary", "#varphi for Loose primary Muons", 70, -3.5, 3.5);
  muPhi_Loose_noise = fs->make < TH1F > ("muPhi_Loose_noise", "#varphi for Loose noise", 70, -3.5, 3.5);
  muPhi_Loose_ghost = fs->make < TH1F > ("muPhi_Loose_ghost", "#varphi for Loose ghosts", 70, -3.5, 3.5);
}

void MuonMCClassifAndAna::endJob()
{
  double myScale = N_Muons->GetBinContent(65);
  N_Muons_norm->Scale(1. / myScale);
}

void MuonMCClassifAndAna::fillDescriptions(edm::ConfigurationDescriptions& descriptions)
{
//The following says we do not know what parameters are allowed so do no validation
// Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}
//define this as a plug-in
DEFINE_FWK_MODULE (MuonMCClassifAndAna);

