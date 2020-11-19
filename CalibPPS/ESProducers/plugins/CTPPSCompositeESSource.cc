/****************************************************************************
*
* Authors:
*  Jan Kaspar (jan.kaspar@gmail.com)
*  Christopher Misan (krzysmisan@gmail.com)
*
****************************************************************************/

// FIXME: clean up
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/SourceFactory.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/ESProducer.h"
#include "FWCore/Framework/interface/EventSetupRecordIntervalFinder.h"
#include "FWCore/Framework/interface/ESProducts.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CondFormats/RunInfo/interface/LHCInfo.h"
#include "CondFormats/DataRecord/interface/LHCInfoRcd.h"
#include "CondFormats/PPSObjects/interface/LHCOpticalFunctionsSetCollection.h"
#include "CondFormats/DataRecord/interface/CTPPSOpticsRcd.h"
#include "GeometryReaders/XMLIdealGeometryESSource/interface/GeometryConfiguration.h"
#include "Geometry/Records/interface/IdealGeometryRecord.h"
#include "DetectorDescription/Parser/interface/DDLParser.h"
#include "DetectorDescription/Core/interface/DDCompactView.h"
#include "Geometry/VeryForwardGeometryBuilder/interface/DetGeomDesc.h"
#include "Geometry/VeryForwardGeometryBuilder/interface/CTPPSGeometry.h"
#include "Geometry/VeryForwardGeometryBuilder/interface/CTPPSDDDNames.h"
#include "CondFormats/PPSObjects/interface/CTPPSRPAlignmentCorrectionsData.h"
#include "DetectorDescription/Core/interface/DDFilteredView.h"
#include "DataFormats/CTPPSDetId/interface/TotemRPDetId.h"
#include "DataFormats/CTPPSDetId/interface/TotemTimingDetId.h"
#include "DataFormats/CTPPSDetId/interface/CTPPSPixelDetId.h"
#include "DataFormats/CTPPSDetId/interface/CTPPSDiamondDetId.h"
#include "Geometry/Records/interface/VeryForwardMisalignedGeometryRecord.h"
#include "Geometry/Records/interface/VeryForwardRealGeometryRecord.h"
#include "CondFormats/PPSObjects/interface/CTPPSRPAlignmentCorrectionsDataSequence.h"
#include "CondFormats/PPSObjects/interface/CTPPSRPAlignmentCorrectionsMethods.h"

// FIXME: what is this?
#include "CondFormats/AlignmentRecord/interface/CTPPSRPAlignmentCorrectionsDataRcd.h"  // this used to be RPMeasuredAlignmentRecord.h

#include "CondFormats/AlignmentRecord/interface/RPRealAlignmentRecord.h"
#include "CondFormats/AlignmentRecord/interface/RPMisalignedAlignmentRecord.h"
#include "CondFormats/PPSObjects/interface/PPSDirectSimulationData.h"
#include "CondFormats/DataRecord/interface/PPSDirectSimulationDataRcd.h"
#include "CLHEP/Random/RandFlat.h"
#include "CLHEP/Random/JamesRandom.h"
#include <cstdio>
#include <memory>
#include <regex>
#include <vector>
#include <string>
#include <map>
#include <set>
#include "TRandom.h"
#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "CalibPPS/ESProducers/interface/CTPPSRPAlignmentCorrectionsDataESSourceXMLCommon.h"
#include "Geometry/VeryForwardGeometryBuilder/interface/CTPPSGeometryESCommon.h"
#include "Geometry/VeryForwardGeometryBuilder/interface/DetGeomDescBuilder.h"

//----------------------------------------------------------------------------------------------------

class CTPPSCompositeESSource : public edm::ESProducer, public edm::EventSetupRecordIntervalFinder {
public:
  CTPPSCompositeESSource(const edm::ParameterSet &);

  static void fillDescriptions(edm::ConfigurationDescriptions &);

  std::unique_ptr<LHCInfo> produceLhcInfo(const LHCInfoRcd &);
  std::unique_ptr<LHCOpticalFunctionsSetCollection> produceOptics(const CTPPSOpticsRcd &);
  std::shared_ptr<CTPPSGeometry> produceRealTG(const VeryForwardRealGeometryRecord &);
  std::shared_ptr<CTPPSGeometry> produceMisalignedTG(const VeryForwardMisalignedGeometryRecord &);
  std::unique_ptr<PPSDirectSimulationData> produceDirectSimuData(const PPSDirectSimulationDataRcd &);
  
private:
  // config parameters
  std::string lhcInfoLabel_;
  std::string opticsLabel_;
  unsigned int m_generateEveryNEvents_;
  unsigned int verbosity_;

  // FIXME: give understandable names
  edm::ESGetToken<DDCompactView, IdealGeometryRecord> ddToken_, ddToken2_;

  // FIXME: move to the code where needed?
  struct FileInfo {
    double m_xangle;
    std::string m_fileName;
  };

  // FIXME: move to the code where needed?
  struct RPInfo {
    std::string m_dirName;
    double m_scoringPlaneZ;
  };

  // FIXME: move to the code where needed?
  struct Entry {
    std::vector<FileInfo> m_fileInfo;
    std::unordered_map<unsigned int, RPInfo> m_rpInfo;
  };

  template <typename T>
  struct BinData {
    double min, max;
    T data;
  };

  struct ProfileData {
    // LHCInfo
    double beamEnergy, xangle, betaStar;
    std::vector<BinData<std::pair<double,double>>> xangleBetaStarBins;

    // optics
    LHCOpticalFunctionsSetCollection lhcOptical;

    // geometry
    std::shared_ptr<DDCompactView> ddCompactView;
    std::shared_ptr<DetGeomDesc> misalignedGD;
    std::shared_ptr<DetGeomDesc> realGD;
    std::shared_ptr<CTPPSGeometry> misalignedTG;
    std::shared_ptr<CTPPSGeometry> realTG;

    // alignment
    std::shared_ptr<CTPPSRPAlignmentCorrectionsData> acMeasured, acReal, acMisaligned;

    // direct simulation configuration
    PPSDirectSimulationData directSimuData;
  };

  // profile variables
  std::vector<BinData<ProfileData>> profile_bins_;
  const ProfileData *currentProfile_;

  // workers
  std::unique_ptr<CLHEP::HepRandomEngine> m_engine_;

  std::unique_ptr<CTPPSGeometryESCommon> ctppsGeometryESModuleCommon;

  // methods to pre-compute profile data
  void buildLHCInfo(const edm::ParameterSet& profile, ProfileData& pData);
  void buildOptics(const edm::ParameterSet& profile, ProfileData& pData);
  void buildGeom(const DDCompactView& cpv);
  void buildDirectSimuData(const edm::ParameterSet& profile, ProfileData& pData);

  // method set IOV (common to all products)
  void setIntervalFor(const edm::eventsetup::EventSetupRecordKey &,
                      const edm::IOVSyncValue &,
                      edm::ValidityInterval &) override;
};

//----------------------------------------------------------------------------------------------------

CTPPSCompositeESSource::CTPPSCompositeESSource(const edm::ParameterSet &conf)
    : lhcInfoLabel_(conf.getParameter<std::string>("lhcInfoLabel")),

    opticsLabel_(conf.getParameter<std::string>("opticsLabel")),

    m_generateEveryNEvents_(conf.getParameter<unsigned int>("generateEveryNEvents")),

    verbosity_(conf.getUntrackedParameter<unsigned int>("verbosity")),

    m_engine_(new CLHEP::HepJamesRandom(conf.getParameter<unsigned int>("seed")))
{
  double l_int_sum = 0;

  for (const auto &cfg : conf.getParameter<std::vector<edm::ParameterSet>>("periods")) {
    double l_int = cfg.getParameter<double>("L_int");

    profile_bins_.emplace_back(BinData<ProfileData>{l_int_sum, l_int_sum + l_int, ProfileData()});

    l_int_sum += l_int;

    auto& pData = profile_bins_.back().data;

    auto ctppsRPAlignmentCorrectionsDataXMLpSet = cfg.getParameter<edm::ParameterSet>("ctppsRPAlignmentCorrectionsDataXML");
    ctppsRPAlignmentCorrectionsDataXMLpSet.addUntrackedParameter("verbosity", verbosity_);
    CTPPSRPAlignmentCorrectionsDataESSourceXMLCommon ctppsRPAlignmentCorrectionsDataESSourceXMLCommon(ctppsRPAlignmentCorrectionsDataXMLpSet);

    if (!ctppsRPAlignmentCorrectionsDataXMLpSet.getParameter<std::vector<std::string> >("MeasuredFiles").empty())
      pData.acMeasured=std::make_shared<CTPPSRPAlignmentCorrectionsData>(ctppsRPAlignmentCorrectionsDataESSourceXMLCommon.acsMeasured[0].second);

    pData.acReal = std::make_shared<CTPPSRPAlignmentCorrectionsData>(ctppsRPAlignmentCorrectionsDataESSourceXMLCommon.acsReal[0].second);
    pData.acMisaligned = std::make_shared<CTPPSRPAlignmentCorrectionsData>(ctppsRPAlignmentCorrectionsDataESSourceXMLCommon.acsMisaligned[0].second);

    buildLHCInfo(cfg, pData);
    buildOptics(cfg, pData);
    buildDirectSimuData(cfg, pData);
  }

  // normalise L_int sums to probabilities
  for (auto &bin : profile_bins_)
  {
    bin.min /= l_int_sum;
    bin.max /= l_int_sum;
  }

  // framework registrations
  setWhatProduced(this, &CTPPSCompositeESSource::produceLhcInfo, edm::es::Label(lhcInfoLabel_));
  setWhatProduced(this, &CTPPSCompositeESSource::produceOptics, edm::es::Label(opticsLabel_));

  // FIXME: give names
  ddToken_ = setWhatProduced(this, &CTPPSCompositeESSource::produceRealTG).consumesFrom<DDCompactView,IdealGeometryRecord>(edm::ESInputTag("","XMLIdealGeometryESSource_CTPPS"));
  ddToken2_ = setWhatProduced(this, &CTPPSCompositeESSource::produceMisalignedTG).consumesFrom<DDCompactView,IdealGeometryRecord>(edm::ESInputTag("","XMLIdealGeometryESSource_CTPPS"));

  setWhatProduced(this, &CTPPSCompositeESSource::produceDirectSimuData);

  findingRecord<LHCInfoRcd>();
  findingRecord<CTPPSOpticsRcd>();
  findingRecord<PPSDirectSimulationDataRcd>();
}

//----------------------------------------------------------------------------------------------------

void CTPPSCompositeESSource::fillDescriptions(edm::ConfigurationDescriptions &descriptions) {
  edm::ParameterSetDescription desc;
  desc.add<std::string>("lhcInfoLabel", "")->setComment("label of the LHCInfo record");
  desc.add<std::string>("opticsLabel", "")->setComment("label of the optics record");
  desc.add<unsigned int>("seed", 1)->setComment("random seed");
  desc.add<unsigned int>("generateEveryNEvents", 1)->setComment("how often to switch conditions");
  desc.addUntracked<unsigned int>("verbosity",0);

  edm::ParameterSetDescription desc_profile;
  std::vector<edm::ParameterSet> vp;
  desc_profile.add<double>("L_int", 0.)->setComment("integrated luminosity");

  // lhcInfo
  edm::ParameterSetDescription desc_profile_ctppsLHCInfo;
  desc_profile_ctppsLHCInfo.add<double>("xangle", 0.)->setComment("constant xangle");
  desc_profile_ctppsLHCInfo.add<double>("betaStar", 0.)->setComment("constant betaStar");
  desc_profile_ctppsLHCInfo.add<double>("beamEnergy", 0.)->setComment("beam energy");
  desc_profile_ctppsLHCInfo.add<std::string>("xangleBetaStarHistogramFile", "")->setComment("ROOT file with xangle/beta* distribution");
  desc_profile_ctppsLHCInfo.add<std::string>("xangleBetaStarHistogramObject", "")->setComment("xangle distribution object in the ROOT file");
  desc_profile.add<edm::ParameterSetDescription>("ctppsLHCInfo",desc_profile_ctppsLHCInfo);

  // optics
  edm::ParameterSetDescription desc_profile_ctppsOpticalFunctions;
  edm::ParameterSetDescription of_desc;
  of_desc.add<double>("xangle")->setComment("half crossing angle value in urad");
  of_desc.add<edm::FileInPath>("fileName")->setComment("ROOT file with optical functions");
  std::vector<edm::ParameterSet> of;
  desc_profile_ctppsOpticalFunctions.addVPSet("opticalFunctions", of_desc, of)
      ->setComment("list of optical functions at different crossing angles");

  edm::ParameterSetDescription sp_desc;
  sp_desc.add<unsigned int>("rpId")->setComment("associated detector DetId");
  sp_desc.add<std::string>("dirName")->setComment("associated path to the optical functions file");
  sp_desc.add<double>("z")->setComment("longitudinal position at scoring plane/detector");
  std::vector<edm::ParameterSet> sp;
  desc_profile_ctppsOpticalFunctions.addVPSet("scoringPlanes", sp_desc, sp)->setComment("list of sensitive planes/detectors stations");
  desc_profile.add<edm::ParameterSetDescription>("ctppsOpticalFunctions",desc_profile_ctppsOpticalFunctions);

  // geometry
  edm::ParameterSetDescription desc_profile_xmlIdealGeometry;
  desc_profile_xmlIdealGeometry.add<std::vector<std::string>>("geomXMLFiles");
  desc_profile_xmlIdealGeometry.add<std::string>("rootNodeName");
  desc_profile.add<edm::ParameterSetDescription>("xmlIdealGeometry",desc_profile_xmlIdealGeometry);

  // alignment
  edm::ParameterSetDescription desc_profile_ctppsRPAlignmentCorrectionsDataXML;
  desc_profile_ctppsRPAlignmentCorrectionsDataXML.add<std::vector<std::string>>("MeasuredFiles");
  desc_profile_ctppsRPAlignmentCorrectionsDataXML.add<std::vector<std::string>>("RealFiles");
  desc_profile_ctppsRPAlignmentCorrectionsDataXML.add<std::vector<std::string>>("MisalignedFiles");
  desc_profile.add<edm::ParameterSetDescription>("ctppsRPAlignmentCorrectionsDataXML",desc_profile_ctppsRPAlignmentCorrectionsDataXML);

  // direct simu config
  edm::ParameterSetDescription desc_profile_ctppsDirectSimuData;
  desc_profile_ctppsDirectSimuData.add<std::string>("empiricalAperture45");
  desc_profile_ctppsDirectSimuData.add<std::string>("empiricalAperture56");

  desc_profile_ctppsDirectSimuData.add<std::string>("timeResolutionDiamonds45");
  desc_profile_ctppsDirectSimuData.add<std::string>("timeResolutionDiamonds56");

  desc_profile_ctppsDirectSimuData.add<std::string>("effTimePath");
  desc_profile_ctppsDirectSimuData.add<std::string>("effTimeObject45");
  desc_profile_ctppsDirectSimuData.add<std::string>("effTimeObject56");

  desc_profile.add<edm::ParameterSetDescription>("ctppsDirectSimuData",desc_profile_ctppsDirectSimuData);

  desc.addVPSet("periods", desc_profile,vp)->setComment("profiles");

  descriptions.add("ctppsCompositeESSource", desc);
}

//----------------------------------------------------------------------------------------------------

void CTPPSCompositeESSource::buildDirectSimuData(const edm::ParameterSet& profile, ProfileData& pData) {
  const auto& ctppsDirectSimuData=profile.getParameter<edm::ParameterSet>("ctppsDirectSimuData");

  pData.directSimuData.setEmpiricalAperture45(ctppsDirectSimuData.getParameter<std::string>("empiricalAperture45"));
  pData.directSimuData.setEmpiricalAperture56(ctppsDirectSimuData.getParameter<std::string>("empiricalAperture56"));

  pData.directSimuData.setTimeResolutionDiamonds45(ctppsDirectSimuData.getParameter<std::string>("timeResolutionDiamonds45"));
  pData.directSimuData.setTimeResolutionDiamonds56(ctppsDirectSimuData.getParameter<std::string>("timeResolutionDiamonds56"));

  pData.directSimuData.setEffTimePath(ctppsDirectSimuData.getParameter<std::string>("effTimePath"));
  pData.directSimuData.setEffTimeObject45(ctppsDirectSimuData.getParameter<std::string>("effTimeObject45"));
  pData.directSimuData.setEffTimeObject56(ctppsDirectSimuData.getParameter<std::string>("effTimeObject56"));
}

//----------------------------------------------------------------------------------------------------

void CTPPSCompositeESSource::buildGeom(const DDCompactView& cpv) {
  std::unique_ptr<DetGeomDesc> idealGD = detgeomdescbuilder::buildDetGeomDescFromCompactView(cpv);

  for (auto &pb : profile_bins_)
  {
    auto &p = pb.data;

    p.misalignedGD = ctppsGeometryESModuleCommon->applyAlignments(*(idealGD), p.acMisaligned.get());
    p.misalignedTG = std::make_shared<CTPPSGeometry>(p.misalignedGD.get(),verbosity_);

    p.realGD = ctppsGeometryESModuleCommon->applyAlignments(*(idealGD), p.acReal.get());
    p.realTG = std::make_shared<CTPPSGeometry>(p.realGD.get(),verbosity_);
  }
}

//----------------------------------------------------------------------------------------------------

void CTPPSCompositeESSource::buildOptics(const edm::ParameterSet& profile, ProfileData& pData) {
  const auto& ctppsOpticalFunctions=profile.getParameter<edm::ParameterSet>("ctppsOpticalFunctions");
  std::vector<FileInfo> fileInfo;
  for (const auto &pset : ctppsOpticalFunctions.getParameter<std::vector<edm::ParameterSet>>("opticalFunctions")) {
    const double &xangle = pset.getParameter<double>("xangle");
    const std::string &fileName = pset.getParameter<edm::FileInPath>("fileName").fullPath();
    fileInfo.push_back({xangle, fileName});
  }

  std::unordered_map<unsigned int, RPInfo> rpInfo;
  for (const auto &pset : ctppsOpticalFunctions.getParameter<std::vector<edm::ParameterSet>>("scoringPlanes")) {
    const unsigned int rpId = pset.getParameter<unsigned int>("rpId");
    const std::string dirName = pset.getParameter<std::string>("dirName");
    const double z = pset.getParameter<double>("z");
    const RPInfo entry = {dirName, z};
    rpInfo.emplace(rpId, entry);
  }

  Entry entry({fileInfo, rpInfo});

  for (const auto &fi : entry.m_fileInfo) {
    std::unordered_map<unsigned int, LHCOpticalFunctionsSet> xa_data;

    for (const auto &rpi : entry.m_rpInfo) {
      LHCOpticalFunctionsSet fcn(fi.m_fileName, rpi.second.m_dirName, rpi.second.m_scoringPlaneZ);
      xa_data.emplace(rpi.first, std::move(fcn));
    }

    pData.lhcOptical.emplace(fi.m_xangle, xa_data);
  }
}

//----------------------------------------------------------------------------------------------------

void CTPPSCompositeESSource::buildLHCInfo(const edm::ParameterSet& profile, ProfileData& pData) {
  const auto& ctppsLHCInfo = profile.getParameter<edm::ParameterSet>("ctppsLHCInfo");

  pData.beamEnergy = ctppsLHCInfo.getParameter<double>("beamEnergy");
  pData.betaStar = ctppsLHCInfo.getParameter<double>("betaStar");
  pData.xangle = ctppsLHCInfo.getParameter<double>("xangle");

  // continue only if distributed xangle/beta* shall be used
  if (pData.xangle > 0)
    return;

  edm::FileInPath fip(ctppsLHCInfo.getParameter<std::string>("xangleBetaStarHistogramFile").c_str());
  std::unique_ptr<TFile> f_in(TFile::Open(fip.fullPath().c_str()));
  if (!f_in)
    throw cms::Exception("PPS") << "Cannot open input file '" << ctppsLHCInfo.getParameter<std::string>("xangleBetaStarHistogramFile") << "'.";

  TH2D* h_xangle_beta_star = (TH2D *)f_in->Get(ctppsLHCInfo.getParameter<std::string>("xangleBetaStarHistogramObject").c_str());
  if (!h_xangle_beta_star)
    throw cms::Exception("PPS") << "Cannot load input object '" << ctppsLHCInfo.getParameter<std::string>("xangleBetaStarHistogramObject") << "'.";

  // extract non-empty bins, calculate weights
  double sum = 0.;
  for (int bi = 1; bi <= h_xangle_beta_star->GetNcells(); ++bi)
    sum += h_xangle_beta_star->GetBinContent(bi);

  double cw = 0.;
  for (int x = 1; x <= h_xangle_beta_star->GetNbinsX(); ++x)
    for (int y = 1; y <= h_xangle_beta_star->GetNbinsY(); ++y) {
      const double w = h_xangle_beta_star->GetBinContent(h_xangle_beta_star->GetBin(x,y)) / sum;
      if (w > 0.) {
        pData.xangleBetaStarBins.push_back({cw, cw + w, std::pair<double,double>(
          h_xangle_beta_star->GetXaxis()->GetBinCenter(x), h_xangle_beta_star->GetYaxis()->GetBinCenter(y))});
        cw += w;
      }
    }
}

//----------------------------------------------------------------------------------------------------

void CTPPSCompositeESSource::setIntervalFor(const edm::eventsetup::EventSetupRecordKey &key,
                                                      const edm::IOVSyncValue &iosv,
                                                      edm::ValidityInterval &oValidity) {
  // determine new IOV
  edm::EventID beginEvent = iosv.eventID();
  edm::EventID endEvent(beginEvent.run(), beginEvent.luminosityBlock(), beginEvent.event() + m_generateEveryNEvents_);
  oValidity = edm::ValidityInterval(edm::IOVSyncValue(beginEvent), edm::IOVSyncValue(endEvent));

  // randomly pick the next profile
  const double u = CLHEP::RandFlat::shoot(m_engine_.get(), 0., 1.);

  for (const auto &bin : profile_bins_) {
    if (bin.min <= u && u <= bin.max) {
      currentProfile_ = &bin.data;
      break;
    }
  }
}

//----------------------------------------------------------------------------------------------------

std::shared_ptr<CTPPSGeometry> CTPPSCompositeESSource::produceRealTG(const VeryForwardRealGeometryRecord& iRecord) {
  if(currentProfile_->realTG == nullptr) {
    auto const& cpv = iRecord.getRecord<IdealGeometryRecord>().get(ddToken_);
    buildGeom(cpv);
  }

  return currentProfile_->realTG;
}

//----------------------------------------------------------------------------------------------------

std::shared_ptr<CTPPSGeometry> CTPPSCompositeESSource::produceMisalignedTG(const VeryForwardMisalignedGeometryRecord& iRecord) {
  if(currentProfile_->misalignedTG == nullptr) {
    auto const& cpv = iRecord.getRecord<IdealGeometryRecord>().get(ddToken2_);
    buildGeom(cpv);
  }
  return currentProfile_->misalignedTG;
}

//----------------------------------------------------------------------------------------------------

std::unique_ptr<PPSDirectSimulationData> CTPPSCompositeESSource::produceDirectSimuData(const PPSDirectSimulationDataRcd &) {
  return std::make_unique<PPSDirectSimulationData>(currentProfile_->directSimuData);
}

//----------------------------------------------------------------------------------------------------

std::unique_ptr<LHCOpticalFunctionsSetCollection> CTPPSCompositeESSource::produceOptics(const CTPPSOpticsRcd &) {
  return std::make_unique<LHCOpticalFunctionsSetCollection>(currentProfile_->lhcOptical);
}

//----------------------------------------------------------------------------------------------------

std::unique_ptr<LHCInfo> CTPPSCompositeESSource::produceLhcInfo(const LHCInfoRcd &) {
  double xangle = currentProfile_->xangle;
  double betaStar = currentProfile_->betaStar;

  if (currentProfile_->xangle < 0) {
    const double u = CLHEP::RandFlat::shoot(m_engine_.get(), 0., 1.);
    for (const auto &d : currentProfile_->xangleBetaStarBins) {
      if (d.min <= u && u <= d.max) {
        xangle = d.data.first;
        betaStar = d.data.second;
        break;
      }
    }
  }

  auto lhcInfo = std::make_unique<LHCInfo>();
  lhcInfo->setEnergy(currentProfile_->beamEnergy);
  lhcInfo->setCrossingAngle(xangle);
  lhcInfo->setBetaStar(betaStar);

  edm::LogInfo("PPS")
    << "new LHCInfo: xangle=" << xangle << ", betaStar=" << betaStar;

  return lhcInfo;
}

//----------------------------------------------------------------------------------------------------

DEFINE_FWK_EVENTSETUP_SOURCE(CTPPSCompositeESSource);