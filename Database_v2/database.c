# include <stdio.h>
# include <stdlib.h>
# include <assert.h>
# include <err.h>
# include <string.h>

typedef struct
{
  char *name;
  char *fname;
} database;



/*char *add(char *name)
{
  
}

unsigned long data_len(FILE *file)
{
  int len = 0;
  fseek(file, 0L, SEEK_END);
  len = ftell(file);
  fseek(file, 0L, SEEK_SET);
  return len;
}*/

database *init_database()
{
  database *data = malloc(sizeof(database));
  data->name = NULL;
  data->fname = NULL;
  return data;
}

int str_len(char *s)
{
  int len = 0;
  while (*(s + len) != '\0')
    len++;
  return len;
}

int read_data(FILE *file, database *data)
{
  int index = 0;
  char *name = NULL, *fname = NULL;
  while (end == 0)
  {
    data = realloc(data, sizeof(data) * (index + 1) * 2);
    fscanf(file, "%s::%s$\n", name, fname);
    data[index].name = malloc(str_len(name)*sizeof(char) + 1);
    strcpy(data[index].name, name);
    data[index].fname = malloc(str_len(fname)*sizeof(char) + 1);
    strcpy(data[index].fname, fname);
    index++;
    char *end_string = "- End.";
    if (strcmp(data[index].name, end_string) == 0)
	end = 1;
  }
  return index;
}

/*void write_file(database *data, FILE *for)
{
  unsigned (file long i = 0; i < sizeof(data) ; i++)
    fprintf(file, "%s::%s$\n", data[i].name, data[i].fname);
  fprintf(file, "- End.");
  }*/

void print_database(database *data, int index)
{
  printf("Content of the database:\n");
  for (int i = 0; i < index; i++)
    printf("\t%s %s\n", data[i].name, data[i].fname);
}

int main(/*int argc, char *argv[]*/)
{
  printf("coucou");
  FILE *file;
  file = fopen("Database.txt", "r");
  printf("Crash before init");
  database *data = init_database();
  printf("Crash before read");
  int nb_elt = read_data(file, data);
  printf("Crash before print");
  print_database(data, nb_elt);
  //write_file(data, file);
  fclose(file);
  free(data);
  return 0;
}

