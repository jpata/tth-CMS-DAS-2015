import FWCore.ParameterSet.Types as CfgTypes
import FWCore.ParameterSet.Config as cms
process = cms.Process("TreeProducer")

process.fwliteInput = cms.PSet(
    outFileName   = cms.string("output.root"),
    pathToFile    = cms.string("data/"),
    ordering      = cms.string("DiJetPt_"),
    samples = cms.VPSet(
        cms.PSet(
            skip     = cms.bool(False),
            name     = cms.string('TTH_HToBB_M-125_8TeV-pythia6'),
            nickName = cms.string('TTH_HToBB'),
            color    = cms.int32(1),
            xSec     = cms.double(508.5)
        ),
    )
)
