/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 14:53:54 by mbocquel          #+#    #+#             */
/*   Updated: 2023/03/06 18:17:56 by mbocquel         ###   ########.fr       */
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
	new_cmd[nb_arg] = ft_strdup_gc(prm, prm->source.id, arg);
	if (new_cmd[nb_arg] == NULL)
		return (NULL);
	new_cmd[nb_arg + 1] = NULL;
	while (++i < nb_arg)
		new_cmd[i] = cmd[i];
	return (new_cmd);
}
