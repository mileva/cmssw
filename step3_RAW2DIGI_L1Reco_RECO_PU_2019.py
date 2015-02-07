# Auto generated configuration file
# using: 
# Revision: 1.20 
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v 
# with command line options: step3 --conditions DES19_62_V8::All -n 100 --eventcontent FEVTDEBUGHLT -s RAW2DIGI,L1Reco,RECO --datatier GEN-SIM-DIGI-RECO --customise SLHCUpgradeSimulations/Configuration/combinedCustoms.cust_2019WithGem --geometry Extended2019 --magField 38T_PostLS1 --filein file:step2.root --fileout file:step3.root --pileup AVE_50_BX_25ns --pileup_input dbs:/MinBias_TuneZ2star_14TeV-pythia6/GEM2019Upg14-DES19_62_V8-v1/GEN-SIM --no_exec
import FWCore.ParameterSet.Config as cms

process = cms.Process('RECO')

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('SimGeneral.MixingModule.mix_POISSON_average_cfi')
process.load('Configuration.Geometry.GeometryExtended2019Reco_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_PostLS1_cff')
process.load('Configuration.StandardSequences.RawToDigi_cff')
process.load('Configuration.StandardSequences.L1Reco_cff')
process.load('Configuration.StandardSequences.Reconstruction_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

#process.MessageLogger.cout.placeholder = cms.untracked.bool(False)

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(100)
)

# Input source
process.source = cms.Source("PoolSource",
    secondaryFileNames = cms.untracked.vstring(),
    fileNames = cms.untracked.vstring(

'file:DY2019Digi_pu50.root'
#'/store/group/upgrade/muon/RecoFolder/MuMinusPt100_2019_2Step/Muminus_Pt100-gun/calabria_MuMinusPt100_GEN-SIM-DIGI-RAW_CMSSW_6_2_0_SLHC12_2019Scenario_2Step/1b69b0f16be16775753770be7f95b243/step2_100_2_3nh.root'
)


)

#--------------------------------------------------------------------------

process.load('RecoLocalMuon.RPCRecHit.rpcRecHits_cfi')
process.load('RecoLocalMuon.GEMRecHit.gemRecHits_cfi')
process.gemRecHits.recAlgoConfig.stationToUse = cms.untracked.int32(0)
#process.rpcRecHits.recAlgoConfig.stationToUse = cms.untracked.int32(0)

#--------------------------------------------------------------------------

# Production Info
process.configurationMetadata = cms.untracked.PSet(
    version = cms.untracked.string('$Revision: 1.20 $'),
    annotation = cms.untracked.string('step3 nevts:100'),
    name = cms.untracked.string('Applications')
)

# Output definition

process.FEVTDEBUGHLToutput = cms.OutputModule("PoolOutputModule",
    splitLevel = cms.untracked.int32(0),
    eventAutoFlushCompressedSize = cms.untracked.int32(5242880),
    outputCommands = process.FEVTDEBUGHLTEventContent.outputCommands,
    fileName = cms.untracked.string('file:DY2019PU50reco_simlink.root'),
    dataset = cms.untracked.PSet(
        filterName = cms.untracked.string(''),
        dataTier = cms.untracked.string('GEN-SIM-DIGI-RECO')
    )
)

# Additional output definition

# Other statements
process.mix.input.nbPileupEvents.averageNumber = cms.double(50.000000)
process.mix.bunchspace = cms.int32(25)
process.mix.minBunch = cms.int32(-12)
process.mix.maxBunch = cms.int32(3)
process.mix.input.fileNames = cms.untracked.vstring(['/store/mc/GEM2019Upg14/MinBias_TuneZ2star_14TeV-pythia6/GEN-SIM/DES19_62_V8-v1/00000/0005E995-28CD-E311-AEB9-002590743042.root', '/store/mc/GEM2019Upg14/MinBias_TuneZ2star_14TeV-pythia6/GEN-SIM/DES19_62_V8-v1/00000/0021E269-DDCF-E311-9F81-0022191F5E84.root', '/store/mc/GEM2019Upg14/MinBias_TuneZ2star_14TeV-pythia6/GEN-SIM/DES19_62_V8-v1/00000/0029137D-E9CC-E311-ADDE-001EC9AA9F6D.root', '/store/mc/GEM2019Upg14/MinBias_TuneZ2star_14TeV-pythia6/GEN-SIM/DES19_62_V8-v1/00000/002F2726-12CD-E311-8AEA-00259075D706.root', '/store/mc/GEM2019Upg14/MinBias_TuneZ2star_14TeV-pythia6/GEN-SIM/DES19_62_V8-v1/00000/00395040-D4CC-E311-9E12-BCAEC5097210.root', '/store/mc/GEM2019Upg14/MinBias_TuneZ2star_14TeV-pythia6/GEN-SIM/DES19_62_V8-v1/00000/0045680E-F1CC-E311-9D7A-001D091C6771.root', '/store/mc/GEM2019Upg14/MinBias_TuneZ2star_14TeV-pythia6/GEN-SIM/DES19_62_V8-v1/00000/00536E28-FACC-E311-98DE-AC853D9F5120.root', '/store/mc/GEM2019Upg14/MinBias_TuneZ2star_14TeV-pythia6/GEN-SIM/DES19_62_V8-v1/00000/0058FCC7-D6CC-E311-8ABD-002590E2DA08.root', '/store/mc/GEM2019Upg14/MinBias_TuneZ2star_14TeV-pythia6/GEN-SIM/DES19_62_V8-v1/00000/00977CB0-F0CE-E311-AC2A-002590747D9C.root', '/store/mc/GEM2019Upg14/MinBias_TuneZ2star_14TeV-pythia6/GEN-SIM/DES19_62_V8-v1/00000/00A61631-0ACD-E311-B77F-00259048AE4E.root'])
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'DES19_62_V8::All', '')

# Path and EndPath definitions
process.raw2digi_step = cms.Path(process.RawToDigi)
process.L1Reco_step = cms.Path(process.L1Reco)
process.reconstruction_step = cms.Path(process.reconstruction)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.FEVTDEBUGHLToutput_step = cms.EndPath(process.FEVTDEBUGHLToutput)

# Schedule definition
process.schedule = cms.Schedule(process.raw2digi_step,process.L1Reco_step,process.reconstruction_step,process.endjob_step,process.FEVTDEBUGHLToutput_step)

# customisation of the process.

# Automatic addition of the customisation function from SLHCUpgradeSimulations.Configuration.combinedCustoms
from SLHCUpgradeSimulations.Configuration.combinedCustoms import cust_2019WithGem 

#call to customisation function cust_2019WithGem imported from SLHCUpgradeSimulations.Configuration.combinedCustoms
process = cust_2019WithGem(process)

# End of customisation functions
