#pragma once

struct Point {
  int x, y;
  /***
   * index 0 => haut
   * index 1 => gauche
   * index 2 => droite
   * index 3 => bas
   * index 4 => haut-gauche
   * index 5 => bas-gauche
   * index 6 => haut-droite
   * index 7 => bas-droite
   * */
  char initiale;
};