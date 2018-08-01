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

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(5000))	#180120) )

#process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )

process.source = cms.Source("PoolSource",
#    fileNames = cms.untracked.vstring(options.inputFiles)

    fileNames = cms.untracked.vstring(

## here are the root files, corresponding to file dataset=/ExpressPhysics/Run2018C-Express-v1/FEVT run=319853 lumi=1
## https://cmsweb.cern.ch/das/request?view=list&limit=50&instance=prod%2Fglobal&input=file+dataset%3D%2FExpressPhysics%2FRun2018C-Express-v1%2FFEVT+run%3D319853+lumi%3D1
## ! some files contain more than 1 lumi section and thus json file is needed
#'/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/319/853/00000/D03A7C49-798A-E811-929A-02163E01492B.root'


'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/003BD8C5-1C8E-E811-89F6-FA163E5AEA3D.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/006F33C0-248E-E811-9098-02163E010E93.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/007C2302-138E-E811-9B0C-FA163E4E1411.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/009422B9-0D8E-E811-BEE9-FA163EB132D4.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/00F29AA8-298E-E811-8FA3-FA163E15F06E.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/00FE77C7-1C8E-E811-BD3B-FA163E07DD78.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/02819822-358E-E811-AC1B-FA163E6509E5.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/028B719F-2A8E-E811-B407-FA163ED8FB28.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/02E49AA8-0D8E-E811-8EC3-FA163EDC261A.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/0412E75E-0D8E-E811-A775-FA163E390E7D.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/0472F692-1E8E-E811-9148-FA163E75A0C6.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/04834E6F-248E-E811-A7C2-FA163EFD1641.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/04B2C637-148E-E811-9439-FA163EC86521.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/04BD4F32-0D8E-E811-80AF-FA163EAF4DA3.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/04D5852F-0D8E-E811-8CC3-FA163EB18E96.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/0613A3FB-338E-E811-8882-FA163E4637E0.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/0625A71F-0E8E-E811-B7B5-FA163EAE1B00.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/0645ECEB-318E-E811-A2ED-FA163EEFB5F4.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/06A24B40-128E-E811-A9AC-FA163EB464F1.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/06ABF701-328E-E811-88D9-FA163E52F8C2.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/06C38F8F-0D8E-E811-81E8-FA163E8F4E24.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/06CFCE09-2F8E-E811-87C4-FA163E6B427B.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/06DDDE42-328E-E811-9C42-FA163E1E4DD9.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/06FBDFAC-358E-E811-9EED-02163E016100.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/084E8F62-358E-E811-A717-02163E01A02A.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/08527C6C-0D8E-E811-AA6B-FA163EAAAB05.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/0867672D-338E-E811-AD68-FA163E29B158.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/086F4329-268E-E811-BD6C-FA163E22EC2E.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/0878DABF-1C8E-E811-8B4C-FA163E7B5655.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/0879E732-238E-E811-806D-FA163E8867C8.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/0893255F-218E-E811-94E1-FA163E48E52D.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/0896CCBB-108E-E811-8F32-FA163E8DC37A.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/089C305A-218E-E811-97B8-FA163E6509E5.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/08BED1C7-1D8E-E811-B9AB-FA163E3D1715.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/08E7A117-2F8E-E811-86EB-FA163E405ADB.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/08F62657-298E-E811-97D2-FA163E69A638.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/0A0F49C4-108E-E811-8C7B-FA163EF23112.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/0A3D29E8-108E-E811-A36A-FA163E8103B1.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/0A400960-298E-E811-B331-FA163EF21D25.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/0A545F69-158E-E811-B89A-FA163EBDA549.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/0A70096B-118E-E811-AF25-02163E014AF9.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/0A757E97-248E-E811-865A-FA163EE8E7AA.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/0ACA612D-158E-E811-A495-FA163E742E94.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/0ACD854F-128E-E811-865F-02163E019FD9.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/0C381748-118E-E811-AC67-FA163E8CB8CB.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/0C6CF7DC-1C8E-E811-851A-FA163E42CC98.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/0CCB33BE-0E8E-E811-87DF-FA163E6A65E5.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/0CDF9150-148E-E811-829B-FA163E169DBD.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/0CEF6C13-2F8E-E811-A906-FA163E8F57B5.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/0E511B15-118E-E811-B4F9-FA163E0DC947.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/0E84E211-298E-E811-B366-FA163EF31053.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/0EC65FD4-108E-E811-B84B-02163E017F0F.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/0EE2990C-328E-E811-844C-FA163EC8B7BD.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/10216691-278E-E811-AD0C-FA163E5B858A.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/1031D1FD-218E-E811-9C7B-FA163E6509E5.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/1038ABCD-208E-E811-8A4E-FA163EB8F22B.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/1080749E-078E-E811-9DF2-FA163E448F1D.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/109A912F-0D8E-E811-96B9-FA163E6AE23B.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/10A4DE5F-308E-E811-AAD4-FA163EB783E7.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/10A9A513-298E-E811-A242-FA163E492FB1.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/10AB6860-178E-E811-8923-02163E010E3C.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/10ADFFD6-258E-E811-88E4-FA163E648DBD.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/10FC4A82-178E-E811-9C34-02163E017F53.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/121CFF20-2F8E-E811-B0E3-FA163ECAE37B.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/12398709-298E-E811-86C4-FA163EB5C384.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/128A932E-158E-E811-B0B1-FA163EF87070.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/128C64C6-0E8E-E811-A66C-FA163EC8DCCA.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/12A30AB0-178E-E811-A37F-02163E010E44.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/12BAF6D4-1C8E-E811-9B68-FA163E071670.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/12BAFDA3-148E-E811-8DBB-FA163E8E65F7.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/12DD9383-218E-E811-B84B-FA163E7B5655.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/12E36C88-248E-E811-A804-FA163EE46B94.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/1405BF56-218E-E811-9984-FA163EC10120.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/142008E7-318E-E811-8A93-FA163E00F3D3.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/14258091-288E-E811-897A-FA163E1B5CE1.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/1479354B-158E-E811-B286-FA163EEADE18.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/1493F7A0-248E-E811-B54D-02163E010D55.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/14AFDA00-348E-E811-9C33-FA163EABE0AA.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/14CB1D5A-358E-E811-B68C-FA163EAFE8F6.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/14E18D57-2F8E-E811-8AB9-FA163E75C6E8.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/14EFC4E9-258E-E811-92C4-FA163E03A9B7.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/16032F48-158E-E811-B402-FA163E64C8B0.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/162AAB52-178E-E811-9456-FA163EB89E18.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/163C18B0-268E-E811-96F7-02163E010CA8.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/165DF1E1-0E8E-E811-9C93-FA163E67D598.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/1665CC15-2F8E-E811-9238-FA163EAA8A81.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/1691536B-0D8E-E811-BC59-FA163EEBD539.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/169D4A83-248E-E811-A808-FA163EC2DD21.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/16E628D1-318E-E811-861F-FA163E47E71E.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/16F8816F-148E-E811-8EE7-FA163EDC2E45.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/180BA27A-248E-E811-AF1C-FA163E87D4FF.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/18267BF1-318E-E811-87C5-FA163EF1FB9C.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/1827F75F-0A8E-E811-BA0A-FA163EBA050E.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/182C0C26-2F8E-E811-AE9A-02163E015C0F.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/186989A2-258E-E811-A67F-FA163EFC4E1B.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/188C3CC9-328E-E811-9DC2-02163E010E3D.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/18963279-0F8E-E811-83D6-FA163EAE16F7.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/18A3A5BB-108E-E811-9780-FA163EDA3F4C.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/18DA128C-148E-E811-8CAE-FA163EF55B81.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/1A14A4F6-318E-E811-B0BC-FA163E43A949.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/1A1E0B66-298E-E811-881E-FA163E1A9BF9.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/1A46B232-388E-E811-A7A1-FA163EBDD79C.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/1A7F9F6B-298E-E811-A4A1-A4BF01277792.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/1AB622BE-0D8E-E811-848E-FA163E5C9AAE.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/1AC480B0-278E-E811-8056-FA163E99485E.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/1C070A75-0D8E-E811-A85B-FA163EEFFA87.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/1C1D7899-148E-E811-9075-FA163E617121.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/1C29D83C-1E8E-E811-934A-FA163EB2BB26.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/1C3F5015-268E-E811-90D4-FA163EC58599.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/1C47D515-2F8E-E811-9D6C-02163E019FA0.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/1C51A9DD-248E-E811-A5EB-FA163EA6472C.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/1CF30A35-158E-E811-BDFB-FA163E498C7B.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/1E019D47-298E-E811-83FE-FA163EE09AAE.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/1E0592F4-148E-E811-B904-FA163E81F19A.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/1E0ED0D4-108E-E811-BDA8-FA163EDC261A.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/1E12315A-178E-E811-83BD-FA163E22812C.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/1E3F9B9E-0E8E-E811-85F7-FA163E20727F.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/1E4F4AFC-148E-E811-B9AF-FA163E20F4FC.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/200141DC-258E-E811-95BA-FA163EA11B26.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/20500209-118E-E811-A691-FA163E140C81.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/2052AFD0-1C8E-E811-9D3D-FA163EB2BB26.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/206FB0C9-378E-E811-BB09-FA163E2D8A7B.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/20D874ED-1D8E-E811-B429-FA163E7B5655.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/20F53999-0D8E-E811-BFBB-FA163E48E52D.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/2203A3A1-0E8E-E811-9961-FA163E6E32F8.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/220E7A31-298E-E811-B9ED-FA163EFFF7A4.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/224971F3-348E-E811-A939-FA163E14AD21.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/225C16EA-1C8E-E811-8A1F-FA163EAC4CED.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/2263E052-248E-E811-9A2B-FA163E48C3C0.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/2264187C-0D8E-E811-8D50-FA163EB5923B.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/22ED80E2-288E-E811-8671-FA163E8CE6BD.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/2400B9C2-0A8E-E811-BB4A-FA163E42BF0F.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/24347374-298E-E811-A00D-02163E01A05B.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/243C8E8C-258E-E811-9025-FA163EDF0BCA.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/244DB4A0-2A8E-E811-80BE-FA163EA79471.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/2456EAA3-248E-E811-BF8D-FA163E194DBB.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/2493B16B-0D8E-E811-A763-FA163EC01D9C.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/24A13AB1-1C8E-E811-BD6F-FA163EC6DCA7.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/24A812BE-1C8E-E811-91AB-FA163E6F0F4A.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/24C7178D-248E-E811-99BA-FA163EE09AAE.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/24F3CCC5-378E-E811-8F94-FA163EA87350.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/26033443-328E-E811-933F-FA163E334E58.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/2626C97D-0D8E-E811-985A-FA163E5D107F.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/264813A5-298E-E811-9C92-FA163E253C3C.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/269B7AE1-2D8E-E811-9678-FA163EC7CC24.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/26B9873C-2F8E-E811-B506-02163E015C52.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/26EE1EF0-318E-E811-94BC-FA163E9394F7.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/283B5443-0F8E-E811-84CE-FA163E50F7ED.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/287AF9FB-1C8E-E811-93C5-FA163EE1C1A2.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/28CF8F79-1D8E-E811-A072-FA163E733247.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/28D76BA8-0A8E-E811-90B6-FA163E92AE01.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/2A871660-288E-E811-8137-FA163E3902DB.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/2AA43C0C-2F8E-E811-811A-FA163E0FF8B4.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/2AAEEC04-1D8E-E811-9C01-FA163E520798.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/2AC12F02-158E-E811-81E5-FA163EDEAFA5.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/2AD6205F-258E-E811-BA46-FA163EA1BA7E.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/2C47179F-218E-E811-8C82-FA163E8867C8.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/2C53BA3C-118E-E811-8688-FA163E60A5FD.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/2C5403BA-1C8E-E811-A955-FA163E19CDEB.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/2C884E51-158E-E811-848B-FA163E8A4693.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/2CAE9C51-328E-E811-8153-02163E010D2E.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/2CAFC594-3D8E-E811-BC5E-FA163E3EBAF3.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/2CB74D10-1E8E-E811-92F3-FA163E3CE8C4.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/2CBAD831-148E-E811-8A6E-FA163E6FB005.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/2CC39D97-1C8E-E811-B74C-FA163EBDA549.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/2CEC8019-2F8E-E811-8F31-FA163E1DA13A.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/2CEC89DC-1C8E-E811-86AF-FA163E28726B.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/2CF55408-1D8E-E811-9078-FA163EF4F4A1.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/2E1C8CA6-148E-E811-B288-02163E010E44.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/2E265E5C-328E-E811-B94F-FA163EF31053.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/2E2BA6CB-258E-E811-B419-FA163EC18BC6.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/2E34F7CF-1C8E-E811-BFB5-FA163E21A544.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/2E4BBA46-0D8E-E811-8973-FA163E569205.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/2E4EED37-1D8E-E811-A2E7-FA163EDEFB2C.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/2EBBA00B-388E-E811-946B-FA163E9F2F39.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/2EC24662-2F8E-E811-968D-FA163E32BC8F.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/3047612C-328E-E811-B4EC-02163E017712.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/305364E9-108E-E811-9F64-02163E018005.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/3057C8BE-148E-E811-9957-02163E018005.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/30615E4F-078E-E811-8749-FA163E468189.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/306A6753-148E-E811-8A43-FA163E07DD78.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/30939427-088E-E811-B9D8-FA163E063EFC.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/309C556D-2F8E-E811-801D-FA163E1E4DD9.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/30A76291-118E-E811-B0CF-FA163E50F7ED.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/30AB1179-178E-E811-8661-FA163E6E32F8.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/3202BA65-248E-E811-8FE7-FA163EF89580.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/3218E3DB-148E-E811-A117-FA163EEFFA87.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/32615173-2F8E-E811-931B-02163E010E3D.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/3262F135-0D8E-E811-AAC2-FA163E92AE01.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/327A2207-2F8E-E811-9C55-FA163EF7B363.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/32C355BC-258E-E811-9DC4-02163E010DE0.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/32E7C78A-078E-E811-973F-FA163E53585E.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/32F0ABE8-208E-E811-8D4F-FA163EEB8199.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/3412FDC7-1C8E-E811-97FA-02163E01A066.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/34135085-248E-E811-821C-FA163E6C4A2C.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/3472B209-2F8E-E811-A928-FA163E16165C.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/34D92D47-1E8E-E811-B9E7-FA163EF5354D.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/361013AA-248E-E811-91C9-FA163E8E506A.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/3617876D-1D8E-E811-8F51-FA163E7594BA.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/3635DD7E-248E-E811-8FE5-FA163E28C9AF.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/36557458-168E-E811-B94B-02163E010E19.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/36BE157C-248E-E811-B0C1-FA163E63D50D.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/36D9D172-248E-E811-85D2-FA163E1EE512.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/36FCE23D-078E-E811-8C41-FA163E42BF0F.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/3800CC36-158E-E811-BBAE-02163E010F33.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/3840E3D2-1C8E-E811-B3C2-FA163E561F15.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/384FB89F-2F8E-E811-875F-02163E01770D.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/38763D2A-308E-E811-ADE8-02163E017727.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/3897DCE7-258E-E811-9B5E-02163E01A02A.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/38DCA565-0D8E-E811-AFF6-FA163EB15818.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/38E31954-0D8E-E811-9AD8-FA163EC7D185.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/3A1D5390-1F8E-E811-99F1-02163E00BFBA.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/3A21D0E4-358E-E811-985D-FA163EEFB5F4.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/3A3F0466-0D8E-E811-A705-FA163EF55B81.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/3A730169-248E-E811-8A5F-FA163E35F67F.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/3AB41468-308E-E811-95FA-02163E01617D.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/3ADA2D6C-248E-E811-B616-FA163E37A6C4.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/3C02F976-158E-E811-AF2F-FA163E4E1411.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/3C512BBA-328E-E811-A1F1-FA163EB69816.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/3C5EC91C-2F8E-E811-81DC-FA163E2F414D.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/3C73F534-0D8E-E811-B6CD-02163E019E95.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/3C7DADDA-1D8E-E811-A02E-FA163E510BE5.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/3CCCB2C8-1C8E-E811-9F03-FA163E34040E.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/3CDA1848-158E-E811-A082-FA163EB19AA2.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/3CE1F8EA-308E-E811-8F9C-FA163E99485E.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/3CFD0B14-388E-E811-BA94-FA163E46DFDB.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/3E4EE1F1-318E-E811-861B-FA163EF38B4B.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/3E620061-178E-E811-9F69-FA163E20F4FC.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/3E644BE9-148E-E811-8B92-FA163EECDD26.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/3E8809B1-108E-E811-AD63-FA163E742E94.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/3EAC4252-0D8E-E811-898D-FA163ED84AE9.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/3EE88821-2F8E-E811-8D63-FA163E53636C.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/3EE97CF8-0D8E-E811-A7D9-FA163EB63606.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/3EF0AB77-218E-E811-90D5-FA163EA2F461.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/400D196B-158E-E811-92D1-02163E010DA3.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/40220921-328E-E811-909E-FA163E160BB8.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/4062646A-208E-E811-9A63-FA163E2A9C42.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/4087EA34-148E-E811-AF01-FA163E826F19.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/40BBB976-248E-E811-8445-FA163E5601EC.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/40DB81DD-258E-E811-917E-FA163E28C9AF.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/40F565C7-108E-E811-A8B7-FA163EC6DCA7.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/42204BD3-248E-E811-B1AE-FA163EDBDD4C.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/422D22C8-288E-E811-82E9-FA163E9494F2.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/42671930-358E-E811-919D-FA163EE6286A.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/428A9F94-0E8E-E811-9A3B-FA163E77814C.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/42AC6F6C-358E-E811-A1E9-FA163EA1F4CF.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/42C9AEF6-1C8E-E811-B4B5-FA163EF2F592.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/42D95DCE-178E-E811-98B5-FA163E721D55.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/42D9E58B-2C8E-E811-8BAB-FA163E8187F0.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/42E339E5-338E-E811-8BDB-FA163EA79EBD.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/4419615D-118E-E811-AEB0-FA163EA94480.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/44472144-148E-E811-A098-FA163EB23546.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/4462996E-248E-E811-8489-FA163E337911.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/44826230-248E-E811-8791-FA163E5453A2.root',
'file:/eos/cms/store/express/Run2018C/ExpressPhysics/FEVT/Express-v1/000/320/065/00000/44854A9E-2F8E-E811-8CB0-FA163E841855.root'



    )
)

process.demo = cms.EDAnalyzer('RPCDigiAna'
     , debug = cms.untracked.bool(False)
     , doAllBXs = cms.untracked.bool(False)	# default is True. If true, please put numbBXs=6, put False if you want to investigate only particular BX window
     , srcRPC_PACT = cms.InputTag('muonRPCDigis')
     , numbBXs = cms.int32(1)		#default number is 6 bx windows [-2, 3], change this number regarding the mubmer of time windows (BXs) you are invstigating
     , bxInvest = cms.int32(-2) 	#put the BX number that you want to investigate, doAllBXs should be set to True and numbBXs to 1. For the default options(i.e. all BX) this parameter will be skipped by the code. 

)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('myoutput_test.root')
)

#import PhysicsTools.PythonAnalysis.LumiList as LumiList
#process.source.lumisToProcess = LumiList.LumiList(filename = '/afs/cern.ch/work/m/mileva/testRPCDigis/CMSSW_10_1_7/src/myJson318876.txt').getVLuminosityBlockRange()
#process.source.lumisToProcess = LumiList.LumiList(filename = '/afs/cern.ch/work/m/mileva/testRPCDigis/CMSSW_10_1_7/src/rpcDigis/RPCDigiAna/myJson318880.txt').getVLuminosityBlockRange()

process.p = cms.Path(process.muonRPCDigis*process.demo)
