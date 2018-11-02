from WMCore.Configuration import Configuration

config = Configuration()

config.section_("General")
config.General.requestName   = 'zeroBias_rpcRechitsDigis1_instLumi'
config.General.transferLogs = True
config.General.transferOutputs = True

config.section_("JobType")
config.JobType.pluginName  = 'Analysis'
# Name of the CMSSW configuration file
config.JobType.psetName    = 'ConfFile_cfg_zeroBias.py'
config.JobType.outputFiles = ['myoutput_digi_lumi_test.root']

config.section_("Data")
config.Data.inputDataset = '/ZeroBias/Run2018D-PromptReco-v2/AOD'
#config.Data.inputDataset = '/ExpressCosmics/Commissioning2016-Express-v1/FEVT'

config.Data.inputDBS = 'global'
config.Data.splitting = 'LumiBased'
config.Data.unitsPerJob = 10
config.Data.outLFNDirBase = '/store/user/mileva/zeroBias'
config.Data.publication = False
# This string is used to construct the output dataset name
#config.Data.outputDatasetTag = 'Efficiency_Express2016Cruzet_step1'

# These values only make sense for processing data
#    Select input data based on a lumi mask
config.Data.lumiMask = 'mytestJsn.txt'
#    Select input data based on run-ranges
#config.Data.runRange = '234407'

config.section_("Site")
# Where the output files will be transmitted to
config.Site.storageSite = 'T2_CH_CERN'

