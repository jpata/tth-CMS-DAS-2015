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
#include "DataFormats/FWLite/interface/Event.h"
#include "DataFormats/FWLite/interface/Handle.h"
#include "DataFormats/GeometryVector/interface/VectorUtil.h"
#include "DataFormats/FWLite/interface/LuminosityBlock.h"
#include "DataFormats/FWLite/interface/Run.h"
#include "DataFormats/Luminosity/interface/LumiSummary.h"

#include "CMSDAS/TTH/interface/TTHTree.h"
#include "CMSDAS/TTH/interface/slim_tree.hh"

#include "CMSDAS/TTH/interface/helpers.hh"

#define GENJETDR 0.3
#define VERBOSE false

#define assign(va, vb, la, lb) ot.va
using namespace std;


int main(int argc, const char* argv[])
{

	std::cout << "TreeDumper" << std::endl;
	gROOT->SetBatch(true);

	gSystem->Load("libFWCoreFWLite");
	gSystem->Load("libDataFormatsFWLite");

	AutoLibraryLoader::enable();

	PythonProcessDesc builder(argv[1]);
	const edm::ParameterSet& in = builder.processDesc()->getProcessPSet()->getParameter<edm::ParameterSet>("fwliteInput");
	const edm::VParameterSet& samples = in.getParameter<edm::VParameterSet>("samples") ;
	const std::string out_fn = in.getParameter<std::string>("outFileName") ;

	TFile* outfile = new TFile(out_fn.c_str(), "RECREATE");
	outfile->cd();
	TTree* out_tree = new TTree("tree", "");

	SlimTree ot(out_tree);
	ot.make_branches();

	std::string pathToFile(in.getParameter<std::string>("pathToFile"));
	std::string ordering(in.getParameter<std::string>("ordering"));

	for(unsigned int sample = 0 ; sample < samples.size(); sample++) {

		string currentName = samples[sample].getParameter<std::string>("name");

		const string fn(pathToFile + ordering + currentName + ".root");
		TFile* currentFile = new TFile(fn.c_str());

		assert(currentFile != 0);

		TTree* currentTree = (TTree*)(currentFile->Get("tree"));

		OldTTHTree it(currentTree);

		assert(currentTree != 0);

		TH1F* counter = (TH1F*)(currentFile->Get("CountWithPU"));

		Long64_t nentries = currentTree->GetEntries();
		cout << "sample " << currentName << " total entries: " << nentries << endl;

		for (Long64_t entry = 0; entry < nentries ; entry++) {

			if(entry%5000==0) cout << entry << "  (" << float(entry)/float(nentries)*100. << " % completed)" << endl;

			currentTree->GetEntry(entry);
			ot.loop_initialize();

			ot.n__jet = 0;
			for (int i=0; i < it.naJets; i++) {
				#define ASSIGN(x, y) ot.jet__##x[ot.n__jet] = it.aJet_##y[i];
				#define ASSIGN_GEN(x, y) ot.gen_jet__##x[ot.n__jet] = it.aJet_##y[i];

				ASSIGN(pt, pt);
				ASSIGN(eta, eta);
				ASSIGN(phi, phi);
				ASSIGN(energy, e);
				ASSIGN(bd_csv, csv_nominal);
				ASSIGN(bd_csv__bc_up, csv_upBC);
				ASSIGN(bd_csv__l_up, csv_upL);
				ASSIGN(bd_csv__bc_down, csv_downBC);
				ASSIGN(bd_csv__l_down, csv_downL);
				ASSIGN(id, flavour);
				ASSIGN(jec_unc, JECUnc);

				ASSIGN_GEN(pt, genPt);
				ASSIGN_GEN(eta, genEta);
				ASSIGN_GEN(phi, genPhi);

				#undef ASSIGN
				#undef ASSIGN_GEN

				ot.n__jet += 1;
			}

			for (int i=0; i < it.nhJets; i++) {
				#define ASSIGN(x, y) ot.jet__##x[ot.n__jet] = it.hJet_##y[i];
				#define ASSIGN_GEN(x, y) ot.gen_jet__##x[ot.n__jet] = it.hJet_##y[i];

				ASSIGN(pt, pt);
				ASSIGN(eta, eta);
				ASSIGN(phi, phi);
				ASSIGN(energy, e);
				ASSIGN(bd_csv, csv_nominal);
				ASSIGN(bd_csv__bc_up, csv_upBC);
				ASSIGN(bd_csv__l_up, csv_upL);
				ASSIGN(bd_csv__bc_down, csv_downBC);
				ASSIGN(bd_csv__l_down, csv_downL);
				ASSIGN(id, flavour);
				ASSIGN(jec_unc, JECUnc);

				ASSIGN_GEN(pt, genPt);
				ASSIGN_GEN(eta, genEta);
				ASSIGN_GEN(phi, genPhi);

				#undef ASSIGN
				#undef ASSIGN_GEN

				ot.n__jet += 1;
			}

			ot.n__lep = 0;
			for (int i=0; i < it.nvlep; i++) {
				#define ASSIGN(x, y) ot.lep__##x[ot.n__lep] = it.vLepton_##y[i];
				#define ASSIGN_GEN(x, y) ot.gen_lep__##x[ot.n__lep] = it.vLepton_##y[i];

				ASSIGN(pt, pt);
				ASSIGN(eta, eta);
				ASSIGN(phi, phi);
				ASSIGN(mass, mass);

				ASSIGN_GEN(pt, genPt);
				ASSIGN_GEN(eta, genEta);
				ASSIGN_GEN(phi, genPhi);

				ASSIGN(dxy, dxy);
				ASSIGN(dz, dz);
				ASSIGN(rel_iso, pfCombRelIso);
				ASSIGN(id, type);
				#undef ASSIGN
				#undef ASSIGN_GEN
				ot.n__lep += 1;
			}

			for (int i=0; i < it.nalep; i++) {
				#define ASSIGN(x, y) ot.lep__##x[ot.n__lep] = it.aLepton_##y[i];
				#define ASSIGN_GEN(x, y) ot.gen_lep__##x[ot.n__lep] = it.aLepton_##y[i];

				ASSIGN(pt, pt);
				ASSIGN(eta, eta);
				ASSIGN(phi, phi);
				ASSIGN(mass, mass);

				ASSIGN_GEN(pt, genPt);
				ASSIGN_GEN(eta, genEta);
				ASSIGN_GEN(phi, genPhi);

				ASSIGN(dxy, dxy);
				ASSIGN(dz, dz);
				ASSIGN(rel_iso, pfCombRelIso);
				ASSIGN(id, type);

				#undef ASSIGN
				#undef ASSIGN_GEN

				ot.n__lep += 1;
			}

			#define ASSIGN(x, y) ot.gen_##x = it.gen##y;
			ASSIGN(b__pt,	B_pt);
			ASSIGN(b__mass,	B_mass);
			ASSIGN(b__eta,	B_eta);
			ASSIGN(b__phi, 	B_phi);

			ASSIGN(bbar__pt,	Bbar_pt);
			ASSIGN(bbar__mass,	Bbar_mass);
			ASSIGN(bbar__eta,	Bbar_eta);
			ASSIGN(bbar__phi, 	Bbar_phi);
			
			ASSIGN(t__b__pt,	Top_bpt);
			ASSIGN(t__b__eta,	Top_beta);
			ASSIGN(t__b__phi,	Top_bphi);
			ASSIGN(t__b__mass,	Top_bmass);

			ASSIGN(t__w_d1__pt,		Top_wdau1pt);
			ASSIGN(t__w_d1__eta,	Top_wdau1eta);
			ASSIGN(t__w_d1__phi,	Top_wdau1phi);
			ASSIGN(t__w_d1__mass,	Top_wdau1mass);
			ASSIGN(t__w_d1__id,		Top_wdau1id);

			ASSIGN(t__w_d2__pt,		Top_wdau2pt);
			ASSIGN(t__w_d2__eta,	Top_wdau2eta);
			ASSIGN(t__w_d2__phi,	Top_wdau2phi);
			ASSIGN(t__w_d2__mass,	Top_wdau2mass);
			ASSIGN(t__w_d2__id,		Top_wdau2id);

			ASSIGN(tbar__b__pt,		Tbar_bpt);
			ASSIGN(tbar__b__eta,	Tbar_beta);
			ASSIGN(tbar__b__phi,	Tbar_bphi);
			ASSIGN(tbar__b__mass,	Tbar_bmass);

			ASSIGN(tbar__w_d1__pt,		Top_wdau1pt);
			ASSIGN(tbar__w_d1__eta,		Top_wdau1eta);
			ASSIGN(tbar__w_d1__phi,		Top_wdau1phi);
			ASSIGN(tbar__w_d1__mass,	Top_wdau1mass);
			ASSIGN(tbar__w_d1__id,		Top_wdau1id);

			ASSIGN(tbar__w_d2__pt,		Top_wdau2pt);
			ASSIGN(tbar__w_d2__eta,		Top_wdau2eta);
			ASSIGN(tbar__w_d2__phi,		Top_wdau2phi);
			ASSIGN(tbar__w_d2__mass,	Top_wdau2mass);
			ASSIGN(tbar__w_d2__id,		Top_wdau2id);
			#undef ASSIGN

			//p4 of the b(bbar) from the top(anti-top) decay
			TLorentzVector topBLV(1, 0, 0, 1);
			TLorentzVector atopBLV(1, 0, 0, 1);

			//p4 of the c(cbar) from the top(anti-top)->W hadronic decay
			TLorentzVector topCLV(1, 0, 0, 1);
			TLorentzVector atopCLV(1, 0, 0, 1);


			topBLV.SetPtEtaPhiM(ot.gen_t__b__pt, ot.gen_t__b__eta, ot.gen_t__b__phi, ot.gen_t__b__mass);
			atopBLV.SetPtEtaPhiM(ot.gen_tbar__b__pt, ot.gen_tbar__b__eta, ot.gen_tbar__b__phi, ot.gen_tbar__b__mass);

			if (std::abs(ot.gen_t__w_d1__id) == 4) {
				topCLV.SetPtEtaPhiM(
					ot.gen_t__w_d1__pt,
					ot.gen_t__w_d1__eta,
					ot.gen_t__w_d1__phi,
					ot.gen_t__w_d1__mass
				);
			} else if (std::abs(ot.gen_t__w_d2__id) == 4) {
				topCLV.SetPtEtaPhiM(
					ot.gen_t__w_d2__pt,
					ot.gen_t__w_d2__eta,
					ot.gen_t__w_d2__phi,
					ot.gen_t__w_d2__mass
				);
			}

			if (std::abs(ot.gen_tbar__w_d1__id) == 4) {
				atopCLV.SetPtEtaPhiM(
					ot.gen_tbar__w_d1__pt,
					ot.gen_tbar__w_d1__eta,
					ot.gen_tbar__w_d1__phi,
					ot.gen_tbar__w_d1__mass
				);
			} else if (std::abs(ot.gen_tbar__w_d2__id) == 4) {
				atopCLV.SetPtEtaPhiM(
					ot.gen_tbar__w_d2__pt,
					ot.gen_tbar__w_d2__eta,
					ot.gen_tbar__w_d2__phi,
					ot.gen_tbar__w_d2__mass
				);
			}

			ot.n__match_sim_b = 0;
			ot.n__match_sim_c = 0;
			 // now find out how many matched b's we have...
			for(int hj = 0; hj < ot.n__jet; hj++){
				TLorentzVector hJLV(1,0,0,1);

				if(ot.gen_jet__pt[hj]>20) {
					hJLV.SetPtEtaPhiM(
						ot.gen_jet__pt[hj],
						ot.gen_jet__eta[hj],
						ot.gen_jet__phi[hj],
						0.0
					);
				}
				
				// if jet is within acceptance...
				if( hJLV.Pt() > 20 && TMath::Abs(hJLV.Eta()) < 5) {

					if (std::abs(ot.jet__id[hj]) == 5) {
						if(  topBLV.Pt() > 10 && topBLV.DeltaR(hJLV) < 0.5 ) continue;
						if(atopBLV.Pt() > 10 && atopBLV.DeltaR(hJLV) < 0.5 ) continue;
						ot.n__match_sim_b++;
					}
					else if (std::abs(ot.jet__id[hj]) == 4) {
						if(  topCLV.Pt() > 10 && topCLV.DeltaR(hJLV) < 0.5 ) continue;
						if(atopCLV.Pt() > 10 && atopCLV.DeltaR(hJLV) < 0.5 ) continue;
						ot.n__match_sim_c++;
					}
				}
			}

			for (int i=0; i < it.nSimBs; i++) {
				#define ASSIGN(x, y) ot.sim_b__##x[i] = it.SimBs_##y[i];
				ASSIGN(pt, pt);
				ASSIGN(eta, eta);
				ASSIGN(phi, phi);
				ASSIGN(mass, mass);
				#undef ASSIGN
			}
			ot.n__sim_b = it.nSimBs;
			
			if (ot.n__sim_b > 2 && ot.n__match_sim_b >= 2) {
				ot.tt_type = TTbarType::TT_BB;
			}
			else if (ot.n__sim_b > 2 && ot.n__match_sim_b < 2) {
				ot.tt_type = TTbarType::TT_BJ;
			}
			else if (ot.n__sim_b == 2 && ot.n__match_sim_c > 0) {
				ot.tt_type = TTbarType::TT_CC;
			}
			else if (ot.n__sim_b == 2 && ot.n__match_sim_c == 0) {
				ot.tt_type = TTbarType::TT_JJ;
			} else {
				ot.tt_type = TTbarType::TT_UNKNOWN;
			}
			ot.event__id = it.EVENT_event;
			ot.event__run = it.EVENT_run;
			ot.event__lumi = it.EVENT_lumi;

			ot.weight__genmc = counter->GetBinContent(1);
			ot.tree->Fill();

		} // event loop

		cout << "Output tree has " << ot.tree->GetEntries() << " entries";
		currentFile->Close();

	} // samples loop
	outfile->Write("", TObject::kOverwrite);	
	return 0;

}
