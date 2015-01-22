#include "TFile.h"
#include "TH1F.h"
#include <iostream>
#include <assert.h>

using namespace std;

int main(int argc, const char* argv[]) {
    TFile* tf = new TFile("output.root", "READ");
    assert(tf != 0);

    cout << "File loaded" << endl;
    TH1F* h = (TH1F*)(tf->Get("TTH125_csv"));
    assert(h != 0);
    cout << "Histogram " << h->GetName() << " opened" << endl;
    return 0;
}
