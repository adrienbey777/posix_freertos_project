Description

Ce projet est un exemple simple de FreeRTOS sur POSIX (Linux, macOS ou Windows WSL).

Il illustre :

Création de tâches (Task A et Task B) avec priorités et délais différents

Scheduler FreeRTOS pour gérer les tâches

Console thread-safe pour afficher les ticks des tâches

Structure du projet

posix_freertos_project/
├─ FreeRTOS-Kernel/          # Sources FreeRTOS
├─ posix_freertos_demo/      # Code de l'application
│  ├─ build/                 # Compilation (généré par CMake)
│  ├─ inc/                   # Includes locaux
│  │  ├─ console.h
│  │  └─ FreeRTOSConfig.h 
│  ├─ src/                   # Code source de l'application
│  │  ├─ main.c              # Point d'entrée principal
│  │  └─ console.c           # Console thread-safe   
│  └─ CMakeLists.txt         # Configuration CMake


Prérequis

CMake 

Compilateur C (GCC ou Clang)

POSIX (Linux, macOS, Windows WSL)

pthread pour threads POSIX

Compilation et exécution avec CMake

Créer un dossier de build et entrer dedans :

mkdir -p build
cd build

Configurer le projet :
cmake ..

Compiler le projet :
cmake --build .

Lancer le binaire :
./main

Résultat attendu
=== Démarrage FreeRTOS ===
Lancement du scheduler...
[Task A] Tick = 0
>> [Task B] Tick = 0
[Task A] Tick = 700
>> [Task B] Tick = 1200
[Task A] Tick = 1400
[Task A] Tick = 2100
...


Les ticks affichent le temps écoulé en “ticks FreeRTOS”

Les messages sont sécurisés pour l’accès depuis plusieurs tâches



Définitions

POSIX (Portable Operating System Interface) est un ensemble de normes définissant des interfaces et services standardisés pour les systèmes d’exploitation, afin de rendre les applications portables entre différents OS compatibles (Linux, macOS, Unix…).

FreeRTOS est un système d'exploitation temps réel léger conçu pour les microcontrôleurs. Il fournit des mécanismes tels que les tâches, les files de messages, les sémaphores et les minuteries, permettant de créer des applications embarquées fiables, prévisibles et performantes.

Dans ce projet, j’utilise une couche POSIX afin de permettre à du code initialement écrit pour FreeRTOS de fonctionner également sous Linux.
Concrètement, je fais passer les API FreeRTOS (tâches, mutex, temporisateurs…) vers leurs équivalents POSIX (pthread, mutex, timer, etc.), ce qui offre :

- une meilleure portabilité du code,

- un environnement de test plus flexible,

- la possibilité d’exécuter la logique FreeRTOS directement sur Linux.