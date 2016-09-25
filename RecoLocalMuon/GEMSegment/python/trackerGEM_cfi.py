import FWCore.ParameterSet.Config as cms


trackerGEM = cms.EDProducer("trackerGEM",
    ## maxPullXGE11 = cms.double (2.0),
    ## maxDiffXGE11 = cms.double (1.5),
    ## maxPullYGE11 = cms.double (2.0),
    ## maxDiffYGE11 = cms.double (10.0),
    ## maxPullXGE21 = cms.double (2.0),
    ## maxDiffXGE21 = cms.double (2.5),
    ## maxPullYGE21 = cms.double (2.0),
    ## maxDiffYGE21 = cms.double (12.0),
    ## maxDiffPhiDirection = cms.double (0.3),
    maxPullXGE11 = cms.double (50.0),
    maxDiffXGE11 = cms.double (50.5),
    maxPullYGE11 = cms.double (50.0),
    maxDiffYGE11 = cms.double (50.0),
    maxPullXGE21 = cms.double (50.0),
    maxDiffXGE21 = cms.double (50.5),
    maxPullYGE21 = cms.double (50.0),
    maxDiffYGE21 = cms.double (52.0),
    maxDiffPhiDirection = cms.double (50),
    gemSegmentsToken = cms.InputTag("gemSegments"),
    generalTracksToken = cms.InputTag("generalTracks")
)
