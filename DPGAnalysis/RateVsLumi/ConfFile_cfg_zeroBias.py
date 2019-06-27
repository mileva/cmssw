import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(1)
process.MessageLogger.cerr.threshold = cms.untracked.string('DEBUG')
process.MessageLogger.debugModules = cms.untracked.vstring()
process.options = cms.untracked.PSet( wantSummary=cms.untracked.bool(False))

process.load('Configuration.StandardSequences.Services_cff')
process.load('Configuration.StandardSequences.GeometryDB_cff')
process.load('Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.load('Configuration.StandardSequences.RawToDigi_Data_cff')

from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
process.GlobalTag.globaltag = '102X_dataRun2_Prompt_v11'

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1))	#180120) )

#process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )

process.source = cms.Source("PoolSource",

    fileNames = cms.untracked.vstring(

'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/D580E361-B379-744F-B1E9-4F6041EC5FD7.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/D44A8FA4-672F-5549-84AC-6ECB68C2A098.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/495DD4C5-9D8F-0B43-B0B9-4E34D455807F.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/1EF2E7F0-7170-AB49-8092-335AAFD06647.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/CCE657B8-B293-D943-A566-BE5D384E41C5.root'

    )
)

process.demo = cms.EDAnalyzer('RateVsLumi'
     , debug = cms.untracked.bool(False)
     , doAllBXs = cms.untracked.bool(True)	# default is True. If true, please put numbBXs=6, put False if you want to investigate only particular BX window
     , doAllBXno0 = cms.untracked.bool(False)	# run over all the noncentral BX, i.e. all BX!=0
     , doOnlyOneBX = cms.untracked.bool(False)	# run over one choosen BX, the ID number t be given in bxInvest
     , rpcRecHits_tag=cms.untracked.InputTag('rpcRecHits')                       
     , numbBXs = cms.int32(6)		#default number is 6 bx windows [-2, 3], change this number regarding the mubmer of time windows (BXs) you are investigating
     , bxInvest = cms.int32(-2) 	#put the BX number that you want to investigate, doAllBXs should be set to False and numbBXs to 1. For the default options(i.e. all BX) this parameter will be skipped by the code. 
     ,scalersResults = cms.InputTag("scalersRawToDigi")
     , doRechits = cms.untracked.bool(True)	# default is True. # If true, the rate is counted from the rpc rechits.
# If False the rate will be counted from digis (belonging to the rechits,
# i.e. raw digis not entered in the reconstrcutions will not be counted)
# to run over all the digis the input dataformat should be changed.
# Reco format does not contain raw digis
     , anaREm = cms.untracked.bool(False)	#do for RE negative?
     , anaREp =  cms.untracked.bool(False)	#do for RE positive>
     , anaW =  cms.untracked.bool(False)	#do  summary for wheel
     , myWheel = cms.int32(1) 		# wheel number under investigation
     , myBlackList = cms.string('chambersOff2018D.txt')

)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('rpcRechits_Zb2018D_AOD_DTcheck_ChOff_Wp1.root')
)

#process.Tracer = cms.Service("Tracer")
process.p = cms.Path(process.demo)
