#ifndef  TRACKTOGEM_H
#define  TRACKTOGEM_H

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/TrackReco/interface/TrackExtraFwd.h"
#include "DataFormats/MuonReco/interface/MuonTrackLinks.h"
#include "DataFormats/MuonReco/interface/MuonFwd.h"
#include "DataFormats/MuonReco/interface/Muon.h"
#include "TrackingTools/PatternTools/interface/Trajectory.h"
#include "TrackingTools/PatternTools/interface/TrajTrackAssociation.h"
#include "TrackingTools/GeomPropagators/interface/Propagator.h"
#include "TrackingTools/TransientTrack/interface/TransientTrackBuilder.h"
#include "TrackingTools/Records/interface/TransientTrackRecord.h"
#include "TrackingTools/Records/interface/TrackingComponentsRecord.h"
#include "TrackingTools/TransientTrack/interface/TransientTrack.h"
#include "TrackingTools/TrajectoryState/interface/FreeTrajectoryState.h"
#include "TrackingTools/TrajectoryState/interface/TrajectoryStateTransform.h"
#include "RecoMuon/DetLayers/interface/MuonDetLayerGeometry.h"
#include "RecoMuon/Records/interface/MuonRecoGeometryRecord.h"
#include "RecoMuon/MeasurementDet/interface/MuonDetLayerMeasurements.h"
#include "RecoMuon/TransientTrackingRecHit/interface/MuonTransientTrackingRecHit.h"
#include "DataFormats/GEMRecHit/interface/GEMRecHit.h"
#include "DataFormats/GEMRecHit/interface/GEMRecHitCollection.h"
#include "DataFormats/Common/interface/Ref.h"
#include "Geometry/TrackerGeometryBuilder/interface/TrackerGeometry.h"
#include "Geometry/GEMGeometry/interface/GEMGeometry.h"
#include "Geometry/CommonDetUnit/interface/GeomDetType.h"
#include "Geometry/GEMGeometry/interface/GEMEtaPartition.h"
#include "Geometry/CSCGeometry/interface/CSCGeometry.h"
#include "Geometry/CommonTopologies/interface/RectangularStripTopology.h"
#include "Geometry/CommonTopologies/interface/TrapezoidalStripTopology.h"
#include "TrackingTools/TrackRefitter/interface/TrackTransformerForCosmicMuons.h"
#include "TrackingTools/TrackRefitter/interface/TrackTransformerBase.h"
#include "TrackingTools/TrackRefitter/interface/TrackTransformer.h"

using reco::MuonCollection;
using reco::TrackCollection;
typedef std::vector<Trajectory> Trajectories;

class TracktoGEM {
public:

  explicit TracktoGEM(edm::Handle<reco::TrackCollection> alltracks,const edm::EventSetup& iSetup, const edm::Event& iEvent,bool debug, const edm::ParameterSet& iConfig,edm::InputTag& tracklabel);

  ~TracktoGEM();
  GEMRecHitCollection* thePoints(){return _ThePoints;}
  bool ValidGEMSurface(GEMDetId gemid, LocalPoint LocalP, const edm::EventSetup& iSetup);

private:
  GEMRecHitCollection* _ThePoints;
  edm::OwnVector<GEMRecHit> GEMPointVector;
  double MaxD;

 TrackTransformerBase *theTrackTransformer;
 edm::ESHandle<Propagator> thePropagator;
};

class CSCStationIndex2{
public:
  CSCStationIndex2():_region(0),_station(0),_ring(0),_chamber(0){}
  CSCStationIndex2(int region, int station, int ring, int chamber):
    _region(region),
    _station(station),
    _ring(ring),
    _chamber(chamber){}
  ~CSCStationIndex2(){}
  int region() const {return _region;}
  int station() const {return _station;}
  int ring() const {return _ring;}
  int chamber() const {return _chamber;}
  bool operator<(const CSCStationIndex2& cscind) const{
    if(cscind.region()!=this->region())
      return cscind.region()<this->region();
    else if(cscind.station()!=this->station())
      return cscind.station()<this->station();
    else if(cscind.ring()!=this->ring())
      return cscind.ring()<this->ring();
    else if(cscind.chamber()!=this->chamber())
      return cscind.chamber()<this->chamber();
    return false;
  }

private:
  int _region;
  int _station;
  int _ring;  
  int _chamber;
};

class ObjectMap2CSC{
public:
  static ObjectMap2CSC* GetInstance(const edm::EventSetup& iSetup);
  std::set<GEMDetId> GetRolls(CSCStationIndex2 cscstationindex){return mapInstance->rollstoreCSC[cscstationindex];}
  std::map<CSCStationIndex2,std::set<GEMDetId> > rollstoreCSC;
  ObjectMap2CSC(const edm::EventSetup& iSetup);
private:
  static ObjectMap2CSC* mapInstance;
}; 

#endif
