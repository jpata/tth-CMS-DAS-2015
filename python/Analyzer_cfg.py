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
    samples = cms.VPSet([
        cms.PSet(
            skip     = cms.bool(False),
            name     = cms.string("TTH125"),
            nickName = cms.string("TTH125"),
            color    = cms.int32(1),
            xSec     = cms.double(0.1302*0.569),
            ntree    = cms.double(184648.0),
            ngen    = cms.double(433891.09375),
        ),
        cms.PSet(
            skip     = cms.bool(False),
            name     = cms.string("TTJetsFullLept"),
            nickName = cms.string("TTJetsFullLept"),
            color    = cms.int32(2),
            xSec     = cms.double(xsecTT_FL),
            ntree    = cms.double(9644590.0),
            ngen    = cms.double(11684417.0),
        ),
        cms.PSet(
            skip     = cms.bool(False),
            name     = cms.string("TTJetsSemiLept"),
            nickName = cms.string("TTJetsSemiLept"),
            color    = cms.int32(3),
            xSec     = cms.double(xsecTT_SL),
            ntree    = cms.double(16755422.0),
            ngen    = cms.double(25370432.0),
        ),

        cms.PSet(
            skip     = cms.bool(False),
            name     = cms.string("SingleMuRun2012BJul13"),
            nickName = cms.string("SingleMuRun2012B"),
            color    = cms.int32(0),
            xSec     = cms.double(1.0),
            ntree    = cms.double(1.0),
            ngen    = cms.double(1.0),
        ),
        cms.PSet(
            skip     = cms.bool(False),
            name     = cms.string("SingleMuRun2012AJul13"),
            nickName = cms.string("SingleMuRun2012A"),
            color    = cms.int32(0),
            xSec     = cms.double(1.0),
            ntree    = cms.double(1.0),
            ngen    = cms.double(1.0),
        ),
        cms.PSet(
            skip     = cms.bool(False),
            name     = cms.string("SingleMuRun2012CAug24Rereco"),
            nickName = cms.string("SingleMuRun2012C"),
            color    = cms.int32(0),
            xSec     = cms.double(1.0),
            ntree    = cms.double(1.0),
            ngen    = cms.double(1.0),
        ),
        cms.PSet(
            skip     = cms.bool(False),
            name     = cms.string("SingleMuRun2012D-PromptReco-v1"),
            nickName = cms.string("SingleMuRun2012D"),
            color    = cms.int32(0),
            xSec     = cms.double(1.0),
            ntree    = cms.double(1.0),
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
