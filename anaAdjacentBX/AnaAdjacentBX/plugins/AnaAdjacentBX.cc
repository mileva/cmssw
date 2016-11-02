// -*- C++ -*-
//
// Package:    anaAdjacentBX/AnaAdjacentBX
// Class:      AnaAdjacentBX
// 
/**\class AnaAdjacentBX AnaAdjacentBX.cc anaAdjacentBX/AnaAdjacentBX/plugins/AnaAdjacentBX.cc

 Description: [one line class summary]

 Implementation:
 [Notes on implementation]
 */
//
// Original Author:  Roumyana Mileva Hadjiiska
//         Created:  Fri, 28 Oct 2016 17:57:55 GMT
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

//
// class declaration
//

#include "FWCore/Framework/interface/MakerMacros.h"
#include "DataFormats/RPCDigi/interface/RPCDigiCollection.h"
#include "DataFormats/RPCRecHit/interface/RPCRecHitCollection.h"
#include "DataFormats/MuonDetId/interface/RPCDetId.h"
#include "Geometry/RPCGeometry/interface/RPCGeomServ.h"
#include "Geometry/CommonDetUnit/interface/GeomDet.h"
#include "Geometry/Records/interface/MuonGeometryRecord.h"
#include "Geometry/CommonTopologies/interface/RectangularStripTopology.h"
#include "Geometry/CommonTopologies/interface/TrapezoidalStripTopology.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "TH2F.h"
#include "TH1F.h"

#include <cmath>
#include "TFile.h"
//#include "TCanvas.h"
#include "TAxis.h"
#include "TString.h"

#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/Utilities/interface/EDGetToken.h"

#include "FWCore/Framework/interface/ESHandle.h"
#include "Geometry/RPCGeometry/interface/RPCGeometry.h"

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<> and also remove the line from
// constructor "usesResource("TFileService");"
// This will improve performance in multithreaded jobs.

class AnaAdjacentBX: public edm::one::EDAnalyzer<edm::one::SharedResources>
{
public:
  explicit AnaAdjacentBX(const edm::ParameterSet&);
  ~AnaAdjacentBX();

  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

private:
  virtual void beginJob() override;
  virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
  virtual void endJob() override;

  // ----------member data ---------------------------
  edm::EDGetTokenT<RPCRecHitCollection> rpcRecHitsLabel;

  TH1F * bxStatisticsBarrel;
  TH1F *bxStatisticsEndcap;

};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
AnaAdjacentBX::AnaAdjacentBX(const edm::ParameterSet& iConfig)

{
  //now do what ever initialization is needed
//   usesResource("TFileService");
  rpcRecHitsLabel = consumes < RPCRecHitCollection > (iConfig.getUntrackedParameter < edm::InputTag > ("rpcRecHits"));

}

AnaAdjacentBX::~AnaAdjacentBX()
{

  // do anything here that needs to be done at desctruction time
  // (e.g. close files, deallocate resources etc.)

}

//
// member functions
//

// ------------ method called for each event  ------------
void AnaAdjacentBX::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace edm;
  using namespace std;
  bool debug = false;

  edm::ESHandle < RPCGeometry > rpcGeo;
  iSetup.get<MuonGeometryRecord>().get(rpcGeo);

  Handle < RPCRecHitCollection > rpcHits;
  iEvent.getByToken(rpcRecHitsLabel, rpcHits);

  const std::vector<const RPCRoll*>& rpcRolls = rpcGeo->rolls();
  for (auto r = rpcRolls.begin(); r != rpcRolls.end(); r++)
  {
    RPCDetId rpcId = (*r)->id();
    RPCGeomServ rpcsrv(rpcId);
    std::string nameRoll = rpcsrv.name();
    if(debug)    std::cout << nameRoll << std::endl;

    typedef std::pair<RPCRecHitCollection::const_iterator, RPCRecHitCollection::const_iterator> rangeRecHits;
    rangeRecHits recHitCollection = rpcHits->get(rpcId);
    RPCRecHitCollection::const_iterator recHit;

    int countRecHitsBarrel = 0;
    int countRecHitsEndcap = 0;
    std::vector<std::pair<int, int>> myDigis;
    if (rpcId.region() == 0)
    {
      bxStatisticsBarrel->Fill(1);
      for (recHit = recHitCollection.first; recHit != recHitCollection.second; recHit++)
      {
std::cout << nameRoll << std::endl;
        countRecHitsBarrel++;
        for (int i = recHit->firstClusterStrip(); i < (recHit->firstClusterStrip() + recHit->clusterSize()); i++)
        {
          myDigis.push_back(make_pair(i, recHit->BunchX()));
        }
        std::cout << "@@@@ rechit number\t" << countRecHitsBarrel << "\tBX\t" << recHit->BunchX() << "\tfirst strip\t"
            << recHit->firstClusterStrip() << "\tlast strip\t"
            << (recHit->firstClusterStrip() + recHit->clusterSize() - 1) << "\tcls\t" << recHit->clusterSize()
            << std::endl;
      }
      if (countRecHitsBarrel == 0)
        bxStatisticsBarrel->Fill(2);
      if (countRecHitsBarrel == 1)
        bxStatisticsBarrel->Fill(3);
      if (!(countRecHitsBarrel > 1))
        continue;
      bool isBareClusters = true;
      for (unsigned int i = 0; i < (myDigis.size() - 1); i++)
      {
        int myStrip1 = myDigis[i].first;
        int myBX1 = myDigis[i].second;
        for (unsigned int j = i + 1; j < myDigis.size(); j++)
        {
          int myStrip2 = myDigis[j].first;
          int myBX2 = myDigis[j].second;
          if (myStrip1 == myStrip2 && myBX1 == myBX2)
            continue;
          if (myStrip1 == (myStrip2 + 1) || myStrip1 == (myStrip2 - 1))
          {
            if (myBX1 == (myBX2 + 1) || myBX1 == (myBX2 - 1))
            {
//               std::cout << "@@@@ myStrip1\t" << myStrip1 << "\tmyBX1\t" << myBX1 << "\tmyStrip2\t" << myStrip2 << "\tmyBX2\t" << myBX2 << std::endl;
              if ((myBX1 == 0 && myBX2 == 1) || (myBX2 == 0 && myBX1 == 1))
                bxStatisticsBarrel->Fill(6);
              if ((myBX1 == 0 && myBX2 == -1) || (myBX2 == 0 && myBX1 == -1))
                bxStatisticsBarrel->Fill(7);
              if ((myBX1 == 2 && myBX2 == 1) || (myBX2 == 2 && myBX1 == 1))
                bxStatisticsBarrel->Fill(9);
              if ((myBX1 == -2 && myBX2 == -1) || (myBX2 == -2 && myBX1 == -1))
                bxStatisticsBarrel->Fill(10);
              isBareClusters = false;
            }
          }
        }
      }
      if (isBareClusters)
        bxStatisticsBarrel->Fill(4);
      else
        bxStatisticsBarrel->Fill(5);
    }
    else
    {
      bxStatisticsEndcap->Fill(1);
      for (recHit = recHitCollection.first; recHit != recHitCollection.second; recHit++)
      {
        countRecHitsEndcap++;
        for (int i = recHit->firstClusterStrip(); i < (recHit->firstClusterStrip() + recHit->clusterSize()); i++)
        {
          myDigis.push_back(make_pair(i, recHit->BunchX()));
        }
        std::cout << "@@@@ rechit number\t" << countRecHitsEndcap << "\tBX\t" << recHit->BunchX() << "\tfirst strip\t"
            << recHit->firstClusterStrip() << "\tlast strip\t"
            << (recHit->firstClusterStrip() + recHit->clusterSize() - 1) << "\tcls\t" << recHit->clusterSize()
            << std::endl;
      }
      if (countRecHitsEndcap == 0)
        bxStatisticsEndcap->Fill(2);
      if (countRecHitsEndcap == 1)
        bxStatisticsEndcap->Fill(3);
      if (!(countRecHitsEndcap > 1))
        continue;
      bool isBareClusters = true;
      for (unsigned int i = 0; i < (myDigis.size() - 1); i++)
      {
        int myStrip1 = myDigis[i].first;
        int myBX1 = myDigis[i].second;
        for (unsigned int j = i + 1; j < myDigis.size(); j++)
        {
          int myStrip2 = myDigis[j].first;
          int myBX2 = myDigis[j].second;
          if (myStrip1 == myStrip2 && myBX1 == myBX2)
            continue;
          if (myStrip1 == (myStrip2 + 1) || myStrip1 == (myStrip2 - 1))
          {
            if (myBX1 == (myBX2 + 1) || myBX1 == (myBX2 - 1))
            {
//               std::cout << "@@@@ myStrip1\t" << myStrip1 << "\tmyBX1\t" << myBX1 << "\tmyStrip2\t" << myStrip2 << "\tmyBX2\t" << myBX2 << std::endl;
              if ((myBX1 == 0 && myBX2 == 1) || (myBX2 == 0 && myBX1 == 1))
                bxStatisticsEndcap->Fill(6);
              if ((myBX1 == 0 && myBX2 == -1) || (myBX2 == 0 && myBX1 == -1))
                bxStatisticsEndcap->Fill(7);
              if ((myBX1 == 2 && myBX2 == 1) || (myBX2 == 2 && myBX1 == 1))
                bxStatisticsEndcap->Fill(9);
              if ((myBX1 == -2 && myBX2 == -1) || (myBX2 == -2 && myBX1 == -1))
                bxStatisticsEndcap->Fill(10);
              isBareClusters = false;
            }
          }
        }
      }
      if (isBareClusters)
        bxStatisticsEndcap->Fill(4);
      else
        bxStatisticsEndcap->Fill(5);
    }
//std::cout << "@@@@ ----------------------------------------------" << std::endl;
  }
}

// ------------ method called once each job just before starting event loop  ------------
void AnaAdjacentBX::beginJob()
{

  edm::Service < TFileService > tFileService;

  bxStatisticsBarrel = tFileService->make < TH1F > ("bxStatisticsBarrel", "bxStatisticsBarrel", 12, 0.5, 12.5);
  bxStatisticsEndcap = tFileService->make < TH1F > ("bxStatisticsEndcap", "bxStatisticsEndcap", 12, 0.5, 12.5);

  bxStatisticsBarrel->GetXaxis()->SetBinLabel(1, "Events");
  bxStatisticsBarrel->GetXaxis()->SetBinLabel(2, "No Clusters");
  bxStatisticsBarrel->GetXaxis()->SetBinLabel(3, "SingleCluster");
  bxStatisticsBarrel->GetXaxis()->SetBinLabel(4, "BareClusters");
  bxStatisticsBarrel->GetXaxis()->SetBinLabel(5, "AddjClusters");
  bxStatisticsBarrel->GetXaxis()->SetBinLabel(6, "0+1 BX");
  bxStatisticsBarrel->GetXaxis()->SetBinLabel(7, "0-1 BX");
  bxStatisticsBarrel->GetXaxis()->SetBinLabel(8, "-1 0 +1 BX");
  bxStatisticsBarrel->GetXaxis()->SetBinLabel(9, "1+2 BX");
  bxStatisticsBarrel->GetXaxis()->SetBinLabel(10, "-1-2 BX");
  bxStatisticsBarrel->GetXaxis()->SetBinLabel(11, "0+2 BX");
  bxStatisticsBarrel->GetXaxis()->SetBinLabel(12, "0-2 BX");

  bxStatisticsEndcap->GetXaxis()->SetBinLabel(1, "Events");
  bxStatisticsEndcap->GetXaxis()->SetBinLabel(2, "No Clusters");
  bxStatisticsEndcap->GetXaxis()->SetBinLabel(3, "SingleCluster");
  bxStatisticsEndcap->GetXaxis()->SetBinLabel(4, "BareClusters");
  bxStatisticsEndcap->GetXaxis()->SetBinLabel(5, "AddjClusters");
  bxStatisticsEndcap->GetXaxis()->SetBinLabel(6, "0+1 BX");
  bxStatisticsEndcap->GetXaxis()->SetBinLabel(7, "0-1 BX");
  bxStatisticsEndcap->GetXaxis()->SetBinLabel(8, "-1 0 +1 BX");
  bxStatisticsEndcap->GetXaxis()->SetBinLabel(9, "1+2 BX");
  bxStatisticsEndcap->GetXaxis()->SetBinLabel(10, "-1-2 BX");
  bxStatisticsEndcap->GetXaxis()->SetBinLabel(11, "0+2 BX");
  bxStatisticsEndcap->GetXaxis()->SetBinLabel(12, "0-2 BX");

}

// ------------ method called once each job just after ending the event loop  ------------
void AnaAdjacentBX::endJob()
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void AnaAdjacentBX::fillDescriptions(edm::ConfigurationDescriptions& descriptions)
{
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE (AnaAdjacentBX);

