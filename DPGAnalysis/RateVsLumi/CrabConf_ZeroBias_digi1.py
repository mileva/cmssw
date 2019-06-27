from WMCore.Configuration import Configuration
from CRABClient.UserUtilities import config, getUsernameFromSiteDB

config = config()

config.section_("General")
config.General.requestName   = 'zerobias_rpcDigis_instLumi_Wp1'
config.General.transferLogs = True
config.General.transferOutputs = True

config.section_("JobType")
config.JobType.pluginName  = 'Analysis'
config.JobType.psetName    = 'ConfFile_cfg_zeroBias_digi.py'
config.JobType.inputFiles = ['chambersOff2018D.txt']
config.JobType.outputFiles = ['rpcDigis_Zb2018D_AOD_DTcheck_ChOff_Wp1.root']

config.section_("Data")
config.Data.inputDataset = '/ZeroBias/Run2018D-PromptReco-v2/AOD'

config.Data.inputDBS = 'global'
config.Data.splitting = 'LumiBased'
config.Data.unitsPerJob = 8	#10
config.Data.outLFNDirBase = '/store/user/mileva/zerobiasAODdigis'
config.Data.publication = False
config.Data.outputDatasetTag = 'zerobias_rpcDigis_instLumi_Wp1'
config.Data.lumiMask = 'myjsonforDTcomparison.txt'	#'notFinishedLumis_zerobias_digis_aod.json'
#    Select input data based on run-ranges
#config.Data.runRange = '234407'

config.section_("Site")
config.Site.storageSite = 'T2_CH_CERN'

