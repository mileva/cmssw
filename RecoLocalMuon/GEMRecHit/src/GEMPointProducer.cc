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

//#include "RecoLocalMuon/RPCRecHit/interface/RPCPointProducer.h"
#include "RecoLocalMuon/GEMRecHit/interface/GEMPointProducer.h"

// system include files

#include <memory>
#include <ctime>

// user include files

//RPCPointProducer::RPCPointProducer(const edm::ParameterSet& iConfig)
GEMPointProducer::GEMPointProducer(const edm::ParameterSet& iConfig)
{
  cscSegments=iConfig.getParameter<edm::InputTag>("cscSegments");
//  dt4DSegments=iConfig.getParameter<edm::InputTag>("dt4DSegments");
  tracks=iConfig.getParameter<edm::InputTag>("tracks");

  debug=iConfig.getUntrackedParameter<bool>("debug",false);
//  incldt=iConfig.getUntrackedParameter<bool>("incldt",true);
  inclcsc=iConfig.getUntrackedParameter<bool>("inclcsc",true);
  incltrack=iConfig.getUntrackedParameter<bool>("incltrack",true);
  MinCosAng=iConfig.getUntrackedParameter<double>("MinCosAng",0.95);
  MaxD=iConfig.getUntrackedParameter<double>("MaxD",80.);
  MaxDrb4=iConfig.getUntrackedParameter<double>("MaxDrb4",150.);
  ExtrapolatedRegion=iConfig.getUntrackedParameter<double>("ExtrapolatedRegion",0.5);

//  produces<RPCRecHitCollection>("RPCDTExtrapolatedPoints");
//  produces<RPCRecHitCollection>("RPCCSCExtrapolatedPoints");
  produces<GEMRecHitCollection>("GEMCSCExtrapolatedPoints");
//  produces<RPCRecHitCollection>("RPCTrackExtrapolatedPoints");
  produces<GEMRecHitCollection>("GEMTrackExtrapolatedPoints");
  trackTransformerParam = iConfig.getParameter<edm::ParameterSet>("TrackTransformer");  
}


//RPCPointProducer::~RPCPointProducer(){
GEMPointProducer::~GEMPointProducer(){

}

//void RPCPointProducer::produce(edm::Event& iEvent, const edm::EventSetup& iSetup){
void GEMPointProducer::produce(edm::Event& iEvent, const edm::EventSetup& iSetup){
  /*	rumi:not commented by me
  struct timespec start_time, stop_time;
  time_t fs;
  time_t fn;
  time_t ls;
  time_t ln;
  clock_gettime(CLOCK_REALTIME, &start_time);  
  */

/*
  if(incldt){
    edm::Handle<DTRecSegment4DCollection> all4DSegments;
    iEvent.getByLabel(dt4DSegments, all4DSegments);
    if(all4DSegments.isValid()){
      DTSegtoRPC DTClass(all4DSegments,iSetup,iEvent,debug,ExtrapolatedRegion);
      std::auto_ptr<RPCRecHitCollection> TheDTPoints(DTClass.thePoints());     
      iEvent.put(TheDTPoints,"RPCDTExtrapolatedPoints"); 
    }else{
      if(debug) std::cout<<"RPCHLT Invalid DTSegments collection"<<std::endl;
    }
  }
*/

  if(inclcsc){
    edm::Handle<CSCSegmentCollection> allCSCSegments;
    iEvent.getByLabel(cscSegments, allCSCSegments);
    if(allCSCSegments.isValid()){
//      CSCSegtoRPC CSCClass(allCSCSegments,iSetup,iEvent,debug,ExtrapolatedRegion);
      CSCSegtoGEM CSCClass(allCSCSegments,iSetup,iEvent,debug,ExtrapolatedRegion);
//      std::auto_ptr<RPCRecHitCollection> TheCSCPoints(CSCClass.thePoints());  
      std::auto_ptr<GEMRecHitCollection> TheCSCPoints(CSCClass.thePoints());  
//      iEvent.put(TheCSCPoints,"RPCCSCExtrapolatedPoints"); 
      iEvent.put(TheCSCPoints,"GEMCSCExtrapolatedPoints"); 
    }else{
//      if(debug) std::cout<<"RPCHLT Invalid CSCSegments collection"<<std::endl;
      if(debug) std::cout<<"GEM Invalid CSCSegments collection"<<std::endl;
    }
  }
  if(incltrack){
    edm::Handle<reco::TrackCollection> alltracks;
    iEvent.getByLabel(tracks,alltracks);
    if(!(alltracks->empty())){
//      TracktoRPC TrackClass(alltracks,iSetup,iEvent,debug,trackTransformerParam,tracks);
      TracktoGEM TrackClass(alltracks,iSetup,iEvent,debug,trackTransformerParam,tracks);
//      std::auto_ptr<RPCRecHitCollection> TheTrackPoints(TrackClass.thePoints());
      std::auto_ptr<GEMRecHitCollection> TheTrackPoints(TrackClass.thePoints());
//      iEvent.put(TheTrackPoints,"RPCTrackExtrapolatedPoints");
      iEvent.put(TheTrackPoints,"GEMTrackExtrapolatedPoints");
    }else{
//      std::cout<<"RPCHLT Invalid Tracks collection"<<std::endl;
      std::cout<<"GEM Invalid Tracks collection"<<std::endl;
    }
  }
 
}

// ------------ method called once each job just before starting event loop  ------------
void 
//RPCPointProducer::beginJob()
GEMPointProducer::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
//RPCPointProducer::endJob() {
GEMPointProducer::endJob() {
}


