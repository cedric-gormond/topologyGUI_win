# topologyGUI_win
(in french)

Créer et/ou modifier des fichiers de contraintes d'architecture NoC pour le logiciel
Xilinx Vivado. Ces fichiers de contraintes contiennent l'emplacement de
routeurs (blocs) correspondant à une certaine topologie, que l'on veut modifier.
Ce programme a été créé pour le **Laboratoire Hubert Curien (CNRS)**.

![main menu](https://user-images.githubusercontent.com/17772801/52050556-30a1ce80-2551-11e9-86b3-0df601561969.png)

## Comment fonctionne le logiciel ?

- Utiliser un fichier de contrainte existant, généré auparavant par Vivado, pour l'importer et modifier ses caractéristiques, notamment la disposition des routeurs.

- Créer un nouveau fichier de contrainte en précisant la disposition des routeurs

![alt sketch](https://user-images.githubusercontent.com/17772801/51992550-7b6a0a80-24ad-11e9-94f2-ee78873cc239.png)

1. **A partir d'un fichier de contrainte**

   Il faut premièrement importer un fichier de contrainte au **format .txt** (le logiciel n'arrive pas encore à reconnaître les format .xdc). Les blocs contenu dans ce fichier ont été placé aléatoirement ou approximativement par l'utilisateur sur Vivado. 

   Le logiciel va ensuite extraire les données de ce fichier de contrainte comme l'ensemble des blocs avec leur position **XY correspondante (slices)**. Il est possible à présent de changer les caractéristiques de ce fichier en définissant une certaine topologie. L'utilisateur a le choix entre une topologie maillée 2D, hexagonale 2D et maillée 3D.

   <u>2D maillée:</u>  l'utilisateur doit spécifier la **distance entre le centre de chaque bloc.** La hauteur et la largeur de chaque bloc est basée sur celle du premier (pbloc1). Il est ainsi possible de conserver la hauteur et largeur du bloc1 par défaut ou de la redimensionner, comme illustré sur la figure 2 avec **w'** et **h'**. ![2d maille](https://user-images.githubusercontent.com/17772801/52047707-e10bd480-2549-11e9-8bd6-777aff1ddad8.png)

   <u>2D hexa:</u> l'utilisateur doit spécifier la **distance (rayon) entre le centre du bloc1 et les centres des n-1 blocs sur le cercle**. Comme pour la topologie 2D maillée, la hauteur et la largeur de chaque bloc est basée sur celle du premier (pbloc1). Il est donc possible de conserver ces donnéees ou de les redimensionner.![2d hexa](https://user-images.githubusercontent.com/17772801/52047706-e10bd480-2549-11e9-8150-920f9b6844f3.png)

<u>3D maillée:</u>  l'utilisateur doit spécifier la **distance entre le centre de chaque bloc.** Cependant, l'utilisateur est limité à seulement une profondeur (pour une meilleure visibilité).  Comme pour la topologie 2D maillée, la hauteur et la largeur de chaque bloc est basée sur celle du premier (pbloc1). Il est donc possible de conserver ces donnéees ou de les redimensionner.

Les blocs en profondeur commencent avec une coordonées **X0 + D/2** et **Y0 + D/2** (voir schéma) 

![3d maille-2](https://user-images.githubusercontent.com/17772801/52051068-ba9e6700-2552-11e9-80ce-84024e3a2d9c.png)

**ATTENTION !** Il n'est encore pas possible de générer une topologie 3D maillée à partir d'une topologie 2D maillée ou hexagonale, et inversement.

2. **Créer un fichier de contrainte à partir de zéro** (WIP)

   Sans importer de fichier, l'utilisateur spéficie :

- les dimensions de son fichier de contrainte **dimX** et **dimY**
- les caractéristiques de son premier routeur, c'est à dire ses coordonnées **X0Y0** et **X1Y1**
- la topologie souhaîtée 
