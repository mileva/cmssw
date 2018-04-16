// -*- C++ -*-
//
// Package:    myNoiseScan/MyNoiseScan
// Class:      MyNoiseScan
// 
/**\class MyNoiseScan MyNoiseScan.cc myNoiseScan/MyNoiseScan/plugins/MyNoiseScan.cc

 Description: [one line class summary]

 Implementation:
 [Notes on implementation]
 */
//
// Original Author:  Roumyana Mileva Hadjiiska
//         Created:  Tue, 10 Apr 2018 08:28:30 GMT
//
//

// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/MuonDetId/interface/RPCDetId.h"
#include "Geometry/RPCGeometry/interface/RPCRoll.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "TH1F.h"
#include "TH2F.h"

#include "TMath.h"
#include "TGraphErrors.h"
#include "TGraph.h"
#include "TCanvas.h"
//
// class declaration
//

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<> and also remove the line from
// constructor "usesResource("TFileService");"
// This will improve performance in multithreaded jobs.

class MyNoiseScan: public edm::one::EDAnalyzer<edm::one::SharedResources>
{
public:
  explicit MyNoiseScan(const edm::ParameterSet&);
  ~MyNoiseScan();

  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

private:
  virtual void beginJob() override;
  virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
  virtual void endJob() override;

  // ----------member data ---------------------------
//  std::string myInputFile_;
  std::string myMapIdName_;
  bool debug_;
  bool doNoiseMagnet_;
  bool doNoiseNoMagnet_;

  struct subject
  {
    std::string name;
//    uint32_t id;
    RPCDetId id;
    std::map<double, double> pairHvRate;
  };

//analysis
  TH1F *rateBarrelMagnet8800;
  TH1F *rateEndcapPosMagnet8800;
  TH1F *rateEndcapNegMagnet8800;

  TH1F *rateBarrelNoMagnet8800;
  TH1F *rateEndcapPosNoMagnet8800;
  TH1F *rateEndcapNegNoMagnet8800;

  TH1F *rateBarrelMagnet9000;
  TH1F *rateEndcapPosMagnet9000;
  TH1F *rateEndcapNegMagnet9000;

  TH1F *rateBarrelNoMagnet9000;
  TH1F *rateEndcapPosNoMagnet9000;
  TH1F *rateEndcapNegNoMagnet9000;

  TH1F *rateBarrelMagnet9100;
  TH1F *rateEndcapPosMagnet9100;
  TH1F *rateEndcapNegMagnet9100;

  TH1F *rateBarrelNoMagnet9100;
  TH1F *rateEndcapPosNoMagnet9100;
  TH1F *rateEndcapNegNoMagnet9100;

  TH1F *rateBarrelMagnet9200;
  TH1F *rateEndcapPosMagnet9200;
  TH1F *rateEndcapNegMagnet9200;

  TH1F *rateBarrelNoMagnet9200;
  TH1F *rateEndcapPosNoMagnet9200;
  TH1F *rateEndcapNegNoMagnet9200;

  TH1F *rateBarrelMagnet9300;
  TH1F *rateEndcapPosMagnet9300;
  TH1F *rateEndcapNegMagnet9300;

  TH1F *rateBarrelNoMagnet9300;
  TH1F *rateEndcapPosNoMagnet9300;
  TH1F *rateEndcapNegNoMagnet9300;

  TH1F *rateBarrelMagnet9400;
  TH1F *rateEndcapPosMagnet9400;
  TH1F *rateEndcapNegMagnet9400;

  TH1F *rateBarrelNoMagnet9400;
  TH1F *rateEndcapPosNoMagnet9400;
  TH1F *rateEndcapNegNoMagnet9400;

  TH1F *rateBarrelMagnet9500;
  TH1F *rateEndcapPosMagnet9500;
  TH1F *rateEndcapNegMagnet9500;

  TH1F *rateBarrelNoMagnet9500;
  TH1F *rateEndcapPosNoMagnet9500;
  TH1F *rateEndcapNegNoMagnet9500;

  TH1F *rateBarrelMagnet9600;
  TH1F *rateEndcapPosMagnet9600;
  TH1F *rateEndcapNegMagnet9600;

  TH1F *rateBarrelNoMagnet9600;
  TH1F *rateEndcapPosNoMagnet9600;
  TH1F *rateEndcapNegNoMagnet9600;

  TH1F *rateBarrelMagnet9700;
  TH1F *rateEndcapPosMagnet9700;
  TH1F *rateEndcapNegMagnet9700;

  TH1F *rateBarrelNoMagnet9700;
  TH1F *rateEndcapPosNoMagnet9700;
  TH1F *rateEndcapNegNoMagnet9700;

  TH1F *rateEndcapPosMagnet9800;
  TH1F *rateEndcapNegMagnet9800;

  TH1F *rateEndcapPosNoMagnet9800;
  TH1F *rateEndcapNegNoMagnet9800;



  TGraphErrors *barrelScanMagnet;
  TGraphErrors *EndcapPosScanMagnet;
  TGraphErrors *EndcapNegScanMagnet;

  TGraphErrors *barrelScanNoMagnet;
  TGraphErrors *EndcapPosScanNoMagnet;
  TGraphErrors *EndcapNegScanNoMagnet;

  TGraphErrors *deltabarrel;
  TGraphErrors *deltaEndcapPos;
  TGraphErrors *deltaEndcapNeg;


//  std::ofstream noiseData;

};

MyNoiseScan::MyNoiseScan(const edm::ParameterSet& iConfig)

{
//  myInputFile_ = iConfig.getParameter < std::string > ("myInputFile");
  myMapIdName_ = iConfig.getParameter < std::string > ("myMapIdName");
  debug_ = iConfig.getParameter<bool>("debug");
  doNoiseMagnet_ = iConfig.getParameter<bool>("doNoiseMagnet");
  doNoiseNoMagnet_ = iConfig.getParameter<bool>("doNoiseNoMagnet");
//  usesResource("TFileService");

}

MyNoiseScan::~MyNoiseScan()
{
}

//
// member functions
//

// ------------ method called for each event  ------------
void MyNoiseScan::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace std;
  fstream myMapStream;
  uint32_t myId;
  string myName;
  std::map<string, uint32_t> mapIdName;
  vector<subject> sub;
  vector<subject> subNoMagnet;
  std::map<double, double> tempMap;

  myMapStream.open(myMapIdName_, ios::in);
  for (; myMapStream >> myName >> myId;)
  {
#ifdef debug_
    cout << myId << "\t"<< myName << endl;
#endif
    mapIdName.insert(std::pair<string, uint32_t>(myName, myId));
  }
  myMapStream.close();

  double rate;
  double hvpoint;
  string rollName;
  vector<double> virate;
  vector<double> vihvpoint;
  vector<string> virollName;

  fstream f_input;
//  TCanvas *c2 = new TCanvas("c2", "c2", 600., 600);
  if (doNoiseMagnet_)
  {
    int justcounter = 0;
    f_input.open("data/noisemagnet/allNoise_noRE11.txt", ios::in);
    for (; f_input >> rollName >> hvpoint >> rate;)
    {
      justcounter++;
#ifdef debug_
      std::cout << rollName << "\t" << hvpoint << "\t" << rate << std::endl;
#endif
      vihvpoint.push_back(hvpoint);
      virollName.push_back(rollName);
      virate.push_back(rate);

      tempMap.insert(std::pair<double, double>(hvpoint, rate));

      RPCDetId myrpcid(mapIdName[rollName]);
      if (justcounter % 10 == 0)
      {
        subject subObj;
        subObj.name = rollName;
//        RPCDetId tempid(myrpcid);
        subObj.id = myrpcid;
        subObj.pairHvRate = tempMap;
        sub.push_back(subObj);
        tempMap.clear();
      }
    }
    f_input.close();

  if(debug_) std::cout << "sub.size() = " << sub.size() << std::endl;
//  std::map<double, double>::iterator iter;
  for (unsigned int i = 0; i < sub.size(); i++)
  {
    if(debug_) std::cout << sub[i].name << "\t" << sub[i].id << "\tmap size = " << (sub[i].pairHvRate).size()<< "\t" << (sub[i].pairHvRate)[8800] << std::endl;
//    for (iter = (sub[i].pairHvRate).begin(); iter != (sub[i].pairHvRate).end(); ++iter)
      if((sub[i].id).region()==0)
      {
        rateBarrelMagnet8800->Fill((sub[i].pairHvRate)[8800]);
        rateBarrelMagnet9000->Fill((sub[i].pairHvRate)[9000]);
        rateBarrelMagnet9100->Fill((sub[i].pairHvRate)[9100]);
        rateBarrelMagnet9200->Fill((sub[i].pairHvRate)[9200]);
        rateBarrelMagnet9300->Fill((sub[i].pairHvRate)[9300]);
        rateBarrelMagnet9400->Fill((sub[i].pairHvRate)[9400]);
        rateBarrelMagnet9500->Fill((sub[i].pairHvRate)[9500]);
        rateBarrelMagnet9600->Fill((sub[i].pairHvRate)[9600]);
        rateBarrelMagnet9700->Fill((sub[i].pairHvRate)[9700]);
     }
      if((sub[i].id).region()==+1)
      {
        rateEndcapPosMagnet8800->Fill((sub[i].pairHvRate)[8800]);
        rateEndcapPosMagnet9000->Fill((sub[i].pairHvRate)[9000]);
        rateEndcapPosMagnet9100->Fill((sub[i].pairHvRate)[9100]);
        rateEndcapPosMagnet9200->Fill((sub[i].pairHvRate)[9200]);
        rateEndcapPosMagnet9300->Fill((sub[i].pairHvRate)[9300]);
        rateEndcapPosMagnet9400->Fill((sub[i].pairHvRate)[9400]);
        rateEndcapPosMagnet9500->Fill((sub[i].pairHvRate)[9500]);
        rateEndcapPosMagnet9600->Fill((sub[i].pairHvRate)[9600]);
        rateEndcapPosMagnet9700->Fill((sub[i].pairHvRate)[9700]);
        rateEndcapPosMagnet9800->Fill((sub[i].pairHvRate)[9800]);
     }
      if((sub[i].id).region()==-1)
      {
        rateEndcapNegMagnet8800->Fill((sub[i].pairHvRate)[8800]);
        rateEndcapNegMagnet9000->Fill((sub[i].pairHvRate)[9000]);
        rateEndcapNegMagnet9100->Fill((sub[i].pairHvRate)[9100]);
        rateEndcapNegMagnet9200->Fill((sub[i].pairHvRate)[9200]);
        rateEndcapNegMagnet9300->Fill((sub[i].pairHvRate)[9300]);
        rateEndcapNegMagnet9400->Fill((sub[i].pairHvRate)[9400]);
        rateEndcapNegMagnet9500->Fill((sub[i].pairHvRate)[9500]);
        rateEndcapNegMagnet9600->Fill((sub[i].pairHvRate)[9600]);
        rateEndcapNegMagnet9700->Fill((sub[i].pairHvRate)[9700]);
        rateEndcapNegMagnet9800->Fill((sub[i].pairHvRate)[9800]);
     }
  }
}//end noise with magnet

  if (doNoiseNoMagnet_)
  {
    int justcounter = 0;
    f_input.open("data/noisenomagnet/allNoiseNomagnet_noRE11.txt", ios::in);
    for (; f_input >> rollName >> hvpoint >> rate;)
    {
      justcounter++;
#ifdef debug_
      std::cout << rollName << "\t" << hvpoint << "\t" << rate << std::endl;
#endif
      tempMap.insert(std::pair<double, double>(hvpoint, rate));

      RPCDetId myrpcid(mapIdName[rollName]);
      if (justcounter % 10 == 0)
      {
        subject subObj;
        subObj.name = rollName;
//        RPCDetId tempid(myrpcid);
        subObj.id = myrpcid;
        subObj.pairHvRate = tempMap;
        subNoMagnet.push_back(subObj);
        tempMap.clear();
      }
    }
    f_input.close();

  if(debug_) std::cout << "sub.size() = " << subNoMagnet.size() << std::endl;
//  std::map<double, double>::iterator iter;
  for (unsigned int i = 0; i < subNoMagnet.size(); i++)
  {
    if(debug_) std::cout << subNoMagnet[i].name << "\t" << subNoMagnet[i].id << "\tmap size = " << (subNoMagnet[i].pairHvRate).size()<< "\t" << (subNoMagnet[i].pairHvRate)[8800] << std::endl;
//    for (iter = (subNoMagnet[i].pairHvRate).begin(); iter != (subNoMagnet[i].pairHvRate).end(); ++iter)
      if((subNoMagnet[i].id).region()==0)
      {
        rateBarrelNoMagnet8800->Fill((subNoMagnet[i].pairHvRate)[8800]);
        rateBarrelNoMagnet9000->Fill((subNoMagnet[i].pairHvRate)[9000]);
        rateBarrelNoMagnet9100->Fill((subNoMagnet[i].pairHvRate)[9100]);
        rateBarrelNoMagnet9200->Fill((subNoMagnet[i].pairHvRate)[9200]);
        rateBarrelNoMagnet9300->Fill((subNoMagnet[i].pairHvRate)[9300]);
        rateBarrelNoMagnet9400->Fill((subNoMagnet[i].pairHvRate)[9400]);
        rateBarrelNoMagnet9500->Fill((subNoMagnet[i].pairHvRate)[9500]);
        rateBarrelNoMagnet9600->Fill((subNoMagnet[i].pairHvRate)[9600]);
        rateBarrelNoMagnet9700->Fill((subNoMagnet[i].pairHvRate)[9700]);
     }
      if((subNoMagnet[i].id).region()==+1)
      {
        rateEndcapPosNoMagnet8800->Fill((subNoMagnet[i].pairHvRate)[8800]);
        rateEndcapPosNoMagnet9000->Fill((subNoMagnet[i].pairHvRate)[9000]);
        rateEndcapPosNoMagnet9100->Fill((subNoMagnet[i].pairHvRate)[9100]);
        rateEndcapPosNoMagnet9200->Fill((subNoMagnet[i].pairHvRate)[9200]);
        rateEndcapPosNoMagnet9300->Fill((subNoMagnet[i].pairHvRate)[9300]);
        rateEndcapPosNoMagnet9400->Fill((subNoMagnet[i].pairHvRate)[9400]);
        rateEndcapPosNoMagnet9500->Fill((subNoMagnet[i].pairHvRate)[9500]);
        rateEndcapPosNoMagnet9600->Fill((subNoMagnet[i].pairHvRate)[9600]);
        rateEndcapPosNoMagnet9700->Fill((subNoMagnet[i].pairHvRate)[9700]);
        rateEndcapPosNoMagnet9800->Fill((subNoMagnet[i].pairHvRate)[9800]);
     }
      if((subNoMagnet[i].id).region()==-1)
      {
        rateEndcapNegNoMagnet8800->Fill((subNoMagnet[i].pairHvRate)[8800]);
        rateEndcapNegNoMagnet9000->Fill((subNoMagnet[i].pairHvRate)[9000]);
        rateEndcapNegNoMagnet9100->Fill((subNoMagnet[i].pairHvRate)[9100]);
        rateEndcapNegNoMagnet9200->Fill((subNoMagnet[i].pairHvRate)[9200]);
        rateEndcapNegNoMagnet9300->Fill((subNoMagnet[i].pairHvRate)[9300]);
        rateEndcapNegNoMagnet9400->Fill((subNoMagnet[i].pairHvRate)[9400]);
        rateEndcapNegNoMagnet9500->Fill((subNoMagnet[i].pairHvRate)[9500]);
        rateEndcapNegNoMagnet9600->Fill((subNoMagnet[i].pairHvRate)[9600]);
        rateEndcapNegNoMagnet9700->Fill((subNoMagnet[i].pairHvRate)[9700]);
        rateEndcapNegNoMagnet9800->Fill((subNoMagnet[i].pairHvRate)[9800]);
     }
  }
}
//end noise without magnet

if(doNoiseMagnet_ & doNoiseNoMagnet_)
{
rateBarrelMagnet8800->GetXaxis()->SetRangeUser(0.0005, 2);
barrelScanMagnet-> SetPoint (1, 8800, rateBarrelMagnet8800->GetMean());
rateBarrelMagnet9000->GetXaxis()->SetRangeUser(0.0005, 2);
barrelScanMagnet-> SetPoint (2, 9000, rateBarrelMagnet9000->GetMean());
rateBarrelMagnet9100->GetXaxis()->SetRangeUser(0.0005, 2);
barrelScanMagnet-> SetPoint (3, 9100, rateBarrelMagnet9100->GetMean());
rateBarrelMagnet9200->GetXaxis()->SetRangeUser(0.0005, 2);
barrelScanMagnet-> SetPoint (4, 9200, rateBarrelMagnet9200->GetMean());
rateBarrelMagnet9300->GetXaxis()->SetRangeUser(0.0005, 2);
barrelScanMagnet-> SetPoint (5, 9300, rateBarrelMagnet9300->GetMean());
rateBarrelMagnet9400->GetXaxis()->SetRangeUser(0.0005, 2);
barrelScanMagnet-> SetPoint (6, 9400, rateBarrelMagnet9400->GetMean());
rateBarrelMagnet9500->GetXaxis()->SetRangeUser(0.0005, 2);
barrelScanMagnet-> SetPoint (7, 9500, rateBarrelMagnet9500->GetMean());
rateBarrelMagnet9600->GetXaxis()->SetRangeUser(0.0005, 2);
barrelScanMagnet-> SetPoint (8, 9600, rateBarrelMagnet9600->GetMean());
rateBarrelMagnet9700->GetXaxis()->SetRangeUser(0.0005, 2);
barrelScanMagnet-> SetPoint (9, 9700, rateBarrelMagnet9700->GetMean());

rateEndcapPosMagnet8800->GetXaxis()->SetRangeUser(0.0005, 2);
EndcapPosScanMagnet-> SetPoint (1, 8800, rateEndcapPosMagnet8800->GetMean());
rateEndcapPosMagnet9000->GetXaxis()->SetRangeUser(0.0005, 2);
EndcapPosScanMagnet-> SetPoint (2, 9000, rateEndcapPosMagnet9000->GetMean());
rateEndcapPosMagnet9100->GetXaxis()->SetRangeUser(0.0005, 2);
EndcapPosScanMagnet-> SetPoint (3, 9100, rateEndcapPosMagnet9100->GetMean());
rateEndcapPosMagnet9200->GetXaxis()->SetRangeUser(0.0005, 2);
EndcapPosScanMagnet-> SetPoint (4, 9200, rateEndcapPosMagnet9200->GetMean());
rateEndcapPosMagnet9300->GetXaxis()->SetRangeUser(0.0005, 2);
EndcapPosScanMagnet-> SetPoint (5, 9300, rateEndcapPosMagnet9300->GetMean());
rateEndcapPosMagnet9400->GetXaxis()->SetRangeUser(0.0005, 2);
EndcapPosScanMagnet-> SetPoint (6, 9400, rateEndcapPosMagnet9400->GetMean());
rateEndcapPosMagnet9500->GetXaxis()->SetRangeUser(0.0005, 2);
EndcapPosScanMagnet-> SetPoint (7, 9500, rateEndcapPosMagnet9500->GetMean());
rateEndcapPosMagnet9600->GetXaxis()->SetRangeUser(0.0005, 2);
EndcapPosScanMagnet-> SetPoint (8, 9600, rateEndcapPosMagnet9600->GetMean());
rateEndcapPosMagnet9700->GetXaxis()->SetRangeUser(0.0005, 2);
EndcapPosScanMagnet-> SetPoint (9, 9700, rateEndcapPosMagnet9700->GetMean());
rateEndcapPosMagnet9800->GetXaxis()->SetRangeUser(0.0005, 2);
EndcapPosScanMagnet-> SetPoint (10, 9800, rateEndcapPosMagnet9800->GetMean());

rateEndcapNegMagnet8800->GetXaxis()->SetRangeUser(0.0005, 2);
EndcapNegScanMagnet-> SetPoint (1, 8800, rateEndcapNegMagnet8800->GetMean());
rateEndcapNegMagnet9000->GetXaxis()->SetRangeUser(0.0005, 2);
EndcapNegScanMagnet-> SetPoint (2, 9000, rateEndcapNegMagnet9000->GetMean());
rateEndcapNegMagnet9100->GetXaxis()->SetRangeUser(0.0005, 2);
EndcapNegScanMagnet-> SetPoint (3, 9100, rateEndcapNegMagnet9100->GetMean());
rateEndcapNegMagnet9200->GetXaxis()->SetRangeUser(0.0005, 2);
EndcapNegScanMagnet-> SetPoint (4, 9200, rateEndcapNegMagnet9200->GetMean());
rateEndcapNegMagnet9300->GetXaxis()->SetRangeUser(0.0005, 2);
EndcapNegScanMagnet-> SetPoint (5, 9300, rateEndcapNegMagnet9300->GetMean());
rateEndcapNegMagnet9400->GetXaxis()->SetRangeUser(0.0005, 2);
EndcapNegScanMagnet-> SetPoint (6, 9400, rateEndcapNegMagnet9400->GetMean());
rateEndcapNegMagnet9500->GetXaxis()->SetRangeUser(0.0005, 2);
EndcapNegScanMagnet-> SetPoint (7, 9500, rateEndcapNegMagnet9500->GetMean());
rateEndcapNegMagnet9600->GetXaxis()->SetRangeUser(0.0005, 2);
EndcapNegScanMagnet-> SetPoint (8, 9600, rateEndcapNegMagnet9600->GetMean());
rateEndcapNegMagnet9700->GetXaxis()->SetRangeUser(0.0005, 2);
EndcapNegScanMagnet-> SetPoint (9, 9700, rateEndcapNegMagnet9700->GetMean());
rateEndcapNegMagnet9800->GetXaxis()->SetRangeUser(0.0005, 2);
EndcapNegScanMagnet-> SetPoint (10, 9800, rateEndcapNegMagnet9800->GetMean());

rateBarrelNoMagnet8800->GetXaxis()->SetRangeUser(0.0005, 2);
barrelScanNoMagnet-> SetPoint (1, 8800, rateBarrelNoMagnet8800->GetMean());
rateBarrelNoMagnet9000->GetXaxis()->SetRangeUser(0.0005, 2);
barrelScanNoMagnet-> SetPoint (2, 9000, rateBarrelNoMagnet9000->GetMean());
rateBarrelNoMagnet9100->GetXaxis()->SetRangeUser(0.0005, 2);
barrelScanNoMagnet-> SetPoint (3, 9100, rateBarrelNoMagnet9100->GetMean());
rateBarrelNoMagnet9200->GetXaxis()->SetRangeUser(0.0005, 2);
barrelScanNoMagnet-> SetPoint (4, 9200, rateBarrelNoMagnet9200->GetMean());
rateBarrelNoMagnet9300->GetXaxis()->SetRangeUser(0.0005, 2);
barrelScanNoMagnet-> SetPoint (5, 9300, rateBarrelNoMagnet9300->GetMean());
rateBarrelNoMagnet9400->GetXaxis()->SetRangeUser(0.0005, 2);
barrelScanNoMagnet-> SetPoint (6, 9400, rateBarrelNoMagnet9400->GetMean());
rateBarrelNoMagnet9500->GetXaxis()->SetRangeUser(0.0005, 2);
barrelScanNoMagnet-> SetPoint (7, 9500, rateBarrelNoMagnet9500->GetMean());
rateBarrelNoMagnet9600->GetXaxis()->SetRangeUser(0.0005, 2);
barrelScanNoMagnet-> SetPoint (8, 9600, rateBarrelNoMagnet9600->GetMean());
rateBarrelNoMagnet9700->GetXaxis()->SetRangeUser(0.0005, 2);
barrelScanNoMagnet-> SetPoint (9, 9700, rateBarrelNoMagnet9700->GetMean());

rateEndcapPosNoMagnet8800->GetXaxis()->SetRangeUser(0.0005, 2);
EndcapPosScanNoMagnet-> SetPoint (1, 8800, rateEndcapPosNoMagnet8800->GetMean());
rateEndcapPosNoMagnet9000->GetXaxis()->SetRangeUser(0.0005, 2);
EndcapPosScanNoMagnet-> SetPoint (2, 9000, rateEndcapPosNoMagnet9000->GetMean());
rateEndcapPosNoMagnet9100->GetXaxis()->SetRangeUser(0.0005, 2);
EndcapPosScanNoMagnet-> SetPoint (3, 9100, rateEndcapPosNoMagnet9100->GetMean());
rateEndcapPosNoMagnet9200->GetXaxis()->SetRangeUser(0.0005, 2);
EndcapPosScanNoMagnet-> SetPoint (4, 9200, rateEndcapPosNoMagnet9200->GetMean());
rateEndcapPosNoMagnet9300->GetXaxis()->SetRangeUser(0.0005, 2);
EndcapPosScanNoMagnet-> SetPoint (5, 9300, rateEndcapPosNoMagnet9300->GetMean());
rateEndcapPosNoMagnet9400->GetXaxis()->SetRangeUser(0.0005, 2);
EndcapPosScanNoMagnet-> SetPoint (6, 9400, rateEndcapPosNoMagnet9400->GetMean());
rateEndcapPosNoMagnet9500->GetXaxis()->SetRangeUser(0.0005, 2);
EndcapPosScanNoMagnet-> SetPoint (7, 9500, rateEndcapPosNoMagnet9500->GetMean());
rateEndcapPosNoMagnet9600->GetXaxis()->SetRangeUser(0.0005, 2);
EndcapPosScanNoMagnet-> SetPoint (8, 9600, rateEndcapPosNoMagnet9600->GetMean());
rateEndcapPosNoMagnet9700->GetXaxis()->SetRangeUser(0.0005, 2);
EndcapPosScanNoMagnet-> SetPoint (9, 9700, rateEndcapPosNoMagnet9700->GetMean());
rateEndcapPosNoMagnet9800->GetXaxis()->SetRangeUser(0.0005, 2);
EndcapPosScanNoMagnet-> SetPoint (10, 9800, rateEndcapPosNoMagnet9800->GetMean());

rateEndcapNegNoMagnet8800->GetXaxis()->SetRangeUser(0.0005, 2);
EndcapNegScanNoMagnet-> SetPoint (1, 8800, rateEndcapNegNoMagnet8800->GetMean());
rateEndcapNegNoMagnet9000->GetXaxis()->SetRangeUser(0.0005, 2);
EndcapNegScanNoMagnet-> SetPoint (2, 9000, rateEndcapNegNoMagnet9000->GetMean());
rateEndcapNegNoMagnet9100->GetXaxis()->SetRangeUser(0.0005, 2);
EndcapNegScanNoMagnet-> SetPoint (3, 9100, rateEndcapNegNoMagnet9100->GetMean());
rateEndcapNegNoMagnet9200->GetXaxis()->SetRangeUser(0.0005, 2);
EndcapNegScanNoMagnet-> SetPoint (4, 9200, rateEndcapNegNoMagnet9200->GetMean());
rateEndcapNegNoMagnet9300->GetXaxis()->SetRangeUser(0.0005, 2);
EndcapNegScanNoMagnet-> SetPoint (5, 9300, rateEndcapNegNoMagnet9300->GetMean());
rateEndcapNegNoMagnet9400->GetXaxis()->SetRangeUser(0.0005, 2);
EndcapNegScanNoMagnet-> SetPoint (6, 9400, rateEndcapNegNoMagnet9400->GetMean());
rateEndcapNegNoMagnet9500->GetXaxis()->SetRangeUser(0.0005, 2);
EndcapNegScanNoMagnet-> SetPoint (7, 9500, rateEndcapNegNoMagnet9500->GetMean());
rateEndcapNegNoMagnet9600->GetXaxis()->SetRangeUser(0.0005, 2);
EndcapNegScanNoMagnet-> SetPoint (8, 9600, rateEndcapNegNoMagnet9600->GetMean());
rateEndcapNegNoMagnet9700->GetXaxis()->SetRangeUser(0.0005, 2);
EndcapNegScanNoMagnet-> SetPoint (9, 9700, rateEndcapNegNoMagnet9700->GetMean());
rateEndcapNegNoMagnet9800->GetXaxis()->SetRangeUser(0.0005, 2);
EndcapNegScanNoMagnet-> SetPoint (10, 9800, rateEndcapNegNoMagnet9800->GetMean());

deltabarrel-> SetPoint (1, 8800, (rateBarrelNoMagnet8800->GetMean() - rateBarrelMagnet8800->GetMean()));
deltabarrel-> SetPoint (2, 9000, (rateBarrelNoMagnet9000->GetMean() - rateBarrelMagnet9000->GetMean()));
deltabarrel-> SetPoint (3, 9100, (rateBarrelNoMagnet9100->GetMean() - rateBarrelMagnet9100->GetMean()));
deltabarrel-> SetPoint (4, 9200, (rateBarrelNoMagnet9200->GetMean() - rateBarrelMagnet9200->GetMean()));
deltabarrel-> SetPoint (5, 9300, (rateBarrelNoMagnet9300->GetMean() - rateBarrelMagnet9300->GetMean()));
deltabarrel-> SetPoint (6, 9400, (rateBarrelNoMagnet9400->GetMean() - rateBarrelMagnet9400->GetMean()));
deltabarrel-> SetPoint (7, 9500, (rateBarrelNoMagnet9500->GetMean() - rateBarrelMagnet9500->GetMean()));
deltabarrel-> SetPoint (8, 9600, (rateBarrelNoMagnet9600->GetMean() - rateBarrelMagnet9600->GetMean()));
deltabarrel-> SetPoint (9, 9700, (rateBarrelNoMagnet9700->GetMean() - rateBarrelMagnet9700->GetMean()));

deltaEndcapPos-> SetPoint (1, 8800, (rateEndcapPosNoMagnet8800->GetMean() - rateEndcapPosMagnet8800->GetMean()));
deltaEndcapPos-> SetPoint (2, 9000, (rateEndcapPosNoMagnet9000->GetMean() - rateEndcapPosMagnet9000->GetMean()));
deltaEndcapPos-> SetPoint (3, 9100, (rateEndcapPosNoMagnet9100->GetMean() - rateEndcapPosMagnet9100->GetMean()));
deltaEndcapPos-> SetPoint (4, 9200, (rateEndcapPosNoMagnet9200->GetMean() - rateEndcapPosMagnet9200->GetMean()));
deltaEndcapPos-> SetPoint (5, 9300, (rateEndcapPosNoMagnet9300->GetMean() - rateEndcapPosMagnet9300->GetMean()));
deltaEndcapPos-> SetPoint (6, 9400, (rateEndcapPosNoMagnet9400->GetMean() - rateEndcapPosMagnet9400->GetMean()));
deltaEndcapPos-> SetPoint (7, 9500, (rateEndcapPosNoMagnet9500->GetMean() - rateEndcapPosMagnet9500->GetMean()));
deltaEndcapPos-> SetPoint (8, 9600, (rateEndcapPosNoMagnet9600->GetMean() - rateEndcapPosMagnet9600->GetMean()));
deltaEndcapPos-> SetPoint (9, 9700, (rateEndcapPosNoMagnet9700->GetMean() - rateEndcapPosMagnet9700->GetMean()));
deltaEndcapPos-> SetPoint (10, 9800, (rateEndcapPosNoMagnet9800->GetMean() - rateEndcapPosMagnet9800->GetMean()));

deltaEndcapNeg-> SetPoint (1, 8800, (rateEndcapNegNoMagnet8800->GetMean() - rateEndcapNegMagnet8800->GetMean()));
deltaEndcapNeg-> SetPoint (2, 9000, (rateEndcapNegNoMagnet9000->GetMean() - rateEndcapNegMagnet9000->GetMean()));
deltaEndcapNeg-> SetPoint (3, 9100, (rateEndcapNegNoMagnet9100->GetMean() - rateEndcapNegMagnet9100->GetMean()));
deltaEndcapNeg-> SetPoint (4, 9200, (rateEndcapNegNoMagnet9200->GetMean() - rateEndcapNegMagnet9200->GetMean()));
deltaEndcapNeg-> SetPoint (5, 9300, (rateEndcapNegNoMagnet9300->GetMean() - rateEndcapNegMagnet9300->GetMean()));
deltaEndcapNeg-> SetPoint (6, 9400, (rateEndcapNegNoMagnet9400->GetMean() - rateEndcapNegMagnet9400->GetMean()));
deltaEndcapNeg-> SetPoint (7, 9500, (rateEndcapNegNoMagnet9500->GetMean() - rateEndcapNegMagnet9500->GetMean()));
deltaEndcapNeg-> SetPoint (8, 9600, (rateEndcapNegNoMagnet9600->GetMean() - rateEndcapNegMagnet9600->GetMean()));
deltaEndcapNeg-> SetPoint (9, 9700, (rateEndcapNegNoMagnet9700->GetMean() - rateEndcapNegMagnet9700->GetMean()));
deltaEndcapNeg-> SetPoint (10, 9800, (rateEndcapNegNoMagnet9800->GetMean() - rateEndcapNegMagnet9800->GetMean()));
}

}

// ------------ method called once each job just before starting event loop  ------------
void MyNoiseScan::beginJob()
{
  usesResource("TFileService");
  edm::Service < TFileService > fs; 

  rateBarrelMagnet8800 = fs->make<TH1F>("rateBarrelMagnet8800", "rateBarrelMagnet8800", 4000, 0.,2);
  rateBarrelMagnet8800->SetXTitle("rate [Hz/cm^{2}]");
  rateEndcapPosMagnet8800 = fs->make<TH1F>("rateEndcapPosMagnet8800", "rateEndcapPosMagnet8800", 4000, 0.,2);
  rateEndcapPosMagnet8800->SetXTitle("rate [Hz/cm^{2}]");
  rateEndcapNegMagnet8800 = fs->make<TH1F>("rateEndcapNegMagnet8800", "rateEndcapNegMagnet8800", 4000, 0.,2);
  rateEndcapNegMagnet8800->SetXTitle("rate [Hz/cm^{2}]");

  rateBarrelNoMagnet8800 = fs->make<TH1F>("rateBarrelNoMagnet8800", "rateBarrelNoMagnet8800", 4000, 0.,2);
  rateBarrelNoMagnet8800->SetXTitle("rate [Hz/cm^{2}]");
  rateEndcapPosNoMagnet8800 = fs->make<TH1F>("rateEndcapPosNoMagnet8800", "rateEndcapPosNoMagnet8800", 4000, 0.,2);
  rateEndcapPosNoMagnet8800->SetXTitle("rate [Hz/cm^{2}]");
  rateEndcapNegNoMagnet8800 = fs->make<TH1F>("rateEndcapNegNoMagnet8800", "rateEndcapNegNoMagnet8800", 4000, 0.,2);
  rateEndcapNegNoMagnet8800->SetXTitle("rate [Hz/cm^{2}]");

  rateBarrelMagnet9000 = fs->make<TH1F>("rateBarrelMagnet9000", "rateBarrelMagnet9000", 4000, 0.,2);
  rateBarrelMagnet9000->SetXTitle("rate [Hz/cm^{2}]");
  rateEndcapPosMagnet9000 = fs->make<TH1F>("rateEndcapPosMagnet9000", "rateEndcapPosMagnet9000", 4000, 0.,2);
  rateEndcapPosMagnet9000->SetXTitle("rate [Hz/cm^{2}]");
  rateEndcapNegMagnet9000 = fs->make<TH1F>("rateEndcapNegMagnet9000", "rateEndcapNegMagnet9000", 4000, 0.,2);
  rateEndcapNegMagnet9000->SetXTitle("rate [Hz/cm^{2}]");

  rateBarrelNoMagnet9000 = fs->make<TH1F>("rateBarrelNoMagnet9000", "rateBarrelNoMagnet9000", 4000, 0.,2);
  rateBarrelNoMagnet9000->SetXTitle("rate [Hz/cm^{2}]");
  rateEndcapPosNoMagnet9000 = fs->make<TH1F>("rateEndcapPosNoMagnet9000", "rateEndcapPosNoMagnet9000", 4000, 0.,2);
  rateEndcapPosNoMagnet9000->SetXTitle("rate [Hz/cm^{2}]");
  rateEndcapNegNoMagnet9000 = fs->make<TH1F>("rateEndcapNegNoMagnet9000", "rateEndcapNegNoMagnet9000", 4000, 0.,2);
  rateEndcapNegNoMagnet9000->SetXTitle("rate [Hz/cm^{2}]");

  rateBarrelMagnet9100 = fs->make<TH1F>("rateBarrelMagnet9100", "rateBarrelMagnet9100", 4000, 0.,2);
  rateBarrelMagnet9100->SetXTitle("rate [Hz/cm^{2}]");
  rateEndcapPosMagnet9100 = fs->make<TH1F>("rateEndcapPosMagnet9100", "rateEndcapPosMagnet9100", 4000, 0.,2);
  rateEndcapPosMagnet9100->SetXTitle("rate [Hz/cm^{2}]");
  rateEndcapNegMagnet9100 = fs->make<TH1F>("rateEndcapNegMagnet9100", "rateEndcapNegMagnet9100", 4000, 0.,2);
  rateEndcapNegMagnet9100->SetXTitle("rate [Hz/cm^{2}]");

  rateBarrelNoMagnet9100 = fs->make<TH1F>("rateBarrelNoMagnet9100", "rateBarrelNoMagnet9100", 4000, 0.,2);
  rateBarrelNoMagnet9100->SetXTitle("rate [Hz/cm^{2}]");
  rateEndcapPosNoMagnet9100 = fs->make<TH1F>("rateEndcapPosNoMagnet9100", "rateEndcapPosNoMagnet9100", 4000, 0.,2);
  rateEndcapPosNoMagnet9100->SetXTitle("rate [Hz/cm^{2}]");
  rateEndcapNegNoMagnet9100 = fs->make<TH1F>("rateEndcapNegNoMagnet9100", "rateEndcapNegNoMagnet9100", 4000, 0.,2);
  rateEndcapNegNoMagnet9100->SetXTitle("rate [Hz/cm^{2}]");

  rateBarrelMagnet9200 = fs->make<TH1F>("rateBarrelMagnet9200", "rateBarrelMagnet9200", 4000, 0.,2);
  rateBarrelMagnet9200->SetXTitle("rate [Hz/cm^{2}]");
  rateEndcapPosMagnet9200 = fs->make<TH1F>("rateEndcapPosMagnet9200", "rateEndcapPosMagnet9200", 4000, 0.,2);
  rateEndcapPosMagnet9200->SetXTitle("rate [Hz/cm^{2}]");
  rateEndcapNegMagnet9200 = fs->make<TH1F>("rateEndcapNegMagnet9200", "rateEndcapNegMagnet9200", 4000, 0.,2);
  rateEndcapNegMagnet9200->SetXTitle("rate [Hz/cm^{2}]");

  rateBarrelNoMagnet9200 = fs->make<TH1F>("rateBarrelNoMagnet9200", "rateBarrelNoMagnet9200", 4000, 0.,2);
  rateBarrelNoMagnet9200->SetXTitle("rate [Hz/cm^{2}]");
  rateEndcapPosNoMagnet9200 = fs->make<TH1F>("rateEndcapPosNoMagnet9200", "rateEndcapPosNoMagnet9200", 4000, 0.,2);
  rateEndcapPosNoMagnet9200->SetXTitle("rate [Hz/cm^{2}]");
  rateEndcapNegNoMagnet9200 = fs->make<TH1F>("rateEndcapNegNoMagnet9200", "rateEndcapNegNoMagnet9200", 4000, 0.,2);
  rateEndcapNegNoMagnet9200->SetXTitle("rate [Hz/cm^{2}]");

  rateBarrelMagnet9300 = fs->make<TH1F>("rateBarrelMagnet9300", "rateBarrelMagnet9300", 4000, 0.,2);
  rateBarrelMagnet9300->SetXTitle("rate [Hz/cm^{2}]");
  rateEndcapPosMagnet9300 = fs->make<TH1F>("rateEndcapPosMagnet9300", "rateEndcapPosMagnet9300", 4000, 0.,2);
  rateEndcapPosMagnet9300->SetXTitle("rate [Hz/cm^{2}]");
  rateEndcapNegMagnet9300 = fs->make<TH1F>("rateEndcapNegMagnet9300", "rateEndcapNegMagnet9300", 4000, 0.,2);
  rateEndcapNegMagnet9300->SetXTitle("rate [Hz/cm^{2}]");

  rateBarrelNoMagnet9300 = fs->make<TH1F>("rateBarrelNoMagnet9300", "rateBarrelNoMagnet9300", 4000, 0.,2);
  rateBarrelNoMagnet9300->SetXTitle("rate [Hz/cm^{2}]");
  rateEndcapPosNoMagnet9300 = fs->make<TH1F>("rateEndcapPosNoMagnet9300", "rateEndcapPosNoMagnet9300", 4000, 0.,2);
  rateEndcapPosNoMagnet9300->SetXTitle("rate [Hz/cm^{2}]");
  rateEndcapNegNoMagnet9300 = fs->make<TH1F>("rateEndcapNegNoMagnet9300", "rateEndcapNegNoMagnet9300", 4000, 0.,2);
  rateEndcapNegNoMagnet9300->SetXTitle("rate [Hz/cm^{2}]");

  rateBarrelMagnet9400 = fs->make<TH1F>("rateBarrelMagnet9400", "rateBarrelMagnet9400", 4000, 0.,2);
  rateBarrelMagnet9400->SetXTitle("rate [Hz/cm^{2}]");
  rateEndcapPosMagnet9400 = fs->make<TH1F>("rateEndcapPosMagnet9400", "rateEndcapPosMagnet9400", 4000, 0.,2);
  rateEndcapPosMagnet9400->SetXTitle("rate [Hz/cm^{2}]");
  rateEndcapNegMagnet9400 = fs->make<TH1F>("rateEndcapNegMagnet9400", "rateEndcapNegMagnet9400", 4000, 0.,2);
  rateEndcapNegMagnet9400->SetXTitle("rate [Hz/cm^{2}]");

  rateBarrelNoMagnet9400 = fs->make<TH1F>("rateBarrelNoMagnet9400", "rateBarrelNoMagnet9400", 4000, 0.,2);
  rateBarrelNoMagnet9400->SetXTitle("rate [Hz/cm^{2}]");
  rateEndcapPosNoMagnet9400 = fs->make<TH1F>("rateEndcapPosNoMagnet9400", "rateEndcapPosNoMagnet9400", 4000, 0.,2);
  rateEndcapPosNoMagnet9400->SetXTitle("rate [Hz/cm^{2}]");
  rateEndcapNegNoMagnet9400 = fs->make<TH1F>("rateEndcapNegNoMagnet9400", "rateEndcapNegNoMagnet9400", 4000, 0.,2);
  rateEndcapNegNoMagnet9400->SetXTitle("rate [Hz/cm^{2}]");

  rateBarrelMagnet9500 = fs->make<TH1F>("rateBarrelMagnet9500", "rateBarrelMagnet9500", 4000, 0.,2);
  rateBarrelMagnet9500->SetXTitle("rate [Hz/cm^{2}]");
  rateEndcapPosMagnet9500 = fs->make<TH1F>("rateEndcapPosMagnet9500", "rateEndcapPosMagnet9500", 4000, 0.,2);
  rateEndcapPosMagnet9500->SetXTitle("rate [Hz/cm^{2}]");
  rateEndcapNegMagnet9500 = fs->make<TH1F>("rateEndcapNegMagnet9500", "rateEndcapNegMagnet9500", 4000, 0.,2);
  rateEndcapNegMagnet9500->SetXTitle("rate [Hz/cm^{2}]");

  rateBarrelNoMagnet9500 = fs->make<TH1F>("rateBarrelNoMagnet9500", "rateBarrelNoMagnet9500", 4000, 0.,2);
  rateBarrelNoMagnet9500->SetXTitle("rate [Hz/cm^{2}]");
  rateEndcapPosNoMagnet9500 = fs->make<TH1F>("rateEndcapPosNoMagnet9500", "rateEndcapPosNoMagnet9500", 4000, 0.,2);
  rateEndcapPosNoMagnet9500->SetXTitle("rate [Hz/cm^{2}]");
  rateEndcapNegNoMagnet9500 = fs->make<TH1F>("rateEndcapNegNoMagnet9500", "rateEndcapNegNoMagnet9500", 4000, 0.,2);
  rateEndcapNegNoMagnet9500->SetXTitle("rate [Hz/cm^{2}]");

  rateBarrelMagnet9600 = fs->make<TH1F>("rateBarrelMagnet9600", "rateBarrelMagnet9600", 4000, 0.,2);
  rateBarrelMagnet9600->SetXTitle("rate [Hz/cm^{2}]");
  rateEndcapPosMagnet9600 = fs->make<TH1F>("rateEndcapPosMagnet9600", "rateEndcapPosMagnet9600", 4000, 0.,2);
  rateEndcapPosMagnet9600->SetXTitle("rate [Hz/cm^{2}]");
  rateEndcapNegMagnet9600 = fs->make<TH1F>("rateEndcapNegMagnet9600", "rateEndcapNegMagnet9600", 4000, 0.,2);
  rateEndcapNegMagnet9600->SetXTitle("rate [Hz/cm^{2}]");

  rateBarrelNoMagnet9600 = fs->make<TH1F>("rateBarrelNoMagnet9600", "rateBarrelNoMagnet9600", 4000, 0.,2);
  rateBarrelNoMagnet9600->SetXTitle("rate [Hz/cm^{2}]");
  rateEndcapPosNoMagnet9600 = fs->make<TH1F>("rateEndcapPosNoMagnet9600", "rateEndcapPosNoMagnet9600", 4000, 0.,2);
  rateEndcapPosNoMagnet9600->SetXTitle("rate [Hz/cm^{2}]");
  rateEndcapNegNoMagnet9600 = fs->make<TH1F>("rateEndcapNegNoMagnet9600", "rateEndcapNegNoMagnet9600", 4000, 0.,2);
  rateEndcapNegNoMagnet9600->SetXTitle("rate [Hz/cm^{2}]");

  rateBarrelMagnet9700 = fs->make<TH1F>("rateBarrelMagnet9700", "rateBarrelMagnet9700", 4000, 0.,2);
  rateBarrelMagnet9700->SetXTitle("rate [Hz/cm^{2}]");
  rateEndcapPosMagnet9700 = fs->make<TH1F>("rateEndcapPosMagnet9700", "rateEndcapPosMagnet9700", 4000, 0.,2);
  rateEndcapPosMagnet9700->SetXTitle("rate [Hz/cm^{2}]");
  rateEndcapNegMagnet9700 = fs->make<TH1F>("rateEndcapNegMagnet9700", "rateEndcapNegMagnet9700", 4000, 0.,2);
  rateEndcapNegMagnet9700->SetXTitle("rate [Hz/cm^{2}]");

  rateBarrelNoMagnet9700 = fs->make<TH1F>("rateBarrelNoMagnet9700", "rateBarrelNoMagnet9700", 4000, 0.,2);
  rateBarrelNoMagnet9700->SetXTitle("rate [Hz/cm^{2}]");
  rateEndcapPosNoMagnet9700 = fs->make<TH1F>("rateEndcapPosNoMagnet9700", "rateEndcapPosNoMagnet9700", 4000, 0.,2);
  rateEndcapPosNoMagnet9700->SetXTitle("rate [Hz/cm^{2}]");
  rateEndcapNegNoMagnet9700 = fs->make<TH1F>("rateEndcapNegNoMagnet9700", "rateEndcapNegNoMagnet9700", 4000, 0.,2);
  rateEndcapNegNoMagnet9700->SetXTitle("rate [Hz/cm^{2}]");

  rateEndcapPosMagnet9800 = fs->make<TH1F>("rateEndcapPosMagnet9800", "rateEndcapPosMagnet9800", 4000, 0.,2);
  rateEndcapPosMagnet9800->SetXTitle("rate [Hz/cm^{2}]");
  rateEndcapNegMagnet9800 = fs->make<TH1F>("rateEndcapNegMagnet9800", "rateEndcapNegMagnet9800", 4000, 0.,2);
  rateEndcapNegMagnet9800->SetXTitle("rate [Hz/cm^{2}]");

  rateEndcapPosNoMagnet9800 = fs->make<TH1F>("rateEndcapPosNoMagnet9800", "rateEndcapPosNoMagnet9800", 4000, 0.,2);
  rateEndcapPosNoMagnet9800->SetXTitle("rate [Hz/cm^{2}]");
  rateEndcapNegNoMagnet9800 = fs->make<TH1F>("rateEndcapNegNoMagnet9800", "rateEndcapNegNoMagnet9800", 4000, 0.,2);
  rateEndcapNegNoMagnet9800->SetXTitle("rate [Hz/cm^{2}]");



  barrelScanMagnet = fs->make<TGraphErrors> (9);
  barrelScanMagnet->SetName("barrelScanMagnet");
  barrelScanMagnet->SetTitle("Barrel - Noise Scan with Magnet");

  EndcapPosScanMagnet = fs->make<TGraphErrors> (10);
  EndcapPosScanMagnet->SetName("EndcapPosScanMagnet");
  EndcapPosScanMagnet->SetTitle("Endcap Positive - Noise Scan with Magnet");

  EndcapNegScanMagnet = fs->make<TGraphErrors> (10);
  EndcapNegScanMagnet->SetName("EndcapNegScanMagnet");
  EndcapNegScanMagnet->SetTitle("Endcap Negative - Noise Scan with Magnet");

  barrelScanNoMagnet = fs->make<TGraphErrors> (9);
  barrelScanNoMagnet->SetName("barrelScanNoMagnet");
  barrelScanNoMagnet->SetTitle("Barrel - Noise Scan without Magnet");

  EndcapPosScanNoMagnet = fs->make<TGraphErrors> (10);
  EndcapPosScanNoMagnet->SetName("EndcapPosScanNoMagnet");
  EndcapPosScanNoMagnet->SetTitle("Endcap Positive - Noise Scan without Magnet");

  EndcapNegScanNoMagnet = fs->make<TGraphErrors> (10);
  EndcapNegScanNoMagnet->SetName("EndcapNegScanNoMagnet");
  EndcapNegScanNoMagnet->SetTitle("Endcap Negative - Noise Scan without Magnet");

  deltabarrel = fs->make<TGraphErrors> (9);
  deltabarrel->SetName("deltabarrel");
  deltabarrel->SetTitle("Barrel - #Delta Rate (with/out Magnet)");
  deltabarrel->GetXaxis()->SetTitle("HV_{eff} [V]");
  deltabarrel->GetYaxis()->SetTitle("#Delta Rate [Hz/cm^{2}]");

  deltaEndcapPos = fs->make<TGraphErrors> (10);
  deltaEndcapPos->SetName("deltaEndcapPos");
  deltaEndcapPos->SetTitle("Endcap Positive - #Delta Rate (with/out Magnet)");
  deltaEndcapPos->GetXaxis()->SetTitle("HV_{eff} [V]");
  deltaEndcapPos->GetYaxis()->SetTitle("#Delta Rate [Hz/cm^{2}]");

  deltaEndcapNeg = fs->make<TGraphErrors> (10);
  deltaEndcapNeg->SetName("deltaEndcapNeg");
  deltaEndcapNeg->SetTitle("Endcap Negative - #Delta Rate (with/out Magnet)");
  deltaEndcapNeg->GetXaxis()->SetTitle("HV_{eff} [V]");
  deltaEndcapNeg->GetYaxis()->SetTitle("#Delta Rate [Hz/cm^{2}]");




}
// ------------ method called once each job just after ending the event loop  ------------
void MyNoiseScan::endJob()
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void MyNoiseScan::fillDescriptions(edm::ConfigurationDescriptions& descriptions)
{
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE (MyNoiseScan);
