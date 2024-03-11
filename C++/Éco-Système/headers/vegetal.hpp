#pragma once

#include "point.hpp"

class Vegetal {
 protected:
  Point coords;
  int x, y;
  char initiale;

 public:
  Vegetal();

  Point getCoords(void);

  void setXetY(int pX, int pY);

  char getInitiale(void);

  ~Vegetal();
};