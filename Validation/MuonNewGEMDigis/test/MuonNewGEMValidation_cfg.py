import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.load('Configuration.EventContent.EventContent_cff')
process.load('Configuration.Geometry.GeometryExtended2023MuonReco_cff')
process.load('Configuration.Geometry.GeometryExtended2023Muon_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_PostLS1_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.load("DQMServices.Components.MEtoEDMConverter_cfi")
process.load("DQMServices.Core.DQM_cfg")

## global tag for 2019 upgrade studies
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:upgradePLS3', '')

#process.load("Validation.MuonME0Hits.MuonME0Hits_cfi")
#process.me0HitsValidation.EffSaveRootFile = True
process.load("Validation.MuonNewGEMDigis.MuonNewGEMDigis_cfi")
process.newGEMDigiValidation.EffSaveRootFile = True
#process.load("Validation.MuonME0RecHits.MuonME0RecHits_cfi")
#process.me0RecHitsValidation.EffSaveRootFile = True

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(  

#  'file:/tmp/archie/out_digi_GEMPesudoDigis.root'
  'file:/tmp/archie/out_digi.root'
#'file:/lustre/cms/store/user/piet/ME0Segment_Time/SampleProd4/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola_HGCALGS_GEN-SIM_v2/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola_HGCALGS_PU140_1ns_500um_1cm_SP4_v1_DIGI/151210_173525/0000/JME-TP2023SHCALDR-00001_step1_1.root',
 

)
)
process.p = cms.Path(#process.me0HitsValidation *
		     process.newGEMDigiValidation
		     #process.me0RecHitsValidation
			)
