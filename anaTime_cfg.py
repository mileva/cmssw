import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.load('Configuration.Geometry.GeometryExtended2023Reco_cff')
process.load('Configuration.Geometry.GeometryExtended2023_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
#process.GlobalTag.pfnPrefix = cms.untracked.string('frontier://FrontierProd/')
process.load('Configuration.StandardSequences.MagneticField_38T_PostLS1_cff')
#process.GlobalTag.globaltag = 'PH2_1K_FB_V2::All'
#process.GlobalTag.globaltag = 'DES23_62_V1::All'
process.GlobalTag.globaltag = 'DES19_62_V8::All'
process.maxEvents = cms.untracked.PSet(
     input = cms.untracked.int32(-1) 
)

#process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )
#process.Tracer = cms.Service("Tracer")
readFiles = cms.untracked.vstring()
process.source = cms.Source ("PoolSource",fileNames = readFiles)
readFiles.extend( [
'root://xrootd.ba.infn.it//store/user/calabria/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/calabria_DYToMuMu_GEN-SIM-DIGI-RECO_CMSSW_6_2_0_SLHC12_2023Scenario_3Step/7e82c0353afc1625567b3844e4c947b8/step3_1000_1_HIo.root',
'root://xrootd.ba.infn.it//store/user/calabria/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/calabria_DYToMuMu_GEN-SIM-DIGI-RECO_CMSSW_6_2_0_SLHC12_2023Scenario_3Step/7e82c0353afc1625567b3844e4c947b8/step3_1001_1_PG2.root',
'root://xrootd.ba.infn.it//store/user/calabria/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/calabria_DYToMuMu_GEN-SIM-DIGI-RECO_CMSSW_6_2_0_SLHC12_2023Scenario_3Step/7e82c0353afc1625567b3844e4c947b8/step3_1002_1_tVX.root',
'root://xrootd.ba.infn.it//store/user/calabria/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/calabria_DYToMuMu_GEN-SIM-DIGI-RECO_CMSSW_6_2_0_SLHC12_2023Scenario_3Step/7e82c0353afc1625567b3844e4c947b8/step3_1003_1_0rr.root',
'root://xrootd.ba.infn.it//store/user/calabria/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/calabria_DYToMuMu_GEN-SIM-DIGI-RECO_CMSSW_6_2_0_SLHC12_2023Scenario_3Step/7e82c0353afc1625567b3844e4c947b8/step3_1004_1_uAL.root',
'root://xrootd.ba.infn.it//store/user/calabria/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/calabria_DYToMuMu_GEN-SIM-DIGI-RECO_CMSSW_6_2_0_SLHC12_2023Scenario_3Step/7e82c0353afc1625567b3844e4c947b8/step3_1005_1_Vdx.root',
'root://xrootd.ba.infn.it//store/user/calabria/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/calabria_DYToMuMu_GEN-SIM-DIGI-RECO_CMSSW_6_2_0_SLHC12_2023Scenario_3Step/7e82c0353afc1625567b3844e4c947b8/step3_1006_1_1Yg.root',
'root://xrootd.ba.infn.it//store/user/calabria/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/calabria_DYToMuMu_GEN-SIM-DIGI-RECO_CMSSW_6_2_0_SLHC12_2023Scenario_3Step/7e82c0353afc1625567b3844e4c947b8/step3_1007_1_0Ca.root',
'root://xrootd.ba.infn.it//store/user/calabria/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/calabria_DYToMuMu_GEN-SIM-DIGI-RECO_CMSSW_6_2_0_SLHC12_2023Scenario_3Step/7e82c0353afc1625567b3844e4c947b8/step3_1008_1_ih1.root',
'root://xrootd.ba.infn.it//store/user/calabria/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/calabria_DYToMuMu_GEN-SIM-DIGI-RECO_CMSSW_6_2_0_SLHC12_2023Scenario_3Step/7e82c0353afc1625567b3844e4c947b8/step3_1009_1_z9J.root',
'root://xrootd.ba.infn.it//store/user/calabria/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/calabria_DYToMuMu_GEN-SIM-DIGI-RECO_CMSSW_6_2_0_SLHC12_2023Scenario_3Step/7e82c0353afc1625567b3844e4c947b8/step3_100_1_IWN.root',
'root://xrootd.ba.infn.it//store/user/calabria/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/calabria_DYToMuMu_GEN-SIM-DIGI-RECO_CMSSW_6_2_0_SLHC12_2023Scenario_3Step/7e82c0353afc1625567b3844e4c947b8/step3_1010_1_FKE.root',
'root://xrootd.ba.infn.it//store/user/calabria/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/calabria_DYToMuMu_GEN-SIM-DIGI-RECO_CMSSW_6_2_0_SLHC12_2023Scenario_3Step/7e82c0353afc1625567b3844e4c947b8/step3_1011_1_6aT.root',
'root://xrootd.ba.infn.it//store/user/calabria/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/calabria_DYToMuMu_GEN-SIM-DIGI-RECO_CMSSW_6_2_0_SLHC12_2023Scenario_3Step/7e82c0353afc1625567b3844e4c947b8/step3_1012_1_qI3.root',
'root://xrootd.ba.infn.it//store/user/calabria/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/calabria_DYToMuMu_GEN-SIM-DIGI-RECO_CMSSW_6_2_0_SLHC12_2023Scenario_3Step/7e82c0353afc1625567b3844e4c947b8/step3_1013_1_WrC.root',
'root://xrootd.ba.infn.it//store/user/calabria/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/calabria_DYToMuMu_GEN-SIM-DIGI-RECO_CMSSW_6_2_0_SLHC12_2023Scenario_3Step/7e82c0353afc1625567b3844e4c947b8/step3_1014_1_Gms.root',
'root://xrootd.ba.infn.it//store/user/calabria/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/calabria_DYToMuMu_GEN-SIM-DIGI-RECO_CMSSW_6_2_0_SLHC12_2023Scenario_3Step/7e82c0353afc1625567b3844e4c947b8/step3_1015_1_WMY.root',
'root://xrootd.ba.infn.it//store/user/calabria/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/calabria_DYToMuMu_GEN-SIM-DIGI-RECO_CMSSW_6_2_0_SLHC12_2023Scenario_3Step/7e82c0353afc1625567b3844e4c947b8/step3_1016_1_47f.root',
'root://xrootd.ba.infn.it//store/user/calabria/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/calabria_DYToMuMu_GEN-SIM-DIGI-RECO_CMSSW_6_2_0_SLHC12_2023Scenario_3Step/7e82c0353afc1625567b3844e4c947b8/step3_1017_1_Gzc.root',
'root://xrootd.ba.infn.it//store/user/calabria/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/calabria_DYToMuMu_GEN-SIM-DIGI-RECO_CMSSW_6_2_0_SLHC12_2023Scenario_3Step/7e82c0353afc1625567b3844e4c947b8/step3_1018_1_TBe.root',
'root://xrootd.ba.infn.it//store/user/calabria/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/calabria_DYToMuMu_GEN-SIM-DIGI-RECO_CMSSW_6_2_0_SLHC12_2023Scenario_3Step/7e82c0353afc1625567b3844e4c947b8/step3_1019_1_dxz.root',
'root://xrootd.ba.infn.it//store/user/calabria/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/calabria_DYToMuMu_GEN-SIM-DIGI-RECO_CMSSW_6_2_0_SLHC12_2023Scenario_3Step/7e82c0353afc1625567b3844e4c947b8/step3_101_1_5pj.root',
'root://xrootd.ba.infn.it//store/user/calabria/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/calabria_DYToMuMu_GEN-SIM-DIGI-RECO_CMSSW_6_2_0_SLHC12_2023Scenario_3Step/7e82c0353afc1625567b3844e4c947b8/step3_1020_1_0B8.root',
'root://xrootd.ba.infn.it//store/user/calabria/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/calabria_DYToMuMu_GEN-SIM-DIGI-RECO_CMSSW_6_2_0_SLHC12_2023Scenario_3Step/7e82c0353afc1625567b3844e4c947b8/step3_1021_1_2jn.root'

]);

process.checkMuSize = cms.EDFilter("MuonsizeFilter"
                                            )
## require scraping filter
process.scrapingVeto = cms.EDFilter("FilterOutScraping",
                                     applyfilter = cms.untracked.bool(True),
                                     debugOn = cms.untracked.bool(False),
                                     numtrack = cms.untracked.uint32(10),
                                     thresh = cms.untracked.double(0.2)
                                     )

process.primaryVertexFilter = cms.EDFilter("GoodVertexFilter",
                                            vertexCollection = cms.InputTag('offlinePrimaryVertices'),
                                            minimumNDOF = cms.uint32(4) ,
                                            maxAbsZ = cms.double(24),
                                            maxd0 = cms.double(2)
                                            )


#from SimGeneral.MixingModule.mixNoPU_cfi                          import *
#from SimGeneral.TrackingAnalysis.trackingParticlesNoSimHits_cfi   import * 
#from SimMuon.MCTruth.MuonAssociatorByHitsESProducer_NoSimHits_cfi import *

process.load('MuonAnalysis.MuonAssociators.anaTime_cfi')

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('muTime_histos.root')
)

#process.demo = cms.EDAnalyzer('AnaTime'
#)

process.p = cms.Path(process.demo)
