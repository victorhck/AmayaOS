/*
 * Copyright (C) 2015 Alvaro Stagg. [alvarostagg@openmailbox.org]
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

 #include "avim_command.h"
 #include "avim_colores.h"
 #include "avim_version.h"
 #include <stdio.h>
 #include <string.h>

int create_file_and_edit;

 typedef struct avim_command_tag
 {
 	char* nombre;
 	char* alias;
 	void (*call_back)();
 } avim_command;

 void avim_command_version()
 {
 	printf("AVIM %s\n", VERSION);
 	return;
 }

 void avim_command_help()
 {
 	printf("-v          Te dice la version del editor.\n");
 	printf("-h          Muestra esta ayuda.\n");
 	printf("-c          Lista de comandos dentro del editor.\n");
 	printf("-o <nombre> Crea un archivo para editar.\n");
 	return;
 }

void create_and_edit_file()
{
	create_file_and_edit = _TRUE;
	return;
}

 void avim_command_commands_in_editor()
 {
 	printf(":x         Salir y guardar\n");
 	return;
 }

/* comandos permitidos, de momento solo 4... */
int avim_command_count = 4;

avim_command avim_commands[4] = { 
	{"-version", "-v", avim_command_version}, 
	{"-help", "-h", avim_command_help},
	{"-cie", "-c", avim_command_commands_in_editor},
	{"-ofte", "-o", create_and_edit_file}
 };

int avim_command_execute(char* c_cmd)
{
	int i = 0;

 	for(i = 0; i < avim_command_count; i++)
 	{
 		if(strcmp(c_cmd, avim_commands[i].nombre) == 0 || strcmp(c_cmd, avim_commands[i].alias) == 0)
 		{
 			avim_commands[i].call_back();
			return i;
 		}
 	}
 	/* printf(ROJO "Error:" NORMAL " comando invalido.\n"); */
 	printf(ROJO "Error: " NORMAL "el archivo %s no existe.\n", c_cmd);
	return -1;
}
