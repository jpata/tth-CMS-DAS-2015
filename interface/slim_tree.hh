//python $CMSSW_BASE/src/TTH/TTHNtupleAnalyzer/python/headergen.py $CMSSW_BASE/src/TTH/das/interface/template.hh $CMSSW_BASE/src/TTH/das/python/branches.py 
#ifndef SLIM_TREE
#define SLIM_TREE

#include <TTree.h>
#include <string>
#include <map>
#include <cmath>
#include <iostream>

#define N_MAX 500
#define T_MAX 100
#define MET_S_MAX 20

#define DEF_VAL_FLOAT -9999.0f
#define DEF_VAL_DOUBLE -9999.0d
#define DEF_VAL_INT -9999

//macros to initialize 1D and 2D (square) arrays
//x is the array, n is the size, y is the initialized value
#define SET_ZERO(x,n,y) for(int i=0;i<n;i++) {x[i]=y;}
#define SET_ZERO_2(x,n,m,y) for(int i=0;i<n;i++) { for(int j=0;j<m;j++) { x[i][j]=y; } }

class SlimTree {
public:
	SlimTree(TTree* _tree) { tree = _tree; };
	TTree* tree;
   
        // Helper functions for accessing branches
	template <typename T> 
	T get_address(const std::string name) {
		auto* br = tree->GetBranch(name.c_str());
		if (br==0) {
			std::cerr << "ERROR: get_address SlimTree " << "branch " << name << " does not exist" << std::endl;
			throw std::exception();
		}
		auto* p = br->GetAddress();
		return reinterpret_cast<T>(p);
	}

	int event__id;
	int event__json;
	int event__lumi;
	int event__run;

	float gen_met__phi;
	float gen_met__pt;
	float gen_met__sumet;
	
	//gen-level information from LHE
	float lhe__ht;
	int lhe__n_b;
	int lhe__n_c;
	int lhe__n_e;
	int lhe__n_g;
	float lhe__n_j;
	int lhe__n_l;
	
	int n_sim_b;
	int n_sim_c;

	//MET along with systematic shifts
	float met__phi;
	float met__pt;
	float met__sumet;
	float met__pt__en_down;
	float met__pt__en_up;
	float met__pt__shift[MET_S_MAX];
	float met__px__shift[MET_S_MAX];
	float met__py__shift[MET_S_MAX];
	float met__phi__shift[MET_S_MAX];


	float weight__pu;
	float weight__pu_down;
	float weight__pu_up;
	float weight__trigger;
	float weight__trigger_down;
	float weight__trigger_up;
    
	float weight__genmc;
	int n__match_sim_b;
	int n__match_sim_c;
	int tt_type;
	int n__tr;
	int n__pvi;
	int n__jet;
	int n__lep;
	int n__met_shift;
	float lep__pt[N_MAX];
	float lep__eta[N_MAX];
	float lep__phi[N_MAX];
	float lep__mass[N_MAX];
	float lep__dxy[N_MAX];
	float lep__dz[N_MAX];
	float lep__mva[N_MAX];
	float lep__rel_iso[N_MAX];
	int lep__id[N_MAX];
	int lep__id_bitmask[N_MAX];
	int lep__is_loose[N_MAX];
	int lep__is_medium[N_MAX];
	int lep__is_tight[N_MAX];
	int lep__is_tight_id[N_MAX];
	int lep__charge[N_MAX];
	float trig_lep__pt[N_MAX];
	float trig_jet__pt[N_MAX];
	float trig_lep__eta[N_MAX];
	float trig_jet__eta[N_MAX];
	float trig_lep__phi[N_MAX];
	float trig_jet__phi[N_MAX];
	int trig_lep__pass[N_MAX];
	int trig_jet__pass[N_MAX];
	float jet__bd_csv[N_MAX];
	float jet__bd_csv__up[N_MAX];
	float jet__bd_csv__down[N_MAX];
	float jet__energy[N_MAX];
	float jet__eta[N_MAX];
	float jet__phi[N_MAX];
	float jet__pt[N_MAX];
	float jet__jec_unc[N_MAX];
	int jet__id[N_MAX];
	int jet__match_id[N_MAX];
	float gen_jet__phi[N_MAX];
	float gen_lep__phi[N_MAX];
	float gen_jet__pt[N_MAX];
	float gen_lep__pt[N_MAX];
	float gen_jet__eta[N_MAX];
	float gen_lep__eta[N_MAX];
	int trigger__bits[T_MAX];
	float trigger__prescale[T_MAX];
	int gen_jet__id[N_MAX];
	int gen_jet_parton__id[N_MAX];
	int gen_lep__id[N_MAX];
	int gen_jet__status[N_MAX];
	int gen_jet_parton__status[N_MAX];
	int gen_lep__status[N_MAX];
	float gen_t__eta;
	float gen_t__mass;
	float gen_t__phi;
	float gen_t__pt;
	int gen_t__status;
	float gen_t__b__eta;
	float gen_t__b__mass;
	float gen_t__b__phi;
	float gen_t__b__pt;
	int gen_t__b__status;
	float gen_t__w_d1__eta;
	float gen_t__w_d1__mass;
	float gen_t__w_d1__phi;
	float gen_t__w_d1__pt;
	int gen_t__w_d1__status;
	int gen_t__w_d1__id;
	float gen_t__w_d2__eta;
	float gen_t__w_d2__mass;
	float gen_t__w_d2__phi;
	float gen_t__w_d2__pt;
	int gen_t__w_d2__status;
	int gen_t__w_d2__id;
	float gen_tbar__eta;
	float gen_tbar__mass;
	float gen_tbar__phi;
	float gen_tbar__pt;
	int gen_tbar__status;
	float gen_tbar__b__eta;
	float gen_tbar__b__mass;
	float gen_tbar__b__phi;
	float gen_tbar__b__pt;
	int gen_tbar__b__status;
	float gen_tbar__w_d1__eta;
	float gen_tbar__w_d1__mass;
	float gen_tbar__w_d1__phi;
	float gen_tbar__w_d1__pt;
	int gen_tbar__w_d1__status;
	int gen_tbar__w_d1__id;
	float gen_tbar__w_d2__eta;
	float gen_tbar__w_d2__mass;
	float gen_tbar__w_d2__phi;
	float gen_tbar__w_d2__pt;
	int gen_tbar__w_d2__status;
	int gen_tbar__w_d2__id;
	float gen_b__eta;
	float gen_b__mass;
	float gen_b__phi;
	float gen_b__pt;
	int gen_b__status;
	int gen_b__id;
	float gen_bbar__eta;
	float gen_bbar__mass;
	float gen_bbar__phi;
	float gen_bbar__pt;
	int gen_bbar__status;
	int gen_bbar__id;
	int n__sim_b;
	float sim_b__pt[N_MAX];
	float sim_b__eta[N_MAX];
	float sim_b__phi[N_MAX];
	float sim_b__mass[N_MAX];
    //HEADERGEN_BRANCH_VARIABLES
    //This comment is for automatic header generation, do not remove

    //initializes all branch variables
	void loop_initialize(void) {
		event__id = DEF_VAL_INT;
		event__json = DEF_VAL_INT;
		event__lumi = DEF_VAL_INT;
		event__run = DEF_VAL_INT;
		
		gen_met__phi = DEF_VAL_FLOAT;
		gen_met__pt = DEF_VAL_FLOAT;
		gen_met__sumet = DEF_VAL_FLOAT;

		lhe__ht = DEF_VAL_FLOAT;
		lhe__n_b = DEF_VAL_INT;
		lhe__n_c = DEF_VAL_INT;
		lhe__n_e = DEF_VAL_INT;
		lhe__n_g = DEF_VAL_INT;
		lhe__n_j = DEF_VAL_FLOAT;
		lhe__n_l = DEF_VAL_INT;
		
		n_sim_b = DEF_VAL_INT;
		n_sim_c = DEF_VAL_INT;
		
		met__phi = DEF_VAL_FLOAT;
		met__pt = DEF_VAL_FLOAT;
		met__sumet = DEF_VAL_FLOAT;
		SET_ZERO(met__pt__shift,  MET_S_MAX, DEF_VAL_FLOAT);
		SET_ZERO(met__px__shift,  MET_S_MAX, DEF_VAL_FLOAT);
		SET_ZERO(met__py__shift,  MET_S_MAX, DEF_VAL_FLOAT);
		SET_ZERO(met__phi__shift, MET_S_MAX, DEF_VAL_FLOAT);

		weight__pu = DEF_VAL_FLOAT;
		weight__pu_down = DEF_VAL_FLOAT;
		weight__pu_up = DEF_VAL_FLOAT;
		weight__trigger = DEF_VAL_FLOAT;
		weight__trigger_down = DEF_VAL_FLOAT;
		weight__trigger_up = DEF_VAL_FLOAT;
        
		weight__genmc = DEF_VAL_FLOAT;
		n__match_sim_b = DEF_VAL_INT;
		n__match_sim_c = DEF_VAL_INT;
		tt_type = DEF_VAL_INT;
		n__tr = DEF_VAL_INT;
		n__pvi = DEF_VAL_INT;
		n__jet = DEF_VAL_INT;
		n__lep = DEF_VAL_INT;
		n__met_shift = DEF_VAL_INT;
		SET_ZERO(lep__pt, N_MAX, DEF_VAL_FLOAT);
		SET_ZERO(lep__eta, N_MAX, DEF_VAL_FLOAT);
		SET_ZERO(lep__phi, N_MAX, DEF_VAL_FLOAT);
		SET_ZERO(lep__mass, N_MAX, DEF_VAL_FLOAT);
		SET_ZERO(lep__dxy, N_MAX, DEF_VAL_FLOAT);
		SET_ZERO(lep__dz, N_MAX, DEF_VAL_FLOAT);
		SET_ZERO(lep__mva, N_MAX, DEF_VAL_FLOAT);
		SET_ZERO(lep__rel_iso, N_MAX, DEF_VAL_FLOAT);
		SET_ZERO(lep__id, N_MAX, DEF_VAL_INT);
		SET_ZERO(lep__id_bitmask, N_MAX, DEF_VAL_INT);
		SET_ZERO(lep__is_loose, N_MAX, DEF_VAL_INT);
		SET_ZERO(lep__is_medium, N_MAX, DEF_VAL_INT);
		SET_ZERO(lep__is_tight, N_MAX, DEF_VAL_INT);
		SET_ZERO(lep__is_tight_id, N_MAX, DEF_VAL_INT);
		SET_ZERO(lep__charge, N_MAX, DEF_VAL_INT);
		SET_ZERO(trig_lep__pt, N_MAX, DEF_VAL_FLOAT);
		SET_ZERO(trig_jet__pt, N_MAX, DEF_VAL_FLOAT);
		SET_ZERO(trig_lep__eta, N_MAX, DEF_VAL_FLOAT);
		SET_ZERO(trig_jet__eta, N_MAX, DEF_VAL_FLOAT);
		SET_ZERO(trig_lep__phi, N_MAX, DEF_VAL_FLOAT);
		SET_ZERO(trig_jet__phi, N_MAX, DEF_VAL_FLOAT);
		SET_ZERO(trig_lep__pass, N_MAX, DEF_VAL_INT);
		SET_ZERO(trig_jet__pass, N_MAX, DEF_VAL_INT);
		SET_ZERO(jet__bd_csv, N_MAX, DEF_VAL_FLOAT);
		SET_ZERO(jet__bd_csv__up, N_MAX, DEF_VAL_FLOAT);
		SET_ZERO(jet__bd_csv__down, N_MAX, DEF_VAL_FLOAT);
		SET_ZERO(jet__energy, N_MAX, DEF_VAL_FLOAT);
		SET_ZERO(jet__eta, N_MAX, DEF_VAL_FLOAT);
		SET_ZERO(jet__phi, N_MAX, DEF_VAL_FLOAT);
		SET_ZERO(jet__pt, N_MAX, DEF_VAL_FLOAT);
		SET_ZERO(jet__jec_unc, N_MAX, DEF_VAL_FLOAT);
		SET_ZERO(jet__id, N_MAX, DEF_VAL_INT);
		SET_ZERO(jet__match_id, N_MAX, DEF_VAL_INT);
		SET_ZERO(gen_jet__phi, N_MAX, DEF_VAL_FLOAT);
		SET_ZERO(gen_lep__phi, N_MAX, DEF_VAL_FLOAT);
		SET_ZERO(gen_jet__pt, N_MAX, DEF_VAL_FLOAT);
		SET_ZERO(gen_lep__pt, N_MAX, DEF_VAL_FLOAT);
		SET_ZERO(gen_jet__eta, N_MAX, DEF_VAL_FLOAT);
		SET_ZERO(gen_lep__eta, N_MAX, DEF_VAL_FLOAT);
		SET_ZERO(trigger__bits, T_MAX, DEF_VAL_INT);
		SET_ZERO(trigger__prescale, T_MAX, DEF_VAL_FLOAT);
		SET_ZERO(gen_jet__id, N_MAX, DEF_VAL_INT);
		SET_ZERO(gen_jet_parton__id, N_MAX, DEF_VAL_INT);
		SET_ZERO(gen_lep__id, N_MAX, DEF_VAL_INT);
		SET_ZERO(gen_jet__status, N_MAX, DEF_VAL_INT);
		SET_ZERO(gen_jet_parton__status, N_MAX, DEF_VAL_INT);
		SET_ZERO(gen_lep__status, N_MAX, DEF_VAL_INT);
		gen_t__eta = DEF_VAL_FLOAT;
		gen_t__mass = DEF_VAL_FLOAT;
		gen_t__phi = DEF_VAL_FLOAT;
		gen_t__pt = DEF_VAL_FLOAT;
		gen_t__status = DEF_VAL_INT;
		gen_t__b__eta = DEF_VAL_FLOAT;
		gen_t__b__mass = DEF_VAL_FLOAT;
		gen_t__b__phi = DEF_VAL_FLOAT;
		gen_t__b__pt = DEF_VAL_FLOAT;
		gen_t__b__status = DEF_VAL_INT;
		gen_t__w_d1__eta = DEF_VAL_FLOAT;
		gen_t__w_d1__mass = DEF_VAL_FLOAT;
		gen_t__w_d1__phi = DEF_VAL_FLOAT;
		gen_t__w_d1__pt = DEF_VAL_FLOAT;
		gen_t__w_d1__status = DEF_VAL_INT;
		gen_t__w_d1__id = DEF_VAL_INT;
		gen_t__w_d2__eta = DEF_VAL_FLOAT;
		gen_t__w_d2__mass = DEF_VAL_FLOAT;
		gen_t__w_d2__phi = DEF_VAL_FLOAT;
		gen_t__w_d2__pt = DEF_VAL_FLOAT;
		gen_t__w_d2__status = DEF_VAL_INT;
		gen_t__w_d2__id = DEF_VAL_INT;
		gen_tbar__eta = DEF_VAL_FLOAT;
		gen_tbar__mass = DEF_VAL_FLOAT;
		gen_tbar__phi = DEF_VAL_FLOAT;
		gen_tbar__pt = DEF_VAL_FLOAT;
		gen_tbar__status = DEF_VAL_INT;
		gen_tbar__b__eta = DEF_VAL_FLOAT;
		gen_tbar__b__mass = DEF_VAL_FLOAT;
		gen_tbar__b__phi = DEF_VAL_FLOAT;
		gen_tbar__b__pt = DEF_VAL_FLOAT;
		gen_tbar__b__status = DEF_VAL_INT;
		gen_tbar__w_d1__eta = DEF_VAL_FLOAT;
		gen_tbar__w_d1__mass = DEF_VAL_FLOAT;
		gen_tbar__w_d1__phi = DEF_VAL_FLOAT;
		gen_tbar__w_d1__pt = DEF_VAL_FLOAT;
		gen_tbar__w_d1__status = DEF_VAL_INT;
		gen_tbar__w_d1__id = DEF_VAL_INT;
		gen_tbar__w_d2__eta = DEF_VAL_FLOAT;
		gen_tbar__w_d2__mass = DEF_VAL_FLOAT;
		gen_tbar__w_d2__phi = DEF_VAL_FLOAT;
		gen_tbar__w_d2__pt = DEF_VAL_FLOAT;
		gen_tbar__w_d2__status = DEF_VAL_INT;
		gen_tbar__w_d2__id = DEF_VAL_INT;
		gen_b__eta = DEF_VAL_FLOAT;
		gen_b__mass = DEF_VAL_FLOAT;
		gen_b__phi = DEF_VAL_FLOAT;
		gen_b__pt = DEF_VAL_FLOAT;
		gen_b__status = DEF_VAL_INT;
		gen_b__id = DEF_VAL_INT;
		gen_bbar__eta = DEF_VAL_FLOAT;
		gen_bbar__mass = DEF_VAL_FLOAT;
		gen_bbar__phi = DEF_VAL_FLOAT;
		gen_bbar__pt = DEF_VAL_FLOAT;
		gen_bbar__status = DEF_VAL_INT;
		gen_bbar__id = DEF_VAL_INT;
		n__sim_b = DEF_VAL_INT;
		SET_ZERO(sim_b__pt, N_MAX, DEF_VAL_FLOAT);
		SET_ZERO(sim_b__eta, N_MAX, DEF_VAL_FLOAT);
		SET_ZERO(sim_b__phi, N_MAX, DEF_VAL_FLOAT);
		SET_ZERO(sim_b__mass, N_MAX, DEF_VAL_FLOAT);
        //HEADERGEN_BRANCH_INITIALIZERS
	}

    //makes branches on a new TTree
	void make_branches(void) {
		tree->Branch("event__id", &event__id, "event__id/I");
		tree->Branch("event__json", &event__json, "event__json/I");
		tree->Branch("event__lumi", &event__lumi, "event__lumi/I");
		tree->Branch("event__run", &event__run, "event__run/I");
				
		tree->Branch("lhe__n_b", &lhe__n_b, "lhe__n_b/I");
		tree->Branch("lhe__n_c", &lhe__n_c, "lhe__n_c/I");
		tree->Branch("lhe__n_e", &lhe__n_e, "lhe__n_e/I");
		tree->Branch("lhe__n_g", &lhe__n_g, "lhe__n_g/I");
		tree->Branch("lhe__n_l", &lhe__n_l, "lhe__n_l/I");
		tree->Branch("n_sim_b", &n_sim_b, "n_sim_b/I");
		tree->Branch("n_sim_c", &n_sim_c, "n_sim_c/I");	

		tree->Branch("gen_met__phi", &gen_met__phi, "gen_met__phi/F");
		tree->Branch("gen_met__pt", &gen_met__pt, "gen_met__pt/F");
		tree->Branch("gen_met__sumet", &gen_met__sumet, "gen_met__sumet/F");
		
		tree->Branch("lhe__ht", &lhe__ht, "lhe__ht/F");
		tree->Branch("lhe__n_j", &lhe__n_j, "lhe__n_j/F");
		tree->Branch("met__phi", &met__phi, "met__phi/F");
		tree->Branch("met__pt", &met__pt, "met__pt/F");
		tree->Branch("met__sumet", &met__sumet, "met__sumet/F");
		tree->Branch("met__pt__shift", met__pt__shift, "met__pt__shift[n__met_shift]/F");
		tree->Branch("met__px__shift", met__px__shift, "met__px__shift[n__met_shift]/F");
		tree->Branch("met__py__shift", met__py__shift, "met__py__shift[n__met_shift]/F");
		tree->Branch("met__phi__shift", met__phi__shift, "met__phi__shift[n__met_shift]/F");
		tree->Branch("met__pt__en_down", &met__pt__en_down, "met__pt__en_down/F");
		tree->Branch("met__pt__en_up", &met__pt__en_up, "met__pt__en_up/F");
		tree->Branch("weight__pu", &weight__pu, "weight__pu/F");
		tree->Branch("weight__pu_down", &weight__pu_down, "weight__pu_down/F");
		tree->Branch("weight__pu_up", &weight__pu_up, "weight__pu_up/F");
		tree->Branch("weight__trigger", &weight__trigger, "weight__trigger/F");
		tree->Branch("weight__trigger_down", &weight__trigger_down, "weight__trigger_down/F");
		tree->Branch("weight__trigger_up", &weight__trigger_up, "weight__trigger_up/F");
        
		tree->Branch("weight__genmc", &weight__genmc, "weight__genmc/F");
		tree->Branch("n__match_sim_b", &n__match_sim_b, "n__match_sim_b/I");
		tree->Branch("n__match_sim_c", &n__match_sim_c, "n__match_sim_c/I");
		tree->Branch("tt_type", &tt_type, "tt_type/I");
		tree->Branch("n__tr", &n__tr, "n__tr/I");
		tree->Branch("n__pvi", &n__pvi, "n__pvi/I");
		tree->Branch("n__jet", &n__jet, "n__jet/I");
		tree->Branch("n__lep", &n__lep, "n__lep/I");
		tree->Branch("n__met_shift", &n__met_shift, "n__met_shift/I");
		tree->Branch("lep__pt", lep__pt, "lep__pt[n__lep]/F");
		tree->Branch("lep__eta", lep__eta, "lep__eta[n__lep]/F");
		tree->Branch("lep__phi", lep__phi, "lep__phi[n__lep]/F");
		tree->Branch("lep__mass", lep__mass, "lep__mass[n__lep]/F");
		tree->Branch("lep__dxy", lep__dxy, "lep__dxy[n__lep]/F");
		tree->Branch("lep__dz", lep__dz, "lep__dz[n__lep]/F");
		tree->Branch("lep__mva", lep__mva, "lep__mva[n__lep]/F");
		tree->Branch("lep__rel_iso", lep__rel_iso, "lep__rel_iso[n__lep]/F");
		tree->Branch("lep__id", lep__id, "lep__id[n__lep]/I");
		tree->Branch("lep__id_bitmask", lep__id_bitmask, "lep__id_bitmask[n__lep]/I");
		tree->Branch("lep__is_loose", lep__is_loose, "lep__is_loose[n__lep]/I");
		tree->Branch("lep__is_medium", lep__is_medium, "lep__is_medium[n__lep]/I");
		tree->Branch("lep__is_tight", lep__is_tight, "lep__is_tight[n__lep]/I");
		tree->Branch("lep__is_tight_id", lep__is_tight_id, "lep__is_tight_id[n__lep]/I");
		tree->Branch("lep__charge", lep__charge, "lep__charge[n__lep]/I");
		tree->Branch("trig_lep__pt", trig_lep__pt, "trig_lep__pt[n__lep]/F");
		tree->Branch("trig_jet__pt", trig_jet__pt, "trig_jet__pt[n__jet]/F");
		tree->Branch("trig_lep__eta", trig_lep__eta, "trig_lep__eta[n__lep]/F");
		tree->Branch("trig_jet__eta", trig_jet__eta, "trig_jet__eta[n__jet]/F");
		tree->Branch("trig_lep__phi", trig_lep__phi, "trig_lep__phi[n__lep]/F");
		tree->Branch("trig_jet__phi", trig_jet__phi, "trig_jet__phi[n__jet]/F");
		tree->Branch("trig_lep__pass", trig_lep__pass, "trig_lep__pass[n__lep]/I");
		tree->Branch("trig_jet__pass", trig_jet__pass, "trig_jet__pass[n__jet]/I");
		tree->Branch("jet__bd_csv", jet__bd_csv, "jet__bd_csv[n__jet]/F");
		tree->Branch("jet__bd_csv__up", jet__bd_csv__up, "jet__bd_csv__up[n__jet]/F");
		tree->Branch("jet__bd_csv__down", jet__bd_csv__down, "jet__bd_csv__down[n__jet]/F");
		tree->Branch("jet__energy", jet__energy, "jet__energy[n__jet]/F");
		tree->Branch("jet__eta", jet__eta, "jet__eta[n__jet]/F");
		tree->Branch("jet__phi", jet__phi, "jet__phi[n__jet]/F");
		tree->Branch("jet__pt", jet__pt, "jet__pt[n__jet]/F");
		tree->Branch("jet__jec_unc", jet__jec_unc, "jet__jec_unc[n__jet]/F");
		tree->Branch("jet__id", jet__id, "jet__id[n__jet]/I");
		tree->Branch("jet__match_id", jet__match_id, "jet__match_id[n__jet]/I");
		tree->Branch("gen_jet__phi", gen_jet__phi, "gen_jet__phi[n__jet]/F");
		tree->Branch("gen_lep__phi", gen_lep__phi, "gen_lep__phi[n__lep]/F");
		tree->Branch("gen_jet__pt", gen_jet__pt, "gen_jet__pt[n__jet]/F");
		tree->Branch("gen_lep__pt", gen_lep__pt, "gen_lep__pt[n__lep]/F");
		tree->Branch("gen_jet__eta", gen_jet__eta, "gen_jet__eta[n__jet]/F");
		tree->Branch("gen_lep__eta", gen_lep__eta, "gen_lep__eta[n__lep]/F");
		tree->Branch("trigger__bits", trigger__bits, "trigger__bits[n__tr]/I");
		tree->Branch("trigger__prescale", trigger__prescale, "trigger__prescale[n__tr]/F");
		tree->Branch("gen_jet__id", gen_jet__id, "gen_jet__id[n__jet]/I");
		tree->Branch("gen_jet_parton__id", gen_jet_parton__id, "gen_jet_parton__id[n__jet]/I");
		tree->Branch("gen_lep__id", gen_lep__id, "gen_lep__id[n__lep]/I");
		tree->Branch("gen_jet__status", gen_jet__status, "gen_jet__status[n__jet]/I");
		tree->Branch("gen_jet_parton__status", gen_jet_parton__status, "gen_jet_parton__status[n__jet]/I");
		tree->Branch("gen_lep__status", gen_lep__status, "gen_lep__status[n__lep]/I");
		tree->Branch("gen_t__eta", &gen_t__eta, "gen_t__eta/F");
		tree->Branch("gen_t__mass", &gen_t__mass, "gen_t__mass/F");
		tree->Branch("gen_t__phi", &gen_t__phi, "gen_t__phi/F");
		tree->Branch("gen_t__pt", &gen_t__pt, "gen_t__pt/F");
		tree->Branch("gen_t__status", &gen_t__status, "gen_t__status/I");
		tree->Branch("gen_t__b__eta", &gen_t__b__eta, "gen_t__b__eta/F");
		tree->Branch("gen_t__b__mass", &gen_t__b__mass, "gen_t__b__mass/F");
		tree->Branch("gen_t__b__phi", &gen_t__b__phi, "gen_t__b__phi/F");
		tree->Branch("gen_t__b__pt", &gen_t__b__pt, "gen_t__b__pt/F");
		tree->Branch("gen_t__b__status", &gen_t__b__status, "gen_t__b__status/I");
		tree->Branch("gen_t__w_d1__eta", &gen_t__w_d1__eta, "gen_t__w_d1__eta/F");
		tree->Branch("gen_t__w_d1__mass", &gen_t__w_d1__mass, "gen_t__w_d1__mass/F");
		tree->Branch("gen_t__w_d1__phi", &gen_t__w_d1__phi, "gen_t__w_d1__phi/F");
		tree->Branch("gen_t__w_d1__pt", &gen_t__w_d1__pt, "gen_t__w_d1__pt/F");
		tree->Branch("gen_t__w_d1__status", &gen_t__w_d1__status, "gen_t__w_d1__status/I");
		tree->Branch("gen_t__w_d1__id", &gen_t__w_d1__id, "gen_t__w_d1__id/I");
		tree->Branch("gen_t__w_d2__eta", &gen_t__w_d2__eta, "gen_t__w_d2__eta/F");
		tree->Branch("gen_t__w_d2__mass", &gen_t__w_d2__mass, "gen_t__w_d2__mass/F");
		tree->Branch("gen_t__w_d2__phi", &gen_t__w_d2__phi, "gen_t__w_d2__phi/F");
		tree->Branch("gen_t__w_d2__pt", &gen_t__w_d2__pt, "gen_t__w_d2__pt/F");
		tree->Branch("gen_t__w_d2__status", &gen_t__w_d2__status, "gen_t__w_d2__status/I");
		tree->Branch("gen_t__w_d2__id", &gen_t__w_d2__id, "gen_t__w_d2__id/I");
		tree->Branch("gen_tbar__eta", &gen_tbar__eta, "gen_tbar__eta/F");
		tree->Branch("gen_tbar__mass", &gen_tbar__mass, "gen_tbar__mass/F");
		tree->Branch("gen_tbar__phi", &gen_tbar__phi, "gen_tbar__phi/F");
		tree->Branch("gen_tbar__pt", &gen_tbar__pt, "gen_tbar__pt/F");
		tree->Branch("gen_tbar__status", &gen_tbar__status, "gen_tbar__status/I");
		tree->Branch("gen_tbar__b__eta", &gen_tbar__b__eta, "gen_tbar__b__eta/F");
		tree->Branch("gen_tbar__b__mass", &gen_tbar__b__mass, "gen_tbar__b__mass/F");
		tree->Branch("gen_tbar__b__phi", &gen_tbar__b__phi, "gen_tbar__b__phi/F");
		tree->Branch("gen_tbar__b__pt", &gen_tbar__b__pt, "gen_tbar__b__pt/F");
		tree->Branch("gen_tbar__b__status", &gen_tbar__b__status, "gen_tbar__b__status/I");
		tree->Branch("gen_tbar__w_d1__eta", &gen_tbar__w_d1__eta, "gen_tbar__w_d1__eta/F");
		tree->Branch("gen_tbar__w_d1__mass", &gen_tbar__w_d1__mass, "gen_tbar__w_d1__mass/F");
		tree->Branch("gen_tbar__w_d1__phi", &gen_tbar__w_d1__phi, "gen_tbar__w_d1__phi/F");
		tree->Branch("gen_tbar__w_d1__pt", &gen_tbar__w_d1__pt, "gen_tbar__w_d1__pt/F");
		tree->Branch("gen_tbar__w_d1__status", &gen_tbar__w_d1__status, "gen_tbar__w_d1__status/I");
		tree->Branch("gen_tbar__w_d1__id", &gen_tbar__w_d1__id, "gen_tbar__w_d1__id/I");
		tree->Branch("gen_tbar__w_d2__eta", &gen_tbar__w_d2__eta, "gen_tbar__w_d2__eta/F");
		tree->Branch("gen_tbar__w_d2__mass", &gen_tbar__w_d2__mass, "gen_tbar__w_d2__mass/F");
		tree->Branch("gen_tbar__w_d2__phi", &gen_tbar__w_d2__phi, "gen_tbar__w_d2__phi/F");
		tree->Branch("gen_tbar__w_d2__pt", &gen_tbar__w_d2__pt, "gen_tbar__w_d2__pt/F");
		tree->Branch("gen_tbar__w_d2__status", &gen_tbar__w_d2__status, "gen_tbar__w_d2__status/I");
		tree->Branch("gen_tbar__w_d2__id", &gen_tbar__w_d2__id, "gen_tbar__w_d2__id/I");
		tree->Branch("gen_b__eta", &gen_b__eta, "gen_b__eta/F");
		tree->Branch("gen_b__mass", &gen_b__mass, "gen_b__mass/F");
		tree->Branch("gen_b__phi", &gen_b__phi, "gen_b__phi/F");
		tree->Branch("gen_b__pt", &gen_b__pt, "gen_b__pt/F");
		tree->Branch("gen_b__status", &gen_b__status, "gen_b__status/I");
		tree->Branch("gen_b__id", &gen_b__id, "gen_b__id/I");
		tree->Branch("gen_bbar__eta", &gen_bbar__eta, "gen_bbar__eta/F");
		tree->Branch("gen_bbar__mass", &gen_bbar__mass, "gen_bbar__mass/F");
		tree->Branch("gen_bbar__phi", &gen_bbar__phi, "gen_bbar__phi/F");
		tree->Branch("gen_bbar__pt", &gen_bbar__pt, "gen_bbar__pt/F");
		tree->Branch("gen_bbar__status", &gen_bbar__status, "gen_bbar__status/I");
		tree->Branch("gen_bbar__id", &gen_bbar__id, "gen_bbar__id/I");
		tree->Branch("n__sim_b", &n__sim_b, "n__sim_b/I");
		tree->Branch("sim_b__pt", sim_b__pt, "sim_b__pt[n__sim_b]/F");
		tree->Branch("sim_b__eta", sim_b__eta, "sim_b__eta[n__sim_b]/F");
		tree->Branch("sim_b__phi", sim_b__phi, "sim_b__phi[n__sim_b]/F");
		tree->Branch("sim_b__mass", sim_b__mass, "sim_b__mass[n__sim_b]/F");
        //HEADERGEN_BRANCH_CREATOR
	}

    //connects the branches of an existing TTree to variables
    //used when loading the file
	void set_branch_addresses(void) {

		tree->SetBranchAddress("event__id", &event__id);
		tree->SetBranchAddress("event__json", &event__json);
		tree->SetBranchAddress("event__lumi", &event__lumi);
		tree->SetBranchAddress("event__run", &event__run);
		tree->SetBranchAddress("gen_met__phi", &gen_met__phi);
		tree->SetBranchAddress("gen_met__pt", &gen_met__pt);
		tree->SetBranchAddress("gen_met__sumet", &gen_met__sumet);
		
		tree->SetBranchAddress("lhe__ht", &lhe__ht);
		tree->SetBranchAddress("lhe__n_b", &lhe__n_b);
		tree->SetBranchAddress("lhe__n_c", &lhe__n_c);
		tree->SetBranchAddress("lhe__n_e", &lhe__n_e);
		tree->SetBranchAddress("lhe__n_g", &lhe__n_g);
		tree->SetBranchAddress("lhe__n_j", &lhe__n_j);
		tree->SetBranchAddress("lhe__n_l", &lhe__n_l);
		tree->SetBranchAddress("n_sim_b", &n_sim_b);
		tree->SetBranchAddress("n_sim_c", &n_sim_c);
		
		tree->SetBranchAddress("met__phi", &met__phi);
		tree->SetBranchAddress("met__pt", &met__pt);
		tree->SetBranchAddress("met__sumet", &met__sumet);
		tree->SetBranchAddress("met__pt__en_down", &met__pt__en_down);
		tree->SetBranchAddress("met__pt__en_up", &met__pt__en_up);

		tree->SetBranchAddress("weight__pu", &weight__pu);
		tree->SetBranchAddress("weight__pu_down", &weight__pu_down);
		tree->SetBranchAddress("weight__pu_up", &weight__pu_up);
		tree->SetBranchAddress("weight__trigger", &weight__trigger);
		tree->SetBranchAddress("weight__trigger_down", &weight__trigger_down);
		tree->SetBranchAddress("weight__trigger_up", &weight__trigger_up);
        
		tree->SetBranchAddress("weight__genmc", &weight__genmc);
		tree->SetBranchAddress("n__match_sim_b", &n__match_sim_b);
		tree->SetBranchAddress("n__match_sim_c", &n__match_sim_c);
		tree->SetBranchAddress("tt_type", &tt_type);
		tree->SetBranchAddress("n__tr", &n__tr);
		tree->SetBranchAddress("n__pvi", &n__pvi);
		tree->SetBranchAddress("n__jet", &n__jet);
		tree->SetBranchAddress("n__lep", &n__lep);
		tree->SetBranchAddress("n__met_shift", &n__met_shift);
		tree->SetBranchAddress("lep__pt", lep__pt);
		tree->SetBranchAddress("lep__eta", lep__eta);
		tree->SetBranchAddress("lep__phi", lep__phi);
		tree->SetBranchAddress("lep__mass", lep__mass);
		tree->SetBranchAddress("lep__dxy", lep__dxy);
		tree->SetBranchAddress("lep__dz", lep__dz);
		tree->SetBranchAddress("lep__mva", lep__mva);
		tree->SetBranchAddress("lep__rel_iso", lep__rel_iso);
		tree->SetBranchAddress("lep__id", lep__id);
		tree->SetBranchAddress("lep__id_bitmask", lep__id_bitmask);
		tree->SetBranchAddress("lep__is_loose", lep__is_loose);
		tree->SetBranchAddress("lep__is_medium", lep__is_medium);
		tree->SetBranchAddress("lep__is_tight", lep__is_tight);
		tree->SetBranchAddress("lep__is_tight_id", lep__is_tight_id);
		tree->SetBranchAddress("lep__charge", lep__charge);
		tree->SetBranchAddress("trig_lep__pt", trig_lep__pt);
		tree->SetBranchAddress("trig_jet__pt", trig_jet__pt);
		tree->SetBranchAddress("trig_lep__eta", trig_lep__eta);
		tree->SetBranchAddress("trig_jet__eta", trig_jet__eta);
		tree->SetBranchAddress("trig_lep__phi", trig_lep__phi);
		tree->SetBranchAddress("trig_jet__phi", trig_jet__phi);
		tree->SetBranchAddress("trig_lep__pass", trig_lep__pass);
		tree->SetBranchAddress("trig_jet__pass", trig_jet__pass);
		tree->SetBranchAddress("jet__bd_csv", jet__bd_csv);
		tree->SetBranchAddress("jet__bd_csv__up", jet__bd_csv__up);
		tree->SetBranchAddress("jet__bd_csv__down", jet__bd_csv__down);
		tree->SetBranchAddress("jet__energy", jet__energy);
		tree->SetBranchAddress("jet__eta", jet__eta);
		tree->SetBranchAddress("jet__phi", jet__phi);
		tree->SetBranchAddress("jet__pt", jet__pt);
		tree->SetBranchAddress("jet__jec_unc", jet__jec_unc);
		tree->SetBranchAddress("jet__id", jet__id);
		tree->SetBranchAddress("jet__match_id", jet__match_id);
		tree->SetBranchAddress("gen_jet__phi", gen_jet__phi);
		tree->SetBranchAddress("gen_lep__phi", gen_lep__phi);
		tree->SetBranchAddress("gen_jet__pt", gen_jet__pt);
		tree->SetBranchAddress("gen_lep__pt", gen_lep__pt);
		tree->SetBranchAddress("gen_jet__eta", gen_jet__eta);
		tree->SetBranchAddress("gen_lep__eta", gen_lep__eta);
		tree->SetBranchAddress("trigger__bits", trigger__bits);
		tree->SetBranchAddress("trigger__prescale", trigger__prescale);
		tree->SetBranchAddress("gen_jet__id", gen_jet__id);
		tree->SetBranchAddress("gen_jet_parton__id", gen_jet_parton__id);
		tree->SetBranchAddress("gen_lep__id", gen_lep__id);
		tree->SetBranchAddress("gen_jet__status", gen_jet__status);
		tree->SetBranchAddress("gen_jet_parton__status", gen_jet_parton__status);
		tree->SetBranchAddress("gen_lep__status", gen_lep__status);
		tree->SetBranchAddress("gen_t__eta", &gen_t__eta);
		tree->SetBranchAddress("gen_t__mass", &gen_t__mass);
		tree->SetBranchAddress("gen_t__phi", &gen_t__phi);
		tree->SetBranchAddress("gen_t__pt", &gen_t__pt);
		tree->SetBranchAddress("gen_t__status", &gen_t__status);
		tree->SetBranchAddress("gen_t__b__eta", &gen_t__b__eta);
		tree->SetBranchAddress("gen_t__b__mass", &gen_t__b__mass);
		tree->SetBranchAddress("gen_t__b__phi", &gen_t__b__phi);
		tree->SetBranchAddress("gen_t__b__pt", &gen_t__b__pt);
		tree->SetBranchAddress("gen_t__b__status", &gen_t__b__status);
		tree->SetBranchAddress("gen_t__w_d1__eta", &gen_t__w_d1__eta);
		tree->SetBranchAddress("gen_t__w_d1__mass", &gen_t__w_d1__mass);
		tree->SetBranchAddress("gen_t__w_d1__phi", &gen_t__w_d1__phi);
		tree->SetBranchAddress("gen_t__w_d1__pt", &gen_t__w_d1__pt);
		tree->SetBranchAddress("gen_t__w_d1__status", &gen_t__w_d1__status);
		tree->SetBranchAddress("gen_t__w_d1__id", &gen_t__w_d1__id);
		tree->SetBranchAddress("gen_t__w_d2__eta", &gen_t__w_d2__eta);
		tree->SetBranchAddress("gen_t__w_d2__mass", &gen_t__w_d2__mass);
		tree->SetBranchAddress("gen_t__w_d2__phi", &gen_t__w_d2__phi);
		tree->SetBranchAddress("gen_t__w_d2__pt", &gen_t__w_d2__pt);
		tree->SetBranchAddress("gen_t__w_d2__status", &gen_t__w_d2__status);
		tree->SetBranchAddress("gen_t__w_d2__id", &gen_t__w_d2__id);
		tree->SetBranchAddress("gen_tbar__eta", &gen_tbar__eta);
		tree->SetBranchAddress("gen_tbar__mass", &gen_tbar__mass);
		tree->SetBranchAddress("gen_tbar__phi", &gen_tbar__phi);
		tree->SetBranchAddress("gen_tbar__pt", &gen_tbar__pt);
		tree->SetBranchAddress("gen_tbar__status", &gen_tbar__status);
		tree->SetBranchAddress("gen_tbar__b__eta", &gen_tbar__b__eta);
		tree->SetBranchAddress("gen_tbar__b__mass", &gen_tbar__b__mass);
		tree->SetBranchAddress("gen_tbar__b__phi", &gen_tbar__b__phi);
		tree->SetBranchAddress("gen_tbar__b__pt", &gen_tbar__b__pt);
		tree->SetBranchAddress("gen_tbar__b__status", &gen_tbar__b__status);
		tree->SetBranchAddress("gen_tbar__w_d1__eta", &gen_tbar__w_d1__eta);
		tree->SetBranchAddress("gen_tbar__w_d1__mass", &gen_tbar__w_d1__mass);
		tree->SetBranchAddress("gen_tbar__w_d1__phi", &gen_tbar__w_d1__phi);
		tree->SetBranchAddress("gen_tbar__w_d1__pt", &gen_tbar__w_d1__pt);
		tree->SetBranchAddress("gen_tbar__w_d1__status", &gen_tbar__w_d1__status);
		tree->SetBranchAddress("gen_tbar__w_d1__id", &gen_tbar__w_d1__id);
		tree->SetBranchAddress("gen_tbar__w_d2__eta", &gen_tbar__w_d2__eta);
		tree->SetBranchAddress("gen_tbar__w_d2__mass", &gen_tbar__w_d2__mass);
		tree->SetBranchAddress("gen_tbar__w_d2__phi", &gen_tbar__w_d2__phi);
		tree->SetBranchAddress("gen_tbar__w_d2__pt", &gen_tbar__w_d2__pt);
		tree->SetBranchAddress("gen_tbar__w_d2__status", &gen_tbar__w_d2__status);
		tree->SetBranchAddress("gen_tbar__w_d2__id", &gen_tbar__w_d2__id);
		tree->SetBranchAddress("gen_b__eta", &gen_b__eta);
		tree->SetBranchAddress("gen_b__mass", &gen_b__mass);
		tree->SetBranchAddress("gen_b__phi", &gen_b__phi);
		tree->SetBranchAddress("gen_b__pt", &gen_b__pt);
		tree->SetBranchAddress("gen_b__status", &gen_b__status);
		tree->SetBranchAddress("gen_b__id", &gen_b__id);
		tree->SetBranchAddress("gen_bbar__eta", &gen_bbar__eta);
		tree->SetBranchAddress("gen_bbar__mass", &gen_bbar__mass);
		tree->SetBranchAddress("gen_bbar__phi", &gen_bbar__phi);
		tree->SetBranchAddress("gen_bbar__pt", &gen_bbar__pt);
		tree->SetBranchAddress("gen_bbar__status", &gen_bbar__status);
		tree->SetBranchAddress("gen_bbar__id", &gen_bbar__id);
		tree->SetBranchAddress("n__sim_b", &n__sim_b);
		tree->SetBranchAddress("sim_b__pt", sim_b__pt);
		tree->SetBranchAddress("sim_b__eta", sim_b__eta);
		tree->SetBranchAddress("sim_b__phi", sim_b__phi);
		tree->SetBranchAddress("sim_b__mass", sim_b__mass);
        //HEADERGEN_BRANCH_SETADDRESS

	}
};

#endif
