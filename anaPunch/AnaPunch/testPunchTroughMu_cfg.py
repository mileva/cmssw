import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = 'DES19_62_V8::All'
process.GlobalTag.pfnPrefix = cms.untracked.string('frontier://FrontierProd/')

process.load('Configuration.StandardSequences.MagneticField_38T_PostLS1_cff')
process.load('Configuration.Geometry.GeometryExtended2019Reco_cff')
process.load('Configuration.Geometry.GeometryExtended2019_cff')

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

readFiles = cms.untracked.vstring()
process.source = cms.Source ("PoolSource",fileNames = readFiles)
readFiles.extend( [

#'file:/afs/cern.ch/work/m/mileva/git/slhc7/CMSSW_6_2_0_SLHC7/src/minBias_reco.root'
#'file:/afs/cern.ch/work/m/mileva/git/slhc7/CMSSW_6_2_0_SLHC7/src/punchtest_reco.root'
'root://eoscms//eos/cms/store/user/mileva/minBiasTest/punchtest_reco.root'

]);

process.demo = cms.EDAnalyzer('AnaPunch')

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('testPunchTrough.root')
)

process.p = cms.Path(process.demo)

