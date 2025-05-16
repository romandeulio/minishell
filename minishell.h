/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodeulio <rodeulio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 12:13:14 by rodeulio          #+#    #+#             */
/*   Updated: 2025/05/16 15:30:47 by rodeulio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

#define MINISHELL_H

#include "libft_add/libft_add.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/wait.h>
#include <signal.h>
#include <termios.h>
#include <curses.h>
#include <term.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_rdline
{
	char *cur_dir;
	char *line;
	char *ertgfre;
} t_rdline;

typedef struct s_global
{
	char **env;
	t_rdline rd;
	
} t_global;


void    ft_exit(char *msg, t_global *g);
char    *get_cur_dir(t_global *g);
void	minishell(t_global *g);

#endif
