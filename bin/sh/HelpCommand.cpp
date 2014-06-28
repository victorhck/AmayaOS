/*
 * Copyright (C) 2009 Niek Linnenbank, 2014 Daniel Martin
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
#include <HashIterator.h>
#include "HelpCommand.h"
#include "ShellCommand.h"

int HelpCommand::execute(Size nparams, char **params)
{
    printf("Amaya-OS Help\r\n");
    printf("Lista de commandos integrados de la consola:\r\n\r\n");

    for (HashIterator<String, ShellCommand> i(&commands); i.hasNext(); i++) {
        printf("%s  %s\r\n", i.current()->getName(), i.current()->help());
    }
    
    printf("\r\n");
    
    printf("Escriba 'ls /bin' para ver los comandos de usuario disponibles\r\n");
    printf("Escriba 'ls /sbin' para ver los comandos del sistema disponibles\r\n");
    printf("Escriba 'ls /bin /sbin' para ver todos los comandos disponibles\r\n");

    
    return 0;
}

INITOBJ(HelpCommand, helpCmd, LIBCRT_DEFAULT)
