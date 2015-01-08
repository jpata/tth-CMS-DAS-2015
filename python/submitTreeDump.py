import FWCore.ParameterSet.Config as cms

xsecTT_SL = 107.66
xsecTT_FL = 25.81
xsecTT_FH = 112.33

ps = cms.VPSet([
    cms.PSet(
    skip     = cms.bool(True),  
    name     = cms.string('TTH_HToBB_M-125_8TeV-pythia6'),
    nickName = cms.string('TTH125'),
    color    = cms.int32(2),
    xSec     = cms.double(0.1302*0.569)
    ),

    cms.PSet(
    skip     = cms.bool(True),  
    name     = cms.string('TTJets_SemiLeptMGDecays_8TeV-madgraph'),
    nickName = cms.string('TTJetsSemiLept'),
    color    = cms.int32(41),
    xSec     = cms.double(xsecTT_SL),
    ),

    cms.PSet(
    skip     = cms.bool(True),  
    name     = cms.string('TTJets_FullLeptMGDecays_8TeV-madgraph'),
    nickName = cms.string('TTJetsFullLept'),
    color    = cms.int32(41),
    xSec     = cms.double(xsecTT_FL),
    ),

    # cms.PSet(
    # skip     = cms.bool(True), 
    # name     = cms.string('DoubleElectronRun2012C-EcalRecover_11Dec2012-v1_v2'),
    # nickName = cms.string('Run2012_DoubleElectronRun2012C-EcalRecover_11Dec2012-v1_v2'),
    # color    = cms.int32(1),
    # xSec     = cms.double(-1),
    # ),
    # cms.PSet(
    # skip     = cms.bool(True), 
    # name     = cms.string('DoubleElectronRun2012CAug24RerecoEdmV42'),
    # nickName = cms.string('Run2012_DoubleElectronRun2012CAug24RerecoEdmV42'),
    # color    = cms.int32(1),
    # xSec     = cms.double(-1),
    # ),
    # cms.PSet(
    # skip     = cms.bool(True), 
    # name     = cms.string('DoubleElectronRun2012D'),
    # nickName = cms.string('Run2012_DoubleElectronRun2012D'),
    # color    = cms.int32(1),
    # xSec     = cms.double(-1),
    # ),
    # cms.PSet(
    # skip     = cms.bool(True), 
    # name     = cms.string('DoubleElectron_Run2012A-13Jul2012-v1_ProcFIXED'),
    # nickName = cms.string('Run2012_DoubleElectron_Run2012A-13Jul2012-v1_ProcFIXED'),
    # color    = cms.int32(1),
    # xSec     = cms.double(-1),
    # ),
    # cms.PSet(
    # skip     = cms.bool(True), 
    # name     = cms.string('DoubleElectron_Run2012A-recover-06Aug2012-v1_ProcV2'),
    # nickName = cms.string('Run2012_DoubleElectron_Run2012A-recover-06Aug2012-v1_ProcV2'),
    # color    = cms.int32(1),
    # xSec     = cms.double(-1),
    # ),
    # cms.PSet(
    # skip     = cms.bool(True), 
    # name     = cms.string('DoubleElectron_Run2012B-13Jul2012-v1_ProcFIXED'),
    # nickName = cms.string('Run2012_DoubleElectron_Run2012B-13Jul2012-v1_ProcFIXED'),
    # color    = cms.int32(1),
    # xSec     = cms.double(-1),
    # ),
    # cms.PSet(
    # skip     = cms.bool(True), 
    # name     = cms.string('DoubleElectron_Run2012C-PromptReco-v2_HBB_EDMNtupleV42_ProcV1'),
    # nickName = cms.string('Run2012_DoubleElectron_Run2012C-PromptReco-v2_HBB_EDMNtupleV42_ProcV1'),
    # color    = cms.int32(1),
    # xSec     = cms.double(-1),
    # ),
    # cms.PSet(
    # skip     = cms.bool(True), 
    # name     = cms.string('DoubleElectron_Run2012C-PromptReco-v2_HBB_EDMNtupleV42_ProcV2'),
    # nickName = cms.string('Run2012_DoubleElectron_Run2012C-PromptReco-v2_HBB_EDMNtupleV42_ProcV2'),
    # color    = cms.int32(1),
    # xSec     = cms.double(-1),
    # ),



    # cms.PSet(
    # skip     = cms.bool(True),  # 148139
    # name     = cms.string('SingleElectronRun2012AAug06EdmV42'),
    # nickName = cms.string('Run2012_SingleElectronRun2012AAug06EdmV42'),
    # color    = cms.int32(1),
    # xSec     = cms.double(-1),
    # ),
    # cms.PSet(
    # skip     = cms.bool(True), # 1551019
    # name     = cms.string('SingleElectronRun2012AJul13EdmV42b'),
    # nickName = cms.string('Run2012_SingleElectronRun2012AJul13EdmV42b'),
    # color    = cms.int32(1),
    # xSec     = cms.double(-1),
    # ),
    # cms.PSet(
    # skip     = cms.bool(True), # 9351330
    # name     = cms.string('SingleElectronRun2012BJul13EdmV42'),
    # nickName = cms.string('Run2012_SingleElectronRun2012BJul13EdmV42'),
    # color    = cms.int32(1),
    # xSec     = cms.double(-1),
    # ),
    # cms.PSet(
    # skip     = cms.bool(True), # 263593
    # name     = cms.string('SingleElectronRun2012C-EcalRecover_11Dec2012-v1_v2'),
    # nickName = cms.string('Run2012_SingleElectronRun2012C-EcalRecover_11Dec2012-v1_v2'),
    # color    = cms.int32(1),
    # xSec     = cms.double(-1),
    # ),
    # cms.PSet(
    # skip     = cms.bool(True), # 1064158
    # name     = cms.string('SingleElectronRun2012CAug24RerecoEdmV42'),
    # nickName = cms.string('Run2012_SingleElectronRun2012CAug24RerecoEdmV42'),
    # color    = cms.int32(1),
    # xSec     = cms.double(-1),
    # ),
    # cms.PSet(
    # skip     = cms.bool(True), # 9768094
    # name     = cms.string('SingleElectronRun2012CPromptv2EdmV42'),
    # nickName = cms.string('Run2012_SingleElectronRun2012CPromptv2EdmV42'),
    # color    = cms.int32(1),
    # xSec     = cms.double(-1),
    # ),
    # cms.PSet(
    # skip     = cms.bool(True), # 3491407
    # name     = cms.string('SingleElectronRun2012CPromptV2TopUpEdmV42'),
    # nickName = cms.string('Run2012_SingleElectronRun2012CPromptV2TopUpEdmV42'),
    # color    = cms.int32(1),
    # xSec     = cms.double(-1),
    # ),
    # cms.PSet(
    # skip     = cms.bool(True), # 16178887
    # name     = cms.string('SingleElectronRun2012D-PromptReco-v1_v3'),
    # nickName = cms.string('Run2012_SingleElectronRun2012D-PromptReco-v1_v3'),
    # color    = cms.int32(1),
    # xSec     = cms.double(-1),
    # ),

    # # THESE ARE FOR V2
    # cms.PSet(
    # skip     = cms.bool(True), # 90889
    # name     = cms.string('SingleMuRun2012AAug06EdmV42'),
    # nickName = cms.string('Run2012_SingleMuRun2012AAug06EdmV42'),
    # color    = cms.int32(1),
    # xSec     = cms.double(-1),
    # ),
    # cms.PSet(
    # skip     = cms.bool(True), # 916855
    # name     = cms.string('SingleMuRun2012AJul13EdmV42'),
    # nickName = cms.string('Run2012_SingleMuRun2012AJul13EdmV42'),
    # color    = cms.int32(1),
    # xSec     = cms.double(-1),
    # ),
    # cms.PSet(
    # skip     = cms.bool(True), # 6121904
    # name     = cms.string('SingleMuRun2012BJul13EdmV42'),
    # nickName = cms.string('Run2012_SingleMuRun2012BJul13EdmV42'),
    # color    = cms.int32(1),
    # xSec     = cms.double(-1),
    # ),
    # cms.PSet(
    # skip     = cms.bool(True), 
    # name     = cms.string('SingleMuRun2012C-EcalRecover_11Dec2012-v1_v2'),
    # nickName = cms.string('Run2012_SingleMuRun2012C-EcalRecover_11Dec2012-v1_v2'),
    # color    = cms.int32(1),
    # xSec     = cms.double(-1),
    # ),
    # cms.PSet(
    # skip     = cms.bool(True), 
    # name     = cms.string('SingleMuRun2012CAug24RerecoEdmV42'),
    # nickName = cms.string('Run2012_SingleMuRun2012CAug24RerecoEdmV42'),
    # color    = cms.int32(1),
    # xSec     = cms.double(-1),
    # ),
    # cms.PSet(
    # skip     = cms.bool(True), 
    # name     = cms.string('SingleMuRun2012CPromptV2TopUpEdmV42'),
    # nickName = cms.string('Run2012_SingleMuRun2012CPromptV2TopUpEdmV42'),
    # color    = cms.int32(1),
    # xSec     = cms.double(-1),
    # ),
    # cms.PSet(
    # skip     = cms.bool(True), 
    # name     = cms.string('SingleMuRun2012CPromptv2EdmV42'),
    # nickName = cms.string('Run2012_SingleMuRun2012CPromptv2EdmV42'),
    # color    = cms.int32(1),
    # xSec     = cms.double(-1),
    # ),
    # cms.PSet(
    # skip     = cms.bool(True), # 11860310
    # name     = cms.string('SingleMuRun2012D-PromptReco-v1'),
    # nickName = cms.string('Run2012_SingleMuRun2012D-PromptReco-v1'),
    # color    = cms.int32(1),
    # xSec     = cms.double(-1),
    # )
])

process = cms.Process("TreeProducer")

process.fwliteInput = cms.PSet(
    outFileName   = cms.string("output.root"),
    pathToFile    = cms.string("data/"),
    ordering      = cms.string("DiJetPt_"),
    samples = ps
)
for i in range(len(ps)):
	nick = ps[i].nickName.value()
	process.fwliteInput.samples = cms.VPSet(ps[i])
	process.fwliteInput.samples[0].skip = False
	process.fwliteInput.outFileName = nick + ".root"
	of = open("dump_" + nick + ".py", "w")
	of.write(process.dumpPython())
	of.close()

	