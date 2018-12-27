#define nt_cxx
#include "nt.h"
#include <TH2.h>
#include <TH1D.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TGraphErrors.h>

//#include <iostream>
//#include <cmath>
#include <map>

long long LsKey(long long Ls, long long run){
  return (10000000*run + 1*Ls);
}

void nt::Loop()
{
  TFile *fout = new TFile("rpcRateGraph.root","RECREATE");
  fout->cd();

  TGraphErrors *RB1in_InstLumi = new TGraphErrors();
  RB1in_InstLumi->SetName("RB1in_InstLumi");
  RB1in_InstLumi->SetTitle("RB1in rate [Hz/cm^{2}] vs Inst. lumi");

  TGraphErrors *RB1out_InstLumi = new TGraphErrors();
  RB1out_InstLumi->SetName("RB1out_InstLumi");
  RB1out_InstLumi->SetTitle("RB1out rate [Hz/cm^{2}] vs Inst. lumi");

  TGraphErrors *RB2in_InstLumi = new TGraphErrors();
  RB2in_InstLumi->SetName("RB2in_InstLumi");
  RB2in_InstLumi->SetTitle("RB2in rate [Hz/cm^{2}] vs Inst. lumi");

  TGraphErrors *RB2out_InstLumi = new TGraphErrors();
  RB2out_InstLumi->SetName("RB2out_InstLumi");
  RB2out_InstLumi->SetTitle("RB2out rate [Hz/cm^{2}] vs Inst. lumi");

  TGraphErrors *RB3_InstLumi = new TGraphErrors();
  RB3_InstLumi->SetName("RB3_InstLumi");
  RB3_InstLumi->SetTitle("RB3 rate [Hz/cm^{2}] vs Inst. lumi");

  TGraphErrors *RB4_InstLumi = new TGraphErrors();
  RB4_InstLumi->SetName("RB4_InstLumi");
  RB4_InstLumi->SetTitle("RB4 rate [Hz/cm^{2}] vs Inst. lumi");

  TGraphErrors *Wp1_InstLumi = new TGraphErrors();
  Wp1_InstLumi->SetName("Wp1_InstLumi");
  Wp1_InstLumi->SetTitle("Wp1 rate [Hz/cm^{2}] vs Inst. lumi");

  TGraphErrors *Wp2_InstLumi = new TGraphErrors();
  Wp2_InstLumi->SetName("Wp2_InstLumi");
  Wp2_InstLumi->SetTitle("Wp2 rate [Hz/cm^{2}] vs Inst. lumi");

  TGraphErrors *Wm1_InstLumi = new TGraphErrors();
  Wm1_InstLumi->SetName("Wm1_InstLumi");
  Wm1_InstLumi->SetTitle("Wm1 rate [Hz/cm^{2}] vs Inst. lumi");

  TGraphErrors *Wm2_InstLumi = new TGraphErrors();
  Wm2_InstLumi->SetName("Wm2_InstLumi");
  Wm2_InstLumi->SetTitle("Wm2 rate [Hz/cm^{2}] vs Inst. lumi");

  TGraphErrors *W0_InstLumi = new TGraphErrors();
  W0_InstLumi->SetName("W0_InstLumi");
  W0_InstLumi->SetTitle("W0 rate [Hz/cm^{2}] vs Inst. lumi");

  TGraphErrors *B_InstLumi = new TGraphErrors();
  B_InstLumi->SetName("B_InstLumi");
  B_InstLumi->SetTitle("Barrel rate [Hz/cm^{2}] vs Inst. lumi");

  TGraphErrors *REp1_InstLumi = new TGraphErrors();
  REp1_InstLumi->SetName("REp1_InstLumi");
  REp1_InstLumi->SetTitle("REp1 rate [Hz/cm^{2}] vs Inst. lumi");

  TGraphErrors *REp2_InstLumi = new TGraphErrors();
  REp2_InstLumi->SetName("REp2_InstLumi");
  REp2_InstLumi->SetTitle("REp2 rate [Hz/cm^{2}] vs Inst. lumi");

  TGraphErrors *REp3_InstLumi = new TGraphErrors();
  REp3_InstLumi->SetName("REp3_InstLumi");
  REp3_InstLumi->SetTitle("REp3 rate [Hz/cm^{2}] vs Inst. lumi");

  TGraphErrors *REp4_InstLumi = new TGraphErrors();
  REp4_InstLumi->SetName("REp4_InstLumi");
  REp4_InstLumi->SetTitle("REp4 rate [Hz/cm^{2}] vs Inst. lumi");

  TGraphErrors *REp_InstLumi = new TGraphErrors();
  REp_InstLumi->SetName("REp_InstLumi");
  REp_InstLumi->SetTitle("REp rate [Hz/cm^{2}] vs Inst. lumi");

  TGraphErrors *REm1_InstLumi = new TGraphErrors();
  REm1_InstLumi->SetName("REm1_InstLumi");
  REm1_InstLumi->SetTitle("REm1 rate [Hz/cm^{2}] vs Inst. lumi");

  TGraphErrors *REm2_InstLumi = new TGraphErrors();
  REm2_InstLumi->SetName("REm2_InstLumi");
  REm2_InstLumi->SetTitle("REm2 rate [Hz/cm^{2}] vs Inst. lumi");

  TGraphErrors *REm3_InstLumi = new TGraphErrors();
  REm3_InstLumi->SetName("REm3_InstLumi");
  REm3_InstLumi->SetTitle("REm3 rate [Hz/cm^{2}] vs Inst. lumi");

  TGraphErrors *REm4_InstLumi = new TGraphErrors();
  REm4_InstLumi->SetName("REm4_InstLumi");
  REm4_InstLumi->SetTitle("REm4 rate [Hz/cm^{2}] vs Inst. lumi");

  TGraphErrors *REm_InstLumi = new TGraphErrors();
  REm_InstLumi->SetName("REm_InstLumi");
  REm_InstLumi->SetTitle("REm rate [Hz/cm^{2}] vs Inst. lumi");

  TH2F *hRB1in_InstLumi = new TH2F("hRB1in_InstLumi", "hRB1in_InstLumi", 1400, 6, 20, 1000, 0., 10.);
  TH2F *hRB1out_InstLumi = new TH2F("hRB1out_InstLumi", "hRB1out_InstLumi", 1400, 6, 20, 1000, 0., 10.);
  TH2F *hRB2in_InstLumi = new TH2F("hRB2in_InstLumi", "hRB2in_InstLumi", 1400, 6, 20, 1000, 0., 10.);
  TH2F *hRB2out_InstLumi = new TH2F("hRB2out_InstLumi", "hRB2out_InstLumi", 1400, 6, 20, 1000, 0., 10.);
  TH2F *hRB3_InstLumi = new TH2F("hRB3_InstLumi", "hRB3_InstLumi", 1400, 6, 20, 1000, 0., 10.);
  TH2F *hRB4_InstLumi = new TH2F("hRB4_InstLumi", "hRB4_InstLumi", 1400, 6, 20, 1000, 0., 10.);

  TH2F *hWp1_InstLumi = new TH2F("hWp1_InstLumi", "hWp1_InstLumi", 1400, 6, 20, 1000, 0., 10.);
  TH2F *hWp2_InstLumi = new TH2F("hWp2_InstLumi", "hWp2_InstLumi", 1400, 6, 20, 1000, 0., 10.);
  TH2F *hWm1_InstLumi = new TH2F("hWm1_InstLumi", "hWm1_InstLumi", 1400, 6, 20, 1000, 0., 10.);
  TH2F *hWm2_InstLumi = new TH2F("hWm2_InstLumi", "hWm2_InstLumi", 1400, 6, 20, 1000, 0., 10.);
  TH2F *hW0_InstLumi = new TH2F("hW0_InstLumi", "hW0_InstLumi", 1400, 6, 20, 1000, 0., 10.);

  TH2F *hB_InstLumi = new TH2F("hB_InstLumi", "hB_InstLumi", 1400, 6, 20, 1000, 0., 10.);

  TH2F *hREp1_InstLumi = new TH2F("hREp1_InstLumi", "hREp1_InstLumi", 1400, 6, 20, 1000, 0., 10.);
  TH2F *hREp2_InstLumi = new TH2F("hREp2_InstLumi", "hREp2_InstLumi", 1400, 6, 20, 1000, 0., 10.);
  TH2F *hREp3_InstLumi = new TH2F("hREp3_InstLumi", "hREp3_InstLumi", 1400, 6, 20, 1000, 0., 10.);
  TH2F *hREp4_InstLumi = new TH2F("hREp4_InstLumi", "hREp4_InstLumi", 1400, 6, 20, 1000, 0., 10.);

  TH2F *hREm1_InstLumi = new TH2F("hREm1_InstLumi", "hREm1_InstLumi", 1400, 6, 20, 1000, 0., 10.);
  TH2F *hREm2_InstLumi = new TH2F("hREm2_InstLumi", "hREm2_InstLumi", 1400, 6, 20, 1000, 0., 10.);
  TH2F *hREm3_InstLumi = new TH2F("hREm3_InstLumi", "hREm3_InstLumi", 1400, 6, 20, 1000, 0., 10.);
  TH2F *hREm4_InstLumi = new TH2F("hREm4_InstLumi", "hREm4_InstLumi", 1400, 6, 20, 1000, 0., 10.);

  TH2F *hREm_InstLumi = new TH2F("hREm_InstLumi", "hREm_InstLumi", 1400, 6, 20, 1000, 0., 10.);
  TH2F *hREp_InstLumi = new TH2F("hREp_InstLumi", "hREp_InstLumi", 1400, 6, 20, 1000, 0., 10.);

  std::map<long long , double> pairLsKeyLumi;
  std::map<long long , double> pairLsKeyRateRB1in;
  std::map<long long , double> pairLsKeyRateRB1out;
  std::map<long long , double> pairLsKeyRateRB2in;
  std::map<long long , double> pairLsKeyRateRB2out;
  std::map<long long , double> pairLsKeyRateRB3;
  std::map<long long , double> pairLsKeyRateRB4;

  std::map<long long , double> pairLsKeyRateB;

  std::map<long long , double> pairLsKeyRateW0;
  std::map<long long , double> pairLsKeyRateWp1;
  std::map<long long , double> pairLsKeyRateWp2;
  std::map<long long , double> pairLsKeyRateWm1;
  std::map<long long , double> pairLsKeyRateWm2;

  std::map<long long , double> pairLsKeyRateREp1;
  std::map<long long , double> pairLsKeyRateREp2;
  std::map<long long , double> pairLsKeyRateREp3;
  std::map<long long , double> pairLsKeyRateREp4;

  std::map<long long , double> pairLsKeyRateREm1;
  std::map<long long , double> pairLsKeyRateREm2;
  std::map<long long , double> pairLsKeyRateREm3;
  std::map<long long , double> pairLsKeyRateREm4;

  std::map<long long , double> pairLsKeyRateREp;
  std::map<long long , double> pairLsKeyRateREm;

  int nRun_pre=0;

//rumi
  std::map<long long, int> pairLsCounts;
  std::map<long long, int>::iterator cc;
  int myscale = 1;
  double myTime = 25.e-9 * 6.;
//double myTime = 25.e-9 * numbBXs_;

  if (fChain == 0) return;

  Long64_t nentries = fChain->GetEntriesFast();

  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);  nbytes += nb;

//pairLsCounts
    cc = pairLsCounts.find(LsKey(Ls,nRun));
    if(cc != pairLsCounts.end()) cc->second += 1;
    else pairLsCounts.insert ( std::pair<long long ,int>(LsKey(Ls,nRun),1));

    pairLsKeyLumi.insert ( std::pair<long long,double>(LsKey(Ls,nRun),Lumi));

    std::map<long long, double>::iterator lb = pairLsKeyRateRB1in.find(LsKey(Ls,nRun));
    if(lb != pairLsKeyRateRB1in.end()) {lb->second += RB1inHits;
    }
    else {
      pairLsKeyRateRB1in.insert ( std::pair<long long,double>(LsKey(Ls,nRun),RB1inHits));    
    }

    lb = pairLsKeyRateRB1out.find(LsKey(Ls,nRun));
    if(lb != pairLsKeyRateRB1out.end()) {lb->second += RB1outHits;
    }
    else {
      pairLsKeyRateRB1out.insert ( std::pair<long long,double>(LsKey(Ls,nRun),RB1outHits));    
    }
    lb = pairLsKeyRateRB2in.find(LsKey(Ls,nRun));
    if(lb != pairLsKeyRateRB2in.end()) {lb->second += RB2inHits;
    }
    else {
      pairLsKeyRateRB2in.insert ( std::pair<long long,double>(LsKey(Ls,nRun),RB2inHits));    
    }
    lb = pairLsKeyRateRB2out.find(LsKey(Ls,nRun));
    if(lb != pairLsKeyRateRB2out.end()) {lb->second += RB2outHits;
    }
    else {
      pairLsKeyRateRB2out.insert ( std::pair<long long,double>(LsKey(Ls,nRun),RB2outHits));    
    }
    lb = pairLsKeyRateRB3.find(LsKey(Ls,nRun));
    if(lb != pairLsKeyRateRB3.end()) {lb->second += RB3Hits;
    }
    else {
      pairLsKeyRateRB3.insert ( std::pair<long long,double>(LsKey(Ls,nRun),RB3Hits));    
    }
    lb = pairLsKeyRateRB4.find(LsKey(Ls,nRun));
    if(lb != pairLsKeyRateRB4.end()) {lb->second += RB4Hits;
    }
    else {
      pairLsKeyRateRB4.insert ( std::pair<long long,double>(LsKey(Ls,nRun),RB4Hits));    
    }
    lb = pairLsKeyRateB.find(LsKey(Ls,nRun));

    if(lb != pairLsKeyRateB.end()) {lb->second += BHits;
    }
    else {
      pairLsKeyRateB.insert ( std::pair<long long,double>(LsKey(Ls,nRun),BHits));    
    }

    lb = pairLsKeyRateWp2.find(LsKey(Ls,nRun));
    if(lb != pairLsKeyRateWp2.end()) {lb->second += Wp2Hits;
    }
    else {
      pairLsKeyRateWp2.insert ( std::pair<long long,double>(LsKey(Ls,nRun),Wp2Hits));    
    }
    lb = pairLsKeyRateWp1.find(LsKey(Ls,nRun));
    if(lb != pairLsKeyRateWp1.end()) {lb->second += Wp1Hits;
    }
    else {
      pairLsKeyRateWp1.insert ( std::pair<long long,double>(LsKey(Ls,nRun),Wp1Hits));    
    }
    lb = pairLsKeyRateWm2.find(LsKey(Ls,nRun));
    if(lb != pairLsKeyRateWm2.end()) {lb->second += Wm2Hits;
    }
    else {
      pairLsKeyRateWm2.insert ( std::pair<long long,double>(LsKey(Ls,nRun),Wm2Hits));    
    }
    lb = pairLsKeyRateWm1.find(LsKey(Ls,nRun));
    if(lb != pairLsKeyRateWm1.end()) {lb->second += Wm1Hits;
    }
    else {
      pairLsKeyRateWm1.insert ( std::pair<long long,double>(LsKey(Ls,nRun),Wm1Hits));    
    }
    lb = pairLsKeyRateW0.find(LsKey(Ls,nRun));
    if(lb != pairLsKeyRateW0.end()) {lb->second += W0Hits;
    }
    else {
      pairLsKeyRateW0.insert ( std::pair<long long,double>(LsKey(Ls,nRun),W0Hits));    
    }

    lb = pairLsKeyRateREm1.find(LsKey(Ls,nRun));
    if(lb != pairLsKeyRateREm1.end()) {lb->second += REm1Hits;
    }
    else {
      pairLsKeyRateREm1.insert ( std::pair<long long,double>(LsKey(Ls,nRun),REm1Hits));    
    }
    lb = pairLsKeyRateREm2.find(LsKey(Ls,nRun));
    if(lb != pairLsKeyRateREm2.end()) {lb->second += REm2Hits;
    }
    else {
      pairLsKeyRateREm2.insert ( std::pair<long long,double>(LsKey(Ls,nRun),REm2Hits));    
    }
    lb = pairLsKeyRateREm3.find(LsKey(Ls,nRun));
    if(lb != pairLsKeyRateREm3.end()) {lb->second += REm3Hits;
    }
    else {
      pairLsKeyRateREm3.insert ( std::pair<long long,double>(LsKey(Ls,nRun),REm3Hits));    
    }
    lb = pairLsKeyRateREm4.find(LsKey(Ls,nRun));
    if(lb != pairLsKeyRateREm4.end()) {lb->second += REm4Hits;
    }
    else {
      pairLsKeyRateREm4.insert ( std::pair<long long,double>(LsKey(Ls,nRun),REm4Hits));    
    }

    lb = pairLsKeyRateREp1.find(LsKey(Ls,nRun));
    if(lb != pairLsKeyRateREp1.end()) {lb->second += REp1Hits;
    }
    else {
      pairLsKeyRateREp1.insert ( std::pair<long long,double>(LsKey(Ls,nRun),REp1Hits));    
    }
    lb = pairLsKeyRateREp2.find(LsKey(Ls,nRun));
    if(lb != pairLsKeyRateREp2.end()) {lb->second += REp2Hits;
    }
    else {
      pairLsKeyRateREp2.insert ( std::pair<long long,double>(LsKey(Ls,nRun),REp2Hits));    
    }
    lb = pairLsKeyRateREp3.find(LsKey(Ls,nRun));
    if(lb != pairLsKeyRateREp3.end()) {lb->second += REp3Hits;
    }
    else {
      pairLsKeyRateREp3.insert ( std::pair<long long,double>(LsKey(Ls,nRun),REp3Hits));    
    }
    lb = pairLsKeyRateREp4.find(LsKey(Ls,nRun));
    if(lb != pairLsKeyRateREp4.end()) {lb->second += REp4Hits;
    }
    else {
      pairLsKeyRateREp4.insert ( std::pair<long long,double>(LsKey(Ls,nRun),REp4Hits));    
    }

    lb = pairLsKeyRateREp.find(LsKey(Ls,nRun));
    if(lb != pairLsKeyRateREp.end()) {lb->second += REpHits;
    }
    else {
      pairLsKeyRateREp.insert ( std::pair<long long,double>(LsKey(Ls,nRun),REpHits));    
    }
    lb = pairLsKeyRateREm.find(LsKey(Ls,nRun));
    if(lb != pairLsKeyRateREm.end()) {lb->second += REmHits;
    }
    else {
      pairLsKeyRateREm.insert ( std::pair<long long,double>(LsKey(Ls,nRun),REmHits));    
    }

  } // end for jentry<nentries

// filling TGraph
//rb1in
  int jrb1in=0;
  std::map<long long,double>::iterator itLumi = pairLsKeyLumi.begin();
  for (itLumi=pairLsKeyLumi.begin(); itLumi!=pairLsKeyLumi.end(); ++itLumi)
  {
//find how many times the lumi section was analyzed
   std::map<long long, int>::iterator itr = pairLsCounts.find(itLumi->first);
   if(itr != pairLsCounts.end()) myscale = itr->second;
   else std::cout << "no scale was found for luminosity: " << itLumi->first << " " << itLumi->second << std::endl;

   std::map<long long,double>::iterator itRateRB1in = pairLsKeyRateRB1in.find(itLumi->first);
   if(itRateRB1in != pairLsKeyRateRB1in.end())
   {
    if(itRateRB1in->second > 1e8  ) {
      cout<<"Rb1in_istLumi jr = "<<jrb1in<<" ,Ls = "<<itLumi->first<<" ,lumi  = "<<itLumi->second<<" ,rateRB1in = "<<itRateRB1in->second<<endl;
      continue;
    }
    RB1in_InstLumi->SetPoint(jrb1in, itLumi->second, (itRateRB1in->second)/(areaRB1in*myTime*myscale*1.));
    hRB1in_InstLumi->Fill(itLumi->second, (itRateRB1in->second)/(areaRB1in*myTime*myscale*1.));
    jrb1in++;
   }
  } // end loop LsLumi

//rb1out
  int jrb1out=0;
  itLumi = pairLsKeyLumi.begin();
  for (itLumi=pairLsKeyLumi.begin(); itLumi!=pairLsKeyLumi.end(); ++itLumi)
  {
//find how many times the lumi section was analyzed
   std::map<long long, int>::iterator itr = pairLsCounts.find(itLumi->first);
   if(itr != pairLsCounts.end()) myscale = itr->second;
   else std::cout << "no scale was found for luminosity: " << itLumi->first << " " << itLumi->second << std::endl;

   std::map<long long,double>::iterator itRateRB1out = pairLsKeyRateRB1out.find(itLumi->first);
   if(itRateRB1out != pairLsKeyRateRB1out.end())
   {
    if(itRateRB1out->second > 1e8  ) {

      cout<<"Rb1out_istLumi jr = "<<jrb1out<<" ,Ls = "<<itLumi->first<<" ,lumi  = "<<itLumi->second<<" ,rateRB1out = "<<itRateRB1out->second<<endl;
      continue;
    }
    RB1out_InstLumi->SetPoint(jrb1out, itLumi->second, (itRateRB1out->second)/(areaRB1out*myTime*myscale*1.));
    hRB1out_InstLumi->Fill(itLumi->second, (itRateRB1out->second)/(areaRB1out*myTime*myscale*1.));
    jrb1out++;
   }
  }

//rb2in
  int jrb2in=0;
  itLumi = pairLsKeyLumi.begin();
  for (itLumi=pairLsKeyLumi.begin(); itLumi!=pairLsKeyLumi.end(); ++itLumi)
  {
//find how many times the lumi section was analyzed
   std::map<long long, int>::iterator itr = pairLsCounts.find(itLumi->first);
   if(itr != pairLsCounts.end()) myscale = itr->second;
   else std::cout << "no scale was found for luminosity: " << itLumi->first << " " << itLumi->second << std::endl;

   std::map<long long,double>::iterator itRateRB2in = pairLsKeyRateRB2in.find(itLumi->first);
   if(itRateRB2in != pairLsKeyRateRB2in.end())
   {
    if(itRateRB2in->second > 1e8  ) {

      cout<<"Rb2in_istLumi jr = "<<jrb2in<<" ,Ls = "<<itLumi->first<<" ,lumi  = "<<itLumi->second<<" ,rateRB2in = "<<itRateRB2in->second<<endl;
      continue;
    }
    RB2in_InstLumi->SetPoint(jrb2in, itLumi->second, (itRateRB2in->second)/(areaRB2in*myTime*myscale*1.));
    hRB2in_InstLumi->Fill(itLumi->second, (itRateRB2in->second)/(areaRB2in*myTime*myscale*1.));
    jrb2in++;
   }
  }

//rb2out
  int jrb2out=0;
  itLumi = pairLsKeyLumi.begin();
  for (itLumi=pairLsKeyLumi.begin(); itLumi!=pairLsKeyLumi.end(); ++itLumi)
  {
//find how many times the lumi section was analyzed
   std::map<long long, int>::iterator itr = pairLsCounts.find(itLumi->first);
   if(itr != pairLsCounts.end()) myscale = itr->second;
   else std::cout << "no scale was found for luminosity: " << itLumi->first << " " << itLumi->second << std::endl;

   std::map<long long,double>::iterator itRateRB2out = pairLsKeyRateRB2out.find(itLumi->first);
   if(itRateRB2out != pairLsKeyRateRB2out.end())
   {
    if(itRateRB2out->second > 1e8  ) {

      cout<<"Rb2out_istLumi jr = "<<jrb2out<<" ,Ls = "<<itLumi->first<<" ,lumi  = "<<itLumi->second<<" ,rateRB2out = "<<itRateRB2out->second<<endl;
      continue;
    }
    RB2out_InstLumi->SetPoint(jrb2out, itLumi->second, (itRateRB2out->second)/(areaRB2out*myTime*myscale*1.));
    hRB2out_InstLumi->Fill(itLumi->second, (itRateRB2out->second)/(areaRB2out*myTime*myscale*1.));
    jrb2out++;
   }
  }

//rb3
  int jrb3=0;
  itLumi = pairLsKeyLumi.begin();
  for (itLumi=pairLsKeyLumi.begin(); itLumi!=pairLsKeyLumi.end(); ++itLumi)
  {
//find how many times the lumi section was analyzed
   std::map<long long, int>::iterator itr = pairLsCounts.find(itLumi->first);
   if(itr != pairLsCounts.end()) myscale = itr->second;
   else std::cout << "no scale was found for luminosity: " << itLumi->first << " " << itLumi->second << std::endl;

   std::map<long long,double>::iterator itRateRB3 = pairLsKeyRateRB3.find(itLumi->first);
   if(itRateRB3 != pairLsKeyRateRB3.end())
   {
    if(itRateRB3->second > 1e8  ) {

      cout<<"Rb3_istLumi jr = "<<jrb3<<" ,Ls = "<<itLumi->first<<" ,lumi  = "<<itLumi->second<<" ,rateRB3 = "<<itRateRB3->second<<endl;
      continue;
    }
    RB3_InstLumi->SetPoint(jrb3, itLumi->second, (itRateRB3->second)/(areaRB3*myTime*myscale*1.));
    hRB3_InstLumi->Fill(itLumi->second, (itRateRB3->second)/(areaRB3*myTime*myscale*1.));
    jrb3++;
   }
  }

//rb4
  int jrb4=0;
  itLumi = pairLsKeyLumi.begin();
  for (itLumi=pairLsKeyLumi.begin(); itLumi!=pairLsKeyLumi.end(); ++itLumi)
  {
//find how many times the lumi section was analyzed
   std::map<long long, int>::iterator itr = pairLsCounts.find(itLumi->first);
   if(itr != pairLsCounts.end()) myscale = itr->second;
   else std::cout << "no scale was found for luminosity: " << itLumi->first << " " << itLumi->second << std::endl;

   std::map<long long,double>::iterator itRateRB4 = pairLsKeyRateRB4.find(itLumi->first);
   if(itRateRB4 != pairLsKeyRateRB4.end())
   {
    if(itRateRB4->second > 1e8  ) {

      cout<<"Rb4_istLumi jr = "<<jrb4<<" ,Ls = "<<itLumi->first<<" ,lumi  = "<<itLumi->second<<" ,rateRB4 = "<<itRateRB4->second<<endl;
      continue;
    }
    RB4_InstLumi->SetPoint(jrb4, itLumi->second, (itRateRB4->second)/(areaRB4*myTime*myscale*1.));
    hRB4_InstLumi->Fill(itLumi->second, (itRateRB4->second)/(areaRB4*myTime*myscale*1.));
    jrb4++;
   }
  }

//Wp2
  int jWp2=0;
  itLumi = pairLsKeyLumi.begin();
  for (itLumi=pairLsKeyLumi.begin(); itLumi!=pairLsKeyLumi.end(); ++itLumi)
  {
//find how many times the lumi section was analyzed
   std::map<long long, int>::iterator itr = pairLsCounts.find(itLumi->first);
   if(itr != pairLsCounts.end()) myscale = itr->second;
   else std::cout << "no scale was found for luminosity: " << itLumi->first << " " << itLumi->second << std::endl;

   std::map<long long,double>::iterator itRateWp2 = pairLsKeyRateWp2.find(itLumi->first);
   if(itRateWp2 != pairLsKeyRateWp2.end())
   {
    if(itRateWp2->second > 1e8  ) {

      cout<<"Wp2_istLumi jr = "<<jWp2<<" ,Ls = "<<itLumi->first<<" ,lumi  = "<<itLumi->second<<" ,rateWp2 = "<<itRateWp2->second<<endl;
      continue;
    }
    Wp2_InstLumi->SetPoint(jWp2, itLumi->second, (itRateWp2->second)/(areaWp2*myTime*myscale*1.));
    hWp2_InstLumi->Fill(itLumi->second, (itRateWp2->second)/(areaWp2*myTime*myscale*1.));
    jWp2++;
   }
  }

//Wp1
  int jWp1=0;
  itLumi = pairLsKeyLumi.begin();
  for (itLumi=pairLsKeyLumi.begin(); itLumi!=pairLsKeyLumi.end(); ++itLumi)
  {
//find how many times the lumi section was analyzed
   std::map<long long, int>::iterator itr = pairLsCounts.find(itLumi->first);
   if(itr != pairLsCounts.end()) myscale = itr->second;
   else std::cout << "no scale was found for luminosity: " << itLumi->first << " " << itLumi->second << std::endl;

   std::map<long long,double>::iterator itRateWp1 = pairLsKeyRateWp1.find(itLumi->first);
   if(itRateWp1 != pairLsKeyRateWp1.end())
   {
    if(itRateWp1->second > 1e8  ) {

      cout<<"Wp1_istLumi jr = "<<jWp1<<" ,Ls = "<<itLumi->first<<" ,lumi  = "<<itLumi->second<<" ,rateWp1 = "<<itRateWp1->second<<endl;
      continue;
    }
    Wp1_InstLumi->SetPoint(jWp1, itLumi->second, (itRateWp1->second)/(areaWp1*myTime*myscale*1.));
    hWp1_InstLumi->Fill(itLumi->second, (itRateWp1->second)/(areaWp1*myTime*myscale*1.));
    jWp1++;
   }
  }

//Wm2
  int jWm2=0;
  itLumi = pairLsKeyLumi.begin();
  for (itLumi=pairLsKeyLumi.begin(); itLumi!=pairLsKeyLumi.end(); ++itLumi)
  {
//find how many times the lumi section was analyzed
   std::map<long long, int>::iterator itr = pairLsCounts.find(itLumi->first);
   if(itr != pairLsCounts.end()) myscale = itr->second;
   else std::cout << "no scale was found for luminosity: " << itLumi->first << " " << itLumi->second << std::endl;

   std::map<long long,double>::iterator itRateWm2 = pairLsKeyRateWm2.find(itLumi->first);
   if(itRateWm2 != pairLsKeyRateWm2.end())
   {
    if(itRateWm2->second > 1e8  ) {

      cout<<"Wm2_istLumi jr = "<<jWm2<<" ,Ls = "<<itLumi->first<<" ,lumi  = "<<itLumi->second<<" ,rateWm2 = "<<itRateWm2->second<<endl;
      continue;
    }
    Wm2_InstLumi->SetPoint(jWm2, itLumi->second, (itRateWm2->second)/(areaWm2*myTime*myscale*1.));
    hWm2_InstLumi->Fill(itLumi->second, (itRateWm2->second)/(areaWm2*myTime*myscale*1.));
    jWm2++;
   }
  }

//Wm1
  int jWm1=0;
  itLumi = pairLsKeyLumi.begin();
  for (itLumi=pairLsKeyLumi.begin(); itLumi!=pairLsKeyLumi.end(); ++itLumi)
  {
//find how many times the lumi section was analyzed
   std::map<long long, int>::iterator itr = pairLsCounts.find(itLumi->first);
   if(itr != pairLsCounts.end()) myscale = itr->second;
   else std::cout << "no scale was found for luminosity: " << itLumi->first << " " << itLumi->second << std::endl;

   std::map<long long,double>::iterator itRateWm1 = pairLsKeyRateWm1.find(itLumi->first);
   if(itRateWm1 != pairLsKeyRateWm1.end())
   {
    if(itRateWm1->second > 1e8  ) {

      cout<<"Wm1_istLumi jr = "<<jWm1<<" ,Ls = "<<itLumi->first<<" ,lumi  = "<<itLumi->second<<" ,rateWm1 = "<<itRateWm1->second<<endl;
      continue;
    }
    Wm1_InstLumi->SetPoint(jWm1, itLumi->second, (itRateWm1->second)/(areaWm1*myTime*myscale*1.));
    hWm1_InstLumi->Fill(itLumi->second, (itRateWm1->second)/(areaWm1*myTime*myscale*1.));
    jWm1++;
   }
  }

//W0
  int jW0=0;
  itLumi = pairLsKeyLumi.begin();
  for (itLumi=pairLsKeyLumi.begin(); itLumi!=pairLsKeyLumi.end(); ++itLumi)
  {
//find how many times the lumi section was analyzed
   std::map<long long, int>::iterator itr = pairLsCounts.find(itLumi->first);
   if(itr != pairLsCounts.end()) myscale = itr->second;
   else std::cout << "no scale was found for luminosity: " << itLumi->first << " " << itLumi->second << std::endl;

   std::map<long long,double>::iterator itRateW0 = pairLsKeyRateW0.find(itLumi->first);
   if(itRateW0 != pairLsKeyRateW0.end())
   {
    if(itRateW0->second > 1e8  ) {

      cout<<"W0_istLumi jr = "<<jW0<<" ,Ls = "<<itLumi->first<<" ,lumi  = "<<itLumi->second<<" ,rateW0 = "<<itRateW0->second<<endl;
      continue;
    }
    W0_InstLumi->SetPoint(jW0, itLumi->second, (itRateW0->second)/(areaW0*myTime*myscale*1.));
    hW0_InstLumi->Fill(itLumi->second, (itRateW0->second)/(areaW0*myTime*myscale*1.));
    jW0++;
   }
  }

//B
  int jB=0;
  itLumi = pairLsKeyLumi.begin();
  for (itLumi=pairLsKeyLumi.begin(); itLumi!=pairLsKeyLumi.end(); ++itLumi)
  {
//find how many times the lumi section was analyzed
   std::map<long long, int>::iterator itr = pairLsCounts.find(itLumi->first);
   if(itr != pairLsCounts.end()) myscale = itr->second;
   else std::cout << "no scale was found for luminosity: " << itLumi->first << " " << itLumi->second << std::endl;

   std::map<long long,double>::iterator itRateB = pairLsKeyRateB.find(itLumi->first);
   if(itRateB != pairLsKeyRateB.end())
   {
    if(itRateB->second > 1e8  ) {

      cout<<"B_istLumi jr = "<<jB<<" ,Ls = "<<itLumi->first<<" ,lumi  = "<<itLumi->second<<" ,rateB = "<<itRateB->second<<endl;
      continue;
    }
    B_InstLumi->SetPoint(jB, itLumi->second, (itRateB->second)/(areaB*myTime*myscale*1.));
    hB_InstLumi->Fill(itLumi->second, (itRateB->second)/(areaB*myTime*myscale*1.));
    jB++;
   }
  }

//REp
  int jREp=0;
  itLumi = pairLsKeyLumi.begin();
  for (itLumi=pairLsKeyLumi.begin(); itLumi!=pairLsKeyLumi.end(); ++itLumi)
  {
//find how many times the lumi section was analyzed
   std::map<long long, int>::iterator itr = pairLsCounts.find(itLumi->first);
   if(itr != pairLsCounts.end()) myscale = itr->second;
   else std::cout << "no scale was found for luminosity: " << itLumi->first << " " << itLumi->second << std::endl;

   std::map<long long,double>::iterator itRateREp = pairLsKeyRateREp.find(itLumi->first);
   if(itRateREp != pairLsKeyRateREp.end())
   {
    if(itRateREp->second > 1e8  ) {

      cout<<"REp_istLumi jr = "<<jREp<<" ,Ls = "<<itLumi->first<<" ,lumi  = "<<itLumi->second<<" ,rateREp = "<<itRateREp->second<<endl;
      continue;
    }
    REp_InstLumi->SetPoint(jREp, itLumi->second, (itRateREp->second)/(areaREp*myTime*myscale*1.));
    hREp_InstLumi->Fill(itLumi->second, (itRateREp->second)/(areaREp*myTime*myscale*1.));
    jREp++;
   }
  }

//REm
  int jREm=0;
  itLumi = pairLsKeyLumi.begin();
  for (itLumi=pairLsKeyLumi.begin(); itLumi!=pairLsKeyLumi.end(); ++itLumi)
  {
//find how many times the lumi section was analyzed
   std::map<long long, int>::iterator itr = pairLsCounts.find(itLumi->first);
   if(itr != pairLsCounts.end()) myscale = itr->second;
   else std::cout << "no scale was found for luminosity: " << itLumi->first << " " << itLumi->second << std::endl;

   std::map<long long,double>::iterator itRateREm = pairLsKeyRateREm.find(itLumi->first);
   if(itRateREm != pairLsKeyRateREm.end())
   {
    if(itRateREm->second > 1e8  ) {

      cout<<"REm_istLumi jr = "<<jREm<<" ,Ls = "<<itLumi->first<<" ,lumi  = "<<itLumi->second<<" ,rateREm = "<<itRateREm->second<<endl;
      continue;
    }
    REm_InstLumi->SetPoint(jREm, itLumi->second, (itRateREm->second)/(areaREm*myTime*myscale*1.));
    hREm_InstLumi->Fill(itLumi->second, (itRateREm->second)/(areaREm*myTime*myscale*1.));
    jREm++;
   }
  }

//REm1
  int jREm1=0;
  itLumi = pairLsKeyLumi.begin();
  for (itLumi=pairLsKeyLumi.begin(); itLumi!=pairLsKeyLumi.end(); ++itLumi)
  {
//find how many times the lumi section was analyzed
   std::map<long long, int>::iterator itr = pairLsCounts.find(itLumi->first);
   if(itr != pairLsCounts.end()) myscale = itr->second;
   else std::cout << "no scale was found for luminosity: " << itLumi->first << " " << itLumi->second << std::endl;

   std::map<long long,double>::iterator itRateREm1 = pairLsKeyRateREm1.find(itLumi->first);
   if(itRateREm1 != pairLsKeyRateREm1.end())
   {
    if(itRateREm1->second > 1e8  ) {

      cout<<"REm1_istLumi jr = "<<jREm1<<" ,Ls = "<<itLumi->first<<" ,lumi  = "<<itLumi->second<<" ,rateREm1 = "<<itRateREm1->second<<endl;
      continue;
    }
    REm1_InstLumi->SetPoint(jREm1, itLumi->second, (itRateREm1->second)/(areaREm1*myTime*myscale*1.));
    hREm1_InstLumi->Fill(itLumi->second, (itRateREm1->second)/(areaREm1*myTime*myscale*1.));
    jREm1++;
   }
  }

//REm2
  int jREm2=0;
  itLumi = pairLsKeyLumi.begin();
  for (itLumi=pairLsKeyLumi.begin(); itLumi!=pairLsKeyLumi.end(); ++itLumi)
  {
//find how many times the lumi section was analyzed
   std::map<long long, int>::iterator itr = pairLsCounts.find(itLumi->first);
   if(itr != pairLsCounts.end()) myscale = itr->second;
   else std::cout << "no scale was found for luminosity: " << itLumi->first << " " << itLumi->second << std::endl;

   std::map<long long,double>::iterator itRateREm2 = pairLsKeyRateREm2.find(itLumi->first);
   if(itRateREm2 != pairLsKeyRateREm2.end())
   {
    if(itRateREm2->second > 1e8  ) {

      cout<<"REm2_istLumi jr = "<<jREm2<<" ,Ls = "<<itLumi->first<<" ,lumi  = "<<itLumi->second<<" ,rateREm2 = "<<itRateREm2->second<<endl;
      continue;
    }
    REm2_InstLumi->SetPoint(jREm2, itLumi->second, (itRateREm2->second)/(areaREm2*myTime*myscale*1.));
    hREm2_InstLumi->Fill(itLumi->second, (itRateREm2->second)/(areaREm2*myTime*myscale*1.));
    jREm2++;
   }
  }

//REm3
  int jREm3=0;
  itLumi = pairLsKeyLumi.begin();
  for (itLumi=pairLsKeyLumi.begin(); itLumi!=pairLsKeyLumi.end(); ++itLumi)
  {
//find how many times the lumi section was analyzed
   std::map<long long, int>::iterator itr = pairLsCounts.find(itLumi->first);
   if(itr != pairLsCounts.end()) myscale = itr->second;
   else std::cout << "no scale was found for luminosity: " << itLumi->first << " " << itLumi->second << std::endl;

   std::map<long long,double>::iterator itRateREm3 = pairLsKeyRateREm3.find(itLumi->first);
   if(itRateREm3 != pairLsKeyRateREm3.end())
   {
    if(itRateREm3->second > 1e8  ) {

      cout<<"REm3_istLumi jr = "<<jREm3<<" ,Ls = "<<itLumi->first<<" ,lumi  = "<<itLumi->second<<" ,rateREm3 = "<<itRateREm3->second<<endl;
      continue;
    }
    REm3_InstLumi->SetPoint(jREm3, itLumi->second, (itRateREm3->second)/(areaREm3*myTime*myscale*1.));
    hREm3_InstLumi->Fill(itLumi->second, (itRateREm3->second)/(areaREm3*myTime*myscale*1.));
    jREm3++;
   }
  }

//REm4
  int jREm4=0;
  itLumi = pairLsKeyLumi.begin();
  for (itLumi=pairLsKeyLumi.begin(); itLumi!=pairLsKeyLumi.end(); ++itLumi)
  {
//find how many times the lumi section was analyzed
   std::map<long long, int>::iterator itr = pairLsCounts.find(itLumi->first);
   if(itr != pairLsCounts.end()) myscale = itr->second;
   else std::cout << "no scale was found for luminosity: " << itLumi->first << " " << itLumi->second << std::endl;

   std::map<long long,double>::iterator itRateREm4 = pairLsKeyRateREm4.find(itLumi->first);
   if(itRateREm4 != pairLsKeyRateREm4.end())
   {
    if(itRateREm4->second > 1e8  ) {

      cout<<"REm4_istLumi jr = "<<jREm4<<" ,Ls = "<<itLumi->first<<" ,lumi  = "<<itLumi->second<<" ,rateREm4 = "<<itRateREm4->second<<endl;
      continue;
    }
    REm4_InstLumi->SetPoint(jREm4, itLumi->second, (itRateREm4->second)/(areaREm4*myTime*myscale*1.));
    hREm4_InstLumi->Fill(itLumi->second, (itRateREm4->second)/(areaREm4*myTime*myscale*1.));
    jREm4++;
   }
  }

//REp1
  int jREp1=0;
  itLumi = pairLsKeyLumi.begin();
  for (itLumi=pairLsKeyLumi.begin(); itLumi!=pairLsKeyLumi.end(); ++itLumi)
  {
//find how many times the lumi section was analyzed
   std::map<long long, int>::iterator itr = pairLsCounts.find(itLumi->first);
   if(itr != pairLsCounts.end()) myscale = itr->second;
   else std::cout << "no scale was found for luminosity: " << itLumi->first << " " << itLumi->second << std::endl;

   std::map<long long,double>::iterator itRateREp1 = pairLsKeyRateREp1.find(itLumi->first);
   if(itRateREp1 != pairLsKeyRateREp1.end())
   {
    if(itRateREp1->second > 1e8  ) {

      cout<<"REp1_istLumi jr = "<<jREp1<<" ,Ls = "<<itLumi->first<<" ,lumi  = "<<itLumi->second<<" ,rateREp1 = "<<itRateREp1->second<<endl;
      continue;
    }
    REp1_InstLumi->SetPoint(jREp1, itLumi->second, (itRateREp1->second)/(areaREp1*myTime*myscale*1.));
    hREp1_InstLumi->Fill(itLumi->second, (itRateREp1->second)/(areaREp1*myTime*myscale*1.));
    jREp1++;
   }
  }

//REp2
  int jREp2=0;
  itLumi = pairLsKeyLumi.begin();
  for (itLumi=pairLsKeyLumi.begin(); itLumi!=pairLsKeyLumi.end(); ++itLumi)
  {
//find how many times the lumi section was analyzed
   std::map<long long, int>::iterator itr = pairLsCounts.find(itLumi->first);
   if(itr != pairLsCounts.end()) myscale = itr->second;
   else std::cout << "no scale was found for luminosity: " << itLumi->first << " " << itLumi->second << std::endl;

   std::map<long long,double>::iterator itRateREp2 = pairLsKeyRateREp2.find(itLumi->first);
   if(itRateREp2 != pairLsKeyRateREp2.end())
   {
    if(itRateREp2->second > 1e8  ) {

      cout<<"REp2_istLumi jr = "<<jREp2<<" ,Ls = "<<itLumi->first<<" ,lumi  = "<<itLumi->second<<" ,rateREp2 = "<<itRateREp2->second<<endl;
      continue;
    }
    REp2_InstLumi->SetPoint(jREp2, itLumi->second, (itRateREp2->second)/(areaREp2*myTime*myscale*1.));
    hREp2_InstLumi->Fill(itLumi->second, (itRateREp2->second)/(areaREp2*myTime*myscale*1.));
    jREp2++;
   }
  }

//REp3
  int jREp3=0;
  itLumi = pairLsKeyLumi.begin();
  for (itLumi=pairLsKeyLumi.begin(); itLumi!=pairLsKeyLumi.end(); ++itLumi)
  {
//find how many times the lumi section was analyzed
   std::map<long long, int>::iterator itr = pairLsCounts.find(itLumi->first);
   if(itr != pairLsCounts.end()) myscale = itr->second;
   else std::cout << "no scale was found for luminosity: " << itLumi->first << " " << itLumi->second << std::endl;

   std::map<long long,double>::iterator itRateREp3 = pairLsKeyRateREp3.find(itLumi->first);
   if(itRateREp3 != pairLsKeyRateREp3.end())
   {
    if(itRateREp3->second > 1e8  ) {

      cout<<"REp3_istLumi jr = "<<jREp3<<" ,Ls = "<<itLumi->first<<" ,lumi  = "<<itLumi->second<<" ,rateREp3 = "<<itRateREp3->second<<endl;
      continue;
    }
    REp3_InstLumi->SetPoint(jREp3, itLumi->second, (itRateREp3->second)/(areaREp3*myTime*myscale*1.));
    hREp3_InstLumi->Fill(itLumi->second, (itRateREp3->second)/(areaREp3*myTime*myscale*1.));
    jREp3++;
   }
  }

//REp4
  int jREp4=0;
  itLumi = pairLsKeyLumi.begin();
  for (itLumi=pairLsKeyLumi.begin(); itLumi!=pairLsKeyLumi.end(); ++itLumi)
  {
//find how many times the lumi section was analyzed
   std::map<long long, int>::iterator itr = pairLsCounts.find(itLumi->first);
   if(itr != pairLsCounts.end()) myscale = itr->second;
   else std::cout << "no scale was found for luminosity: " << itLumi->first << " " << itLumi->second << std::endl;

   std::map<long long,double>::iterator itRateREp4 = pairLsKeyRateREp4.find(itLumi->first);
   if(itRateREp4 != pairLsKeyRateREp4.end())
   {
    if(itRateREp4->second > 1e8  ) {

      cout<<"REp4_istLumi jr = "<<jREp4<<" ,Ls = "<<itLumi->first<<" ,lumi  = "<<itLumi->second<<" ,rateREp4 = "<<itRateREp4->second<<endl;
      continue;
    }
    REp4_InstLumi->SetPoint(jREp4, itLumi->second, (itRateREp4->second)/(areaREp4*myTime*myscale*1.));
    hREp4_InstLumi->Fill(itLumi->second, (itRateREp4->second)/(areaREp4*myTime*myscale*1.));
    jREp4++;
   }
  }

 fout->cd();
//  RB1in_InstLumi->Draw();
  RB1in_InstLumi->Write();
//  RB1out_InstLumi->Draw();
  RB1out_InstLumi->Write();
  RB2in_InstLumi->Write();
  RB2out_InstLumi->Write();
  RB3_InstLumi->Write();
  RB4_InstLumi->Write();
  B_InstLumi->Write();
  Wp2_InstLumi->Write();
  Wp1_InstLumi->Write();
  W0_InstLumi->Write();
  Wm1_InstLumi->Write();
  Wm2_InstLumi->Write();
  REp_InstLumi->Write();
  REm_InstLumi->Write();
  REp4_InstLumi->Write();
  REp3_InstLumi->Write();
  REp2_InstLumi->Write();
  REp1_InstLumi->Write();
  REm4_InstLumi->Write();
  REm3_InstLumi->Write();
  REm2_InstLumi->Write();
  REm1_InstLumi->Write();

  hRB1in_InstLumi->Write();
  hRB1out_InstLumi->Write();
  hRB2in_InstLumi->Write();
  hRB2out_InstLumi->Write();
  hRB3_InstLumi->Write();
  hRB4_InstLumi->Write();
  hB_InstLumi->Write();
  hWp2_InstLumi->Write();
  hWp1_InstLumi->Write();
  hW0_InstLumi->Write();
  hWm1_InstLumi->Write();
  hWm2_InstLumi->Write();
  hREp_InstLumi->Write();
  hREm_InstLumi->Write();
  hREp4_InstLumi->Write();
  hREp3_InstLumi->Write();
  hREp2_InstLumi->Write();
  hREp1_InstLumi->Write();
  hREm4_InstLumi->Write();
  hREm3_InstLumi->Write();
  hREm2_InstLumi->Write();
  hREm1_InstLumi->Write();

  cout<<"nentries = "<<nentries<<endl;
}

int readntPlot(){
  nt m;
  m.Loop();
  return 0;
}

