cmsrel CMSSW_10_0_4
cd CMSSW_10_0_4/src/
cmsenv
git cms-init
git cms-merge-topic mileva:noiseScanAna
scram b -j 23
cd myNoiseScan/MyNoiseScan/
scram b -j 10
cmsRun myNoiseScanAna_cfg.py 
root -l noiseScanAna.root 


