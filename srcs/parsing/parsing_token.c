/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbrecqueville <nicolasbrecquevill    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 01:08:58 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/05/20 17:27:21 by nicolasbrec      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Erreur de parsing a detecter :
// (TOKEN) Quote jamais refermer (pas obligatoire).
// (TOKEN) Parenthese non fermante ou parenthese fermante sans l'avoir ouvrir
// (AST) Un operateur logique au debut, a la fin,
//	ou plusieurs consequitifs. (a gerer dans l'arbe AST)
// (AST) Redirection sans cmd (mot autre qu'un separateur) qui suit la redirection
// (AST) Deux cmd d'affiler (compter aussi les cmd entre parentheses)

int	parsing_token(char *line, t_global *g, t_tok_nd *nd)
{
	int	i;
	int	j;

	i = 0;
	j = ft_strlen(nd->word);
	while (line[i])
	{
		if (handle_backslash(&line[i], &i, g))
			nd->word[j++] = line[i - 1];
		else if (handle_sq(&line[i], &i, g) || handle_dq(&line[i], &i, g))
			continue ;
		else if (handle_space_sep(&line[i], g))
			break ;
		else if (handle_sep(&line[i], &i, g, nd))
			break ;
		else
		{
			check_dollar(*line, &g->tok_stk, nd);
			g->tok_stk.backslash = 0;
			printf("line[i] = %c\n", line[i]);
			printf("g->tok_stk.dq = %d\n", g->tok_stk.dq);
			nd->word[j++] = line[i++];
		}
	}
	printf("nd->type = %d\n", nd->type);
	// printf("nd->type = %c\n", nd->type);
	if (nd->type == CMD)
		nd->word[j] = '\0';
	return (i);
}

void	parsing_tokens(t_global *g)
{
	int			i;
	int			size;
	t_tok_stk	*stk;
	t_tok_nd	*nd;

	stk = &g->tok_stk;
	nd = stk->top;
	i = 0;
	while (g->rd.line[i])
	{
		while (handle_space_sep(&g->rd.line[i], g))
			i++;
		size = count_size_token(&g->rd.line[i], stk);
		nd = get_nd(size, &g->rd.line[i], g);
		nd->type = CMD;
		i += parsing_token(&g->rd.line[i], g, nd);
		defined_state(stk, nd);
		nd->size = size;
		lstadd_back_token(stk, nd);
		printf("FINAL :\n");
		print_token(g);
	}
}
