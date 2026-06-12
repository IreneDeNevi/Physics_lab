#pragma once

#include <functional>
#include <string>
#include <vector>

#include "PuntoMateriale.h"
#include "Vettore.h"

class OdeSolver {
public:
  explicit OdeSolver(const std::string& method = "Eulero", const std::vector<PuntoMateriale>& p = std::vector<PuntoMateriale>())
      : m_method(method), m_p(p), m_t(0), m_h(0.1) {}

  void Punto(const PuntoMateriale& tmp);
  PuntoMateriale Punto(unsigned int i) const;
  const std::vector<PuntoMateriale>& Punti() const;
  void T(double t0);
  unsigned int N() const;
  double T() const;
  void Passo(double h);
  double Passo() const;
  void Cinematica();

  // External callbacks define the dynamical model.
  std::function<Vettore(unsigned int i, unsigned int j, double t, const std::vector<PuntoMateriale>& p)> fInterna;
  std::function<Vettore(unsigned int i, double t, const std::vector<PuntoMateriale>& p)> fEsterna;

private:
  std::string m_method;
  std::vector<PuntoMateriale> m_p;
  double m_t;
  double m_h;

  Vettore m_eqDiff(unsigned int i, double t, const std::vector<PuntoMateriale>& p) const;
};
