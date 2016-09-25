import FWCore.ParameterSet.Config as cms
#process = cms.Process("RecoSTAMuon")
process = cms.Process("STARECO")
process.load("RecoMuon.Configuration.RecoMuon_cff")
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('SimGeneral.MixingModule.mixNoPU_cfi')
#process.load('Configuration.Geometry.GeometryExtended2019Reco_cff')
#process.load('Configuration.StandardSequences.MagneticField_38T_cff')
#process.load('Configuration.Geometry.GeometryExtended2023Reco_cff')
#process.load('Configuration.Geometry.GeometryExtended2023_cff')
#process.load('Configuration.Geometry.GeometryExtended2015MuonGEMDevReco_cff')
#process.load('Configuration.Geometry.GeometryExtended2015MuonGEMDev_cff')
process.load('Configuration.Geometry.GeometryExtended2023MuonReco_cff')
process.load('Configuration.Geometry.GeometryExtended2023Muon_cff')
process.load('Configuration.Geometry.GeometryExtended2023HGCalMuonReco_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_PostLS1_cff')
process.load('Configuration.StandardSequences.RawToDigi_cff')
process.load('Configuration.StandardSequences.L1Reco_cff')
process.load('Configuration.StandardSequences.Reconstruction_cff') #!!!!!!!!!!!!!!!!!!!!!!!!!!
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

from Configuration.AlCa.GlobalTag import GlobalTag
#process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:upgradePLS3', '')
process.GlobalTag = GlobalTag(process.GlobalTag, 'PH2_1K_FB_V6::All', '')

# Fix DT and CSC Alignment #
############################
#from SLHCUpgradeSimulations.Configuration.fixMissingUpgradeGTPayloads import fixDTAlignmentConditions
#process = fixDTAlignmentConditions(process)
#from SLHCUpgradeSimulations.Configuration.fixMissingUpgradeGTPayloads import fixCSCAlignmentConditions
#process = fixCSCAlignmentConditions(process)

process.maxEvents = cms.untracked.PSet(
input = cms.untracked.int32(-1)
)

 # Seed generator
from RecoMuon.MuonSeedGenerator.standAloneMuonSeeds_cff import *

# Stand alone muon track producer
from RecoMuon.StandAloneMuonProducer.standAloneMuons_cff import *

# Beam Spot 
from RecoVertex.BeamSpotProducer.BeamSpot_cff import *

############ ME21 off ########################
#process.load('RecoLocalMuon.CSCRecHitD.cscRecHitD_cfi')
#process.csc2DRecHits.stationToUse = cms.untracked.int32(2)

############ all csc in ########################
process.load('RecoLocalMuon.CSCRecHitD.cscRecHitD_cfi')
process.csc2DRecHits.stationToUse = cms.untracked.int32(0)


process.source = cms.Source("PoolSource",
fileNames = cms.untracked.vstring(
#            'file:/afs/cern.ch/user/r/rgupta/public/step3.root'
#             'file:/afs/cern.ch/work/a/archie/private/Dir_GEMSegment/CMSSW_6_2_0_SLHC27/src/RecoLocalMuon/GEMRecHit/test/out_rec_gem.root'
#             '/store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_2layers_10mm/160610_121123/0000/step4_1.root'
             '/store/user/archie/Signal/CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-REDIGI_2layers_500um/160623_083438/0000/ReDIGI_10.root' 

                )
           )

process.output = cms.OutputModule("PoolOutputModule",
    fileName = cms.untracked.string(
        'out_STA_reco_NoGE21_pT100.root'
    ),
    outputCommands = cms.untracked.vstring(
        'keep  *_*_*_*',
    ),
   # SelectEvents = cms.untracked.PSet(
   #     SelectEvents = cms.vstring('stareco_step')
   #)

 )

process.raw2digi_step = cms.Path(process.RawToDigi)
process.L1Reco_step = cms.Path(process.L1Reco)
#process.stareco_step = cms.Path(process.offlineBeamSpot*process.standalonemuontracking)
process.reconstruction_step = cms.Path(process.reconstruction)
process.endjob_step  = cms.Path(process.endOfProcess)
process.out_step     = cms.EndPath(process.output)

process.schedule = cms.Schedule(
    process.raw2digi_step,
    process.L1Reco_step,
#    process.stareco_step,
    process.reconstruction_step,
    process.endjob_step,
    process.out_step
)

# Automatic addition of the customisation function from SLHCUpgradeSimulations.Configuration.combinedCustoms
from SLHCUpgradeSimulations.Configuration.combinedCustoms import cust_2023HGCalMuon

#call to customisation function cust_2023HGCalMuon imported from SLHCUpgradeSimulations.Configuration.combinedCustoms
process = cust_2023HGCalMuon(process)

# Automatic addition of the customisation function from Configuration.DataProcessing.Utils
from Configuration.DataProcessing.Utils import addMonitoring

#call to customisation function addMonitoring imported from Configuration.DataProcessing.Utils
process = addMonitoring(process)

# Automatic addition of the customisation function from Geometry.GEMGeometry.gemGeometryCustoms
from Geometry.GEMGeometry.gemGeometryCustoms import custom_GE11_8and8partitions_v2

#call to customisation function custom_GE11_8and8partitions_v2 imported from Geometry.GEMGeometry.gemGeometryCustoms
process = custom_GE11_8and8partitions_v2(process)

# End of customisation functions

