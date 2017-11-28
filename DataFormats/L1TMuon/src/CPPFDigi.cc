// Class for RPC trigger primitives sent from CPPF to EMTF
// Author Alejandro Segura -- Universidad de los Andes

#include "DataFormats/L1TMuon/interface/CPPFDigi.h"

#include <iostream>

namespace l1t {


  CPPFDigi::CPPFDigi( const RPCDetId& _rpcId, int _bx ) : 
    rpcId(_rpcId), bx(_bx), phi_int(-99), theta_int(-99), emtf_sector(-99), valid(-99),
    first_strip(-99), cluster_size(-99), station(-99), phi_glob(-99), theta_glob(-99)
  {
  }
  

  CPPFDigi::CPPFDigi( const RPCDetId& _rpcId, int _bx, int _phi_int, int _theta_int,
  		      int _emtf_sector, int _valid, int _first_strip, int _cluster_size,
  		      int _station, float _phi_glob, float _theta_glob ) :
    rpcId(_rpcId), bx(_bx), phi_int(_phi_int), theta_int(_theta_int), 
    emtf_sector(_emtf_sector), valid(_valid), first_strip(_first_strip), 
    cluster_size(_cluster_size), station(_station), phi_glob(_phi_glob), theta_glob(_theta_glob)
  {
  }

  CPPFDigi * CPPFDigi::clone() const {
    return new CPPFDigi(*this);
  }
  
  std::ostream & operator<<(std::ostream & o, const CPPFDigi& cppf){
    o << "Local integer phi: "   << cppf.Phi_int() ;
    o << "Local integer theta: " << cppf.Theta_int() ;
    return o;
  }
  
} // End namespace l1t
