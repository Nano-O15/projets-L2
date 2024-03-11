#include "../headers/mouton.hpp"

Mouton::Mouton() {
  faim = 6;
  esperance = 50;
  initiale = 'M';
}

bool Mouton::getEstMange(void) { return estMange; }

void Mouton::setEstMange(void) { estMange = true; }

Mouton::~Mouton() {}
