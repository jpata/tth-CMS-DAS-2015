import ROOT
import time
import numpy

from TTH.das.samples import samples, pathToFile

of = ROOT.TFile("out.root", "RECREATE")

csv_WP_L = 0.244
csv_WP_M = 0.679
csv_WP_T = 0.898

for sample_name, in samples:
	tf = ROOT.TFile(pathToFile + sample_name + ".root")
	tt = tf.Get("tree")

	print tt.GetEntries()
	csv_hists = {}
	csv_ntags_hist = ROOT.TH2D(sample_name + "_csv_ntags", sample_name + "_csv_ntags", 60, 0, 1, 10, 0, 10)
	csv_ntags_hist.SetDirectory(of)

	ntags_hist = ROOT.TH1D(sample_name + "_ntags", sample_name + "_ntags", 10, 0, 10)
	ntags_hist.SetDirectory(of)

	ntags_hist_true = ROOT.TH1D(sample_name + "_ntags_true", sample_name + "_ntags_true", 10, 0, 10)
	ntags_hist_true.SetDirectory(of)

	for _id in [0, 1, 2, 3, 4, 5, 21, 99]:
		hn = sample_name + "_csv_" + str(_id)
		csv_hists[(_id)] = ROOT.TH1F(hn, hn, 80, 0, 1)
	for h in csv_hists.values():
		h.SetDirectory(of)
		h.Sumw2()
	nev = 0
	t0 = time.time()
	for ev in tt:

		if nev % 100000 == 0:
			t1 = time.time()
			dt = t1 - t0
			t0 = t1
			print nev, dt

		if nev > 400000:
			break

		njets = ev.n__jet
		csvs = [ev.jet__bd_csv[i] for i in range(njets)]
		ids = [ev.jet__id[i] for i in range(njets)]
		pts = [ev.jet__pt[i] for i in range(njets)]
		etas = [ev.jet__eta[i] for i in range(njets)]
		phis = [ev.jet__phi[i] for i in range(njets)]

		jets = zip(csvs, ids, pts, etas, phis)
		jets.sort(key=lambda x: x[0], reverse=True)

		jets = filter(lambda x: x[2] > 30 and abs(x[3]) < 2.5, jets)

		for i in range(len(jets)):
			_id = abs(jets[i][1])
			csv = jets[i][0]
			csv_hists[(_id)].Fill(csv)

		if njets == 6:
			for csv in numpy.arange(0.0, 1.0, 0.0125):
				jets_pass = filter(lambda x: x[0] > csv, jets)
				csv_ntags_hist.Fill(csv, len(jets_pass))

		if njets == 6:
			ntags = len(filter(lambda x: x[0] > csv_WP_M, jets))
			ntags_hist.Fill(ntags)

			if ntags == 4:
				ntags_hist_true.Fill(len(filter(lambda x: abs(x[1]) == 5, jets)))

		nev += 1
	of.Write("", ROOT.TObject.kOverwrite)
