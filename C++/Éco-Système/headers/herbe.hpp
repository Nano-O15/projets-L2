#pragma once

#include "vegetal.hpp"

class Herbe : public Vegetal {
 protected:
  bool estMange = false;

 public:
  Herbe();
  bool getEstMange(void);
  void setEstMange(void);
  ~Herbe();
};