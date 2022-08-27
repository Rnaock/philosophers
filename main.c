/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 18:16:08 by mabimich          #+#    #+#             */
/*   Updated: 2022/08/27 21:36:22 by mabimich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data	*init(int ac, char **av)
{
	int		i;
	t_data	*data;

	i = -1;
	data = ft_calloc(sizeof(t_data), 1);
	if (!data)
		return (NULL);
	while (++i < ac - 1)
	{
		data->n[i] = ft_atoi(av[i + 1]);
		if (data->n[i] < 1)
		{
			free(data);
			ft_putendl_fd("Erreur parsing", 2);
			return (NULL);
		}
	}
	return (data);
}

int	main(int ac, char **av)
{
	int		i;
	t_data	*data;

	i = -1;
	data = NULL;
	if (ac != 5 && ac != 6)
		return (ft_putendl_fd("Usage: 'number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat", 2), 1);
	data = init(ac, av);
	if (!data)
		return (1);
	free(data);
	return (0);
}
