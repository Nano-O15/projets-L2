# Projet - "Compression/Décompression de Huffman"

Par OUKHEMANOU Mohand

# DESCRIPTION

Ce projet consiste en une implémentation en langage C de l'algorithme de Compression/Décompression de Huffman. 
Le codage de Huffman est une méthode de compression de données qui permet de réduire la taille des fichiers tout en préservant l'intégrité de l'information. Il fonctionne en utilisant un système de codage à longueurs variables pour représenter chaque symbole de la source, tel qu'un caractère dans un fichier. L'algorithme repose sur la construction d'un arbre de Huffman composé de nœuds.

# **UTILISATION**

Pour lancer le programme, suivez ces étapes :
    1. Compiler le code en exécutant la commande : make.
    2. Exécuter l'algorithme sur un fichier en lançant : 
        -> pour compresser : ./huffman -c mon_fichier.txt
        -> pour décompresser : ./huffman -d mon_fichier.txt.huff

## Exemple

Avec le fichier projet.txt : 
    -> pour la compression : ./huffman -c projet.txt
    -> pour la décompression : ./huffman -d projet.txt.huff