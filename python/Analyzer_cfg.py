import FWCore.ParameterSet.Types as CfgTypes
import FWCore.ParameterSet.Config as cms
process = cms.Process("TTHAnalyzer")

xsecTT_SL = 107.66
xsecTT_FL = 25.81
xsecTT_FH = 112.33

process.fwliteInput = cms.PSet(
    outFileName   = cms.string("output.root"),
    pathToFile    = cms.string("/data/shared/Long_Exercise_tth/"),
    ordering      = cms.string(""),
    firstEvent    = cms.uint64(0),
    lastEvent    = cms.uint64(0),
    samples = cms.VPSet([
        cms.PSet(
            name     = cms.string("TTH125"),
            nickName = cms.string("TTH125"),
            color    = cms.int32(1),
            xSec     = cms.double(0.1302*0.569),
            ngen    = cms.double(433891.09375),
        ),
        cms.PSet(
            name     = cms.string("TTJetsFullLept"),
            nickName = cms.string("TTJetsFullLept"),
            color    = cms.int32(2),
            xSec     = cms.double(xsecTT_FL),
            ngen    = cms.double(11684417.0),
        ),
        cms.PSet(
            name     = cms.string("TTJetsSemiLept"),
            nickName = cms.string("TTJetsSemiLept"),
            color    = cms.int32(3),
            xSec     = cms.double(xsecTT_SL),
            ngen    = cms.double(25370432.0),
        ),

        cms.PSet(
            name     = cms.string("SingleMuRun2012AJul13"),
            nickName = cms.string("SingleMuRun2012A1"),
            color    = cms.int32(0),
            xSec     = cms.double(1.0),
            ngen    = cms.double(1.0),
        ),
        cms.PSet(
            name     = cms.string("SingleMuRun2012AAug06"),
            nickName = cms.string("SingleMuRun2012A2"),
            color    = cms.int32(0),
            xSec     = cms.double(1.0),
            ngen    = cms.double(1.0),
        ),

        cms.PSet(
            name     = cms.string("SingleMuRun2012BJul13"),
            nickName = cms.string("SingleMuRun2012B"),
            color    = cms.int32(0),
            xSec     = cms.double(1.0),
            ngen    = cms.double(1.0),
        ),
        cms.PSet(
            name     = cms.string("SingleMuRun2012CAug24Rereco"),
            nickName = cms.string("SingleMuRun2012C1"),
            color    = cms.int32(0),
            xSec     = cms.double(1.0),
            ngen    = cms.double(1.0),
        ),
        cms.PSet(
            name     = cms.string("SingleMuRun2012C-EcalRecover_11Dec2012-v1_v2"),
            nickName = cms.string("SingleMuRun2012C2"),
            color    = cms.int32(0),
            xSec     = cms.double(1.0),
            ngen    = cms.double(1.0),
        ),
        cms.PSet(
            name     = cms.string("SingleMuRun2012CPromptv2"),
            nickName = cms.string("SingleMuRun2012C3"),
            color    = cms.int32(0),
            xSec     = cms.double(1.0),
            ngen    = cms.double(1.0),
        ),
        cms.PSet(
            name     = cms.string("SingleMuRun2012CPromptV2TopUp"),
            nickName = cms.string("SingleMuRun2012C4"),
            color    = cms.int32(0),
            xSec     = cms.double(1.0),
            ngen    = cms.double(1.0),
        ),
        cms.PSet(
            name     = cms.string("SingleMuRun2012D-PromptReco-v1"),
            nickName = cms.string("SingleMuRun2012D"),
            color    = cms.int32(0),
            xSec     = cms.double(1.0),
            ngen    = cms.double(1.0),
        ),
        ]
    )
)


if __name__ == "__main__":
    import ROOT
    for s in process.fwliteInput.samples:
        fn = process.fwliteInput.pathToFile.value() + process.fwliteInput.ordering.value() + s.name.value() + ".root"
        tf = ROOT.TFile(fn)
        tt = tf.Get("tree")
        print s.nickName.value(), tt.GetEntries()
