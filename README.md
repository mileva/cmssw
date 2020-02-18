This is the first working version of the cppf emulator using rpc digis as an input instead of rpc rechits. The cppf emulator is working localy, however it is still not included in the standard sequences. The clusterizer is a alcmost a copy from the clusterizer in the rpc rechit package. It might be updated further depend on the particular needs.


Run the code:

mkdir testEmulator2

cd testEmulator2

cmsrel CMSSW_11_0_0_pre7

cd CMSSW_11_0_0_pre7/src

cmsenv

git cms-init

git cms-addpkg L1Trigger

git cms-merge-topic mileva:cppfClusterizerWithDigi

scram b -j 8

cmsRun L1Trigger/L1TMuonCPPF/test/cppf_emulator_MC_modified.py

18.02.2020 - working for MC, but stil not in the standard sequences

cmsRun step2_DIGI_L1_DIGI2RAW_HLT.py




