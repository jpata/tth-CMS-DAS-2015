FLAGS=`root-config --cflags --libs`

plotter: bin/plotter.cc
	g++ $(FLAGS) bin/plotter.cc -o plotter.exe

roofit: bin/roofit.cc
	g++ $(FLAGS) -I/cvmfs/cms.cern.ch/slc6_amd64_gcc481/lcg/roofit/5.34.18/include/ -L/cvmfs/cms.cern.ch/slc6_amd64_gcc481/lcg/roofit/5.34.18/lib/ -lRooFitCore bin/roofit.cc -o roofit.exe
