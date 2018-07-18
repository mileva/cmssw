import FWCore.ParameterSet.Config as cms

demo = cms.EDAnalyzer('RPCDigiAna'
     ,tracks = cms.untracked.InputTag('ctfWithMaterialTracks')
)
