#include "fonctions_lecture.h"
#include <string.h> // On inclut string.h pour strchr()
#include <stdio.h>

void vide_buffer()
{
  int c = 0;
  while (c != '\n' && c != EOF)
    {
      c = getchar();
    }
}
void vide_tab(char t[], int t_len){
	int i;
	for(i=0;i<t_len;i++){
		t[i]='\0';
	}
}
int lire(char *chaine, int longueur)
{
  char *position_entree = NULL;
  
  // On lit le texte saisi au clavier
  if(fgets(chaine, longueur, stdin) != NULL)  // Pas d'erreur de saisie ?
    {
      position_entree = strchr(chaine, '\n'); // On recherche l'"Entrée"
      if (position_entree != NULL) // Si on a trouvé le retour à la ligne
	{
	  *position_entree = '\0'; // On remplace ce caractère par \0
        }
      return 1; // On renvoie 1 si la fonction s'est déroulée sans erreur
    }
  else
    {
      vide_buffer();
      return -1; // On renvoie -1 s'il y a eu une erreur
    }
}

