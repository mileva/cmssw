import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.load('Configuration.StandardSequences.GeometryDB_cff')

### conditions
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = '100X_dataRun2_Express_v1'


process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1) )

process.source = cms.Source("EmptySource"
                            )

process.demo = cms.EDAnalyzer('MyNoiseScan',
                               myInputFileMagn = cms.string('data/noisemagnet/allNoise_noRE11.txt'),
                               myInputFileNoMagn = cms.string('data/noisenomagnet/allNoiseNomagnet_noRE11.txt'),
                               myMapIdName = cms.string('data/mapNameId.txt'),
                               debug = cms.bool(False),
                               doNoiseMagnet = cms.bool(True),
                               doNoiseNoMagnet = cms.bool(True),
                               hvpointpar = cms.double(9800)	#HV point value for filing the 2D rate plots
                              )

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('noiseScanAna9800_magnet.root')
)

process.p = cms.Path(process.demo)
