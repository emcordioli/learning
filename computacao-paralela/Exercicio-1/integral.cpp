//Baseado em http://rosettacode.org/wiki/Numerical_integration#C.2B.2B
#include <iostream>
#include <cstdlib>
#include <omp.h>
#include "mytime.h"

// the integration routine
template<typename Method, typename F, typename Float>
 double integrate(F f, Float a, Float b, int steps, Method m)
{
  double s = 0;
  double h = (b-a)/steps;
  for (int i = 0; i < steps; ++i)
    s += m(f, a + h*i, h);
  return h*s;
}

// methods
class rectangular
{
public:
  enum position_type { left, middle, right };
  rectangular(position_type pos): position(pos) {}
  template<typename F, typename Float>
   double operator()(F f, Float x, Float h) const
  {
    switch(position)
    {
    case left:
      return f(x);
    case middle:
      return f(x+h/2);
    case right:
      return f(x+h);
    }
    return f(x+h/2); //standard return
  }
private:
  const position_type position;
};

// sample usage
double quad(double x) { return x*x; }
double lin(double x) { return x+2; }
double cubo(double x) { return x*x*x+9*x*x+18*x+27; }

int main(int argc, char *argv[]){
    double resposta;
    double inicio, fim;
    int rets = 1e6;

    if ( argc < 2 ) std::cout << "Estimando integrais com 1M a 100M retangulos." << std::endl;
    else {
        rets = atoi(argv[1]);
        std::cout << "Estimando integrais com " << rets << " a " << rets*100 << " retangulos." << std::endl;
    }

    mytime(&inicio);
    resposta = integrate(quad, 0.0, 1.0, rets, rectangular(rectangular::left));
    mytime(&fim);
    std::cout << "Integral de x^2 de 0 a 1 estimada em " << resposta << " em " << fim - inicio << " segundos." << std::endl;

    mytime(&inicio);
    resposta = integrate(lin, 0.0, 10.0, rets*10, rectangular(rectangular::left));
    mytime(&fim);
    std::cout << "Integral de x+2 de 0 a 10 estimada em " << resposta << " em " << fim - inicio << " segundos." << std::endl;

    mytime(&inicio);
    resposta = integrate(cubo, 3.0, 7.0, rets*100, rectangular(rectangular::left));
    mytime(&fim);
    std::cout << "Integral de x^3+9x^2+18x+27 de 3 a 7 estimada em " << resposta << " em " << fim - inicio << " segundos." << std::endl;

}
