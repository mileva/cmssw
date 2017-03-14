#ifndef RecoLocalMuon_ME0TrivRecHitBaseAlgo_H
#define RecoLocalMuon_ME0TrivRecHitBaseAlgo_H

/** \class ME0TrivRecHitBaseAlgo
 *  Abstract algorithmic class to compute Rec Hit
 *  from a ME0 realistic digi
 *
 *  \author M. Maggi -- INFN Bari
 *  \modified R. Hadjiiska -- INRNE Sofia
 */


#include "DataFormats/GeometryVector/interface/LocalPoint.h"
#include "DataFormats/GeometrySurface/interface/LocalError.h"
#include "DataFormats/GeometryVector/interface/GlobalPoint.h"
#include "DataFormats/GEMDigi/interface/ME0DigiCollection.h"
#include "DataFormats/GEMRecHit/interface/ME0TrivRecHit.h"
#include "DataFormats/Common/interface/OwnVector.h"

#include "RecoLocalMuon/GEMRecHit/src/ME0EtaPartitionMask.h"
#include "RecoLocalMuon/GEMRecHit/src/ME0MaskReClusterizer.h"

class ME0Cluster;
class ME0EtaPartition;
class ME0DetId;

namespace edm {
  class ParameterSet;
  class EventSetup;
}


class ME0TrivRecHitBaseAlgo {

 public:
  
  /// Constructor
  ME0TrivRecHitBaseAlgo(const edm::ParameterSet& config);

  /// Destructor
  virtual ~ME0TrivRecHitBaseAlgo();  

  /// Pass the Event Setup to the algo at each event
  virtual void setES(const edm::EventSetup& setup) = 0;

  /// Build all hits in the range associated to the me0Id, at the 1st step.
  virtual edm::OwnVector<ME0TrivRecHit> reconstruct(const ME0EtaPartition& roll,
						const ME0DetId& me0Id,
						const ME0DigiCollection::Range& digiRange,
                                                const EtaPartitionMask& mask);

  /// standard local recHit computation
  virtual bool compute(const ME0EtaPartition& roll,
                       const ME0Cluster& cl,
                       LocalPoint& Point,
                       LocalError& error) const = 0;


  /// local recHit computation accounting for track direction and 
  /// absolute position
  virtual bool compute(const ME0EtaPartition& roll,
		       const ME0Cluster& cl,
                       const float& angle,
                       const GlobalPoint& globPos, 
                       LocalPoint& Point,
                       LocalError& error) const = 0;
};
#endif
