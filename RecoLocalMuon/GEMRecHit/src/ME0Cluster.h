#ifndef RecoLocalMuon_ME0Cluster_h
#define RecoLocalMuon_ME0Cluster_h
#include <boost/cstdint.hpp>
class ME0Cluster{
 public:
  ME0Cluster();
  ME0Cluster(int fs,int ls, int bx);
  ~ME0Cluster();

  int firstStrip() const;
  int lastStrip() const;
  int clusterSize() const;
  int bx() const;

  void merge(const ME0Cluster& cl);

  bool operator<(const ME0Cluster& cl) const;
  bool operator==(const ME0Cluster& cl) const;
  bool isAdjacent(const ME0Cluster& cl) const;

 private:
  uint16_t fstrip;
  uint16_t lstrip;
  int16_t bunchx;
};
#endif
