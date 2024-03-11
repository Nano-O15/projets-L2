#include "../headers/animal.hpp"

#include <cstdio>
#include <cstdlib>

Animal::Animal() {
  age = 0;
  sexe = rand() % 2 + 1;
}

Point Animal::getCoords(void) { return coords; }

bool Animal::getFertile(void) { return fertile; }

char Animal::getInitiale() { return initiale; }

void Animal::manger(void) { faim = (initiale == 'M') ? 6 : 10; }

void Animal::decrementFaim(void) { faim--; }

void Animal::setId(int pId) { id = pId; }

void Animal::setXetY(int pX, int pY) {
  coords.x = pX;
  coords.y = pY;
}

void Animal::setPause(int pPause) { pause = pPause; }

void Animal::setFertile() { fertile = true; }

void Animal::incrementAge(void) { age++; }

void Animal::setRestrictRepro(int pRestrictRepro) {
  restrictRepro = pRestrictRepro;
}

void Animal::decrementRestrictRepro(void) { restrictRepro--; }

int Animal::getFaim(void) { return faim; }

int Animal::getId(void) { return id; }

int Animal::getPause(void) { return pause; }

int Animal::getAge(void) { return age; }

int Animal::getRestrictRepro(void) { return restrictRepro; }

int Animal::getSexe() { return sexe; }

int Animal::getEsperance(void) { return esperance; }

Animal::~Animal() {}