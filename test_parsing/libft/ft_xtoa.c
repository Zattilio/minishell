/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xtoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:41:05 by mbocquel          #+#    #+#             */
/*   Updated: 2023/03/08 11:04:02 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_power_u(unsigned int nb, int power)
{
	if (power < 0)
		return (0);
	else if (power == 1)
		return (nb);
	else
		return (nb * ft_power_u(nb, power - 1));
}

static int	ft_size_nb_hex(unsigned int nb)
{
	int	size;

	size = 1;
	while (nb >= 16)
	{
		nb = nb / 16;
		size++;
	}
	return (size);
}

char	*ft_xtoa(unsigned int n, char x)
{
	char		*nbr_char;
	int			i;
	int			power;
	char		*base;

	i = 0;
	if (x == 'x')
		base = "0123456789abcdef";
	else
		base = "0123456789ABCDEF";
	nbr_char = (char *)malloc((ft_size_nb_hex(n) + 1) * sizeof(char));
	if (nbr_char == NULL)
		return (NULL);
	power = ft_size_nb_hex(n) - 1;
	while (power > 0)
	{
		nbr_char[i] = base[(n / ft_power_u(16, power))];
		n = n % ft_power_u(16, power);
		power--;
		i++;
	}
	nbr_char[i] = base[n];
	nbr_char[i + 1] = '\0';
	return (nbr_char);
}
