#ifndef SimMuon_GEMDigitizer_ME0TrivialModel_h
#define SimMuon_GEMDigitizer_ME0TrivialModel_h

/**
 * \class ME0TrivialModel
 *
 * Class for the ME0 strip response simulation based on a trivial model
 *
 * \author Roumyana Hadjiiska
 */

#include "SimMuon/GEMDigitizer/interface/ME0DigiModel.h"

class ME0Geometry;

namespace CLHEP
{
  class HepRandomEngine;
}

class ME0TrivialModel: public ME0DigiModel
{
public:

  ME0TrivialModel(const edm::ParameterSet&);

  ~ME0TrivialModel() {}

  void simulateSignal(const ME0EtaPartition*, const edm::PSimHitContainer&, CLHEP::HepRandomEngine* engine);

  void simulateNoise(const ME0EtaPartition*, CLHEP::HepRandomEngine* engine) {}

  std::vector<std::pair<int,int> > 
    simulateClustering(const ME0EtaPartition*, const PSimHit*, const int, CLHEP::HepRandomEngine* engine);

  void setup() {}

private:
};
#endif
