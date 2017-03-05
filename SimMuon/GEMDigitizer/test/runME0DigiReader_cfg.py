import FWCore.ParameterSet.Config as cms

process = cms.Process("Dump")

process.load('Configuration.StandardSequences.Services_cff')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('SimGeneral.MixingModule.mixNoPU_cfi')
process.load('Configuration.Geometry.GeometryExtended2023D9Reco_cff')
process.load('Configuration.Geometry.GeometryExtended2023D9_cff')
process.load('Configuration.StandardSequences.MagneticField_cff')
process.load('Configuration.StandardSequences.SimIdeal_cff')
process.load('Configuration.StandardSequences.Generator_cff')
process.load('Configuration.StandardSequences.Digi_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '90X_upgrade2023_realistic_v1', '')

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(	
    'file:/afs/cern.ch/work/m/mileva/milena/CMSSW_9_0_0_pre4/src/step2.root'
    )
)

process.dumper = cms.EDAnalyzer("ME0DigiReader",
    simhitToken = cms.InputTag("g4SimHits","MuonME0Hits"), 
    me0DigiToken = cms.InputTag("simMuonME0TrivDigis"), 
    me0StripDigiSimLinkToken = cms.InputTag("simMuonME0TrivDigis","ME0") 
)

process.p    = cms.Path(process.dumper)

