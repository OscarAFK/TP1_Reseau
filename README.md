# TPs_Reseau
Sur ce repository sont sotckés les différents TP réalisés dans le cadre du cours de Programmation réseau dans les Jeux Vidéo de l'UQAC, encadré par L. Da Costa.
Ils sont organisés en librairies, avec un executable pour chaque TP, correspondant à la mise en pratique de la librairie.  
Contributeurs:
* Oscar Trosseau
* Florent Bogacz
* Hippolyte Gossoin 

## Instructions
Pour utiliser le projet, téléchargez le en local, puis générez et configurez le projet avec Cmake.  
Une fois cela fait, allez dans le dossier Build, puis ouvrez le fichier TPs_Reseau.sln avec Visual Studio 2019. Générez le projet, des fichiers .exe auront été crées dans le dossier Build\Debug.

## TP1_Reseau
TP1 du cours de réseau pour le Jeux Vidéo à l'UQAC, portant sur l'utilisation des Sockets de Berkeley sous windows.    

### Utilisation  
Avez cmd, lancez le fichier TP1_Server.exe de la manière suivante:  
```TP1_Server.exe port```  
en remplaçant "port" par le numéro de port sur lequel vous souhaitez que le serveur soit visible (i.e: 8888).  

Dans un second temps, lancez le fichier TP1_Client.exe de la manière suivante:  
```TP1_Client.exe addresse port```  
en remplaçant "adresse" par l'adresse sur laquelle vous souhaitez vous connecter (i.e: localhost).  

### Question  
Sur le TP, la question suivante est posée:  
Quel protocole choisi-t-on pour le chat du jeu vidéo ? UDP ou TCP et pourquoi ?   

On choisira le protocole TCP, car on souhaite être certain que le message arrive bien à destination.  

## TP2_Reseau
TP1 du cours de réseau pour le Jeux Vidéo à l'UQAC, portant sur l'utilisation des Sockets de Berkeley sous windows.    

### Utilisation
Avez cmd, lancez le fichier TP2_PlayerSerialization.exe de la manière suivante:  
```TP2_PlayerSerialization.exe```  

### Notes
Dans le programme, on créer un objet player, qu'on compresse, sérialise, déserialise et décompresse. On affiche ses valeurs avant et après la sérialisation. Des détailles sur les différentes étapes de la compression/décompression sont affichés. Par manque de temps, nous n'avons pas pu implémenter la sérialisation d'une chaine de caractères.
