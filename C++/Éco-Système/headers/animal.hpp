#pragma once

#include "point.hpp"

class Animal {
 protected:
  char initiale;
  Point coords;

  bool fertile = false;
  // bool mortFaim = false;

  int id;
  int age;
  int esperance;
  int faim;
  int pause;
  // restriction de reproduction en nombre de tours
  int restrictRepro;
  int sexe;

 public:
  Animal();
  Point getCoords(void);
  bool getFertile(void);
  char getInitiale(void);
  void manger(void);
  void decrementFaim(void);
  void setId(int pId);
  void setXetY(int pX, int pY);
  void setPause(int pPause);
  void setFertile(void);
  void incrementAge(void);
  void setRestrictRepro(int pRestrictRepro);
  void decrementRestrictRepro(void);
  int getFaim(void);
  int getId(void);
  int getPause(void);
  int getAge(void);
  int getRestrictRepro(void);
  int getSexe(void);
  int getEsperance(void);
  ~Animal();
};