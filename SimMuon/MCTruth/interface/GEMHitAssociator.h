#ifndef MCTruth_GEMHitAssociator_h
#define MCTruth_GEMHitAssociator_h

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/Common/interface/Handle.h"
#include "SimDataFormats/EncodedEventId/interface/EncodedEventId.h"
#include "SimDataFormats/TrackingHit/interface/PSimHit.h"
#include "SimDataFormats/TrackingHit/interface/PSimHitContainer.h"
#include "DataFormats/TrackingRecHit/interface/TrackingRecHit.h"
#include "DataFormats/MuonDetId/interface/GEMDetId.h"
#include "SimDataFormats/GEMDigiSimLink/interface/GEMDigiSimLink.h"

#include <vector>
#include <map>
#include <string>
#include <set>

#include "SimDataFormats/CrossingFrame/interface/CrossingFrame.h"
#include "SimDataFormats/CrossingFrame/interface/MixCollection.h"
#include "DataFormats/DetId/interface/DetId.h"
#include "DataFormats/MuonDetId/interface/MuonSubdetId.h"
#include "DataFormats/GEMDigi/interface/GEMDigiCollection.h"
#include "DataFormats/GEMRecHit/interface/GEMRecHitCollection.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "Geometry/Records/interface/MuonGeometryRecord.h"
#include "Geometry/GEMGeometry/interface/GEMGeometry.h"
#include "DataFormats/Common/interface/DetSetVector.h"

class GEMHitAssociator {

 public:

   typedef edm::DetSetVector<GEMDigiSimLink> GEMDigiSimLinks;
//   typedef edm::DetSet<GEMDigiSimLink> LayerLinks;
   typedef std::pair<uint32_t, EncodedEventId> SimHitIdpr;

  // Constructor with configurable parameters
  GEMHitAssociator(const edm::Event&, const edm::EventSetup&, const edm::ParameterSet&); 

  // Destructor
  ~GEMHitAssociator(){}

   std::vector<SimHitIdpr> associateRecHit(const TrackingRecHit & hit);
   std::set<GEMDigiSimLink> findGEMDigiSimLink(uint32_t gemDetId, int strip, int bx);
   //   const PSimHit* linkToSimHit(GEMDigiSimLink link);


 private:
   bool useGEMs_;
   edm::Handle< edm::DetSetVector<GEMDigiSimLink> > _thelinkDigis;
   edm::InputTag GEMdigisimlinkTag;
 
   bool crossingframe;
   edm::InputTag GEMsimhitsTag;
   edm::InputTag GEMsimhitsXFTag;

   std::map<unsigned int, edm::PSimHitContainer> _SimHitMap;

//   const DigiSimLinks * theDigiSimLinks;

 };

#endif



