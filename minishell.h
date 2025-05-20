/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodeulio <rodeulio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 12:13:14 by rodeulio          #+#    #+#             */
/*   Updated: 2025/05/20 16:31:26 by rodeulio         ###   ########.fr       */
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

typedef enum e_type
{
	CMD,
	PAREN_OPEN,
	PAREN_CLOSE,
	IN_REDIR,
	OUT_REDIR,
	HERE_DOC,
	APPEND,
	PIPE,
	AND,
	OR,
	SEMICOLON,
}					t_type;

typedef enum e_state
{
	NORMAL,
	SQ,
	DQ,
}					t_state;

typedef struct s_tok_nd
{
	char			*word;
	t_type			type;
	t_state			state;
	int				varenv;
	int				size;
	struct s_tok_nd	*next;
}					t_tok_nd;

typedef struct s_tok_stk
{
	t_tok_nd		*top;
	int				sq;
	int				dq;
	int				parenthesis;
	int				backslash;
}					t_tok_stk;

// typedef enum e_operator
// {
// 	CMD,
// 	PIPE,
// 	AND,
// 	OR,
// }						t_operator;

// typedef enum e_redirectory
// {
// 	NONE,
// 	TRUNC,
// 	APPEND,
// 	HERE_DOC,
// }						t_redirectory;

typedef struct s_file
{
	char			*file;
	t_type			redir;
}					t_file;

typedef struct s_token
{
	char			*token;
	t_state			state;
}					t_token;

typedef struct s_cmd
{
	t_token			*token;
	t_file			infile;
	t_file			outfile;
}					t_cmd;

typedef struct s_arg
{
	t_type			type;
	int				subshell;
	t_cmd			cmd;
	struct t_arg	*left;
	struct t_arg	*right;
}					t_arg;

typedef struct s_global
{
	char			**env;
	t_rdline		rd;
	t_tok_stk		tok_stk;
	t_arg			arg;
}					t_global;

/*------------------------------Parsing------------------------------*/

// count_len_token.c
void				count_size_sep(char *line, int *sep);
int					count_size_token(char *line, t_tok_stk *stk);

// count_len_token2.c
int					count_backslash(char *line, int *i, t_tok_stk *stk);
int					count_sq(char *line, int *i, t_tok_stk *stk);
int					count_dq(char *line, int *i, t_tok_stk *stk);
int					count_space_sep(char *line, t_tok_stk *stk);
int					count_sep(char *line, int *i, t_tok_stk *stk);

// defined_token.c

void				defined_type(char *line, t_tok_nd *nd);
void				defined_state(t_tok_stk *stk, t_tok_nd *nd);

// handle_parsing.c
int					handle_backslash(char *line, int *i, t_global *g);
int					handle_sq(char *line, int *i, t_global *g);
int					handle_dq(char *line, int *i, t_global *g);
int					handle_space_sep(char *line, t_global *g);
int					handle_sep(char *line, int *i, t_global *g, t_tok_nd *nd);

// parsing_tok_utils.c
void				handle_parentheses(t_global *g, t_tok_nd *nd);
int					save_sep(char *line, t_tok_nd *nd);
void				check_dollar(char c, t_tok_stk *stk, t_tok_nd *nd);
t_tok_nd			*get_nd(int size, char *line, t_global *g);
void				realloc_token(char *line, t_tok_nd *last, t_tok_stk *stk);

// parsing_token.c
int					parsing_token(char *line, t_global *g, t_tok_nd *nd);
void				parsing_tokens(t_global *g);

/*------------------------------...------------------------------*/

// exit.c
void				ft_exit(char *msg, t_global *g);

// ft_free.c
void				free_and_reset_readline(t_global *g);
void				free_and_reset_parsing(t_global *g);

// handle_error.c
void				write_error_syntax(char *token);

// handle_path.c
char				*get_cur_dir(t_global *g);

// history.c
void				check_and_add_history(char *str);

// lst.c
void				lstfree_token(t_tok_stk *p);
void				lstadd_back_token(t_tok_stk *stk, t_tok_nd *nd);
t_tok_nd			*lstnew_nd_token(int size, t_global *g);
t_tok_nd			*lstlast_nd(t_tok_stk *stk);
int					lstcount_node_token(t_tok_stk *stk);

// minishell.c
void				parsing(t_global *g);
void				minishell(t_global *g);
int					main(int ac, char **av, char **env);

#endif
