/*
 *  See header file for a description of this class.
 *
 *  \author M. Maggi -- INFN Bari
 */


#include "DataFormats/GEMRecHit/interface/ME0TrivRecHit.h"


ME0TrivRecHit::ME0TrivRecHit(const ME0DetId& me0Id, int bx) :  RecHit2DLocalPos(me0Id),
  theME0TrivId(me0Id), theBx(bx),theFirstStrip(999),theClusterSize(999), theLocalPosition(), theLocalError() 
{
}

ME0TrivRecHit::ME0TrivRecHit() :  RecHit2DLocalPos(),
  theME0TrivId(), theBx(999),theFirstStrip(999),theClusterSize(999), theLocalPosition(), theLocalError() 
{
}


ME0TrivRecHit::ME0TrivRecHit(const ME0DetId& me0Id, int bx, const LocalPoint& pos) :  RecHit2DLocalPos(me0Id),
  theME0TrivId(me0Id), theBx(bx), theFirstStrip(999),theClusterSize(999), theLocalPosition(pos) 
{
  float stripResolution = 3.0 ; //cm  this sould be taken from trimmed cluster size times strip size 
                                 //    taken out from geometry service i.e. topology	//rumi: the value to be changed with respect to the ME0  strip pitch
  theLocalError =
    LocalError(stripResolution*stripResolution, 0., 0.); //FIXME: is it really needed?
}



// Constructor from a local position and error, wireId and digi time.
ME0TrivRecHit::ME0TrivRecHit(const ME0DetId& me0Id,
		     int bx,
		     const LocalPoint& pos,
		     const LocalError& err) :  RecHit2DLocalPos(me0Id),
  theME0TrivId(me0Id), theBx(bx),theFirstStrip(99), theClusterSize(99), theLocalPosition(pos), theLocalError(err) 
{
}


// Constructor from a local position and error, wireId, bx and cluster size.
ME0TrivRecHit::ME0TrivRecHit(const ME0DetId& me0Id,
		     int bx,
		     int firstStrip,
		     int clustSize,
		     const LocalPoint& pos,
		     const LocalError& err) :  RecHit2DLocalPos(me0Id),
  theME0TrivId(me0Id), theBx(bx),theFirstStrip(firstStrip), theClusterSize(clustSize), theLocalPosition(pos), theLocalError(err) 
{
}




// Destructor
ME0TrivRecHit::~ME0TrivRecHit()
{
}



ME0TrivRecHit * ME0TrivRecHit::clone() const {
  return new ME0TrivRecHit(*this);
}


// Access to component RecHits.
// No components rechits: it returns a null vector
std::vector<const TrackingRecHit*> ME0TrivRecHit::recHits() const {
  std::vector<const TrackingRecHit*> nullvector;
  return nullvector; 
}



// Non-const access to component RecHits.
// No components rechits: it returns a null vector
std::vector<TrackingRecHit*> ME0TrivRecHit::recHits() {
  std::vector<TrackingRecHit*> nullvector;
  return nullvector; 
}


// Comparison operator, based on the wireId and the digi time
bool ME0TrivRecHit::operator==(const ME0TrivRecHit& hit) const {
  return this->geographicalId() == hit.geographicalId(); 
}


// The ostream operator
std::ostream& operator<<(std::ostream& os, const ME0TrivRecHit& hit) {
  os << "pos: " << hit.localPosition().x() ; 
  os << " +/- " << sqrt(hit.localPositionError().xx()) ;
  return os;
}
