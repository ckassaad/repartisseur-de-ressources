#include <stdio.h>
#include <stdlib.h> //free et malloc
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <string.h> //strlen
#include <unistd.h> //write
#include <pthread.h> //for threading, link with lpthread
#include <math.h>

#include "fonctions_lecture.h"
#include "table.h"
#include <semaphore.h>


#define MESSAGE_CLIENT_LEN 2000
#define PORT 3200
#define RESSOURCES "ressources.txt"

int arriere_plan(char* programme)
{
  pid_t pid_fils;
  pid_fils = fork ();  // Duplique le processus. 
  if (pid_fils != 0) // Si c'est le père
     return pid_fils;
  else{
     execlp(programme, programme, NULL);
     // Si il y a une erreur dans execlp
     fprintf (stderr, "une erreur est survenue au sein de execlp\n");
     exit(1);
  }
}

// Pour compiler: gcc -lpthread -lm main.c -o Main
void *gere_connexion(void *);


int main(int argc, char *argv[]){
	int sock_fd, new_sock, c, *new_socket;
	struct sockaddr_in server, client;
	char *message;
	
	//Création de la socket
	sock_fd=socket(AF_INET, SOCK_STREAM, 0);
	if (sock_fd == -1)
	{
		printf("Echec de la création de la socket\n");
	}
	
	//Préparation de la structure sockaddr_in
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons ( PORT );
	
	//Liaison
	if (bind(sock_fd,(struct sockaddr *)&server, sizeof(server))<0)
	{
		puts("Echec du bind");
		printf("Veuilllez changer le numéro de port dans main.c et interro.c\n");
		exit(1);
	}
	puts("Bind reussi");
	
	//Ecoute
	
	listen(sock_fd, 3);
	
	//Acceptation des connexions entrantes
	puts("Dans l'attente de connexions entrantes...");
	c = sizeof(struct sockaddr_in);
	while (new_sock = accept(sock_fd, (struct sockaddr *)&client, (socklen_t *)&c))
	{
		//puts("Connexion acceptée");	
		//Réponse au client
		message = "Bonjour, le serveur Main à reçu votre demande de connexion et l'a acceptée. Un thread vous est alloué afin de pouvoir envoyer vos demandes pour la gestion des ressources";
		write(new_sock, message, strlen(message));
		
		pthread_t sniffer_thread;
		new_socket = malloc(1);
		*new_socket = new_sock;
		
		if (pthread_create(&sniffer_thread, NULL, gere_connexion, (void*) new_socket) <0)
		{
			perror("Could not create thread");
			return 1;
		}
        pthread_join( sniffer_thread , NULL);
        //puts("Gérant de connexion assistée");
	}
	
	if (new_sock<0)
	{
		perror("accept failed");
		return -1;
	}
		return 0;
}

void *gere_connexion(void *socket_fd){
	
	//initialisation de la liste d'attente
		 
	table liste_attente;
	liste_attente=creer_table();
	
	char buffer[100];
	FILE * fd;
	fd=fopen(RESSOURCES,"r");
	
	if (fd == NULL)
	{
		exit(1);
	}
	printf("Le nombre de ressources disponibles est: ");
	fread(buffer,1,100,fd);
	fclose(fd);
	
	double ressource=atof(buffer);
	printf("%f\n",ressource);

	sem_t sem;

	//sem_init() renvoie 0 s’il réussit. S’il échoue, il renvoie -1

	sem_init(&sem, 0, ressource);
/*
	// sem_post() incrémente le sémaphore pointé par sem. Si, à la suite de cet incrément, la valeur du sémaphore devient supérieure  à zéro,  un  autre  processus  ou thread bloqué dans un appel sem_wait(3) sera réveillé et procédera au verrouillage du sémaphore.
	
	int sem_post(&sem);

	//sem_wait() décrémente (verrouille) le sémaphore pointé par sem.  Si  lavaleur du sémaphore est plus grande que 0, la décrémentation 	s’effectue et la fonction  revient  immédiatement.  Si  le  sémaphore  vaut  zéro, l’appel bloquera jusqu’à ce que soit il devienne disponible 	d’effectuer la décrémentation 
	
	int sem_wait(&sem);


	//sem_getvalue()  place  la  valeur  actuelle du sémaphore pointé par sem dans l’entier pointé par sval.
	
	int sem_getvalue(sem_t *sem, int *sval);
	  */

	//Socket
	//Obtenir le fd de la socket
	
	int sock = *(int*)socket_fd;
	int read_size;
	char *message;
	char message_client[2000];
	char *nom_processus;
	int priorite_processus;
	double taille_processus;
	processus p;
	int k=0;
	int m;
	
	int compteur2;
	compteur2=0;
	char str[2];
	char name_id[10];
	
	// Recevoir un message du client
	int sem_temp;
	int i=0;
	int j;
	int size;
	int test;
	int value;
	//	char *nouveau_nom;
	//strcpy(*nouveau_nom, "processus");
	int tab[10][2];
	for(j=0;j<10;j++){
		for(m=0;m<2;m++){
			tab[j][m]=0;
		}
	}
	int compteur=0;
	int l;
	while ((read_size = recv(sock, message_client, MESSAGE_CLIENT_LEN, 0)) > 0)
	{
		i++;
		if(i==1){
			//Renvoyer le message au client
			puts("J'affiche le nom");
			puts(message_client);
			nom_processus=(char *)message_client;
			p.nom=(char *)message_client;
			 
			sprintf(str, "%i", compteur2);
			compteur2++;
			strcpy(name_id, "processus");
			strcat(name_id, str); 
			printf("test: %s\n",name_id);		
			p.nom=name_id;
			vide_tab(message_client, MESSAGE_CLIENT_LEN);
		}
		if(i==2){
			//Renvoyer le message au client
			//puts("J'affiche la priorite");
			//puts(message_client);
			priorite_processus=atoi(message_client);
			p.priorite=priorite_processus;
			vide_tab(message_client, MESSAGE_CLIENT_LEN);
		}
		if(i==3){
			//Renvoyer le message au client
			//puts("J'affiche la taille");
			//puts(message_client);
			taille_processus=strtod(message_client,NULL);
			p.taille=taille_processus;
			vide_tab(message_client, MESSAGE_CLIENT_LEN);
			i=0;
			//printf("llll %s\n", p.nom);
			//puts(p.nom);
			afficher_processus(p);
		
			if(liste_attente.size=0){
				liste_attente=creer_table();
			}
			liste_attente=ajouter(liste_attente,p);
			trier(liste_attente);
			printf("Le premier sur liste d'attente est :%s %i %f \n", liste_attente.tableau[0].nom,liste_attente.tableau[0].priorite,liste_attente.tableau[0].taille);
			sem_getvalue(&sem, &sem_temp);
			printf("Ressources disponibles %d\n", sem_temp);
			if (sem_temp>liste_attente.tableau[0].taille)
			{
			//execlp("./test", "./test", NULL);
				size=(int)ceil(liste_attente.tableau[i].taille);
				for(j=0;j<size;j++){
					sem_wait(&sem);
				}
				test=arriere_plan("/etc/alternatives/emacs");
				if(test != 0){
					tab[compteur][0]=test;
					tab[compteur][1]=size;
					compteur++;
				}
				sem_getvalue(&sem, &sem_temp);
				printf("Ressources disponibles après éxécution %d\n", sem_temp);
				supprimer(liste_attente);
				/*for(j=0;j<10;j++){
					for(l=0;l<10;l++){
						printf("%d ", tab[j][l]);
					}
				}
				* */
			}
			for(m=0;m<10;m++){
			  if(tab[m][0]!=0){
					if( (WIFEXITED(tab[m][0])) || WIFSIGNALED(&tab[m][0]) ){
						printf("La mort du fils  de pid  %d a été détécté!\n", tab[m][0]);
						value=tab[m][1];
						for(j=0;j<value;j++){
							sem_post(&sem);
						}
					}
			  }
			}
		}
		sem_getvalue(&sem, &sem_temp);
	       	printf("Ressources disponibles après libération des fils morts %d", sem_temp);
	}
	if ( read_size == 0 )
	{
		puts("Client déconnecté");
		fflush(stdout);
	}
	else if(read_size == -1)
	{
		perror("recv failed");
	}
	
	//Liberer le pointeur de socket
	free(socket_fd);
	//sem_destroy(&sem);
	//liberer(liste_attente);
	return 0;
}
