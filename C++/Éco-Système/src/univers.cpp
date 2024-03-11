#include "../headers/univers.hpp"

#include <string.h>
#include <unistd.h>

#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>

#include "../headers/herbe.hpp"

using namespace std;

#define RESET "\033[0m"
#define GREEN "\033[32m"
#define BRIGHTWHITE "\033[1m\033[37m"
#define BOLDRED "\033[1m\033[31m"
#define BOLDMAGENTA "\033[1m\033[35m"
#define BOLDBLUE "\033[1m\033[34m"
#define BOLDCYAN "\033[1m\033[36m"

Univers::Univers(int pLigne, int pColonne) {
  ligne = pLigne;
  colonne = pColonne;

  tab.resize(ligne, vector<char>(colonne));
}

vector<Point> Univers::casesAlentours(int x, int y) {
  vector<Point> cases;
  cases.resize(8);

  cases[0] = {0, 0, 'F'};  // haut
  cases[1] = {0, 0, 'F'};  // gauche
  cases[2] = {0, 0, 'F'};  // droite
  cases[3] = {0, 0, 'F'};  // bas
  cases[4] = {0, 0, 'F'};  // haut-gauche
  cases[5] = {0, 0, 'F'};  // bas-gauche
  cases[6] = {0, 0, 'F'};  // haut-droite
  cases[7] = {0, 0, 'F'};  // bas-droite

  if (x == 0 && y == 0) {                              // coin haut gauche (A;1)
    cases[2] = {x, y + 1, getCase(x, y + 1)};          // droite
    cases[3] = {x + 1, y, getCase(x + 1, y)};          // bas
    cases[7] = {x + 1, y + 1, getCase(x + 1, y + 1)};  // bas-droite
  } else if (x == 0 && y == colonne - 1) {             // coin haut droite (A;7)
    cases[1] = {x, y - 1, getCase(x, y - 1)};          // gauche
    cases[3] = {x + 1, y, getCase(x + 1, y)};          // bas
    cases[5] = {x + 1, y - 1, getCase(x + 1, y - 1)};  // bas-gauche
  } else if (x == ligne - 1 && y == 0) {               // coin bas gauche (G;1)
    cases[0] = {x - 1, y, getCase(x - 1, y)};          // haut
    cases[2] = {x, y + 1, getCase(x, y + 1)};          // droite
    cases[6] = {x - 1, y + 1, getCase(x - 1, y + 1)};  // haut-droite
  } else if (x == ligne - 1 && y == colonne - 1) {     // coin bas droite (G;7)
    cases[0] = {x - 1, y, getCase(x - 1, y)};          // haut
    cases[1] = {x, y - 1, getCase(x, y - 1)};          // gauche
    cases[4] = {x - 1, y - 1, getCase(x - 1, y - 1)};  // haut-gauche
  } else if (x == 0) {                                 // ligne A
    cases[1] = {x, y - 1, getCase(x, y - 1)};          // gauche
    cases[2] = {x, y + 1, getCase(x, y + 1)};          // droite
    cases[3] = {x + 1, y, getCase(x + 1, y)};          // bas
    cases[5] = {x + 1, y - 1, getCase(x + 1, y - 1)};  // bas-gauche
    cases[7] = {x + 1, y + 1, getCase(x + 1, y + 1)};  // bas-droite
  } else if (y == 0) {                                 // colonne 1
    cases[0] = {x - 1, y, getCase(x - 1, y)};          // haut
    cases[2] = {x, y + 1, getCase(x, y + 1)};          // droite
    cases[3] = {x + 1, y, getCase(x + 1, y)};          // bas
    cases[6] = {x - 1, y + 1, getCase(x - 1, y + 1)};  // haut-droite
    cases[7] = {x + 1, y + 1, getCase(x + 1, y + 1)};  // bas-droite
  } else if (y == colonne - 1) {                       // colonne 7
    cases[0] = {x - 1, y, getCase(x - 1, y)};          // haut
    cases[1] = {x, y - 1, getCase(x, y - 1)};          // gauche
    cases[3] = {x + 1, y, getCase(x + 1, y)};          // bas
    cases[4] = {x - 1, y - 1, getCase(x - 1, y - 1)};  // haut-gauche
    cases[5] = {x + 1, y - 1, getCase(x + 1, y - 1)};  // bas-gauche
  } else if (x == ligne - 1) {                         // ligne G
    cases[0] = {x - 1, y, getCase(x - 1, y)};          // haut
    cases[1] = {x, y - 1, getCase(x, y - 1)};          // gauche
    cases[2] = {x, y + 1, getCase(x, y + 1)};          // droite
    cases[4] = {x - 1, y - 1, getCase(x - 1, y - 1)};  // haut-gauche
    cases[6] = {x - 1, y + 1, getCase(x - 1, y + 1)};  // haut-droite
  } else {
    cases[0] = {x - 1, y, getCase(x - 1, y)};          // haut
    cases[1] = {x, y - 1, getCase(x, y - 1)};          // gauche
    cases[2] = {x, y + 1, getCase(x, y + 1)};          // droite
    cases[3] = {x + 1, y, getCase(x + 1, y)};          // bas
    cases[4] = {x - 1, y - 1, getCase(x - 1, y - 1)};  // haut-gauche
    cases[5] = {x + 1, y - 1, getCase(x + 1, y - 1)};  // bas-gauche
    cases[6] = {x - 1, y + 1, getCase(x - 1, y + 1)};  // haut-droite
    cases[7] = {x + 1, y + 1, getCase(x + 1, y + 1)};  // bas-droite
  }

  return cases;
}

void Univers::afficheInitiale(char initiale, int id, int sexe) {
  switch (initiale) {
    case 'H':
      cout << GREEN << initiale << RESET;
      break;

    case 'S':
      cout << BRIGHTWHITE << initiale << RESET;
      break;

    case 'M':
      if (sexe == 1) cout << BOLDBLUE << initiale << id << RESET;
      if (sexe == 2) cout << BOLDCYAN << initiale << id << RESET;
      break;

    case 'L':
      if (sexe == 1) cout << BOLDRED << initiale << id << RESET;
      if (sexe == 2) cout << BOLDMAGENTA << initiale << id << RESET;
      break;

    default:
      cout << initiale << id << endl;
      break;
  }
}

void Univers::setCase(int ligne, int col, char val) {
  tab[ligne][col] = val;

  if (ligne >= this->ligne || col >= this->colonne || ligne < 0 || col < 0) {
    throw 1;
  }
}

char Univers::getCase(int ligne, int col) { return tab[ligne][col]; }

template <typename T>
void Univers::deplacer(T &animal, vector<Point> cases,
                       vector<Mouton *> &moutons) {
  int x, y;
  size_t i;
  int alea;

  vector<Point> casesPossible;
  // cases contenant des moutons (pour les méchants loups)
  vector<Point> casesMouton;

  for (i = 0; i < cases.size(); i++) {
    if ((animal->getInitiale() == 'M') &&
            ((cases[i].initiale == 'H' || cases[i].initiale == '\0') ||
        cases[i].initiale == 'S')) {
      casesPossible.insert(casesPossible.begin() + casesPossible.size(),
                           cases[i]);
    }

    if (animal->getInitiale() == 'L') {
      if (cases[i].initiale == 'M' && animal->getFaim() < 7) {
        casesMouton.insert(casesMouton.begin() + casesMouton.size(), cases[i]);
      }

      if (cases[i].initiale == 'H' || cases[i].initiale == '\0' ||
          cases[i].initiale == 'S') {
        casesPossible.insert(casesPossible.begin() + casesPossible.size(),
                             cases[i]);
      }
    }
  }

  if (casesPossible.size() == 0) return;

  setCase(animal->getCoords().x, animal->getCoords().y, '\0');

  if (animal->getInitiale() == 'M' || casesMouton.size() == 0) {
    alea = rand() % casesPossible.size();
    x = casesPossible[alea].x;
    y = casesPossible[alea].y;

    if (tab[x][y] == 'H' && animal->getInitiale() == 'M') {
      int index = getIndexHerbes(x, y);
      herbes[index]->setEstMange();
      animal->manger();
    }
  }
  if (animal->getInitiale() == 'L' && casesMouton.size() > 0) {
    // le loup mange un mouton
    alea = rand() % casesMouton.size();
    x = casesMouton[alea].x;
    y = casesMouton[alea].y;

    int indexMouton =
        getIndexVector(moutons, casesMouton[alea].x, casesMouton[alea].y);

    // on supprime le mouton qui va se faire manger
    setCase(moutons[indexMouton]->getCoords().x,
            moutons[indexMouton]->getCoords().y, '\0');

    moutons[indexMouton]->setEstMange();

    // on rassasie le loup
    animal->manger();
  }

  animal->setXetY(x, y);
  setCase(x, y, animal->getInitiale());
}

template <typename T>
void Univers::mourirDeVieillesse(vector<T *> &animaux) {
  string typeAnimal = typeid(T).name();
  for (size_t i = 0; i < animaux.size(); i++) {
    if (animaux[i]->getAge() == animaux[i]->getEsperance()) {
      setCase(animaux[i]->getCoords().x, animaux[i]->getCoords().y, 'S');
      // ajouter sel mine au vecteur sels.
      cout << "    [" << (char)(65 + animaux[i]->getCoords().x)
           << to_string(animaux[i]->getCoords().y + 1) << "] "
           << "Un " << typeAnimal.substr(1) << " meurt de vieillesse." << endl;
      cout << "    Des sels minéraux sont apparus à sa place." << endl;

      delete animaux[i];
      animaux.erase(animaux.begin() + i);
      i--;
    }
  }
}

template <typename T>
void Univers::seFaireManger(vector<T *> &objets) {
  for (size_t i = 0; i < objets.size(); i++) {
    if (objets[i]->getEstMange() && objets[i]->getInitiale() == 'M') {
      cout << "    [" << (char)(65 + objets[i]->getCoords().x)
           << to_string(objets[i]->getCoords().y + 1) << "] ";
      cout << "Un mouton a servi de repas à un loup." << endl;

      delete objets[i];
      objets.erase(objets.begin() + i);
      i--;
    }
  }
}

template <typename T>
void Univers::mourirDeFaim(vector<T *> &animaux) {
  string typeAnimal = typeid(T).name();
  for (size_t i = 0; i < animaux.size(); i++) {
    if (animaux[i]->getFaim() == 0) {
      setCase(animaux[i]->getCoords().x, animaux[i]->getCoords().y, 'S');
      cout << "    [" << (char)(65 + animaux[i]->getCoords().x)
           << to_string(animaux[i]->getCoords().y + 1) << "] "
           << "Un " << typeAnimal.substr(1) << " est mort de faim." << endl;
      cout << "    Des sels minéraux sont apparus à sa place." << endl;

      delete animaux[i];
      animaux.erase(animaux.begin() + i);
      i--;
    }
  }
}

void Univers::repousseHerbe(void) {
  int compte = 0;

  for (int i = 0; i < ligne; i++) {
    for (int j = 0; j < colonne; j++) {
      if (getCase(i, j) == 'S') {
        if (compte == 0) cout << "    [";

        if (compte != 0) cout << ", ";

        cout << (char)(65 + i) << to_string(j + 1);

        Herbe *nouvelleHerbe = new Herbe();
        herbes.push_back(nouvelleHerbe);
        setCase(i, j, nouvelleHerbe->getInitiale());
        nouvelleHerbe->setXetY(i, j);

        compte++;
      }
    }
  }

  if (compte > 0) cout << "] De l'herbe repousse !" << endl;
}

void Univers::tourSuivant(vector<Mouton *> &moutons, vector<Loup *> &loups,
                          int &tours, int &nbrLoups, int &nbrMoutons) {
  for (size_t i = 0; i < moutons.size(); i++) {
    etatAnimal(moutons, moutons[i], moutons, tours, nbrMoutons);
  }
  seFaireManger(herbes);

  sleep(2);

  affiche(moutons, loups);
  cout << BOLDBLUE << "    Tour " << to_string(tours)
       << " (Moutons) | Loups: " << to_string(loups.size())
       << " | Moutons: " << to_string(moutons.size()) << RESET << endl
       << endl;

  mourirDeVieillesse(moutons);
  mourirDeFaim(moutons);

  sleep(2);

  for (size_t j = 0; j < loups.size(); j++) {
    etatAnimal(loups, loups[j], moutons, tours, nbrLoups);
  }

  replacerComestible(herbes);

  affiche(moutons, loups);
  cout << BOLDRED << "    Tour " << to_string(tours)
       << " (Loups) | Loups: " << to_string(loups.size())
       << " | Moutons: " << to_string(moutons.size()) << RESET << endl
       << endl;
  tours++;

  repousseHerbe();
  seFaireManger(moutons);
  mourirDeVieillesse(loups);
  mourirDeFaim(loups);
}

template <typename T, typename U>
void Univers::etatAnimal(vector<T *> &animaux, U &animal,
                         vector<Mouton *> &moutons, int tours,
                         int &nbrAnimaux) {
  int x, y;
  vector<Point> cases;

  string typeAnimal = typeid(U).name();

  x = animal->getCoords().x;
  y = animal->getCoords().y;

  cases = casesAlentours(x, y);

  // reproduction
  for (int j = 0; j < 4; j++) {
    // rien ne devrait se passer au premier tour
    if (tours == 0) break;

    if (cases[j].initiale == animal->getInitiale()) {
      int indexAnimal = getIndexVector(animaux, cases[j].x, cases[j].y);

      if (animal->getSexe() != animaux[indexAnimal]->getSexe() &&
          (animal->getPause() == 0 && animaux[indexAnimal]->getPause() == 0) &&
          (animal->getFertile() && animaux[indexAnimal]->getFertile()) &&
          (animal->getRestrictRepro() == 0 &&
           animaux[indexAnimal]->getRestrictRepro() == 0)) {
        animal->setPause(1);
        animal->setRestrictRepro(5);

        animaux[indexAnimal]->setPause(1);
        animaux[indexAnimal]->setRestrictRepro(5);

        cout << "    [" << typeAnimal.substr(2) << "] [" << (char)(65 + x)
             << to_string(y + 1) << "] ET ["
             << (char)(65 + animaux[indexAnimal]->getCoords().x)
             << to_string(animaux[indexAnimal]->getCoords().y + 1)
             << "] peuvent se reproduire !" << endl;

        // on prend les cases alentours au mouton mere
        if (animal->getSexe() == 2)
          cases = casesAlentours(x, y);
        else if (animaux[indexAnimal]->getSexe() == 2)
          cases = casesAlentours(animaux[indexAnimal]->getCoords().x,
                                 animaux[indexAnimal]->getCoords().y);

        // les 4 premiers index sont les cases adjacentes
        for (int k = 0; k < 4; k++) {
          if (cases[k].initiale == 'H' || cases[k].initiale == '\0') {
            nbrAnimaux++;
            ajouterAnimal(animaux, nbrAnimaux, false, cases[k].x, cases[k].y,
                          1);

            cout << "    Un " << typeAnimal.substr(2) << " est né en ["
                 << (char)(65 + cases[k].x) << to_string(cases[k].y + 1) << "]"
                 << endl;

            break;
          }
        }
      }
    }
  }

  animal->decrementFaim();

  if (animal->getRestrictRepro() > 0) animal->decrementRestrictRepro();

  animal->incrementAge();

  if (animal->getAge() >= 1) animal->setFertile();

  if (animal->getPause() > 0)
    animal->setPause(animal->getPause() - 1);
  else
    deplacer(animal, cases, moutons);
}

void Univers::affiche(vector<Mouton *> moutons, vector<Loup *> loups) {
  int i, j, k;
  int index, sexe, id;

  cout << endl;

  cout << "        ";  // premier espace pour les numéros
  // espaces pour chaque numéro
  for (i = 0; i < colonne; i++) {
    if ((i + 1) > 9) {
      cout << to_string(i + 1) << "       ";
    } else {
      cout << to_string(i + 1) << "        ";
    }
  }

  cout << endl;

  // espace pour première rangée
  cout << "    ";

  // ligne de la première rangée
  for (i = 0; i < colonne; i++) cout << "+--------";
  cout << "+" << endl;  // dernier + de la première rangée

  for (i = 0; i < ligne; i++) {
    // les lettres
    cout << "  " << (char)(65 + i) << " ";
    for (j = 0; j < colonne; j++) {
      // évident
      if (tab[i][j] == '\0') {
        cout << "|        ";
      } else {
        // affiche l'initiale (H, L, M, S)
        // cout << "| " << tab[i][j] << " ";
        if (tab[i][j] == 'M') {
          index = getIndexVector(moutons, i, j);
          id = moutons[index]->getId();
          sexe = moutons[index]->getSexe();
        }
        if (tab[i][j] == 'L') {
          index = getIndexVector(loups, i, j);
          id = loups[index]->getId();
          sexe = loups[index]->getSexe();
        }

        if ((tab[i][j] != 'H' && tab[i][j] != 'S') && id > 9) {
          cout << "|  ";
        } else {
          cout << "|   ";
        }

        afficheInitiale(tab[i][j], id, sexe);
        cout << "  ";

        if (tab[i][j] == 'H' || tab[i][j] == 'S') {
          cout << " ";
        }

        cout << " ";
      }
    }
    // dernier | de chaque rangée
    cout << "|" << endl;

    // espaces de gauche
    cout << "    ";
    for (k = 0; k < colonne; k++) cout << "+--------";

    // dernier + de chaque rangée
    cout << "+" << endl;
  }
}

void Univers::remplirHerbe() {
  for (int i = 0; i < ligne; i++) {
    for (int j = 0; j < colonne; j++) {
      if (tab[i][j] != '\0') continue;

      Herbe *nouvelleHerbe = new Herbe();
      herbes.push_back(nouvelleHerbe);
      setCase(i, j, nouvelleHerbe->getInitiale());
      nouvelleHerbe->setXetY(i, j);
    }
  }
}

template <typename T>
void Univers::replacerComestible(vector<T *> comestibles) {
  int x, y;

  // cout << "Taille comestibles: " << comestibles.size() << endl;
  for (size_t i = 0; i < comestibles.size(); i++) {
    // cout << " " << to_string(i) << endl;
    x = comestibles[i]->getCoords().x;
    y = comestibles[i]->getCoords().y;

    if (tab[x][y] != 'L' && tab[x][y] != 'M' && tab[x][y] != 'S')
      setCase(x, y, comestibles[i]->getInitiale());
  }
  // cout << "oui" << endl;
}

void Univers::ajoutAnimauxInitiaux(vector<Mouton *> &moutons,
                                   vector<Loup *> &loups, int nbrMoutons,
                                   int nbrLoups, int maxAnimaux) {
  for (int i = 0; i < maxAnimaux; i++) {
    if (i < nbrMoutons) ajouterAnimal(moutons, nbrMoutons, true);
    if (i < nbrLoups) ajouterAnimal(loups, nbrLoups, true);
  }
}

template <typename T>
void Univers::ajouterAnimal(vector<T *> &animaux, int nbrAnimaux, bool tourInit,
                            int x, int y, int p) {
  char initialeEnnemie;

  T *nouvelAnimal = new T();
  animaux.push_back(nouvelAnimal);

  if (tourInit) {
    x = rand() % ligne;
    y = rand() % colonne;
    // while (getCase(x, y) != '\0') {
    //   cout << "diff" << endl;
    //   x = rand() % ligne;
    //   y = rand() % colonne;
    // }

    vector<Point> cases = casesAlentours(x, y);

    initialeEnnemie = (nouvelAnimal->getInitiale() == 'M') ? 'L' : 'M';

    bool trouve = true;

    while (trouve) {
      for (size_t i = 0; i < cases.size(); i++) {
        trouve =
            (cases[i].initiale == initialeEnnemie || getCase(x, y) != '\0');
        if (trouve) {
          x = rand() % ligne;
          y = rand() % colonne;

          cases = casesAlentours(x, y);
          break;
        }
      }
    }
  }

  if (tourInit) nbrAnimaux = animaux.size();

  nouvelAnimal->setId(nbrAnimaux);
  nouvelAnimal->setXetY(x, y);

  setCase(x, y, nouvelAnimal->getInitiale());
  nouvelAnimal->setPause(p);
}

int Univers::getIndexHerbes(int x, int y) {
  for (size_t i = 0; i <= herbes.size(); i++) {
    if (herbes[i]->getCoords().x == x && herbes[i]->getCoords().y == y) {
      return i;
    }
  }

  return -1;
}

template <typename T>
int Univers::getIndexVector(std::vector<T *> objets, int x, int y) {
  for (size_t i = 0; i <= objets.size(); i++) {
    if (objets[i]->getCoords().x == x && objets[i]->getCoords().y == y) {
      return i;
    }
  }

  return -1;
}

Univers::~Univers() {
  for (size_t i = 0; i < herbes.size(); i++) delete herbes[i];
}
