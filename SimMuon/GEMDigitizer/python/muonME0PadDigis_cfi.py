import FWCore.ParameterSet.Config as cms

# Module to create simulated ME0-CSC trigger pad digis.
simMuonME0PadDigis = cms.EDProducer("ME0PadDigiProducer",
    InputCollection = cms.InputTag('simMuonME0ReDigis'),
)
