# Auto generated configuration file
# using: 
# Revision: 1.19 
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v 
# with command line options: SingleMuPt10_pythia8_cfi.py -s GEN,SIM,DIGI --pileup=NoPileUp --geometry DB --conditions=auto:run1_mc --eventcontent FEVTDEBUGHLT --no_exec -n 30
import FWCore.ParameterSet.Config as cms
import datetime
import random

process = cms.Process('CPPFEM')

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('SimGeneral.MixingModule.mixNoPU_cfi')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
#process.load('Configuration.Geometry.GeometryDB_cff')
#process.load('Configuration.StandardSequences.GeometryExtended_cff')
#process.load('Configuration.Geometry.GeometryExtended2016_cff')
#process.load('Configuration.Geometry.GeometryExtended2016Reco_cff')
process.load('Configuration.StandardSequences.MagneticField_cff')
#process.load('Configuration.StandardSequences.Generator_cff')
#process.load('IOMC.EventVertexGenerators.VtxSmearedRealistic50ns13TeVCollision_cfi')
#process.load('GeneratorInterface.Core.genFilterSummary_cff')
#process.load('Configuration.StandardSequences.SimIdeal_cff')
##process.load('Configuration.StandardSequences.Digi_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run2_mc', '')
process.load('Configuration.StandardSequences.EndOfProcess_cff')

##rumi
process.load("EventFilter.RPCRawToDigi.RPCCPPFRawToDigi_cff")	#
process.load("EventFilter.RPCRawToDigi.rpcPacker_cfi")			#
process.rpcpacker.InputLabel = cms.InputTag("rpcCPPFRawToDigi")		#
process.load("EventFilter.RPCRawToDigi.rpcUnpackingModule_cfi")		#
process.rpcUnpackingModulePacked = process.rpcUnpackingModule.clone()	#
process.rpcUnpackingModulePacked.InputLabel = cms.InputTag("rpcpacker")	#
###

#process.load('RecoLocalMuon.RPCRecHit.rpcRecHits_cfi')
#from RecoLocalMuon.RPCRecHit.rpcRecHits_cfi import *

process.load('L1Trigger.L1TMuonCPPF.emulatorCppfDigis_cfi')
from L1Trigger.L1TMuonCPPF.emulatorCppfDigis_cfi import *

process.load('EventFilter.L1TRawToDigi.emtfStage2Digis_cfi')
process.load('L1Trigger.L1TMuonEndCap.simEmtfDigis_cfi')
#process.simEmtfDigisData.RPCInput  = cms.InputTag('rpcunpacker')
process.simEmtfDigisMC.RPCInput  = cms.InputTag('simMuonRPCDigis')

process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(1)
process.MessageLogger = cms.Service("MessageLogger")
process.maxEvents = cms.untracked.PSet(
	input = cms.untracked.int32(-1)
	)

# Input source
process.source = cms.Source("PoolSource",
#    fileNames = cms.untracked.vstring('file:/eos/cms/store/user/mileva/rpcUpgrade/cppfEmu/step2_DIGI_L1_DIGI2RAW_HLT_fevtcont.root'),
    fileNames = cms.untracked.vstring('file:/afs/cern.ch/work/m/mileva/testEmulator2/CMSSW_11_0_0_pre7/src/step2a_DIGI.root'),
			    )
process.options = cms.untracked.PSet(
	)

process.FEVTDEBUGHLToutput = cms.OutputModule("PoolOutputModule",
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('GEN-SIM-DIGI-RAW-HLTDEBUG'),
        filterName = cms.untracked.string('')
    ),
    fileName = cms.untracked.string('file:step2a_cppf_myDraftTestOnDigi.root'),
#    outputCommands = process.FEVTDEBUGHLTEventContent.outputCommands,
    outputCommands = cms.untracked.vstring("keep *",),
#    outputCommands = cms.untracked.vstring('drop *',"keep *_emulatorMuonRPCDigis_*_*", "keep *_emulatorCppfDigis_*_*", "keep *_rpcRecHits_*_*", "keep *_genParticles_*_*"),
    splitLevel = cms.untracked.int32(0)
)


# Additional output definition

# Other statements
#process.rpcRecHits.rpcDigiLabel = 'simMuonRPCDigis'
process.emulatorCppfDigis.rpcDigiLabel = 'simMuonRPCDigis'
process.emulatorCppfDigis.rpcDigiSimLinkLabel = cms.InputTag("simMuonRPCDigis", "RPCDigiSimLink")
process.emulatorCppfDigis.recHitLabel = 'rpcRecHits'

#process.Tracer = cms.Service("Tracer")

# Path and EndPath definitions
#process.rpcrechits_step = cms.Path(process.rpcRecHits)
process.emulatorCppfDigis_step = cms.Path(process.emulatorCppfDigis)
process.emtfStage2Digis_step = cms.Path(process.emtfStage2Digis)
process.simEmtfDigisData_step = cms.Path(process.simEmtfDigisData)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.FEVTDEBUGHLToutput_step = cms.EndPath(process.FEVTDEBUGHLToutput)

# Schedule definition
#process.schedule = cms.Schedule(process.rpcrechits_step,process.emulatorCppfDigis_step,process.endjob_step,process.FEVTDEBUGHLToutput_step)
#process.schedule = cms.Schedule(process.emulatorCppfDigis_step,process.endjob_step,process.FEVTDEBUGHLToutput_step)
process.schedule = cms.Schedule(process.emulatorCppfDigis_step,process.emtfStage2Digis_step,process.simEmtfDigisData_step,process.endjob_step,process.FEVTDEBUGHLToutput_step)

