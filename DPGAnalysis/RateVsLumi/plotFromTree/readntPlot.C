#define nt_cxx
#include "nt.h"
#include <TH2.h>
#include <TH1D.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TGraphErrors.h>

#include <iostream>
#include <cmath>
#include <map>

long long LsKey(long long Ls, long long run){
	return (10000000*run + 1*Ls);
}


void nt::Loop()
{
//   In a ROOT session, you can do:
//      root> .L nt.C
//      root> nt t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch

	 TFile *fout = new TFile("rpcRateGraph.root","RECREATE");
	 fout->cd();

	 TGraphErrors *RB1in_InstLumi = new TGraphErrors();
	 RB1in_InstLumi->SetName("RB1in_InstLumi");
	 RB1in_InstLumi->SetTitle("RB1in hits vs Inst. lumi");

      std::map<long long , double> pairLsKeyLumi;
      std::map<long long , double> pairLsKeyRateRB1in;

	int nRun_pre=0;


   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

		  pairLsKeyLumi.insert ( std::pair<long long,double>(LsKey(Ls,nRun),Lumi));

	    std::map<long long, double>::iterator lb = pairLsKeyRateRB1in.find(LsKey(Ls,nRun));
      if(lb != pairLsKeyRateRB1in.end()) {lb->second += RB1inHits;
			}
      else {
				pairLsKeyRateRB1in.insert ( std::pair<long long,double>(LsKey(Ls,nRun),RB1inHits));			
			}

   } // end for jentry<nentries


// filling TGraph

		int jrb1in=0;
  std::map<long long,double>::iterator itLumi = pairLsKeyLumi.begin();
  for (itLumi=pairLsKeyLumi.begin(); itLumi!=pairLsKeyLumi.end(); ++itLumi)
  {

		// cout<<"pairLsLumi first = "<<itLumi->first<<" , second = "<<itLumi->second<<endl;

    std::map<long long,double>::iterator itRateRB1in = pairLsKeyRateRB1in.find(itLumi->first);
    if(itRateRB1in != pairLsKeyRateRB1in.end())
    {
      // if (debug) std::cout << "Found " << itRateRB1in->first << " " << itRateRB1in->second << std::endl;
			if(itRateRB1in->second > 1e8  ) {

				cout<<"Rb1in_istLumi jr = "<<jrb1in<<" ,Ls = "<<itLumi->first<<" ,lumi  = "<<itLumi->second<<" ,rateRB1in = "<<itRateRB1in->second<<endl;
				continue;
			}
      RB1in_InstLumi->SetPoint(jrb1in, itLumi->second, itRateRB1in->second);
				// cout<<"Rb1in_istLumi jr = "<<jrb1in<<" ,Ls = "<<itLumi->first<<" ,lumi  = "<<itLumi->second<<" ,rateRB1in = "<<itRateRB1in->second<<endl;
			// cout<<"jrb1in = "<<jrb1in<<" ,Lumi = "<< itLumi->second<<" RB1in = "<<itRateRB1in->second<<endl;
      // RB1in_toHz->SetPoint(jrb1in, itLumi->second, (itRateRB1in->second)/(myTime*myscale*1.));
      // RB1in_toHzcm2->SetPoint(jrb1in, itLumi->second, (itRateRB1in->second)/(areaRB1in*myTime*myscale*1.));
      jrb1in++;
    }
	} // end loop LsLumi

	/*
	for(auto &it : pairLsKeyRateRB1in){
			 cout<<"pairLsRateRB1in , first = "<<it.first<<" , second = "<<it.second<<endl;
	}
	*/

	fout->cd();
	RB1in_InstLumi->Draw();
	RB1in_InstLumi->Write();


	cout<<"nentries = "<<nentries<<endl;

}

int readntPlot(){

	nt m;
	m.Loop();


	return 0;
}



