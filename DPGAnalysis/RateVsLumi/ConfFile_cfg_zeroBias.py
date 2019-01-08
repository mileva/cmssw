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
process.GlobalTag.globaltag = '102X_dataRun2_Prompt_v7'

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1))	#180120) )

#process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )

process.source = cms.Source("PoolSource",
#    fileNames = cms.untracked.vstring(options.inputFiles)

    fileNames = cms.untracked.vstring(

'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/6117BC9E-23AD-EA4F-B356-9BE8BED6AEC0.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/065FB0FC-4EA3-E44F-B6F9-0B703759491E.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/4B9619E2-76BB-CC4F-91CB-574437A71F8D.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/951BF20A-0AB3-A64F-8774-171E670369AD.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/7742652B-F20A-9941-ABC6-F31B212DC69F.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/A8A56823-A575-E34C-AE0D-014483801FF4.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/FB229C0E-A2FD-D74D-BEE6-11B744FB7FA4.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/C978BCA3-96C5-8445-86A7-C5F1DAE3D576.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/3CD3E58B-6349-4E4F-AF7E-CB0113678F6B.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/4344F6D7-407F-074B-AF11-060D69C49C91.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/3046A047-843B-C049-8076-BC846DADCCBD.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/84EF1720-0784-0547-B303-4D8D7D433058.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/BC56C59F-3EF2-BC46-AF94-601E9A2A7E0C.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/2A5B85D4-2ACE-8E4F-8D76-42879405B828.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/BBDE8C32-96D2-5541-8F50-9B29ED541B19.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/D3AD8A6E-BE89-484F-9019-752CB83E4209.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/7F62D451-DC14-274B-B171-1394EC342540.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/FE13ABDE-A412-0945-AC03-8F66BA935F7A.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/BE1D9536-ECE5-5946-A01E-BECCB4EA4F3D.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/5AADD410-B7C3-DF45-AF2D-25502BA176AA.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/5535D4B4-85D2-904A-AD2E-F52B1C1E6733.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/6293B594-5128-BE41-AA6A-7467475A2B4D.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/17FBCF36-DE2A-6B4E-BF29-C04DD94ACD60.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/C098E2B3-E31D-E84E-8345-58DC0E0CAEA5.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/2376833F-5C52-DC42-9442-9CF7ECD52D97.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/531B1F44-E826-5B4B-B924-45241BCF41CC.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/1165C2AB-9F1F-8247-AFA5-5D0E3F8ECCF4.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/1B643803-6ACD-6C48-80B4-2615A8B53F73.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/989BA6D9-F84B-644F-B542-1D0A1D777558.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/1A9B112C-298C-8B46-B0DC-94C91E80982F.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/EBEB2FCD-1991-1843-8C80-57A9AE9EF1DF.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/4921DCAC-36F4-C648-9F13-22509A0C368C.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/D0350F4D-4F03-3641-BB12-825DD08A9F37.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/294129EF-80B6-9B41-BD26-43499DA5B557.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/78343E4A-6D51-B249-9EF2-1CA3C5E9276C.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/FCDC6402-C5C5-9644-822C-592DB7B73840.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/BACA1ABC-8778-5042-BA0B-06F8306407CA.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/C0F2CE7F-E645-9547-9945-1FEBDBF119E7.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/0C027661-AF80-3E4C-AECA-2FB8778B2793.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/5B81FFFB-C301-E24D-8BCF-FE7C8280DA3A.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/4CA20055-6DF6-F041-BA72-2FB978752C48.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/8F9AFD0D-CDEC-6741-9E09-75782F2DC479.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/59FFC267-A243-1148-9C26-EA3353D94ED5.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/55664048-013A-1D45-A0C8-6DA9F2CF27E4.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/45A5150B-C8F2-2D47-AD15-F82860659D6A.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/84329240-020E-C043-9047-CF820874AF87.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/DCADD412-7093-C542-A981-195F84D51C69.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/1CC8ED3B-87B7-BC40-9647-F2069278DC5C.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/6FA25596-EC55-E747-89D1-DBE89A8A0816.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/240F3793-F472-2E4A-BAE0-A0F541C5EDD6.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/FE5758E8-DC63-414F-9A1F-DEE334D1B009.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/E62EF307-7030-0F46-8545-82A69562D301.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/90FA5922-7D82-BB49-8877-37E747A66285.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/84ACD5D6-72F7-084F-AC6C-430FB474D34B.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/5E028668-CA56-DD4F-84C2-8E80F1976747.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/C657B8D4-0B4C-0045-94A7-123175CC9D3C.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/3C9C706B-5F8C-494F-B527-AEBF9E116CAA.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/0C2891D9-26C7-DB4A-86C2-2FC48A90212B.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/5044A5D2-0256-C94D-90A5-9D34B2C397EF.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/89CFE0A3-FB3F-144F-A187-6869E9EF8BDE.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/82EB88E9-6EE8-F24D-A7DB-965F4C1B8FA8.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/A8D11591-1F7B-5D4A-B308-9856CBFCED68.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/896A62EB-7426-A34B-8840-52C4730F0D8C.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/D29FF84F-6E09-BF46-8382-72138DDFB19F.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/1E9341B7-16BE-6E45-88B2-8455A4E0096D.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/0EC661A0-3B15-9F46-ADE4-7EAE0CB6C74C.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/4AC5989A-D0CC-414B-B070-FE62EADBAC79.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/D6A36684-D010-DA42-8825-F8492BC22991.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/8CA5C6D3-0163-9B46-A4C8-A25311DF1EA6.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/7FAB2981-0A83-A44F-BA45-314CC3C49277.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/C149E3C8-D95A-F543-8BA9-FAC9110E62DB.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/A7A2700B-D488-2540-A30B-94435913CD10.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/9D1357E9-64A4-DB4B-BC4A-46E21BDA4EA1.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/B4F08225-0867-334B-AF00-F64E32DFED32.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/5D86FD62-C730-554A-B383-9A20BC311D40.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/3C3602BA-819A-9747-9879-B7D64BC11269.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/1871E433-CB58-ED47-AC31-D939B3C9CEB6.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/67B6F91C-D12E-C74A-B0DE-3F518CEA4848.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/2AF40CF9-17A8-2E46-9144-1DB95CB28D43.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/DFB5FF76-66D4-9649-B85A-BE97BCDF92D7.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/3E1B78BC-4398-DF4F-9D4F-4F5C10E7CC88.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/7808A5DD-F073-0B43-B29E-8B146FA448A0.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/26F99981-F82D-9047-9142-A7E76FEA18D8.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/A26F5A34-300D-A841-915E-2739A76CAB99.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/4057E58C-8388-834C-B0DF-950A9B401EC8.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/2C87D214-19D4-CA4A-B55F-4D4EAF2372D0.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/F337C373-EADD-2546-A793-5E88529CF940.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/5E3BC9BC-C0E8-C040-8DC8-729DF5DC2703.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/E5335903-E247-FE4C-83DD-2A12AAB1A5E4.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/36AE7D78-D8B0-4F45-A3B6-FF69CC258DA6.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/F314C767-7D3D-224F-9201-16ED6ED60975.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/A249EF14-7D4C-FF4F-ACE2-B42E47DC3C59.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/992A57EF-694C-CC4F-8337-399A981B5941.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/05642E27-E45D-7143-A661-2D3D0DC8006C.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/C2109E54-1633-F441-9E8C-EF069D321879.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/4B6A9AF4-D9CB-D048-A69E-07B438658CB6.root',
'/store/data/Run2018D/ZeroBias/AOD/PromptReco-v2/000/323/525/00000/6070E163-0003-6C4D-9ADE-49686AA64BB2.root',
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
#     , srcRPC_PACT = cms.InputTag('muonRPCDigis')
     , rpcRecHits_tag=cms.untracked.InputTag('rpcRecHits')                       
     , numbBXs = cms.int32(6)		#default number is 6 bx windows [-2, 3], change this number regarding the mubmer of time windows (BXs) you are investigating
     , bxInvest = cms.int32(-2) 	#put the BX number that you want to investigate, doAllBXs should be set to False and numbBXs to 1. For the default options(i.e. all BX) this parameter will be skipped by the code. 
     ,scalersResults = cms.InputTag("scalersRawToDigi")
     , doRechits = cms.untracked.bool(False)	# default is True. # If true, the rate is counted from the rpc rechits.
# If False the rate will be counted from digis (belonging to the rechits,
# i.e. raw digis not entered in the reconstrcutions will not be counted)
# to run over all the digis the input dataformat should be changed.
# Reco format does not contain raw digis

)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('rpc_rechits_lumi_ZBpr2018D.root')
)

#import PhysicsTools.PythonAnalysis.LumiList as LumiList
#process.source.lumisToProcess = LumiList.LumiList(filename = '/afs/cern.ch/work/m/mileva/testRPCDigis/CMSSW_10_2_1/src/ratevslumi/RateVsLumi/myjsnrun321732.json').getVLuminosityBlockRange()
#process.source.lumisToProcess = LumiList.LumiList(filename = '/afs/cern.ch/work/m/mileva/testRPCDigis/CMSSW_10_1_7/src/rpcDigis/RPCDigiAna/myJson318880.txt').getVLuminosityBlockRange()

#process.Tracer = cms.Service("Tracer")
#process.p = cms.Path(process.muonRPCDigis*process.demo)
process.p = cms.Path(process.demo)
