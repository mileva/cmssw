import FWCore.ParameterSet.Config as cms

SimTrackMatching = cms.PSet(
    # common
    useCSCChamberTypes = cms.untracked.vint32(0,1,2),
    ntupleTrackChamberDelta = cms.bool(True),
    ntupleTrackEff = cms.bool(True),
    overrideminNHitsChamber = cms.bool(False),
    minNHitsChamber = cms.untracked.int32(4),
    verbose = cms.bool(False),
    ## per collection params
    simTrack = cms.PSet(
        verbose = cms.int32(0),
        input = cms.InputTag('g4SimHits'),
        minPt = cms.double(1.5),
        maxPt = cms.double(999.),
        minEta = cms.double(1.45),
        maxEta = cms.double(4.0),
        onlyMuon = cms.bool(True),
        requireVertex = cms.bool(True),
        requireGenPart = cms.bool(True),
    ),

    gemSimHit = cms.PSet(
        verbose = cms.int32(0),
        input = cms.InputTag('g4SimHits','MuonGEMHits'),
        simMuOnly = cms.bool(True),
        discardEleHits = cms.bool(True),
    ),
    gemStripDigi = cms.PSet(
        verbose = cms.int32(0),
        input = cms.InputTag("simMuonGEMDigiswithTiming"),
        minBX = cms.int32(-1),
        maxBX = cms.int32(1),
        matchDeltaStrip = cms.int32(1),
    ),
    gemRecHit = cms.PSet(
        verbose = cms.int32(0),
        input = cms.InputTag('gemRecHitsPreReco'),
        simMuOnly = cms.bool(True),
        discardEleHits = cms.bool(True),
    ),
    gemSeg = cms.PSet(
        verbose = cms.int32(0),
        input = cms.InputTag('gemPreSegments'),
        simMuOnly = cms.bool(True),
        discardEleHits = cms.bool(True),
    ),

)
