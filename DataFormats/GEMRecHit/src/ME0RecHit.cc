/*
 *  See header file for a description of this class.
 *
 *  $Date: 2013/04/24 16:54:24 $
 *  $Revision: 1.1 $
 *  \author M. Maggi -- INFN Bari
 */


#include "DataFormats/GEMRecHit/interface/ME0RecHit.h"


ME0RecHit::ME0RecHit(const ME0DetId& me0Id, float tof) :  RecHit2DLocalPos(me0Id),
  theME0Id(me0Id), theTOF(tof), theLocalPosition(), theLocalError()
{
}

ME0RecHit::ME0RecHit() :  RecHit2DLocalPos(),
  theME0Id(), theTOF(0.), theLocalPosition(), theLocalError()
{
}


ME0RecHit::ME0RecHit(const ME0DetId& me0Id, float tof, const LocalPoint& pos) :  RecHit2DLocalPos(me0Id),
   theME0Id(me0Id), theTOF(tof), theLocalPosition(pos), theLocalError()
{
}

// Constructor from a local position and error, wireId and digi time.
ME0RecHit::ME0RecHit(const ME0DetId& me0Id,
		     float tof, 
		     const LocalPoint& pos,
		     const LocalError& err) :  RecHit2DLocalPos(me0Id),
  theME0Id(me0Id), theTOF(tof), theLocalPosition(pos), theLocalError(err)
{
}

//rumi: constructors for me0 real rechit
ME0RecHit::ME0RecHit(const ME0DetId& me0Id, int bx) :  RecHit2DLocalPos(me0Id),
  theME0Id(me0Id),  theLocalPosition(), theLocalError(), theBx(bx),theFirstStrip(999), theClusterSize(999), RealDigi(true) 
{
}

ME0RecHit::ME0RecHit(const ME0DetId& me0Id, int bx, const LocalPoint& pos) :  RecHit2DLocalPos(me0Id),
  theME0Id(me0Id), theLocalPosition(pos), theBx(bx), theFirstStrip(999), theClusterSize(999), RealDigi(true) 
{
  float stripResolution = 3.0 ; //cm  this sould be taken from trimmed cluster size times strip size 
                                 //    taken out from geometry service i.e. topology	//rumi: the value to be changed with respect to the ME0  strip pitch
  theLocalError =
    LocalError(stripResolution*stripResolution, 0., 0.); //FIXME: is it really needed?
}

// Constructor from a local position and error, wireId and digi time.
ME0RecHit::ME0RecHit(const ME0DetId& me0Id,
		     int bx,
		     const LocalPoint& pos,
		     const LocalError& err) :  RecHit2DLocalPos(me0Id),
  theME0Id(me0Id), theLocalPosition(pos), theLocalError(err), theBx(bx),theFirstStrip(99), theClusterSize(999), RealDigi(true) 
{
}

// Constructor from a local position and error, wireId, bx and cluster size.
ME0RecHit::ME0RecHit(const ME0DetId& me0Id,
		     int bx,
		     int firstStrip,
		     int clustSize,
		     const LocalPoint& pos,
		     const LocalError& err) :  RecHit2DLocalPos(me0Id),
  theME0Id(me0Id), theLocalPosition(pos), theLocalError(err), theBx(bx),theFirstStrip(firstStrip), theClusterSize(clustSize), RealDigi(true) 
{
}

//rumi: end constructors for me0 real rechit


// Destructor
ME0RecHit::~ME0RecHit()
{
}



ME0RecHit * ME0RecHit::clone() const {
  return new ME0RecHit(*this);
}


// Access to component RecHits.
// No components rechits: it returns a null vector
std::vector<const TrackingRecHit*> ME0RecHit::recHits() const {
  std::vector<const TrackingRecHit*> nullvector;
  return nullvector; 
}
// Non-const access to component RecHits.
// No components rechits: it returns a null vector
std::vector<TrackingRecHit*> ME0RecHit::recHits() {
  std::vector<TrackingRecHit*> nullvector;
  return nullvector; 
}

// Comparison operator, based on the wireId and the digi time
bool ME0RecHit::operator==(const ME0RecHit& hit) const {
  return this->geographicalId() == hit.geographicalId(); 
}


// The ostream operator
std::ostream& operator<<(std::ostream& os, const ME0RecHit& hit) {
  os << "pos: x = " << hit.localPosition().x() ; 
  os << " +/- " << sqrt(hit.localPositionError().xx())<<" cm";
  os<< " y = " << hit.localPosition().y() ;
  os << " +/- " << sqrt(hit.localPositionError().yy())<<" cm";
  return os;
}
