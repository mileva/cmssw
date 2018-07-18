import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

#from FWCore.ParameterSet.VarParsing import VarParsing

#options = VarParsing("analysis")


process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(1)
process.MessageLogger.cerr.threshold = cms.untracked.string('DEBUG')
process.MessageLogger.debugModules = cms.untracked.vstring()
#process.MessageLogger.debugModules.append('muonRPCDigis')
#process.MessageLogger.debugModules.append('omtfStage2Digis')
process.options = cms.untracked.PSet( wantSummary=cms.untracked.bool(False))


process.load('Configuration.StandardSequences.Services_cff')
#process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
##process.load('Configuration.EventContent.EventContent_cff')
#process.load('Configuration.Geometry.GeometryExtended2016Reco_cff')
process.load('Configuration.StandardSequences.GeometryDB_cff')
process.load('Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff')
#process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.load('Configuration.StandardSequences.RawToDigi_Data_cff')
#process.load('EventFilter.L1TRawToDigi.bmtfDigis_cfi')
#process.load('EventFilter.L1TRawToDigi.emtfStage2Digis_cfi')
#process.load('EventFilter.L1TRawToDigi.gmtStage2Digis_cfi')
#process.load('EventFilter.L1TXRawToDigi.twinMuxStage2Digis_cfi')

from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
process.GlobalTag.globaltag = '101X_dataRun2_Express_v8'

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

#process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )

process.source = cms.Source("PoolSource",
#    fileNames = cms.untracked.vstring(options.inputFiles)

    fileNames = cms.untracked.vstring(

## here are the root files, corresponding to file dataset=/ExpressPhysics/Run2018C-Express-v1/FEVT run=319853 lumi=1
## https://cmsweb.cern.ch/das/request?view=list&limit=50&instance=prod%2Fglobal&input=file+dataset%3D%2FExpressPhysics%2FRun2018C-Express-v1%2FFEVT+run%3D319853+lumi%3D1
## ! some files contain more than 1 lumi section and thus json file is needed
'/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/319/853/00000/D03A7C49-798A-E811-929A-02163E01492B.root'


    )
)

process.demo = cms.EDAnalyzer('RPCDigiAna'
#     , tracks = cms.untracked.InputTag('ctfWithMaterialTracks')
     , srcRPC_PACT = cms.InputTag('muonRPCDigis')
)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('myoutput.root')
)

#import PhysicsTools.PythonAnalysis.LumiList as LumiList
#process.source.lumisToProcess = LumiList.LumiList(filename = '/afs/cern.ch/work/m/mileva/testRPCDigis/CMSSW_10_1_7/src/myJson318876.txt').getVLuminosityBlockRange()
#process.source.lumisToProcess = LumiList.LumiList(filename = '/afs/cern.ch/work/m/mileva/testRPCDigis/CMSSW_10_1_7/src/rpcDigis/RPCDigiAna/myJson318880.txt').getVLuminosityBlockRange()

process.p = cms.Path(process.muonRPCDigis*process.demo)
