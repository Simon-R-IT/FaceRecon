# include <stdio.h>
# include <stdlib.h>
# include <err.h>
# include <assert.h>
# include <string.h>

/*commentaire inutile*/

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Not enough arguments\n");
    return 0;
  }
  if (!strcmp(argv[1],"add")) {  //ajouter entrée avec Prénom NOm et Couleur
    FILE *f = fopen("database.txt", "a+");
    fprintf(f, "\n%s %s\n%s\n", argv[2], argv[3], argv[4]);
    fclose(f);
  }
  if (!strcmp(argv[1],"open")) { //Ouvre la database (en fait c'est surtout pour le read line par line que c'est la
    FILE *f = fopen("database.txt", "r+");
    char line[256];
    while (fgets(line, sizeof(line), f)) {
      printf("%s", line);
    }
    fclose(f);
  }
  return 0;
} 
