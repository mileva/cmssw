import FWCore.ParameterSet.Config as cms

# Module to create simulated GEM digis.
simMuonGEMDigis = cms.EDProducer("GEMDigiProducer",
    signalPropagationSpeed = cms.double(0.66),
    cosmics = cms.bool(False),
    timeResolution = cms.double(5),
    timeJitter = cms.double(1.0),
    averageShapingTime = cms.double(50.0),
    averageClusterSize = cms.double(1.5),#1.5
#cumulative cls distribution at 771 mkA
#    clsParametrization = cms.vdouble(0.455091, 0.865613, 0.945891, 0.973286, 0.986234, 0.991686, 0.996865, 0.998501, 1.),
#cumulative cls distribution at 752 mkA
    clsParametrization = cms.vdouble(0.663634, 0.928571, 0.967544, 0.982665, 0.990288, 0.994222, 0.997541, 0.999016, 1.),
    averageEfficiency = cms.double(0.98),
    averageNoiseRate = cms.double(0.001), #intrinsic noise
    bxwidth = cms.int32(25),
    minBunch = cms.int32(-5), ## in terms of 25 ns
    maxBunch = cms.int32(3),
    inputCollection = cms.string('g4SimHitsMuonGEMHits'),
    digiModelString = cms.string('Simple'),
    digitizeOnlyMuons = cms.bool(True),
    doBkgNoise = cms.bool(True),
    doNoiseCLS = cms.bool(True),
    fixedRollRadius = cms.bool(False),
    minPabsNoiseCLS = cms.double(0.),
    simulateIntrinsicNoise = cms.bool(False),
    scaleLumi = cms.double(1.),
    constGE11 = cms.double(1195.),
    slopeGE11 = cms.double(-0.01658),
    constGE21Short = cms.double(316.2),
    slopeGE21Short = cms.double(-0.008704),
    constGE21Long = cms.double(316.2),
    slopeGE21Long = cms.double(-0.008704)

)


