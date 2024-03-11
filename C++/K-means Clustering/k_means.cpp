/*Algorithmique et Structure de Données 2*/
/*OUKHEMANOU Mohand L2-X n°20010867*/
/*Projet*/

#include <math.h>
#include <cstdio>
#include <ctime>
#include <fstream>
#include <iostream>
#include <iterator>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

class PointA
{
public:
  float x;
  float y;
  int groupe;
  float distance_max;

  PointA(float pX, float pY)
  {
    x = pX;
    y = pY;
    groupe = -1;
    distance_max = std::numeric_limits<float>::max();
  }

  float getDistance(PointA a)
  {
    float distance;

    distance = pow((a.x - x), 2) + pow((a.y - y), 2);

    return distance;
  }
};

// La classe Data va nous permettre de stocker dans un vecteur de point,
// l'ensemble des données contenus dans le fichier csv.
class Data
{
public:
  std::vector<PointA> data;

  Data(std::string nom_fichier) { data = lirecsv(nom_fichier); }

  std::vector<PointA> lirecsv(std::string nom_fichier)
  {
    std::string ligne;

    // La fonction ifstream() permet de lire le fichier ligne par ligne.
    std::ifstream fichier(nom_fichier);

    // On vérifie si le fichier est bien ouvert.
    if (fichier.is_open())
    {
      // Tant que le fichier n'est pas vide, on lit chaque ligne (via la fonction getline()).
      while (getline(fichier, ligne))
      {
        // La classe stringstream permet de convertir un string en objet de type file-stream (flux de fichier).
        // Elle va nous permettre d'extraire les éléments qui sont séparés par une virgule (comme dans notre fichier.csv).
        std::stringstream Streamligne(ligne);

        std::string element;

        float x, y;

        //',' correspond à la délimitation.
        getline(Streamligne, element, ',');

        // La fonction stof() permet d'attribuer à x la première valeur (par ligne) lu (avant la virgule) dans le fichier.
        x = std::stof(element);

        getline(Streamligne, element, '\n');

        // Ici on attribue à y la seconde valeur (toujours par ligne) lu (avant le retour à la ligne) dans le fichier.
        y = std::stof(element);

        // On ajoute à notre vecteur, comme point, le couple (x,y).
        data.push_back(PointA(x, y));
      }
    }

    else
    {
      std::cout << "Fichier impossible à ouvrir." << std::endl;
    }

    return data;
  }
};

void creer_nvFichier(Data donnees)
{
  // On ouvre le fichier (on le crée puisqu'il n'existe pas).
  std::ofstream nv_fichier;
  nv_fichier.open("kmeans_clustering.csv");
  nv_fichier << "Point[i] x, Point[i] y, Point[i] groupe" << std::endl;

  // On parcourt les points de nos données un par un, et on les ajoute valeur par valeur avec des séparateurs.
  for (std::vector<PointA>::iterator point = donnees.data.begin(); point != donnees.data.end(); ++point)
  {
    nv_fichier << point->x << "," << point->y << "," << point->groupe << std::endl;
  }

  // Puis nous fermons notre nouveau fichier.
  nv_fichier.close();
}

void k_moyennes(Data donnees, int repetitions, int k)
{
  // La première étape de l'algorithme consiste en l'initialisation des premiers centres de gravité de manière aléatoire (dans un premier temps).
  // On crée un vecteur qui contiendra les centres (qui serviront de référence pour le partitionnement et les groupes).
  std::vector<PointA> centres;

  // On veut choisir nos centres, de manière aléatoire parmi nos points contenus dans nos données.
  // On crée donc un élément de la classe PointA qui contiendra un point choisit aléatoirement parmi ceux de nos données.
  PointA random_element(0.0, 0.0);

  srand(time(NULL));

  // k représente le nombre de centres que l'on veut obtenir (ce sera le nombre de groupes pour partitionner les données).
  for (int i = 0; i < k; i++)
  {
    // On attribue à notre élément, précédemment crée, les valeurs d'un de nos points de données via la fonction at().
    // La fonction at() permet de retourner une référence vers l'élément à la position mis en argument, ici on lui donne une position aléatoire comprise entre 0
    // et la taille maximum de notre vecteur.
    random_element = donnees.data.at(rand() % donnees.data.size());

    // Puis on ajoute cet élément random à notre vecteur de centres.
    centres.push_back(random_element);
  }

  // L'algorithme de k-means consiste à la répétition des étapes 2 (groupement) et 3 (recalcul) jusqu'à ce que les points ne changent plus de groupe.
  for (int i = 0; i < repetitions; i++)
  {
    // La seconde étape consiste à affecter les points de nos données au groupe qui lui correspond, selon sa distance aux différents centres (on l'affecte au groupe du centre le plus proche).
    std::vector<PointA>::iterator centre;

    for (centre = centres.begin(); centre != centres.end(); centre++)
    {
      // On crée la variable du groupe (elle correspond à la position du centre dans le vecteur).
      int index_groupe;

      // Pour accéder aux différents centres de manière individuelle, on crée un iterateur de vecteur de PointA.
      std::vector<PointA>::iterator centre;

      // On parcourt le vecteur de centres.
      for (centre = centres.begin(); centre != centres.end(); centre++)
      {
        // On attribue à notre variable index_groupe l'index du centre dans le vecteur, via la fonction distance().
        // La fonction distance() permet de calculer le nombre d'éléments entre deux positions (ici le début du vecteur et la position du centre).
        index_groupe = std::distance(centres.begin(), centre);

        // On réitère pour accéder aux différents points de nos données de manière individuelle et on crée de nouveau un itérateur de vecteur de PointA.
        std::vector<PointA>::iterator point;

        // On parcourt les données.
        for (point = donnees.data.begin(); point != donnees.data.end(); point++)
        {
          // On crée un objet de type PointA qui correspond au contenu de l'objet courant (soit un point des données).
          PointA a = *point;

          // On crée une variable distance qui, via la fonction getDistance() de notre class PointA, sera égale à la distance entre notre objet (soit un point des données) et un centre.
          float distance = centre->getDistance(a);

          // On comparera alors la distance obtenue avec la valeur de distance max de chaque point (par defaut égale à une valeur max que peut prendre un float (comparable à "l'infini")).
          // Tant que la distance obtenue est inférieure à cette valeur max, alors on attribue à notre objet cette distance comme valeur max
          // et on lui donne comme groupe la valeur de l'index du centre avec lequel on la compare.
          if (distance < a.distance_max)
          {
            a.distance_max = distance;
            a.groupe = index_groupe;
          }
          // Puis on met le contenu du point des données référencé par point aux valeurs de notre objet a.
          *point = a;
        }
      }
    }

    // La dernière étape consiste au recalcule du centre de chaque groupe (qui contient alors plus d'éléments pouvant servir de référence au partitionnement)
    // et de modifier les centres en fonction des résultats du calcul.
    // Pour cela on calcule la moyenne des x, ainsi que la moyenne des y des points du groupe, et on crée un centre avec comme valeur de x et y ces moyennes calculées.
    std::vector<PointA>::iterator point;

    for (point = donnees.data.begin(); point != donnees.data.end(); point++)
    {
      // Comme précédemment, on crée un objet de type PointA qui correspond au contenu de l'objet courant (soit un point des données).
      PointA a = *point;

      // On crée nos variables qui vont servir au calcul de moyennes des points de nos données.
      int nb_points = 0;
      int sommeX = 0;
      int sommeY = 0;

      for (int i = 0; i <= k; i++)
      {
        // Si la valeur de groupe du point courant est égale à i (soit un des index de groupe) alors on augmente nos variables de moyenne.
        if (a.groupe == i)
        {
          nb_points += 1;
          sommeX += a.x;
          sommeY += a.y;

          // On remplace les centres de gravité choisis précédemment aléatoirement par notre nouveau centre aux coordonnées correspondantes aux moyennes des x et des y.
          for (centre = centres.begin(); centre != centres.end(); centre++)
          {
            centre->x = sommeX / nb_points;
            centre->y = sommeY / nb_points;
          }
        }
      }
    }
  }
  // Une fois toutes les répétitions des étapes 2 et 3 terminés, nous créons le nouveau fichier contenant nos groupes.
  creer_nvFichier(donnees);
}

int main(int argc, char *argv[])
{
  if (argc == 2)
  {
    Data donnees(argv[1]);

    // L'algorithme de k-means consiste à la répétition des étapes 2 (groupement) et 3 (recalcul) jusqu'à ce que les points ne changent plus de groupe.
    // Pour faciliter la chose, on va demander à l'utilisateur de fixer une limite de répétitions.
    int repetitions;

    int k;

    std::cout << "Veuillez entrer le nombre de répétitions à effectuer : "
              << std::endl;
    std::cin >> repetitions;

    std::cout << std::endl;

    std::cout << "Veuillez entrer la valeur k, le nombre de groupes souhaités."
              << std::endl;
    std::cin >> k;

    k_moyennes(donnees, repetitions, k);
  }

  else if (argc > 2)
  {
    printf("Trop d'arguments.\n");
  }

  else
  {
    printf("1 argument est attendu.\n");
  }

  return 0;
}