from CRABClient.UserUtilities import config
config = config()

config.General.workArea = 'crab_workArea'
config.General.transferOutputs = True
config.General.transferLogs = False
config.JobType.pluginName = 'Analysis'
config.Data.publication = False
config.Site.storageSite = 'T2_US_Wisconsin'
config.JobType.allowUndistributedCMSSW = True

config.JobType.psetName = 'test_summary_mc.py'
config.General.requestName = 'DYToLL_M_1_TuneCUETP8M1_13TeV_pythia8_May12_correceleID_correctneighbour_Sorted'
config.Data.inputDataset = '/DYToLL_M_1_TuneCUETP8M1_13TeV_pythia8/RunIIFall15DR76-25nsFlat10to50ZsecalNzshcalRaw_76X_mcRun2_asymptotic_2016EcalTune_30fb_v1_ext1-v1/AODSIM'
config.Data.inputDBS = 'global'
config.Data.splitting = 'FileBased'
config.Data.useParent= True
config.Data.unitsPerJob = 1
config.Data.totalUnits = -1 #-1 to run over all                                                                                                                                                                    
config.Data.outLFNDirBase = '/store/user/gomber'
