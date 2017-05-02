# Fauxtoshop

Fauxtoshop (pronounced like Photoshop)  is an image processing software developped for a C++/OpenMP class. I contains a Linux command-line interface used for unblurring images, and can be used to stabilize the camera when a photo is taken. The program uses different algorithms to unblur: genetic algorithm, swarm intelligence and ant colony optimization algorithm. These algorithms have been parallelized using OpenMP.

## Français

### Description

Fauxtoshop est un logiciel de traitement d’images avec une interface en ligne de commande fonctionnant sous Linux. Il permet de déflouter les images, et peut être embarqué dans des appareils photo pour stabiliser la caméra. Le programme utilise différents algorithmes de défloutage: algorithme génétique, intelligence distribuée et algorithme de colonies de fourmis. Ces algorithmes ont été par la suite parallélisés en utilisant OpenMP.

### Commandes

Le programme est appelé depuis le terminal en lançant le fichier Fauxtoshop dans le répertoire
Fauxtoshop défini à l’installation, avec la commande « ./Fauxtoshop ».

Une ligne de commande doit ressembler à :

```./Fauxtoshop --deblur (--chrono) (--parallel <nombre de threads>) entrée.png (sortie .png)```

Où les arguments sont :

```./ Fauxtoshop``` : Nom du programme à exécuter

```--deblur``` : Traitement de défloutage à appliquer sur l'image

```--chrono``` : Cette commande va ajouter un compteur de temps en millisecondes qui décomptera le
temps pris par le programme pour déflouter l'image

```--parallel``` : Pour exécuter le programme en séquentiel, omettez la commande ci-dessus ou indiquez
1 comme nombre de thread. Pour exécuter le programme en parallèle, ajoutez cette
commande suivi du nombre de threads à n’importe quel endroit de la ligne de
commande avant le/les noms de fichiers d’entrée/sortie.

```entree.png``` : Image à traiter. Si le fichier de sortie n’est pas spécifié, le résultat du/des traitement(s) sera sauvegardé par-dessus et écrasera le fichier. Le fichier d’entrée doit exister et être
au format *.png.

```sortie.png``` : Si spécifié, le résultat du/des traitement(s) sera sauvegardé dans un fichier correspondant
au nom spécifié. Si le fichier existe déjà, il sera écrasé, sinon un nouveau fichier sera
crée. Les fichiers d’entrée et/ou de sortie doivent toujours être en fin de la ligne de
commande.

Les arguments entre parenthèses sont optionnels, tandis que les autres sont obligatoires.
