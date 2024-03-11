#include <time.h>

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>

#include "../headers/herbe.hpp"
#include "../headers/loup.hpp"
#include "../headers/mouton.hpp"
#include "../headers/univers.hpp"

#define RESET "\033[0m"
#define RED "\033[31m"

using namespace std;

int main(void) {
  srand(time(NULL));

  int m, n, tours = 0, nbrMoutons, nbrLoups;
  bool mauvaiseReponse = true;

  while (mauvaiseReponse) {
    cout << "Veuillez entrer votre nombre de lignes : " << endl;
    cin >> m;
    if (m > 26) {
      cout << "Votre nombre de lignes doit être inférieur à 26 !" << endl;
      continue;
    }
    mauvaiseReponse = false;
  }

  cout << endl;

  mauvaiseReponse = true;

  while (mauvaiseReponse) {
    cout << "Veuillez entrer votre nombre de colonnes : " << endl;
    cin >> n;
    if (n > 26) {
      cout << "Votre nombre de colonnes doit être inférieur à 26 !" << endl;
      continue;
    }
    mauvaiseReponse = false;
  }

  cout << endl;

  mauvaiseReponse = true;

  while (mauvaiseReponse) {
    cout << "Veuillez entrer votre nombre de moutons : " << endl;
    cin >> nbrMoutons;
    if (nbrMoutons > (m * n) / 2) {
      cout << "Votre nombre de mouton doit être inférieur à "
           << to_string((m * n) / 2) << " !" << endl;
      continue;
    }
    mauvaiseReponse = false;
  }

  cout << endl;

  mauvaiseReponse = true;

  while (mauvaiseReponse) {
    cout << "Veuillez entrer votre nombre de loups : " << endl;
    cin >> nbrLoups;
    if (nbrLoups > (m * n) / 4) {
      cout << "Votre nombre de loups doit être inférieur à "
           << to_string((m * n) / 4) << " !" << endl;
      continue;
    }
    mauvaiseReponse = false;
  }

  int maxAnimaux;
  bool finDuMonde = false;

  vector<Mouton *> moutons;
  vector<Loup *> loups;

  Univers ecran = Univers(m, n);

  maxAnimaux = max(nbrMoutons, nbrLoups);

  ecran.ajoutAnimauxInitiaux(moutons, loups, nbrMoutons, nbrLoups, maxAnimaux);
  ecran.remplirHerbe();

  ecran.affiche(moutons, loups);
  cout << "    Tour " << to_string(tours)
       << " | Loups: " << to_string(loups.size())
       << " | Moutons: " << to_string(moutons.size()) << endl
       << endl;
  tours++;

  while (!finDuMonde) {
    ecran.tourSuivant(moutons, loups, tours, nbrLoups, nbrMoutons);

    if (moutons.size() == 0 && loups.size() == 0) {
      ecran.affiche(moutons, loups);
      cout << "    Tour " << to_string(tours)
           << " | Loups: " << to_string(loups.size())
           << " | Moutons: " << to_string(moutons.size()) << endl;
      cout << endl;
      cout << RED << "    Il n'y a plus de moutons, ni de loups." << endl
           << "    Cet univers n'est plus viable !" << RESET << endl << endl;
      finDuMonde = true;
    }
  }

  for (size_t i = 0; i < moutons.size(); i++) delete moutons[i];
  for (size_t i = 0; i < loups.size(); i++) delete loups[i];

  return EXIT_SUCCESS;
}
