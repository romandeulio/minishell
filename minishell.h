/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodeulio <rodeulio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 12:13:14 by rodeulio          #+#    #+#             */
/*   Updated: 2025/05/16 17:15:00 by rodeulio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include "libft_add/libft_add.h"
# include <curses.h>
# include <dirent.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <term.h>
# include <termios.h>
# include <unistd.h>

typedef struct s_rdline
{
	char			*cur_dir;
	char			*line;
}					t_rdline;

typedef struct s_node
{
	char *word;
	t_node *next;
} t_node;

typedef struct s_parsing
{
	int sq;
    int dq;
    t_node *node;
} t_parsing;

typedef enum e_operator
{
	CMD,
	PIPE,
	AND,
	OR,
}					t_operator;

typedef enum e_redirection
{
	NONE,
	TRUNC,
	APPEND,
	HERE_DOC,
}					t_redirection;

typedef struct s_file
{
	char			*file;
	t_redirection	redir;
}					t_file;

typedef struct s_cmd
{
	char			**cmd;
	t_file			infile;
	t_file			outfile;
}					t_cmd;

typedef struct s_arg
{
	t_operator		type;
	t_cmd			cmd;
	t_arg			*left;
	t_arg			*right;
}					t_arg;

typedef struct s_global
{
	char			**env;
	t_rdline		rd;
	t_parsing parsing;
	t_cmd			cmd;
}					t_global;

void				ft_exit(char *msg, t_global *g);
char				*get_cur_dir(t_global *g);
void				minishell(t_global *g);
void				check_and_add_history(char *str);
t_node *new_node(char *word, t_global *g);
void    free_list(t_parsing *p);

#endif
