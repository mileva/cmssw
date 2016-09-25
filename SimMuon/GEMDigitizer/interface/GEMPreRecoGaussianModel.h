#ifndef GEMDigitizer_GEMPreRecoGaussianModel_h
#define GEMDigitizer_GEMPreRecoGaussianModel_h
/**
 * \class GEMPreRecoGaussianModel
 *
 * Class for the GEM Gaussian response simulation as pre-reco step
 */
#include "SimMuon/GEMDigitizer/interface/GEMDigiPreRecoModel.h"
class GEMGeometry;
namespace CLHEP
{
  class HepRandomEngine;
  class RandFlat;
  class RandGaussQ;
  class RandPoissonQ;
}
class GEMPreRecoGaussianModel: public GEMDigiPreRecoModel
{
public:
  GEMPreRecoGaussianModel(const edm::ParameterSet&);
  ~GEMPreRecoGaussianModel();
  void simulateSignal(const GEMEtaPartition*, const edm::PSimHitContainer&);
  void setRandomEngine(CLHEP::HepRandomEngine&);
  void simulateNoise(const GEMEtaPartition*);
  double correctSigmaU(const GEMEtaPartition*, double);
  void setup()
  {
  }
private:
  double sigma_t;
  double sigma_u;
  double sigma_u1;
  double sigma_v;
  bool corr;
  bool etaproj;
  bool digitizeOnlyMuons_;
  double gaussianSmearing_;
  double constPhiSmearing_;
  double averageEfficiency_;
  // bool simulateIntrinsicNoise_; // not implemented
  // double averageNoiseRate_;     // not implemented
  bool simulateElectronBkg_;   // to be added later
  bool simulateNeutralBkg_;    // to be added later
  bool doBkgNoise_;  
  int minBunch_;
  int maxBunch_;
  CLHEP::RandGaussQ* gauss_;
  CLHEP::RandFlat* flat1_;
  CLHEP::RandFlat* flat2_;
  CLHEP::RandFlat* poisson_;
  //parameters from the fit:
  //params for pol3 model of electron bkg for GE1/1:
  double GE11ElecBkgParam0;
  double GE11ElecBkgParam1;
  double GE11ElecBkgParam2;
  double GE11ElecBkgParam3;
  //params for expo of electron bkg for GE2/1:
  double constElecGE21;
  double slopeElecGE21;
  //Neutral Bkg
  //High Rate model L=5x10^{34}cm^{-2}s^{-1}
  //params for expo model of neutral bkg for GE1/1: 
  double constNeuGE11_highRate;
  double slopeNeuGE11_highRate;
  //params for pol5 model of neutral bkg for GE2/1:
  double GE21ModNeuBkgParam0;
  double GE21ModNeuBkgParam1;
  double GE21ModNeuBkgParam2;
  double GE21ModNeuBkgParam3;
  double GE21ModNeuBkgParam4;
  double GE21ModNeuBkgParam5;
};
#endif

