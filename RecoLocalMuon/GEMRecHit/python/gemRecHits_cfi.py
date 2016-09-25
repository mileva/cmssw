import FWCore.ParameterSet.Config as cms

gemRecHits = cms.EDProducer("GEMRecHitProducerPreReco",
    recAlgoConfig = cms.PSet(
                    recOnlyMuons = cms.bool(True),
    ),
    prerecAlgo = cms.string('GEMRecHitStandardAlgoPreReco'),
    gemPreDigiLabel = cms.InputTag("simMuonGEMDigiswithTiming"),
    recAlgo = cms.string('GEMRecHitStandardAlgo'),
    gemDigiLabel = cms.InputTag("simMuonGEMDigis"),
    maskSource = cms.string('File'),
    maskvecfile = cms.FileInPath('RecoLocalMuon/GEMRecHit/data/GEMMaskVec.dat'),
    deadSource = cms.string('File'),
    deadvecfile = cms.FileInPath('RecoLocalMuon/GEMRecHit/data/GEMDeadVec.dat')
)


