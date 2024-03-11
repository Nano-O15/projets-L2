# Projet - "Algorithme K-Means"

Par OUKHEMANOU Mohand

# DESCRIPTION

Ce projet implémente l'algorithme de partitionnement K-Means en C++. Le partitionnement k-means est une technique courante pour regrouper des données en k clusters en minimisant la variance intra-cluster.

## FONCTIONNEMENT

L'algorithme K-Means divise un ensemble de points en k clusters, où chaque point est attribué au cluster dont le centre (moyenne) est le plus proche. La fonction objectif à minimiser est la somme des carrés des distances entre chaque point et le centre de son cluster.

# **UTILISATION**

Pour lancer le programme, suivez ces étapes :
    1. Compiler le code en exécutant la commande : make.
    2. Exécuter l'algorithme sur un fichier CSV en lançant : 
        -> ./kmeans mon_fichier.csv

## Exemple

Avec le fichiers csv/iris2.csv : 
    -> ./kmeans csv/iris2.csv

Cela générera un nouveau fichier kmeans_clustering.csv contenant le regroupement des données en clusters. Vous pouvez comparer ce fichier avec iris.csv pour évaluer la cohérence du partitionnement proposé (en tenant compte du nombre de répétitions et du nombre de clusters spécifiés).