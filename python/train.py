#!/usr/bin/env python

# Import the important parts from ROOT
try:
    import ROOT
except:
    pass

from ROOT import TMVA,TCut,TFile

import json
import sys

def file_type(fn):
    if fn in trainfiles:
        return TMVA.Types.kTraining
    else:
        return TMVA.Types.kTesting

#TMVA output file
out = TFile('TMVA.root', 'RECREATE')

factory = TMVA.Factory(
    "train", out,
    'Transformations=I;N:DrawProgressBar=False'
)

#define variables that we'll use for training
varlist = [
    "ht",
    "csv0", "csv1", "csv2", "csv3", "csv4", "csv5",
    "jet1_pt", "jet2_pt", "mean_csv", "sigma_csv", "m_closest"
]
for v in varlist:
    factory.AddVariable(v, "D")

flist = []
for fn in ["output.root"]:
    tf = TFile(fn.strip())
    for sample in ["TTH125"]:
        tree = tf.Get(sample + "_events")
        factory.AddSignalTree(tree, 1.0)

    for sample in ["TTJetsFullLept", "TTJetsSemiLept"]:
        tree = tf.Get(sample + "_events")
        factory.AddBackgroundTree(tree, 1.0)

# Set the per event weights string
factory.SetWeightExpression("1.0")

cut = ""
print("cut=", cut)
factory.PrepareTrainingAndTestTree(
    TCut(cut), TCut(cut),
    "NormMode=None:VerboseLevel=Debug:nTrain_Signal=5000:nTrain_Background=5000:SplitMode=Random:SplitSeed=0"
)

# Book the MVA method
mva_args = ""\
   "H:VerbosityLevel=Default:"\
   "NTrees=50:"\
   "BoostType=Grad:"\
   "Shrinkage=0.1:"\
   "!UseBaggedGrad:"\
   "nCuts=200:"\
   "SeparationType=CrossEntropy:"\
   "NNodesMax=5:"\
   "UseNvars=4:"\
   "PruneStrength=7:"\
   "PruneMethod=CostComplexity:"\
   "MaxDepth=2"

#muon events
factory.BookMethod(
    TMVA.Types.kBDT,
    "BDT",
    mva_args
)

factory.BookMethod(
    TMVA.Types.kLikelihood,
    "Likelihood",
    "H:VerbosityLevel=Default:CreateMVAPdfs:TransformOutput"
)
# Train, test and evaluate them all
factory.TrainAllMethods()
factory.TestAllMethods()
factory.EvaluateAllMethods()

out.Close()
