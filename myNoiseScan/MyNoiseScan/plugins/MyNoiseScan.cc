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

//geometry
#include "Geometry/Records/interface/MuonGeometryRecord.h"
#include "Geometry/RPCGeometry/interface/RPCGeometry.h"
#include "Geometry/RPCGeometry/interface/RPCGeomServ.h"
#include "Geometry/CommonTopologies/interface/RectangularStripTopology.h"
#include "Geometry/CommonTopologies/interface/TrapezoidalStripTopology.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/MuonDetId/interface/RPCDetId.h"
#include "Geometry/RPCGeometry/interface/RPCRoll.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <cmath>

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
  int rollB(std::string shortname, std::map<int, std::string> rollNames);

private:
  virtual void beginJob() override;
  virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
  virtual void endJob() override;

  // ----------member data ---------------------------
  std::string myInputFileMagn_;
  std::string myInputFileNoMagn_;
  std::string myMapIdName_;
  bool debug_;
  bool doNoiseMagnet_;
  bool doNoiseNoMagnet_;
  double hvpointpar_;

  struct subject
  {
    std::string name;
//    uint32_t id;
    RPCDetId id;
    std::map<double, double> pairHvRate;
  };

  std::map<int, std::string> rollNamesInter;
  std::map<int, std::string> rollNamesExter;

//RollSector
  TH2F * Diskm4RollSector, *Diskm3RollSector, *Diskm2RollSector, *Diskm1RollSector, *Diskp1RollSector, *Diskp2RollSector, *Diskp3RollSector, *Diskp4RollSector;
  TH2F *Wheelm1RollSector, *Wheel0RollSector, *Wheel1RollSector, *Wheelm2RollSector, *Wheel2RollSector;

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
  myInputFileMagn_ = iConfig.getParameter < std::string > ("myInputFileMagn");
  myInputFileNoMagn_ = iConfig.getParameter < std::string > ("myInputFileNoMagn");
  myMapIdName_ = iConfig.getParameter < std::string > ("myMapIdName");
  debug_ = iConfig.getParameter<bool>("debug");
  doNoiseMagnet_ = iConfig.getParameter<bool>("doNoiseMagnet");
  doNoiseNoMagnet_ = iConfig.getParameter<bool>("doNoiseNoMagnet");
  hvpointpar_ = iConfig.getParameter<double>("hvpointpar");
//  usesResource("TFileService");

  rollNamesInter[1] = "RB1in B";
  rollNamesInter[2] = "RB1in F";
  rollNamesInter[3] = "RB1out B";
  rollNamesInter[4] = "RB1out F";
  rollNamesInter[5] = "RB2in B";
  rollNamesInter[6] = "RB2in F";
  rollNamesInter[7] = "RB2in M";
  rollNamesInter[8] = "RB2out B";
  rollNamesInter[9] = "RB2out F";
  rollNamesInter[10] = "RB3,- B";
  rollNamesInter[11] = "RB3,- F";
  rollNamesInter[12] = "RB3+ B";
  rollNamesInter[13] = "RB3+ F";
  rollNamesInter[14] = "RB4,- B";
  rollNamesInter[15] = "RB4,- F";
  rollNamesInter[16] = "RB4+ B";
  rollNamesInter[17] = "RB4+ F";
  rollNamesInter[18] = "RB4++ B";
  rollNamesInter[19] = "RB4++ F";
  rollNamesInter[20] = "RB4-- B";
  rollNamesInter[21] = "RB4-- F";

  for (int i = 1; i <= 22; i++)
  {
    rollNamesExter[i] = rollNamesInter[i];
  }
  rollNamesExter[7] = "RB2out B";
  rollNamesExter[8] = "RB2out F";
  rollNamesExter[9] = "RB2out M";
}

MyNoiseScan::~MyNoiseScan()
{
}
//
// member functions
//
int MyNoiseScan::rollB(std::string shortname, std::map<int, std::string> rollNames)
{
  int myy = 0;
  for (int i = 1; i < 22; i++)
  {
    if (rollNames[i].compare(shortname) == 0)
    {
      myy = i;
      return myy;
    }
  }
  if (myy == 0)
  {
    std::cout << "Check your map or your DetId for " << shortname << std::endl;
  }
  return myy;
}


// ------------ method called for each event  ------------
void MyNoiseScan::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace std;

  // Get the RPC Geometry
  edm::ESHandle < RPCGeometry > rpcGeom;
  iSetup.get<MuonGeometryRecord>().get(rpcGeom);
//  double area = 0.0;
//  double stripArea = 0.0;
//  TCanvas *c2 = new TCanvas("c2", "c2", 600., 600);
  double hvpoint2D = hvpointpar_;	//parametrize this
  double rate2D = -1.;

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

  fstream f_input;
  if (doNoiseMagnet_)
  {
    int justcounter = 0;
//    f_input.open("data/noisemagnet/allNoise_noRE11.txt", ios::in);
    f_input.open(myInputFileMagn_, ios::in);
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
        subObj.id = myrpcid;
        subObj.pairHvRate = tempMap;
        sub.push_back(subObj);
        tempMap.clear();
      }
    }
    f_input.close();

std::cout << "justcounter = " << justcounter << std::endl;

  if(debug_) std::cout << "sub.size() = " << sub.size() << std::endl;

  for (unsigned int i = 0; i < sub.size(); i++)
  {
    if(debug_) std::cout << sub[i].name << "\t" << sub[i].id << "\tmap size = " << (sub[i].pairHvRate).size()<< "\t" << (sub[i].pairHvRate)[8800] << std::endl;
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

//Fill 2D histos rolls vs sector
    RPCGeomServ rpcsrv(sub[i].id);
    int rollY = (sub[i].id).roll();
    if (rollY == 1)		rollY = 3;
    else if (rollY == 3)	rollY = 1;
    int Y = ((sub[i].id).ring() - 2) * 3 + rollY;
    rate2D = (sub[i].pairHvRate)[hvpoint2D];

    if ((sub[i].id).region() == -1)
    {
      if ((sub[i].id).station() == 1) {Diskm1RollSector->Fill(rpcsrv.segment(), Y, rate2D);}
      else if ((sub[i].id).station() == 2) {Diskm2RollSector->Fill(rpcsrv.segment(), Y, rate2D);}
      else if ((sub[i].id).station() == 3) {Diskm3RollSector->Fill(rpcsrv.segment(), Y, rate2D);}
      else if ((sub[i].id).station() == 4) {Diskm4RollSector->Fill(rpcsrv.segment(), Y, rate2D);}
      else std::cout << " no match for " << sub[i].id << std::endl;
    }
    if ((sub[i].id).region() == 1)
    {
      if ((sub[i].id).station() == 1) {Diskp1RollSector->Fill(rpcsrv.segment(), Y, rate2D);}
      else if ((sub[i].id).station() == 2) {Diskp2RollSector->Fill(rpcsrv.segment(), Y, rate2D);}
      else if ((sub[i].id).station() == 3) {Diskp3RollSector->Fill(rpcsrv.segment(), Y, rate2D);}
      else if ((sub[i].id).station() == 4) {Diskp4RollSector->Fill(rpcsrv.segment(), Y, rate2D);}
      else std::cout << " no match for " << sub[i].id << std::endl;
    }
    if ((sub[i].id).region() == 0)
    {
      if (hvpoint2D > 9700)  hvpoint2D = 9500;
      else
      {
        if (debug_) std::cout<< "Wheel " << (sub[i].id).ring()<< "\tid = " << (sub[i].id) << "\t" <<rollB(rpcsrv.shortname(),rollNamesExter)<<"\t"<<rpcsrv.shortname()<<std::endl;
        if ((sub[i].id).ring() == 2)		Wheel2RollSector->Fill((sub[i].id).sector(), rollB(rpcsrv.shortname(), rollNamesExter), rate2D);
        else if ((sub[i].id).ring() == -2)	Wheelm2RollSector->Fill((sub[i].id).sector(), rollB(rpcsrv.shortname(), rollNamesExter), rate2D);
        else if ((sub[i].id).ring() == -1)	Wheelm1RollSector->Fill((sub[i].id).sector(), rollB(rpcsrv.shortname(), rollNamesInter), rate2D);
        else if ((sub[i].id).ring() == 0)		Wheel0RollSector->Fill((sub[i].id).sector(), rollB(rpcsrv.shortname(), rollNamesInter), rate2D);
        else if ((sub[i].id).ring() == 1)		Wheel1RollSector->Fill((sub[i].id).sector(), rollB(rpcsrv.shortname(), rollNamesInter), rate2D);
        else std::cout << " no match for " << sub[i].id << std::endl;
      }
    }
  }
}//end noise with magnet

  if (doNoiseNoMagnet_)
  {
    int justcounter = 0;
//    f_input.open("data/noisenomagnet/allNoiseNomagnet_noRE11.txt", ios::in);
    f_input.open(myInputFileNoMagn_, ios::in);
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
        subObj.id = myrpcid;
        subObj.pairHvRate = tempMap;
        subNoMagnet.push_back(subObj);
        tempMap.clear();
      }
    }
    f_input.close();

  if(debug_) std::cout << "sub.size() = " << subNoMagnet.size() << std::endl;
  for (unsigned int i = 0; i < subNoMagnet.size(); i++)
  {
    if(debug_) std::cout << subNoMagnet[i].name << "\t" << subNoMagnet[i].id << "\tmap size = " << (subNoMagnet[i].pairHvRate).size()<< "\t" << (subNoMagnet[i].pairHvRate)[8800] << std::endl;
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

if(doNoiseMagnet_ && doNoiseNoMagnet_)
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

//for 2D plots rolls vs sector
  TFileDirectory rollVsSectorB = fs->mkdir("rollVsSectorB");
  TFileDirectory rollVsSectorE = fs->mkdir("rollVsSectorE");

  std::stringstream titleLabel;
  for (int i = 0; i < 4; i++)
  {
    titleLabel.str("");
    titleLabel  << "Disk" << i-4 << ", Rate at HV = " <<  hvpointpar_;
    if(i == 0)  Diskm4RollSector = rollVsSectorE.make < TH2F > ("Diskm4RollSector", titleLabel.str().c_str(), 36, 0.5, 36.5, 6, 0.5, 6.5);
    if(i == 1)  Diskm3RollSector = rollVsSectorE.make < TH2F > ("Diskm3RollSector", titleLabel.str().c_str(), 36, 0.5, 36.5, 6, 0.5, 6.5);
    if(i == 2)  Diskm2RollSector = rollVsSectorE.make < TH2F > ("Diskm2RollSector", titleLabel.str().c_str(), 36, 0.5, 36.5, 6, 0.5, 6.5);
    if(i == 3)  Diskm1RollSector = rollVsSectorE.make < TH2F > ("Diskm1RollSector", titleLabel.str().c_str(), 36, 0.5, 36.5, 6, 0.5, 6.5);
  }
  for (int i = 0; i < 4; i++)
  {
    titleLabel.str("");
    titleLabel  << "Disk" << i+1 << ", Rate at HV = " <<  hvpointpar_;
    if(i == 0)  Diskp1RollSector = rollVsSectorE.make < TH2F > ("Diskp1RollSector", titleLabel.str().c_str(), 36, 0.5, 36.5, 6, 0.5, 6.5);
    if(i == 1)  Diskp2RollSector = rollVsSectorE.make < TH2F > ("Diskp2RollSector", titleLabel.str().c_str(), 36, 0.5, 36.5, 6, 0.5, 6.5);
    if(i == 2)  Diskp3RollSector = rollVsSectorE.make < TH2F > ("Diskp3RollSector", titleLabel.str().c_str(), 36, 0.5, 36.5, 6, 0.5, 6.5);
    if(i == 3)  Diskp4RollSector = rollVsSectorE.make < TH2F > ("Diskp4RollSector", titleLabel.str().c_str(), 36, 0.5, 36.5, 6, 0.5, 6.5);
  }
  std::stringstream binLabel;
  for (int i = 1; i <= 36; i++)
  {
    binLabel.str("");
    binLabel << i;
    Diskm4RollSector->GetXaxis()->SetBinLabel(i, binLabel.str().c_str());
    Diskm3RollSector->GetXaxis()->SetBinLabel(i, binLabel.str().c_str());
    Diskm2RollSector->GetXaxis()->SetBinLabel(i, binLabel.str().c_str());
    Diskm1RollSector->GetXaxis()->SetBinLabel(i, binLabel.str().c_str());
    Diskp4RollSector->GetXaxis()->SetBinLabel(i, binLabel.str().c_str());
    Diskp3RollSector->GetXaxis()->SetBinLabel(i, binLabel.str().c_str());
    Diskp2RollSector->GetXaxis()->SetBinLabel(i, binLabel.str().c_str());
    Diskp1RollSector->GetXaxis()->SetBinLabel(i, binLabel.str().c_str());
  }
  for (int ri = 2; ri <= 3; ri++)
  {
    for (int roll = 1; roll <= 3; roll++)
    {
      binLabel.str("");
      if (roll == 3) binLabel << "Ring " << ri << " A";
      else if (roll == 2) binLabel << "Ring " << ri << " B";
      else if (roll == 1) binLabel << "Ring " << ri << " C";
      if(debug_) std::cout<<"Labeling EndCaps "<<binLabel.str()<<std::endl;
      Diskm4RollSector->GetYaxis()->SetBinLabel((ri - 2) * 3 + roll, binLabel.str().c_str());
      Diskm3RollSector->GetYaxis()->SetBinLabel((ri - 2) * 3 + roll, binLabel.str().c_str());
      Diskm2RollSector->GetYaxis()->SetBinLabel((ri - 2) * 3 + roll, binLabel.str().c_str());
      Diskm1RollSector->GetYaxis()->SetBinLabel((ri - 2) * 3 + roll, binLabel.str().c_str());
      Diskp4RollSector->GetYaxis()->SetBinLabel((ri - 2) * 3 + roll, binLabel.str().c_str());
      Diskp3RollSector->GetYaxis()->SetBinLabel((ri - 2) * 3 + roll, binLabel.str().c_str());
      Diskp2RollSector->GetYaxis()->SetBinLabel((ri - 2) * 3 + roll, binLabel.str().c_str());
      Diskp1RollSector->GetYaxis()->SetBinLabel((ri - 2) * 3 + roll, binLabel.str().c_str());
    }
  }
  Diskm4RollSector->SetZTitle("Rate [Hz/cm^{2}]");
  Diskm3RollSector->SetZTitle("Rate [Hz/cm^{2}]");
  Diskm2RollSector->SetZTitle("Rate [Hz/cm^{2}]");
  Diskm1RollSector->SetZTitle("Rate [Hz/cm^{2}]");
  Diskp4RollSector->SetZTitle("Rate [Hz/cm^{2}]");
  Diskp3RollSector->SetZTitle("Rate [Hz/cm^{2}]");
  Diskp2RollSector->SetZTitle("Rate [Hz/cm^{2}]");
  Diskp1RollSector->SetZTitle("Rate [Hz/cm^{2}]");

  for (int i = 0; i < 5; i++)
  {
    titleLabel.str("");
    titleLabel  << "Wheel" << i-2 << ", Rate at HV = " <<  hvpointpar_;
    if(i == 0)  Wheelm2RollSector = rollVsSectorB.make < TH2F > ("Wheelm2RollSector", titleLabel.str().c_str(), 12, 0.5, 12.5, 22, 0.5, 22.5);
    if(i == 1)  Wheelm1RollSector = rollVsSectorB.make < TH2F > ("Wheelm1RollSector", titleLabel.str().c_str(), 12, 0.5, 12.5, 22, 0.5, 22.5);
    if(i == 2)  Wheel0RollSector = rollVsSectorB.make < TH2F > ("Wheel0RollSector", titleLabel.str().c_str(), 12, 0.5, 12.5, 22, 0.5, 22.5);
    if(i == 3)  Wheel1RollSector = rollVsSectorB.make < TH2F > ("Wheel1RollSector", titleLabel.str().c_str(), 12, 0.5, 12.5, 22, 0.5, 22.5);
    if(i == 4)  Wheel2RollSector = rollVsSectorB.make < TH2F > ("Wheel2RollSector", titleLabel.str().c_str(), 12, 0.5, 12.5, 22, 0.5, 22.5);
  }
  for (int i = 1; i <= 12; i++)
  {
    binLabel.str("");
    binLabel << "Sec " << i;
    Wheelm2RollSector->GetXaxis()->SetBinLabel(i, binLabel.str().c_str());
    Wheelm1RollSector->GetXaxis()->SetBinLabel(i, binLabel.str().c_str());
    Wheel0RollSector->GetXaxis()->SetBinLabel(i, binLabel.str().c_str());
    Wheel1RollSector->GetXaxis()->SetBinLabel(i, binLabel.str().c_str());
    Wheel2RollSector->GetXaxis()->SetBinLabel(i, binLabel.str().c_str());
  }
  for (int i = 1; i < 22; i++)
  {
    Wheelm1RollSector->GetYaxis()->SetBinLabel(i, rollNamesInter[i].c_str());
    Wheel0RollSector->GetYaxis()->SetBinLabel(i, rollNamesInter[i].c_str());
    Wheel1RollSector->GetYaxis()->SetBinLabel(i, rollNamesInter[i].c_str());
  }
  for (int i = 1; i < 22; i++)
  {
    Wheelm2RollSector->GetYaxis()->SetBinLabel(i, rollNamesExter[i].c_str());
    Wheel2RollSector->GetYaxis()->SetBinLabel(i, rollNamesExter[i].c_str());
  }
  Wheelm2RollSector->SetZTitle("Rate [Hz/cm^{2}]");
  Wheelm1RollSector->SetZTitle("Rate [Hz/cm^{2}]");
  Wheel0RollSector->SetZTitle("Rate [Hz/cm^{2}]");
  Wheel1RollSector->SetZTitle("Rate [Hz/cm^{2}]");
  Wheel2RollSector->SetZTitle("Rate [Hz/cm^{2}]");
//end 2D plots rolls vs sector

//TH1F per detector region and HV point
  TFileDirectory dirHV8800 = fs->mkdir("dirHV8800");
  TFileDirectory dirHV9000 = fs->mkdir("dirHV9000");
  TFileDirectory dirHV9100 = fs->mkdir("dirHV9100");
  TFileDirectory dirHV9200 = fs->mkdir("dirHV9200");
  TFileDirectory dirHV9300 = fs->mkdir("dirHV9300");
  TFileDirectory dirHV9400 = fs->mkdir("dirHV9400");
  TFileDirectory dirHV9500 = fs->mkdir("dirHV9500");
  TFileDirectory dirHV9600 = fs->mkdir("dirHV9600");
  TFileDirectory dirHV9700 = fs->mkdir("dirHV9700");
  TFileDirectory dirHV9800 = fs->mkdir("dirHV9800");

  rateBarrelMagnet8800 = dirHV8800.make<TH1F>("rateBarrelMagnet8800", "rateBarrelMagnet8800", 4000, 0.,2);
  rateBarrelMagnet8800->SetXTitle("rate [Hz/cm^{2}]");
  rateEndcapPosMagnet8800 = dirHV8800.make<TH1F>("rateEndcapPosMagnet8800", "rateEndcapPosMagnet8800", 4000, 0.,2);
  rateEndcapPosMagnet8800->SetXTitle("rate [Hz/cm^{2}]");
  rateEndcapNegMagnet8800 = dirHV8800.make<TH1F>("rateEndcapNegMagnet8800", "rateEndcapNegMagnet8800", 4000, 0.,2);
  rateEndcapNegMagnet8800->SetXTitle("rate [Hz/cm^{2}]");

  rateBarrelNoMagnet8800 = dirHV8800.make<TH1F>("rateBarrelNoMagnet8800", "rateBarrelNoMagnet8800", 4000, 0.,2);
  rateBarrelNoMagnet8800->SetXTitle("rate [Hz/cm^{2}]");
  rateEndcapPosNoMagnet8800 = dirHV8800.make<TH1F>("rateEndcapPosNoMagnet8800", "rateEndcapPosNoMagnet8800", 4000, 0.,2);
  rateEndcapPosNoMagnet8800->SetXTitle("rate [Hz/cm^{2}]");
  rateEndcapNegNoMagnet8800 = dirHV8800.make<TH1F>("rateEndcapNegNoMagnet8800", "rateEndcapNegNoMagnet8800", 4000, 0.,2);
  rateEndcapNegNoMagnet8800->SetXTitle("rate [Hz/cm^{2}]");

  rateBarrelMagnet9000 = dirHV9000.make<TH1F>("rateBarrelMagnet9000", "rateBarrelMagnet9000", 4000, 0.,2);
  rateBarrelMagnet9000->SetXTitle("rate [Hz/cm^{2}]");
  rateEndcapPosMagnet9000 = dirHV9000.make<TH1F>("rateEndcapPosMagnet9000", "rateEndcapPosMagnet9000", 4000, 0.,2);
  rateEndcapPosMagnet9000->SetXTitle("rate [Hz/cm^{2}]");
  rateEndcapNegMagnet9000 = dirHV9000.make<TH1F>("rateEndcapNegMagnet9000", "rateEndcapNegMagnet9000", 4000, 0.,2);
  rateEndcapNegMagnet9000->SetXTitle("rate [Hz/cm^{2}]");

  rateBarrelNoMagnet9000 = dirHV9000.make<TH1F>("rateBarrelNoMagnet9000", "rateBarrelNoMagnet9000", 4000, 0.,2);
  rateBarrelNoMagnet9000->SetXTitle("rate [Hz/cm^{2}]");
  rateEndcapPosNoMagnet9000 = dirHV9000.make<TH1F>("rateEndcapPosNoMagnet9000", "rateEndcapPosNoMagnet9000", 4000, 0.,2);
  rateEndcapPosNoMagnet9000->SetXTitle("rate [Hz/cm^{2}]");
  rateEndcapNegNoMagnet9000 = dirHV9000.make<TH1F>("rateEndcapNegNoMagnet9000", "rateEndcapNegNoMagnet9000", 4000, 0.,2);
  rateEndcapNegNoMagnet9000->SetXTitle("rate [Hz/cm^{2}]");

  rateBarrelMagnet9100 = dirHV9100.make<TH1F>("rateBarrelMagnet9100", "rateBarrelMagnet9100", 4000, 0.,2);
  rateBarrelMagnet9100->SetXTitle("rate [Hz/cm^{2}]");
  rateEndcapPosMagnet9100 = dirHV9100.make<TH1F>("rateEndcapPosMagnet9100", "rateEndcapPosMagnet9100", 4000, 0.,2);
  rateEndcapPosMagnet9100->SetXTitle("rate [Hz/cm^{2}]");
  rateEndcapNegMagnet9100 = dirHV9100.make<TH1F>("rateEndcapNegMagnet9100", "rateEndcapNegMagnet9100", 4000, 0.,2);
  rateEndcapNegMagnet9100->SetXTitle("rate [Hz/cm^{2}]");

  rateBarrelNoMagnet9100 = dirHV9100.make<TH1F>("rateBarrelNoMagnet9100", "rateBarrelNoMagnet9100", 4000, 0.,2);
  rateBarrelNoMagnet9100->SetXTitle("rate [Hz/cm^{2}]");
  rateEndcapPosNoMagnet9100 = dirHV9100.make<TH1F>("rateEndcapPosNoMagnet9100", "rateEndcapPosNoMagnet9100", 4000, 0.,2);
  rateEndcapPosNoMagnet9100->SetXTitle("rate [Hz/cm^{2}]");
  rateEndcapNegNoMagnet9100 = dirHV9100.make<TH1F>("rateEndcapNegNoMagnet9100", "rateEndcapNegNoMagnet9100", 4000, 0.,2);
  rateEndcapNegNoMagnet9100->SetXTitle("rate [Hz/cm^{2}]");

  rateBarrelMagnet9200 = dirHV9200.make<TH1F>("rateBarrelMagnet9200", "rateBarrelMagnet9200", 4000, 0.,2);
  rateBarrelMagnet9200->SetXTitle("rate [Hz/cm^{2}]");
  rateEndcapPosMagnet9200 = dirHV9200.make<TH1F>("rateEndcapPosMagnet9200", "rateEndcapPosMagnet9200", 4000, 0.,2);
  rateEndcapPosMagnet9200->SetXTitle("rate [Hz/cm^{2}]");
  rateEndcapNegMagnet9200 = dirHV9200.make<TH1F>("rateEndcapNegMagnet9200", "rateEndcapNegMagnet9200", 4000, 0.,2);
  rateEndcapNegMagnet9200->SetXTitle("rate [Hz/cm^{2}]");

  rateBarrelNoMagnet9200 = dirHV9200.make<TH1F>("rateBarrelNoMagnet9200", "rateBarrelNoMagnet9200", 4000, 0.,2);
  rateBarrelNoMagnet9200->SetXTitle("rate [Hz/cm^{2}]");
  rateEndcapPosNoMagnet9200 = dirHV9200.make<TH1F>("rateEndcapPosNoMagnet9200", "rateEndcapPosNoMagnet9200", 4000, 0.,2);
  rateEndcapPosNoMagnet9200->SetXTitle("rate [Hz/cm^{2}]");
  rateEndcapNegNoMagnet9200 = dirHV9200.make<TH1F>("rateEndcapNegNoMagnet9200", "rateEndcapNegNoMagnet9200", 4000, 0.,2);
  rateEndcapNegNoMagnet9200->SetXTitle("rate [Hz/cm^{2}]");

  rateBarrelMagnet9300 = dirHV9300.make<TH1F>("rateBarrelMagnet9300", "rateBarrelMagnet9300", 4000, 0.,2);
  rateBarrelMagnet9300->SetXTitle("rate [Hz/cm^{2}]");
  rateEndcapPosMagnet9300 = dirHV9300.make<TH1F>("rateEndcapPosMagnet9300", "rateEndcapPosMagnet9300", 4000, 0.,2);
  rateEndcapPosMagnet9300->SetXTitle("rate [Hz/cm^{2}]");
  rateEndcapNegMagnet9300 = dirHV9300.make<TH1F>("rateEndcapNegMagnet9300", "rateEndcapNegMagnet9300", 4000, 0.,2);
  rateEndcapNegMagnet9300->SetXTitle("rate [Hz/cm^{2}]");

  rateBarrelNoMagnet9300 = dirHV9300.make<TH1F>("rateBarrelNoMagnet9300", "rateBarrelNoMagnet9300", 4000, 0.,2);
  rateBarrelNoMagnet9300->SetXTitle("rate [Hz/cm^{2}]");
  rateEndcapPosNoMagnet9300 = dirHV9300.make<TH1F>("rateEndcapPosNoMagnet9300", "rateEndcapPosNoMagnet9300", 4000, 0.,2);
  rateEndcapPosNoMagnet9300->SetXTitle("rate [Hz/cm^{2}]");
  rateEndcapNegNoMagnet9300 = dirHV9300.make<TH1F>("rateEndcapNegNoMagnet9300", "rateEndcapNegNoMagnet9300", 4000, 0.,2);
  rateEndcapNegNoMagnet9300->SetXTitle("rate [Hz/cm^{2}]");

  rateBarrelMagnet9400 = dirHV9400.make<TH1F>("rateBarrelMagnet9400", "rateBarrelMagnet9400", 4000, 0.,2);
  rateBarrelMagnet9400->SetXTitle("rate [Hz/cm^{2}]");
  rateEndcapPosMagnet9400 = dirHV9400.make<TH1F>("rateEndcapPosMagnet9400", "rateEndcapPosMagnet9400", 4000, 0.,2);
  rateEndcapPosMagnet9400->SetXTitle("rate [Hz/cm^{2}]");
  rateEndcapNegMagnet9400 = dirHV9400.make<TH1F>("rateEndcapNegMagnet9400", "rateEndcapNegMagnet9400", 4000, 0.,2);
  rateEndcapNegMagnet9400->SetXTitle("rate [Hz/cm^{2}]");

  rateBarrelNoMagnet9400 = dirHV9400.make<TH1F>("rateBarrelNoMagnet9400", "rateBarrelNoMagnet9400", 4000, 0.,2);
  rateBarrelNoMagnet9400->SetXTitle("rate [Hz/cm^{2}]");
  rateEndcapPosNoMagnet9400 = dirHV9400.make<TH1F>("rateEndcapPosNoMagnet9400", "rateEndcapPosNoMagnet9400", 4000, 0.,2);
  rateEndcapPosNoMagnet9400->SetXTitle("rate [Hz/cm^{2}]");
  rateEndcapNegNoMagnet9400 = dirHV9400.make<TH1F>("rateEndcapNegNoMagnet9400", "rateEndcapNegNoMagnet9400", 4000, 0.,2);
  rateEndcapNegNoMagnet9400->SetXTitle("rate [Hz/cm^{2}]");

  rateBarrelMagnet9500 = dirHV9500.make<TH1F>("rateBarrelMagnet9500", "rateBarrelMagnet9500", 4000, 0.,2);
  rateBarrelMagnet9500->SetXTitle("rate [Hz/cm^{2}]");
  rateEndcapPosMagnet9500 = dirHV9500.make<TH1F>("rateEndcapPosMagnet9500", "rateEndcapPosMagnet9500", 4000, 0.,2);
  rateEndcapPosMagnet9500->SetXTitle("rate [Hz/cm^{2}]");
  rateEndcapNegMagnet9500 = dirHV9500.make<TH1F>("rateEndcapNegMagnet9500", "rateEndcapNegMagnet9500", 4000, 0.,2);
  rateEndcapNegMagnet9500->SetXTitle("rate [Hz/cm^{2}]");

  rateBarrelNoMagnet9500 = dirHV9500.make<TH1F>("rateBarrelNoMagnet9500", "rateBarrelNoMagnet9500", 4000, 0.,2);
  rateBarrelNoMagnet9500->SetXTitle("rate [Hz/cm^{2}]");
  rateEndcapPosNoMagnet9500 = dirHV9500.make<TH1F>("rateEndcapPosNoMagnet9500", "rateEndcapPosNoMagnet9500", 4000, 0.,2);
  rateEndcapPosNoMagnet9500->SetXTitle("rate [Hz/cm^{2}]");
  rateEndcapNegNoMagnet9500 = dirHV9500.make<TH1F>("rateEndcapNegNoMagnet9500", "rateEndcapNegNoMagnet9500", 4000, 0.,2);
  rateEndcapNegNoMagnet9500->SetXTitle("rate [Hz/cm^{2}]");

  rateBarrelMagnet9600 = dirHV9600.make<TH1F>("rateBarrelMagnet9600", "rateBarrelMagnet9600", 4000, 0.,2);
  rateBarrelMagnet9600->SetXTitle("rate [Hz/cm^{2}]");
  rateEndcapPosMagnet9600 = dirHV9600.make<TH1F>("rateEndcapPosMagnet9600", "rateEndcapPosMagnet9600", 4000, 0.,2);
  rateEndcapPosMagnet9600->SetXTitle("rate [Hz/cm^{2}]");
  rateEndcapNegMagnet9600 = dirHV9600.make<TH1F>("rateEndcapNegMagnet9600", "rateEndcapNegMagnet9600", 4000, 0.,2);
  rateEndcapNegMagnet9600->SetXTitle("rate [Hz/cm^{2}]");

  rateBarrelNoMagnet9600 = dirHV9600.make<TH1F>("rateBarrelNoMagnet9600", "rateBarrelNoMagnet9600", 4000, 0.,2);
  rateBarrelNoMagnet9600->SetXTitle("rate [Hz/cm^{2}]");
  rateEndcapPosNoMagnet9600 = dirHV9600.make<TH1F>("rateEndcapPosNoMagnet9600", "rateEndcapPosNoMagnet9600", 4000, 0.,2);
  rateEndcapPosNoMagnet9600->SetXTitle("rate [Hz/cm^{2}]");
  rateEndcapNegNoMagnet9600 = dirHV9600.make<TH1F>("rateEndcapNegNoMagnet9600", "rateEndcapNegNoMagnet9600", 4000, 0.,2);
  rateEndcapNegNoMagnet9600->SetXTitle("rate [Hz/cm^{2}]");

  rateBarrelMagnet9700 = dirHV9700.make<TH1F>("rateBarrelMagnet9700", "rateBarrelMagnet9700", 4000, 0.,2);
  rateBarrelMagnet9700->SetXTitle("rate [Hz/cm^{2}]");
  rateEndcapPosMagnet9700 = dirHV9700.make<TH1F>("rateEndcapPosMagnet9700", "rateEndcapPosMagnet9700", 4000, 0.,2);
  rateEndcapPosMagnet9700->SetXTitle("rate [Hz/cm^{2}]");
  rateEndcapNegMagnet9700 = dirHV9700.make<TH1F>("rateEndcapNegMagnet9700", "rateEndcapNegMagnet9700", 4000, 0.,2);
  rateEndcapNegMagnet9700->SetXTitle("rate [Hz/cm^{2}]");

  rateBarrelNoMagnet9700 = dirHV9700.make<TH1F>("rateBarrelNoMagnet9700", "rateBarrelNoMagnet9700", 4000, 0.,2);
  rateBarrelNoMagnet9700->SetXTitle("rate [Hz/cm^{2}]");
  rateEndcapPosNoMagnet9700 = dirHV9700.make<TH1F>("rateEndcapPosNoMagnet9700", "rateEndcapPosNoMagnet9700", 4000, 0.,2);
  rateEndcapPosNoMagnet9700->SetXTitle("rate [Hz/cm^{2}]");
  rateEndcapNegNoMagnet9700 = dirHV9700.make<TH1F>("rateEndcapNegNoMagnet9700", "rateEndcapNegNoMagnet9700", 4000, 0.,2);
  rateEndcapNegNoMagnet9700->SetXTitle("rate [Hz/cm^{2}]");

  rateEndcapPosMagnet9800 = dirHV9800.make<TH1F>("rateEndcapPosMagnet9800", "rateEndcapPosMagnet9800", 4000, 0.,2);
  rateEndcapPosMagnet9800->SetXTitle("rate [Hz/cm^{2}]");
  rateEndcapNegMagnet9800 = dirHV9800.make<TH1F>("rateEndcapNegMagnet9800", "rateEndcapNegMagnet9800", 4000, 0.,2);
  rateEndcapNegMagnet9800->SetXTitle("rate [Hz/cm^{2}]");

  rateEndcapPosNoMagnet9800 = dirHV9800.make<TH1F>("rateEndcapPosNoMagnet9800", "rateEndcapPosNoMagnet9800", 4000, 0.,2);
  rateEndcapPosNoMagnet9800->SetXTitle("rate [Hz/cm^{2}]");
  rateEndcapNegNoMagnet9800 = dirHV9800.make<TH1F>("rateEndcapNegNoMagnet9800", "rateEndcapNegNoMagnet9800", 4000, 0.,2);
  rateEndcapNegNoMagnet9800->SetXTitle("rate [Hz/cm^{2}]");

//TGraphs scan

  TFileDirectory myScan = fs->mkdir("myScan");


  barrelScanMagnet = myScan.make<TGraphErrors> (9);
  barrelScanMagnet->SetName("barrelScanMagnet");
  barrelScanMagnet->SetTitle("Barrel - Noise Scan with Magnet");

  EndcapPosScanMagnet = myScan.make<TGraphErrors> (10);
  EndcapPosScanMagnet->SetName("EndcapPosScanMagnet");
  EndcapPosScanMagnet->SetTitle("Endcap Positive - Noise Scan with Magnet");

  EndcapNegScanMagnet = myScan.make<TGraphErrors> (10);
  EndcapNegScanMagnet->SetName("EndcapNegScanMagnet");
  EndcapNegScanMagnet->SetTitle("Endcap Negative - Noise Scan with Magnet");

  barrelScanNoMagnet = myScan.make<TGraphErrors> (9);
  barrelScanNoMagnet->SetName("barrelScanNoMagnet");
  barrelScanNoMagnet->SetTitle("Barrel - Noise Scan without Magnet");

  EndcapPosScanNoMagnet = myScan.make<TGraphErrors> (10);
  EndcapPosScanNoMagnet->SetName("EndcapPosScanNoMagnet");
  EndcapPosScanNoMagnet->SetTitle("Endcap Positive - Noise Scan without Magnet");

  EndcapNegScanNoMagnet = myScan.make<TGraphErrors> (10);
  EndcapNegScanNoMagnet->SetName("EndcapNegScanNoMagnet");
  EndcapNegScanNoMagnet->SetTitle("Endcap Negative - Noise Scan without Magnet");

  deltabarrel = myScan.make<TGraphErrors> (9);
  deltabarrel->SetName("deltabarrel");
  deltabarrel->SetTitle("Barrel - #Delta Rate (with/out Magnet)");
  deltabarrel->GetXaxis()->SetTitle("HV_{eff} [V]");
  deltabarrel->GetYaxis()->SetTitle("#Delta Rate [Hz/cm^{2}]");

  deltaEndcapPos = fs->make<TGraphErrors> (10);
  deltaEndcapPos->SetName("deltaEndcapPos");
  deltaEndcapPos->SetTitle("Endcap Positive - #Delta Rate (with/out Magnet)");
  deltaEndcapPos->GetXaxis()->SetTitle("HV_{eff} [V]");
  deltaEndcapPos->GetYaxis()->SetTitle("#Delta Rate [Hz/cm^{2}]");

  deltaEndcapNeg = myScan.make<TGraphErrors> (10);
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
