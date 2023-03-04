/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnstr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 15:42:18 by jlanza            #+#    #+#             */
/*   Updated: 2023/03/04 16:36:13 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

void	ft_put2str_fd(char *s1, char *s2, int fd)
{
	char	*tmp;

	tmp = ft_strjoin(s1, s2);
	ft_putstr_fd(tmp, fd);
	free(tmp);
}

void	ft_put3str_fd(char *s1, char *s2, char *s3, int fd)
{
	char	*tmp;

	tmp = ft_strjoin3(s1, s2, s3);
	ft_putstr_fd(tmp, fd);
	free(tmp);
}
