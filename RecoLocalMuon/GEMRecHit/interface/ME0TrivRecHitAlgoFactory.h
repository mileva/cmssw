#ifndef RecoLocalMuon_ME0TrivRecHitAlgoFactory_H
#define RecoLocalMuon_ME0TrivRecHitAlgoFactory_H

/** \class ME0TrivRecHitAlgoFactory
 *  Factory of seal plugins for 1D RecHit reconstruction algorithms.
 *  The plugins are concrete implementations of ME0TrivRecHitBaseAlgo base class.
 *
 *  \author G. Cerminara - INFN Torino
 */
#include "FWCore/PluginManager/interface/PluginFactory.h"
#include "RecoLocalMuon/GEMRecHit/interface/ME0TrivRecHitBaseAlgo.h"

typedef edmplugin::PluginFactory<ME0TrivRecHitBaseAlgo *(const edm::ParameterSet &)> ME0TrivRecHitAlgoFactory;
#endif




