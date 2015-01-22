FLAGS=`root-config --cflags --libs`

plotter: bin/plotter.cc
	g++ $(FLAGS) bin/plotter.cc -o plotter.exe
