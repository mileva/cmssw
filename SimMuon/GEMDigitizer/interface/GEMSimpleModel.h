#ifndef GEMDigitizer_GEMSimpleModel_h
#define GEMDigitizer_GEMSimpleModel_h

/** 
 * \class GEMSimpleModel
 *
 * Class for the GEM strip response simulation based on a very simple model
 *
 * \author Sven Dildick
 * \modified by Roumyana Hadjiiska
 */

#include "SimMuon/GEMDigitizer/interface/GEMDigiModel.h"

class GEMGeometry;

namespace CLHEP
{
  class HepRandomEngine;
  class RandFlat;
  class RandPoissonQ;
  class RandGaussQ;
  class RandGamma;
}

class GEMSimpleModel: public GEMDigiModel
{
public:

  GEMSimpleModel(const edm::ParameterSet&);

  ~GEMSimpleModel();

  void setRandomEngine(CLHEP::HepRandomEngine&);

  void setup();

  void simulateSignal(const GEMEtaPartition*, const edm::PSimHitContainer&);

  int getSimHitBx(const PSimHit*);

  void simulateNoise(const GEMEtaPartition*);

  std::vector<std::pair<int,int> > 
    simulateClustering(const GEMEtaPartition*, const PSimHit*, const int);

private:

  double averageEfficiency_;
  double averageShapingTime_;
  double timeResolution_;
  double timeJitter_;
  double averageNoiseRate_;
  double averageClusterSize_;
  std::vector<double> clsParametrization_;
  double signalPropagationSpeed_;
  bool cosmics_;
  int bxwidth_;
  int minBunch_;
  int maxBunch_;
  bool digitizeOnlyMuons_;
  bool doBkgNoise_;
  bool doNoiseCLS_;
  bool fixedRollRadius_;
  double minPabsNoiseCLS_;
  bool simulateIntrinsicNoise_;
  double scaleLumi_;
  double constGE11_;
  double slopeGE11_;
  double constGE21Short_;
  double slopeGE21Short_;
  double constGE21Long_;
  double slopeGE21Long_;


  CLHEP::RandFlat* flat1_;
  CLHEP::RandFlat* flat2_;
  CLHEP::RandFlat* flat3_;
  CLHEP::RandFlat* flat4_;
  CLHEP::RandPoissonQ* poisson_;
  CLHEP::RandGaussQ* gauss1_;
  CLHEP::RandGaussQ* gauss2_;
  CLHEP::RandGamma* gamma1_;

};
#endif




