Ce projet est un exemple de FreeRTOS sur POSIX (Linux, macOS ou Windows WSL).

Il illustre :

Création de tâches (Task A, Task B, Task C et Task D) avec priorités et délais différents

Scheduler FreeRTOS pour gérer les tâches

Synchronisation avec mutex et sémaphores

Utilisation de timer pour déclencher Task C

Task D démarrée depuis Task C

Console thread-safe pour afficher les messages

Structure du projet  
posix_freertos_project/  
├─ FreeRTOS-Kernel/          # Sources FreeRTOS  
├─ posix_freertos_demo/      # Code de l'application  
│  ├─ build/                 # Compilation (généré par CMake)  
│  ├─ inc/                   # Includes locaux  
│  │  ├─ console.h  
│  │  ├─ counter_tasks.h  
│  │  ├─ timer_tasks.h  
│  │  └─ FreeRTOSConfig.h   
│  ├─ src/                   # Code source de l'application  
│  │  ├─ main.c              # Point d'entrée principal  
│  │  ├─ console.c           # Console thread-safe  
│  │  ├─ counter_tasks.c     # Task A + Task B  
│  │  └─ timer_tasks.c       # Task C + Task D + Timer  
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


ou en une seule commande :

mkdir build && cd build && cmake .. && cmake --build . && ./main

[Task A] SharedCounter = 1
[Task B] SharedCounter = 11
>> [Timer] Callback executed
[Task C] Timer triggered, starting Task D...
[Task D] Started!
[Task D] Running...
[Task A] SharedCounter = 12
[Task B] SharedCounter = 22
>> [Timer] Callback executed
[Task C] Timer triggered    
[Task D] Running...
[Task A] SharedCounter = 23 
[Task B] SharedCounter = 33 
>> [Timer] Callback executed
[Task C] Timer triggered    
[Task D] Running...        


Task A : incrémente et affiche le compteur partagé

Task B : lit le compteur, ajoute +10, affiche

Task C : réveillée par le timer et démarre Task D

Task D : s’exécute après avoir été démarrée par Task C

Tous les messages sont thread-safe pour l’accès concurrent
