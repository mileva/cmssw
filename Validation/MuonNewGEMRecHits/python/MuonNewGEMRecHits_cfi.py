import FWCore.ParameterSet.Config as cms
from Validation.MuonNewGEMDigis.simTrackMatching_cfi import SimTrackMatching

gemRecHitsValidation = cms.EDAnalyzer("MuonNewGEMRecHits",
                                   debug = cms.untracked.bool(False),
                                   folderPath = cms.untracked.string('MuonNewGEMRecHitsV/GEMRecHitTask'),
                                   EffSaveRootFile = cms.untracked.bool(False),
                                   EffRootFileName = cms.untracked.string('GEMRecHits_NEW.root'),
                                   simTrackMatching = SimTrackMatching
)                
