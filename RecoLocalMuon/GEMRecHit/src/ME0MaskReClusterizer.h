#ifndef RecoLocalMuon_ME0MaskReClusterizer_h
#define RecoLocalMuon_ME0MaskReClusterizer_h

/** \Class ME0MaskReClusterizer
 *  \author J.C. Sanabria -- UniAndes, Bogota
 *  \modified for ME0 by Roumyana Hadjiiska -- INRNE, BAS
 */

#include "ME0EtaPartitionMask.h"

#include "ME0Cluster.h"
#include "ME0Clusterizer.h"
#include "ME0ClusterContainer.h"

#include "DataFormats/MuonDetId/interface/ME0DetId.h"


class ME0MaskReClusterizer 
{
 public :

   ME0MaskReClusterizer();
   ~ME0MaskReClusterizer();
   ME0ClusterContainer doAction(const ME0DetId& ,ME0ClusterContainer& , const EtaPartitionMask& );
   int get(const EtaPartitionMask& ,int strip);

};

#endif
