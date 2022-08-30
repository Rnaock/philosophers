/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 18:16:08 by mabimich          #+#    #+#             */
/*   Updated: 2022/08/30 19:13:48 by mabimich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

# define NC	"\e[0m"
# define YELLOW	"\e[1;33m"

time_t	get_time_in_ms(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (0);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	*philo_routine(void *d)
{
	pthread_t tid;

	t_data *data = d;
	tid = pthread_self();
	printf("%sThread [%ld]: Le plus grand ennui c'est d'exister sans vivre.%d\t%s\n", YELLOW, tid, data->n[0], NC);
	return (NULL);
}

t_data	*create_philo(t_data *data)
{
	int	i;
	int	out;

	i = -1;
	out = 0;
	init_philo(data);
	while (++i < data->n[0] && !out)
	{
		printf("%d) Thread [%ld]: %d\n", i, data->philo[i]->thd, out);
		out = pthread_create(&data->philo[i]->thd, NULL, philo_routine, data);
	}
	i = -1;
	while (++i < data->n[0] && !out)
	{
		printf("%d) join [%ld]\n", i, data->philo[i]->thd);
		out = pthread_join(data->philo[i]->thd, NULL);
	}
	return (data);
}

void	init_philo(t_data *data)
{
	int	i;

	i = -1;
	while (i < n[0])
		data->philo[i]->id = i;
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
	data->philo = ft_calloc(sizeof(t_philo), data->n[0]);
	if (!data->philo)
	{
		free(data);
		ft_putendl_fd("Erreur malloc", 2);
		return (NULL);
	data->fork = ft_calloc(sizeof(t_fork), data->n[0]);
	if (!data->fork)
	{
		free(data->philo);
		free(data);
		ft_putendl_fd("Erreur malloc", 2);
		return (NULL);
	}
	data->start_t = get_time_in_ms();
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
	if (!data || !data->start_t)
		return (1);
	create_philo(data);
	free(data);
	return (0);
}
