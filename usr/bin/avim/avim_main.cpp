/*
 * Copyright (C) 2015 Alvaro Stagg. [alvarostagg@openmailbox.org]
 *		 2015 Dan Rulos. [amaya@amayaos.com]
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include "avim_command.h"
#include "avim_colores.h"
#include "avim_version.h"

void cls();
void editor();

int fp;

char* n_archivo;

int main(int argc, char* argv[])
{
  if(argc < 2)
  {
    printf(VERDE "Uso: " NORMAL "avim archivo.ext\n");
    return -1;
  }
  else if(argc > 3)
  {
    printf(VERDE "Uso: " NORMAL "avim archivo.ext\n");
    return -1;
  }
  else
  {
    n_archivo = argv[1];

    if((fp = open(argv[1], O_WRONLY | O_TRUNC)) < 0)
    {
      /* el archivo no existe, tal vez sea un comando*/
      int n = avim_command_execute(argv[1]);

      /* quiere que creemos un archivo */
      if(n == 3 && argc == 3)
      {
        n_archivo = argv[2];

	touch(argv[2], S_IWUSR | S_IRUSR);
        if((fp = open(argv[2], O_WRONLY)) < 0)
        {
          printf(ROJO "Error: " NORMAL "el archivo no pudo ser creado.\n");
          return -1;
        }
        else
        {
          /* comienza la edición */
          cls();
          editor();

          /* salida exitosa */
          return 0;
        }
      }
      else if(n == 4 && argc == 3)
      {
        n_archivo = argv[2];

	FILE *file1;
	if ((file1 = fopen(argv[2], "r")) == NULL) {
		printf("El archivo de origen '%s' no existe\n", argv[2]);
		return -1;
	}
	char contenido[2048];
	int n_bytes = fread(contenido, 1, sizeof(contenido), file1);
	fclose(file1);
        if((fp = open(argv[2], O_WRONLY)) < 0)
        {
          printf(ROJO "Error: " NORMAL "el archivo %s no pudo ser abierto.\n", argv[0]);
          return -1;
        }
        else
        {
          /* comienza la edición */
          cls();
	  write(fp, contenido, n_bytes);
          editor();

          /* salida exitosa */
          return 0;
        }
      }
    }
    else
    {
      /* comienza la edición */
      cls();
      editor();
    }
  }
  /* salida exitosa */
  return 0;
}

void cls()
{
  char str[] = {0x1b, 0x5b, 0x48, 0x1b, 0x5b, 0x4a, '\0'};
  printf("%s", str);
}

void editor()
{
  char linea[128];
  int n_linea = 1;

  printf(VERDE "AVIM %s" NORMAL " | Editando archivo: " VERDE "%s " NORMAL "|\n\n", VERSION, n_archivo);
  do
  {
    printf("%d ", n_linea);
    gets(linea);

    if(linea[0] == ':' && linea[1] == 'x')
    {
      close(fp);
    }
    n_linea++;

    write(fp, linea, strlen(linea));
    write(fp, "\r\n", 2);
  } while (linea[0] != ':' || linea[1] != 'x');

  cls();
}
