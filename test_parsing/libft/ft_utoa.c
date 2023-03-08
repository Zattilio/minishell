/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:41:05 by mbocquel          #+#    #+#             */
/*   Updated: 2023/03/08 10:27:55 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_size_nb(unsigned int nb)
{
	int	size;

	size = 1;
	while (nb >= 10)
	{
		nb = nb / 10;
		size++;
	}
	return (size);
}

char	*ft_utoa(unsigned int n)
{
	char		*nbr_char;
	int			i;
	int			power;

	i = 0;
	nbr_char = (char *)malloc((ft_size_nb(n) + 1) * sizeof(char));
	if (nbr_char == NULL)
		return (NULL);
	power = ft_size_nb(n) - 1;
	while (power > 0)
	{
		nbr_char[i] = (n / ft_power(10, power)) + '0';
		n = n % ft_power(10, power);
		power--;
		i++;
	}
	nbr_char[i] = n + '0';
	nbr_char[i + 1] = '\0';
	return (nbr_char);
}
