import FWCore.ParameterSet.Config as cms
process = cms.Process("OwnParticles")

# process.load("Geometry.MuonCommonData.muonIdealGeometryXML_cfi")

#process.load("Configuration.StandardSequences.GeometryRecoDB_cff")
#process.load("Configuration.StandardSequences.GeometryDB_cff")

process.load("Geometry.MuonNumbering.muonNumberingInitialization_cfi")
process.load("DQMServices.Components.MEtoEDMConverter_cfi")
process.load("DQMServices.Core.DQM_cfg")
#process.load("Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff")
process.load('Configuration.StandardSequences.MagneticField_38T_PostLS1_cff')
process.load("Configuration.StandardSequences.MagneticField_cff")

process.load('Configuration.Geometry.GeometryExtended2023MuonReco_cff')
process.load('Configuration.Geometry.GeometryExtended2023Muon_cff')
process.load('Configuration.Geometry.GeometryExtended2023HGCalMuonReco_cff')

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'PH2_1K_FB_V6::All', '')



# do Stand Alone Muon reconstruction
# ----------------------------------
# in RPCMonitor files there are     
# - no StandAloneMuons reconstructed
# - only Rechits and Segments are   
#   reconstructed (RecoLocalMuon)   
# ----------------------------------
#	rumi		process.load("MuonTools.StandardSequences.RecoStandAloneMuon_cff")
# have stareco use hlt digis
# (change all input tags in offline reco config to use hlt tags)
#process.load("MuonTools.Configuration.HltMuonDigis_cff")
# have stareco use hlt segments (1)
# (change all input tags in offline reco config to use hlt tags)
#process.load("MuonTools.Configuration.HltMuonSegments_cff")
# keep stareco from using rpcs
#	rumi		process.load("MuonTools.Configuration.StandAloneNoRpc_cff")
# do we need this?
# process.load("RecoTracker.IterativeTracking.MuonSeededStep_cff")
# process.load("RecoTracker.CkfPattern.GroupedCkfTrajectoryBuilder_cfi")
# import RecoTracker.CkfPattern.GroupedCkfTrajectoryBuilder_cfi         
#	rumi		process.load("RecoTracker.CkfPattern.GroupedCkfTrajectoryBuilder_cff")


process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(1300)
)

#readFiles = cms.untracked.vstring()
#secFiles = cms.untracked.vstring() 
#source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
#readFiles.extend( [
#] );
#secFiles.extend( [
#               ] )


process.source = cms.Source("PoolSource",
   fileNames = cms.untracked.vstring(
#'root://xrootd-cms.infn.it//store/user/rgupta/Signal/CMSSW_620SLHC27_SingleMuPt100_Reco_8June/160608_035354/0000/step3_1.root'


#'file:out_STA_reco_GE21Upd_pT100_102.root',
#'file:out_STA_reco_GE21Upd_pT100_103.root',
#'file:out_STA_reco_GE21Upd_pT100_110.root',
#'file:out_STA_reco_GE21Upd_pT100_111.root',
#'file:out_STA_reco_GE21Upd_pT100_112.root',
#'file:out_STA_reco_GE21Upd_pT100_113.root',
#'file:out_STA_reco_GE21Upd_pT100_114.root',
#'file:out_STA_reco_GE21Upd_pT100_115.root',
#'file:out_STA_reco_GE21Upd_pT100_116.root',
#'file:out_STA_reco_GE21Upd_pT100_117.root',
#'file:out_STA_reco_GE21Upd_pT100_1.root',
#'file:out_STA_reco_GE21Upd_pT100_2.root',
#'file:out_STA_reco_GE21Upd_pT100_3.root',

'file:out_STA_reco_GE21Upd_pT100_100.root',
'file:out_STA_reco_GE21Upd_pT100_101.root',
'file:out_STA_reco_GE21Upd_pT100_102.root',
'file:out_STA_reco_GE21Upd_pT100_103.root',
'file:out_STA_reco_GE21Upd_pT100_104.root',
'file:out_STA_reco_GE21Upd_pT100_105.root',
'file:out_STA_reco_GE21Upd_pT100_106.root',
'file:out_STA_reco_GE21Upd_pT100_107.root',
'file:out_STA_reco_GE21Upd_pT100_108.root',
'file:out_STA_reco_GE21Upd_pT100_109.root',
'file:out_STA_reco_GE21Upd_pT100_110.root',
'file:out_STA_reco_GE21Upd_pT100_111.root',
'file:out_STA_reco_GE21Upd_pT100_112.root',



#with pseudodigis
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_1.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_10.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_100.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_101.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_102.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_103.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_104.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_105.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_106.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_107.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_108.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_109.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_11.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_110.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_111.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_112.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_113.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_114.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_115.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_116.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_117.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_118.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_119.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_12.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_120.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_121.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_122.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_123.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_124.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_125.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_126.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_127.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_128.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_129.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_13.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_130.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_131.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_132.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_133.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_134.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_135.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_136.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_137.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_138.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_139.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_14.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_140.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_141.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_142.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_143.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_144.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_145.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_146.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_147.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_148.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_149.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_15.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_150.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_151.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_152.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_153.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_154.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_155.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_156.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_157.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_158.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_159.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_16.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_160.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_161.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_162.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_163.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_164.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_165.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_166.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_167.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_168.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_169.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_17.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_170.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_171.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_172.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_173.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_174.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_175.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_176.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_177.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_178.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_179.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_18.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_180.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_181.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_182.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_183.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_184.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_185.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_186.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_187.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_188.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_189.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_19.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_190.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_191.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_192.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_193.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_194.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_195.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_196.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_197.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_198.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_199.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_2.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_20.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_200.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_201.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_202.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_203.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_204.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_205.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_206.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_207.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_208.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_209.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_21.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_210.root',
       'root://xrootd-cms.infn.it//store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_500um/160908_215201/0000/out_STA_reco_GE21Upd_pT100_211.root'

)
)

process.dTandCSCSegmentsinTracks = cms.EDProducer("DTandCSCSegmentsinTracks",
                                                  cscSegments = cms.untracked.InputTag("cscSegments"),
                                                  tracks = cms.untracked.InputTag("standAloneMuons","UpdatedAtVtx")
                                                  )



process.gemPointProducer = cms.EDProducer('GEMPointProducer',
  inclcsc = cms.untracked.bool(True),
  incltrack =  cms.untracked.bool(False),
  debug = cms.untracked.bool(False),
  rangestrips = cms.untracked.double(4.),
  rangestripsRB4 = cms.untracked.double(4.),
  MinCosAng = cms.untracked.double(0.85),
  MaxD = cms.untracked.double(80.0),
  MaxDrb4 = cms.untracked.double(150.0),
  ExtrapolatedRegion = cms.untracked.double(0.6), # in stripl/2 in Y and stripw*nstrips/2 in X
  cscSegments = cms.InputTag('cscSegments', '', 'RECO'),
  tracks = cms.InputTag("standAloneMuons"),
  TrackTransformer = cms.PSet(
      DoPredictionsOnly = cms.bool(False),
      Fitter = cms.string('KFFitterForRefitInsideOut'),
      TrackerRecHitBuilder = cms.string('WithTrackAngle'),
      Smoother = cms.string('KFSmootherForRefitInsideOut'),
      MuonRecHitBuilder = cms.string('MuonRecHitBuilder'),
      RefitDirection = cms.string('alongMomentum'),
      RefitRPCHits = cms.bool(False),
      Propagator = cms.string('SmartPropagatorAnyRKOpposite')
  )
)

process.museg = cms.EDAnalyzer("GEMMuonSegmentPseudo",
    inclcsc = cms.untracked.bool(True),
    debug = cms.untracked.bool(False),
    inves = cms.untracked.bool(True),
    DuplicationCorrection = cms.untracked.int32(1),
    manualalignment = cms.untracked.bool(False),
    AliFileName = cms.untracked.string(''),
#    rangestrips = cms.untracked.double(4.),
#    gemRecHits = cms.untracked.InputTag("gemRecHits"),
#    gemRecHits = cms.untracked.InputTag("gemRecHits", "STARECO"),
    gemRecHits = cms.untracked.InputTag('gemRecHits', '', 'STARECO'),
    cscSegments = cms.untracked.InputTag('cscSegments'),
    gemCSCPoints = cms.untracked.InputTag("gemPointProducer","GEMCSCExtrapolatedPoints"),
    EffSaveRootFile = cms.untracked.bool(True),
    EffRootFileName = cms.untracked.string('testGEMreso_100um.root'),
    EffSaveRootFileEventsInterval = cms.untracked.int32(100)
)


#process.p = cms.Path(process.muonstandalonereco*process.dTandCSCSegmentsinTracks*process.gemPointProducer*process.museg)
#process.p = cms.Path(process.dTandCSCSegmentsinTracks*process.gemPointProducer*process.museg)
process.p = cms.Path(process.gemPointProducer*process.museg)	#under test
#process.p = cms.Path(process.gemPointProducer)	#this step ie working

# Automatic addition of the customisation function from SLHCUpgradeSimulations.Configuration.combinedCustoms
from SLHCUpgradeSimulations.Configuration.combinedCustoms import cust_2023HGCalMuon

#call to customisation function cust_2023HGCalMuon imported from SLHCUpgradeSimulations.Configuration.combinedCustoms
process = cust_2023HGCalMuon(process)

# Automatic addition of the customisation function from Configuration.DataProcessing.Utils
from Configuration.DataProcessing.Utils import addMonitoring

#call to customisation function addMonitoring imported from Configuration.DataProcessing.Utils
process = addMonitoring(process)

# Automatic addition of the customisation function from Geometry.GEMGeometry.gemGeometryCustoms
from Geometry.GEMGeometry.gemGeometryCustoms import custom_GE11_8and8partitions_v2

#call to customisation function custom_GE11_8and8partitions_v2 imported from Geometry.GEMGeometry.gemGeometryCustoms
process = custom_GE11_8and8partitions_v2(process)

# End of customisation functions


