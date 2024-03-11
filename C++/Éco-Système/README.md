# Projet - "Éco-Système"

Par OUKHEMANOU Mohand

# DESCRIPTION

Ce projet vise à créer un éco-système en C++, où la survie des espèces dépend de diverses interactions. L'objectif est de maintenir la viabilité de l'éco-système aussi longtemps que possible, avec au moins une espèce encore en vie.

## FONCTIONNEMENT

L'éco-système est composé de moutons, de loups, d'herbe et de sels minéraux. Les loups se nourrissent des moutons pour survivre, tandis que les moutons consomment l'herbe à cette fin. Lorsqu'un loup ou un mouton meurt de faim ou de vieillesse, il laisse des sels minéraux sur sa case, agissant comme engrais pour l'herbe. Les loups ne se mangent pas entre eux et meurent uniquement de vieillesse.

L'éco-système est considéré comme "mort" lorsqu'il ne reste plus ni loups ni moutons vivants.

## INITIALISATION

L'univers est constitué de m*n cases, initialement recouvertes d'herbe. Le nombre de moutons et de loups est défini par l'utilisateur, et les animaux sont placés aléatoirement dans l'univers, avec au plus un animal par case.

Les moutons et les loups se déplacent d'une case par tour, avec huit directions possibles de déplacement.

## CYCLE DE VIE DES ANIMAUX

- Moutons : Ils consomment toute l'herbe d'une case et vivent 50 tours, à moins d'être mangés par un loup. Lorsqu'ils meurent naturellement, ils laissent des sels minéraux sur leur dernière case. Deux moutons adjacents peuvent se reproduire si les conditions le permettent.

- Loups : Ils se nourrissent des moutons et doivent manger un mouton tous les 10 tours pour survivre. Ils meurent de vieillesse après 60 tours ou de faim. Comme les moutons, ils laissent des sels minéraux lors de leur mort et peuvent se reproduire.

## REPRODUCTION 

Les moutons et les loups se reproduisent si deux individus adjacents de sexes compatibles sont présents. Un nouvel individu naît alors sur une case adjacente, à condition que cette case soit libre.

## CROISSANCE DE L'HERBE

L'herbe repousse une fois que des sels minéraux ont été déposés sur une case dépourvue d'herbe.

# **UTILISATION**

Pour lancer le programme, suivez ces étapes :
    1. Compiler le code en exécutant la commande : make.
    2. Exécuter le programme en lançant : ./eco_systeme.