#include "FWCore/FWLite/interface/AutoLibraryLoader.h"

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <map>
#include <string>

#include "TSystem.h"
#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TF1.h"
#include "TF2.h"
#include "TGraph.h"
#include "Math/GenVector/LorentzVector.h"
#include "TLorentzVector.h"
#include "TVectorD.h"

#include "PhysicsTools/FWLite/interface/TFileService.h"

#include "FWCore/ParameterSet/interface/ProcessDesc.h"
#include "FWCore/PythonParameterSet/interface/PythonProcessDesc.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "CMSDAS/TTH/interface/slim_tree.hh"

int main(int argc, const char* argv[])
{

	using namespace std;

	gROOT->SetBatch(true);
	gSystem->Load("libFWCoreFWLite");
	gSystem->Load("libDataFormatsFWLite");
	AutoLibraryLoader::enable();

	PythonProcessDesc builder(argv[1]);
	const edm::ParameterSet& in = builder.processDesc()->getProcessPSet()->getParameter<edm::ParameterSet>("fwliteInput");
	const edm::VParameterSet& samples = in.getParameter<edm::VParameterSet>("samples") ;
	const std::string out_fn = in.getParameter<std::string>("outFileName") ;

	const std::string pathToFile(in.getParameter<std::string>("pathToFile"));
	const std::string ordering(in.getParameter<std::string>("ordering"));

	TFile* outfile = new TFile(out_fn.c_str(), "RECREATE");

	for(unsigned int sample = 0 ; sample < samples.size(); sample++) {

		const string currentName = samples[sample].getParameter<std::string>("name");
		const string fn(pathToFile + ordering + currentName + ".root");
		
		TFile* currentFile = new TFile(fn.c_str());

		assert(currentFile != 0);

		TTree* currentTree = (TTree*)(currentFile->Get("tree"));

		Long64_t nentries = currentTree->GetEntries();
		cout << "sample " << currentName << " total entries: " << nentries << endl;

		for (Long64_t entry = 0; entry < nentries ; entry++) {

			if(entry%5000==0) cout << entry << "  (" << float(entry)/float(nentries)*100. << " % completed)" << endl;

			currentTree->GetEntry(entry);

		} // event loop

		currentFile->Close();

	} // samples loop

	outfile->Write("", TObject::kOverwrite);	
	return 0;

}
