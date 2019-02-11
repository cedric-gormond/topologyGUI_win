# topologyGUI pour Windows

Un [Guide Utilisateur](Guide Utilisateur.pdf) illustré est disponible dans le dossier du projet.

## Pour commencer

Créer et/ou modifier des fichiers de contraintes d'architecture NoC pour le logiciel Xilinx Vivado. Ces fichiers de contraintes contiennent l'emplacement de routeurs (blocs) correspondant à une certaine topologie, que l'on veut modifier. Ce programme a été créé pour le **Laboratoire Hubert Curien (CNRS)**.

### Installation

Vous devez extraire le contenu de l'archive dans un espace de travail. Pour utiliser le programme, vous devez lancer l'éxecutable `topologyGUI` contenue dans le dossier.

## Utiliser le programme

### Comment importer un fichier de contrainte ?

Il faut premièrement modifier l’extension du fichier de contrainte au format .**txt** (le logiciel n'arrive pas encore à reconnaître le format. xdc). Ensuite, pour importer un fichier, il faut que celui-ci soit présent dans le répertoire `io` dans répertoire contenant l’exécutable. **Attention, le fichier de contrainte doit avoir le nom suivant : cstr_file.txt**


### Les fichiers de contrainte simplifiés

TopologyGUI permet la génération de fichiers simplifiés. Ces fichiers simplifiés contiennent uniquement les informations essentielles d’un fichier classique (position d’un bloc avec ses coordonnées) et sont donc plus lisibles. Cependant, **ces fichiers simplifiés ne sont pas pris en compte par le logiciel Xilinx Vivado**.

#### Le fichier simplifié original
- Cliquez sur « **Generate simplified constraint file»** pour générer un fichier de contrainte simplifié du fichier original, sans aucune modification. 

#### Le fichier simplifié
- Cliquez sur « **Generate constraint file (simplified)»** pour générer un fichier de contrainte simplifié suivant les caractéristiques sélectionnées auparavant (topologie). 

### Comment modifier d’un fichier de contrainte ?
Il est possible de modifier les caractéristiques d’un fichier de contrainte en appliquant une certaine topologie plus homogène à celui-ci en utilisant la section « **Topology**».

1. Vérifier que la case « **Disable** » de la section **«** **Create constraint file from scratch** » est bien coché.


2. Optionnel : Il est possible de redimensionner le premier bloc (et ainsi **tous les autres blocs**) du fichier de contrainte importé dans la section « **Dimensions** ». Saisissez la hauteur et la largeur du premier bloc.

   Vous avez bien sûr la possibilité d’effectuer aucune modification en sélectionnant l’option « **Default** » de la section « **Dimensions** ». Les dimensions du premier bloc sont affichées.

3. Choisissez la topologie que vous voulez appliquer au fichier de contrainte initial en saisissant la distance **d** ou **r**. Pour rappel, la distance **d** est la distance entre le centre de chaque bloc et la distance **r** est la diagonale entre les blocs hexagonaux. Pour plus d’indications, consultez la partie 3 à propos des topologies. 

4. Enregistrez le fichier de contrainte normalisé ou simplifié au format texte **.txt** ou format. **xdc** en cliquant sur « **Generate constraint file** » ou « **Generate constraint file (simplified)** ». Le fichier original ne sera pas modifié.   


### Comment créer un fichier de contrainte ?

Il est possible de créer un fichier de contrainte (en ignorant le fichier de contrainte importé) en utilisant la section « **Create constraint file from scratch** ».  

#### Création de topologies 2D et 3D 

1. Décochez la case « **Disable** ». En décochant cette case, le fichier de contrainte initial sera ignoré.

2.	Remplissez les caractéristiques du fichier de contrainte de sortie en spécifiant le nombre de routeur en X (**dimX**), le nombre de routeur en Y (**dimY**) et les **coordonnées** du bloc1. Pour plus d’indications, consultez la partie 2.1 à propos des coordonnées des blocs.

3.  Choisissez la topologie à appliquer (**2D maillée, 2D hexagonale, 3D maillée**) et spécifiez la distance **d** ou **r** que vous souhaitez utiliser. Pour plus d’indications, consultez la partie 2 à propos des topologies. 

5.	Enregistrez le fichier de contrainte normalisé ou simplifié au format texte **.txt** ou format. **xdc** en cliquant sur « **Generate constraint file** » ou « **Generate constraint file (simplified)** ».

#### Remarques à propos de la topologie 3D

La topologie 3D maillée ne possède qu’une seule dimension Z, c’est-à-dire que le paramètre **dimZ** est fixé à **1** et ne peut être changé.

### Comment gérer les surfaces d’une topologie ?

Il est possible calculer la surface d’une topologie en utilisant la section « **Surface** ».  

#### Comment calculer la surface d’une topologie ?

- Cliquez sur le bouton « **Generate constraint file** ». La surface calculée est basée sur paramètres des sections précédentes. Vous pouvez soit calculez la surface d’une topologie basée sur un fichier de contrainte importé ou soit calculez la surface d’une topologie crée par le logiciel en prenant soin de décocher la case « **Disable** ». Les surfaces s’affichent de la façon suivante :

#### Comment calculer la distance à partir d’une surface ?

Dans la section « **Surface** », il est possible calculer la distance entre le centre de chaque bloc d’une topologie en spécifiant la surface de celle-ci. Pour pourvoir utiliser ce mode :

1.	Spécifiez la surface à partir de laquelle vous voulez calculer une distance.

2.  Remplissez les caractéristiques du premier bloc de la topologie en utilisant la section en spécifiant le nombre de routeur en X (**dimX**), le nombre de routeur en Y (**dimY**) et les **coordonnées** du bloc1. Pour plus d’indications, consultez la partie 3.1 à propos des coordonnées des blocs.

3.  Appuyez sur le bouton **« Get Distance** » pour voir affichez le résultat, respectif à chaque topologie.

4.  Vous pouvez appliquer la distance **d** ou **r** calculée en sélectionnant la distance propre à la topologie souhaitée et en cliquant sur « **Apply selected distance** ». Le résultat apparaitra ainsi dans la section « **Topology** ».

### Comment récupérer un fichier de contrainte généré ?

Les fichiers de contrainte (normalisés ou simplifiés) sont générés dans le dossier `io` du projet au format imposé. Les fichiers générés respectent les appellations suivantes :

| **Topologie** | **Fichier généré (output) :** | **Fichier simplifié généré (output)**   |
| ------------- | ----------------------------- | --------------------------------------- |
| 2D maillée    | cstr_file_2D_generated.txt    | cstr_file_2D_simplified_generated.txt   |
| 2D hexagonale | cstr_file_hexa_generated.txt  | cstr_file_hexa_simplified_generated.txt |
| 3D maillée    | cstr_file_3D_generated.txt    | cstr_file_3D_simplified_generated.txt   |

### Logs

Le logiciel possède une partie log permettant de vous informer sur les différentes opérations effectuées.

### Bugs

Il se peut que le programme possède des bugs ou des erreurs mémoires. S’il-vous-plaît, envoyez un mail à l’adresse suivante ou de proposer une issue sur **Github** afin de les corriger : [cedric.gormond@gmail.com](mailto:cedric.gormond@gmail.com) 

## Développé avec

* [SFML](https://www.sfml-dev.org/community.php)  : Framework open-source permettant de rendus graphiques *(licence ‘as-is’).*

* [ImGui](https://github.com/ocornut/imgui) : Librairie graphique open-source permettant l’utilisation d’un GUI *(licence MIT*)

* [ImGui-SFML](https://github.com/eliasdaler/imgui-sfml)  : Librairie permettant l’intégration de la bibliothèque ImGui au Framework SFML *(licence MIT)*

IDE : 
* Clion Mac & PC

## Auteur

* **Cédric Gormond** - *Etudiant à Télécom Saint-Etienne*

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details
