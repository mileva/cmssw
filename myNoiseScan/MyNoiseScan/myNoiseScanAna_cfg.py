import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1) )

process.source = cms.Source("EmptySource"
                            )

process.demo = cms.EDAnalyzer('MyNoiseScan',
#                               myInputFile = cms.string('data/myInputFile.txt'),
                               myMapIdName = cms.string('data/mapNameId.txt'),
                               debug = cms.bool(False),
                               doNoiseMagnet = cms.bool(True),
                               doNoiseNoMagnet = cms.bool(True)
                              )

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('noiseScanAna.root')
)

process.p = cms.Path(process.demo)
