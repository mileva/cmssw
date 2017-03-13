#ifndef DataFormats_ME0TrivRecHitCollection_H
#define DataFormats_ME0TrivRecHitCollection_H

/** \class ME0TrivRecHitCollection
 *  Collection of ME0TrivRecHit for storage in the event
 *
 *  \author M. Maggi - INFN Bari
 */


#include "DataFormats/MuonDetId/interface/ME0DetId.h"
#include "DataFormats/GEMRecHit/interface/ME0RecHit.h"
#include "DataFormats/Common/interface/RangeMap.h"
#include "DataFormats/Common/interface/ClonePolicy.h"
#include "DataFormats/Common/interface/OwnVector.h"
#include <functional>

typedef edm::RangeMap <ME0DetId,
		       edm::OwnVector<ME0TrivRecHit,edm::ClonePolicy<ME0TrivRecHit> >,
		       edm::ClonePolicy<ME0TrivRecHit> > ME0TrivRecHitCollection;


#endif




