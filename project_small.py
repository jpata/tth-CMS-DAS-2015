import ROOT, sys

tf = ROOT.TFile(sys.argv[1])

tt = tf.Get("tree")

of = ROOT.TFile(sys.argv[2], "RECREATE")
of.cd()

tt.CloneTree(400000)

of.Write()
of.Close()
