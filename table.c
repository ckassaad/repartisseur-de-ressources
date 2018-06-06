#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include "table.h"

void afficher_processus(processus p){
  printf("Nom du processus: %s\n", p.nom);
  printf("Priorite du processus: %d\n", p.priorite);
  printf("Taille du processus: %f\n", p.taille);
}

table creer_table(){
  table liste;	
  liste.tableau =(processus *)malloc(sizeof(processus ));
  liste.size=0;
  return liste;
}

table ajouter (table liste,  processus p)
{
  int i,j;
  processus temp[liste.size];
  for(i=0;i<liste.size;i++)
    {
      temp[i]=liste.tableau[i];
    }
  liste.tableau=(processus *)malloc(sizeof(processus )*(liste.size+1)); 
  if(liste.tableau==NULL)
    {
      fprintf(stderr, "Not enough memory\n");
    } 
 
  for(i=0;i<liste.size;i++)
    {
      liste.tableau[i]=temp[i];
    }
  
  liste.tableau[liste.size].nom=p.nom;
  liste.tableau[liste.size].priorite=p.priorite;
  liste.tableau[liste.size].taille=p.taille;  
  
  liste.size=(liste.size)+1;
  return liste;
}

table supprimer(table liste)
{
  int i;
  for(i=0;i<liste.size;i++)
    {
      liste.tableau[i]=liste.tableau[i+1];
    }
  processus temp[liste.size-1];
  for(i=0;i<(liste.size-1);i++)
    {
      temp[i]=liste.tableau[i];
    }
  liste.tableau=(processus *)malloc(sizeof(processus )*(liste.size-1)); 
  if(liste.tableau==NULL)
    {
      fprintf(stderr, "Not enough memory\n");
    } 
 
  for(i=0;i<liste.size-1;i++)
    {
      liste.tableau[i]=temp[i];
      }  
  liste.size=liste.size-1;
  return liste;
}

void trier(table liste)
{
  int i,j;
  processus temp;
  for(i=0;i<liste.size;i++)
    {
      for(j=i;j<liste.size;j++)
	{
	  if(liste.tableau[i].priorite>liste.tableau[j].priorite)
	    {
	      temp=liste.tableau[i];
	      liste.tableau[i]=liste.tableau[j];
	      liste.tableau[j]=temp;
	    }
	  else if(liste.tableau[i].priorite==liste.tableau[j].priorite)
	    {
	      if (liste.tableau[i].taille>liste.tableau[j].taille)
		{
		  temp=liste.tableau[i];
		  liste.tableau[i]=liste.tableau[j];
		  liste.tableau[j]=temp;
		}
	    }
	}
    }
}

void liberer(table liste)
{
  int i;
      free(liste.tableau);
}
