#ifndef RecoLocalMuon_ME0EtaPartitionMask_h
#define RecoLocalMuon_ME0EtaPartitionMask_h

#include <bitset>
#include <vector>

const int maskSIZE=768;			//as the maximum number of strips per eta partition
typedef std::bitset<maskSIZE> EtaPartitionMask;

#endif
