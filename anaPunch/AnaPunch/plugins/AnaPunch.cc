// -*- C++ -*-
//
// Package:    AnaPunch
// Class:      AnaPunch
// 
/**\class AnaPunch AnaPunch.cc anaPunch/AnaPunch/plugins/AnaPunch.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Roumyana Mileva Hadjiiska
//         Created:  Tue, 01 Apr 2014 07:57:54 GMT
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

#include "SimDataFormats/TrackingHit/interface/PSimHitContainer.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "TH1F.h"



//
// class declaration
//

class AnaPunch : public edm::EDAnalyzer {
   public:
      explicit AnaPunch(const edm::ParameterSet&);
      ~AnaPunch();

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

  TH1F *histoMomentum;
  TH1F *histoEnergyLoss;
  TH1F *histoTimeOfFlight;
  TH1F *histoThetaAtEntry;
  TH1F *histoPhiAtEntry;

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
AnaPunch::AnaPunch(const edm::ParameterSet& iConfig)

{
   //now do what ever initialization is needed

}


AnaPunch::~AnaPunch()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
AnaPunch::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
/////test punch
 edm::Handle<PSimHitContainer> simHit;
 iEvent.getByLabel("g4SimHits", "MuonGEMHits", simHit);
// iEvent.getByLabel("g4SimHits", "MuonME0Hits", simHit);
 PSimHitContainer::const_iterator simIt;

  for (simIt = simHit->begin(); simIt != simHit->end(); simIt++)
  {
    {
      std::cout << "particle type: pdg Id = " << simIt->particleType() << std::endl;
      std::cout << "track Id = " << simIt->trackId() << std::endl;
      std::cout << "process type = " << simIt->processType() << std::endl;
    }
    if(abs(simIt->particleType())==13)
      {
        //take all muons which are Not coming from primary interactions
        if(!(simIt->processType() == 2))
         {
           histoMomentum->Fill(simIt->pabs());
           histoEnergyLoss->Fill(simIt->energyLoss());
           histoTimeOfFlight->Fill(simIt->tof());
           histoThetaAtEntry->Fill(simIt->thetaAtEntry());
           histoPhiAtEntry->Fill(simIt->phiAtEntry());
         }
      }
    

  }


/////test punch end



#ifdef THIS_IS_AN_EVENT_EXAMPLE
   Handle<ExampleData> pIn;
   iEvent.getByLabel("example",pIn);
#endif
   
#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
   ESHandle<SetupData> pSetup;
   iSetup.get<SetupRecord>().get(pSetup);
#endif
}


// ------------ method called once each job just before starting event loop  ------------
void 
AnaPunch::beginJob()
{
  edm::Service<TFileService> fs;
  histoMomentum = fs->make<TH1F>("simHit_momentum", "simHit_momentum", 500, 0., 50.);
  histoEnergyLoss = fs->make<TH1F>("simHit_energyLoss", "simHit_energyLoss", 1000, 0., 1.);
  histoTimeOfFlight = fs->make<TH1F> ("simHit_TimeOfFlight", "simHit_TimeOfFlight", 5000, 0., 50.);
  histoThetaAtEntry = fs->make<TH1F> ("thetaAtEntry", "thetaAtEntry", 60, -3., 3.);
  histoPhiAtEntry = fs->make<TH1F> ("phiAtEntry", "phiAtEntry", 140, -7., 7.);
}

// ------------ method called once each job just after ending the event loop  ------------
void 
AnaPunch::endJob() 
{
}

// ------------ method called when starting to processes a run  ------------
/*
void 
AnaPunch::beginRun(edm::Run const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when ending the processing of a run  ------------
/*
void 
AnaPunch::endRun(edm::Run const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when starting to processes a luminosity block  ------------
/*
void 
AnaPunch::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when ending the processing of a luminosity block  ------------
/*
void 
AnaPunch::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
AnaPunch::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(AnaPunch);
