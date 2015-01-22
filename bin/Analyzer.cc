
//C++ imports
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <map>
#include <string>

//ROOT imports
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

//FWLite imports
#include "FWCore/FWLite/interface/AutoLibraryLoader.h"

//import the headers to configure via python
#include "FWCore/ParameterSet/interface/ProcessDesc.h"
#include "FWCore/PythonParameterSet/interface/PythonProcessDesc.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

//This header file contains the input TTree structure
#include "CMSDAS/TTH/interface/slim_tree.hh"

int main(int argc, const char* argv[])
{

    using namespace std;

    //Disable pop-up plots
    gROOT->SetBatch(true);

    //Automatically load necessary precompiled libraries via ROOT
    gSystem->Load("libFWCoreFWLite");
    gSystem->Load("libDataFormatsFWLite");
    AutoLibraryLoader::enable();

    //Load the python configuration from the first command line argument
    PythonProcessDesc builder(argv[1]);

    //This is the full configuration
    const edm::ParameterSet& in = builder.processDesc()->getProcessPSet()->getParameter<edm::ParameterSet>("fwliteInput");
    
    //A vector of input samples
    const edm::VParameterSet& samples = in.getParameter<edm::VParameterSet>("samples");

    //The output file name
    const std::string out_fn = in.getParameter<std::string>("outFileName") ;

    //These two will be prepended to the input file name (pathToFile + ordering + sample)
    const std::string pathToFile(in.getParameter<std::string>("pathToFile")); //must be / terminated
    const std::string ordering(in.getParameter<std::string>("ordering")); //can be empty
    
    const unsigned long long firstEvent(in.getParameter<unsigned long long>("firstEvent"));
    const unsigned long long lastEvent(in.getParameter<unsigned long long>("lastEvent"));
    
    unsigned long long total_entries = 0;
    unsigned long long processed_entries = 0;

    //Create the output file. Old output will be deleted if it exists
    TFile* outfile = new TFile(out_fn.c_str(), "RECREATE");

    //Process each sample
    for(unsigned int sample = 0 ; sample < samples.size(); sample++) {

        //Create the sample file name
        const string currentName = samples[sample].getParameter<std::string>("name");
        const string fn(pathToFile + ordering + currentName + ".root");
        
        const double ngen = samples[sample].getParameter<double>("ngen");
        const double xs = samples[sample].getParameter<double>("xSec");
        const double xsweight = xs / ngen;
        
        TFile* currentFile = new TFile(fn.c_str());

        //Asserts are useful to avoid segfaults in case of error
        assert(currentFile != 0);

        TTree* currentTree = (TTree*)(currentFile->Get("tree"));
        assert(currentTree != 0);
       
        //Create the input TTree wrapper
        SlimTree it(currentTree);

        Long64_t nentries = currentTree->GetEntries();
        cout << "sample " << currentName << " total entries: " << nentries << " xsw " << xsweight << endl;
    
        //Attach the input TTree branches 
        it.set_branch_addresses();

        for (Long64_t entry = 0; entry < nentries ; entry++) {
            
            if (firstEvent <= lastEvent && lastEvent > 0 && (total_entries < firstEvent || total_entries > lastEvent)) {
                total_entries += 1;
                continue;
            }
            total_entries += 1;
            processed_entries += 1;
            if(total_entries%50000==0) cout << "Processed " << total_entries << endl;

            //Load one event to memory
            currentTree->GetEntry(entry);

            //Access the event data
            
            //Number of jets in event
            int njets = it.n__jet;

            //A C array containing [0...njets-1] jet transverse momenta
            float* jet_pt = it.jet__pt;
           
            //The PDG-id of the parton matched to the jet
            int* jet_id = it.jet__id;

            for (int nj=0; nj < njets; nj++) {
                cout << "jet " << nj << " pt=" << jet_pt[nj] << " id=" << jet_id[nj] << endl;
            }

        } // event loop

        currentFile->Close();

    } // samples loop

    outfile->Write("", TObject::kOverwrite);    
    return 0;

}
