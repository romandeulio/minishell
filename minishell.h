/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbrecqueville <nicolasbrecquevill    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 12:13:14 by rodeulio          #+#    #+#             */
/*   Updated: 2025/05/21 18:10:01 by nicolasbrec      ###   ########.fr       */
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
	int				varenv;
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
	int				error_line;
	t_arg			arg;
}					t_global;

/*------------------------------Parsing------------------------------*/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~Syntax~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// check_syntax.c
int					check_start_error(t_tok_nd *first, t_global *g);
int					check_middle_error(t_tok_nd *first, t_tok_nd *next,
						t_global *g);
int					check_end_error(t_tok_nd *first, t_global *g);
void				check_syntax(t_global *g);

// check_type.c
int					is_operator(t_type t);
int					is_redir(t_type t);
int					is_parenthesis(t_type t);
int					is_cmd(t_type t);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~Token~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// count_len_token.c
void				count_size_sep(char *line, int *sep);
int					count_size_token(char *line, t_tok_stk *stk);
int					count_sep(char *line, int *i, int *count, t_tok_stk *stk);

// defined_token.c
void				defined_type(char *line, t_tok_nd *nd);
// void				defined_state(t_tok_stk *stk, t_tok_nd *nd);

// multi_line_utils.c
int					is_end_line(t_tok_stk *stk);
void				add_semicolon(t_global *g);
void				add_nl_last_nd(t_global *g);

// handle_multi_line.c
void				handle_incomplete_bs(t_global *g);
void				handle_incomplete_op(t_global *g);
void				handle_incomplete_quote(t_global *g);
void				handle_incomplete_parenthesis(t_global *g);

// handle_parsing.c
int					handle_backslash(char *line, int *i, t_tok_stk *stk);
int					handle_sq(char *line, int *i, t_tok_stk *stk);
int					handle_dq(char *line, int *i, t_tok_stk *stk);
int					handle_space_sep(char *line, t_tok_stk *stk);
int					handle_sep(char *line, int *i, t_global *g, t_tok_nd *nd);

// parsing_tok_utils.c
void				handle_parentheses(t_global *g, t_tok_nd *nd);
int					save_sep(char *line, t_tok_nd *nd);
void				check_dollar(char c, t_tok_stk *stk, t_tok_nd *nd);
t_tok_nd			*get_nd(int size, char *line, t_global *g);
char				*realloc_token(char *line, t_tok_nd *last, t_global *g);

// parsing_token.c
int					parse_loop(int *j, char *line, t_global *g, t_tok_nd *nd);
int					parsing_token(char *line, t_global *g, t_tok_nd *nd);
void				check_end_line(t_global *g);
void				parsing_tokens(t_global *g);

/*------------------------------...------------------------------*/

// exit.c
void				ft_exit(char *msg, t_global *g);

// ft_free.c
void				free_and_reset_readline(t_global *g);
void				free_and_reset_parsing(t_global *g);

// handle_error.c
void				close_line(char *token, t_global *g);
void				write_syntax_error(char *token);

// handle_path.c
char				*get_cur_dir(t_global *g);

// history.c
void				check_and_add_history(char *str);

// lst.c
void				lstfree_token(t_tok_stk *p);
void				lstadd_back_token(t_tok_stk *stk, t_tok_nd *nd);
t_tok_nd			*lstnew_nd_token(int size, t_global *g);
t_tok_nd			*lstget_last_nd(t_tok_stk *stk);
int					lstcount_nd_token(t_tok_stk *stk);
void				lstdel_last_nd(t_tok_stk *stk);

// minishell.c
void				print_token(t_global *g);
int					is_operator(t_type t);
int					is_redir(t_type t);
int					is_parenthesis(t_type t);
int					is_cmd(t_type t);
int					is_operator_endline(t_tok_stk *stk);
void				check_order_op(t_global *g);
void				check_order_redir(t_global *g);
void				check_order_parenthesis(t_global *g);
void				check_syntax(t_global *g);
void				parsing(t_global *g);
void				minishell(t_global *g);
int					main(int ac, char **av, char **env);

// utils.c
void				ft_strcpy(char *dst, char *src);
char				*ft_strndup(const char *s, int size);

#endif
