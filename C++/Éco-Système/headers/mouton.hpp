#pragma once

#include "animal.hpp"

class Mouton : public Animal {
 protected:
  bool estMange = false;

 public:
  Mouton();
  bool getEstMange(void);
  void setEstMange(void);
  ~Mouton();
};