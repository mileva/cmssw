// -*- C++ -*-
//
// Package:    GEMPointProducer
// Class:      GEMPointProducer
// 
/**\class GEMPointProducer GEMPointProducer.cc Analysis/GEMPointProducer/src/GEMPointProducer.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Camilo Andres Carrillo Montoya
//         Created:  Wed Sep 16 14:56:18 CEST 2009
// $Id: RPCPointProducer.cc,v 1.9 2010/10/19 19:18:22 wmtan Exp $
//Modified for GEM: Roumyna Hadjiiska
// $Id: GEMPointProducer.cc,v 1.0 2016/09/01 19:18:22 wmtan Exp $
//
//

#include "RecoLocalMuon/GEMRecHit/interface/GEMPointProducer.h"
// system include files
#include <memory>
#include <ctime>
// user include files

GEMPointProducer::GEMPointProducer(const edm::ParameterSet& iConfig)
{
  cscSegments=iConfig.getParameter<edm::InputTag>("cscSegments");
  tracks=iConfig.getParameter<edm::InputTag>("tracks");
  debug=iConfig.getUntrackedParameter<bool>("debug",false);
  inclcsc=iConfig.getUntrackedParameter<bool>("inclcsc",true);
  incltrack=iConfig.getUntrackedParameter<bool>("incltrack",true);
  MinCosAng=iConfig.getUntrackedParameter<double>("MinCosAng",0.95);
  MaxD=iConfig.getUntrackedParameter<double>("MaxD",80.);
  MaxDrb4=iConfig.getUntrackedParameter<double>("MaxDrb4",150.);
  ExtrapolatedRegion=iConfig.getUntrackedParameter<double>("ExtrapolatedRegion",0.5);
  produces<GEMRecHitCollection>("GEMCSCExtrapolatedPoints");
  produces<GEMRecHitCollection>("GEMTrackExtrapolatedPoints");
  trackTransformerParam = iConfig.getParameter<edm::ParameterSet>("TrackTransformer");  
}

GEMPointProducer::~GEMPointProducer(){
}

void GEMPointProducer::produce(edm::Event& iEvent, const edm::EventSetup& iSetup){

  if(inclcsc){
    edm::Handle<CSCSegmentCollection> allCSCSegments;
    iEvent.getByLabel(cscSegments, allCSCSegments);
    if(allCSCSegments.isValid()){
      CSCSegtoGEM CSCClass(allCSCSegments,iSetup,iEvent,debug,ExtrapolatedRegion);
      std::auto_ptr<GEMRecHitCollection> TheCSCPoints(CSCClass.thePoints());  
      iEvent.put(TheCSCPoints,"GEMCSCExtrapolatedPoints"); 
    }else{
      if(debug) std::cout<<"GEM Invalid CSCSegments collection"<<std::endl;
    }
  }
  if(incltrack){
    edm::Handle<reco::TrackCollection> alltracks;
    iEvent.getByLabel(tracks,alltracks);
    if(!(alltracks->empty())){
      TracktoGEM TrackClass(alltracks,iSetup,iEvent,debug,trackTransformerParam,tracks);
      std::auto_ptr<GEMRecHitCollection> TheTrackPoints(TrackClass.thePoints());
      iEvent.put(TheTrackPoints,"GEMTrackExtrapolatedPoints");
    }else{
      std::cout<<"GEM Invalid Tracks collection"<<std::endl;
    }
  }
 
}

// ------------ method called once each job just before starting event loop  ------------
void 
GEMPointProducer::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
//RPCPointProducer::endJob() {
GEMPointProducer::endJob() {
}


