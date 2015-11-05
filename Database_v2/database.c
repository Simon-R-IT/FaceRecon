# include <stdio.h>
# include <stdlib.h>
# include <assert.h>
# include <err.h>

typedef struct
{
  char *name;
  char *fname;
} database;



/*char *add(char *name)
{
  
}*/

unsigned long data_len(FILE *file)
{
  int len = 0;
  fseek(file, 0L, SEEK_END);
  len = ftell(file);
  fseek(file, 0L, SEEK_SET);
  return len;
}

database *read_data(FILE *file)
{
  database *data = malloc(data_len * sizeof(data));
  int index, end = 0;
  while (end == 0)
  {
    fscanf(file, "%s::%s$\n", data[index].name, data[index].fname);
    index++;
    char *end_string = "- End.";
    if (strcmp(data[index].name, end_string) == 0)
	end = 1;
  }
  return data;
}

FILE *write_file(database *data, FILE *file)
{
  
  for (unsigned long i = 0; i < sizeof(data) ; i++)
    fprintf(file, "%s::%s$\n", data[i].name, data[i].fname);
  fprintf(file, "- End.");
}

int main(/*int argc, char *argv[]*/)
{
  FILE *file;
  file = fopen("Database.txt", "w+");
  if (file != NULL)
  {
    read_data(file);
  }
  database *data = read_data(file);
  fclose(file);
  return 0;
}

