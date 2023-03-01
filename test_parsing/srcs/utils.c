/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:57:00 by mbocquel          #+#    #+#             */
/*   Updated: 2023/03/01 13:47:51 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*ft_substr_gc(t_param *prm, char *s, unsigned int start, size_t len)
{
	char	*result_str;
	size_t	i;
	size_t	len_max;

	len_max = len;
	if (ft_strlen(s) - start < len_max && start <= ft_strlen(s))
	{
		len_max = ft_strlen(s) - start;
	}
	else if (start > ft_strlen(s))
		len_max = 0;
	result_str = (char *)ft_calloc_gc(prm, (len_max + 1), sizeof(char));
	if (result_str == NULL)
		return (NULL);
	i = 0;
	while (i < len_max)
	{
		result_str[i] = s[(size_t)start + i];
		i++;
	}
	result_str[i] = '\0';
	return (result_str);
}

char	*ft_strdup_gc(t_param *prm, const char *s)
{
	char	*dest;
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (s[len])
		len++;
	dest = (char *)ft_malloc_gc(prm, (len + 1) * sizeof(char));
	if (dest == NULL)
		return (NULL);
	while (s[i])
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	is_redir(int token_type)
{
	if (token_type == TK_INF || token_type == TK_SUP
		|| token_type == TK_DINF || token_type == TK_DSUP)
		return (1);
	return (0);
}

void	print_space(int space)
{
	int	i;

	i = 15;
	while (i < space)
	{
		ft_printf(" ");
		i++;
	}
}
