import FWCore.ParameterSet.Config as cms

# Module to create simulated GEM digis.
simMuonGEMDigis = cms.EDProducer("GEMDigiProducer",
    signalPropagationSpeed = cms.double(0.66),
    cosmics = cms.bool(False),
    timeResolution = cms.double(5),
    timeJitter = cms.double(1.0),
    averageShapingTime = cms.double(50.0),
    averageClusterSize = cms.double(1.3),#1.5
    averageEfficiency = cms.double(0.98),
    averageNoiseRate = cms.double(0.001), #intrinsic noise
    bxwidth = cms.int32(25),
    minBunch = cms.int32(-5), ## in terms of 25 ns
    maxBunch = cms.int32(3),
    inputCollection = cms.string('g4SimHitsMuonGEMHits'),
    digiModelString = cms.string('Simple'),
    digitizeOnlyMuons = cms.bool(False),
    doNOTNoise = cms.bool(False),
    doNoiseCLS = cms.bool(True),
    randomNoise = cms.bool(True),
    minPabsNoiseCLS = cms.double(0.),
    simulateIntrinsicNoise = cms.bool(False),
    scaleLumi = cms.double(1.),
    constGE11 = cms.double(1195.),
    slopeGE11 = cms.double(-0.01658),
    constGE21 = cms.double(316.2),
    slopeGE21 = cms.double(-0.008704),
    constGE22 = cms.double(316.2),
    slopeGE22 = cms.double(-0.008704)

)

