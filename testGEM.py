import FWCore.ParameterSet.Config as cms
process = cms.Process("OwnParticles")

# process.load("Geometry.MuonCommonData.muonIdealGeometryXML_cfi")

#process.load("Configuration.StandardSequences.GeometryRecoDB_cff")
#process.load("Configuration.StandardSequences.GeometryDB_cff")

process.load("Geometry.MuonNumbering.muonNumberingInitialization_cfi")
process.load("DQMServices.Components.MEtoEDMConverter_cfi")
process.load("DQMServices.Core.DQM_cfg")
#process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")

#process.load("Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff")
process.load('Configuration.StandardSequences.MagneticField_38T_PostLS1_cff')
process.load("Configuration.StandardSequences.MagneticField_cff")

process.load('Configuration.Geometry.GeometryExtended2023MuonReco_cff')
process.load('Configuration.Geometry.GeometryExtended2023Muon_cff')
process.load('Configuration.Geometry.GeometryExtended2023HGCalMuonReco_cff')

#process.GlobalTag.globaltag = "80X_dataRun2_Prompt_v6"

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
#process.GlobalTag.globaltag = 'IDEAL_V9::All'
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
    input = cms.untracked.int32(10)
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
'/store/user/rgupta/Signal/CMSSW_620SLHC27_SingleMuPt100_Reco_8June/160608_035354/0000/step3_1.root'
)
)

process.dTandCSCSegmentsinTracks = cms.EDProducer("DTandCSCSegmentsinTracks",
                                                  #cscSegments = cms.untracked.InputTag("hltCscSegments"),
                                                  #dt4DSegments = cms.untracked.InputTag("hltDt4DSegments"),
                                                  cscSegments = cms.untracked.InputTag("cscSegments"),
                                                  dt4DSegments = cms.untracked.InputTag("dt4DSegments"),
#                                                  tracks = cms.untracked.InputTag("standAloneMuons","")
                                                  tracks = cms.untracked.InputTag("standAloneMuons","UpdatedAtVtx")
                                                  )



process.gemPointProducer = cms.EDProducer('GEMPointProducer',
#  incldt = cms.untracked.bool(True),
  inclcsc = cms.untracked.bool(True),
  incltrack =  cms.untracked.bool(False),
  debug = cms.untracked.bool(True),
  rangestrips = cms.untracked.double(4.),
  rangestripsRB4 = cms.untracked.double(4.),
  MinCosAng = cms.untracked.double(0.85),
  MaxD = cms.untracked.double(80.0),
  MaxDrb4 = cms.untracked.double(150.0),
  ExtrapolatedRegion = cms.untracked.double(0.6), # in stripl/2 in Y and stripw*nstrips/2 in X
  #cscSegments = cms.InputTag('dTandCSCSegmentsinTracks','SelectedCscSegments','OwnParticles'),
  #dt4DSegments = cms.InputTag('dTandCSCSegmentsinTracks','SelectedDtSegments','OwnParticles'),
  cscSegments = cms.InputTag('cscSegments', '', 'RECO'),
  dt4DSegments = cms.InputTag('dt4DSegments', '', 'RECO'),
  tracks = cms.InputTag("standAloneMuons"),
  TrackTransformer = cms.PSet(
      DoPredictionsOnly = cms.bool(False),
      Fitter = cms.string('KFFitterForRefitInsideOut'),
      TrackerRecHitBuilder = cms.string('WithTrackAngle'),
      Smoother = cms.string('KFSmootherForRefitInsideOut'),
      MuonRecHitBuilder = cms.string('MuonRecHitBuilder'),
      RefitDirection = cms.string('alongMomentum'),
#      RefitRPCHits = cms.bool(False),
      RefitGEMHits = cms.bool(False),
      Propagator = cms.string('SmartPropagatorAnyRKOpposite')
  )
)

process.museg = cms.EDAnalyzer("MuonSegmentEff",
    incldt = cms.untracked.bool(True),
    incldtMB4 = cms.untracked.bool(True),
    inclcsc = cms.untracked.bool(True),
    debug = cms.untracked.bool(False),
    inves = cms.untracked.bool(True),
    DuplicationCorrection = cms.untracked.int32(1),
    manualalignment = cms.untracked.bool(False),
    AliFileName = cms.untracked.string('../../../DQM/RPCMonitorModule/data/Alignment69912.dat'),
    rangestrips = cms.untracked.double(4.),
    #cscSegments = cms.untracked.InputTag('hltCscSegments'),	#use hltSegments with RPCMonitor
    #dt4DSegments = cms.untracked.InputTag('hltDt4DSegments'),
    #rpcRecHits = cms.untracked.InputTag("hltRpcRecHits"),
    rpcRecHits = cms.untracked.InputTag("rpcRecHits"),
    cscSegments = cms.untracked.InputTag('cscSegments'),
    dt4DSegments = cms.untracked.InputTag('dt4DSegments'),
    rpcDTPoints = cms.untracked.InputTag("rpcPointProducer","RPCDTExtrapolatedPoints"),
    rpcCSCPoints = cms.untracked.InputTag("rpcPointProducer","RPCCSCExtrapolatedPoints"),
    EffSaveRootFile = cms.untracked.bool(True),
    EffRootFileName = cms.untracked.string('Efficiency_MYTEST_Zmu2016B.root'),
    EffSaveRootFileEventsInterval = cms.untracked.int32(100)
)

process.normfilter = cms.EDFilter("HLTHighLevel",
    TriggerResultsTag = cms.InputTag("TriggerResults","","HLT"),
    HLTPaths = cms.vstring("AlCa_RPCMuonNormalisation*"),
    eventSetupPathsKey = cms.string(''),
    andOr = cms.bool(True),
    throw = cms.bool(True)
)

process.triggerFilter = cms.EDFilter('TriggerFilter',
                        gtDigis = cms.untracked.InputTag('hltGtDigis')
                        #gtDigis = cms.untracked.InputTag('hltGtStage2Digis')
                        #gtDigis = cms.untracked.InputTag('gtDigis')
)

# Use this for RPCMonitor stream (Raw Data format)
#process.p = cms.Path(process.normfilter*process.triggerFilter*process.muonstandalonereco*process.dTandCSCSegmentsinTracks*process.rpcPointProducer*process.museg)

#Use this for Express stream data (FEVT format)
#process.p = cms.Path(process.triggerFilter*process.muonstandalonereco*process.dTandCSCSegmentsinTracks*process.rpcPointProducer*process.museg)

#Use this with 2016 data - for the moment process.triggerFilter is disabled. The filter needs to be updated regarding to the new triger candidates content 

#import PhysicsTools.PythonAnalysis.LumiList as LumiList
#process.source.lumisToProcess = LumiList.LumiList(filename = '/afs/cern.ch/work/m/mileva/myGitLab/CMSSW_8_0_7/src/DQM/RPCMonitorModule/test/p86.txt').getVLuminosityBlockRange()

#process.p = cms.Path(process.muonstandalonereco*process.dTandCSCSegmentsinTracks*process.rpcPointProducer*process.museg)
#process.p = cms.Path(process.dTandCSCSegmentsinTracks*process.rpcPointProducer*process.museg)
#process.p = cms.Path(process.rpcPointProducer*process.museg)
process.p = cms.Path(process.gemPointProducer)

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


