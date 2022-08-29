/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 18:16:08 by mabimich          #+#    #+#             */
/*   Updated: 2022/08/29 20:38:58 by mabimich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

# define NC	"\e[0m"
# define YELLOW	"\e[1;33m"

void	*thd_routine(void *d)
{
	pthread_t tid;

	t_data *data = d;
	tid = pthread_self();
	printf("%sThread [%ld]: Le plus grand ennui c'est d'exister sans vivre.%d\t%s\n", YELLOW, tid, data->n[0], NC);
	return (NULL);
}

t_data	*create_thd(t_data *data)
{
	int	i;
	int	out;

	i = -1;
	out = 0;
	while (++i < data->n[0] && !out)
	{
		out = pthread_create(&data->thd[i], NULL, thd_routine, data);
		printf("%d) Thread [%ld]: %d\n", i, data->thd[i], out);
	}
	i = -1;
	while (++i < data->n[0] && !out)
	{
		printf("%d) join [%ld]\n", i, data->thd[i]);
		out = pthread_join(data->thd[i], NULL);
	}
	return (data);
}

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
	data->thd = ft_calloc(sizeof(pthread_t), data->n[0]);
	if (!data->thd)
	{
		free(data);
		ft_putendl_fd("Erreur malloc", 2);
		return (NULL);
	}
	data->fork = ft_calloc(sizeof(t_fork), data->n[0]);
	if (!data->fork)
	{
		free(data->thd);
		free(data);
		ft_putendl_fd("Erreur malloc", 2);
		return (NULL);
	}
	return (create_thd(data));
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
