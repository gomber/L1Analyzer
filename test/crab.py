from WMCore.Configuration import Configuration
config = Configuration()
#General                                                                                                                                                                           
config.section_('General')
config.General.requestName = 'job_ZeroBias4_Stage3_fixMET_try'
config.General.workArea = 'crab_projects_ntuples_ZeroBias4_Stage3_fixMET_try'
config.General.transferLogs = True
#JobType                                                                                                                                                                           
config.section_('JobType')
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'test_summary.py'
config.JobType.outputFiles = ['Ntuple_Stage3.root']
config.JobType.allowUndistributedCMSSW = True

#Data                                                                                                                                                                              
config.section_('Data')
config.Data.inputDataset = '/ZeroBias4/Run2015D-v1/RAW'
#config.Data.inputDBS = 'global'                                                                                                                                                   
config.Data.splitting = 'LumiBased'
config.Data.unitsPerJob = 15
config.Data.publication = False
config.Data.totalUnits =  -1
config.Data.runRange = '259721'
#config.Data.ignoreLocality = True                                                                                                                                                 
config.Data.outLFNDirBase  ='/store/user/gomber/'
#User                                                                                                                                                                              
config.section_('User')
#Site                                                                                                                                                                              
config.section_('Site')
config.Site.storageSite = 'T2_US_Wisconsin'
