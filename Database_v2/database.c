# include <stdio.h>
# include <stdlib.h>
# include <assert.h>
# include <err.h>

typedef struct
{
  char *name;
  char *fname;
} database;



char *add(char *name)
{
  
}

int data_len(FILE file)
{
  char ch;
  int len = 0;
  while (ch != EOF)
  {
    ch = fgetc(file);
    len++;
  }
  return len;
}

database *read_data(FILE file)
{
  database *data = malloc(data_len + 1) * sizeof(*database));
  int index, end = 0;
  while (end == 0)
  {
    fscanf(data, "%s::%s$\n", &data[i].name, &data[i].fname);
    index++;
    if (data[i].name == "- End."
	end = 1;
  }
  return data;
}

FILE *write_file(database *data)
{
  for (int i = 0; i < sizeof(data) ; i++)
    fprintf(file, "%s::%s$\n", data[i].name, &data[i].fname);
  fprintf("- End.");
}

int main(/*int argc, char *argv[]*/)
{
  FILE *file;
  data = fopen("Database.txt", "w+");
  if (file != NULL)
  {
    read_data(file);
  }
  database *data = read_data(file);
  fclose(file);
  return 0;
}

