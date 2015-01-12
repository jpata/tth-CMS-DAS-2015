import ROOT
import time

from TTH.das.samples import samples, pathToFile

of = ROOT.TFile("out.root", "RECREATE")

for sample_name, in samples:
	tf = ROOT.TFile(pathToFile + sample_name + ".root")
	tt = tf.Get("tree")

	print tt.GetEntries()
	csv_hists = {}
	for i in range(4):
		for _id in [0, 1, 2, 3, 4, 5, 21, 99]:
			hn = sample_name + "_csv_" + str(_id) + "_" + str(i)
			csv_hists[(i, _id)] = ROOT.TH1F(hn, hn, 20, 0, 1)
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

		if nev > 200000:
			break
		csvs = ev.jet__bd_csv
		ids = ev.jet__id
		njets = ev.n__jet

		csvs = [csvs[i] for i in range(njets)]
		ids = [ids[i] for i in range(njets)]

		jets = zip(csvs, ids)
		jets.sort(key=lambda x: x[0], reverse=True)

		csvs = [x[0] for x in jets]
		ids = [x[1] for x in jets]

		for i in range(min(4, njets)):
			_id = abs(ids[i])
			csv = csvs[i]
			csv_hists[(i, _id)].Fill(csv)
		nev += 1
	of.Write("", ROOT.TObject.kOverwrite)

for sample_name, in samples:
	for i in range(4):
		s = of.Get(sample_name + "_csv_5_%d" % i).Clone("s")
		b = of.Get(sample_name + "_csv_21_%d" % i).Clone("b")

		for _id in [0, 1, 2, 3, 4, 5]:
			b.Add(of.Get(sample_name + "_csv_%d_%d" % (_id, i)))
		sob = s.Clone(sample_name + "_sob_%d" % i)
		sob.SetDirectory(of)
		sob.Divide(b)
		of.Write("", ROOT.TObject.kOverwrite)

of.Close()
