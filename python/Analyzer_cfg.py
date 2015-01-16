import FWCore.ParameterSet.Types as CfgTypes
import FWCore.ParameterSet.Config as cms
process = cms.Process("TreeProducer")

xsecTT_SL = 107.66
xsecTT_FL = 25.81
xsecTT_FH = 112.33

process.fwliteInput = cms.PSet(
    outFileName   = cms.string("output.root"),
    pathToFile    = cms.string(""),
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
            name     = cms.string("TTJetsFullLept_small"),
            nickName = cms.string("TTJetsFullLept"),
            color    = cms.int32(2),
            xSec     = cms.double(xsecTT_FL),
            ntree    = cms.double(9644590.0),
            ngen    = cms.double(11684417.0),
        ),
        cms.PSet(
            skip     = cms.bool(False),
            name     = cms.string("TTJetsSemiLept_small"),
            nickName = cms.string("TTJetsSemiLept"),
            color    = cms.int32(3),
            xSec     = cms.double(xsecTT_SL),
            ntree    = cms.double(16755422.0),
            ngen    = cms.double(25370432.0),
        ),
        ]
    )
)
