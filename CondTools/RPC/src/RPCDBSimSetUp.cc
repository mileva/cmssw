#include "CondTools/RPC/interface/RPCDBSimSetUp.h"
#include "DataFormats/MuonDetId/interface/RPCDetId.h"

#include <cmath>
#include <math.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include<cstring>
#include<string>
#include<vector>
#include<stdlib.h>
#include <utility>
#include <map>

using namespace std;

RPCDBSimSetUp::RPCDBSimSetUp(const edm::ParameterSet& ps) {
  
  _mapDetIdNoise.clear();
  _mapDetIdEff.clear();
  _bxmap.clear();

    //------------------------ Noise Reading ----------------------------
  edm::FileInPath fp1 = ps.getParameter<edm::FileInPath>("noisemapfile");
  _infile1 = new ifstream(fp1.fullPath().c_str(), std::ios::in);

  int rpcdetid = 0;
  float noiseValue = 0.;

  while(!_infile1->eof())
  {
    *_infile1 >> rpcdetid >> noiseValue;
    _mapDetIdNoise[rpcdetid] = noiseValue;
  }
  _infile1->close();
    

  //------------------------ Eff Reading ----------------------------

  edm::FileInPath fp2 = ps.getParameter<edm::FileInPath>("effmapfile");
  _infile2 = new ifstream(fp2.fullPath().c_str(), std::ios::in);

  rpcdetid = 0;
  float effic = 0.;

  while(!_infile2->eof())
  {
    *_infile2 >> rpcdetid >> effic;
    _mapDetIdEff[rpcdetid] = effic;
  }
  _infile2->close();

  
  //---------------------- Timing reading ------------------------------------

  edm::FileInPath fp3 = ps.getParameter<edm::FileInPath>("timingMap");
  _infile3 = new ifstream(fp3.fullPath().c_str(), std::ios::in);

  uint32_t detUnit = 0;
  float timing = 0.;
  while(!_infile3->eof()){
    *_infile3>>detUnit>>timing;
    _bxmap[RPCDetId(detUnit)] = timing;
  }
  _infile3->close();

  //---------------------- Cluster size --------------------------------------

  edm::FileInPath fp4 = ps.getParameter<edm::FileInPath>("clsmapfile");
  _infile4 = new ifstream(fp4.fullPath().c_str(), ios::in);

  string buffer;
  double sum = 0;
  unsigned int counter = 1;
  unsigned int row = 1;
  std::vector<double> sum_clsize;

  while ( *_infile4 >> buffer ) {
    const char *buffer1 = buffer.c_str();
    double dato = atof(buffer1);
    sum += dato;
    sum_clsize.push_back(sum);

    if(counter == row*20) {
      _clsMap[row] = sum_clsize;
      row++;
      sum = 0;
      sum_clsize.clear();
    }
    counter++;
  }
  _infile4->close();
}

float RPCDBSimSetUp::getNoise(uint32_t id)
{
  map<uint32_t, float>::iterator iter = _mapDetIdNoise.find(id);
  return (iter->second);
}

float RPCDBSimSetUp::getEff(uint32_t id)
{
  map<uint32_t, float>::iterator iter = _mapDetIdEff.find(id);
  return iter->second;
}

float RPCDBSimSetUp::getTime(uint32_t id)
{
  RPCDetId rpcid(id);
  std::map<RPCDetId, float>::iterator iter = _bxmap.find(rpcid);
  return iter->second;
}

std::map< int, std::vector<double> > RPCDBSimSetUp::getClsMap()
{
  return _clsMap;
}

RPCDBSimSetUp::~RPCDBSimSetUp(){
  delete _infile1;
  delete _infile2;
  delete _infile3;
  delete _infile4;
}
