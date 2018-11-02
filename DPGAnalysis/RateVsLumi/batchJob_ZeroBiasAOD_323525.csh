#!/bin/csh
cd /afs/cern.ch/work/m/mileva/testRPCDigis/CMSSW_10_2_5_patch1/src/ratevslumi/RateVsLumi
eval `scramv1 runtime -csh`
cd -
setenv X509_USER_PROXY /afs/cern.ch/user/m/mileva/x509up_u35160
cmsRun /afs/cern.ch/work/m/mileva/testRPCDigis/CMSSW_10_2_5_patch1/src/ratevslumi/RateVsLumi/ConfFile_cfg_zeroBias323525.py
cp myoutput_rechits_lumi_323525_2Mevt.root /afs/cern.ch/work/m/mileva/testRPCDigis/CMSSW_10_2_5_patch1/src/ratevslumi/RateVsLumi/myoutput_rechits_lumi_323525_2Mevt.root
