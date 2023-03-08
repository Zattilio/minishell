/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:41:05 by mbocquel          #+#    #+#             */
/*   Updated: 2023/03/08 11:01:48 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned long long	ft_power_ull(unsigned long long nb, int power)
{
	if (power < 0)
		return (0);
	else if (power == 1)
		return (nb);
	else
		return (nb * ft_power_ull(nb, power - 1));
}

static int	ft_size_nb_hex(unsigned long long nb)
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

char	*ft_ptoa(void *ptr)
{
	char				*nbr_char;
	int					i;
	int					power;
	char				*base;
	unsigned long long	n;

	if (ptr == NULL)
		return (ft_strdup("(nil)"));
	n = (unsigned long long)ptr;
	base = "0123456789abcdef";
	nbr_char = (char *)ft_calloc((ft_size_nb_hex(n) + 3), sizeof(char));
	if (nbr_char == NULL)
		return (NULL);
	nbr_char[0] = '0';
	nbr_char[1] = 'x';
	i = 1;
	power = ft_size_nb_hex(n) - 1;
	while (power > 0)
	{
		nbr_char[++i] = base[(n / ft_power_ull(16, power))];
		n = n % ft_power_ull(16, power);
		power--;
	}
	nbr_char[++i] = base[n];
	return (nbr_char);
}
