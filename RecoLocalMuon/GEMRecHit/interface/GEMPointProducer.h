#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include <DataFormats/CSCRecHit/interface/CSCSegmentCollection.h>
#include "FWCore/Framework/interface/ESHandle.h"
#include <DataFormats/GEMRecHit/interface/GEMRecHit.h>
#include "DataFormats/MuonDetId/interface/GEMDetId.h"
#include "RecoLocalMuon/GEMRecHit/interface/CSCSegtoGEM.h"
#include "RecoLocalMuon/GEMRecHit/interface/TracktoGEM.h"

//
// class decleration
//

class GEMPointProducer : public edm::EDProducer {
   public:
      explicit GEMPointProducer(const edm::ParameterSet&);
      ~GEMPointProducer();
      edm::InputTag cscSegments;
      edm::InputTag tracks;
   private:
      virtual void beginJob() ;
      virtual void produce(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      bool inclcsc;
      bool incltrack; 
      bool debug;
      double MinCosAng;
      double MaxD;
      double MaxDrb4;
      double MaxDistanceBetweenSegments;
      double ExtrapolatedRegion;
      edm::ParameterSet trackTransformerParam;
      edm::ParameterSet serviceParameters;
      // ----------member data ---------------------------
};

