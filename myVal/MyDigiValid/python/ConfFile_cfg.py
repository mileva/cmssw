import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.load("Geometry.MuonCommonData.muonIdealGeometryXML_cfi")

process.load("Geometry.MuonNumbering.muonNumberingInitialization_cfi")

#process.load("Geometry.RPCGeometry.rpcGeometry_cfi")
process.load('Configuration.StandardSequences.GeometryDB_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = 'MCRUN2_74_V0::All' #'PRE_ST62_V8::All'


process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

readFiles = cms.untracked.vstring()

process.source = cms.Source ("PoolSource",fileNames = readFiles)


readFiles.extend( [

'root://eoscms//eos/cms/store/relval/CMSSW_7_4_0_pre6/RelValTTbar_13/GEN-SIM-DIGI-RAW-HLTDEBUG/PUpmx50ns_MCRUN2_74_V0-v1/00000/1605CC29-70B1-E411-B976-0025905A48F2.root',
'root://eoscms//eos/cms/store/relval/CMSSW_7_4_0_pre6/RelValTTbar_13/GEN-SIM-DIGI-RAW-HLTDEBUG/PUpmx50ns_MCRUN2_74_V0-v1/00000/1ABB9E67-5FB1-E411-A672-0025905A48F0.root',
'root://eoscms//eos/cms/store/relval/CMSSW_7_4_0_pre6/RelValTTbar_13/GEN-SIM-DIGI-RAW-HLTDEBUG/PUpmx50ns_MCRUN2_74_V0-v1/00000/36070B84-5FB1-E411-8ECF-0025905A60DE.root',
'root://eoscms//eos/cms/store/relval/CMSSW_7_4_0_pre6/RelValTTbar_13/GEN-SIM-DIGI-RAW-HLTDEBUG/PUpmx50ns_MCRUN2_74_V0-v1/00000/50D2AE5F-5FB1-E411-A953-0025905A6064.root',
'root://eoscms//eos/cms/store/relval/CMSSW_7_4_0_pre6/RelValTTbar_13/GEN-SIM-DIGI-RAW-HLTDEBUG/PUpmx50ns_MCRUN2_74_V0-v1/00000/5A3D0C60-5FB1-E411-B7D8-0025905B858A.root',
'root://eoscms//eos/cms/store/relval/CMSSW_7_4_0_pre6/RelValTTbar_13/GEN-SIM-DIGI-RAW-HLTDEBUG/PUpmx50ns_MCRUN2_74_V0-v1/00000/6625D646-65B1-E411-95EA-0025905A48F2.root',
'root://eoscms//eos/cms/store/relval/CMSSW_7_4_0_pre6/RelValTTbar_13/GEN-SIM-DIGI-RAW-HLTDEBUG/PUpmx50ns_MCRUN2_74_V0-v1/00000/7A9F5684-5FB1-E411-9DEE-0025905A60A8.root',
'root://eoscms//eos/cms/store/relval/CMSSW_7_4_0_pre6/RelValTTbar_13/GEN-SIM-DIGI-RAW-HLTDEBUG/PUpmx50ns_MCRUN2_74_V0-v1/00000/80C6B872-5FB1-E411-A81E-0025905AA9F0.root',
'root://eoscms//eos/cms/store/relval/CMSSW_7_4_0_pre6/RelValTTbar_13/GEN-SIM-DIGI-RAW-HLTDEBUG/PUpmx50ns_MCRUN2_74_V0-v1/00000/985ACB7C-5FB1-E411-979E-0025905A610A.root',
'root://eoscms//eos/cms/store/relval/CMSSW_7_4_0_pre6/RelValTTbar_13/GEN-SIM-DIGI-RAW-HLTDEBUG/PUpmx50ns_MCRUN2_74_V0-v1/00000/9AABCC87-5FB1-E411-B111-0025905B858C.root'


     ] );




#process.source = cms.Source("PoolSource",
#    # replace 'myfile.root' with the source file you want to use
#    fileNames = cms.untracked.vstring(
#        'file:myfile.root'
#    )
#)

process.demo = cms.EDAnalyzer('MyDigiValid',
    # Tag for Digis event data retrieval
    rpcDigiTag = cms.untracked.InputTag("simMuonRPCDigis"),
    # Tag for simulated hits event data retrieval
    simHitTag = cms.untracked.InputTag("g4SimHits", "MuonRPCHits")

)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('myVal_histos.root')
)

process.p = cms.Path(process.demo)
