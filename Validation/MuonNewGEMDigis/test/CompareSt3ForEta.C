#include "TCanvas.h"
#include "TStyle.h"
#include "TFile.h"
#include "TF1.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TGraph.h"
#include "TGraph2D.h"
#include "TGraphAsymmErrors.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TList.h"
#include "TGaxis.h"
#include "TMath.h"
#include <stdio.h>
#include <TROOT.h>
#include "TSystem.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <string>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>


void savePlot(TCanvas*, TString);
void prepareEtaHisto (TH1F* hist, Int_t rebin, Double_t weight, Color_t color);

Double_t myfunction1(Double_t *x, Double_t *par)
{
  Float_t xx =x[0];
  Double_t f = par[0]+par[1]*xx+par[2]*pow(xx,2)+par[3]*pow(xx,3)+par[4]*pow(xx,4)+par[5]*pow(xx,5);
  return f;
}


Double_t myfunction2(Double_t *x1, Double_t *par1)
{
  Float_t xx1 =x1[0];
  Double_t f1 = par1[0]*TMath::Exp(par1[1] * xx1); 
  return f1;
}


// My Branch :: Neutral Bkg
// neuBkg.push_back(899644.0); neuBkg.push_back(-30841.0); neuBkg.push_back(441.28);
// neuBkg.push_back(-3.3405); neuBkg.push_back(0.0140588); neuBkg.push_back(-3.11473e-05); neuBkg.push_back(2.83736e-08);
// My Branch :: Electron Bkg
// eleBkg.push_back(4.68590e+05); eleBkg.push_back(-1.63834e+04); eleBkg.push_back(2.35700e+02);
// eleBkg.push_back(-1.77706e+00); eleBkg.push_back(7.39960e-03); eleBkg.push_back(-1.61448e-05); eleBkg.push_back(1.44368e-08);

// 76X
// ME0ModNeuBkgParam0 = 5.69e+06;
// ME0ModNeuBkgParam1 = -293334;
// ME0ModNeuBkgParam2 = 6279.6;
// ME0ModNeuBkgParam3 = -71.2928;
// ME0ModNeuBkgParam4 = 0.452244;
// ME0ModNeuBkgParam5 = -0.0015191;
// ME0ModNeuBkgParam6 = 2.1106e-06;
// ME0ModElecBkgParam0 = 3.77712e+06;
// ME0ModElecBkgParam1 = -199280;
// ME0ModElecBkgParam2 = 4340.69;
// ME0ModElecBkgParam3 = -49.922;
// ME0ModElecBkgParam4 = 0.319699;
// ME0ModElecBkgParam5 = -0.00108113;
// ME0ModElecBkgParam6 = 1.50889e-06;


void CompareSt3ForEta(const TString input = "GEMDigis_SingleMuPt100.root", const int nbin=16)
 {

    cout<<" New Eta loop "<<endl; 
    TH1::SetDefaultSumw2();
    
    TFile* file = TFile::Open(input);
    TString tDir = "DQMData/MuonGEMDigisV/GEMDigiTask";
    TString events    = tDir+"/num_events";
    TString total     = tDir+"/NoPrompt/strip_dg_eta_st3_NoPrompt";
    TString electrons = tDir+"/NoPrompt/strip_dg_eta_st3_NoPrompt_e";
    TString neutrons  = tDir+"/NoPrompt/strip_dg_eta_st3_NoPrompt_n";
    TString gammas    = tDir+"/NoPrompt/strip_dg_eta_st3_NoPrompt_g";
    
    TH1F* totalBkg     = (TH1F*) file->Get(total);
    TH1F* electronsBkg = (TH1F*) file->Get(electrons);
    TH1F* neutronsBkg  = (TH1F*) file->Get(neutrons);
    TH1F* gammasBkg    = (TH1F*) file->Get(gammas);
    TH1F* numEvents    = (TH1F*) file->Get(events);
    
    Double_t NumEvents = numEvents->Integral();
    Double_t weight    = NumEvents*9*25e-09;
    
    int rebin = (electronsBkg->GetNbinsX())/nbin;
    prepareEtaHisto(electronsBkg,rebin,weight,kRed+1);
    prepareEtaHisto(neutronsBkg,rebin,weight,kOrange+1);
    prepareEtaHisto(gammasBkg,rebin,weight,kGreen+2);
    
    TH1F* neutralBkg = (TH1F*) gammasBkg->Clone();
    neutralBkg->Add(neutronsBkg);
    neutralBkg->SetMarkerColor(kBlack);
    neutralBkg->SetLineColor(kBlack);
    
    
    TLegend *leg_hits = new TLegend(0.10,0.70,0.35,0.90);
    leg_hits->SetFillColor(0);
    leg_hits->SetHeader("GEM St3 Background Hits");
    leg_hits->AddEntry(neutralBkg,"n/#gamma Bkg","l");
    leg_hits->AddEntry(gammasBkg,"#gamma Bkg","l");
    leg_hits->AddEntry(electronsBkg,"e^{#pm} Bkg ","l");
    leg_hits->AddEntry(neutronsBkg,"n Bkg","l");
    
    TCanvas *c_noPrompt = new TCanvas("NoPrompt_Eta_Rate","NoPrompt_Rate",600,600);
    c_noPrompt->cd();
    c_noPrompt->SetLogy();
    c_noPrompt->SetTicks(1,1);
    c_noPrompt->SetGrid(1,1);
    c_noPrompt->SetTitle("GEM St3 Neutron Background Hits");
    neutralBkg->Draw("9p0e1TEXT0");
    gammasBkg->Draw("9samep0e1");
    electronsBkg->Draw("9p0e1sameTEXT0");
    neutronsBkg->Draw("9p0e1same");
    leg_hits->Draw();
    
    //double minHist = (neutronsBkg->GetMinimum())*0.8;
    
    neutralBkg->GetYaxis()->SetRangeUser(1.001,5E3);
    neutralBkg->GetYaxis()->SetTitleOffset(1.35);
    neutralBkg->GetYaxis()->SetTitle("Rate (Hz/[ Strip ])");
    neutralBkg->GetXaxis()->SetTitle("|#eta|");
    neutralBkg->SetTitle("Digi Backgroud Rate per Stirp");
    
    c_noPrompt->Update();
    //savePlot(c_noPrompt,"NoPromptHitsRate");
    

}


void savePlot(TCanvas * c, TString name) {
  // c->SaveAs(name+".root");
  c->SaveAs(name+".png");
  c->SaveAs(name+".eps");
  gSystem->Exec("epstopdf "+name+".eps");
  std::cout<<"Plots saved"<<std::endl;
}


void prepareEtaHisto (TH1F* hist, Int_t rebin, Double_t weight, Color_t color){
    hist->Rebin(rebin);
    hist->SetStats(kFALSE);
    hist->SetLineColor(color);
    hist->SetMarkerColor(color);
    hist->SetMarkerStyle(kFullTriangleDown);
    hist->SetMarkerSize(0.7);
    std::cout << " Histogram :  "<<hist->GetName() << " -------------  "<<std::endl;
    for (Int_t bin = 1; bin<=hist->GetNbinsX();++bin){
        
        Double_t Area     = 18*2*2*768;
//        std::cout << "\n #bin = "<<bin
//        <<"\n\tArea = "<<Area<<" Weight = "<< Area*weight
//        <<"\n\tBinContent = "<<hist->GetBinContent(bin)<<"  SetBinContent = "<<(hist->GetBinContent(bin))/(Area*weight)<<std::endl;
        hist->SetBinContent(bin,(hist->GetBinContent(bin))/(Area*weight));
        
}
}

