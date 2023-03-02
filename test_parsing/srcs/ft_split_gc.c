/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_gc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:30:26 by mbocquel          #+#    #+#             */
/*   Updated: 2023/03/02 16:43:15 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	is_sep(char c, char *sep)
{
	int	i;

	i = 0;
	while (sep[i])
	{
		if (sep[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	ft_count_words(char const *s, char *c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (!is_sep(s[i], c) && (is_sep(s[i + 1], c) || s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

static char	*ft_get_word(char const *s, char *c, int *i)
{
	int		len_word;
	char	*new_word;
	int		j;

	j = 0;
	len_word = 0;
	while (s[*i] && is_sep(s[*i], c))
		(*i)++;
	while (s[*i] && !is_sep(s[*i], c))
	{
		len_word++;
		(*i)++;
	}
	new_word = (char *)ft_calloc(len_word + 1, sizeof(char));
	if (new_word == NULL)
		return (NULL);
	while (j < len_word)
	{
		new_word[j] = s[*i - len_word + j];
		j++;
	}
	return (new_word);
}

char	**ft_split(t_param *prm, int id, char const *s, char *c)
{
	char	**strs;
	int		w;
	int		i;
	int		word_count;

	word_count = ft_count_words(s, c);
	w = 0;
	i = 0;
	strs = (char **)ft_calloc_gc(prm, id, (word_count + 1), sizeof(char *));
	if (strs == NULL)
		return (NULL);
	while (w < word_count)
	{
		strs[w] = ft_get_word(s, c, &i);
		if (strs[w] == NULL)
			return (NULL);
		garbage_col(prm, id, strs[w]);
		w++;
	}
	return (strs);
}
