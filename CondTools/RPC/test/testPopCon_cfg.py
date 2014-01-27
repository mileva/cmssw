import FWCore.ParameterSet.Config as cms

process = cms.Process("ProcessOne")

#process.load("Configuration.Geometry.GeometryExtended2023RPCEtaUpscope_cff")
#process.load('Configuration.Geometry.GeometryExtended2023RPCEtaUpscopeReco_cff')

process.load("Configuration.Geometry.GeometryExtended2023RPCEta2Upscope_cff")
process.load('Configuration.Geometry.GeometryExtended2023RPCEta2UpscopeReco_cff')
#process.load("Configuration.Geometry.GeometryExtended2023RPCEtaUpscope_cff")
#process.load('Configuration.Geometry.GeometryExtended2023RPCEtaUpscopeReco_cff')
#process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.load("CondCore.DBCommon.CondDBCommon_cfi")
process.CondDBCommon.connect = 'sqlite_file:RPC_defaultValues_RPCEta2Upscope_mc.db'
process.CondDBCommon.DBParameters.authenticationPath = '/afs/cern.ch/cms/DB/conddb'

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(1)
)

# Input source
process.source = cms.Source("EmptySource")

process.options = cms.untracked.PSet(

)

process.MessageLogger = cms.Service("MessageLogger",
    cout = cms.untracked.PSet(
        default = cms.untracked.PSet(
            limit = cms.untracked.int32(0)
        )
    ),
    destinations = cms.untracked.vstring('cout')
)

process.source = cms.Source("EmptyIOVSource",
    firstValue = cms.uint64(1),
    lastValue = cms.uint64(1),
    timetype = cms.string('runnumber'),
    interval = cms.uint64(1)
)

process.PoolDBOutputService = cms.Service("PoolDBOutputService",
    process.CondDBCommon,
    logconnect = cms.untracked.string('sqlite_file:log.db'),
    timetype = cms.untracked.string('runnumber'),
    toPut = cms.VPSet(cms.PSet(
        record = cms.string('RPCStripNoisesRcd'),
        tag = cms.string('RPC_defaultValues_RPCEta2Upscope_mc')
    ))
)

#process.Test1 = cms.EDAnalyzer("MyRPCDBPopConAnalyzer",
process.Test1 = cms.EDAnalyzer("MyPopConAnalyzer",
    record = cms.string('RPCStripNoisesRcd'),
                               loggingOn= cms.untracked.bool(True),
                               IsDestDbCheckedInQueryLog=cms.untracked.bool(True),
                               SinceAppendMode=cms.bool(True),
    Source = cms.PSet(
        effmapfile = cms.FileInPath('CondTools/RPC/data/eff_short.txt'),
        noisemapfile = cms.FileInPath('CondTools/RPC/data/noise_short.txt'),
        clsmapfile = cms.FileInPath('CondTools/RPC/data/ClSizeTot.dat'),
        firstSince = cms.untracked.int32(1),
        tag = cms.string('RPC_defaultValues_RPCEta2Upscope_mc'),
        timingMap = cms.FileInPath('CondTools/RPC/data/RPCTiming_PhaseII.dat')
    )
)

process.p = cms.Path(process.Test1)
#process.CondDBCommon.connect = 'sqlite_file:pop_test.db'
#process.CondDBCommon.DBParameters.authenticationPath = '.'
#process.CondDBCommon.DBParameters.messageLevel = 1
