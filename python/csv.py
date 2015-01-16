import ROOT
ROOT.TH1.SetDefaultSumw2()
import time
import numpy

from TTH.das.samples import samples, pathToFile

of = ROOT.TFile("csv.root", "RECREATE")

csv_WP_L = 0.244
csv_WP_M = 0.679
csv_WP_T = 0.898

for sample_name, nick_name, ntree, ngen, xs in samples:
	tf = ROOT.TFile(pathToFile + sample_name + ".root")
	tt = tf.Get("tree")

	ntree2 = tt.GetEntries()

	ngen_effective = ngen * (ntree2/ntree)
	print "Ngen effective", ngen_effective

	xsweight = xs / ngen_effective
	print xsweight

	of.cd()

	csv_hists = {}
	csv_ntags_hist = ROOT.TH2D(nick_name + "_csv_ntags", nick_name + "_csv_ntags", 60, 0, 1, 10, 0, 10)
	ntags_hist = ROOT.TH1D(nick_name + "_ntags", nick_name + "_ntags", 7, 0, 7)
	ntags_hist_nj5 = ROOT.TH1D(nick_name + "_ntags_nj5", nick_name + "_ntags_nj5", 6, 0, 6)

	ntags_hist_true = ROOT.TH2D(nick_name + "_ntags_true", nick_name + "_ntags_true", 10, 0, 10, 10, 0, 10)
	ntags_hist_true.GetXaxis().SetTitle("tagged true b jets")
	ntags_hist_true.GetYaxis().SetTitle("all true b jets")
	jet_ids = ROOT.TH1D(nick_name + "_jet_ids", nick_name + "_jet_ids", 22, 0, 22)
	csv_scan = ROOT.TH2D(nick_name + "_csv_scan", nick_name + "_csv_scan",
		50, 0.0 - 0.01, 1.0 - 0.01,
		50, 0.0 - 0.01, 1.0 - 0.01
	)

	for _id in [0, 1, 2, 3, 4, 5, 21, 99]:
		hn = nick_name + "_csv_" + str(_id)
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
			csv_hists[(_id)].Fill(csv, xsweight)

		if njets == 6:
			for csv in numpy.arange(0.0, 1.0, 0.0125):
				jets_pass = filter(lambda x: x[0] > csv, jets)
				csv_ntags_hist.Fill(csv, len(jets_pass), xsweight)

		if njets == 5:
			ntags = len(filter(lambda x: x[0] > csv_WP_M, jets))
			ntags_hist_nj5.Fill(ntags, xsweight)

		if njets == 6:
			ntags = len(filter(lambda x: x[0] > csv_WP_M, jets))
			ntags_hist.Fill(ntags, xsweight)

			if ntags == 4:
				#to calculate tagging efficiency (fraction of b-jets that are tagged)
				ntags_hist_true.Fill(
					len(filter(lambda x: abs(x[1]) == 5 and x[0] > csv_WP_M, jets)),
					len(filter(lambda x: abs(x[1]) == 5, jets)),
					xsweight
				)

				#to calculate purity of tagged jets (fraction of tagged jets that are true bs)
				for i in range(len(jets)):
					if jets[i][1] > csv_WP_M:
						jet_ids.Fill(abs(jets[i][1]), xsweight)

			for csv_high in numpy.arange(0.0, 1.0, 0.02):
				for csv_low in numpy.arange(0.0, 1.0, 0.02):
					nlow = len(filter(lambda x: x[0] > csv_low, jets))
					nhigh = len(filter(lambda x: x[0] > csv_high, jets))

					if nhigh >= 2 and nlow >= 4:
						csv_scan.Fill(csv_low, csv_high, xsweight)

		nev += 1
	of.Write("", ROOT.TObject.kOverwrite)
