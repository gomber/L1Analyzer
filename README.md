# L1Analyzer
cmsrel CMSSW_8_0_7
cd CMSSW_8_0_7/src
cmsenv
git cms-init
git remote add cms-l1t-offline git@github.com:cms-l1t-offline/cmssw.git
git fetch cms-l1t-offline
git cms-merge-topic cms-l1t-offline:l1t-integration-$CMSSW_VERSION
cd L1Trigger
git clone git@github.com:SridharaDasu/L1TCaloSummary.git
git clone https://github.com/gomber/L1Analyzer.git
cd ..
scram b -j 8