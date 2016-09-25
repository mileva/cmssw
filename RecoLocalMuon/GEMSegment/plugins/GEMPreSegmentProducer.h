#ifndef GEMRecHit_GEMPreSegmentProducer_h
#define GEMRecHit_GEMPreSegmentProducer_h

/** \class GEMSegmentProducer derived by CSCSegmentProducer 
 * Produces a collection of GEMSegment's in endcap muon GEMs. 
 *
 * \author Piet Verwilligen
 */

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include <DataFormats/GEMRecHit/interface/GEMRecHitCollection.h>

class GEMPreRecoSegmentBuilder; 

class GEMPreSegmentProducer : public edm::EDProducer {
public:
    /// Constructor
    explicit GEMPreSegmentProducer(const edm::ParameterSet&);
    /// Destructor
    ~GEMPreSegmentProducer();
    /// Produce the GEMSegment collection
    virtual void produce(edm::Event&, const edm::EventSetup&);

private:
    int iev; // events through
    edm::EDGetTokenT<GEMRecHitCollection> theGEMRecHitPreRecoToken;
    std::unique_ptr<GEMPreRecoSegmentBuilder> segmentBuilder_;
};

#endif
