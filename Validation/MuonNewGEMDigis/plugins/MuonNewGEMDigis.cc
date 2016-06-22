// -*- C++ -*-
//
// Package:    MuonNewGEMDigis
// Class:      MuonNewGEMDigis
// 
/**\class MuonNewGEMDigis MuonNewGEMDigis.cc Validation/MuonNewGEMDigis/plugins/MuonNewGEMDigis.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Archie Sharma
//         Created:  Wed, 02 Mar 2016 18:50:43 GMT
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
#include "DataFormats/GEMDigi/interface/GEMDigiCollection.h"
#include "DataFormats/GEMDigi/interface/GEMDigiPreRecoCollection.h"
#include "DataFormats/MuonDetId/interface/GEMDetId.h"
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

struct MyGEMDigi
{
    Int_t detId, particleType;
    Short_t region, ring, station, layer, chamber, roll;
    Short_t strip, bx;
    Float_t x, y;
    Float_t g_r, g_eta, g_phi, g_x, g_y, g_z;
    Float_t x_sim, y_sim;
    Float_t g_eta_sim, g_phi_sim, g_x_sim, g_y_sim, g_z_sim;
};

struct MySimTrack
{
    Float_t pt, eta, phi;
    Char_t charge;
    Char_t endcap;
    Char_t gem_sh_layer1, gem_sh_layer2;
    Char_t gem_dg_layer1, gem_dg_layer2;
    Char_t gem_pad_layer1, gem_pad_layer2;
    Float_t gem_sh_eta, gem_sh_phi;
    Float_t gem_sh_x, gem_sh_y;
    Float_t gem_dg_eta, gem_dg_phi;
    Float_t gem_pad_eta, gem_pad_phi;
    Float_t gem_lx_even, gem_ly_even;
    Float_t gem_lx_odd, gem_ly_odd;
    Char_t  has_gem_sh_l1, has_gem_sh_l2;
    Char_t  has_gem_dg_l1, has_gem_dg_l2;
    Char_t  has_gem_pad_l1, has_gem_pad_l2;
    Float_t gem_trk_eta, gem_trk_phi, gem_trk_rho;
};


class MuonNewGEMDigis : public edm::EDAnalyzer {
   public:
      explicit MuonNewGEMDigis(const edm::ParameterSet&);
      ~MuonNewGEMDigis();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

      bool isSimTrackGood(const SimTrack &);
      bool isGEMDigiMatched(MyGEMDigi gem_dg, MyGEMSimHit gem_sh);

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

    edm::Handle<edm::PSimHitContainer> GEMHits;
    edm::Handle<GEMDigiPreRecoCollection> gem_digis;
    edm::Handle<edm::SimTrackContainer> sim_tracks;
    edm::Handle<edm::SimVertexContainer> sim_vertices;
    edm::ESHandle<GEMGeometry> gem_geom;

    edm::ParameterSet cfg_;

    edm::InputTag gemSimHitInput_;
    edm::InputTag gemDigiInput_;
    edm::InputTag simTrackInput_;

    double simTrackMinPt_;
    double simTrackMaxPt_;
    double simTrackMinEta_;
    double simTrackMaxEta_;
    double simTrackOnlyMuon_;

    const GEMGeometry* gem_geometry_;

    MyGEMDigi gem_digi_;
    MyGEMSimHit gem_sh;
    MySimTrack track_;

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
MuonNewGEMDigis::MuonNewGEMDigis(const edm::ParameterSet& iConfig):
debug_(iConfig.getUntrackedParameter<bool>("debug")),
folderPath_(iConfig.getUntrackedParameter<std::string>("folderPath")),
EffSaveRootFile_(iConfig.getUntrackedParameter<bool>("EffSaveRootFile")),
EffRootFileName_(iConfig.getUntrackedParameter<std::string>("EffRootFileName"))
{
   //now do what ever initialization is needed

    //now do what ever initialization is needed
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

    auto gemDigi = cfg_.getParameter<edm::ParameterSet>("gemStripDigi");
    gemDigiInput_ = gemDigi.getParameter<edm::InputTag>("input");

    hasGEMGeometry_=false;

}


MuonNewGEMDigis::~MuonNewGEMDigis()
{

   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
MuonNewGEMDigis::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
    using namespace edm;
   

    iEvent.getByLabel(simTrackInput_, sim_tracks);
    iEvent.getByLabel(simTrackInput_, sim_vertices);
    iEvent.getByLabel(gemSimHitInput_, GEMHits);
    iEvent.getByLabel(gemDigiInput_, gem_digis);

    std::vector<int> trackIds;
    std::vector<int> trackType;
    const edm::SimTrackContainer & sim_trks = *sim_tracks.product();

    gemCollection["num_events"]->Fill(1);
    for (auto& t: sim_trks)
    {
        if (!isSimTrackGood(t)) continue;
        trackType.push_back(t.type());
        trackIds.push_back(t.trackId());
    }

    for (edm::PSimHitContainer::const_iterator itHit = GEMHits->begin(); itHit != GEMHits->end(); ++itHit)
    {
        if(abs(itHit->particleType()) != 13) continue;
        if(std::find(trackIds.begin(), trackIds.end(), itHit->trackId()) == trackIds.end()) continue;
        
        //std::cout<<"Size "<<trackIds.size()<<" id1 "<<trackIds[0]<<" type1 "<<trackType[0]<<" id2 "<<trackIds[1]<<" type2 "<<trackType[1]<<std::endl;

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
///////////////////////////////////////////////////////////////////////////////////////////////////

        for(GEMDigiPreRecoCollection::DigiRangeIterator cItr = gem_digis->begin(); cItr != gem_digis->end(); ++cItr){

            GEMDetId id = (*cItr).first;

            const GeomDet* gdet = gem_geom->idToDet(id);
            const BoundPlane & surface = gdet->surface();

            gem_digi_.detId = id();
            gem_digi_.region = (Short_t) id.region();
            gem_digi_.ring = 0;
            gem_digi_.station = (Short_t) id.station();
            gem_digi_.layer = (Short_t) id.layer();
            gem_digi_.chamber = (Short_t) id.chamber();
            gem_digi_.roll = (Short_t) id.roll();

            GEMDigiPreRecoCollection::const_iterator digiItr;
            //loop over digis of given roll
            for (digiItr = (*cItr ).second.first; digiItr != (*cItr ).second.second; ++digiItr)
            {
		if(abs(digiItr->pdgid()) != 13) continue;

	        gem_digi_.particleType = digiItr->pdgid();
                gem_digi_.strip = 0;
                gem_digi_.bx = 0;

                gem_digi_.x = (Float_t) digiItr->x();
                gem_digi_.y = (Float_t) digiItr->y();

                LocalPoint lp(digiItr->x(), digiItr->y(), 0);

                GlobalPoint gp = surface.toGlobal(lp);
                gem_digi_.g_r = (Float_t) gp.perp();
                gem_digi_.g_eta = (Float_t) gp.eta();
                gem_digi_.g_phi = (Float_t) gp.phi();
                gem_digi_.g_x = (Float_t) gp.x();
                gem_digi_.g_y = (Float_t) gp.y();
                gem_digi_.g_z = (Float_t) gp.z();

                gem_digi_.x_sim = gem_sh.x;
                gem_digi_.y_sim = gem_sh.y;
                gem_digi_.g_eta_sim = gem_sh.globalEta;
                gem_digi_.g_phi_sim = gem_sh.globalPhi;
                gem_digi_.g_x_sim = gem_sh.globalX;
                gem_digi_.g_y_sim = gem_sh.globalY;
                gem_digi_.g_z_sim = gem_sh.globalZ;

                // abbreviations
                int re(gem_digi_.region);
                int la(gem_digi_.layer);
                int st(gem_digi_.station);
               // int BX(gem_digi_.bx);
                if(gem_digi_.bx != 0) continue;
                if((isGEMDigiMatched(gem_digi_, gem_sh)) && (digiItr->prompt())){
                    count++;
                    //std::cout << " bunch crossings == " << BX << std::endl;
                    std::cout << " GEM station == " << st << std::endl;
                    if(st==3)std::cout << " GEM layer == " << la << std::endl;
                    /*------------zR Occupancy--------------*/
                    const double glb_R(sqrt(gem_digi_.g_x*gem_digi_.g_x+gem_digi_.g_y*gem_digi_.g_y));
                    if(re==-1) gemCollection["strip_dg_zr_rm1"]->Fill(gem_digi_.g_z,glb_R);
                    if(re==1) gemCollection["strip_dg_zr_rp1"]->Fill(gem_digi_.g_z,glb_R);

                    /*-------------XY Occupancy---------------*/
                    
                    if(re==-1 && la==1 && st==1) gemCollection["strip_dg_xy_rm1_st1_l1"]->Fill(gem_digi_.g_x,gem_digi_.g_y);
                    if(re==-1 && la==2 && st==1) gemCollection["strip_dg_xy_rm1_st1_l2"]->Fill(gem_digi_.g_x,gem_digi_.g_y);
                    if(re==-1 && la==1 && st==2) gemCollection["strip_dg_xy_rm1_st2_l1"]->Fill(gem_digi_.g_x,gem_digi_.g_y);
                    if(re==-1 && la==2 && st==2) gemCollection["strip_dg_xy_rm1_st2_l2"]->Fill(gem_digi_.g_x,gem_digi_.g_y);
                    if(re==-1 && la==1 && st==3) gemCollection["strip_dg_xy_rm1_st3_l1"]->Fill(gem_digi_.g_x,gem_digi_.g_y);
                    if(re==-1 && la==2 && st==3) gemCollection["strip_dg_xy_rm1_st3_l2"]->Fill(gem_digi_.g_x,gem_digi_.g_y);

                    if(re==1 && la==1 && st==1) gemCollection["strip_dg_xy_rp1_st1_l1"]->Fill(gem_digi_.g_x,gem_digi_.g_y);
                    if(re==1 && la==2 && st==1) gemCollection["strip_dg_xy_rp1_st1_l2"]->Fill(gem_digi_.g_x,gem_digi_.g_y);
                    if(re==1 && la==1 && st==2) gemCollection["strip_dg_xy_rp1_st2_l1"]->Fill(gem_digi_.g_x,gem_digi_.g_y);
                    if(re==1 && la==2 && st==2) gemCollection["strip_dg_xy_rp1_st2_l2"]->Fill(gem_digi_.g_x,gem_digi_.g_y);
                    if(re==1 && la==1 && st==3) gemCollection["strip_dg_xy_rp1_st3_l1"]->Fill(gem_digi_.g_x,gem_digi_.g_y);
                    if(re==1 && la==2 && st==3) gemCollection["strip_dg_xy_rp1_st3_l2"]->Fill(gem_digi_.g_x,gem_digi_.g_y);
                    
                    /*------------ (x_digi_sim - x_digi_rec) ------------*/
                    gemCollection["digiDX"]->Fill(gem_digi_.g_x_sim-gem_digi_.g_x);

                    
                    if(re==-1 && la==1 && st==1) gemCollection["digiDX_rm1_st1_l1"]->Fill(gem_digi_.g_x_sim-gem_digi_.g_x);
                    if(re==-1 && la==2 && st==1) gemCollection["digiDX_rm1_st1_l2"]->Fill(gem_digi_.g_x_sim-gem_digi_.g_x);
                    if(re==-1 && la==1 && st==2) gemCollection["digiDX_rm1_st2_l1"]->Fill(gem_digi_.g_x_sim-gem_digi_.g_x);
                    if(re==-1 && la==2 && st==2) gemCollection["digiDX_rm1_st2_l2"]->Fill(gem_digi_.g_x_sim-gem_digi_.g_x);
                    if(re==-1 && la==1 && st==3) gemCollection["digiDX_rm1_st3_l1"]->Fill(gem_digi_.g_x_sim-gem_digi_.g_x);
                    if(re==-1 && la==2 && st==3) gemCollection["digiDX_rm1_st3_l2"]->Fill(gem_digi_.g_x_sim-gem_digi_.g_x);

                    if(re==1 && la==1 && st==1) gemCollection["digiDX_rp1_st1_l1"]->Fill(gem_digi_.g_x_sim-gem_digi_.g_x);
                    if(re==1 && la==2 && st==1) gemCollection["digiDX_rp1_st1_l2"]->Fill(gem_digi_.g_x_sim-gem_digi_.g_x);
                    if(re==1 && la==1 && st==2) gemCollection["digiDX_rp1_st2_l1"]->Fill(gem_digi_.g_x_sim-gem_digi_.g_x);
                    if(re==1 && la==2 && st==2) gemCollection["digiDX_rp1_st2_l2"]->Fill(gem_digi_.g_x_sim-gem_digi_.g_x);
                    if(re==1 && la==1 && st==3) gemCollection["digiDX_rp1_st3_l1"]->Fill(gem_digi_.g_x_sim-gem_digi_.g_x);
                    if(re==1 && la==2 && st==3) gemCollection["digiDX_rp1_st3_l2"]->Fill(gem_digi_.g_x_sim-gem_digi_.g_x);
                    
                   /*------------ (phi_digi_sim - phi_digi_rec) ------------*/
                    gemCollection["digiDPhi"]->Fill(gem_digi_.g_phi_sim-gem_digi_.g_phi);
                                     
                    if(re==-1 && la==1 && st==1) gemCollection["digiDPhi_rm1_st1_l1"]->Fill(gem_digi_.g_phi_sim-gem_digi_.g_phi);
                    if(re==-1 && la==2 && st==1) gemCollection["digiDPhi_rm1_st1_l2"]->Fill(gem_digi_.g_phi_sim-gem_digi_.g_phi);
                    if(re==-1 && la==1 && st==2) gemCollection["digiDPhi_rm1_st2_l1"]->Fill(gem_digi_.g_phi_sim-gem_digi_.g_phi);
                    if(re==-1 && la==2 && st==2) gemCollection["digiDPhi_rm1_st2_l2"]->Fill(gem_digi_.g_phi_sim-gem_digi_.g_phi);
                    if(re==-1 && la==1 && st==3) gemCollection["digiDPhi_rm1_st3_l1"]->Fill(gem_digi_.g_phi_sim-gem_digi_.g_phi);
                    if(re==-1 && la==2 && st==3) gemCollection["digiDPhi_rm1_st3_l2"]->Fill(gem_digi_.g_phi_sim-gem_digi_.g_phi);

                    if(re==1 && la==1 && st==1) gemCollection["digiDPhi_rp1_st1_l1"]->Fill(gem_digi_.g_phi_sim-gem_digi_.g_phi);
                    if(re==1 && la==2 && st==1) gemCollection["digiDPhi_rp1_st2_l2"]->Fill(gem_digi_.g_phi_sim-gem_digi_.g_phi);
                    if(re==1 && la==1 && st==2) gemCollection["digiDPhi_rp1_st2_l1"]->Fill(gem_digi_.g_phi_sim-gem_digi_.g_phi);
                    if(re==1 && la==2 && st==2) gemCollection["digiDPhi_rp1_st2_l2"]->Fill(gem_digi_.g_phi_sim-gem_digi_.g_phi);
                    if(re==1 && la==1 && st==3) gemCollection["digiDPhi_rp1_st3_l1"]->Fill(gem_digi_.g_phi_sim-gem_digi_.g_phi);
                    if(re==1 && la==2 && st==3) gemCollection["digiDPhi_rp1_st3_l2"]->Fill(gem_digi_.g_phi_sim-gem_digi_.g_phi);
                    

                }
            }

        }
        gem_sh.countMatching = count;
    }

    for(GEMDigiPreRecoCollection::DigiRangeIterator cItr = gem_digis->begin(); cItr != gem_digis->end(); ++cItr){

        GEMDetId id = (*cItr).first;

        const GeomDet* gdet = gem_geom->idToDet(id);
        const BoundPlane & surface = gdet->surface();

        //Int_t detId = id();
        Short_t region = (Short_t) id.region();
        //Int_t ring = 0;
        //Int_t station = 0;
        Short_t station = (Short_t) id.station();
        Short_t layer = (Short_t) id.layer();
        //Short_t chamber = (Short_t) id.chamber();
        //Short_t roll = (Short_t) id.roll();

        GEMDigiPreRecoCollection::const_iterator digiItr;
        //loop over digis of given roll
        for (digiItr = (*cItr ).second.first; digiItr != (*cItr ).second.second; ++digiItr)
        {

            Int_t particleType = digiItr->pdgid();
            Float_t timing = digiItr->tof();
          //  Int_t strip = 0;
          //  Int_t bx = 0;

          //  Float_t x = (Float_t) digiItr->x();
          //  Float_t y = (Float_t) digiItr->y();

            LocalPoint lp(digiItr->x(), digiItr->y(), 0);

            GlobalPoint gp = surface.toGlobal(lp);
            Float_t g_r = (Float_t) gp.perp();
            //std::cout <<"g_r == " << g_r << std::endl;
            Float_t g_eta = (Float_t) gp.eta();
          //  Float_t g_phi = (Float_t) gp.phi();
            Float_t g_x = (Float_t) gp.x();
            Float_t g_y = (Float_t) gp.y();
            Float_t g_z = (Float_t) gp.z();

            // abbreviations
            int re(region);
            int la(layer);
            int st(station);
/////////////////////////////////////////////////////////////////////////////////////////////////////

            if(digiItr->prompt()){
		  std::cout<<"Prompt"<<std::endl;
                  if(st==1){
                    gemCollection["strip_dg_R_st1_prompt"]->Fill(g_r);
                    gemCollection["strip_dg_st1_prompt_timing"]->Fill(timing);
                  }
                  if(st==2){
                    gemCollection["strip_dg_R_st2_prompt"]->Fill(g_r);
                    gemCollection["strip_dg_st2_prompt_timing"]->Fill(timing);
                  }
                  if(st==3){
                    gemCollection["strip_dg_R_st3_prompt"]->Fill(g_r);
                    gemCollection["strip_dg_st3_prompt_timing"]->Fill(timing);
                  }
                  if ( fabs(particleType) == 11 ) {
                     if(st==1){ 
                     gemCollection["strip_dg_R_st1_prompt_e"]->Fill(g_r);
                     gemCollection["strip_dg_st1_prompt_timing_e"]->Fill(timing);
                     }
                     if(st==2){
                     gemCollection["strip_dg_R_st2_prompt_e"]->Fill(g_r);
                     gemCollection["strip_dg_st2_prompt_timing_e"]->Fill(timing);
                     }
                     if(st==3){
                     gemCollection["strip_dg_R_st3_prompt_e"]->Fill(g_r);
                     gemCollection["strip_dg_st3_prompt_timing_e"]->Fill(timing);
                     }
                  }
                  if ( fabs(particleType) == 13 ) {
                     if(st==1){
                     gemCollection["strip_dg_R_st1_prompt_m"]->Fill(g_r);
                     gemCollection["strip_dg_st1_prompt_timing_m"]->Fill(timing);
                     }
                     if(st==2){
                     gemCollection["strip_dg_R_st2_prompt_m"]->Fill(g_r);
                     gemCollection["strip_dg_st2_prompt_timing_m"]->Fill(timing);
                     }
                     if(st==3){
                     gemCollection["strip_dg_R_st3_prompt_m"]->Fill(g_r);
                     gemCollection["strip_dg_st3_prompt_timing_m"]->Fill(timing);
                     }
                  } 
                  if ( !(fabs(particleType) == 11 && fabs(particleType) == 13) )  {
                     if(st==1){
                     gemCollection["strip_dg_R_st1_prompt_h"]->Fill(g_r);
                     gemCollection["strip_dg_st1_prompt_timing_h"]->Fill(timing);
                     }
                     if(st==2){
                     gemCollection["strip_dg_R_st2_prompt_h"]->Fill(g_r);
                     gemCollection["strip_dg_st2_prompt_timing_h"]->Fill(timing);
                     }
                     if(st==3){
                     gemCollection["strip_dg_R_st3_prompt_h"]->Fill(g_r);
                     gemCollection["strip_dg_st3_prompt_timing_h"]->Fill(timing);
                     }
  
                  }
                 gemCollection["strip_dg_zr_prompt"]->Fill(std::fabs(g_z),g_r);
                   
                  if(re==-1 && la==1 && st==1) gemCollection["strip_dg_xy_rm1_st1_l1_prompt"]->Fill(g_x,g_y);
                  if(re==-1 && la==2 && st==1) gemCollection["strip_dg_xy_rm1_st1_l2_prompt"]->Fill(g_x,g_y);
                  if(re==-1 && la==1 && st==2) gemCollection["strip_dg_xy_rm1_st2_l1_prompt"]->Fill(g_x,g_y);
                  if(re==-1 && la==2 && st==2) gemCollection["strip_dg_xy_rm1_st2_l2_prompt"]->Fill(g_x,g_y);
                  if(re==-1 && la==1 && st==3) gemCollection["strip_dg_xy_rm1_st3_l1_prompt"]->Fill(g_x,g_y);
                  if(re==-1 && la==2 && st==3) gemCollection["strip_dg_xy_rm1_st3_l2_prompt"]->Fill(g_x,g_y);

                  if(re==1 && la==1 && st==1) gemCollection["strip_dg_xy_rp1_st1_l1_prompt"]->Fill(g_x,g_y);
                  if(re==1 && la==2 && st==1) gemCollection["strip_dg_xy_rp1_st1_l2_prompt"]->Fill(g_x,g_y);
                  if(re==1 && la==1 && st==2) gemCollection["strip_dg_xy_rp1_st2_l1_prompt"]->Fill(g_x,g_y);
                  if(re==1 && la==2 && st==2) gemCollection["strip_dg_xy_rp1_st2_l2_prompt"]->Fill(g_x,g_y);
                  if(re==1 && la==1 && st==3) gemCollection["strip_dg_xy_rp1_st3_l1_prompt"]->Fill(g_x,g_y);
                  if(re==1 && la==2 && st==3) gemCollection["strip_dg_xy_rp1_st3_l2_prompt"]->Fill(g_x,g_y);
                
                 }

            if(!(digiItr->prompt())){
                  if(st==1){
                  gemCollection["strip_dg_R_st1_NoPrompt"]->Fill(g_r);
                  gemCollection["strip_dg_eta_st1_NoPrompt"]->Fill(g_eta);
                  gemCollection["strip_dg_timing_st1_NoPrompt"]->Fill(timing);
                  }
                  if(st==2){
                  gemCollection["strip_dg_R_st2_NoPrompt"]->Fill(g_r);
                  gemCollection["strip_dg_eta_st2_NoPrompt"]->Fill(g_eta);
                  gemCollection["strip_dg_timing_st2_NoPrompt"]->Fill(timing);
                  }
                  if(st==3){
                  gemCollection["strip_dg_R_st3_NoPrompt"]->Fill(g_r);
                  gemCollection["strip_dg_eta_st3_NoPrompt"]->Fill(g_eta);
                  gemCollection["strip_dg_timing_st3_NoPrompt"]->Fill(timing);
                  }
                  if ( fabs(particleType) == 11 ){
                     if(st==1){
                     gemCollection["strip_dg_R_st1_NoPrompt_e"]->Fill(g_r);
                     gemCollection["strip_dg_eta_st1_NoPrompt_e"]->Fill(g_eta);
                     gemCollection["strip_dg_timing_st1_NoPrompt_e"]->Fill(timing);
                     }
                     if(st==2){
                     gemCollection["strip_dg_R_st2_NoPrompt_e"]->Fill(g_r);
                     gemCollection["strip_dg_eta_st2_NoPrompt_e"]->Fill(g_eta);
                     gemCollection["strip_dg_timing_st2_NoPrompt_e"]->Fill(timing);
                     }
                     if(st==3){
                     gemCollection["strip_dg_R_st3_NoPrompt_e"]->Fill(g_r);
                     gemCollection["strip_dg_eta_st3_NoPrompt_e"]->Fill(g_eta);
                     gemCollection["strip_dg_timing_st3_NoPrompt_e"]->Fill(timing);
                     }
                  }
                  if ( particleType == 2112 ){
                     if(st==1){
                     gemCollection["strip_dg_R_st1_NoPrompt_n"]->Fill(g_r);
                     gemCollection["strip_dg_eta_st1_NoPrompt_n"]->Fill(g_eta);
                     gemCollection["strip_dg_timing_st1_NoPrompt_n"]->Fill(timing);
                     }
                     if(st==2){
                     gemCollection["strip_dg_R_st2_NoPrompt_n"]->Fill(g_r);
                     gemCollection["strip_dg_eta_st1_NoPrompt_n"]->Fill(g_eta);
                     gemCollection["strip_dg_timing_st2_NoPrompt_n"]->Fill(timing);
                     }
                     if(st==3){
                     gemCollection["strip_dg_R_st3_NoPrompt_n"]->Fill(g_r);
                     gemCollection["strip_dg_eta_st3_NoPrompt_n"]->Fill(g_eta);
                     gemCollection["strip_dg_timing_st3_NoPrompt_n"]->Fill(timing);
                     }
                  }
                  if ( particleType == 22 ) {
                     if(st==1){
                     gemCollection["strip_dg_R_st1_NoPrompt_g"]->Fill(g_r);
                     gemCollection["strip_dg_eta_st1_NoPrompt_g"]->Fill(g_eta);
                     gemCollection["strip_dg_timing_st1_NoPrompt_g"]->Fill(timing);
                     }
                     if(st==2){
                     gemCollection["strip_dg_R_st2_NoPrompt_g"]->Fill(g_r);
                     gemCollection["strip_dg_eta_st2_NoPrompt_g"]->Fill(g_eta);
                     gemCollection["strip_dg_timing_st2_NoPrompt_g"]->Fill(timing);
                     }
                     if(st==3){
                     gemCollection["strip_dg_R_st3_NoPrompt_g"]->Fill(g_r);
                     gemCollection["strip_dg_eta_st3_NoPrompt_g"]->Fill(g_eta);
                     gemCollection["strip_dg_timing_st3_NoPrompt_g"]->Fill(timing);
                     }
                  }
                  gemCollection["strip_dg_zr_NoPrompt"]->Fill(std::fabs(g_z),g_r);
                  
                  if(re==-1 && la==1 && st==1) gemCollection["strip_dg_xy_rm1_st1_l1_NoPrompt"]->Fill(g_x,g_y);
                  if(re==-1 && la==2 && st==1) gemCollection["strip_dg_xy_rm1_st1_l2_NoPrompt"]->Fill(g_x,g_y);
                  if(re==-1 && la==1 && st==2) gemCollection["strip_dg_xy_rm1_st2_l1_NoPrompt"]->Fill(g_x,g_y);
                  if(re==-1 && la==2 && st==2) gemCollection["strip_dg_xy_rm1_st2_l2_NoPrompt"]->Fill(g_x,g_y);
                  if(re==-1 && la==1 && st==3) gemCollection["strip_dg_xy_rm1_st3_l1_NoPrompt"]->Fill(g_x,g_y);
                  if(re==-1 && la==2 && st==3) gemCollection["strip_dg_xy_rm1_st3_l2_NoPrompt"]->Fill(g_x,g_y);

                  if(re==1 && la==1 && st==1) gemCollection["strip_dg_xy_rp1_st1_l1_NoPrompt"]->Fill(g_x,g_y);
                  if(re==1 && la==2 && st==1) gemCollection["strip_dg_xy_rp1_st1_l2_NoPrompt"]->Fill(g_x,g_y);
                  if(re==1 && la==1 && st==2) gemCollection["strip_dg_xy_rp1_st2_l1_NoPrompt"]->Fill(g_x,g_y);
                  if(re==1 && la==2 && st==2) gemCollection["strip_dg_xy_rp1_st2_l2_NoPrompt"]->Fill(g_x,g_y);
                  if(re==1 && la==1 && st==3) gemCollection["strip_dg_xy_rp1_st3_l1_NoPrompt"]->Fill(g_x,g_y);
                  if(re==1 && la==2 && st==3) gemCollection["strip_dg_xy_rp1_st3_l2_NoPrompt"]->Fill(g_x,g_y);
                        
              }

        }

    }

}


// ------------ method called once each job just before starting event loop  ------------
void
MuonNewGEMDigis::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void
MuonNewGEMDigis::endJob()
{
}

// ------------ method called when starting to processes a run  ------------

void MuonNewGEMDigis::beginRun(edm::Run const&, edm::EventSetup const& iSetup)
{
    try {
        iSetup.get<MuonGeometryRecord>().get(gem_geom);
        gem_geometry_ = &*gem_geom;
        hasGEMGeometry_ = true;
    } catch (edm::eventsetup::NoProxyException<GEMGeometry>& e) {
        hasGEMGeometry_ = false;
        LogDebug("MuonSimHitAnalyzer") << "+++ Info: GEM geometry is unavailable. +++\n";
    }

    if(debug_) std::cout<<"booking Global histograms with "<<folderPath_<<std::endl;
    std::string main_folder;
    main_folder = folderPath_;
    std::string prompt_folder = main_folder + "/Prompt";
    std::string noPrompt_folder = main_folder + "/NoPrompt";
    dbe->setCurrentFolder(main_folder);

    if(hasGEMGeometry_){

        int num_region=2;
 	      int num_layers=2;
                  int num_stations=3;

        std::string region[2] ={"m1", "p1"};
   	      std::string layers[2] = {"l1","l2"};
                   std::string stations[3] = {"st1","st2", "st3"};

        gemCollection["num_events"]=dbe->book1D("num_events","Number Total Events",3,0,2);
        gemCollection["strip_dg_zr_rm1"]=dbe->book2D("strip_dg_zr_rm1","Digi occupancy: region m1;globalZ [cm];globalR [cm]",80,-555,-515,120,20,160);
        gemCollection["strip_dg_zr_rp1"]=dbe->book2D("strip_dg_zr_rp1","Digi occupancy: region p1;globalZ [cm];globalR [cm]",80,515,555,120,20,160);
        gemCollection["digiDX"]=dbe->book1D("digiDX","x^{digi}_{sim} - x^{digi}_{rec}; x^{digi}_{sim} - x^{digi}_{rec} [cm]; entries",1000,-50,+50);
        gemCollection["digiDPhi"]=dbe->book1D("digiDPhi","Phi^{digi}_{sim} - Phi^{digi}_{rec}; Phi^{digi}_{sim} - Phi^{digi}_{rec} [rad]; entries",10000,-10,+10);
 

        for(int k=0;k<num_region;k++){
        
           for(int m=0;m<num_stations;m++){
             for(int j=0; j<num_layers;j++){
            //std::cout<<"REGION!!!!!!   "<<region[k]<<std::endl;

            gemCollection["strip_dg_xy_r"+region[k]+"_"+stations[m]+"_"+layers[j]]=dbe->book2D("strip_dg_xy_r"+region[k]+"_"+stations[m]+"_"+layers[j],"Digi occupancy All: region "+region[k]+", station "+stations[m]+", layer "+layers[j]+";globalX [cm];globalY [cm]",120,-280,280,120,-280,280);
            gemCollection["strip_dg_xy_r"+region[k]+"_"+stations[m]+"_"+layers[j]+"_prompt"]=dbe->book2D("strip_dg_xy_r"+region[k]+"_"+stations[m]+"_"+layers[j]+"_prompt","Digi occupancy Prompt: region "+region[k]+", station "+stations[m]+", layer "+layers[j]+" ;globalX [cm];globalY [cm]",120,-280,280,120,-280,280);
            gemCollection["strip_dg_xy_r"+region[k]+"_"+stations[m]+"_"+layers[j]+"_NoPrompt"]=dbe->book2D("strip_dg_xy_r"+region[k]+"_"+stations[m]+"_"+layers[j]+"_NoPrompt","Digi occupancy NoPrompt: region "+region[k]+", station "+stations[m]+", layer "+layers[j]+"; globalX [cm];globalY [cm]",120,-280,280,120,-280,280);

            gemCollection["digiDX_r"+region[k]+"_"+stations[m]+"_"+layers[j]]=dbe->book1D("digiDX_r"+region[k]+"_"+stations[m]+"_"+layers[j],"x^{digi}_{sim} - x^{digi}_{rec} region "+region[k]+", station "+stations[m]+", layer "+layers[j]+"; x^{digi}_{sim} - x^{digi}_{rec} [cm]; entries",1000,-50,+50);

           gemCollection["digiDPhi_r"+region[k]+"_"+stations[m]+"_"+layers[j]]=dbe->book1D("digiDPhi_r"+region[k]+"_"+stations[m]+"_"+layers[j],"Phi^{digi}_{sim} - Phi^{digi}_{rec} region "+region[k]+", station "+stations[m]+", layer "+layers[j]+"; Phi^{digi}_{sim} - Phi^{digi}_{rec} [rad]; entries",10000,-10,+10);
            }

           }
          }


        dbe->setCurrentFolder(prompt_folder);
        gemCollection["strip_dg_zr_prompt"]=dbe->book2D("strip_dg_zr_prompt","Digi occupancy Prompt: region m1;globalZ [cm];globalR [cm]",80,515,555,120,20,160);
        // Prompt particles spectrum Vs R
        gemCollection["strip_dg_R_st1_prompt"]   =dbe->book1D("strip_dg_R_st1_prompt","Digi R distribution Prompt; globalR [cm]; Events; Station 1 ",240,130,400);
        gemCollection["strip_dg_R_st2_prompt"]   =dbe->book1D("strip_dg_R_st2_prompt","Digi R distribution Prompt; globalR [cm]; Events; Station2 ",240,130,400);
        gemCollection["strip_dg_R_st3_prompt"]   =dbe->book1D("strip_dg_R_st3_prompt","Digi R distribution Prompt; globalR [cm]; Events; Station3 ",240,130,400);
 
       gemCollection["strip_dg_R_st1_prompt_e"]   =dbe->book1D("strip_dg_R_st1_prompt_e","Digi R distribution Prompt electrons; globalR [cm]; Events: Station 1 ",240,130,400);
       gemCollection["strip_dg_R_st2_prompt_e"]   =dbe->book1D("strip_dg_R_st2_prompt_e","Digi R distribution Prompt electrons; globalR [cm]; Events; Station 2 ",240,130,400);
       gemCollection["strip_dg_R_st3_prompt_e"]   =dbe->book1D("strip_dg_R_st3_prompt_e","Digi R distribution Prompt electrons; globalR [cm]; Events; Station 3 ",240,130,400);

        gemCollection["strip_dg_R_st1_prompt_m"]   =dbe->book1D("strip_dg_R_st1_prompt_m","Digi R distribution Prompt muons; globalR [cm]; Events; Station 1 ",240,130,400);
        gemCollection["strip_dg_R_st2_prompt_m"]   =dbe->book1D("strip_dg_R_st2_prompt_m","Digi R distribution Prompt muons; globalR [cm]; Events; Station 2 ",240,130,400);
        gemCollection["strip_dg_R_st3_prompt_m"]   =dbe->book1D("strip_dg_R_st3_prompt_m","Digi R distribution Prompt muons; globalR [cm]; Events; Station 3 ",240,130,400);

        gemCollection["strip_dg_R_st1_prompt_h"]   =dbe->book1D("strip_dg_R_st1_prompt_h","Digi R distribution Prompt hadrons; globalR [cm]; Events; Station 1 ",240,130,400);
        gemCollection["strip_dg_R_st2_prompt_h"]   =dbe->book1D("strip_dg_R_st2_prompt_h","Digi R distribution Prompt hadrons; globalR [cm]; Events; Station 2 ",240,130,400);
        gemCollection["strip_dg_R_st3_prompt_h"]   =dbe->book1D("strip_dg_R_st3_prompt_h","Digi R distribution Prompt hadrons; globalR [cm]; Events; Station 3 ",240,130,400);
        // Prompt Timing
        gemCollection["strip_dg_st1_prompt_timing"]    =  dbe->book1D("strip_dg_st1_prompt_timing","Digi Timing Distribution Prompt; time [ns]; Events; Station 1",250,-150,100);
        gemCollection["strip_dg_st2_prompt_timing"]    =  dbe->book1D("strip_dg_st2_prompt_timing","Digi Timing Distribution Prompt; time [ns]; Events; Station 2",250,-150,100);
        gemCollection["strip_dg_st3_prompt_timing"]    =  dbe->book1D("strip_dg_st3_prompt_timing","Digi Timing Distribution Prompt; time [ns]; Events; Station 3",250,-150,100);

        gemCollection["strip_dg_st1_prompt_timing_e"]  =  dbe->book1D("strip_dg_st1_prompt_timing_e","Digi Timing Distribution Prompt electrons; time [ns]; Events; Station 1",250,-150,100);
        gemCollection["strip_dg_st2_prompt_timing_e"]  =  dbe->book1D("strip_dg_st2_prompt_timing_e","Digi Timing Distribution Prompt electrons; time [ns]; Events; Station 2",250,-150,100);
        gemCollection["strip_dg_st3_prompt_timing_e"]  =  dbe->book1D("strip_dg_st3_prompt_timing_e","Digi Timing Distribution Prompt electrons; time [ns]; Events; Station 3",250,-150,100);

        gemCollection["strip_dg_st1_prompt_timing_m"]  =  dbe->book1D("strip_dg_st1_prompt_timing_m","Digi Timing Distribution Prompt muons; time [ns]; Events; Station 1 ",250,-150,100);
        gemCollection["strip_dg_st2_prompt_timing_m"]  =  dbe->book1D("strip_dg_st2_prompt_timing_m","Digi Timing Distribution Prompt muons; time [ns]; Events; Station 2 ",250,-150,100);
        gemCollection["strip_dg_st3_prompt_timing_m"]  =  dbe->book1D("strip_dg_st3_prompt_timing_m","Digi Timing Distribution Prompt muons; time [ns]; Events; Station 3 ",250,-150,100);

        gemCollection["strip_dg_st1_prompt_timing_h"]  =  dbe->book1D("strip_dg_st1_prompt_timing_h","Digi Timing Distribution Prompt hadrons; time [ns]; Events; Station 1",250,-150,100);
        gemCollection["strip_dg_st2_prompt_timing_h"]  =  dbe->book1D("strip_dg_st2_prompt_timing_h","Digi Timing Distribution Prompt hadrons; time [ns]; Events; Station 2",250,-150,100);
        gemCollection["strip_dg_st3_prompt_timing_h"]  =  dbe->book1D("strip_dg_st3_prompt_timing_h","Digi Timing Distribution Prompt hadrons; time [ns]; Events; Station 3",250,-150,100);

        dbe->setCurrentFolder(noPrompt_folder);
        gemCollection["strip_dg_zr_NoPrompt"]=dbe->book2D("strip_dg_zr_NoPrompt","Digi occupancy NoPrompt: region m1;global|Z| [cm];globalR [cm]",80,515,555,120,20,160);
        // NoPrompt particles spectrum Vs R
        gemCollection["strip_dg_R_st1_NoPrompt"]   =dbe->book1D("strip_dg_R_st1_NoPrompt","Digi R distribution NoPrompt; globalR [cm]; Events; Station 1 ",240,130,320);
        gemCollection["strip_dg_R_st2_NoPrompt"]   =dbe->book1D("strip_dg_R_st2_NoPrompt","Digi R distribution NoPrompt; globalR [cm]; Events; Station 2 ",240,130,320); 
        gemCollection["strip_dg_R_st3_NoPrompt"]   =dbe->book1D("strip_dg_R_st3_NoPrompt","Digi R distribution NoPrompt; globalR [cm]; Events; Station 3 ",240,130,320);

        gemCollection["strip_dg_R_st1_NoPrompt_e"]   =dbe->book1D("strip_dg_R_st1_NoPrompt_e","Digi R distribution NoPrompt electrons; globalR [cm]; Events Station 1 ",240,130,320);
        gemCollection["strip_dg_R_st2_NoPrompt_e"]   =dbe->book1D("strip_dg_R_st2_NoPrompt_e","Digi R distribution NoPrompt electrons; globalR [cm]; Events Station 2 ",240,130,320);
       gemCollection["strip_dg_R_st3_NoPrompt_e"]   =dbe->book1D("strip_dg_R_st3_NoPrompt_e","Digi R distribution NoPrompt electrons; globalR [cm]; Events Station 3 ",240,130,320);

        gemCollection["strip_dg_R_st1_NoPrompt_n"]   =dbe->book1D("strip_dg_R_st1_NoPrompt_n","Digi R distribution NoPrompt neutrons; globalR [cm]; Events; Station 1 ",240,130,320);
        gemCollection["strip_dg_R_st2_NoPrompt_n"]   =dbe->book1D("strip_dg_R_st2_NoPrompt_n","Digi R distribution NoPrompt neutrons; globalR [cm]; Events; Station 2 ",240,130,320);
        gemCollection["strip_dg_R_st3_NoPrompt_n"]   =dbe->book1D("strip_dg_R_st3_NoPrompt_n","Digi R distribution NoPrompt neutrons; globalR [cm]; Events; Station 3 ",240,130,320);       

        gemCollection["strip_dg_R_st1_NoPrompt_g"]   =dbe->book1D("strip_dg_R_st1_NoPrompt_g","Digi R distribution NoPrompt gammas; globalR [cm]; Events; Station 1 ",240,130,320);
        gemCollection["strip_dg_R_st2_NoPrompt_g"]   =dbe->book1D("strip_dg_R_st2_NoPrompt_g","Digi R distribution NoPrompt gammas; globalR [cm]; Events; Station 2 ",240,130,320);
        gemCollection["strip_dg_R_st3_NoPrompt_g"]   =dbe->book1D("strip_dg_R_st3_NoPrompt_g","Digi R distribution NoPrompt gammas; globalR [cm]; Events; Station 3 ",240,130,320);

       // NoPrompt particles spectrum Vs eta
       gemCollection["strip_dg_eta_st1_NoPrompt"]   =dbe->book1D("strip_dg_eta_st1_NoPrompt","Digi Eta distribution NoPrompt; globalEta; Events; Station 1 ",240,1.6,2.4);
        gemCollection["strip_dg_eta_st2_NoPrompt"]   =dbe->book1D("strip_dg_eta_st2_NoPrompt","Digi Eta distribution NoPrompt; globalEta; Events; Station 2 ",240,1.6,2.4);
        gemCollection["strip_dg_eta_st3_NoPrompt"]   =dbe->book1D("strip_dg_eta_st3_NoPrompt","Digi Eta distribution NoPrompt; globalEta; Events; Station 3 ",240,1.6,2.4);

      gemCollection["strip_dg_eta_st1_NoPrompt_e"]   =dbe->book1D("strip_dg_eta_st1_NoPrompt_e","Digi Eta distribution NoPrompt electrons; globalEta; Events; Station 1 ",240,1.6,2.4);
        gemCollection["strip_dg_eta_st2_NoPrompt_e"]   =dbe->book1D("strip_dg_eta_st2_NoPrompt_e","Digi Eta distribution NoPrompt electrons; globalEta; Events; Station 2 ",240,1.6,2.4);
        gemCollection["strip_dg_eta_st3_NoPrompt_e"]   =dbe->book1D("strip_dg_eta_st3_NoPrompt_e","Digi Eta distribution NoPrompt electrons; globalEta; Events; Station 3 ",240,1.6,2.4);

      gemCollection["strip_dg_eta_st1_NoPrompt_n"]   =dbe->book1D("strip_dg_eta_st1_NoPrompt_n","Digi Eta distribution NoPrompt neutrons; globalEta; Events; Station 1 ",240,1.6,2.4);
        gemCollection["strip_dg_eta_st2_NoPrompt_n"]   =dbe->book1D("strip_dg_eta_st2_NoPrompt_n","Digi Eta distribution NoPrompt neutrons; globalEta; Events; Station 2 ",240,1.6,2.4);
        gemCollection["strip_dg_eta_st3_NoPrompt_n"]   =dbe->book1D("strip_dg_eta_st3_NoPrompt_n","Digi Eta distribution NoPrompt neutrons; globalEta; Events; Station 3 ",240,1.6,2.4);

      gemCollection["strip_dg_eta_st1_NoPrompt_g"]   =dbe->book1D("strip_dg_eta_st1_NoPrompt_g","Digi Eta distribution NoPrompt gammas; globalEta; Events; Station 1 ",240,1.6,2.4);
        gemCollection["strip_dg_eta_st2_NoPrompt_g"]   =dbe->book1D("strip_dg_eta_st2_NoPrompt_g","Digi Eta distribution NoPrompt gammas; globalEta; Events; Station 2 ",240,1.6,2.4);
        gemCollection["strip_dg_eta_st3_NoPrompt_g"]   =dbe->book1D("strip_dg_eta_st3_NoPrompt_g","Digi Eta distribution NoPrompt gammas; globalEta; Events; Station 3 ",240,1.6,2.4);

        // NoPrompt Timing
        gemCollection["strip_dg_timing_st1_NoPrompt"]    =  dbe->book1D("strip_dg_timing_st1_NoPrompt","Digi Timing Distribution non-Prompt; time [ns]; Events; Station 1",250,-150,100);
        gemCollection["strip_dg_timing_st2_NoPrompt"]    =  dbe->book1D("strip_dg_timing_st2_NoPrompt","Digi Timing Distribution non-Prompt; time [ns]; Events; Station 2",250,-150,100);
        gemCollection["strip_dg_timing_st3_NoPrompt"]    =  dbe->book1D("strip_dg_timing_st3_NoPrompt","Digi Timing Distribution non-Prompt; time [ns]; Events; Station 3",250,-150,100);

        gemCollection["strip_dg_timing_st1_NoPrompt_e"]  =  dbe->book1D("strip_dg_timing_st1_NoPrompt_e","Digi Timing Distribution Prompt electrons; time [ns]; Events; Station 1",250,-150,100);
        gemCollection["strip_dg_timing_st2_NoPrompt_e"]  =  dbe->book1D("strip_dg_timing_st2_NoPrompt_e","Digi Timing Distribution Prompt electrons; time [ns]; Events; Station 2",250,-150,100);
        gemCollection["strip_dg_timing_st3_NoPrompt_e"]  =  dbe->book1D("strip_dg_timing_st3_NoPrompt_e","Digi Timing Distribution Prompt electrons; time [ns]; Events; Station 3",250,-150,100);

        gemCollection["strip_dg_timing_st1_NoPrompt_n"]  =  dbe->book1D("strip_dg_timing_st1_NoPrompt_m","Digi Timing Distribution Prompt neutrons; time [ns]; Events: Station 1",250,-150,100);
        gemCollection["strip_dg_timing_st2_NoPrompt_n"]  =  dbe->book1D("strip_dg_timing_st2_NoPrompt_m","Digi Timing Distribution Prompt neutrons; time [ns]; Events: Station 2",250,-150,100);
        gemCollection["strip_dg_timing_st3_NoPrompt_n"]  =  dbe->book1D("strip_dg_timing_st3_NoPrompt_m","Digi Timing Distribution Prompt neutrons; time [ns]; Events: Station 3",250,-150,100);

        gemCollection["strip_dg_timing_st1_NoPrompt_g"]  =  dbe->book1D("strip_dg_timing_st1_NoPrompt_h","Digi Timing Distribution Prompt gammas; time [ns]; Events; Station 1",250,-150,100);
        gemCollection["strip_dg_timing_st2_NoPrompt_g"]  =  dbe->book1D("strip_dg_timing_st2_NoPrompt_h","Digi Timing Distribution Prompt gammas; time [ns]; Events; Station 2",250,-150,100);
       gemCollection["strip_dg_timing_st3_NoPrompt_g"]  =  dbe->book1D("strip_dg_timing_st3_NoPrompt_h","Digi Timing Distribution Prompt gammas; time [ns]; Events; Station 3",250,-150,100);   


    }
}


// ------------ method called when ending the processing of a run  ------------

void MuonNewGEMDigis::endRun(edm::Run const&, edm::EventSetup const&)
{
    if (EffSaveRootFile_) dbe->save(EffRootFileName_);
}


// ------------ method called when starting to processes a luminosity block  ------------
/*
void
MuonNewGEMDigis::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when ending the processing of a luminosity block  ------------
/*
void
MuonNewGEMDigis::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/

bool MuonNewGEMDigis::isGEMDigiMatched(MyGEMDigi gem_dg, MyGEMSimHit gem_sh)
{

    Int_t gem_region = gem_dg.region;
    Int_t gem_layer = gem_dg.layer;
    Int_t gem_station = gem_dg.station;
    Int_t gem_chamber = gem_dg.chamber;
    Int_t gem_roll = gem_dg.roll;
    //Int_t me0_strip = me0_dg.strip;

    Int_t gem_sh_region = gem_sh.region;
    Int_t gem_sh_layer = gem_sh.layer;
    Int_t gem_sh_station = gem_sh.station;
    Int_t gem_sh_chamber = gem_sh.chamber;
    Int_t gem_sh_roll = gem_sh.roll;
    //Int_t me0_sh_strip = me0_sh.strip;

    bool cond1, cond2;

    if(gem_sh_region == gem_region && gem_sh_layer == gem_layer && gem_sh_station == gem_station) cond1 = true;
    else cond1 = false;
    if(gem_sh_chamber == gem_chamber && gem_sh_roll == gem_roll) cond2 = true;
    else cond2 = false;

    return (cond1 & cond2);

}

bool MuonNewGEMDigis::isSimTrackGood(const SimTrack &t)
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
MuonNewGEMDigis::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(MuonNewGEMDigis);
