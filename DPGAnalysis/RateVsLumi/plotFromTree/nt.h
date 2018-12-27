//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Nov  9 16:51:43 2018 by ROOT version 6.02/13
// from TTree nt/
// found on file: ../myoutput_rechits_lumi_323525_2Mevt.root
//////////////////////////////////////////////////////////

#ifndef nt_h
#define nt_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class nt {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           nEv;
   Int_t           nLumi;
   Int_t           nBX;
   Int_t           nRun;
   Int_t           Ls;
   Double_t        Lumi;
   Double_t        Rate;
   Double_t        RB1inHits;
   Double_t        areaRB1in;
//rumi
   Double_t        RB1outHits;
   Double_t        areaRB1out;
   Double_t        RB2inHits;
   Double_t        RB2outHits;
   Double_t        RB3Hits;
   Double_t        RB4Hits;
   Double_t        BHits;
   Double_t        Wp2Hits;
   Double_t        Wp1Hits;
   Double_t        W0Hits;
   Double_t        Wm1Hits;
   Double_t        Wm2Hits;
   Double_t        REpHits;
   Double_t        REmHits;
   Double_t        REp1Hits;
   Double_t        REp2Hits;
   Double_t        REp3Hits;
   Double_t        REp4Hits;
   Double_t        REm1Hits;
   Double_t        REm2Hits;
   Double_t        REm3Hits;
   Double_t        REm4Hits;
   Double_t        areaRB2in;
   Double_t        areaRB2out;
   Double_t        areaRB3;
   Double_t        areaRB4;
   Double_t        areaB;
   Double_t        areaWp2;
   Double_t        areaWp1;
   Double_t        areaW0;
   Double_t        areaWm1;
   Double_t        areaWm2;
   Double_t        areaREp;
   Double_t        areaREm;
   Double_t        areaREp1;
   Double_t        areaREp2;
   Double_t        areaREp3;
   Double_t        areaREp4;
   Double_t        areaREm1;
   Double_t        areaREm2;
   Double_t        areaREm3;
   Double_t        areaREm4; 

   // List of branches
   TBranch        *b_nEv;   //!
   TBranch        *b_nLumi;   //!
   TBranch        *b_nBX;   //!
   TBranch        *b_nRun;   //!
   TBranch        *b_Ls;   //!
   TBranch        *b_Lumi;   //!
   TBranch        *b_Rate;   //!
   TBranch        *b_RB1inHits;   //!
   TBranch        *b_areaRB1in;   //!
//rumi
   TBranch        *b_RB1outHits;   //!
   TBranch        *b_areaRB1out;   //!
   TBranch        *b_RB2inHits;
   TBranch        *b_RB2outHits;
   TBranch        *b_RB3Hits;
   TBranch        *b_RB4Hits;
   TBranch        *b_BHits;
   TBranch        *b_Wp2Hits;
   TBranch        *b_Wp1Hits;
   TBranch        *b_W0Hits;
   TBranch        *b_Wm1Hits;
   TBranch        *b_Wm2Hits;
   TBranch        *b_REpHits;
   TBranch        *b_REmHits;
   TBranch        *b_REp1Hits;
   TBranch        *b_REp2Hits;
   TBranch        *b_REp3Hits;
   TBranch        *b_REp4Hits;
   TBranch        *b_REm1Hits;
   TBranch        *b_REm2Hits;
   TBranch        *b_REm3Hits;
   TBranch        *b_REm4Hits;
   TBranch        *b_areaRB2in;
   TBranch        *b_areaRB2out;
   TBranch        *b_areaRB3;
   TBranch        *b_areaRB4;
   TBranch        *b_areaB;
   TBranch        *b_areaWp2;
   TBranch        *b_areaWp1;
   TBranch        *b_areaW0;
   TBranch        *b_areaWm1;
   TBranch        *b_areaWm2;
   TBranch        *b_areaREp;
   TBranch        *b_areaREm;
   TBranch        *b_areaREp1;
   TBranch        *b_areaREp2;
   TBranch        *b_areaREp3;
   TBranch        *b_areaREp4;
   TBranch        *b_areaREm1;
   TBranch        *b_areaREm2;
   TBranch        *b_areaREm3;
   TBranch        *b_areaREm4;

   nt(TTree *tree=0);
   virtual ~nt();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef nt_cxx
nt::nt(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("crabtest.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("crabtest.root");
      }
      TDirectory * dir = (TDirectory*)f->Get("crabtest.root:/demo");
      dir->GetObject("nt",tree);

   }
   Init(tree);
}

nt::~nt()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t nt::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t nt::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void nt::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("nEv", &nEv, &b_nEv);
   fChain->SetBranchAddress("nLumi", &nLumi, &b_nLumi);
   fChain->SetBranchAddress("nBX", &nBX, &b_nBX);
   fChain->SetBranchAddress("nRun", &nRun, &b_nRun);
   fChain->SetBranchAddress("Ls", &Ls, &b_Ls);
   fChain->SetBranchAddress("Lumi", &Lumi, &b_Lumi);
   fChain->SetBranchAddress("Rate", &Rate, &b_Rate);
   fChain->SetBranchAddress("RB1inHits", &RB1inHits, &b_RB1inHits);
   fChain->SetBranchAddress("areaRB1in", &areaRB1in, &b_areaRB1in);
//rumi
   fChain->SetBranchAddress("RB1outHits", &RB1outHits, &b_RB1outHits);
   fChain->SetBranchAddress("areaRB1out", &areaRB1out, &b_areaRB1out);
   fChain->SetBranchAddress("RB2inHits", &RB2inHits, &b_RB2inHits);
   fChain->SetBranchAddress("areaRB2in", &areaRB2in, &b_areaRB2in);
   fChain->SetBranchAddress("RB2outHits", &RB2outHits, &b_RB2outHits);
   fChain->SetBranchAddress("areaRB2out", &areaRB2out, &b_areaRB2out);
   fChain->SetBranchAddress("RB3Hits", &RB3Hits, &b_RB3Hits);
   fChain->SetBranchAddress("areaRB3", &areaRB3, &b_areaRB3);
   fChain->SetBranchAddress("RB4Hits", &RB4Hits, &b_RB4Hits);
   fChain->SetBranchAddress("areaRB4", &areaRB4, &b_areaRB4);
   fChain->SetBranchAddress("Wp2Hits", &Wp2Hits, &b_Wp2Hits);
   fChain->SetBranchAddress("areaWp2", &areaWp2, &b_areaWp2);
   fChain->SetBranchAddress("Wp1Hits", &Wp1Hits, &b_Wp1Hits);
   fChain->SetBranchAddress("areaWp1", &areaWp1, &b_areaWp1);
   fChain->SetBranchAddress("Wm2Hits", &Wm2Hits, &b_Wm2Hits);
   fChain->SetBranchAddress("areaWm2", &areaWm2, &b_areaWm2);
   fChain->SetBranchAddress("Wm1Hits", &Wm1Hits, &b_Wm1Hits);
   fChain->SetBranchAddress("areaWm1", &areaWm1, &b_areaWm1);
   fChain->SetBranchAddress("W0Hits", &W0Hits, &b_W0Hits);
   fChain->SetBranchAddress("areaW0", &areaW0, &b_areaW0);
   fChain->SetBranchAddress("BHits", &BHits, &b_BHits);

   fChain->SetBranchAddress("REm1Hits", &REm1Hits, &b_REm1Hits);
   fChain->SetBranchAddress("areaREm1", &areaREm1, &b_areaREm1);
   fChain->SetBranchAddress("REm2Hits", &REm2Hits, &b_REm2Hits);
   fChain->SetBranchAddress("areaREm2", &areaREm2, &b_areaREm2);
   fChain->SetBranchAddress("REm3Hits", &REm3Hits, &b_REm3Hits);
   fChain->SetBranchAddress("areaREm3", &areaREm3, &b_areaREm3);
   fChain->SetBranchAddress("REm4Hits", &REm4Hits, &b_REm4Hits);
   fChain->SetBranchAddress("areaREm4", &areaREm4, &b_areaREm4);
   fChain->SetBranchAddress("REp1Hits", &REp1Hits, &b_REp1Hits);
   fChain->SetBranchAddress("areaREp1", &areaREp1, &b_areaREp1);
   fChain->SetBranchAddress("REp2Hits", &REp2Hits, &b_REp2Hits);
   fChain->SetBranchAddress("areaREp2", &areaREp2, &b_areaREp2);
   fChain->SetBranchAddress("REp3Hits", &REp3Hits, &b_REp3Hits);
   fChain->SetBranchAddress("areaREp3", &areaREp3, &b_areaREp3);
   fChain->SetBranchAddress("REp4Hits", &REp4Hits, &b_REp4Hits);
   fChain->SetBranchAddress("areaREp4", &areaREp4, &b_areaREp4);
   fChain->SetBranchAddress("REpHits", &REpHits, &b_REpHits);
   fChain->SetBranchAddress("areaREp", &areaREp, &b_areaREp);
   fChain->SetBranchAddress("REmHits", &REmHits, &b_REmHits);
   fChain->SetBranchAddress("areaREm", &areaREm, &b_areaREm);

   Notify();
}

Bool_t nt::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void nt::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t nt::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef nt_cxx
