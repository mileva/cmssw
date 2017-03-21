#ifndef RecoLocalMuon_ME0Clusterizer_h
#define RecoLocalMuon_ME0Clusterizer_h
/** \class ME0Clusterizer
 *  \author M. Maggi -- INFN Bari
 */

#include "ME0ClusterContainer.h"
#include "DataFormats/GEMDigi/interface/ME0DigiCollection.h"

class ME0Cluster;
class ME0Clusterizer{
 public:
  ME0Clusterizer();
  ~ME0Clusterizer();
  ME0ClusterContainer doAction(const ME0DigiCollection::Range& digiRange);

 private:
  ME0ClusterContainer doActualAction(ME0ClusterContainer& initialclusters);

 private:
  ME0ClusterContainer cls;
};
#endif
