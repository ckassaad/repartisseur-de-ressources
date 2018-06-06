#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h> //write
#include <sys/socket.h>
#include <arpa/inet.h>// inet_addr
#include <string.h> //strlen
#include "table.h"
#include "fonctions_lecture.h"

#define COMMANDE_LEN 100
#define PRIORITE_LEN 10
#define TAILLE_LEN 10
#define PORT 3200

// Pour compiler: gcc -lpthread interro.c -o interro

int existence_fichier(char *nom_fichier){
  FILE *fichier=NULL;
  fichier=fopen(nom_fichier,"r");
  if(fichier!=NULL){
    fclose(fichier);
    return 1;
  }
  else{
    return 0;
  }
}


int main(int argc, char *argv[]){
  if(argc==1){
	int sock_fd;
	struct sockaddr_in server;
	char reponse_serveur[2000];
	
    char commande[COMMANDE_LEN];
    char priorite_t[PRIORITE_LEN];
    char taille_t[TAILLE_LEN];
    char *position_virgule= NULL;
    int priorite;
    double taille;
    char *message_c;
    char *message_p;
    char *message_t;
    
    //Creation de la socket
	sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (sock_fd == -1)
	{
		printf("La socket n'a pas pu être créé\n");
	}
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_family = AF_INET;
	server.sin_port = htons ( PORT );
	
	// Connexion au serveur distant
	if (connect(sock_fd, (struct sockaddr *)&server, sizeof(server))<0)
	{
		puts("Erreur de connexion");
		return 1;
	}
	puts("Connecté");
	
	// Réception de la réponse du serveur
		if ( recv(sock_fd, reponse_serveur, 2000, 0) <0)
		{
			puts("Pas de reponse");
		}
	//	puts("Reponse reçu");
		puts(reponse_serveur);
    while(1){
		int test=0;
		while(!test){
			printf("Veuillez donner le chemin de la commande à éxécuter (%d caractères max):\n", COMMANDE_LEN);
			lire(commande, COMMANDE_LEN);
			test=existence_fichier(commande);
			if(!test){
				printf("Le fichier n'existe pas!\n");
				//exit(0);
			}
		}
		message_c=commande;
		if (send(sock_fd, message_c, strlen(message_c), 0)<0)
		{
			puts("Envoi échoué");
			return 1;
		}
		vide_tab(commande, COMMANDE_LEN);
		vide_tab(priorite_t, PRIORITE_LEN);
		vide_tab(taille_t, TAILLE_LEN);
		printf("Veuillez saisir sa priorité: \n");
		lire(priorite_t,PRIORITE_LEN);
		priorite=(int)strtod(priorite_t,NULL);
		if(priorite<=0){
			printf("Erreur de lecture\n");
			exit(0);
		}
		message_p=priorite_t;
		if (send(sock_fd, message_p, strlen(message_p), 0)<0)
		{
			puts("Envoi échoué");
			return 1;
		}
		vide_tab(commande, COMMANDE_LEN);
		vide_tab(priorite_t, PRIORITE_LEN);
		vide_tab(taille_t, TAILLE_LEN);
		printf("Veuillez indiquer la taille du processus:\n");
		position_virgule= NULL;
		if(lire(taille_t,TAILLE_LEN))
		{
			// Si lecture du texte ok, convertir le nombre en double et le retourner
			position_virgule = strchr(taille_t, ','); // On recherche la virgule
			if(position_virgule != NULL) // Si on a trouvé la virgule
			{
				*position_virgule = '.'; // On remplace ce caractère par .
			}
		}
		else
		{
			// Si problème de lecture, renvoyer -1
			vide_buffer();
			taille=-1;
		}
		taille=strtod(taille_t,NULL);
		if(taille<=0){
			printf("Erreur de lecture\n");
			exit(0);
		}
		message_t=taille_t;
		if (send(sock_fd, message_t, strlen(message_t), 0)<0)
		{
			puts("Envoi échoué");
			return 1;
		}
		puts("Données envoyées");
		vide_tab(commande, COMMANDE_LEN);
		vide_tab(priorite_t, PRIORITE_LEN);
		vide_tab(taille_t, TAILLE_LEN);
	}
	//Fermeture de la socket
	close(sock_fd);
    return 0;
  }
  else if(argc!=1){
    printf("Usage: %s\n", argv[0]);
    exit(0);
  }
}
