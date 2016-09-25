from CRABClient.UserUtilities import config
config = config()

config.section_("General")
config.General.requestName   = 'csc2gemSegmentextra100um'
config.General.transferLogs = True
config.General.transferOutputs = True

config.section_("JobType")
config.JobType.pluginName  = 'Analysis'
config.JobType.psetName    = 'testGEM_pseudoRechits.py'
config.JobType.outputFiles = ['testGEMreso_100um.root']

config.section_("Data")

config.Data.inputDBS = 'phys03'
config.Data.inputDataset = '/Signal/archie-CMSSW_620SLHC27_SingeMuPt100_14TeV_pythia6_GEN-SIM-DIGI-RECO-RERECO_GE21Upd_2layers_pT100_100um-fd14455753413aa8d90351369f4eb0ef/USER'
#config.Data.outLFNDirBase = '/store/group/dpg_rpc/comm_rpc/Sandbox/mileva'

config.Data.outLFNDirBase = '/store/user/mileva/rpcUpgrade'
config.Data.splitting = 'FileBased'
#config.Data.primaryDataset = 'SingleMu'
config.Data.unitsPerJob = 25
#NJOBS = 1  # This is not a configuration parameter, but an auxiliary variable that we use in the next line.
#config.Data.totalUnits = config.Data.unitsPerJob * NJOBS
config.Data.publication = False
config.Data.publishWithGroupName = False
#config.Data.publishDataName = 'CRAB3_NO_GasLeak_SingleMuPt100_Reco'

config.section_("Site")
config.Site.storageSite = 'T2_CH_CERN'
