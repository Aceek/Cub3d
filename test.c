/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 22:49:59 by ilinhard          #+#    #+#             */
/*   Updated: 2023/02/19 23:43:53 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	ft_count_nbr(int nbr)
{
	int			i;
	long long count;

	i = 0;
	count = nbr;
	if (nbr < 0)
	{
		count = -nbr;
		i++;
	}
	while (count)
	{
		count = count / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(long long nbr)
{
	char	*str;
	int		len;
	int		sign;
	len = ft_count_nbr(nbr);
	
	sign = 0;
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	if (nbr < 0)
	{
		str[0] = '-';
		nbr = -nbr;
		sign = 1;
	}
	str[len] = '\0';
	while (len)
	{
		len --;
		str[len] = nbr % 10 + '0';
		nbr /= 10;
	}
	if (sign)
		str[0] = '-';
	return (str);
}

int	main(void)
{
	int nbr = 1;
	printf("len : %d\n", ft_count_nbr(nbr));
	printf("nbr : %s\n", ft_itoa(nbr));
}