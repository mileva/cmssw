import FWCore.ParameterSet.Config as cms
process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.load('Configuration.Geometry.GeometryExtended2023Reco_cff')
process.load('Configuration.Geometry.GeometryExtended2023_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
#process.GlobalTag.pfnPrefix = cms.untracked.string('frontier://FrontierProd/')
process.load('Configuration.StandardSequences.MagneticField_38T_PostLS1_cff')
process.GlobalTag.globaltag = 'DES19_62_V8::All'
process.maxEvents = cms.untracked.PSet(
     input = cms.untracked.int32(10) 
)

#process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )
#process.Tracer = cms.Service("Tracer")
readFiles = cms.untracked.vstring()
process.source = cms.Source ("PoolSource",fileNames = readFiles)
readFiles.extend( [


'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_1000_1_LnK.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_100_1_fJo.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_101_1_LC8.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_102_1_HtJ.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_103_1_toZ.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_104_1_Gp3.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_105_1_UVQ.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_106_1_5gA.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_107_1_sBK.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_108_1_Kwu.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_109_1_TM6.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_10_1_YvO.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_110_1_m6H.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_111_1_EaX.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_112_1_Y9z.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_113_1_F8j.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_114_1_EGs.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_115_1_sNW.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_116_1_4mZ.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_117_1_sA3.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_118_1_Gnh.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_119_1_Z1d.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_11_1_nJa.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_120_1_ZVU.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_121_1_Nm0.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_122_1_3MP.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_123_1_Rlq.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_124_1_VFP.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_125_1_lrV.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_126_1_qEr.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_127_1_fal.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_128_1_L0z.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_129_1_C6l.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_12_1_rc9.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_130_1_Che.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_131_1_oIQ.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_132_1_GcK.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_133_1_r9P.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_134_1_8ap.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_135_1_Fcq.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_136_1_VJD.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_137_1_zJl.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_138_1_kIX.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_139_1_aSt.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_13_1_IWb.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_140_1_QX4.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_141_1_cN4.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_142_1_CPG.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_143_1_Uog.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_144_1_lDE.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_145_1_UUX.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_146_1_1ZS.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_147_1_iTf.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_148_1_Pzv.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_149_1_NdS.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_14_1_857.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_150_1_7vq.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_151_1_Hz5.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_152_1_IeM.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_153_1_FTb.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_154_1_GcW.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_155_1_Iw3.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_156_1_sTQ.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_157_1_Y8U.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_158_1_11T.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_159_1_x27.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_15_1_WQH.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_160_1_iXT.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_161_1_DoL.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_162_1_q41.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_163_1_wCp.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_164_1_Kvw.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_165_1_INJ.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_166_1_D79.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_167_1_uxR.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_168_1_Fxm.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_169_1_cTI.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_16_1_Lst.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_170_1_9gL.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_171_1_FEj.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_172_1_teP.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_173_1_oCa.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_174_1_J3A.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_175_1_TYQ.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_176_1_dPV.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_177_1_q6y.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_178_1_Hat.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_179_1_MtF.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_17_1_HGq.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_180_1_p7j.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_181_1_HAo.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_182_1_p4W.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_183_1_9ij.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_184_1_W1Y.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_185_1_jyY.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_186_1_jc9.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_187_1_mOr.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_188_1_9Yr.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_189_1_4GS.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_18_1_bOg.root',
'root://eoscms//eos/cms/store/user/mileva/DYToMuMu_M-20_TuneZ2star_14TeV-pythia6-tauola/gem2019DYM20RecoSLHC23p1PU50Link/9429b9589d122f7ca61a6bdea9179dd8/DY2019PU50reco_simlink_190_1_Qao.root',

]);

process.checkMuSize = cms.EDFilter("MuonsizeFilter"
                                            )
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


#from SimGeneral.MixingModule.mixNoPU_cfi                          import *
#from SimGeneral.TrackingAnalysis.trackingParticlesNoSimHits_cfi   import * 
#from SimMuon.MCTruth.MuonAssociatorByHitsESProducer_NoSimHits_cfi import *

process.load('MuonAnalysis.MuonAssociators.muonClassifwithAna_cfi')

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('muClassByHits_histos.root')
)

process.p = cms.Path(
                     process.checkMuSize*
                     process.scrapingVeto*
        	     process.primaryVertexFilter*
                     process.selectedVertices*
                     #process.classByHits
                     (
	             process.classByHits#+
#	             process.classByHitsPtCut15+
#	             process.classByHitsPtCut5+
#	             process.classByHitsPtCut3

                     )

		 ) 
