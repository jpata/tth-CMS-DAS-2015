#pathToFile = "/hdfs/local/joosep/das2015/"
pathToFile = "./"

#----NNLO------
xsecTT_SL = 107.66
xsecTT_FL = 25.81
xsecTT_FH = 112.33

samples = [
#	("output")
	("TTH125", "TTH125", 184648.0, 433891.09375, 0.1302*0.569),
	("TTJetsFullLept_small", "TTJetsFullLept", 9644590.0, 11684417.0, xsecTT_FL),
	("TTJetsSemiLept_small", "TTJetsSemiLept", 16755422.0, 25370432.0, xsecTT_SL)
]


