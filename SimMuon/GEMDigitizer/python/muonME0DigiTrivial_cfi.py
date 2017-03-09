import FWCore.ParameterSet.Config as cms

#me0DigiCommonParameters = cms.PSet(
#    inputCollection = cms.string('g4SimHitsMuonME0Hits'),
#    me0digiModelString = cms.string('Trivial'),
#    timeResolution = cms.double(0.0), # in ns
#    phiResolution = cms.double(0.0), # in cm average resolution along local x in case of no correlation
#    etaResolution = cms.double(0.0), # in cm average resolution along local y in case of no correlation
#    phiError = cms.double(0.001), # normally error should be the resolution, but for the case resolution = 0
#    etaError = cms.double(0.001), # normally error should be the resolution, but for the case resolution = 0
#    constantPhiSpatialResolution = cms.bool(True),
#    useCorrelation = cms.bool(False),
#    useEtaProjectiveGEO = cms.bool(False),
#    averageEfficiency = cms.double(0.98),
#    gaussianSmearing = cms.bool(True),          # False --> Uniform smearing
#    digitizeOnlyMuons = cms.bool(False),
    # simulateIntrinsicNoise = cms.bool(False), # intrinsic noise --> not implemented
    # averageNoiseRate = cms.double(0.001),     # intrinsic noise --> not implemented
#    simulateElectronBkg = cms.bool(True),       # True - will simulate electron background
#    simulateNeutralBkg  = cms.bool(True),       # True - will simulate neutral (n+g)  background
#    minBunch = cms.int32(-5),                   # [x 25 ns], forms the readout window together with maxBunch,
#    maxBunch = cms.int32(3),                    # we should think of shrinking this window ...
#    instLumi = cms.double(7.5),                 # in units of 1E34 cm^-2 s^-1. Internally the background is parametrized from FLUKA+GEANT results at 5x10^34 (PU140). We are adding a 1.5 factor for PU200
#    rateFact = cms.double(2.0),                 # We are adding also a safety factor of 2 to take into account the new beam pipe effect (not yet known). Hits can be thrown away later at re-digi step.
#    mixLabel = cms.string('mix'),
#)

# Module to create simulated ME0 digis.
#simMuonME0TrivDigis = cms.EDProducer("ME0DigiProducer",
#    me0DigiCommonParameters

simMuonME0TrivDigis = cms.EDProducer("ME0DigiProducer",
    signalPropagationSpeed = cms.double(0.66),
    cosmics = cms.bool(False),
    timeResolution = cms.double(5),
    timeJitter = cms.double(1.0),
    averageShapingTime = cms.double(50.0),
# clsParametrization = cms.vdouble(0.455091, 0.865613, 0.945891, 0.973286, 0.986234, 0.991686, 0.996865, 0.998501, 1.),
    averageEfficiency = cms.double(0.98),
    averageNoiseRate = cms.double(0.001), #intrinsic noise
    bxwidth = cms.int32(25),
    minBunch = cms.int32(-5), ## in terms of 25 ns
    maxBunch = cms.int32(3),
    mixLabel = cms.string('mix'),	# added by A.Sharma
    inputCollection = cms.string('g4SimHitsMuonME0Hits'),
    me0digiModelString = cms.string('Simple'),
    digitizeOnlyMuons = cms.bool(False),
    doBkgNoise = cms.bool(True), #False == No background simulation
    doNoiseCLS = cms.bool(True),
    fixedRollRadius = cms.bool(True), #Uses fixed radius in the center of the roll
    simulateIntrinsicNoise = cms.bool(False),
    simulateElectronBkg = cms.bool(True),	#False=simulate only neutral Bkg
    simulateLowNeutralRate = cms.bool(False)	#True=neutral_Bkg at L=1x10^{34}, False at L=5x10^{34}cm^{-2}s^{-1}

)


