#include "FWCore/FWLite/interface/AutoLibraryLoader.h"

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <unordered_map>

#include "TSystem.h"
#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TH2D.h"
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



const double csv_WP_L = 0.244;
const double csv_WP_M = 0.679;
const double csv_WP_T = 0.898;


const double CSV_LOW = 0.0;
const double CSV_HIGH = 1.0;
const double CSV_STEP = 0.01;

class Jet {
public:
	double pt, eta, phi, e, id, csv;

	Jet(double _pt, double _eta, double _phi, double _e, double _id, double _csv) {
		pt = _pt;
		eta = _eta;
		phi = _phi;
		e = _e;
		id = _id;
		csv = _csv;
	}

	Jet(SlimTree& it, int _nj) {
		pt = it.jet__pt[_nj];
		eta = it.jet__eta[_nj];
		phi = it.jet__phi[_nj];
		e = it.jet__energy[_nj];
		id = it.jet__id[_nj];
		csv = it.jet__bd_csv[_nj];
	}

	TLorentzVector get_p4() {
		TLorentzVector r(1,0,0,1);
		r.SetPtEtaPhiE(pt, eta, phi, e);
		return r;
	}
};

class Histograms {
public:
	TH1D* jet_pt;

	//maps jet pdg-id to a TH1D containing the CSV distributions
	std::unordered_map<int, TH1D*> csvs;

	TH1D* failreasons;
	TH1D* njets;

	TH1D* ntags_5j;
	TH1D* ntags_6j;
	TH1D* ntags_6plusj;

	TH2D* csv_scan_1trail;
	TH2D* csv_scan_2trail;

	TH1D* jet1_pt_njets6_ntags3;
	TH1D* jet2_pt_njets6_ntags3;
	TH1D* ht_njets6_ntags3;

	TH1D* mean_csv_njets6_ntags3;
	TH1D* sigma_csv_njets6_ntags3;

	TH1D* mclosest_njets6_ntags3;

	//maps jet index by CSV-descending to a TH1D containing the CSV distributions
	std::unordered_map<int, TH1D*> csv_njets6_ntags3;

	TTree* events;
	std::unordered_map<std::string, double*> event_vars;

	const int csv_ids[8] = {
		0, 1, 2, 3, 4, 5, 21, 99
	};

	void add_branch(const std::string& name) {
		event_vars[name] = new double(0.0);
		events->Branch(name.c_str(), (double*)(event_vars[name.c_str()]), (name + "/D").c_str());
		//std::cout << "created branch " << name << " " << event_vars[name.c_str()] << std::endl;
	}

	Histograms(const std::string sample) {
        //Enable automatic Sumw2 saving 
        TH1::SetDefaultSumw2(true);
		failreasons = new TH1D((sample + "_failreasons").c_str(), "Event cut reasons", 10, 0, 10);
		jet_pt = new TH1D((sample + "_jet_pt").c_str(), "p_t of all jets", 80, 30, 600);
		for (int _csv : csv_ids) {
			csvs[_csv] = new TH1D((sample + "_csv_" + std::to_string(_csv)).c_str(), "CSV", 20, 0, 1);
		}

		njets = new TH1D(
			(sample + "_njets").c_str(), "N_j",
			15, 0, 15
		);

		ntags_5j = new TH1D(
			(sample + "_ntags_5j").c_str(), "N_t (CSVM) for 5 jets",
			6, 0, 6
		);

		ntags_6j = new TH1D(
			(sample + "_ntags_6j").c_str(), "N_t (CSVM) for 6 jets",
			7, 0, 7
		);

		ntags_6plusj = new TH1D(
			(sample + "_ntags_6plusj").c_str(), "N_t (CSVM) for >6 jets",
			12, 0, 12
		);

		csv_scan_1trail = new TH2D(
			(sample + "_csv_scan_1trail").c_str(), "Scan over CSV_l, CSV_h for 6 jets, 3 tags (1 trailing)",
			
			(CSV_HIGH - CSV_LOW) / CSV_STEP,
			CSV_LOW - CSV_STEP/2.0,
			CSV_HIGH - CSV_STEP/2.0,

			(CSV_HIGH - CSV_LOW) / CSV_STEP,
			CSV_LOW - CSV_STEP/2.0,
			CSV_HIGH - CSV_STEP/2.0
		);

		csv_scan_2trail = new TH2D(
			(sample + "_csv_scan_2trail").c_str(), "Scan over CSV_l, CSV_h for 6 jets, 3 tags (2 trailing)",
			
			(CSV_HIGH - CSV_LOW) / CSV_STEP,
			CSV_LOW - CSV_STEP/2.0,
			CSV_HIGH - CSV_STEP/2.0,

			(CSV_HIGH - CSV_LOW) / CSV_STEP,
			CSV_LOW - CSV_STEP/2.0,
			CSV_HIGH - CSV_STEP/2.0
		);


		jet1_pt_njets6_ntags3 = new TH1D(
			(sample + "_jet1_pt_njets6_ntags3").c_str(), "Leading jet p_t for 6 jets, 3 tags (CSVM)",
			60, 30, 600
		);

		jet2_pt_njets6_ntags3 = new TH1D(
			(sample + "_jet2_pt_njets6_ntags3").c_str(), "Leading jet p_t for 6 jets, 3 tags (CSVM)",
			60, 30, 600
		);

		mean_csv_njets6_ntags3 = new TH1D(
			(sample + "_mean_csv_njets6_ntags3").c_str(), "Mean CSV discriminator of jets in event for 6 jets, 3 tags (CSVM)",
			60, 0, 1
		);

		sigma_csv_njets6_ntags3 = new TH1D(
			(sample + "_sigma_csv_njets6_ntags3").c_str(), "Sigma of CSV discriminator of jets in event for 6 jets, 3 tags (CSVM)",
			60, 0, 2
		);

		for (int i=0; i < 6; i++ ) {
			csv_njets6_ntags3[i] = new TH1D(
				(sample + "_csv_" + std::to_string(i) + "_njets6_ntags3").c_str(), "CSV distribution of nth (by CSV) jet for 6 jets, 3 tags (CSVM)",
				60, 0, 1
			);
		}

		ht_njets6_ntags3 = new TH1D(
			(sample + "_ht_njets6_ntags3").c_str(), "H_t of event for 6 jets, 3 tags (CSVM)",
			60, 180, 1000 
		);

		mclosest_njets6_ntags3 = new TH1D(
			(sample + "_mclosest_njets6_ntags3").c_str(), "Mass of closest tagged jet pair for 6 jets, 3 tags (CSVM)",
			60, 180, 1000 
		);

		events = new TTree((sample + "_events").c_str(), "events");

		for (const std::string& b : {
			"jet1_pt", "jet2_pt", "mean_csv", "sigma_csv",
			"csv0", "csv1", "csv2",
			"csv3", "csv4", "csv5",
			"m_closest",
			"ntags",
			"ht"}) {
			add_branch(b);
		}
	}

	void loop_initialize() {
		for (auto& x : event_vars) {
			//std::cout << "II " << x.first << " " << x.second << std::endl;
			*(x.second) = 0.0;
			//std::cout << "IP " << x.first << " " << x.second << std::endl;
		}
	}

	void set_var(const std::string& name, double val) {
		//std::cout << name << " " << event_vars[name] << std::endl;
		assert(event_vars[name] != 0);
		*(event_vars[name]) = val;
	}

	~Histograms() {
		delete jet_pt;
		for (auto it : csvs) {
			delete it.second;
		}
		delete njets;
		delete ntags_5j;
		delete ntags_6j;
		delete ntags_6plusj;

		delete csv_scan_1trail;
		delete csv_scan_2trail;
	}
};

Histograms make_hists(TFile* of, const std::string sample) {
	of->cd();
	//of->mkdir(sample.c_str());
	//of->cd(sample.c_str());
	Histograms hs(sample);
	return hs;
}

double calc_ht(std::vector<Jet>& jets) {
	double ht = 0.0;
	for (auto& j : jets) {
		ht += j.pt;
	}
	return ht;
}

double m_closest_tagged(std::vector<Jet>& jets) {

	TLorentzVector bp1;
	TLorentzVector bp2;
	double bdr = 100.0;

	for (auto& j1 : jets) {
		
		if (j1.csv <= csv_WP_M) {
			continue;
		}

		for (auto& j2 : jets) {
			
			if (j2.csv <= csv_WP_M) {
				continue;
			}

			if (j1.pt != j2.pt) {

				TLorentzVector p1 = j1.get_p4();
				TLorentzVector p2 = j2.get_p4();

				double dr = p1.DeltaR(p2);

				if (dr < bdr) {
					bp1 = p1;
					bp2 = p2;
					bdr = dr;
				}
			}
		}
	}

	// std::cout << " p1 ";
	// bp1.Print();
	// std::cout << " p2 ";
	// bp2.Print();

	TLorentzVector tot = bp1 + bp2;

	//std::cout << " ptot ";
	//tot.Print();

	return tot.M();
}


bool compare_pt (const Jet i, const Jet j) { return (i.pt > j.pt); }
bool compare_csv (const Jet i, const Jet j) { return (i.csv > j.csv); }

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
    
	const unsigned long long firstEvent(in.getParameter<unsigned long long>("firstEvent"));
	const unsigned long long lastEvent(in.getParameter<unsigned long long>("lastEvent"));
    if (firstEvent!=lastEvent) { 
        cout << "processing events " << firstEvent << ":" << lastEvent << endl;
    }
	TFile* outfile = new TFile(out_fn.c_str(), "RECREATE");

	unsigned long long total_entries = 0;
	unsigned long long processed_entries = 0;
	for(unsigned int sample = 0 ; sample < samples.size(); sample++) {

		const string currentName = samples[sample].getParameter<std::string>("name");
		const string nickName = samples[sample].getParameter<std::string>("nickName");
		const string fn(pathToFile + ordering + currentName + ".root");
		const double ngen = samples[sample].getParameter<double>("ngen");
		const double xs = samples[sample].getParameter<double>("xSec");
		
		TFile* currentFile = new TFile(fn.c_str());

		assert(currentFile != 0);

		TTree* currentTree = (TTree*)(currentFile->Get("tree"));
		SlimTree it(currentTree);

		const unsigned long long nentries = currentTree->GetEntries();

		//Calculate the effective number of generated events.
		const double xsweight = xs / ngen;

		cout << "sample " << currentName << " total entries: " << nentries << " xsw " << xsweight << endl;

		it.set_branch_addresses();

		Histograms hs(make_hists(outfile, nickName));

		for (unsigned long long entry = 0; entry < nentries ; entry++) {
			if (firstEvent <= lastEvent && lastEvent > 0 && (total_entries < firstEvent || total_entries > lastEvent)) {
			    total_entries += 1;
				continue;
			}
			total_entries += 1;

			it.loop_initialize();
			hs.loop_initialize();

			if(total_entries%50000==0) cout << "Processed " << total_entries << endl;

			currentTree->GetEntry(entry);
            processed_entries += 1;
			
            int nl = it.n__lep;
            int n_good_mu = 0;
            //int good_muon_index = -1;
            for (int _nl=0; _nl < nl; _nl++) {
                double pt = it.lep__pt[_nl];
                double eta = it.lep__eta[_nl];
                double iso = it.lep__rel_iso[_nl];
                int id = it.lep__id[_nl];
                //std::cout << "_nl " << _nl << pt << " " << eta << " " << iso << " " << id << std::endl;
                if (std::abs(id) == 13 && pt > 26 && std::abs(eta) < 2.4 && iso < 0.12) {
                    n_good_mu += 1;
                    //good_muon_index = nl;
                }
            }
            if (n_good_mu != 1) {
                hs.failreasons->Fill(1); 
                continue;
            }

			//Get the jets from the event
			int nj = it.n__jet;
			std::vector<Jet> jets;
			for (int _nj=0; _nj < nj; _nj++) {
				const Jet jet(it, _nj);

				if (jet.pt > 30 && std::abs(jet.eta) < 2.5) {
					jets.push_back(jet);
				}
			}
            if (jets.size() < 4) {
                hs.failreasons->Fill(2); 
                continue;
            }


			//Fill N_jets
			hs.njets->Fill(jets.size(), xsweight);

			int ntags = 0;

			//Fill histograms for jets before selection
			for(const auto& jet : jets) {
				hs.jet_pt->Fill(jet.pt);

				hs.csvs[std::abs(jet.id)]->Fill(jet.csv, xsweight);

				if (jet.csv > csv_WP_M) {
					ntags += 1;
					//std::cout << "  csv = " << jet.csv << std::endl;
 				}
			}

			//Sort jets by pt descending
			std::sort(jets.begin(), jets.end(), compare_pt);

			if (jets.size() == 5) {
				hs.ntags_5j->Fill(ntags, xsweight);
			}
			else if (jets.size() == 6) {
				hs.ntags_6j->Fill(ntags, xsweight);

				auto count_tags = [&jets](double cut) {
					int ntagged = 0;
					for (auto& j : jets) {
						if (j.csv > cut) {
							ntagged += 1;
						}
					}
					return ntagged;
				};

				for (double csv_low = CSV_LOW; csv_low <= CSV_HIGH; csv_low += CSV_STEP) {
					for (double csv_high = CSV_LOW; csv_high <= CSV_HIGH; csv_high += CSV_STEP) {
						int nlow = count_tags(csv_low); 
						int nhigh = count_tags(csv_high); 

						if (nlow == 4 && nhigh >= 2) {
							hs.csv_scan_2trail->Fill(csv_low, csv_high, xsweight);
						}

						if (nlow == 4 && nhigh >= 3) {
							hs.csv_scan_1trail->Fill(csv_low, csv_high, xsweight);
						}
					}
				}

				hs.set_var("ntags", (double)ntags);

				const double m_closest = m_closest_tagged(jets);

				hs.mclosest_njets6_ntags3->Fill(m_closest);
				hs.set_var("m_closest", m_closest);

				double ht = calc_ht(jets);
				hs.set_var("ht", ht);


				double mean_csv = 0.0;
				for (auto& jet : jets) {
					mean_csv += jet.csv;
				}
				mean_csv = mean_csv / jets.size();
				hs.set_var("mean_csv", mean_csv);


				double sigma_csv = 0.0;
				for (auto& jet : jets) {
					sigma_csv += std::pow((jet.csv - mean_csv), 2);
				}
				sigma_csv = sqrt(sigma_csv);
				hs.set_var("sigma_csv", sigma_csv);

				hs.set_var("jet1_pt", jets[0].pt);
				hs.set_var("jet2_pt", jets[1].pt);

				if (ntags == 3) {
					hs.mean_csv_njets6_ntags3->Fill(mean_csv, xsweight);
					hs.sigma_csv_njets6_ntags3->Fill(sigma_csv, xsweight);

					hs.ht_njets6_ntags3->Fill(ht, xsweight);

					hs.jet1_pt_njets6_ntags3->Fill(jets[0].pt, xsweight);
					hs.jet2_pt_njets6_ntags3->Fill(jets[1].pt, xsweight);

					std::sort(jets.begin(), jets.end(), compare_csv);
					for (unsigned int i=0; i < jets.size(); i++) {
						hs.csv_njets6_ntags3[i]->Fill(jets[i].csv, xsweight);
					}

				} //ntags == 3

				//ensure that the jets are sorted by csv descending
				std::sort(jets.begin(), jets.end(), compare_csv);

				for (unsigned int i=0; i<jets.size(); i++) {
					hs.set_var(("csv" + std::to_string(i)), jets[i].csv);
				}

				hs.events->Fill();

			} //6 jets
			else if (jets.size() > 6) {
				hs.ntags_6plusj->Fill(ntags, xsweight);
			}


		} // event loop
		outfile->Write("", TObject::kOverwrite);
		currentFile->Close();

	} // samples loop

	//outfile->Write("", TObject::kOverwrite);	
	return 0;

}
