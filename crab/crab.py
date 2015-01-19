from CRABClient.client_utilities import getBasicConfig
config = getBasicConfig()

config.General.requestName = 'tutorial_MC_generation_LHE'
config.General.workArea = 'crab_projects'

#config.JobType.pluginName = 'PrivateMC'
#config.JobType.generator = 'lhe'
config.JobType.psetName = 'pset.py'
config.JobType.inputFiles = ['infiles.txt', 'FrameworkJobReport.xml']
config.JobType.scriptExe = 'testsubmit.sh'

#config.Data.primaryDataset = 'MinBias'
config.Data.splitting = 'EventBased'
config.Data.unitsPerJob = 1
config.Data.totalUnits = 5
config.Data.publication = True
config.Data.publishDataName = 'CRAB3_tutorial_MC_generation_LHE'

config.Site.storageSite = "T2_EE_Estonia"
