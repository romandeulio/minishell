/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbrecqueville <nicolasbrecquevill    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 12:13:14 by rodeulio          #+#    #+#             */
/*   Updated: 2025/05/19 17:33:02 by nicolasbrec      ###   ########.fr       */
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
	struct s_tok_nd	*next;
}					t_tok_nd;

typedef struct s_tok_stk
{
	t_tok_nd		*top;
	int				sq;
	int				dq;
	int				parenthese;
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

// parsing/check_token_type.c
int					is_parenthese(char *s);
int					is_redir(char *s);
int					is_operator(char *s);
int					is_word(char *s);

// parsing/count_token.c
int					sq_token_len(char *line);
int					dq_token_len(char *line);
int					word_token_len(char *line);
int					token_len(char *line);

// parsing/definited_token.c
void				definited_type(char *line, t_tok_nd *nd);
void				definited_state(char *line, t_tok_nd *nd, t_tok_stk *stk);

// handle_delimiter_token.c
void				handle_parenthese(t_global *g, t_tok_nd *nd);
// void				handle_quote(t_global *g, t_tok_nd *nd);

// parsing/parsing_token.c
int					handle_backslash(char **line, int i, char *word, t_tok_stk *stk);
int					parsing_sq_state(char *line, t_tok_stk *stk, t_tok_nd *nd);
int					parsing_dq_state(char *line, t_tok_stk *stk, t_tok_nd *nd);
int					parsing_normal_state(char *line, t_tok_nd *nd);
int					parsing_separator(char *line, t_tok_nd *nd);
int					parsing_token2(char *line, t_tok_stk *stk, t_tok_nd *nd);
void				parsing_token(t_global *g);

// parsing/save_token.c
int					save_word_quote_state(char *line, char *word,
						char separator);
void				save_word_normal_state(char *line, char *word);
void				save_separator(char *line, char *word, t_type type);

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

// minishell.c
void				parsing(t_global *g);
void				minishell(t_global *g);
int					main(int ac, char **av, char **env);

#endif
