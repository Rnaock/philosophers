/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 04:29:33 by manuel            #+#    #+#             */
/*   Updated: 2022/09/15 20:43:20 by mabimich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	test_finish(t_data *data)
{	
	pthread_mutex_lock(&data->msg);
	if (data->finish)
		return (pthread_mutex_unlock(&data->msg), 1);
	else
		return (pthread_mutex_unlock(&data->msg), 0);
}

int	is_bad_input(int ac, char **av)
{
	int	i;

	i = 1;
	if (ac != 5 && ac != 6)
		return (1);
	if (ft_atoi(av[i]) < 1 || ft_atoi(av[i]) > 1000)
		return (1);
	while (++i < ac)
		if (ft_atoi(av[i]) < 0)
			return (1);
	return (0);
}
