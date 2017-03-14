import FWCore.ParameterSet.Config as cms

#me0RecHits = cms.EDProducer("ME0TrivRecHitProducer",
me0TrivRecHits = cms.EDProducer("ME0TrivRecHitProducer",
    recAlgoConfig = cms.PSet(),
    recAlgo = cms.string('ME0TrivRecHitStandardAlgo'),
    me0TrivDigiLabel = cms.InputTag("simMuonME0TrivDigis"),
)
