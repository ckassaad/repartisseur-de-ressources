typedef struct Processus{
  char* nom;
  int priorite;
  double taille;
} processus;

typedef struct Table{
  processus *tableau;
  int size;
}table;

void afficher_processus(processus p);
table creer_table(); 
table ajouter (table,  processus);   
table supprimer(table); 
void trier(table); 
void liberer(table);
