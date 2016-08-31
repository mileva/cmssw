#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
//#include <DataFormats/DTRecHit/interface/DTRecSegment4DCollection.h>
#include <DataFormats/CSCRecHit/interface/CSCSegmentCollection.h>

#include "FWCore/Framework/interface/ESHandle.h"
//#include <DataFormats/RPCRecHit/interface/RPCRecHit.h>
#include <DataFormats/GEMRecHit/interface/GEMRecHit.h>
//#include "DataFormats/MuonDetId/interface/RPCDetId.h"
#include "DataFormats/MuonDetId/interface/GEMDetId.h"
//#include "RecoLocalMuon/RPCRecHit/interface/DTSegtoRPC.h"
//#include "RecoLocalMuon/RPCRecHit/interface/CSCSegtoRPC.h"
#include "RecoLocalMuon/GEMRecHit/interface/CSCSegtoGEM.h"
//#include "RecoLocalMuon/RPCRecHit/interface/TracktoRPC.h" 
#include "RecoLocalMuon/GEMRecHit/interface/TracktoGEM.h" 	//rumi: da se implementira

//
// class decleration
//

//class RPCPointProducer : public edm::EDProducer {
class GEMPointProducer : public edm::EDProducer {
   public:
//      explicit RPCPointProducer(const edm::ParameterSet&);
      explicit GEMPointProducer(const edm::ParameterSet&);
//      ~RPCPointProducer();
      ~GEMPointProducer();
      edm::InputTag cscSegments;
//      edm::InputTag dt4DSegments;
      edm::InputTag tracks;
   private:
      virtual void beginJob() ;
      virtual void produce(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
//      bool incldt;
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

