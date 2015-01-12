import FWCore.ParameterSet.Types as CfgTypes
import FWCore.ParameterSet.Config as cms
process = cms.Process("TreeProducer")

process.fwliteInput = cms.PSet(
    outFileName   = cms.string("output.root"),
    pathToFile    = cms.string(""),
    ordering      = cms.string(""),
    samples = cms.VPSet(
        cms.PSet(
            skip     = cms.bool(False),
            name     = cms.string("TTH125"),
            nickName = cms.string("TTH125"),
            color    = cms.int32(1),
            xSec     = cms.double(508.5)
        ),
    )
)
