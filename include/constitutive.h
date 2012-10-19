#ifndef __CONSTITUTIVE_H__
#define __CONSTITUTIVE_H__

#include "point.h"
#include <vector>
#include <iostream>
#include <ostream>
#include <string>

using std::ostream;

namespace constitutive{

  class material{
  public:
    virtual Real sig(Real eps){return 0;}
    Real tanmod_f(Real eps, Real h){return (sig(eps+h)-sig(eps))/h;}
    Real tanmod_b(Real eps, Real h){return (sig(eps)-sig(eps-h))/h;}
    Real tanmod_c(Real eps, Real h){return (sig(eps+h)-sig(eps-h))/2/h;}
    std::vector<Real> par;
    Real epsult[2];
    Real epsulttol[2];
    std::string description;
//    std::vector<Real> eps_ult;
    void print(std::ostream& os = std::cout) const;
//    friend ostream& operator<< (ostream &out, material &mat);
    friend std::ostream& operator << (std::ostream& os, const material& t){
      t.print(os);return os;
    }
  };

// a concrete class that does not allow cracking: \eps_ultimate=\eps_cracking
  class concrete1: public material{
  public:
    Real sig(Real eps);
    concrete1(Real a, Real b, Real c, Real d);
    concrete1();
  private:
    void init(Real f_ck, Real eps_0, Real eps_cu1, Real eps_cu2);
  };

// a concrete class that allows cracking: \eps_ultimate>\eps_cracking
  class concrete2: public material{
  public:
    Real sig(Real eps);
    concrete2(Real a, Real b, Real c, Real d, Real e, Real f);
    concrete2();
  private:
    void init(Real f_ck, Real eps_0, Real eps_cr1, Real eps_cr2, 
              Real eps_cu1, Real eps_cu2);
  };

  class steel1: public material{
  public:
    Real sig(Real eps);
    steel1(Real a, Real b, Real c, Real d, Real e, Real f);
    steel1();
  private:
    void init(Real f_ck, Real eps_0, Real eps_cu1, Real eps_cu2,
              Real eps_u1, Real eps_u2);  
  };




}
#endif
// Local Variables:
// mode: c++
// End:
