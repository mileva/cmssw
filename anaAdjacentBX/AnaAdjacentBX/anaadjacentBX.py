import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.load("Configuration.StandardSequences.GeometryRecoDB_cff")
process.load("Configuration.StandardSequences.GeometryDB_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.load("Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff")
process.GlobalTag.globaltag = "80X_dataRun2_Express_v8"
process.load("Geometry.MuonNumbering.muonNumberingInitialization_cfi")

process.maxEvents = cms.untracked.PSet(
     input = cms.untracked.int32(1000) 
)

#process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )
#process.Tracer = cms.Service("Tracer")
#readFiles = cms.untracked.vstring()
#process.source = cms.Source ("PoolSource",fileNames = readFiles)
#readFiles.extend( [
#]);

process.source = cms.Source("PoolSource",
   fileNames = cms.untracked.vstring(


'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/008E207F-1520-E611-A92B-02163E011FCE.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/042ABAEF-1520-E611-BA90-02163E012812.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/0499257F-1520-E611-B766-02163E012620.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/08A387C2-1620-E611-85E4-02163E0142AA.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/08FAA8BD-1620-E611-9393-02163E014775.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/0A2ADCAD-1620-E611-AE82-02163E013790.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/12870B75-1520-E611-B286-02163E014587.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/161EFB8F-1520-E611-ACC1-02163E01472E.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/18B2C8B7-1620-E611-A87B-02163E012239.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/1CCD2A74-1520-E611-B93E-02163E0124FA.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/1E45FB6A-1520-E611-A19E-02163E0134CD.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/20A6C57E-1520-E611-B720-02163E01434D.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/2228977E-1520-E611-A490-02163E01364C.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/22A9DDB0-1620-E611-96DE-02163E01446D.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/26D0ADBF-1620-E611-897A-02163E013785.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/2A04426D-1520-E611-9976-02163E0122FC.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/2A20E5BB-1620-E611-A89C-02163E011B6E.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/2A692BAF-1620-E611-9C76-02163E014105.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/2C330A7E-1520-E611-BEA5-02163E0133DC.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/2E83A770-1520-E611-ADBB-02163E01451C.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/38E36F7F-1520-E611-9D1A-02163E012344.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/3AD35AB0-1620-E611-9BBD-02163E014736.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/3C07D36C-1520-E611-9CBD-02163E0134F9.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/3CD0D9AA-1620-E611-97EB-02163E011AE2.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/406925AE-1620-E611-BC71-02163E013929.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/408AF46E-1520-E611-895D-02163E011CAD.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/480C306D-1520-E611-8D1C-02163E012788.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/4AE9F17B-1520-E611-B219-02163E012B2B.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/4E9E3F70-1520-E611-A5D7-02163E013989.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/52D219EF-1520-E611-85AD-02163E0143BC.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/56A9C2B0-1620-E611-B86E-02163E014354.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/5869ECB5-1620-E611-9918-02163E01376A.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/62D42982-1520-E611-B861-02163E0133BE.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/645E40B1-1620-E611-94C0-02163E0141B2.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/68823E6E-1520-E611-ABB2-02163E011922.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/6A1A76AF-1620-E611-A85E-02163E0145FD.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/707AD4FA-1520-E611-9A60-02163E013796.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/728C307C-1520-E611-A1C3-02163E012B2B.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/72B7F59A-1520-E611-A859-02163E011B40.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/74D2D48F-1520-E611-80E7-02163E01472E.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/7643736F-1520-E611-B736-02163E01417E.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/76C2CE8F-1520-E611-A0C3-02163E013831.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/78B90EB0-1620-E611-95E4-02163E014529.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/7C19676D-1520-E611-B85E-02163E013785.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/7CB07C7F-1520-E611-88C8-02163E012344.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/7EA2D5B3-1620-E611-9843-02163E013400.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/80C75E7D-1520-E611-918F-02163E014404.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/841FE97D-1520-E611-92C5-02163E01397E.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/88EAEFB0-1620-E611-9812-02163E0137D0.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/8AC803C2-1620-E611-A4CB-02163E0146D6.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/8CBAD2AE-1620-E611-B440-02163E014605.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/8E480FB0-1620-E611-92ED-02163E01444A.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/92BE6CAB-1620-E611-B73C-02163E01385A.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/9411ACB2-1620-E611-8022-02163E011F6B.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/941A18B1-1620-E611-96A8-02163E01460E.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/986CA885-1520-E611-8BD2-02163E0145EE.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/98BFB98F-1520-E611-80FC-02163E013831.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/9E71606D-1520-E611-9C16-02163E013785.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/9E79B86C-1520-E611-86D4-02163E014595.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/A0BC02AF-1620-E611-B1FB-02163E014531.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/AA03C8C0-1620-E611-B3C5-02163E01392E.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/AEBC12AF-1620-E611-AFAF-02163E0145CD.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/B00FE169-1520-E611-A301-02163E0141AB.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/B406E7C1-1620-E611-A95B-02163E0123D9.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/B47929EF-1520-E611-B20D-02163E0143BC.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/B48A307D-1520-E611-B780-02163E013975.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/BCBD43C9-1620-E611-AC44-02163E014146.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/BE43BA71-1520-E611-B252-02163E011CF0.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/BEBB257F-1520-E611-889B-02163E012620.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/C0A324B3-1620-E611-B9B2-02163E014721.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/C0D58E6D-1520-E611-BE1F-02163E014270.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/CA70E0C0-1620-E611-B733-02163E0142AE.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/CC1F0F7E-1520-E611-99FE-02163E0133DC.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/CC8BAE6D-1520-E611-8398-02163E01221A.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/CC9AA3AE-1620-E611-BA46-02163E0145FC.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/D05ED86C-1520-E611-8815-02163E0134F9.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/D22165ED-1520-E611-8B74-02163E0138EF.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/D2F281EB-1520-E611-8B3B-02163E012B71.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/D6CFA6AD-1620-E611-A410-02163E011BDF.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/E049139B-1520-E611-BE33-02163E011B40.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/E07B90EB-1520-E611-8555-02163E012B71.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/E0D00982-1520-E611-B7D3-02163E01433E.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/E2F88982-1520-E611-B842-02163E0136C3.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/E4A62EC8-1620-E611-A3A7-02163E0119F7.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/E4B59D6E-1520-E611-9D19-02163E012AF2.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/E6A1A7AC-1620-E611-87FE-02163E014559.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/E6B576ED-1520-E611-A34A-02163E0138EF.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/E8B4AFB2-1620-E611-97B1-02163E01425D.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/EAD3B26C-1520-E611-9A63-02163E01450E.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/EE0C3DB3-1620-E611-81C3-02163E01449A.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/F04AB86C-1520-E611-959F-02163E01450E.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/F4402371-1520-E611-9C72-02163E0134C3.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/F664D27D-1520-E611-95BF-02163E0136B1.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/F8B3E26C-1520-E611-9BD8-02163E013901.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/FA6FA900-1620-E611-A606-02163E011E47.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/FE18A0AC-1620-E611-9EAB-02163E011A1A.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/FE52A47E-1520-E611-9F97-02163E01364C.root',
'root://eoscms//eos/cms/store/data/Run2016B/RPCMonitor/RAW/v2/000/273/730/00001/FEFB0DB1-1620-E611-8E22-02163E01460E.root'
)
)


#process.checkMuSize = cms.EDFilter("MuonsizeFilter"
#                                            )

## require scraping filter
process.scrapingVeto = cms.EDFilter("FilterOutScraping",
                                     applyfilter = cms.untracked.bool(True),
                                     debugOn = cms.untracked.bool(False),
                                     numtrack = cms.untracked.uint32(10),
                                     thresh = cms.untracked.double(0.2)
                                     )

process.primaryVertexFilter = cms.EDFilter("GoodVertexFilter",
                                            vertexCollection = cms.InputTag('offlinePrimaryVertices'),
                                            minimumNDOF = cms.uint32(4) ,
                                            maxAbsZ = cms.double(24),
                                            maxd0 = cms.double(2)
                                            )


process.demo = cms.EDAnalyzer('AnaAdjacentBX',
    rpcRecHits = cms.untracked.InputTag("hltRpcRecHits")
#    rpcRecHits = cms.untracked.InputTag("rpcRecHits")
)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('anaAdjBX_273730_rpcMon.root')
)

process.p = cms.Path(process.demo)
#process.p = cms.Path(process.scrapingVeto*process.primaryVertexFilter*process.demo)
