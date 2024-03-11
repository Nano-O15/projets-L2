#include "../headers/vegetal.hpp"

Vegetal::Vegetal() {}

Point Vegetal::getCoords(void) { return coords; }

void Vegetal::setXetY(int pX, int pY) {
  coords.x = pX;
  coords.y = pY;
}

char Vegetal::getInitiale(void) { return initiale; }

Vegetal::~Vegetal() {}