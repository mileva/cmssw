import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo1")


process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(1)
process.MessageLogger.cerr.threshold = cms.untracked.string('DEBUG')
process.MessageLogger.debugModules = cms.untracked.vstring()
process.options = cms.untracked.PSet( wantSummary=cms.untracked.bool(False))

#process.load('Configuration.StandardSequences.Services_cff')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')

# Other statements
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run2_mc', '')

#process.load('RecoLocalMuon.RPCRecHit.rpcRecHits_cfi')
#from RecoLocalMuon.RPCRecHit.rpcRecHits_cfi import *

process.load('L1Trigger.L1TMuonCPPF.emulatorCppfDigis_cfi')
from L1Trigger.L1TMuonCPPF.emulatorCppfDigis_cfi import *

#process.load('EventFilter.L1TRawToDigi.emtfStage2Digis_cfi')

process.load('L1Trigger.L1TMuonEndCap.simEmtfDigis_cfi')
from L1Trigger.L1TMuonEndCap.simEmtfDigis_cfi import simEmtfDigisMC

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1))

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring('file:step2a_cppf_myDraftTest.root')#step2_DIGI_L1_DIGI2RAW_HLT_fevtcont.root')
)

#process.simEmtfDigisMC = 
#process.l1tStage2cppf = cms.EDProducer('L1TStage2CPPF',
#    disableROOToutput = cms.untracked.bool(False),
#    #rpcdigiSource = cms.InputTag("rpcCPPFRawToDigi"),
#    rpcdigiSource = cms.InputTag("simMuonRPCDigis"),
#    cppfdigiSource = cms.InputTag("emulatorCppfDigis"),
#    verbose = cms.untracked.bool(False),
#    DQMStore = cms.untracked.bool(True)
#)

#process.TFileService = cms.Service("TFileService",
#    fileName = cms.string('myoutput.root')
#)

process.FEVTDEBUGHLToutput = cms.OutputModule("PoolOutputModule",
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('GEN-SIM-DIGI-RAW-HLTDEBUG'),
        filterName = cms.untracked.string('')
    ),
    fileName = cms.untracked.string('file:testL1TrackProd.root'),
#    outputCommands = process.FEVTDEBUGHLTEventContent.outputCommands,
    outputCommands = cms.untracked.vstring("keep *",),
#    outputCommands = cms.untracked.vstring('drop *',"keep *_emulatorMuonRPCDigis_*_*", "keep *_emulatorCppfDigis_*_*", "keep *_rpcRecHits_*_*", "keep *_genParticles_*_*"),
    splitLevel = cms.untracked.int32(0)
)

#process.rpcRecHits.rpcDigiLabel = 'simMuonRPCDigis'
#process.emulatorCppfDigis.recHitLabel = 'rpcRecHits'

#process.emulatorCppfDigis.rpcDigiLabel = 'simMuonRPCDigis'
#process.simEmtfDigisMC.CPPFInput = 'emulatorCppfDigis'

#process.rpcrechits_step = cms.Path(process.rpcRecHits)
process.emulatorCppfDigis_step = cms.Path(process.emulatorCppfDigis)
process.simEmtfDigisMC_step = cms.Path(process.simEmtfDigisMC)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.FEVTDEBUGHLToutput_step = cms.EndPath(process.FEVTDEBUGHLToutput)

#process.Tracer = cms.Service("Tracer")
# Schedule definition
#process.schedule = cms.Schedule(process.rpcrechits_step,process.emulatorCppfDigis_step,process.simEmtfDigisMC_step,process.endjob_step,process.FEVTDEBUGHLToutput_step)
process.schedule = cms.Schedule(process.simEmtfDigisMC_step,process.emulatorCppfDigis_step,process.endjob_step,process.FEVTDEBUGHLToutput_step)
#process.p = cms.Path(process.rpcrechits_step,process.emulatorCppfDigis_step,process.simEmtfDigisMC_step)
