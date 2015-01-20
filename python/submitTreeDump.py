import FWCore.ParameterSet.Config as cms

xsecTT_SL = 107.66
xsecTT_FL = 25.81
xsecTT_FH = 112.33

# /hdfs/cms/store/user/liis/TTH_Ntuples_v3/DiJetPt_SingleMuRun2012AAug06.root
# /hdfs/cms/store/user/liis/TTH_Ntuples_v3/DiJetPt_SingleMuRun2012AJul13.root
# /hdfs/cms/store/user/liis/TTH_Ntuples_v3/DiJetPt_SingleMuRun2012BJul13.root
# /hdfs/cms/store/user/liis/TTH_Ntuples_v3/DiJetPt_SingleMuRun2012CAug24Rereco.root
# /hdfs/cms/store/user/liis/TTH_Ntuples_v3/DiJetPt_SingleMuRun2012C-EcalRecover_11Dec2012-v1_v2.root
# /hdfs/cms/store/user/liis/TTH_Ntuples_v3/DiJetPt_SingleMuRun2012CPromptv2.root
# /hdfs/cms/store/user/liis/TTH_Ntuples_v3/DiJetPt_SingleMuRun2012CPromptV2TopUp.root
# /hdfs/cms/store/user/liis/TTH_Ntuples_v3/DiJetPt_SingleMuRun2012D-PromptReco-v1.root

# /hdfs/cms/store/user/liis/TTH_Ntuples_v3/DiJetPt_DYJetsToLL_M-10To50_TuneZ2Star_8TeV-madgraph.root
# /hdfs/cms/store/user/liis/TTH_Ntuples_v3/DiJetPt_DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph.root
# /hdfs/cms/store/user/liis/TTH_Ntuples_v3/DiJetPt_Tbar_s-channel_TuneZ2star_8TeV-powheg-tauola.root
# /hdfs/cms/store/user/liis/TTH_Ntuples_v3/DiJetPt_Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola.root
# /hdfs/cms/store/user/liis/TTH_Ntuples_v3/DiJetPt_Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola.root
# /hdfs/cms/store/user/liis/TTH_Ntuples_v3/DiJetPt_T_s-channel_TuneZ2star_8TeV-powheg-tauola.root
# /hdfs/cms/store/user/liis/TTH_Ntuples_v3/DiJetPt_T_t-channel_TuneZ2star_8TeV-powheg-tauola.root
# /hdfs/cms/store/user/liis/TTH_Ntuples_v3/DiJetPt_TTH_HToBB_M-125_8TeV-pythia6.root
# /hdfs/cms/store/user/liis/TTH_Ntuples_v3/DiJetPt_TTJets_FullLeptMGDecays_8TeV-madgraph.root
# /hdfs/cms/store/user/liis/TTH_Ntuples_v3/DiJetPt_TTJets_HadronicMGDecays_8TeV-madgraph.root
# /hdfs/cms/store/user/liis/TTH_Ntuples_v3/DiJetPt_TTJets_MassiveBinDECAY_8TeV-madgraph.root
# /hdfs/cms/store/user/liis/TTH_Ntuples_v3/DiJetPt_TTJets_SemiLeptMGDecays_8TeV-madgraph.root
# /hdfs/cms/store/user/liis/TTH_Ntuples_v3/DiJetPt_T_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola.root
# /hdfs/cms/store/user/liis/TTH_Ntuples_v3/DiJetPt_TTWJets_8TeV-madgraph.root
# /hdfs/cms/store/user/liis/TTH_Ntuples_v3/DiJetPt_TTZJets_8TeV-madgraph.root
# /hdfs/cms/store/user/liis/TTH_Ntuples_v3/DiJetPt_WJetsToLNu_TuneZ2Star_8TeV-madgraph-tarball.root
# /hdfs/cms/store/user/liis/TTH_Ntuples_v3/DiJetPt_WW_TuneZ2star_8TeV_pythia6_tauola.root
# /hdfs/cms/store/user/liis/TTH_Ntuples_v3/DiJetPt_WZ_TuneZ2star_8TeV_pythia6_tauola.root
# /hdfs/cms/store/user/liis/TTH_Ntuples_v3/DiJetPt_ZZ_TuneZ2star_8TeV_pythia6_tauola.root

ps = cms.VPSet([
	cms.PSet(
		skip	 = cms.bool(True),
		name	 = cms.string('TTH_HToBB_M-125_8TeV-pythia6'),
		nickName = cms.string('TTH125'),
		color	= cms.int32(2),
		xSec	 = cms.double(0.1302*0.569)
	),
	cms.PSet(
		skip	 = cms.bool(True),
		name	 = cms.string('TTJets_SemiLeptMGDecays_8TeV-madgraph'),
		nickName = cms.string('TTJetsSemiLept'),
		color	= cms.int32(41),
		xSec	 = cms.double(xsecTT_SL),
	),
	cms.PSet(
		skip	 = cms.bool(True),
		name	 = cms.string('TTJets_FullLeptMGDecays_8TeV-madgraph'),
		nickName = cms.string('TTJetsFullLept'),
		color	= cms.int32(41),
		xSec	 = cms.double(xsecTT_FL),
	),
])

for s in [
	"SingleMuRun2012AAug06",
	"SingleMuRun2012AJul13",
	"SingleMuRun2012BJul13",
	"SingleMuRun2012CAug24Rereco",
	"SingleMuRun2012C-EcalRecover_11Dec2012-v1_v2",
	"SingleMuRun2012CPromptv2",
	"SingleMuRun2012CPromptV2TopUp",
	"SingleMuRun2012D-PromptReco-v1"]:
	ps += [cms.PSet(
		skip	 = cms.bool(True),
		name	 = cms.string(s),
		nickName = cms.string(s),
		color	= cms.int32(1),
		xSec	 = cms.double(-1),
	)]
process = cms.Process("TreeProducer")

process.fwliteInput = cms.PSet(
	outFileName = cms.string("PLACEHOLDER"), #replaced later
	pathToFile = cms.string("/hdfs/cms/store/user/liis/TTH_Ntuples_v3/"),
	ordering = cms.string("DiJetPt_"),
	samples = ps
)

for i in range(len(ps)):
	nick = ps[i].nickName.value()
	process.fwliteInput.samples = cms.VPSet(ps[i])
	process.fwliteInput.samples[0].skip = False
	process.fwliteInput.outFileName = nick + ".root"

	#write python file
	ofname = "dump_" + nick + ".py"
	of = open(ofname, "w")
	of.write(process.dumpPython())
	of.close()

	#write bash file
	of = open("dump_" + nick + ".sh", "w")
	of.write("#!/bin/bash\n")
	of.write("set -e\n")
	of.write("echo TreeDumper " + ofname + "\n")
	of.write("TreeDumper " + ofname + "\n")
	of.close()


