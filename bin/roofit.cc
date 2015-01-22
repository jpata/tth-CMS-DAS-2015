#include "TFile.h"
#include "TH1F.h"
#include "TROOT.h"
#include "TSystem.h"
#include "THStack.h"
#include <iostream>
#include <assert.h>

#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooDataHist.h"
#include "RooHistPdf.h"
#include "RooAddPdf.h"
#include "RooGaussian.h"
#include "TCanvas.h"
#include "RooPlot.h"
#include "TAxis.h"

using namespace RooFit;

using namespace std;

const double lumi = 19500;

int main(int argc, const char* argv[]) {
    gROOT->SetBatch(true); 
    TFile* tf = new TFile("output.root", "READ");
    assert(tf != 0);

    cout << "File loaded" << endl;
    TH1F* h_tt_bb = (TH1F*)(tf->Get("TTJetsSemiLept_mean_csv_njets6_ntags3"));
    //TH1F* h_tt_bj = (TH1F*)(tf->Get("TTH125_csv"));
    TH1F* h_tt_jj = (TH1F*)(tf->Get("TTJetsFullLept_mean_csv_njets6_ntags3"));

    h_tt_jj->Scale(lumi);
    h_tt_bb->Scale(lumi);

    //Load all data
    TH1F* h_data = (TH1F*)(tf->Get("SingleMuRun2012A1_mean_csv_njets6_ntags3"));
    for (const char* s : {
        "SingleMuRun2012A2_mean_csv_njets6_ntags3",
        "SingleMuRun2012B_mean_csv_njets6_ntags3",
    }) {
        h_data->Add(
            (TH1F*)(tf->Get(s))
        );
    }
    assert(h_tt_bb != 0);
    assert(h_tt_jj != 0);
    assert(h_data != 0);

    RooRealVar discriminator("discriminator", "Discriminator between tt+bb/tt+jj", 0, 1);
    RooRealVar bb_jj_ratio("pp_jj_ratio", "Ratio between tt + bb / tt + jj", 0, 1);

    RooDataHist dh_tt_bb("tt_bb", "tt+bb", RooArgList(discriminator), h_tt_bb);
    RooDataHist dh_tt_jj("tt_jj", "tt+jj", RooArgList(discriminator), h_tt_jj);
    RooDataHist dh_data("data", "data", RooArgList(discriminator), h_data);

    RooHistPdf pdf_tt_bb("tt_bb_pdf", "tt+bb PDF", RooArgSet(discriminator), dh_tt_bb);
    RooHistPdf pdf_tt_jj("tt_jj_pdf", "tt+jj PDF", RooArgSet(discriminator), dh_tt_jj);

    //https://root.cern.ch/root/html/RooAddPdf.html
    RooAddPdf pdf_total("total_pdf", "Total PDF", pdf_tt_bb, pdf_tt_jj, bb_jj_ratio);
    
    pdf_total.fitTo(dh_data, RooFit::Save(true));

    cout << "fitted value " << bb_jj_ratio.getVal() << endl;

    TCanvas* c = new TCanvas("c", "c");
    THStack* st = new THStack();
    h_tt_bb->SetFillColor(kRed);
    h_tt_jj->SetFillColor(kBlue);
    h_tt_bb->Scale(bb_jj_ratio.getVal()); 
    h_tt_jj->Scale(1.0 - bb_jj_ratio.getVal()); 
    st->Add(h_tt_bb);
    st->Add(h_tt_jj);
    st->Draw();
    st->Draw("H SAME");
    h_data->SetMarkerStyle(kDot);
    h_data->SetMarkerColor(kBlack);
    h_data->Draw("P SAME");
    c->SaveAs("fitted.png");
    return 0;
}
