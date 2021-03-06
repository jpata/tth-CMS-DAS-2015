//python $CMSSW_BASE/src/TTH/TTHNtupleAnalyzer/python/headergen.py $CMSSW_BASE/src/CMSDAS/TTH/interface/template.hh $CMSSW_BASE/src/CMSDAS/TTH/interface/slim_tree.hh $CMSSW_BASE/src/CMSDAS/TTH/python/branches.py
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
        
        //HEADERGEN_BRANCH_SETADDRESS

	}
};

#endif
