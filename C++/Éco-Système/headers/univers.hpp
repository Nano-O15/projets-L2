#pragma once
#include <vector>

#include "herbe.hpp"
#include "loup.hpp"
#include "mouton.hpp"

class Univers {
 protected:
  int ligne, colonne;
  char val;
  std::vector<std::vector<char>> tab;
  std::vector<Herbe *> herbes;

 public:
  Univers();
  Univers(int pLigne, int pColonne);

  std::vector<Point> casesAlentours(int x, int y);
  void setCase(int ligne, int col, char val);
  void reconstruireTableau(void);
  void affiche(std::vector<Mouton *> moutons, std::vector<Loup *> loups);
  void afficheInitiale(char initiale, int id, int sexe);
  void remplirHerbe();
  void ajoutAnimauxInitiaux(std::vector<Mouton *> &moutons,
                            std::vector<Loup *> &loups, int nbrMoutons,
                            int nbrLoups, int maxAnimaux);
  template <typename T>
  void ajouterAnimal(std::vector<T *> &animaux, int nbrAnimaux, bool tourInit,
                     int x = 0, int y = 0, int p = 0);
  template <typename T, typename U>
  void etatAnimal(std::vector<T *> &animaux, U &animal,
                  std::vector<Mouton *> &moutons, int tours, int &nbrAnimaux);
  void tourSuivant(std::vector<Mouton *> &moutons, std::vector<Loup *> &loups,
                   int &tours, int &nbrLoups, int &nbrMoutons);
  template <typename T>
  void deplacer(T &animal, std::vector<Point> cases,
                std::vector<Mouton *> &moutons);
  template <typename T>
  void mourirDeVieillesse(std::vector<T *> &animaux);
  template <typename T>
  void mourirDeFaim(std::vector<T *> &animaux);
  template <typename T>
  void seReproduire(std::vector<T *> &animaux);
  template <typename T>
  void seFaireManger(std::vector<T *> &objets);
  template <typename T>
  void replacerComestible(std::vector<T *> comestibles);
  void repousseHerbe(void);
  char getCase(int ligne, int col);
  template <typename T>
  int getIndexVector(std::vector<T *> objets, int x, int y);
  int getIndexHerbes(int x, int y);

  ~Univers();
};
