/***************************************
Original Author: 
Camilo Carrillo
Universidad de los Andes Bogota Colombia
camilo.carrilloATcern.ch
Modified for GEM:
Roumyana Hadjiiska
****************************************/

#include "DQM/GEMResoModule/interface/GEMMuonSegment.h"
#include <memory>
#include "FWCore/Framework/interface/MakerMacros.h"
#include <DataFormats/GEMDigi/interface/GEMDigiCollection.h>
#include "DataFormats/GEMRecHit/interface/GEMRecHitCollection.h"
#include <DataFormats/MuonDetId/interface/GEMDetId.h>
#include <DataFormats/CSCRecHit/interface/CSCSegmentCollection.h>
#include <Geometry/CommonDetUnit/interface/GeomDet.h>
#include <Geometry/Records/interface/MuonGeometryRecord.h>
#include <Geometry/CommonTopologies/interface/TrapezoidalStripTopology.h>

#include <cmath>
#include "TFile.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "TString.h"

#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/Utilities/interface/EDGetToken.h"

void GEMMuonSegment::beginJob(){
  firstbook=true;
}

GEMMuonSegment::GEMMuonSegment(const edm::ParameterSet& iConfig){
  debug=iConfig.getUntrackedParameter<bool>("debug",true);
  inves=iConfig.getUntrackedParameter<bool>("inves");
  manualalignment=iConfig.getUntrackedParameter<bool>("manualalignment",false);
 
  rangestrips = iConfig.getUntrackedParameter<double>("rangestrips",1.);
  dupli = iConfig.getUntrackedParameter<int>("DuplicationCorrection",1); 

  cscSegments = consumes<CSCSegmentCollection>(iConfig.getUntrackedParameter < edm::InputTag > ("cscSegments"));
  gemRecHitsLabel = consumes<GEMRecHitCollection>(iConfig.getUntrackedParameter < edm::InputTag > ("gemRecHits"));
  gemCSCPointsLabel = consumes<GEMRecHitCollection>(iConfig.getUntrackedParameter < edm::InputTag > ("gemCSCPoints"));
  
  nameInLog = iConfig.getUntrackedParameter<std::string>("moduleLogName", "GEM_CSCseg");
  EffSaveRootFile  = iConfig.getUntrackedParameter<bool>("EffSaveRootFile", false); 
  EffRootFileName  = iConfig.getUntrackedParameter<std::string>("EffRootFileName", "GEMMuonSegment.root"); 
  AlignmentinfoFile  = iConfig.getUntrackedParameter<std::string>("AliFileName","/afs/cern.ch/user/c/carrillo/segments/CMSSW_2_2_10/src/DQM/RPCMonitorModule/data/Alignment.dat"); 
    
  //Interface
  dbe = edm::Service<DQMStore>().operator->();
  std::string folder = "Muons/MuonSegEff/";
  dbe->setCurrentFolder(folder);

  stationstatistics = dbe->book1D("StationStatistics","All Statistics by Station",5,0.5,5.5);
  statistics = dbe->book1D("Statistics","All Statistics",17,0.5,17.5);

  if(debug) std::cout<<"booking Global histograms"<<std::endl;
  
  statistics->setBinLabel(1,"Events ",1);
  statistics->setBinLabel(2,"Events with CSC segments",1);
  statistics->setBinLabel(3,"Events with 1 CSC segment",1);
  statistics->setBinLabel(4,"Events with 2 CSC segments",1);
  statistics->setBinLabel(5,"Events with 3 CSC segments",1);
  statistics->setBinLabel(6,"Events with 4 CSC segments",1);
  statistics->setBinLabel(7,"Events with 5 CSC segments",1);
  statistics->setBinLabel(8,"Events with 6 CSC segments",1);
  statistics->setBinLabel(9,"Events with 7 CSC segments",1);
  statistics->setBinLabel(10,"Events with 8 CSC segments",1);
  statistics->setBinLabel(11,"Events with 9 CSC segments",1);
  statistics->setBinLabel(12,"Events with 10 CSC segments",1);
  statistics->setBinLabel(13,"Events with 11 CSC segments",1);
  statistics->setBinLabel(14,"Events with 12 CSC segments",1);
  statistics->setBinLabel(15,"Events with 13 CSC segments",1);
  statistics->setBinLabel(16,"Events with 14 CSC segments",1);
  statistics->setBinLabel(17,"Events with 15 CSC segments",1);

  stationstatistics->setBinLabel(1,"Events ",1);
  stationstatistics->setBinLabel(2,"Events with GE11 rechits",1);
  stationstatistics->setBinLabel(3,"Events with GE21 rechits",1);
  stationstatistics->setBinLabel(4,"Events with RE31 rechits",1);
  stationstatistics->setBinLabel(5,"Events with RE41 rechits",1);
  
  if(debug) std::cout<<"booking Global histograms Change statistics"<<std::endl;

  folder = "Muons/MuonSegEff/Investigation";
  dbe->setCurrentFolder(folder);

  //Ang Dependence
  AngClu1Endcaps = dbe->book1D("AngClu1Endcaps","Angle of incident Muon Endcaps Cluster Size 1",100,0.,360.);
  AngClu2Endcaps = dbe->book1D("AngClu2Endcaps","Angle of incident Muon Endcaps Cluster Size 2",100,0.,360.); 
  AngClu3Endcaps = dbe->book1D("AngClu3Endcaps","Angle of incident Muon Endcaps Cluster Size 3",100,0.,360.); 
  ScatterPlotAngCLSEndcaps = dbe->book2D("ScatterPlotAngCLSEndcaps","Scatter Plot Incident  Angle and Cluster Size Endcaps",100,0.,360.,7,0.5,7.5);

  if(debug) std::cout<<"Booking Residuals for EndCap"<<std::endl;
  folder = "Muons/MuonSegEff/Residuals/GE11";
  dbe->setCurrentFolder(folder);

  //Endcap GE11
  hGlobalResAllClsGE11_1 = dbe->book1D("GlobalResidualsAllClsGE11_1","GEM Residuals GE11 Roll 1",100, -1., 1.);
  hGlobalResAllClsGE11_2 = dbe->book1D("GlobalResidualsAllClsGE11_2","GEM Residuals GE11 Roll 2",100, -1., 1.);
  hGlobalResAllClsGE11_3 = dbe->book1D("GlobalResidualsAllClsGE11_3","GEM Residuals GE11 Roll 3",100, -1., 1.);
  hGlobalResAllClsGE11_4 = dbe->book1D("GlobalResidualsAllClsGE11_4","GEM Residuals GE11 Roll 4",100, -1., 1.);
  hGlobalResAllClsGE11_5 = dbe->book1D("GlobalResidualsAllClsGE11_5","GEM Residuals GE11 Roll 5",100, -1., 1.);
  hGlobalResAllClsGE11_6 = dbe->book1D("GlobalResidualsAllClsGE11_6","GEM Residuals GE11 Roll 6",100, -1., 1.);
  hGlobalResAllClsGE11_7 = dbe->book1D("GlobalResidualsAllClsGE11_7","GEM Residuals GE11 Roll 7",100, -1., 1.);
  hGlobalResAllClsGE11_8 = dbe->book1D("GlobalResidualsAllClsGE11_8","GEM Residuals GE11 Roll 8",100, -1., 1.);

  hGlobalResClu1GE11_1 = dbe->book1D("GlobalResidualsClu1GE11_1","GEM Residuals GE11 Roll 1 Cluster Size 1",100, -1., 1.);
  hGlobalResClu1GE11_2 = dbe->book1D("GlobalResidualsClu1GE11_2","GEM Residuals GE11 Roll 2 Cluster Size 1",100, -1., 1.);
  hGlobalResClu1GE11_3 = dbe->book1D("GlobalResidualsClu1GE11_3","GEM Residuals GE11 Roll 3 Cluster Size 1",100, -1., 1.);
  hGlobalResClu1GE11_4 = dbe->book1D("GlobalResidualsClu1GE11_4","GEM Residuals GE11 Roll 4 Cluster Size 1",100, -1., 1.);
  hGlobalResClu1GE11_5 = dbe->book1D("GlobalResidualsClu1GE11_5","GEM Residuals GE11 Roll 5 Cluster Size 1",100, -1., 1.);
  hGlobalResClu1GE11_6 = dbe->book1D("GlobalResidualsClu1GE11_6","GEM Residuals GE11 Roll 6 Cluster Size 1",100, -1., 1.);
  hGlobalResClu1GE11_7 = dbe->book1D("GlobalResidualsClu1GE11_7","GEM Residuals GE11 Roll 7 Cluster Size 1",100, -1., 1.);
  hGlobalResClu1GE11_8 = dbe->book1D("GlobalResidualsClu1GE11_8","GEM Residuals GE11 Roll 8 Cluster Size 1",100, -1., 1.);

  hGlobalResClu2GE11_1 = dbe->book1D("GlobalResidualsClu2GE11_1","GEM Residuals GE11 Roll 1 Cluster Size 2",100, -1., 1.);
  hGlobalResClu2GE11_2 = dbe->book1D("GlobalResidualsClu2GE11_2","GEM Residuals GE11 Roll 2 Cluster Size 2",100, -1., 1.);
  hGlobalResClu2GE11_3 = dbe->book1D("GlobalResidualsClu2GE11_3","GEM Residuals GE11 Roll 3 Cluster Size 2",100, -1., 1.);
  hGlobalResClu2GE11_4 = dbe->book1D("GlobalResidualsClu2GE11_4","GEM Residuals GE11 Roll 4 Cluster Size 2",100, -1., 1.);
  hGlobalResClu2GE11_5 = dbe->book1D("GlobalResidualsClu2GE11_5","GEM Residuals GE11 Roll 5 Cluster Size 2",100, -1., 1.);
  hGlobalResClu2GE11_6 = dbe->book1D("GlobalResidualsClu2GE11_6","GEM Residuals GE11 Roll 6 Cluster Size 2",100, -1., 1.);
  hGlobalResClu2GE11_7 = dbe->book1D("GlobalResidualsClu2GE11_7","GEM Residuals GE11 Roll 7 Cluster Size 2",100, -1., 1.);
  hGlobalResClu2GE11_8 = dbe->book1D("GlobalResidualsClu2GE11_8","GEM Residuals GE11 Roll 8 Cluster Size 2",100, -1., 1.);

  hGlobalResClu3GE11_1 = dbe->book1D("GlobalResidualsClu3GE11_1","GEM Residuals GE11 Roll 1 Cluster Size 3",100, -1., 1.);
  hGlobalResClu3GE11_2 = dbe->book1D("GlobalResidualsClu3GE11_2","GEM Residuals GE11 Roll 2 Cluster Size 3",100, -1., 1.);
  hGlobalResClu3GE11_3 = dbe->book1D("GlobalResidualsClu3GE11_3","GEM Residuals GE11 Roll 3 Cluster Size 3",100, -1., 1.);
  hGlobalResClu3GE11_4 = dbe->book1D("GlobalResidualsClu3GE11_4","GEM Residuals GE11 Roll 4 Cluster Size 3",100, -1., 1.);
  hGlobalResClu3GE11_5 = dbe->book1D("GlobalResidualsClu3GE11_5","GEM Residuals GE11 Roll 5 Cluster Size 3",100, -1., 1.);
  hGlobalResClu3GE11_6 = dbe->book1D("GlobalResidualsClu3GE11_6","GEM Residuals GE11 Roll 6 Cluster Size 3",100, -1., 1.);
  hGlobalResClu3GE11_7 = dbe->book1D("GlobalResidualsClu3GE11_7","GEM Residuals GE11 Roll 7 Cluster Size 3",100, -1., 1.);
  hGlobalResClu3GE11_8 = dbe->book1D("GlobalResidualsClu3GE11_8","GEM Residuals GE11 Roll 8 Cluster Size 3",100, -1., 1.);

  folder = "Muons/MuonSegEff/Residuals/GE21";
  dbe->setCurrentFolder(folder);

  //Endcap GE21
  hGlobalResAllClsGE21_1 = dbe->book1D("GlobalResidualsAllClsGE21_1","GEM Residuals GE21 Roll 1",100, -1., 1.);
  hGlobalResAllClsGE21_2 = dbe->book1D("GlobalResidualsAllClsGE21_2","GEM Residuals GE21 Roll 2",100, -1., 1.);
  hGlobalResAllClsGE21_3 = dbe->book1D("GlobalResidualsAllClsGE21_3","GEM Residuals GE21 Roll 3",100, -1., 1.);
  hGlobalResAllClsGE21_4 = dbe->book1D("GlobalResidualsAllClsGE21_4","GEM Residuals GE21 Roll 4",100, -1., 1.);
  hGlobalResAllClsGE21_5 = dbe->book1D("GlobalResidualsAllClsGE21_5","GEM Residuals GE21 Roll 5",100, -1., 1.);
  hGlobalResAllClsGE21_6 = dbe->book1D("GlobalResidualsAllClsGE21_6","GEM Residuals GE21 Roll 6",100, -1., 1.);
  hGlobalResAllClsGE21_7 = dbe->book1D("GlobalResidualsAllClsGE21_7","GEM Residuals GE21 Roll 7",100, -1., 1.);
  hGlobalResAllClsGE21_8 = dbe->book1D("GlobalResidualsAllClsGE21_8","GEM Residuals GE21 Roll 8",100, -1., 1.);

  hGlobalResClu1GE21_1 = dbe->book1D("GlobalResidualsClu1GE21_1","GEM Residuals GE21 Roll 1 Cluster Size 1",100, -1., 1.);
  hGlobalResClu1GE21_2 = dbe->book1D("GlobalResidualsClu1GE21_2","GEM Residuals GE21 Roll 2 Cluster Size 1",100, -1., 1.);
  hGlobalResClu1GE21_3 = dbe->book1D("GlobalResidualsClu1GE21_3","GEM Residuals GE21 Roll 3 Cluster Size 1",100, -1., 1.);
  hGlobalResClu1GE21_4 = dbe->book1D("GlobalResidualsClu1GE21_4","GEM Residuals GE21 Roll 4 Cluster Size 1",100, -1., 1.);
  hGlobalResClu1GE21_5 = dbe->book1D("GlobalResidualsClu1GE21_5","GEM Residuals GE21 Roll 5 Cluster Size 1",100, -1., 1.);
  hGlobalResClu1GE21_6 = dbe->book1D("GlobalResidualsClu1GE21_6","GEM Residuals GE21 Roll 6 Cluster Size 1",100, -1., 1.);
  hGlobalResClu1GE21_7 = dbe->book1D("GlobalResidualsClu1GE21_7","GEM Residuals GE21 Roll 7 Cluster Size 1",100, -1., 1.);
  hGlobalResClu1GE21_8 = dbe->book1D("GlobalResidualsClu1GE21_8","GEM Residuals GE21 Roll 8 Cluster Size 1",100, -1., 1.);

  hGlobalResClu2GE21_1 = dbe->book1D("GlobalResidualsClu2GE21_1","GEM Residuals GE21 Roll 1 Cluster Size 2",100, -1., 1.);
  hGlobalResClu2GE21_2 = dbe->book1D("GlobalResidualsClu2GE21_2","GEM Residuals GE21 Roll 2 Cluster Size 2",100, -1., 1.);
  hGlobalResClu2GE21_3 = dbe->book1D("GlobalResidualsClu2GE21_3","GEM Residuals GE21 Roll 3 Cluster Size 2",100, -1., 1.);
  hGlobalResClu2GE21_4 = dbe->book1D("GlobalResidualsClu2GE21_4","GEM Residuals GE21 Roll 4 Cluster Size 2",100, -1., 1.);
  hGlobalResClu2GE21_5 = dbe->book1D("GlobalResidualsClu2GE21_5","GEM Residuals GE21 Roll 5 Cluster Size 2",100, -1., 1.);
  hGlobalResClu2GE21_6 = dbe->book1D("GlobalResidualsClu2GE21_6","GEM Residuals GE21 Roll 6 Cluster Size 2",100, -1., 1.);
  hGlobalResClu2GE21_7 = dbe->book1D("GlobalResidualsClu2GE21_7","GEM Residuals GE21 Roll 7 Cluster Size 2",100, -1., 1.);
  hGlobalResClu2GE21_8 = dbe->book1D("GlobalResidualsClu2GE21_8","GEM Residuals GE21 Roll 8 Cluster Size 2",100, -1., 1.);

  hGlobalResClu3GE21_1 = dbe->book1D("GlobalResidualsClu3GE21_1","GEM Residuals GE21 Roll 1 Cluster Size 3",100, -1., 1.);
  hGlobalResClu3GE21_2 = dbe->book1D("GlobalResidualsClu3GE21_2","GEM Residuals GE21 Roll 2 Cluster Size 3",100, -1., 1.);
  hGlobalResClu3GE21_3 = dbe->book1D("GlobalResidualsClu3GE21_3","GEM Residuals GE21 Roll 3 Cluster Size 3",100, -1., 1.);
  hGlobalResClu3GE21_4 = dbe->book1D("GlobalResidualsClu3GE21_4","GEM Residuals GE21 Roll 4 Cluster Size 3",100, -1., 1.);
  hGlobalResClu3GE21_5 = dbe->book1D("GlobalResidualsClu3GE21_5","GEM Residuals GE21 Roll 5 Cluster Size 3",100, -1., 1.);
  hGlobalResClu3GE21_6 = dbe->book1D("GlobalResidualsClu3GE21_6","GEM Residuals GE21 Roll 6 Cluster Size 3",100, -1., 1.);
  hGlobalResClu3GE21_7 = dbe->book1D("GlobalResidualsClu3GE21_7","GEM Residuals GE21 Roll 7 Cluster Size 3",100, -1., 1.);
  hGlobalResClu3GE21_8 = dbe->book1D("GlobalResidualsClu3GE21_8","GEM Residuals GE21 Roll 8 Cluster Size 3",100, -1., 1.);

  folder = "Muons/MuonSegEff/Residuals/GE22";
  dbe->setCurrentFolder(folder);

  //Endcap GE22
  hGlobalResAllClsGE22_1 = dbe->book1D("GlobalResidualsAllClsGE22_1","GEM Residuals GE22 Roll 1",100, -1., 1.);
  hGlobalResAllClsGE22_2 = dbe->book1D("GlobalResidualsAllClsGE22_2","GEM Residuals GE22 Roll 2",100, -1., 1.);
  hGlobalResAllClsGE22_3 = dbe->book1D("GlobalResidualsAllClsGE22_3","GEM Residuals GE22 Roll 3",100, -1., 1.);
  hGlobalResAllClsGE22_4 = dbe->book1D("GlobalResidualsAllClsGE22_4","GEM Residuals GE22 Roll 4",100, -1., 1.);
  hGlobalResAllClsGE22_5 = dbe->book1D("GlobalResidualsAllClsGE22_5","GEM Residuals GE22 Roll 5",100, -1., 1.);
  hGlobalResAllClsGE22_6 = dbe->book1D("GlobalResidualsAllClsGE22_6","GEM Residuals GE22 Roll 6",100, -1., 1.);
  hGlobalResAllClsGE22_7 = dbe->book1D("GlobalResidualsAllClsGE22_7","GEM Residuals GE22 Roll 7",100, -1., 1.);
  hGlobalResAllClsGE22_8 = dbe->book1D("GlobalResidualsAllClsGE22_8","GEM Residuals GE22 Roll 8",100, -1., 1.);
  hGlobalResAllClsGE22_9 = dbe->book1D("GlobalResidualsAllClsGE22_9","GEM Residuals GE22 Roll 9",100, -1., 1.);
  hGlobalResAllClsGE22_10 = dbe->book1D("GlobalResidualsAllClsGE22_10","GEM Residuals GE22 Roll 10",100, -1., 1.);
  hGlobalResAllClsGE22_11 = dbe->book1D("GlobalResidualsAllClsGE22_11","GEM Residuals GE22 Roll 11",100, -1., 1.);
  hGlobalResAllClsGE22_12 = dbe->book1D("GlobalResidualsAllClsGE22_12","GEM Residuals GE22 Roll 12",100, -1., 1.);

  hGlobalResClu1GE22_1 = dbe->book1D("GlobalResidualsClu1GE22_1","GEM Residuals GE22 Roll 1 Cluster Size 1",100, -1., 1.);
  hGlobalResClu1GE22_2 = dbe->book1D("GlobalResidualsClu1GE22_2","GEM Residuals GE22 Roll 2 Cluster Size 1",100, -1., 1.);
  hGlobalResClu1GE22_3 = dbe->book1D("GlobalResidualsClu1GE22_3","GEM Residuals GE22 Roll 3 Cluster Size 1",100, -1., 1.);
  hGlobalResClu1GE22_4 = dbe->book1D("GlobalResidualsClu1GE22_4","GEM Residuals GE22 Roll 4 Cluster Size 1",100, -1., 1.);
  hGlobalResClu1GE22_5 = dbe->book1D("GlobalResidualsClu1GE22_5","GEM Residuals GE22 Roll 5 Cluster Size 1",100, -1., 1.);
  hGlobalResClu1GE22_6 = dbe->book1D("GlobalResidualsClu1GE22_6","GEM Residuals GE22 Roll 6 Cluster Size 1",100, -1., 1.);
  hGlobalResClu1GE22_7 = dbe->book1D("GlobalResidualsClu1GE22_7","GEM Residuals GE22 Roll 7 Cluster Size 1",100, -1., 1.);
  hGlobalResClu1GE22_8 = dbe->book1D("GlobalResidualsClu1GE22_8","GEM Residuals GE22 Roll 8 Cluster Size 1",100, -1., 1.);
  hGlobalResClu1GE22_9 = dbe->book1D("GlobalResidualsClu1GE22_9","GEM Residuals GE22 Roll 9 Cluster Size 1",100, -1., 1.);
  hGlobalResClu1GE22_10 = dbe->book1D("GlobalResidualsClu1GE22_10","GEM Residuals GE22 Roll 10 Cluster Size 1",100, -1., 1.);
  hGlobalResClu1GE22_11 = dbe->book1D("GlobalResidualsClu1GE22_11","GEM Residuals GE22 Roll 11 Cluster Size 1",100, -1., 1.);
  hGlobalResClu1GE22_12 = dbe->book1D("GlobalResidualsClu1GE22_12","GEM Residuals GE22 Roll 12 Cluster Size 1",100, -1., 1.);

  hGlobalResClu2GE22_1 = dbe->book1D("GlobalResidualsClu2GE22_1","GEM Residuals GE22 Roll 1 Cluster Size 2",100, -1., 1.);
  hGlobalResClu2GE22_2 = dbe->book1D("GlobalResidualsClu2GE22_2","GEM Residuals GE22 Roll 2 Cluster Size 2",100, -1., 1.);
  hGlobalResClu2GE22_3 = dbe->book1D("GlobalResidualsClu2GE22_3","GEM Residuals GE22 Roll 3 Cluster Size 2",100, -1., 1.);
  hGlobalResClu2GE22_4 = dbe->book1D("GlobalResidualsClu2GE22_4","GEM Residuals GE22 Roll 4 Cluster Size 2",100, -1., 1.);
  hGlobalResClu2GE22_5 = dbe->book1D("GlobalResidualsClu2GE22_5","GEM Residuals GE22 Roll 5 Cluster Size 2",100, -1., 1.);
  hGlobalResClu2GE22_6 = dbe->book1D("GlobalResidualsClu2GE22_6","GEM Residuals GE22 Roll 6 Cluster Size 2",100, -1., 1.);
  hGlobalResClu2GE22_7 = dbe->book1D("GlobalResidualsClu2GE22_7","GEM Residuals GE22 Roll 7 Cluster Size 2",100, -1., 1.);
  hGlobalResClu2GE22_8 = dbe->book1D("GlobalResidualsClu2GE22_8","GEM Residuals GE22 Roll 8 Cluster Size 2",100, -1., 1.);
  hGlobalResClu2GE22_9 = dbe->book1D("GlobalResidualsClu1GE22_9","GEM Residuals GE22 Roll 9 Cluster Size 1",100, -1., 1.);
  hGlobalResClu2GE22_10 = dbe->book1D("GlobalResidualsClu1GE22_10","GEM Residuals GE22 Roll 10 Cluster Size 1",100, -1., 1.);
  hGlobalResClu2GE22_11 = dbe->book1D("GlobalResidualsClu1GE22_11","GEM Residuals GE22 Roll 11 Cluster Size 1",100, -1., 1.);
  hGlobalResClu2GE22_12 = dbe->book1D("GlobalResidualsClu1GE22_12","GEM Residuals GE22 Roll 12 Cluster Size 1",100, -1., 1.);

  hGlobalResClu3GE22_1 = dbe->book1D("GlobalResidualsClu3GE22_1","GEM Residuals GE22 Roll 1 Cluster Size 3",100, -1., 1.);
  hGlobalResClu3GE22_2 = dbe->book1D("GlobalResidualsClu3GE22_2","GEM Residuals GE22 Roll 2 Cluster Size 3",100, -1., 1.);
  hGlobalResClu3GE22_3 = dbe->book1D("GlobalResidualsClu3GE22_3","GEM Residuals GE22 Roll 3 Cluster Size 3",100, -1., 1.);
  hGlobalResClu3GE22_4 = dbe->book1D("GlobalResidualsClu3GE22_4","GEM Residuals GE22 Roll 4 Cluster Size 3",100, -1., 1.);
  hGlobalResClu3GE22_5 = dbe->book1D("GlobalResidualsClu3GE22_5","GEM Residuals GE22 Roll 5 Cluster Size 3",100, -1., 1.);
  hGlobalResClu3GE22_6 = dbe->book1D("GlobalResidualsClu3GE22_6","GEM Residuals GE22 Roll 6 Cluster Size 3",100, -1., 1.);
  hGlobalResClu3GE22_7 = dbe->book1D("GlobalResidualsClu3GE22_7","GEM Residuals GE22 Roll 7 Cluster Size 3",100, -1., 1.);
  hGlobalResClu3GE22_8 = dbe->book1D("GlobalResidualsClu3GE22_8","GEM Residuals GE22 Roll 8 Cluster Size 3",100, -1., 1.);
  hGlobalResClu3GE22_9 = dbe->book1D("GlobalResidualsClu1GE22_9","GEM Residuals GE22 Roll 9 Cluster Size 1",100, -1., 1.);
  hGlobalResClu3GE22_10 = dbe->book1D("GlobalResidualsClu1GE22_10","GEM Residuals GE22 Roll 10 Cluster Size 1",100, -1., 1.);
  hGlobalResClu3GE22_11 = dbe->book1D("GlobalResidualsClu1GE22_11","GEM Residuals GE22 Roll 11 Cluster Size 1",100, -1., 1.);
  hGlobalResClu3GE22_12 = dbe->book1D("GlobalResidualsClu1GE22_12","GEM Residuals GE22 Roll 12 Cluster Size 1",100, -1., 1.);

//XY_view plots
  folder = "Muons/MuonSegEff/xyViews";
  dbe->setCurrentFolder(folder);

  XY_globalGE21 = dbe->book2D("globalXY_GE21", "globalXY_GE21", 1400, -350, 350, 1400, -350, 350);
  XY_globalGEm21 = dbe->book2D("globalXY_GEm21", "globalXY_GE-21", 1400, -350, 350, 1400, -350, 350);
  XY_globalGE11 = dbe->book2D("globalXY_GE11", "globalXY_GE11", 1400, -350, 350, 1400, -350, 350);
  XY_globalGEm11 = dbe->book2D("globalXY_GEm11", "globalXY_GE-11", 1400, -350, 350, 1400, -350, 350);
  XY_globalGE22 = dbe->book2D("globalXY_GE22", "globalXY_GE22", 1400, -350, 350, 1400, -350, 350);
  XY_globalGEm22 = dbe->book2D("globalXY_GEm22", "globalXY_GE-22", 1400, -350, 350, 1400, -350, 350);
  
  XY_globalGE21_extra = dbe->book2D("globalXY_extrapolated_GE21", "globalXY_extrapolated_GE21", 1400, -350, 350, 1400, -350, 350);
  XY_globalGEm21_extra = dbe->book2D("globalXY_extrapolated_GEm21", "globalXY_extrapolated_GE-21", 1400, -350, 350, 1400, -350, 350);
  XY_globalGE11_extra = dbe->book2D("globalXY_extrapolated_GE11", "globalXY_extrapolated_GE11", 1400, -350, 350, 1400, -350, 350);
  XY_globalGEm11_extra = dbe->book2D("globalXY_extrapolated_GEm11", "globalXY_extrapolated_GE-11", 1400, -350, 350, 1400, -350, 350);
  XY_globalGE22_extra = dbe->book2D("globalXY_extrapolated_GE22", "globalXY_extrapolated_GE22", 1400, -350, 350, 1400, -350, 350);
  XY_globalGEm22_extra = dbe->book2D("globalXY_extrapolated_GEm22", "globalXY_extrapolated_GE-22", 1400, -350, 350, 1400, -350, 350);

  if(debug) ofrej.open("rejected.txt");
  if(debug) std::cout<<"Rejected done"<<std::endl;

}

void GEMMuonSegment::beginRun(const edm::Run& run, const edm::EventSetup& iSetup){
  std::ifstream ifin(AlignmentinfoFile.c_str());

  if(manualalignment)
  {
    int rawId;
    std::string name;
    float offset;
    float rms;
    while (ifin.good()){
      ifin >>name >>rawId >> offset >> rms;
      alignmentinfo[rawId]=offset;

      if(debug) std::cout<<"rawId ="<<rawId<<" offset="<<offset<<std::endl;
    }
  }
  
  if(firstbook)
  {
    std::cout<<"bbooking all histograms"<<std::endl;
    iSetup.get<MuonGeometryRecord>().get(gemGeo);
    iSetup.get<MuonGeometryRecord>().get(cscGeo);

    for (TrackingGeometry::DetContainer::const_iterator it=gemGeo->dets().begin();it<gemGeo->dets().end();it++)
    {
      if(dynamic_cast< const GEMChamber* >( *it ) != 0 )
      {
	const GEMChamber* ch = dynamic_cast< const GEMChamber* >( *it ); 
	std::vector< const GEMEtaPartition*> roles = (ch->etaPartitions());
	for(std::vector<const GEMEtaPartition*>::const_iterator r = roles.begin();r != roles.end(); ++r)
        {
	  GEMDetId gemId = (*r)->id();
	  int region=gemId.region();

//rumi: make GEM_names:
          std::string nameRoll = GEMname(gemId);
	  if(region==0)
          {
            std::cout << "I found a GEM eta partition in the Barrel - should be wrong!" << std::endl;
            continue;
	  }
          else
          {
	    const TrapezoidalStripTopology* topE_=dynamic_cast<const TrapezoidalStripTopology*>(&((*r)->topology()));
	    float stripl = topE_->stripLength();
	    float stripw = topE_->pitch();
	    meCollection[nameRoll] = bookDetUnitSeg(gemId,(*r)->nstrips(),stripw,stripl);
	  }
	}
      }
    }
    firstbook = false;
  }
}//beginRun


GEMMuonSegment::~GEMMuonSegment()
{
}

std::string GEMMuonSegment::GEMname(const GEMDetId& _id)
{
   std::string _n = "";
   int station = _id.station();
   int region = _id.region();
   int roll = _id.roll();
   int ring = _id.ring();
   int layer = _id.layer();
   int chamber = _id.chamber();
   std::stringstream os;

   if( _n.size() < 1 )
   {
    if( region == 0 )
    {
       return "I found a GEM eta partition in the Barrel - should be wrong!";
    }
    else
    {
      os << "GE";
      os << std::setw(2) << std::setfill('+') << station * region << std::setfill(' ') << "_";
      os << "R" << ring;
      os << "_CH" << std::setw(2) << std::setfill('0') << chamber << "_L" << layer;

      if( roll == 1 )
    os << "_A";
      else if( roll == 2 )
    os << "_B";
      else if( roll == 3 )
    os << "_C";
      else if( roll == 4 )
    os << "_D";
      else if( roll == 5 )
    os << "_E";
      else if( roll == 6 )
    os << "_F";
      else if( roll == 7 )
    os << "_G";
      else if( roll == 8 )
    os << "_H";
      else if( roll == 9 )
    os << "_I";
      else if( roll == 10 )
    os << "_J";
      else if( roll == 11 )
    os << "_K";
      else if( roll == 12 )
    os << "_L";
    }
    _n = os.str();
  }
  return _n;
}

void GEMMuonSegment::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{

  if(debug) std::cout << "echo from analyze" << std::endl;
  statistics->Fill(1);
  stationstatistics->Fill(1);
  using namespace edm;

  char layerLabel[128];
  char meIdGEM [128];
  char meIdGEMbx [128];
  char meIdCSC [128];

  if(debug) std::cout <<"\t Getting the CSC Segments"<<std::endl;
  edm::Handle<CSCSegmentCollection> allCSCSegments;
  iEvent.getByToken(cscSegments, allCSCSegments);
  if(debug) std::cout<<"I got the segments"<<std::endl;
  
  if (debug && allCSCSegments->size() == 0)
    std::cout << "event without CSC segments" << iEvent.id() << std::endl;

  if(allCSCSegments->size()!=0 && allCSCSegments->size()<=16){
    statistics->Fill(2);
    statistics->Fill(allCSCSegments->size()+1);
  }
  
  if(debug) std::cout <<"\t Getting the GEM RecHits"<<std::endl;
  Handle<GEMRecHitCollection> gemHits;
  iEvent.getByToken(gemRecHitsLabel,gemHits);

  if(debug) std::cout <<"\t Getting the GEM CSC Points"<<std::endl;
  edm::Handle<GEMRecHitCollection> gemCSCPoints;
  iEvent.getByToken(gemCSCPointsLabel,gemCSCPoints);

  GEMRecHitCollection::const_iterator recHit;
  
  for(recHit = gemHits->begin(); recHit != gemHits->end(); recHit++){ //Filling DQMOccupancies
    
    int cls = recHit->clusterSize();
    int firststrip = recHit->firstClusterStrip();
    int bx = recHit->BunchX();

    GEMDetId gemId = recHit->gemId();

      std::string nameRoll = GEMname(gemId);

    if(debug) std::cout<<nameRoll<<std::endl;
    
    sprintf(meIdGEMbx,"BXDistribution_%s",nameRoll.c_str());

    sprintf(meIdGEM,"RealDetectedOccupancy_%s",nameRoll.c_str());
    
    if(debug) std::cout<<"Filling "<<nameRoll<<" with bx="<<bx<<" and cls="<<cls<<std::endl;

    std::map<std::string, MonitorElement*> meMap=meCollection[nameRoll];
    meMap[meIdGEMbx]->Fill(bx,cls);
    for(int stripDetected = firststrip; stripDetected <= firststrip+cls; stripDetected++)
    {
      meMap[meIdGEM]->Fill(stripDetected-0.5); 
    }
    int gemRegion = gemId.region();
    int gemStation = gemId.station();
    if(gemRegion==0)
    {
      std::cout << "I found a GEM in Barrel - check for something wrong" << std::endl;
    }
    else
    {
      if(gemStation==1)
        stationstatistics->Fill(2);
      if(gemStation==2)
        stationstatistics->Fill(3);
      if(gemStation==3)
        stationstatistics->Fill(4);
      if(gemStation==4)
        stationstatistics->Fill(5);
    }
  }

  if(gemCSCPoints.isValid() && (gemCSCPoints->begin()!=gemCSCPoints->end())){//No Empty Predictions
    GEMRecHitCollection::const_iterator gemPoint;
  
    for(gemPoint = gemCSCPoints->begin(); gemPoint != gemCSCPoints->end(); gemPoint++){
      LocalPoint PointExtrapolatedGEMFrame = gemPoint->localPosition();
      GEMDetId  gemId = gemPoint->gemId();

      if(debug)
        std::cout<<gemId.rawId()<<" "<<PointExtrapolatedGEMFrame.x()<<" "<<PointExtrapolatedGEMFrame.y()<<std::endl;

      double dx=0;
      double dy=0;
      double dz=0;

      CSCSegmentCollection::const_iterator segment;  

      CSCDetId CSCId;
      for (segment = allCSCSegments->begin();segment!=allCSCSegments->end(); ++segment)
      {
	CSCId = segment->cscDetId();
	int gemRegion = 1;
        if(CSCId.endcap()==2)
          gemRegion= -1;//Relacion entre las endcaps
	int gemRing = CSCId.ring();
	int gemStation = CSCId.station();
	if(gemRing==4) gemRing =1;

	if(gemRegion==gemId.region() && CSCId.station()==gemId.station() && gemRing == gemId.ring() && CSCId.chamber()==gemId.chamber())
        {
	  LocalVector segmentDirection=segment->localDirection();
	  dx=segmentDirection.x();
	  dy=segmentDirection.y();
	  dz=segmentDirection.z();
	  continue;
	}
	if(gemStation==1) stationstatistics->Fill(2);
	if(gemStation==2) stationstatistics->Fill(3);
	if(gemStation==3) stationstatistics->Fill(4);
	if(gemStation==4) stationstatistics->Fill(5);
      }
      
      const GEMEtaPartition* rollasociated = gemGeo->etaPartition(gemId);

        GlobalPoint ExtraHitPosGlob = rollasociated->toGlobal(PointExtrapolatedGEMFrame);
        if(rollasociated->id().region() == 1)
        {
          if(rollasociated->id().station()==1) XY_globalGE11_extra->Fill(ExtraHitPosGlob.x(), ExtraHitPosGlob.y());
          if(rollasociated->id().station()==2) XY_globalGE21_extra->Fill(ExtraHitPosGlob.x(), ExtraHitPosGlob.y());
          if(rollasociated->id().station()==3) XY_globalGE22_extra->Fill(ExtraHitPosGlob.x(), ExtraHitPosGlob.y());
        }

        if(rollasociated->id().region() == -1)
        {
          if(rollasociated->id().station()==1) XY_globalGEm11_extra->Fill(ExtraHitPosGlob.x(), ExtraHitPosGlob.y());
          if(rollasociated->id().station()==2) XY_globalGEm21_extra->Fill(ExtraHitPosGlob.x(), ExtraHitPosGlob.y());
          if(rollasociated->id().station()==3) XY_globalGEm22_extra->Fill(ExtraHitPosGlob.x(), ExtraHitPosGlob.y());
        }
      
      const TrapezoidalStripTopology* top_=dynamic_cast<const TrapezoidalStripTopology*>(&(rollasociated->topology()));
      LocalPoint xmin = top_->localPosition(0.);
      if(debug)
        std::cout << "CSC \t \t \t xmin of this  Roll " << xmin << "cm" << std::endl;
      LocalPoint xmax = top_->localPosition((float)rollasociated->nstrips());
      if(debug)
        std::cout << "CSC \t \t \t xmax of this  Roll " << xmax << "cm" << std::endl;
      float rsize = fabs( xmax.x()-xmin.x() );
      if(debug)
        std::cout << "CSC \t \t \t Roll Size " << rsize << "cm" << std::endl;
      float stripl = top_->stripLength();
      float stripw = top_->pitch();
      
      std::string nameRoll = GEMname(gemId);
      if(debug) std::cout << "CSC \t \t \t \t The GEMName is " << nameRoll << std::endl;
      
      const float stripPredicted = rollasociated->strip(LocalPoint(PointExtrapolatedGEMFrame.x(),PointExtrapolatedGEMFrame.y(),0.)  );
       
      if(debug) std::cout << "CSC  \t \t \t \t \t Candidate" << gemId << " " << "(from CSC Segment) STRIP---> " << stripPredicted << std::endl;
      
      //--------- HISTOGRAM STRIP PREDICTED FROM CSC  -------------------
      
      char detUnitLabel[128];
      sprintf(detUnitLabel ,"%s",nameRoll.c_str());
      sprintf(layerLabel ,"%s",nameRoll.c_str());
      
      std::map<std::string, MonitorElement*> meMap=meCollection[nameRoll];
      
      bool prediction=false;
      
      if(fabs(PointExtrapolatedGEMFrame.x()) < rsize*0.5 &&  fabs(PointExtrapolatedGEMFrame.y()) < stripl*0.5)
     {
	if(fabs(stripPredicted-rollasociated->nstrips())<1.)
          if(debug) std::cout<<"CSC \t \t \t \t Extrapolating near last strip, Event"<<iEvent.id()<<" stripPredicted="<<stripPredicted<<" Number of strips="<<rollasociated->nstrips()<<std::endl;
	if(fabs(stripPredicted)<1.)
          if(debug) std::cout<<"CSC \t \t \t \t Extrapolating near first strip, Event"<<iEvent.id()<<" stripPredicted="<<stripPredicted<<" Number of strips="<<rollasociated->nstrips()<<std::endl;
	sprintf(meIdCSC,"ExpectedOccupancy_%s",detUnitLabel);
	if(debug) std::cout << "CSC \t \t \t \t Filling Expected for " << meIdCSC << " with " << stripPredicted << std::endl;
	meMap[meIdCSC]->Fill(stripPredicted);
	prediction = true;
      }
      else
      {
	if(debug) std::cout<<"CSC \t \t \t \t In fact the extrapolation goes outside the roll was done just for 2D histograms"<<std::endl;
      }
	    		
      //-------RecHitPart Just For Residual--------
      int cluSize = 0;
      int bx =0;
      int countRecHits = 0;
      float minres = 3000.;
      
      if(debug)
        std::cout<<"CSC  \t \t \t \t \t Getting RecHits in Roll Asociated"<<std::endl;

      typedef std::pair<GEMRecHitCollection::const_iterator, GEMRecHitCollection::const_iterator> rangeRecHits;
      rangeRecHits recHitCollection =  gemHits->get(rollasociated->id());
      GEMRecHitCollection::const_iterator recHit;
      
      for (recHit = recHitCollection.first; recHit != recHitCollection.second ; recHit++)
      {
	countRecHits++;
	LocalPoint recHitPos=recHit->localPosition();
	float res=PointExtrapolatedGEMFrame.x()- recHitPos.x();

        GlobalPoint recHitPosGlob = rollasociated->toGlobal(recHitPos);
        if(rollasociated->id().region()==1)
        {
          if(rollasociated->id().station()==1) XY_globalGE11->Fill(recHitPosGlob.x(), recHitPosGlob.y());
          if(rollasociated->id().station()==2) XY_globalGE21->Fill(recHitPosGlob.x(), recHitPosGlob.y());
          if(rollasociated->id().station()==3) XY_globalGE22->Fill(recHitPosGlob.x(), recHitPosGlob.y());
        }

        if(rollasociated->id().region()==-1)
        {
          if(rollasociated->id().station()==1) XY_globalGEm11->Fill(recHitPosGlob.x(), recHitPosGlob.y());
          if(rollasociated->id().station()==2) XY_globalGEm21->Fill(recHitPosGlob.x(), recHitPosGlob.y());
          if(rollasociated->id().station()==3) XY_globalGEm22->Fill(recHitPosGlob.x(), recHitPosGlob.y());
        }

        //*straighter(rollasociated->id());//Corrections to the wrong orientations
	if(manualalignment) res = res - alignmentinfo[gemId.rawId()];	//does not work for GEM. We don't have alignment file for them
	if(debug) std::cout<<"CSC  \t \t \t \t \t \t Found Rec Hit at "<<res<<"cm of the prediction."<<std::endl;
	if(fabs(res)<fabs(minres))
        {
	  minres=res;
	  cluSize = recHit->clusterSize();
	  bx = recHit->BunchX();
	  if(debug) std::cout<<"CSC  \t \t \t \t \t \t \t New Min Res "<<res<<"cm."<<std::endl;
	}
      }
      
      bool anycoincidence = false;
      
      if(countRecHits==0)
      {
	if(debug) std::cout <<"CSC \t \t \t \t \t THIS ROLL DOESN'T HAVE ANY RECHIT"<<std::endl;
      }
      else
      {  
	assert(minres!=3000); 
	
	if(debug)
          std::cout<<"CSC \t \t \t \t \t PointExtrapolatedGEMFrame.x="<<PointExtrapolatedGEMFrame.x()<<" Minimal Residual"<<minres<<std::endl;
	if(debug)
          std::cout<<"CSC  \t \t \t \t \t Minimal Residual less than stripw*rangestrips? minres="<<minres<<" range="<<rangestrips<<" stripw="<<stripw<<" cluSize"<<cluSize<<" <=compare minres with"<<(rangestrips+cluSize*0.5)*stripw<<std::endl;
	if(fabs(minres)<=(rangestrips+cluSize*0.5)*stripw)
        {
	  if(debug) std::cout << "CSC  \t \t \t \t \t \t True!" << std::endl;
	  anycoincidence=true;
	}
      }
      
      if(debug) std::cout<<"CSC  \t \t \t \t \t "<< prediction << "\t" << anycoincidence << std::endl;
      
      if(prediction && anycoincidence)
      {
	float distobottom = stripl*0.5 + PointExtrapolatedGEMFrame.y();
	
	sprintf(meIdCSC,"BXYDistribution_%s",detUnitLabel);
	meMap[meIdCSC]->Fill(bx,distobottom);
	
	sprintf(meIdCSC,"CLSDistribution_%s",detUnitLabel);
	meMap[meIdCSC]->Fill(cluSize);
	
	if(debug)
        {
          std::cout<<"CSC  \t \t \t \t \t At least one RecHit inside the range, Predicted="<<stripPredicted<<" minres="<<minres<<"cm range="<<rangestrips<<"strips stripw="<<stripw<<"cm"<<std::endl;
          std::cout<<"CSC  \t \t \t \t \t Norm of Cosine Directors="<<dx*dx+dy*dy+dz*dz<<"~1?"<<std::endl;
        }
	
	//----RESIDUALS----

	if(inves){
	  float cosal = dx/sqrt(dx*dx+dz*dz);
	  float angle = acos(cosal)*180/3.1415926;

          ScatterPlotAngCLSEndcaps->Fill(angle,cluSize);
              
          if(cluSize==1*dupli) AngClu1Endcaps->Fill(angle);
          if(cluSize==2*dupli) AngClu2Endcaps->Fill(angle);
          if(cluSize==3*dupli) AngClu3Endcaps->Fill(angle);

	  if(debug) std::cout<<"CSC \t \t \t \t \t Angle="<<angle<<" degree"<<std::endl;

	  //Filling Residuals
            if(!(gemId.ring()==1)) {std::cout << "something is wrong - GEM is on the ring = " << gemId.ring() << std::endl; continue;}
            if(gemId.station() == 1)
            {
              if(gemId.roll() == 1)  hGlobalResAllClsGE11_1->Fill(minres);
              else if(gemId.roll() == 2) hGlobalResAllClsGE11_2->Fill(minres);
              else if(gemId.roll() == 3) hGlobalResAllClsGE11_3->Fill(minres);
              else if(gemId.roll() == 4) hGlobalResAllClsGE11_4->Fill(minres);
              else if(gemId.roll() == 5) hGlobalResAllClsGE11_5->Fill(minres);
              else if(gemId.roll() == 6) hGlobalResAllClsGE11_6->Fill(minres);
              else if(gemId.roll() == 7) hGlobalResAllClsGE11_7->Fill(minres);
              else if(gemId.roll() == 8) hGlobalResAllClsGE11_8->Fill(minres);
              else std::cout << "more than 8 rolls in a GEM chamber, please fix the hardcoded values" << std::endl;
//now per cls
              if (cluSize == 1 * dupli)
              {
                if(gemId.roll() == 1) hGlobalResClu1GE11_1->Fill(minres);
                else if(gemId.roll() == 2) hGlobalResClu1GE11_2->Fill(minres);
                else if(gemId.roll() == 3) hGlobalResClu1GE11_3->Fill(minres);
                else if(gemId.roll() == 4) hGlobalResClu1GE11_4->Fill(minres);
                else if(gemId.roll() == 5) hGlobalResClu1GE11_5->Fill(minres);
                else if(gemId.roll() == 6) hGlobalResClu1GE11_6->Fill(minres);
                else if(gemId.roll() == 7) hGlobalResClu1GE11_7->Fill(minres);
                else if(gemId.roll() == 8) hGlobalResClu1GE11_8->Fill(minres);
                else std::cout << "more than 8 rolls in a GEM chamber, please fix the hardcoded values" << std::endl;
              }
              if (cluSize == 2 * dupli)
              {
                if(gemId.roll() == 1) hGlobalResClu2GE11_1->Fill(minres);
                else if(gemId.roll() == 2) hGlobalResClu2GE11_2->Fill(minres);
                else if(gemId.roll() == 3) hGlobalResClu2GE11_3->Fill(minres);
                else if(gemId.roll() == 4) hGlobalResClu2GE11_4->Fill(minres);
                else if(gemId.roll() == 5) hGlobalResClu2GE11_5->Fill(minres);
                else if(gemId.roll() == 6) hGlobalResClu2GE11_6->Fill(minres);
                else if(gemId.roll() == 7) hGlobalResClu2GE11_7->Fill(minres);
                else if(gemId.roll() == 8) hGlobalResClu2GE11_8->Fill(minres);
                else std::cout << "more than 8 rolls in a GEM chamber, please fix the hardcoded values" << std::endl;
              }
              if (cluSize == 3 * dupli)
              {
                if(gemId.roll() == 1) hGlobalResClu3GE11_1->Fill(minres);
                else if(gemId.roll() == 2) hGlobalResClu3GE11_2->Fill(minres);
                else if(gemId.roll() == 3) hGlobalResClu3GE11_3->Fill(minres);
                else if(gemId.roll() == 4) hGlobalResClu3GE11_4->Fill(minres);
                else if(gemId.roll() == 5) hGlobalResClu3GE11_5->Fill(minres);
                else if(gemId.roll() == 6) hGlobalResClu3GE11_6->Fill(minres);
                else if(gemId.roll() == 7) hGlobalResClu3GE11_7->Fill(minres);
                else if(gemId.roll() == 8) hGlobalResClu3GE11_8->Fill(minres);
                else std::cout << "more than 8 rolls in a GEM chamber, please fix the hardcoded values" << std::endl;
              }
            }
            if(gemId.station() == 2)
            {
              if(gemId.roll() == 1)  hGlobalResAllClsGE21_1->Fill(minres);
              else if(gemId.roll() == 2) hGlobalResAllClsGE21_2->Fill(minres);
              else if(gemId.roll() == 3) hGlobalResAllClsGE21_3->Fill(minres);
              else if(gemId.roll() == 4) hGlobalResAllClsGE21_4->Fill(minres);
              else if(gemId.roll() == 5) hGlobalResAllClsGE21_5->Fill(minres);
              else if(gemId.roll() == 6) hGlobalResAllClsGE21_6->Fill(minres);
              else if(gemId.roll() == 7) hGlobalResAllClsGE21_7->Fill(minres);
              else if(gemId.roll() == 8) hGlobalResAllClsGE21_8->Fill(minres);
              else std::cout << "more than 8 rolls in a GEM chamber, please fix the hardcoded values" << std::endl;
//now per cls
              if (cluSize == 1 * dupli)
              {
                if(gemId.roll() == 1) hGlobalResClu1GE21_1->Fill(minres);
                else if(gemId.roll() == 2) hGlobalResClu1GE21_2->Fill(minres);
                else if(gemId.roll() == 3) hGlobalResClu1GE21_3->Fill(minres);
                else if(gemId.roll() == 4) hGlobalResClu1GE21_4->Fill(minres);
                else if(gemId.roll() == 5) hGlobalResClu1GE21_5->Fill(minres);
                else if(gemId.roll() == 6) hGlobalResClu1GE21_6->Fill(minres);
                else if(gemId.roll() == 7) hGlobalResClu1GE21_7->Fill(minres);
                else if(gemId.roll() == 8) hGlobalResClu1GE21_8->Fill(minres);
                else std::cout << "more than 8 rolls in a GEM chamber, please fix the hardcoded values" << std::endl;
              }
              if (cluSize == 2 * dupli)
              {
                if(gemId.roll() == 1) hGlobalResClu2GE21_1->Fill(minres);
                else if(gemId.roll() == 2) hGlobalResClu2GE21_2->Fill(minres);
                else if(gemId.roll() == 3) hGlobalResClu2GE21_3->Fill(minres);
                else if(gemId.roll() == 4) hGlobalResClu2GE21_4->Fill(minres);
                else if(gemId.roll() == 5) hGlobalResClu2GE21_5->Fill(minres);
                else if(gemId.roll() == 6) hGlobalResClu2GE21_6->Fill(minres);
                else if(gemId.roll() == 7) hGlobalResClu2GE21_7->Fill(minres);
                else if(gemId.roll() == 8) hGlobalResClu2GE21_8->Fill(minres);
                else std::cout << "more than 8 rolls in a GEM chamber, please fix the hardcoded values" << std::endl;
              }
              if (cluSize == 3 * dupli)
              {
                if(gemId.roll() == 1) hGlobalResClu3GE21_1->Fill(minres);
                else if(gemId.roll() == 2) hGlobalResClu3GE21_2->Fill(minres);
                else if(gemId.roll() == 3) hGlobalResClu3GE21_3->Fill(minres);
                else if(gemId.roll() == 4) hGlobalResClu3GE21_4->Fill(minres);
                else if(gemId.roll() == 5) hGlobalResClu3GE21_5->Fill(minres);
                else if(gemId.roll() == 6) hGlobalResClu3GE21_6->Fill(minres);
                else if(gemId.roll() == 7) hGlobalResClu3GE21_7->Fill(minres);
                else if(gemId.roll() == 8) hGlobalResClu3GE21_8->Fill(minres);
                else std::cout << "more than 8 rolls in a GEM chamber, please fix the hardcoded values" << std::endl;
              }
            }
            if(gemId.station() == 3)
            {
              if(gemId.roll() == 1)  hGlobalResAllClsGE22_1->Fill(minres);
              else if(gemId.roll() == 2) hGlobalResAllClsGE22_2->Fill(minres);
              else if(gemId.roll() == 3) hGlobalResAllClsGE22_3->Fill(minres);
              else if(gemId.roll() == 4) hGlobalResAllClsGE22_4->Fill(minres);
              else if(gemId.roll() == 5) hGlobalResAllClsGE22_5->Fill(minres);
              else if(gemId.roll() == 6) hGlobalResAllClsGE22_6->Fill(minres);
              else if(gemId.roll() == 7) hGlobalResAllClsGE22_7->Fill(minres);
              else if(gemId.roll() == 8) hGlobalResAllClsGE22_8->Fill(minres);
              else if(gemId.roll() == 9) hGlobalResAllClsGE22_9->Fill(minres);
              else if(gemId.roll() == 10) hGlobalResAllClsGE22_10->Fill(minres);
              else if(gemId.roll() == 11) hGlobalResAllClsGE22_11->Fill(minres);
              else if(gemId.roll() == 12) hGlobalResAllClsGE22_12->Fill(minres);
              else std::cout << "more than 12 rolls in a GEM chamber, please fix the hardcoded values" << std::endl;
//now per cls
              if (cluSize == 1 * dupli)
              {
                if(gemId.roll() == 1) hGlobalResClu1GE22_1->Fill(minres);
                else if(gemId.roll() == 2) hGlobalResClu1GE22_2->Fill(minres);
                else if(gemId.roll() == 3) hGlobalResClu1GE22_3->Fill(minres);
                else if(gemId.roll() == 4) hGlobalResClu1GE22_4->Fill(minres);
                else if(gemId.roll() == 5) hGlobalResClu1GE22_5->Fill(minres);
                else if(gemId.roll() == 6) hGlobalResClu1GE22_6->Fill(minres);
                else if(gemId.roll() == 7) hGlobalResClu1GE22_7->Fill(minres);
                else if(gemId.roll() == 8) hGlobalResClu1GE22_8->Fill(minres);
                else if(gemId.roll() == 9) hGlobalResClu1GE22_9->Fill(minres);
                else if(gemId.roll() == 10) hGlobalResClu1GE22_10->Fill(minres);
                else if(gemId.roll() == 11) hGlobalResClu1GE22_11->Fill(minres);
                else if(gemId.roll() == 12) hGlobalResClu1GE22_12->Fill(minres);
              }
              if (cluSize == 2 * dupli)
              {
                if(gemId.roll() == 1) hGlobalResClu2GE22_1->Fill(minres);
                else if(gemId.roll() == 2) hGlobalResClu2GE22_2->Fill(minres);
                else if(gemId.roll() == 3) hGlobalResClu2GE22_3->Fill(minres);
                else if(gemId.roll() == 4) hGlobalResClu2GE22_4->Fill(minres);
                else if(gemId.roll() == 5) hGlobalResClu2GE22_5->Fill(minres);
                else if(gemId.roll() == 6) hGlobalResClu2GE22_6->Fill(minres);
                else if(gemId.roll() == 7) hGlobalResClu2GE22_7->Fill(minres);
                else if(gemId.roll() == 8) hGlobalResClu2GE22_8->Fill(minres);
                else if(gemId.roll() == 9) hGlobalResClu2GE22_9->Fill(minres);
                else if(gemId.roll() == 10) hGlobalResClu2GE22_10->Fill(minres);
                else if(gemId.roll() == 11) hGlobalResClu2GE22_11->Fill(minres);
                else if(gemId.roll() == 12) hGlobalResClu2GE22_12->Fill(minres);
              }
              if (cluSize == 3 * dupli)
              {
                if(gemId.roll() == 1) hGlobalResClu3GE22_1->Fill(minres);
                else if(gemId.roll() == 2) hGlobalResClu3GE22_2->Fill(minres);
                else if(gemId.roll() == 3) hGlobalResClu3GE22_3->Fill(minres);
                else if(gemId.roll() == 4) hGlobalResClu3GE22_4->Fill(minres);
                else if(gemId.roll() == 5) hGlobalResClu3GE22_5->Fill(minres);
                else if(gemId.roll() == 6) hGlobalResClu3GE22_6->Fill(minres);
                else if(gemId.roll() == 7) hGlobalResClu3GE22_7->Fill(minres);
                else if(gemId.roll() == 8) hGlobalResClu3GE22_8->Fill(minres);
                else if(gemId.roll() == 9) hGlobalResClu3GE22_9->Fill(minres);
                else if(gemId.roll() == 10) hGlobalResClu3GE22_10->Fill(minres);
                else if(gemId.roll() == 11) hGlobalResClu3GE22_11->Fill(minres);
                else if(gemId.roll() == 12) hGlobalResClu3GE22_12->Fill(minres);
              }
            }

	  //------------------------
	}
	
	if(cluSize == 1*dupli)
        {
	  sprintf(meIdGEM,"GEMResiduals_Clu1_%s",detUnitLabel);
	  meMap[meIdGEM]->Fill(minres);
	}
        else if(cluSize == 2*dupli)
        {
	  sprintf(meIdGEM,"GEMResiduals_Clu2_%s",detUnitLabel);
	  meMap[meIdGEM]->Fill(minres);
	}
        else if(cluSize == 3*dupli)
        {
	  sprintf(meIdGEM,"GEMResiduals_Clu3_%s",detUnitLabel);
	  meMap[meIdGEM]->Fill(minres);
	}
        else
        {
	  sprintf(meIdGEM,"GEMResiduals_Other_%s",detUnitLabel);
	  meMap[meIdGEM]->Fill(minres);
	}
	
	sprintf(meIdGEM,"GEMDataOccupancy_%s",detUnitLabel);
	meMap[meIdGEM]->Fill(stripPredicted);
	
	if(debug) std::cout <<"CSC \t \t \t \t \t \t COINCEDENCE!!! Event="<<iEvent.id()<<"Filling Filling GEM Data Occupancy for "<<meIdGEM<<" with "<<stripPredicted<<std::endl;
      }//prediction && anycoincidence
      
      if(anycoincidence)
      {
	if(debug) std::cout<<"CSC \t \t \t \t \t \t Filling 2D histo for GEM Occupancy "<<meIdGEM<<std::endl; 	
	sprintf(meIdGEM,"GEMDataOccupancy2D_%s",detUnitLabel);
	meMap[meIdGEM]->Fill(PointExtrapolatedGEMFrame.x(),PointExtrapolatedGEMFrame.y());
      }//anycoincidence
      else if(prediction)
      {
        std::string nameRoll = GEMname(gemId);
//	sprintf(meIdGEM,"Inefficiency2D_%s",detUnitLabel);
//	meMap[meIdGEM]->Fill(PointExtrapolatedGEMFrame.x(),PointExtrapolatedGEMFrame.y());
	
	if(debug) std::cout<<"CSC \t \t \t \t \t \t A roll was ineficient in event"<<iEvent.id().event()<<std::endl;
	if(debug) ofrej<<"CSC \t EndCap " << gemId.region() <<"\t Roll "<<nameRoll <<"\t CSCId "<<CSCId <<"\t Event " <<iEvent.id().event() << "\t Run " << iEvent.id().run() << std::endl;
      }
      else
      {
	if(debug)
          std::cout << "CSC \t \t \t \t No the prediction is outside of this roll" << std::endl;
      }//Condition for the right match
    }
  }
}

void GEMMuonSegment::endRun(const edm::Run& r, const edm::EventSetup& iSetup){
}


void GEMMuonSegment::endJob()
{
  std::cout<<"saving root file"<<std::endl;
  if (EffSaveRootFile){
    dbe->save(EffRootFileName);
  }
  dbe = 0;
}

DEFINE_FWK_MODULE(GEMMuonSegment);
