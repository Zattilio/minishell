/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 12:50:05 by mbocquel          #+#    #+#             */
/*   Updated: 2023/03/03 17:51:08 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

void	add_last_left(t_node **root, t_node *node)
{
	t_node	*elem;

	elem = *root;
	if (elem == NULL)
		*root = node;
	else
	{
		while (elem->left)
			elem = elem->left;
		elem->left = node;
	}
}

char	**add_cmd_arg(t_param *prm, char **cmd, char *arg)
{
	char	**new_cmd;
	int		nb_arg;
	int		i;

	i = -1;
	nb_arg = get_nb_str(cmd);
	new_cmd = (char **)ft_malloc_gc(prm, prm->source.id,
			(nb_arg + 2) * sizeof(char *));
	if (new_cmd == NULL)
		return (NULL);
	new_cmd[nb_arg] = ft_strdup_gc(prm, arg);
	if (new_cmd[nb_arg] == NULL)
		return (NULL);
	new_cmd[nb_arg + 1] = NULL;
	while (++i < nb_arg)
		new_cmd[i] = cmd[i];
	return (new_cmd);
}

char	*get_word(t_param *prm)
{
	t_token	peek;
	char	*token;

	peek = peek_tk(prm);
	if (!(peek == TK_WORD || peek == TK_SQUOTE))
		return (NULL);
	token = get_token(prm);
	if (get_t_token(token) == TK_WORD)
		return (token);
	if (get_t_token(token) == TK_SQUOTE)
		return (get_word_squote(prm));
	if (get_t_token(token) == TK_DQUOTE)
		return (get_word_dquote(prm));
	return (NULL);
}

/*tant que l'on est pas arrive sur une autre simple quote on continue 
et on le rajoute dans le word que l'on renvoie sans jamais rien interpreter. */
char	*get_word_squote(t_param *prm)
{
	char	*word;
	size_t	pos_start;

	word = NULL;
	pos_start = prm->source.cur;
	while (peek_tk(prm) != TK_SQUOTE && peek_tk(prm) != TK_EOF)
		get_token(prm);
	if (peek_tk(prm) == TK_EOF)
	{
		prm->source.error = ERR_SQUOTE_CLOSE;
		return (NULL);
	}
	if (peek_tk(prm) == TK_SQUOTE)
		get_token(prm);
	word = ft_substr_gc(prm, prm->source.line, pos_start,
			prm->source.cur - pos_start - 1);
	return (word);
}

char	*get_word_dquote(t_param *prm)
{
	(void)prm;
	return (NULL);
}