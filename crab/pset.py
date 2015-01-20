import FWCore.ParameterSet.Config as cms

process = cms.Process('CustomJob')

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring()
)
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))
