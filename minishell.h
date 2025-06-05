/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbrecqueville <nicolasbrecquevill    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 12:13:14 by rodeulio          #+#    #+#             */
/*   Updated: 2025/06/05 11:48:56 by nicolasbrec      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include "libft_add/libft_add.h"
# include <curses.h>
# include <dirent.h>
# include <fcntl.h>
# include <limits.h>
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

// global
extern volatile sig_atomic_t	g_signal;

// struct
typedef struct s_rdline
{
	char						*cur_dir;
	char						*line;
	char						*full_line;
}								t_rdline;

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
}								t_type;

typedef enum e_state
{
	NORMAL,
	SQ,
	DQ,
}								t_state;

typedef struct s_subtok
{
	char						*subword;
	t_state						state;
	int							varenv;
	int							wildcard;
	struct s_subtok				*next;
}								t_subtok;

typedef struct s_tok_nd
{
	struct s_subtok				*top;
	t_type						type;
	int							heredoc_fd;
	int							paren_lvl;
	struct s_tok_nd				*next;
	struct s_tok_nd				*prev;
}								t_tok_nd;

typedef struct s_tok_stk
{
	t_tok_nd					*top;
	t_state						state;
	int							paren_lvl;
	int							paren_err;
	int							backslash;
}								t_tok_stk;

typedef struct s_cmd
{
	t_subtok					*subtok;
	struct s_cmd				*next;
}								t_cmd;

typedef struct s_cmds
{
	t_cmd						*topcmd;
	char						*file;
	int							heredoc_fd;
	t_type						redir;
}								t_cmds;

typedef struct s_ast
{
	t_type						type;
	int							subshell_lvl;
	t_cmds						*cmds;
	struct s_ast				*left;
	struct s_ast				*right;
}								t_ast;

typedef struct s_parse_ast
{
	int							start;
	int							end;
	int							dir;
	int							paren_lvl;
	t_ast						*previous;
}								t_parse_ast;

typedef struct s_global
{
	char						**env;
	int							error_line;
	int							exit_code;
	int							is_interactive;
	t_rdline					rd;
	t_tok_stk					tok_stk;
	t_ast						*ast;
}								t_global;

/*--------------------------------built_in-------------------------------*/

// cd.c
void							ft_cd(t_global *g, char **cmd);
int								change_path(char *cmd);
void							change_env(t_global *g);
int								find_path(char **env, char *to_find);

// echo.c
void							ft_echo(char **cmd);

// env.c
void							ft_env(t_global *g);
char							**env_cpy(t_global *g, char **env, int size);

// exit.c
void							ft_exit(t_global *g, char **cmd);

// export.c
void							ft_export(t_global *g, char **cmd);
void							env_add(t_global *g, char *cmd);
char							*find_var(char *cmd);

// pwd.c
void							ft_pwd(void);

// unset.c
void							ft_unset(t_global *g, char **cmd);
void							env_remove(t_global *g, char *cmd);
int								find_cmd_to_remove(char **env, char *cmd);

/*--------------------------------Exec-------------------------------*/

// exec_cmd.c
char							*get_path_line(t_global *g, char *line);
char							*get_cmd_path(t_global *g, t_cmd *top);
int								count_arg(t_cmd *top);
char							**get_cmds_in_tab(t_global *g, t_cmd *top);
int								exec_cmdfile(t_global *g, t_cmds *cmds);
int								exec_cmd(t_global *g, t_cmds *cmds);

// exec_op.c
void							exec_pipe_fork(t_global *g, t_ast *ast,
									int p_fd[2], int n_cmd);
int								exec_pipe(t_global *g, t_ast *ast_left,
									t_ast *ast_right);
int								check_operator(t_global *g, t_ast *ast,
									int last_exit);

// exec.c
pid_t							handle_error_fork(t_global *g, pid_t pid,
									int pipe_fd[2]);
int								exec_ast(t_global *g, t_ast *ast);

/*--------------------------------Lst--------------------------------*/

// lst_ast.c
t_ast							*create_ast_cmd(t_global *g, t_tok_nd *start,
									t_tok_nd *end);
t_ast							*create_ast_op(t_global *g, t_tok_nd *pivot);
void							free_ast(t_ast *ast);

// lst_cmd.c
t_cmd							*lstnew_nd_cmd(t_global *g, t_subtok *nd);
void							free_cmd(t_cmd *top);
void							lstadd_back_cmd(t_global *g, t_cmd **top,
									t_subtok *nd);

// lst_subtok.c
t_subtok						*lstnew_nd_subtok(int size, t_global *g);
void							lstfree_subtok(t_subtok **subtok);
t_subtok						*lstget_last_nd_subtok(t_subtok *top);
void							lstadd_back_subtok(t_subtok **top,
									t_subtok *nd);
void							lstdelete_subtok(t_subtok **top, t_subtok *dlt);

// lst_tok.c
t_tok_nd						*lstnew_nd_tok(t_global *g);
void							lstfree_tok(t_tok_stk *p);
void							lstinit_prev_node_tok(t_tok_nd *nd);
void							lstdelete_tok_nd(t_tok_nd **top, t_tok_nd *dlt);

// lst_tok2.c
void							lstadd_back_tok(t_tok_stk *stk, t_tok_nd *nd);
t_tok_nd						*lstget_last_nd_tok(t_tok_nd *top);
int								lstget_pos_nd_tok(t_tok_nd *cur,
									t_tok_nd *target);
int								lstcount_nd_tok(t_tok_stk *stk);
void							lstdel_last_nd_tok(t_tok_stk *stk);

/*------------------------------Parsing------------------------------*/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~Ast~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// handle_priority.c
int								get_priority(t_tok_nd *nd);
t_tok_nd						*get_first_cmd(t_tok_nd *start, t_tok_nd *end);
t_tok_nd						*find_lowest_prio_op(t_tok_nd *start,
									t_tok_nd *end);

// join_subword.c
int								count_join_subword(t_subtok *subtok);
char							*join_subword(t_global *g, t_subtok *subtok);

// parsing_ast.c
void							init_cmdfile(t_global *g, t_cmds *cmds,
									t_tok_nd *nd);
t_cmds							*new_cmds(t_global *g, t_tok_nd *start,
									t_tok_nd *end);
t_ast							*parsing_ast(t_global *g, t_tok_nd *start,
									t_tok_nd *end);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~Expand~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// handle_expand.c
int								check_ch_after_dollar(char c);
int								count_expand_key(char *subword);
char							*get_expand_key(t_global *g, char *subword);
int								cnt_expand_dollar(t_global *g, char *subword,
									int *count);
int								cnt_new_subw_expand(t_global *g, char *subword);
int								expand_dollars(t_global *g, char *subw,
									char *new_subw, int *idx_newsubw);
void							new_subw_expand(t_global *g, t_subtok *subtok);
int								handle_dlt_subtok(t_subtok **top,
									t_subtok **subtok);
int								handle_dlt_tok_nd(t_tok_nd **top,
									t_tok_nd **tok_nd);
void							handle_expand(t_global *g);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~Syntax~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// check_paren_syntax.c
int								check_double_paren(t_tok_nd *first,
									int lvl_ref);
int								check_paren_expr(t_tok_nd *cur);
int								check_paren_close(t_global *g, t_tok_nd *first);
int								check_paren_err(t_global *g, t_tok_nd *first);

// check_syntax.c
int								check_start_err(t_tok_nd *first, t_global *g);
int								check_middle_err(t_tok_nd *first,
									t_tok_nd *next, t_global *g);
int								check_end_err(t_tok_nd *first, t_global *g);
int								check_syntax(t_global *g, int check);

// check_type.c
int								is_operator(t_type t);
int								is_weak_op(t_type t);
int								is_redir(t_type t);
int								is_parenthesis(t_type t);
int								is_cmd(t_type t);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~Token~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// count_len_token.c
void							count_size_sep(char *line, int *sep);
int								count_sep(char *line, int *i, int *count,
									t_tok_stk *stk);
int								count_sq(char *line, int *i, t_tok_stk *stk);
int								count_dq(char *line, int *i, t_tok_stk *stk);
int								count_size_subword(char *line,
									t_tok_stk *original_stk);

// defined_token.c
void							defined_type(char *line, t_tok_nd *nd);
// void				defined_state(t_tok_stk *stk, t_tok_nd *nd);

// handle_heredoc.c
void							handle_heredoc_redir(int fd[2], char *stop);
int								exec_heredoc(t_global *g, char *stop);
void							check_heredoc(t_global *g, t_tok_nd *first);

// handle_inclomplete_line.c
void							handle_incomplete_bs(t_global *g);
void							handle_incomplete_op(t_global *g);
void							handle_incomplete_quote(t_global *g);
void							handle_incomplete_paren2(t_global *g);
void							handle_incomplete_paren(t_global *g);

// handle_multi_line_utils.c
int								is_operator_endline(t_tok_stk *stk);
int								is_end_line(t_tok_stk *stk);
char							*skip_spaces(char *str);
void							add_semicolon(t_global *g);
void							add_nl_last_nd(t_global *g);

// handle_parsing.c
int								handle_backslash(char *line, int *i,
									t_tok_stk *stk);
int								handle_sq(char *line, int *i, t_tok_stk *stk);
int								handle_dq(char *line, int *i, t_tok_stk *stk);
int								handle_space_sep(char *line, t_tok_stk *stk);
int								handle_sep(char *line, int *i, int *j,
									t_global *g);

// parsing_tok_utils.c
void							handle_parentheses(t_global *g, t_tok_nd *nd);
int								save_sep(char *line, t_tok_nd *nd);
void							realloc_subword(char *line, t_global *g,
									t_subtok *last);
t_subtok						*get_and_addback_subtok(char *line, t_global *g,
									t_tok_nd *nd);
t_tok_nd						*get_and_addback_nd(t_global *g);

// parsing_tok_utils2.c
int								is_sep(char *line, t_tok_nd *nd);
void							check_meta(char *line, t_tok_stk *stk,
									t_subtok *subtok);

// parsing_token.c
int								parse_subword(int *j, char *line, t_global *g,
									t_tok_nd *nd);
int								parse_word(char *line, t_global *g,
									t_tok_nd *nd);
void							check_end_line(t_global *g);
void							parsing_tokens(t_global *g);

/*------------------------------Signal------------------------------*/

// ft_kill.c
void							ft_kill(t_global *g, pid_t pid, int signal);

// handle_echoctl.c
void							disable_echoctl(void);
void							enable_echoctl(void);

// handler.c
void							sigint_handler(int signum);
void							handler_no_interactif(int signum);

// reinit_signal.c
void							reinit_sig_heredoc(void);
void							reinit_sigaction(void);

// signal.c
void							interpret_signal(t_global *g);
void							handle_sig_no_interactif(void);
void							reinit_sigaction(void);
void							handle_signal(t_global *g);

/*-------------------------------Utils-------------------------------*/

// utils_minishell.c

// utils.c
int								is_num_str(char *str);
void							ft_strcpy(char *dst, char *src);
void							free_tabstr(char **str);
int								tab_size(char **array);
int								ft_strcmp(const char *s1, const char *s2);

/*------------------------------...------------------------------*/

// exit.c
void							free_readline(t_global *g);
void							exit_free(t_global *g, char *msg, int fd,
									int n_exit);

// ft_free.c
void							free_and_reset_readline(t_global *g);
void							free_and_reset_parsing(t_global *g);
void							reinit_new_line(t_global *g);

// handle_error.c
void							write_endline_error(t_global *g);
void							write_syntax_error(t_global *g,
									t_subtok *subtok);
void							write_syntax_error_newline(t_global *g);

// handle_path.c
char							*get_cur_dir(t_global *g);

// history.c
void							check_and_add_history(char *str);

// minishell.c
void							print_token(t_global *g);
void							parsing(t_global *g);
void							minishell(t_global *g);
int								main(int ac, char **av, char **env);

#endif
