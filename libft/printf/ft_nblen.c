/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nblen.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 18:06:46 by mabimich          #+#    #+#             */
/*   Updated: 2021/12/15 17:44:09 by mabimich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_nblen(long long nb)
{
	size_t	i;

	i = 1;
	if (nb < 0)
		i++;
	while (nb >= 10 || nb <= -10)
	{
		nb /= 10;
		i++;
	}
	return (i);
}