// -*- C++ -*-
//
// Package:    MuonNewGEMRecHits
// Class:      MuonNewGEMRecHits
// 
/**\class MuonNewGEMRecHits MuonNewGEMRecHits.cc Validation/MuonNewGEMRecHits/plugins/MuonNewGEMRecHits.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Archie Sharma
//         Created:  Thu, 10 Mar 2016 14:18:34 GMT
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
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Utilities/interface/InputTag.h"

#include "DQMServices/Core/interface/DQMStore.h"
#include "DQMServices/Core/interface/MonitorElement.h"

//Data Format
#include <DataFormats/GEMRecHit/interface/GEMRecHit.h>
#include "DataFormats/MuonDetId/interface/GEMDetId.h"
#include "DataFormats/GEMRecHit/interface/GEMRecHitCollection.h"
#include <DataFormats/GEMRecHit/interface/GEMSegment.h>
#include <DataFormats/GEMRecHit/interface/GEMSegmentCollection.h>
#include "DataFormats/GeometrySurface/interface/LocalError.h"
#include "DataFormats/GeometryVector/interface/LocalPoint.h"
#include "DataFormats/Scalers/interface/DcsStatus.h"
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/Math/interface/deltaPhi.h"

#include "SimDataFormats/TrackingHit/interface/PSimHitContainer.h"
#include "SimDataFormats/Track/interface/SimTrackContainer.h"
#include "SimDataFormats/TrackingAnalysis/interface/TrackingParticle.h"

///Geometry
#include "Geometry/Records/interface/MuonGeometryRecord.h"
#include "Geometry/CommonDetUnit/interface/GeomDet.h"
#include "Geometry/GEMGeometry/interface/GEMGeometry.h"
#include "Geometry/GEMGeometry/interface/GEMEtaPartition.h"
#include "Geometry/GEMGeometry/interface/GEMEtaPartitionSpecs.h"
#include "Geometry/CommonTopologies/interface/StripTopology.h"

///Log messages
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"


//
// class declaration
//
struct MyGEMRecHit
{
    Int_t detId, particleType;
    Float_t x, y, xErr, yErr;
    Float_t xExt, yExt;
    Int_t region, ring, station, layer, chamber, roll;
    Float_t globalR, globalEta, globalPhi, globalX, globalY, globalZ;
    Int_t bx, clusterSize, firstClusterStrip;
    Float_t x_sim, y_sim;
    Float_t globalEta_sim, globalPhi_sim, globalX_sim, globalY_sim, globalZ_sim;
    Float_t pull;
};


struct MyGEMSimHit
{
    Int_t eventNumber;
    Int_t detUnitId, particleType;
    Float_t x, y, energyLoss, pabs, timeOfFlight;
    Int_t region, ring, station, layer, chamber, roll;
    Float_t globalR, globalEta, globalPhi, globalX, globalY, globalZ;
    Int_t strip;
    Float_t Phi_0, DeltaPhi, R_0;
    Int_t countMatching;
};

struct MyGEMSegment
{
    Int_t detId;
    Float_t localX, localY, localZ;
    Float_t dirTheta, dirPhi;
    Int_t numberRH, ndof;
    Float_t chi2;
};

struct MySimTrack
{
    Float_t pt, eta, phi;
    Char_t charge;
    Char_t endcap;
    Char_t gem_sh_layer1, gem_sh_layer2;
    Char_t gem_rh_layer1, gem_rh_layer2;
    Float_t gem_sh_eta, gem_sh_phi;
    Float_t gem_sh_x, gem_sh_y;
    Float_t gem_rh_eta, gem_rh_phi;
    Float_t gem_lx_even, gem_ly_even;
    Float_t gem_lx_odd, gem_ly_odd;
    Char_t has_gem_sh_l1, has_gem_sh_l2;
    Char_t has_gem_rh_l1, has_gem_rh_l2;
    Float_t gem_trk_eta, gem_trk_phi, gem_trk_rho;
};


class MuonNewGEMRecHits : public edm::EDAnalyzer {
   public:
      explicit MuonNewGEMRecHits(const edm::ParameterSet&);
      ~MuonNewGEMRecHits();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;
    
      bool isSimTrackGood(const SimTrack &);
      bool isGEMRecHitMatched(MyGEMRecHit gem_recHit_, MyGEMSimHit gem_sh);

      virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
      virtual void endRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
      //virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;

      // ----------member data ---------------------------
    bool debug_;
    std::string folderPath_;
    bool EffSaveRootFile_;
    std::string EffRootFileName_;
    
    DQMStore * dbe;
    std::map<std::string, MonitorElement*> gemCollection;
    
    edm::Handle<GEMRecHitCollection> gemRecHits_;
    edm::Handle<GEMSegmentCollection> gemSegment_;
    edm::Handle<edm::PSimHitContainer> GEMHits;
    edm::Handle<edm::SimTrackContainer> sim_tracks;
    edm::Handle<edm::SimVertexContainer> sim_vertices;
    edm::ESHandle<GEMGeometry> gem_geom;
    
    const GEMGeometry* gem_geometry_;
    
    MyGEMSimHit gem_sh;
    MyGEMRecHit gem_rh;
    MyGEMSegment gem_seg;
    MyGEMRecHit gem_rhFromSeg;
    MySimTrack track_;
    
    edm::ParameterSet cfg_;
    
    edm::InputTag simTrackInput_;
    edm::InputTag gemSimHitInput_;
    edm::InputTag gemRecHitInput_;
    edm::InputTag gemSegInput_;
    
    double simTrackMinPt_;
    double simTrackMaxPt_;
    double simTrackMinEta_;
    double simTrackMaxEta_;
    double simTrackOnlyMuon_;
    
    bool hasGEMGeometry_;
    
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
MuonNewGEMRecHits::MuonNewGEMRecHits(const edm::ParameterSet& iConfig):
debug_(iConfig.getUntrackedParameter<bool>("debug")),
folderPath_(iConfig.getUntrackedParameter<std::string>("folderPath")),
EffSaveRootFile_(iConfig.getUntrackedParameter<bool>("EffSaveRootFile")),
EffRootFileName_(iConfig.getUntrackedParameter<std::string>("EffRootFileName"))
{
    
    dbe = edm::Service<DQMStore>().operator->();    
    
    cfg_ = iConfig.getParameter<edm::ParameterSet>("simTrackMatching");
    auto simTrack = cfg_.getParameter<edm::ParameterSet>("simTrack");
    simTrackInput_ = simTrack.getParameter<edm::InputTag>("input");
    simTrackMinPt_ = simTrack.getParameter<double>("minPt");
    simTrackMaxPt_ = simTrack.getParameter<double>("maxPt");
    simTrackMinEta_ = simTrack.getParameter<double>("minEta");
    simTrackMaxEta_ = simTrack.getParameter<double>("maxEta");
    simTrackOnlyMuon_ = simTrack.getParameter<bool>("onlyMuon");
    
    auto gemSimHit = cfg_.getParameter<edm::ParameterSet>("gemSimHit");
    gemSimHitInput_ = gemSimHit.getParameter<edm::InputTag>("input");
    
    auto gemRecHit = cfg_.getParameter<edm::ParameterSet>("gemRecHit");
    gemRecHitInput_ = gemRecHit.getParameter<edm::InputTag>("input");
    
    auto gemSeg = cfg_.getParameter<edm::ParameterSet>("gemSeg");
    gemSegInput_ = gemSeg.getParameter<edm::InputTag>("input");
    
    hasGEMGeometry_=false;

}


MuonNewGEMRecHits::~MuonNewGEMRecHits()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
MuonNewGEMRecHits::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{

  std::cout << " loop 1 started " << std::endl;
   using namespace edm;
    iEvent.getByLabel(simTrackInput_, sim_tracks);
    iEvent.getByLabel(simTrackInput_, sim_vertices);
    iEvent.getByLabel(gemSimHitInput_, GEMHits);
    iEvent.getByLabel(gemRecHitInput_, gemRecHits_);
    iEvent.getByLabel(gemSegInput_, gemSegment_);
    
    std::vector<int> trackIds;
    std::vector<int> trackType;
    const edm::SimTrackContainer & sim_trks = *sim_tracks.product();
    
    for (auto& t: sim_trks)
    {
        if (!isSimTrackGood(t)) continue;
        trackType.push_back(t.type());
        trackIds.push_back(t.trackId());
    }
    
    
    for (edm::PSimHitContainer::const_iterator itHit = GEMHits->begin(); itHit != GEMHits->end(); ++itHit)
    {
       std::cout << " loop 2 started " << std::endl;
       
        if(abs(itHit->particleType()) != 13) continue;
        if(std::find(trackIds.begin(), trackIds.end(), itHit->trackId()) == trackIds.end()) continue;
        
        //std::cout<<"Size "<<trackIds.size()<<" id1 "<<trackIds[0]<<" type1 "<<trackType[0]<<" id2 "<<trackIds[1]<<" type2 "<<trackType[1]<<std::endl;
        std::cout << " loop 3 started " << std::endl;
        gem_sh.eventNumber = iEvent.id().event();
        gem_sh.detUnitId = itHit->detUnitId();
        gem_sh.particleType = itHit->particleType();
        gem_sh.x = itHit->localPosition().x();
        gem_sh.y = itHit->localPosition().y();
        gem_sh.energyLoss = itHit->energyLoss();
        gem_sh.pabs = itHit->pabs();
        gem_sh.timeOfFlight = itHit->timeOfFlight();
        
        const GEMDetId id(itHit->detUnitId());
        
        gem_sh.region = id.region();
        gem_sh.ring = 0;
        gem_sh.station = id.station();
        gem_sh.layer = id.layer();
        gem_sh.chamber = id.chamber();
        gem_sh.roll = id.roll();
        
        const LocalPoint p0(0., 0., 0.);
        const GlobalPoint Gp0(gem_geometry_->idToDet(itHit->detUnitId())->surface().toGlobal(p0));
        
        gem_sh.Phi_0 = Gp0.phi();
        gem_sh.R_0 = Gp0.perp();
        gem_sh.DeltaPhi = atan(-1*id.region()*pow(-1,id.chamber())*itHit->localPosition().x()/(Gp0.perp() + itHit->localPosition().y()));
        
        const LocalPoint hitLP(itHit->localPosition());
        const GlobalPoint hitGP(gem_geometry_->idToDet(itHit->detUnitId())->surface().toGlobal(hitLP));
        gem_sh.globalR = hitGP.perp();
        gem_sh.globalEta = hitGP.eta();
        gem_sh.globalPhi = hitGP.phi();
        gem_sh.globalX = hitGP.x();
        gem_sh.globalY = hitGP.y();
        gem_sh.globalZ = hitGP.z();
        
        //  Now filling strip info using entry point rather than local position to be
        //  consistent with digi strips. To change back, just switch the comments - WHF
        //  me0_sh.strip=gem_geometry_->etaPartition(itHit->detUnitId())->strip(hitLP);
        const LocalPoint hitEP(itHit->entryPoint());
        gem_sh.strip = gem_geometry_->etaPartition(itHit->detUnitId())->strip(hitEP);
        
        int count = 0;
        //std::cout<<"SimHit: region "<<me0_sh.region<<" station "<<me0_sh.station<<" layer "<<me0_sh.layer<<" chamber "<<me0_sh.chamber<<" roll "<<me0_sh.roll<<" strip "<<me0_sh.strip<<" type "<<itHit->particleType()<<" id "<<itHit->trackId()<<" x: "<<me0_sh.x<<std::endl;
        
        for (GEMRecHitCollection::const_iterator recHit = gemRecHits_->begin(); recHit != gemRecHits_->end(); ++recHit)
        {
     
            std::cout << " loop 4 started " << std::endl;       
            gem_rh.x = recHit->localPosition().x();
            gem_rh.xErr = recHit->localPositionError().xx();
            gem_rh.y = recHit->localPosition().y();
            gem_rh.detId = (Short_t) (*recHit).gemId();
            gem_rh.bx = 0;
            gem_rh.clusterSize = 0;
            gem_rh.firstClusterStrip = 0;
            
            GEMDetId id((*recHit).gemId());
            
            gem_rh.region = (Short_t) id.region();
            gem_rh.ring = 0;
            gem_rh.station = (Short_t) id.station();
            gem_rh.layer = (Short_t) id.layer();
            gem_rh.chamber = (Short_t) id.chamber();
            gem_rh.roll = (Short_t) id.roll();
            
            LocalPoint rhLP = recHit->localPosition();
            GlobalPoint rhGP = gem_geometry_->idToDet((*recHit).gemId())->surface().toGlobal(rhLP);
            
            gem_rh.globalR = rhGP.perp();
            gem_rh.globalEta = rhGP.eta();
            gem_rh.globalPhi = rhGP.phi();
            gem_rh.globalX = rhGP.x();
            gem_rh.globalY = rhGP.y();
            gem_rh.globalZ = rhGP.z();
            
            gem_rh.x_sim = gem_sh.x;
            gem_rh.y_sim = gem_sh.y;
            gem_rh.globalEta_sim = gem_sh.globalEta;
            gem_rh.globalPhi_sim = gem_sh.globalPhi;
            gem_rh.globalX_sim = gem_sh.globalX;
            gem_rh.globalY_sim = gem_sh.globalY;
            gem_rh.globalZ_sim = gem_sh.globalZ;
            gem_rh.pull = (gem_sh.x - gem_rh.x) / sqrt(gem_rh.xErr);
            
            // abbreviations
            int re(gem_rh.region);
            int la(gem_rh.layer);
            int st(gem_rh.station);
            
            if(gem_rh.bx != 0) continue;
            if(isGEMRecHitMatched(gem_rh, gem_sh))
            {
              std::cout << " loop 5 started " << std::endl;
              std::cout << " roll fom simhit " << gem_sh.roll<< " roll from rechit " << gem_rh.roll << std::endl;
               bool verbose(false);
               if (verbose){
                    std::cout<<"SimHit: region "<<gem_sh.region<<" station "<<gem_sh.station
                    <<" layer "<<gem_sh.layer<<" chamber "<<gem_sh.chamber<<" roll "
                    <<gem_sh.roll<<" strip "<<gem_sh.strip<<" type "<<itHit->particleType()
                    <<" id "<<itHit->trackId()<<" x: "<<gem_sh.x<<std::endl;
                    std::cout<<"RecHit: region "<<gem_rh.region<<" station "<<gem_rh.station
                    <<" layer "<<gem_rh.layer<<" chamber "<<gem_rh.chamber
                    <<" roll "<<gem_rh.roll<<" firstStrip "<<gem_rh.firstClusterStrip
                    <<" cls "<<gem_rh.clusterSize<<" bx "<<gem_rh.bx<<" x: "<<gem_rh.x
                    <<" sigma: "<<gem_rh.xErr<<std::endl;
                }
                
                /*---------- (x_sim - x_rec) -----------*/
                
                gemCollection["recHitDX"]->Fill(gem_rh.x_sim-gem_rh.x);
                
                if(re==-1 && st==1 && la==1) gemCollection["recHitDX_rm1_st1_l1"]->Fill(gem_rh.x_sim-gem_rh.x);
                if(re==-1 && st==1 && la==2) gemCollection["recHitDX_rm1_st1_l2"]->Fill(gem_rh.x_sim-gem_rh.x);
                if(re==-1 && st==2 && la==1) gemCollection["recHitDX_rm1_st2_l1"]->Fill(gem_rh.x_sim-gem_rh.x);
                if(re==-1 && st==2 && la==2) gemCollection["recHitDX_rm1_st2_l2"]->Fill(gem_rh.x_sim-gem_rh.x);
                if(re==-1 && st==3 && la==1) gemCollection["recHitDX_rm1_st3_l1"]->Fill(gem_rh.x_sim-gem_rh.x);
                if(re==-1 && st==3 && la==2) gemCollection["recHitDX_rm1_st3_l2"]->Fill(gem_rh.x_sim-gem_rh.x);
                
                if(re==1 && st==1 && la==1) gemCollection["recHitDX_rp1_st1_l1"]->Fill(gem_rh.x_sim-gem_rh.x);
                if(re==1 && st==1 && la==2) gemCollection["recHitDX_rp1_st1_l2"]->Fill(gem_rh.x_sim-gem_rh.x);
                if(re==1 && st==2 && la==1) gemCollection["recHitDX_rp1_st2_l1"]->Fill(gem_rh.x_sim-gem_rh.x);
                if(re==1 && st==2 && la==2) gemCollection["recHitDX_rp1_st2_l2"]->Fill(gem_rh.x_sim-gem_rh.x);
                if(re==1 && st==3 && la==1) gemCollection["recHitDX_rp1_st3_l1"]->Fill(gem_rh.x_sim-gem_rh.x);
                if(re==1 && st==3 && la==2) gemCollection["recHitDX_rp1_st3_l2"]->Fill(gem_rh.x_sim-gem_rh.x);
                
                /*---------- Pull -------------*/
                gemCollection["recHitPullLocalX"]->Fill(gem_rh.pull);
                
                if(re==-1 && st==1 && la==1) gemCollection["recHitPullLocalX_rm1_st1_l1"]->Fill(gem_rh.pull);
                if(re==-1 && st==1 && la==2) gemCollection["recHitPullLocalX_rm1_st1_l2"]->Fill(gem_rh.pull);
                if(re==-1 && st==2 && la==1) gemCollection["recHitPullLocalX_rm1_st2_l1"]->Fill(gem_rh.pull);
                if(re==-1 && st==2 && la==2) gemCollection["recHitPullLocalX_rm1_st2_l2"]->Fill(gem_rh.pull);
                if(re==-1 && st==3 && la==1) gemCollection["recHitPullLocalX_rm1_st3_l1"]->Fill(gem_rh.pull);
                if(re==-1 && st==3 && la==2) gemCollection["recHitPullLocalX_rm1_st3_l2"]->Fill(gem_rh.pull);
                
                if(re==1 && st==1 && la==1) gemCollection["recHitPullLocalX_rp1_st1_l1"]->Fill(gem_rh.pull);
                if(re==1 && st==1 && la==2) gemCollection["recHitPullLocalX_rp1_st1_l2"]->Fill(gem_rh.pull);
                if(re==1 && st==2 && la==1) gemCollection["recHitPullLocalX_rp1_st2_l1"]->Fill(gem_rh.pull);
                if(re==1 && st==2 && la==2) gemCollection["recHitPullLocalX_rp1_st2_l2"]->Fill(gem_rh.pull);
                if(re==1 && st==3 && la==1) gemCollection["recHitPullLocalX_rp1_st3_l1"]->Fill(gem_rh.pull);
                if(re==1 && st==3 && la==2) gemCollection["recHitPullLocalX_rp1_st3_l2"]->Fill(gem_rh.pull);
                
                /*---------- Delta Phi ---------*/
                gemCollection["recHitDPhi"]->Fill(gem_rh.globalPhi-gem_rh.globalPhi_sim);
                
                if(re==-1 && st==1 && la==1) gemCollection["recHitDPhi_rm1_st1_l1"]->Fill(gem_rh.globalPhi-gem_rh.globalPhi_sim);
                if(re==-1 && st==1 && la==2) gemCollection["recHitDPhi_rm1_st1_l2"]->Fill(gem_rh.globalPhi-gem_rh.globalPhi_sim);
                if(re==-1 && st==2 && la==1) gemCollection["recHitDPhi_rm1_st2_l1"]->Fill(gem_rh.globalPhi-gem_rh.globalPhi_sim);
                if(re==-1 && st==2 && la==2) gemCollection["recHitDPhi_rm1_st2_l2"]->Fill(gem_rh.globalPhi-gem_rh.globalPhi_sim);
                if(re==-1 && st==3 && la==1) gemCollection["recHitDPhi_rm1_st3_l1"]->Fill(gem_rh.globalPhi-gem_rh.globalPhi_sim);
                if(re==-1 && st==3 && la==2) gemCollection["recHitDPhi_rm1_st3_l2"]->Fill(gem_rh.globalPhi-gem_rh.globalPhi_sim);
                
                if(re==1 && st==1 && la==1) gemCollection["recHitDPhi_rp1_st1_l1"]->Fill(gem_rh.globalPhi-gem_rh.globalPhi_sim);
                if(re==1 && st==1 && la==2) gemCollection["recHitDPhi_rp1_st1_l2"]->Fill(gem_rh.globalPhi-gem_rh.globalPhi_sim);
                if(re==1 && st==2 && la==1) gemCollection["recHitDPhi_rp1_st2_l1"]->Fill(gem_rh.globalPhi-gem_rh.globalPhi_sim);
                if(re==1 && st==2 && la==2) gemCollection["recHitDPhi_rp1_st2_l2"]->Fill(gem_rh.globalPhi-gem_rh.globalPhi_sim);
                if(re==1 && st==3 && la==1) gemCollection["recHitDPhi_rp1_st3_l1"]->Fill(gem_rh.globalPhi-gem_rh.globalPhi_sim);
                if(re==1 && st==3 && la==2) gemCollection["recHitDPhi_rp1_st3_l2"]->Fill(gem_rh.globalPhi-gem_rh.globalPhi_sim);
                
                /*----------- xy Occupancy --------*/
                if(re==-1 && st==1 && la==1) gemCollection["localrh_xy_rm1_st1_l1"]->Fill(gem_rh.globalX,gem_rh.globalY);
                if(re==-1 && st==1 && la==2) gemCollection["localrh_xy_rm1_st1_l2"]->Fill(gem_rh.globalX,gem_rh.globalY);
                if(re==-1 && st==2 && la==1) gemCollection["localrh_xy_rm1_st2_l1"]->Fill(gem_rh.globalX,gem_rh.globalY);
                if(re==-1 && st==2 && la==2) gemCollection["localrh_xy_rm1_st2_l2"]->Fill(gem_rh.globalX,gem_rh.globalY);
                if(re==-1 && st==3 && la==1) gemCollection["localrh_xy_rm1_st3_l1"]->Fill(gem_rh.globalX,gem_rh.globalY);
                if(re==-1 && st==3 && la==2) gemCollection["localrh_xy_rm1_st3_l2"]->Fill(gem_rh.globalX,gem_rh.globalY);
                
                if(re==1 && st==1 && la==1) gemCollection["localrh_xy_rp1_st1_l1"]->Fill(gem_rh.globalX,gem_rh.globalY);
                if(re==1 && st==1 && la==2) gemCollection["localrh_xy_rp1_st1_l2"]->Fill(gem_rh.globalX,gem_rh.globalY);
                if(re==1 && st==2 && la==1) gemCollection["localrh_xy_rp1_st2_l1"]->Fill(gem_rh.globalX,gem_rh.globalY);
                if(re==1 && st==2 && la==2) gemCollection["localrh_xy_rp1_st2_l2"]->Fill(gem_rh.globalX,gem_rh.globalY);
                if(re==1 && st==3 && la==1) gemCollection["localrh_xy_rp1_st3_l1"]->Fill(gem_rh.globalX,gem_rh.globalY);
                if(re==1 && st==3 && la==2) gemCollection["localrh_xy_rp1_st3_l2"]->Fill(gem_rh.globalX,gem_rh.globalY);
                
                /*---------- zR Occupancy --------*/
                const double glb_R(sqrt(gem_rh.globalX*gem_rh.globalX+gem_rh.globalY*gem_rh.globalY));
                if(re==-1) gemCollection["localrh_zr_rm1"]->Fill(gem_rh.globalZ,glb_R);
                if(re==1)  gemCollection["localrh_zr_rp1"]->Fill(gem_rh.globalZ,glb_R);
                
                count++;
            }
        }
        gem_sh.countMatching = count;
    }
    
    
    for (auto gems = gemSegment_->begin(); gems != gemSegment_->end(); gems++) {
        GEMDetId id = gems->gemDetId();
        std::cout <<" Original GEMDetID "<<id<<std::endl;
        //auto roll = gem_geometry_->etaPartition(id);
        //std::cout <<"Global Segment Position "<< roll->toGlobal(gems->localPosition())<<std::endl;
        auto segLP = gems->localPosition();
        auto segLD = gems->localDirection();
        //std::cout <<" Global Direction theta = "<<segLD.theta()<<" phi="<<segLD.phi()<<std::endl;
        auto gemrhs = gems->specificRecHits();
        //std::cout <<"GEM Ensamble Det Id "<<id<<" Number of RecHits "<<gemrhs.size()<<std::endl;
        
        gem_seg.detId = id;
        gem_seg.localX = segLP.x();
        gem_seg.localY = segLP.y();
        gem_seg.localZ = segLP.z();
        gem_seg.dirTheta = segLD.theta();
        gem_seg.dirPhi = segLD.phi();
        gem_seg.numberRH = gemrhs.size();
        gem_seg.chi2 = gems->chi2();
        gem_seg.ndof = gems->degreesOfFreedom();
        
        Double_t reducedChi2 = gem_seg.chi2/(Float_t)gem_seg.ndof;
        
        gemCollection["segReducedChi2"]->Fill(reducedChi2);
        gemCollection["segNumberRH"]->Fill(gem_seg.numberRH);
        std::cout << " rec hits size " << gemrhs.size() << std::endl;
        for (auto rh = gemrhs.begin(); rh!= gemrhs.end(); rh++){
            auto gemid = rh->gemId();
            auto rhr = gem_geometry_->etaPartition(gemid);
            auto rhLP = rh->localPosition();
            auto erhLEP = rh->localPositionError();
            auto rhGP = rhr->toGlobal(rhLP);
            /*
            auto rhLPSegm = roll->toLocal(rhGP);
            float xe = segLP.x()+segLD.x()*rhLPSegm.z()/segLD.z();
            float ye = segLP.y()+segLD.y()*rhLPSegm.z()/segLD.z();
            float ze = rhLPSegm.z();
            LocalPoint extrPoint(xe,ye,ze); // in segment rest frame
            auto extSegm = rhr->toLocal(roll->toGlobal(extrPoint)); // in layer restframe
            */
         
            gem_rhFromSeg.detId = gemid;
            gem_rhFromSeg.region = gemid.region();
            gem_rhFromSeg.station = gemid.station();
            gem_rhFromSeg.ring = 0;
            gem_rhFromSeg.layer = gemid.layer();
            gem_rhFromSeg.chamber = gemid.chamber();
            gem_rhFromSeg.roll = gemid.roll();
            
            gem_rhFromSeg.x = rhLP.x();
            gem_rhFromSeg.xErr = erhLEP.xx();
            gem_rhFromSeg.y = rhLP.y();
            gem_rhFromSeg.yErr = erhLEP.yy();
            
            gem_rhFromSeg.globalR = rhGP.perp();
            gem_rhFromSeg.globalX = rhGP.x();
            gem_rhFromSeg.globalY = rhGP.y();
            gem_rhFromSeg.globalZ = rhGP.z();
            gem_rhFromSeg.globalEta = rhGP.eta();
            gem_rhFromSeg.globalPhi = rhGP.phi();
            
            /* 
            gem_rhFromSeg.xExt = extSegm.x();
            gem_rhFromSeg.yExt = extSegm.y();
            */


	    Double_t pull_x = (gem_rhFromSeg.x - gem_rhFromSeg.xExt) / sqrt(gem_rhFromSeg.xErr);
	    Double_t pull_y = (gem_rhFromSeg.y - gem_rhFromSeg.yExt) / sqrt(gem_rhFromSeg.yErr);            
            // abbreviations
            int reS(gem_rhFromSeg.region);
            int laS(gem_rhFromSeg.layer);
            int stS(gem_rhFromSeg.station);

            bool verbose(false);
            if (verbose)
                std::cout <<" GEM Layer Id "<<rh->gemId()<<" error on the local point "<< erhLEP
                <<"\n-> Ensamble Rest Frame RH local position "<<"\n-> Layer Rest Frame RH local position "<<rhLP<<std::endl;
                //rhLPSegm<<" Segment extrapolation "<<extrPoint
                //<<" Segment extrapolation "<<extSegm<<std::endl;
            
                      
            gemCollection["globalEtaSpecRH"]->Fill(gem_rhFromSeg.globalEta);
            gemCollection["globalPhiSpecRH"]->Fill(gem_rhFromSeg.globalPhi);
            
            //Occupancy
            if(reS==-1 && stS==1 && laS==1) gemCollection["localrh_xy_specRH_rm1_st1_l1"]->Fill(gem_rhFromSeg.globalX,gem_rhFromSeg.globalY);
            if(reS==-1 && stS==1 && laS==2) gemCollection["localrh_xy_specRH_rm1_st1_l2"]->Fill(gem_rhFromSeg.globalX,gem_rhFromSeg.globalY);
            if(reS==-1 && stS==2 && laS==1) gemCollection["localrh_xy_specRH_rm1_st2_l1"]->Fill(gem_rhFromSeg.globalX,gem_rhFromSeg.globalY);
            if(reS==-1 && stS==2 && laS==2) gemCollection["localrh_xy_specRH_rm1_st2_l2"]->Fill(gem_rhFromSeg.globalX,gem_rhFromSeg.globalY);
            if(reS==-1 && stS==3 && laS==1) gemCollection["localrh_xy_specRH_rm1_st3_l1"]->Fill(gem_rhFromSeg.globalX,gem_rhFromSeg.globalY);
            if(reS==-1 && stS==3 && laS==2) gemCollection["localrh_xy_specRH_rm1_st3_l2"]->Fill(gem_rhFromSeg.globalX,gem_rhFromSeg.globalY);
            
            if(reS==1 && stS==1 && laS==1) gemCollection["localrh_xy_specRH_rp1_st1_l1"]->Fill(gem_rhFromSeg.globalX,gem_rhFromSeg.globalY);
            if(reS==1 && stS==1 && laS==2) gemCollection["localrh_xy_specRH_rp1_st1_l2"]->Fill(gem_rhFromSeg.globalX,gem_rhFromSeg.globalY);
            if(reS==1 && stS==2 && laS==1) gemCollection["localrh_xy_specRH_rp1_st2_l1"]->Fill(gem_rhFromSeg.globalX,gem_rhFromSeg.globalY);
            if(reS==1 && stS==2 && laS==2) gemCollection["localrh_xy_specRH_rp1_st2_l2"]->Fill(gem_rhFromSeg.globalX,gem_rhFromSeg.globalY);
            if(reS==1 && stS==3 && laS==1) gemCollection["localrh_xy_specRH_rp1_st3_l1"]->Fill(gem_rhFromSeg.globalX,gem_rhFromSeg.globalY);
            if(reS==1 && stS==3 && laS==2) gemCollection["localrh_xy_specRH_rp1_st3_l2"]->Fill(gem_rhFromSeg.globalX,gem_rhFromSeg.globalY);
            
            //-----zR Occupancy-----
            const double glb_R_specRH(sqrt(gem_rh.globalX*gem_rh.globalX+gem_rh.globalY*gem_rh.globalY));
            if(reS==-1) gemCollection["localrh_zr_specRH_rm1"]->Fill(gem_rhFromSeg.globalZ,glb_R_specRH);
            if(reS==1)  gemCollection["localrh_zr_specRH_rp1"]->Fill(gem_rhFromSeg.globalZ,glb_R_specRH);
            
            /* 
            //Delta X
            if(reS==-1 && stS==1 && laS==1) gemCollection["specRecHitDX_rm1_st1_l1"]->Fill(gem_rhFromSeg.x-gem_rhFromSeg.xExt);
            if(reS==-1 && stS==1 && laS==2) gemCollection["specRecHitDX_rm1_st1_l2"]->Fill(gem_rhFromSeg.x-gem_rhFromSeg.xExt);
            if(reS==-1 && stS==2 && laS==1) gemCollection["specRecHitDX_rm1_st2_l1"]->Fill(gem_rhFromSeg.x-gem_rhFromSeg.xExt);
            if(reS==-1 && stS==2 && laS==2) gemCollection["specRecHitDX_rm1_st2_l2"]->Fill(gem_rhFromSeg.x-gem_rhFromSeg.xExt);
            if(reS==-1 && stS==3 && laS==1) gemCollection["specRecHitDX_rm1_st3_l1"]->Fill(gem_rhFromSeg.x-gem_rhFromSeg.xExt);
            if(reS==-1 && stS==3 && laS==2) gemCollection["specRecHitDX_rm1_st3_l2"]->Fill(gem_rhFromSeg.x-gem_rhFromSeg.xExt);
            
            if(reS==1 && stS==1 && laS==1) gemCollection["specRecHitDX_rp1_st1_l1"]->Fill(gem_rhFromSeg.x-gem_rhFromSeg.xExt);
            if(reS==1 && stS==1 && laS==2) gemCollection["specRecHitDX_rp1_st1_l2"]->Fill(gem_rhFromSeg.x-gem_rhFromSeg.xExt);
            if(reS==1 && stS==2 && laS==1) gemCollection["specRecHitDX_rp1_st2_l1"]->Fill(gem_rhFromSeg.x-gem_rhFromSeg.xExt);
            if(reS==1 && stS==2 && laS==2) gemCollection["specRecHitDX_rp1_st2_l2"]->Fill(gem_rhFromSeg.x-gem_rhFromSeg.xExt);
            if(reS==1 && stS==3 && laS==1) gemCollection["specRecHitDX_rp1_st3_l1"]->Fill(gem_rhFromSeg.x-gem_rhFromSeg.xExt);
            if(reS==1 && stS==3 && laS==2) gemCollection["specRecHitDX_rp1_st3_l2"]->Fill(gem_rhFromSeg.x-gem_rhFromSeg.xExt);
            //Delta Y
            if(reS==-1 && stS==1 && laS==1) gemCollection["specRecHitDY_rm1_st1_l1"]->Fill(gem_rhFromSeg.y-gem_rhFromSeg.yExt);
            if(reS==-1 && stS==1 && laS==2) gemCollection["specRecHitDY_rm1_st1_l2"]->Fill(gem_rhFromSeg.y-gem_rhFromSeg.yExt);
            if(reS==-1 && stS==2 && laS==1) gemCollection["specRecHitDY_rm1_st2_l1"]->Fill(gem_rhFromSeg.y-gem_rhFromSeg.yExt);
            if(reS==-1 && stS==2 && laS==2) gemCollection["specRecHitDY_rm1_st2_l2"]->Fill(gem_rhFromSeg.y-gem_rhFromSeg.yExt);
            if(reS==-1 && stS==3 && laS==1) gemCollection["specRecHitDY_rm1_st3_l1"]->Fill(gem_rhFromSeg.y-gem_rhFromSeg.yExt);
            if(reS==-1 && stS==3 && laS==2) gemCollection["specRecHitDY_rm1_st3_l2"]->Fill(gem_rhFromSeg.y-gem_rhFromSeg.yExt);
            
            if(reS==1 && stS==1 && laS==1) gemCollection["specRecHitDY_rp1_st1_l1"]->Fill(gem_rhFromSeg.y-gem_rhFromSeg.yExt);
            if(reS==1 && stS==1 && laS==2) gemCollection["specRecHitDY_rp1_st1_l2"]->Fill(gem_rhFromSeg.y-gem_rhFromSeg.yExt);
            if(reS==1 && stS==2 && laS==1) gemCollection["specRecHitDY_rp1_st2_l1"]->Fill(gem_rhFromSeg.y-gem_rhFromSeg.yExt);
            if(reS==1 && stS==2 && laS==2) gemCollection["specRecHitDY_rp1_st2_l2"]->Fill(gem_rhFromSeg.y-gem_rhFromSeg.yExt);
            if(reS==1 && stS==3 && laS==1) gemCollection["specRecHitDY_rp1_st3_l1"]->Fill(gem_rhFromSeg.y-gem_rhFromSeg.yExt);
            if(reS==1 && stS==3 && laS==2) gemCollection["specRecHitDY_rp1_st3_l2"]->Fill(gem_rhFromSeg.y-gem_rhFromSeg.yExt);
            */

            //Pull X
            if(reS==-1 && stS==1 && laS==1) gemCollection["specRecHitPullLocalX_rm1_st1_l1"]->Fill(pull_x);
            if(reS==-1 && stS==1 && laS==2) gemCollection["specRecHitPullLocalX_rm1_st1_l2"]->Fill(pull_x);
            if(reS==-1 && stS==2 && laS==1) gemCollection["specRecHitPullLocalX_rm1_st2_l1"]->Fill(pull_x);
            if(reS==-1 && stS==2 && laS==2) gemCollection["specRecHitPullLocalX_rm1_st2_l2"]->Fill(pull_x);
            if(reS==-1 && stS==3 && laS==1) gemCollection["specRecHitPullLocalX_rm1_st3_l1"]->Fill(pull_x);
            if(reS==-1 && stS==3 && laS==2) gemCollection["specRecHitPullLocalX_rm1_st3_l2"]->Fill(pull_x);
            
            if(reS==1 && stS==1 && laS==1) gemCollection["specRecHitPullLocalX_rp1_st1_l1"]->Fill(pull_x);
            if(reS==1 && stS==1 && laS==2) gemCollection["specRecHitPullLocalX_rp1_st1_l2"]->Fill(pull_x);
            if(reS==1 && stS==2 && laS==1) gemCollection["specRecHitPullLocalX_rp1_st2_l1"]->Fill(pull_x);
            if(reS==1 && stS==2 && laS==2) gemCollection["specRecHitPullLocalX_rp1_st2_l2"]->Fill(pull_x);
            if(reS==1 && stS==3 && laS==1) gemCollection["specRecHitPullLocalX_rp1_st3_l1"]->Fill(pull_x);
            if(reS==1 && stS==3 && laS==2) gemCollection["specRecHitPullLocalX_rp1_st3_l2"]->Fill(pull_x);
            
            //Pull Y
            if(reS==-1 && stS==1 && laS==1) gemCollection["specRecHitPullLocalY_rm1_st1_l1"]->Fill(pull_y);
            if(reS==-1 && stS==1 && laS==2) gemCollection["specRecHitPullLocalY_rm1_st1_l2"]->Fill(pull_y);
            if(reS==-1 && stS==2 && laS==1) gemCollection["specRecHitPullLocalY_rm1_st2_l1"]->Fill(pull_y);
            if(reS==-1 && stS==2 && laS==2) gemCollection["specRecHitPullLocalY_rm1_st2_l2"]->Fill(pull_y);
            if(reS==-1 && stS==3 && laS==1) gemCollection["specRecHitPullLocalY_rm1_st3_l1"]->Fill(pull_y);
            if(reS==-1 && stS==3 && laS==2) gemCollection["specRecHitPullLocalY_rm1_st3_l2"]->Fill(pull_y);
            
            if(reS==1 && stS==1 && laS==1) gemCollection["specRecHitPullLocalY_rp1_st1_l1"]->Fill(pull_y);
            if(reS==1 && stS==1 && laS==2) gemCollection["specRecHitPullLocalY_rp1_st1_l2"]->Fill(pull_y);
            if(reS==1 && stS==2 && laS==1) gemCollection["specRecHitPullLocalY_rp1_st2_l1"]->Fill(pull_y);
            if(reS==1 && stS==2 && laS==2) gemCollection["specRecHitPullLocalY_rp1_st2_l2"]->Fill(pull_y);
            if(reS==1 && stS==3 && laS==1) gemCollection["specRecHitPullLocalY_rp1_st3_l1"]->Fill(pull_y);
            if(reS==1 && stS==3 && laS==2) gemCollection["specRecHitPullLocalY_rp1_st3_l2"]->Fill(pull_y);
           std::cout << " loop 12 started " << std::endl;       
        }
        std::cout << " loop 13 started " << std::endl;
    }
std::cout << " loop 14 started " << std::endl;
}
    
    


// ------------ method called once each job just before starting event loop  ------------
void 
MuonNewGEMRecHits::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
MuonNewGEMRecHits::endJob() 
{
}

// ------------ method called when starting to processes a run  ------------

void 
MuonNewGEMRecHits::beginRun(edm::Run const&, edm::EventSetup const& iSetup)
{
    try {
        iSetup.get<MuonGeometryRecord>().get(gem_geom);
        gem_geometry_ = &*gem_geom;
        hasGEMGeometry_ = true;
    } catch (edm::eventsetup::NoProxyException<GEMGeometry>& e) {
        hasGEMGeometry_ = false;
        LogDebug("MuonRecHitAnalyzer") << "+++ Info: GEM geometry is unavailable. +++\n";
    }

    if(debug_) std::cout<<"booking Global histograms with "<<folderPath_<<std::endl;
    std::string folder;
    folder = folderPath_;
    dbe->setCurrentFolder(folder);
    
    if(hasGEMGeometry_){
        
        int num_region=2;
        int num_layer=2;
        int num_station=3;
        std::string region[2] ={"m1", "p1"};
        std::string layer[2] = {"l1", "l2"};
        std::string station[3] ={"st1", "st2", "st3"};        

        gemCollection["recHitDX"]=dbe->book1D("recHitDX","x^{local}_{sim} - x^{local}_{rec}; x^{local}_{sim} - x^{local}_{rec} [cm]; entries",100,-1,+1);
        gemCollection["recHitPullLocalX"]=dbe->book1D("recHitPullLocalX","(x^{local}_{sim} - x^{local}_{rec})/#sigma_{x}; (x^{local}_{sim} - x^{local}_{rec})/#sigma_{x}; entries",100,-5,+5);
        gemCollection["recHitDPhi"]=dbe->book1D("recHitDPhi","#phi_{rec} - #phi_{sim}; #phi_{rec} - #phi_{sim} [rad]; entries",100,-0.005,+0.005);
        
        gemCollection["localrh_zr_rm1"]=dbe->book2D("localrh_zr_rm1","GEM RecHit occupancy: region m1;globalZ [cm];globalR [cm]",80,-555,-515,120,20,160);
        gemCollection["localrh_zr_rp1"]=dbe->book2D("localrh_zr_rp1","GEM RecHit occupancy: region p1;globalZ [cm];globalR [cm]",80,515,555,120,20,160);
        
        //-------GEM Segments
        gemCollection["segReducedChi2"]=dbe->book1D("segReducedChi2","#chi^{2}/ndof; #chi^{2}/ndof; # Segments",100,0,5);
        gemCollection["segNumberRH"]=dbe->book1D("segNumberRH","Number of fitted RecHits; # RecHits; entries",11,-0.5,10.5);
        //---
        gemCollection["globalEtaSpecRH"]=dbe->book1D("globalEtaSpecRH","Fitted RecHits Eta Distribution; #eta; entries",200,-4.0,4.0);
        gemCollection["globalPhiSpecRH"]=dbe->book1D("globalPhiSpecRH","Fitted RecHits Phi Distribution; #phi; entries",18,-3.14,3.14);
        //---
        gemCollection["localrh_zr_specRH_rm1"]=dbe->book2D("localrh_zr_specRH_rm1","GEM Specific RecHit occupancy: region m1;globalZ [cm];globalR [cm]",80,-555,-515,120,20,160);
        gemCollection["localrh_zr_specRH_rp1"]=dbe->book2D("localrh_zr_specRH_rp1","GEM Specific RecHit occupancy: region p1;globalZ [cm];globalR [cm]",80,515,555,120,20,160);
        
        
        for(int k=0;k<num_region;k++){
            for(int m=0;m<num_station;m++){
               for (int j=0;j<num_layer;j++){
                
                gemCollection["recHitDX_r"+region[k]+"_"+station[m]+"_"+layer[j]]=dbe->book1D("recHitDX_r"+region[k]+"_"+station[m]+"_"+layer[j],"x^{local}_{sim} - x^{local}_{rec} region "+region[k]+", station "+station[m]+", layer "+std::to_string(j+1)+"; x^{local}_{sim} - x^{local}_{rec} [cm]; entries",100,-1,+1);
                
                gemCollection["recHitPullLocalX_r"+region[k]+"_"+station[m]+"_"+layer[j]]=dbe->book1D("recHitPullLocalX_r"+region[k]+"_"+station[m]+"_"+layer[j],"(x^{local}_{sim} - x^{local}_{rec})/#sigma_{x} region "+region[k]+", station "+station[m]+", layer "+std::to_string(j+1)+"; (x^{local}_{sim} - x^{local}_{rec})/#sigma_{x}; entries",100,-5,+5);
               
                gemCollection["recHitDPhi_r"+region[k]+"_"+station[m]+"_"+layer[j]]=dbe->book1D("recHitDPhi_r"+region[k]+"_"+station[m]+"_"+layer[j],"#phi_{rec} - #phi_{sim} region "+region[k]+", station "+station[m]+", layer "+std::to_string(j+1)+"; #phi_{rec} - #phi_{sim} [rad]; entries",100,-0.001,+0.001);
                
                gemCollection["localrh_xy_r"+region[k]+"_"+station[m]+"_"+layer[j]]=dbe->book2D("localrh_xy_r"+region[k]+"_"+station[m]+"_"+layer[j],"ME0 RecHit occupancy: region "+region[k]+", station "+station[m]+", layer "+std::to_string(j+1)+";globalX [cm];globalY [cm]",120,-280,280,120,-280,280);
                
                //GEM segmentes RecHits
                gemCollection["localrh_xy_specRH_r"+region[k]+"_"+station[m]+"_"+layer[j]]=dbe->book2D("localrh_xy_specRH_r"+region[k]+"_"+station[m]+"_"+layer[j],"ME0 Specific RecHit occupancy: region "+region[k]+", station "+station[m]+", layer "+std::to_string(j+1)+";globalX [cm];globalY [cm]",120,-280,280,120,-280,280);
                
                gemCollection["specRecHitDX_r"+region[k]+"_"+station[m]+"_"+layer[j]]=dbe->book1D("specRecHitDX_r"+region[k]+"_"+station[m]+"_"+layer[j],"x^{local}_{rec} - x^{local}_{ext} region "+region[k]+", station "+station[m]+", layer "+std::to_string(j+1)+"; x^{local}_{rec} - x^{local}_{ext} [cm]; entries",100,-1,+1);
                gemCollection["specRecHitDY_r"+region[k]+"_"+station[m]+"_"+layer[j]]=dbe->book1D("specRecHitDY_r"+region[k]+"_"+station[m]+"_"+layer[j],"y^{local}_{rec} - y^{local}_{ext} region "+region[k]+", station "+station[m]+", layer "+std::to_string(j+1)+"; y^{local}_{rec} - y^{local}_{ext} [cm]; entries",100,-5,+5);
                gemCollection["specRecHitPullLocalX_r"+region[k]+"_"+station[m]+"_"+layer[j]]=dbe->book1D("specRecHitPullLocalX_r"+region[k]+"_"+station[m]+"_"+layer[j],"(x^{local}_{rec} - x^{local}_{ext})/#sigma_{x} region "+region[k]+", station "+station[m]+", layer "+std::to_string(j+1)+"; (x^{local}_{rec} - x^{local}_{ext})/#sigma_{x} [cm]; entries",100,-5,+5);
                gemCollection["specRecHitPullLocalY_r"+region[k]+"_"+station[m]+"_"+layer[j]]=dbe->book1D("specRecHitPullLocalY_r"+region[k]+"_"+station[m]+"_"+layer[j],"(y^{local}_{rec} - y^{local}_{ext})/#sigma_{y} region "+region[k]+", station "+station[m]+", layer "+std::to_string(j+1)+"; (y^{local}_{rec} - y^{local}_{ext})/#sigma_{y} [cm]; entries",100,-5,+5);
                
            }//Layers loop
        
        }//Stations loop
    
      }//region loop    
    }
}


// ------------ method called when ending the processing of a run  ------------

void 
MuonNewGEMRecHits::endRun(edm::Run const&, edm::EventSetup const&)
{
    if (EffSaveRootFile_) dbe->save(EffRootFileName_);
}


// ------------ method called when starting to processes a luminosity block  ------------
/*
void 
MuonNewGEMRecHits::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when ending the processing of a luminosity block  ------------
/*
void 
MuonNewGEMRecHits::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/

bool MuonNewGEMRecHits::isGEMRecHitMatched(MyGEMRecHit gem_recHit_, MyGEMSimHit gem_sh)
{
    
    Int_t gem_region = gem_recHit_.region;
    Int_t gem_layer = gem_recHit_.layer;
    Int_t gem_station = gem_recHit_.station;
    Int_t gem_chamber = gem_recHit_.chamber;
    Int_t gem_roll = gem_recHit_.roll;
    Int_t gem_firstStrip = gem_recHit_.firstClusterStrip;
    Int_t gem_cls = gem_recHit_.clusterSize;
    
    Int_t gem_sh_region = gem_sh.region;
    Int_t gem_sh_layer = gem_sh.layer;
    Int_t gem_sh_station = gem_sh.station;
    Int_t gem_sh_chamber = gem_sh.chamber;
    Int_t gem_sh_roll = gem_sh.roll;
    Int_t gem_sh_strip = gem_sh.strip;
    
    std::vector<int> stripsFired;
    for(int i = gem_firstStrip; i < (gem_firstStrip + gem_cls); i++){
        
        stripsFired.push_back(i);
        
    }
    
    bool cond1, cond2, cond3;
    
    if(gem_sh_region == gem_region && gem_sh_layer == gem_layer && gem_sh_station == gem_station) cond1 = true;
    else cond1 = false;
    if(gem_sh_chamber == gem_chamber && gem_sh_roll == gem_roll) cond2 = true;
    else cond2 = false;
    if(std::find(stripsFired.begin(), stripsFired.end(), (gem_sh_strip + 1)) != stripsFired.end()) cond3 = true;
    else cond3 = false;
    
    if(gem_cls == 0) cond3 = true;
    
    //std::cout<<"cond1: "<<cond1<<" cond2: "<<cond2<<" cond3: "<<cond3<<std::endl;
    return (cond1 & cond2 & cond3);
    
}


bool MuonNewGEMRecHits::isSimTrackGood(const SimTrack &t)
{
    // SimTrack selection
    if (t.noVertex()) return false;
    if (t.noGenpart()) return false;
    // only muons
    if (std::abs(t.type()) != 13 and simTrackOnlyMuon_) return false;
    // pt selection
    if (t.momentum().pt() < simTrackMinPt_) return false;
    // eta selection
    const float eta(std::abs(t.momentum().eta()));
    if (eta > simTrackMaxEta_ || eta < simTrackMinEta_) return false;
    return true;
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
MuonNewGEMRecHits::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(MuonNewGEMRecHits);

