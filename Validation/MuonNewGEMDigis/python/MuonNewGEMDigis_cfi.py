import FWCore.ParameterSet.Config as cms
from Validation.MuonNewGEMDigis.simTrackMatching_cfi import SimTrackMatching

newGEMDigiValidation = cms.EDAnalyzer("MuonNewGEMDigis",
                                   debug = cms.untracked.bool(False),
                                   folderPath = cms.untracked.string('MuonGEMDigisV/GEMDigiTask'),
                                   EffSaveRootFile = cms.untracked.bool(False),
                                   EffRootFileName = cms.untracked.string('GEMDigis_New.root'),
                                   simTrackMatching = SimTrackMatching
                                   )
