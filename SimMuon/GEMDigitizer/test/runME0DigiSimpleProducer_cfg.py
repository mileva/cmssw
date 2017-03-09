
import FWCore.ParameterSet.Config as cms

from Configuration.StandardSequences.Eras import eras

process = cms.Process('HLT',eras.Phase2C1)

process = cms.Process("ME0DIGI")

process.load('Configuration.StandardSequences.Services_cff')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('SimGeneral.MixingModule.mixNoPU_cfi')
process.load('Configuration.Geometry.GeometryExtended2023D9Reco_cff')
process.load('Configuration.Geometry.GeometryExtended2023D9_cff')
process.load('Configuration.StandardSequences.MagneticField_cff')
#process.load('Configuration.StandardSequences.SimIdeal_cff')
#process.load('Configuration.StandardSequences.Generator_cff')
process.load('Configuration.StandardSequences.Digi_cff')
#process.load('Configuration.StandardSequences.SimL1Emulator_cff')
#process.load('Configuration.StandardSequences.DigiToRaw_cff')
#process.load('HLTrigger.Configuration.HLT_Fake_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '90X_upgrade2023_realistic_v1', '')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(10)
)

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(
    'file:/afs/cern.ch/work/m/mileva/milena/CMSSW_9_0_0_pre4/src/step1.root'
    )
)
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

#process.contentAna = cms.EDAnalyzer("EventContentAnalyzer")

# GEM digitizer
process.load('SimMuon.GEMDigitizer.muonME0DigisPreReco_cfi')
process.load('SimMuon.GEMDigitizer.muonME0DigiTrivial_cfi')
process.RandomNumberGeneratorService.simMuonME0TrivDigis = cms.PSet(
    initialSeed = cms.untracked.uint32(123456798),
    engineName = cms.untracked.string('HepJamesRandom')
    )


# customization of the process.pdigi sequence to add the GEM digitizer
from SimMuon.GEMDigitizer.customizeGEMDigi import *
process = customize_digi_addGEM_addME0_muon_only(process) # only muon+GEM+ME0 digi

process.output = cms.OutputModule("PoolOutputModule",
    fileName = cms.untracked.string(
        'file:out_digi_me0.test.root'
    ),
    outputCommands = cms.untracked.vstring(
        'keep  *_*_*_*',
        #'drop CastorDataFramesSorted_simCastorDigis_*_GEMDIGI'
        # drop all CF stuff
        ##'drop *_mix_*_*',
        # drop tracker simhits
        ##'drop PSimHits_*_Tracker*_*',
        # drop calorimetry stuff
        ##'drop PCaloHits_*_*_*',
        # clean up simhits from other detectors
        ##'drop PSimHits_*_Totem*_*',
        ##'drop PSimHits_*_FP420*_*',
        ##'drop PSimHits_*_BSC*_*',
        # drop some not useful muon digis and links
        ##'drop *_*_MuonCSCStripDigi_*',
        ##'drop *_*_MuonCSCStripDigiSimLinks_*',
        #'drop *SimLink*_*_*_*',
        ##'drop *RandomEngineStates_*_*_*',
        ##'drop *_randomEngineStateProducer_*_*'
    ),
    SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring('digi_step')
    )
)


#process.contentAna = cms.EDAnalyzer("EventContentAnalyzer")
process.digi_step    = cms.Path(process.pdigi)
process.endjob_step  = cms.Path(process.endOfProcess)
process.out_step     = cms.EndPath(process.output)

process.schedule = cms.Schedule(
    process.digi_step,
    process.endjob_step,
    process.out_step
)
