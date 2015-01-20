from CRABClient.client_utilities import getBasicConfig
config = getBasicConfig()

config.General.requestName = 'custom_script'
config.General.workArea = 'crab_projects'

#config.JobType.pluginName = 'PrivateMC'
#config.JobType.generator = 'lhe'
config.JobType.psetName = 'pset.py'
config.JobType.inputFiles = ['FrameworkJobReport.xml']
config.JobType.scriptExe = 'testsubmit.sh'

#config.Data.primaryDataset = 'MinBias'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 1
config.Data.totalUnits = 5
config.Data.publication = False
config.Data.userInputFile = "infiles.txt"

config.Site.storageSite = "T2_EE_Estonia"
