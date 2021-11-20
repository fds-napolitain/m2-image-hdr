# Sujet #5 Génération d’images à large gamme (HDR).

### Comptes rendus hebdomadaires

Une fois sur la page, cliquer sur Assets pour avoir les différents fichiers relatifs à la release qu'on choisit. 
Les release sont classés par ordre chronologique inverse (récent vers ancien).

https://github.com/fds-napolitain/m2-image-hdr/releases

### Comment compiler

Utilisation de l'outil de build cross-platform CMake.
Il est conseillé d'utiliser un IDE comme CLion (license gratuite pour l'éducation), ou Visual Studio.
Sinon utilisable par ligne de commande.

Pré-requis :
- OpenCV version 4
- C++ 2017
- Qt5

### Architecture

##### Interface: Qt5

Il est assez simple de créer une interface cross platform avec Qt, adaptée donc à une cible universitaire. Plus tard, une piste d'amélioration serait de déplacer le code métier en tant que projet
à part / librairie statique C++. On pourrait ensuite la charger dans une application Qt, mais également Android et autres...

##### Code métier: C++

Nous utiliserons C++ qui possède à la fois les performances et les librairies pour le traitement d'images.
