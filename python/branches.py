#sample branches file for headergen.py
#uses branch classes from headergen
from TTH.TTHNtupleAnalyzer.headergen import *

process += Scalar("weight__genmc", "float"),
process += Scalar("n__match_sim_b", "int"),
process += Scalar("n__match_sim_c", "int"),
process += Scalar("tt_type", "int"),

for t in ["n__tr", "n__pvi", "n__jet", "n__lep", "n__met_shift"]:
    process += [Scalar(t, "int")]

for t in [
    "pt", "eta", "phi", "mass",
    "dxy", "dz",
#    "ch_iso", "ec_iso", "hc_iso",
    "mva",
    #"p_iso", "ph_iso", "puch_iso",
    "rel_iso",
    #"rel_iso2"
    ]:
    full_branch_name = "lep__{0}".format(t)
    process += [
        Dynamic1DArray(full_branch_name, "float", "n__lep", "N_MAX")
    ]

for t in [
    "id", "id_bitmask", "is_loose", "is_medium", "is_tight",
    "is_tight_id", "charge",
    #"type"
    ]:
    full_branch_name = "lep__{0}".format(t)
    process += [
        Dynamic1DArray(full_branch_name, "int", "n__lep", "N_MAX")
    ]

for t in ["pt", "eta", "phi", "pass"]:
    for x in ["lep", "jet"]:
        full_branch_name = "trig_{0}__{1}".format(x, t)
        process += [
            Dynamic1DArray(full_branch_name, "int" if t=="pass" else "float", "n__{0}".format(x), "N_MAX")
        ]

for t in [
    "bd_csv",
#    "ce_e",
#    "ch_e",
#    "el_e",
    "energy",
    "eta",
#    "mass",
#    "mu_e",
#    "ne_e",
#    "nh_e",
#    "ph_e",
    "phi",
#    "pileupJetId",
    "pt",
#    "pt_alt",
    "unc",
#    "vtx3DSig",
#    "vtx3DVal",
#    "vtxMass",
#    "vtxNtracks"
    ]:
    full_branch_name = "jet__{0}".format(t)
    process += [
        Dynamic1DArray(full_branch_name, "float", "n__jet", "N_MAX")
    ]

for t in [
    "id",
    "match_id"
#    "jetId",
#    "pass_pileupJetId",
#    "type"
    ]:
    full_branch_name = "jet__{0}".format(t)
    process += [
        Dynamic1DArray(full_branch_name, "int", "n__jet", "N_MAX")
    ]

for t in [
#    "energy",
    "phi",
    "pt",
    "eta"]:
    for x in [
        "gen_jet",
    #    "gen_jet_parton",
        "gen_lep"
    ]:
        full_branch_name = "{0}__{1}".format(x, t)
        process += [
            Dynamic1DArray(full_branch_name, "float", "n__jet" if "jet" in x
                else "n__lep", "N_MAX")
        ]

for t in [
    "trigger__bits"
    ]:
    process += [
        Dynamic1DArray(t, "int", "n__tr", "T_MAX")
    ]

for t in [
    "trigger__prescale"
    ]:
    process += [
        Dynamic1DArray(t, "float", "n__tr", "T_MAX")
    ]

for t in [
    "id",
    "status",
#    "type"
    ]:
    for x in ["gen_jet", "gen_jet_parton", "gen_lep"]:
        full_branch_name = "{0}__{1}".format(x, t)
        process += [
            Dynamic1DArray(full_branch_name, "int", "n__jet" if "jet" in x
                else "n__lep", "N_MAX")
        ]

# True Top Branches
for t in ["t", "tbar"]:
    for v in [
        ("eta"), ("mass"), ("phi"), ("pt"), ("status"),
        ("b__eta"), ("b__mass"), ("b__phi"), ("b__pt"), ("b__status"),
        ("w_d1__eta"), ("w_d1__mass"), ("w_d1__phi"), ("w_d1__pt"), ("w_d1__status"), ("w_d1__id"),
        ("w_d2__eta"), ("w_d2__mass"), ("w_d2__phi"), ("w_d2__pt"), ("w_d2__status"), ("w_d2__id")
    ]:
        typ = "float"
        if "status" in v or "id" in v:
            typ = "int"
        process += [Scalar("gen_%s__%s" % (t, v), typ)]

for t in ["b", "bbar"]:
    for v in ["eta", "mass", "phi", "pt", "status", "id"]:
        typ = "float"
        if "status" in v or "id" in v:
            typ = "int"
        process += [Scalar("gen_%s__%s" % (t, v), typ)]

process += [Scalar("n__sim_b", "int")]

for t in [
    "pt", "eta", "phi", "mass",
    ]:
    full_branch_name = "sim_b__{0}".format(t)
    process += [
        Dynamic1DArray(full_branch_name, "float", "n__sim_b", "N_MAX")
    ]

