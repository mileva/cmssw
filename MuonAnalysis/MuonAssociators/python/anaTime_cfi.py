import FWCore.ParameterSet.Config as cms

demo = cms.EDAnalyzer('AnaTime',
	muonLabel = cms.InputTag("muons"),
	muonPtCut = cms.double(0.),
	muonMinEtaCut = cms.double(1.5),
	muonMaxEtaCut = cms.double(2.1)
)
