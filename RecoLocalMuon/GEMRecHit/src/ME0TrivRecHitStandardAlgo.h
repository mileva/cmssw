#ifndef RecoLocalMuon_ME0TrivRecHitStandardAlgo_H
#define RecoLocalMuon_ME0TrivRecHitStandardAlgo_H

/** \class ME0TrivRecHitStandardAlgo
 *  Concrete implementation of ME0TrivRecHitBaseAlgo.
 *
 *  \author M. Maggi -- INFN Bari
 *  \modified R. Hadjiiska -- INRNE Sofia
 */

#include "RecoLocalMuon/GEMRecHit/interface/ME0TrivRecHitBaseAlgo.h"



class ME0TrivRecHitStandardAlgo : public ME0TrivRecHitBaseAlgo {
 public:
  /// Constructor
  ME0TrivRecHitStandardAlgo(const edm::ParameterSet& config);

  /// Destructor
  virtual ~ME0TrivRecHitStandardAlgo();

  // Operations

  /// Pass the Event Setup to the algo at each event
  virtual void setES(const edm::EventSetup& setup);


  virtual bool compute(const ME0EtaPartition& roll,
                       const ME0Cluster& cluster,
                       LocalPoint& point,
                       LocalError& error) const;


  virtual bool compute(const ME0EtaPartition& roll,
                       const ME0Cluster& cluster,
                       const float& angle,
                       const GlobalPoint& globPos, 
                       LocalPoint& point,
                       LocalError& error) const;
};
#endif


