import FWCore.ParameterSet.Config as cms



process = cms.Process("TEST")
process.source = cms.Source("EmptyIOVSource",
    lastValue = cms.uint64(1),
    timetype = cms.string('runnumber'),
    firstValue = cms.uint64(1),                    
    interval = cms.uint64(1)
)

process.PoolDBOutputService = cms.Service("PoolDBOutputService",
    logconnect = cms.untracked.string('sqlite_file:log.db'),

    DBParameters = cms.PSet(
        messageLevel = cms.untracked.int32(0),
        authenticationPath = cms.untracked.string('.')
    ),
    timetype = cms.untracked.string('runnumber'),
    connect = cms.string('sqlite_file:RPCClusterSize_PhaseII_mc.db'),
    toPut = cms.VPSet(cms.PSet(
        record = cms.string('RPCClusterSizeRcd'),
        tag = cms.string('RPCClusterSize_PhaseII_mc')
    ))
)

#process.mytest = cms.EDAnalyzer('RPCDBClsPerformanceHandler',
process.mytest = cms.EDAnalyzer('MyRPCDBClsPopConAnalyzer',
                                record = cms.string('RPCClusterSizeRcd'),
    Source = cms.PSet(
clsidmapfile =
                                cms.FileInPath('CalibMuon/RPCCalibration/data/cls_PhaseII.txt'),
        firstSince = cms.untracked.int32(1),
tag = cms.string('RPCClusterSize_PhaseII_mc')
)
)


process.p = cms.Path(process.mytest)



