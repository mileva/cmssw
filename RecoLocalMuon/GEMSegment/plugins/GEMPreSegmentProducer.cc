/** \file GEMPreSegmentProducer.cc
 *
 */

#include <RecoLocalMuon/GEMSegment/plugins/GEMPreSegmentProducer.h>
#include <RecoLocalMuon/GEMSegment/plugins/GEMPreRecoSegmentBuilder.h>

#include <DataFormats/Common/interface/Handle.h>
#include <FWCore/Framework/interface/ESHandle.h>
#include <FWCore/MessageLogger/interface/MessageLogger.h> 

#include <Geometry/Records/interface/MuonGeometryRecord.h>

#include <DataFormats/GEMRecHit/interface/GEMRecHitCollection.h>
#include <DataFormats/GEMRecHit/interface/GEMSegmentCollection.h>
#include <DataFormats/GEMRecHit/interface/GEMSegment.h>

GEMPreSegmentProducer::GEMPreSegmentProducer(const edm::ParameterSet& ps) : iev(0) {
	
    theGEMRecHitPreRecoToken = consumes<GEMRecHitCollection>(ps.getParameter<edm::InputTag>("gemRecHitPreRecoLabel"));
    segmentBuilder_ = std::unique_ptr<GEMPreRecoSegmentBuilder>(new GEMPreRecoSegmentBuilder(ps)); // pass on the Parameter Set

    // register what this produces
    produces<GEMSegmentCollection>();
}

GEMPreSegmentProducer::~GEMPreSegmentProducer() {}

void GEMPreSegmentProducer::produce(edm::Event& ev, const edm::EventSetup& setup) {

   LogDebug("GEMPreSegmentProducer") << "start producing segments for " << ++iev << "th event with csc data";
	
    // find the geometry (& conditions?) for this event & cache it in the builder
    edm::ESHandle<GEMGeometry> gemg;
    setup.get<MuonGeometryRecord>().get(gemg);
    const GEMGeometry* mgeom = &*gemg;
    segmentBuilder_->setGeometry(mgeom);
  
    
    // get the collection of GEMRecHit
    edm::Handle<GEMRecHitCollection> gemRecHitsPreReco;
    ev.getByToken(theGEMRecHitPreRecoToken,gemRecHitsPreReco);


    // create empty collection of Segments for timing
    std::auto_ptr<GEMSegmentCollection> ocT( new GEMSegmentCollection );


    // fill the collection
    segmentBuilder_->build(gemRecHitsPreReco.product(), *ocT); //@@ FILL ocT
 

    // put collection in event
    ev.put(ocT);
}
