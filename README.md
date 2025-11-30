# Projet : Exploration de FreeRTOS sous POSIX

Ce dépôt regroupe mes tests autour des mécanismes internes de FreeRTOS, exécutés via le port POSIX.
L’objectif est de comprendre en profondeur le fonctionnement du noyau (ordonnancement, synchronisation, communication inter-tâches) dans un environnement Linux, sans dépendre d’une carte embarquée.

# Contenu

- Mise en place et gestion de tâches (priorités, comportement du scheduler).

- Utilisation de mutex et sémaphores pour la synchronisation.

- Tests de queues et de notifications pour la communication entre tâches.

- Manipulation des timers et exploration des hooks proposés par FreeRTOS.

- Portage et exécution via POSIX threads.

# Ce que ce projet met en avant

- Compréhension pratique des concepts temps réel.

- Expérience avec les mécanismes de synchronisation et la communication inter-tâches.

- Capacité à travailler sur FreeRTOS sans matériel spécifique, grâce au port POSIX.

- Développement en C dans un environnement Linux (Makefile, pthreads).

# Technologies

- FreeRTOS (port POSIX)

- C

- CMake

- Linux
