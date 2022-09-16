/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 18:16:08 by mabimich          #+#    #+#             */
/*   Updated: 2022/09/16 05:46:34 by manuel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_philos(t_data *data, t_philo **philos)
{
	int		i;

	i = -1;
	while (++i < data->n[0])
	{
		philos[i] = ft_calloc(sizeof(t_philo), 1);
		if (!philos[i])
			while (--i >= 0)
				free(philos[i]);
		if (!philos[i])
			return (free(philos), 1);
		philos[i]->id = i + 1;
		philos[i]->n_of_t_philo_eat = data->n[4];
		philos[i]->data = data;
		if (philos[i]->id == 1)
			philos[i]->fork_l = &data->fork[data->n[0] - 1];
		else
			philos[i]->fork_l = &data->fork[i - 1];
		if (philos[i]->id == data->n[0])
			philos[i]->fork_r = &data->fork[data->n[0] - 1];
		else
			philos[i]->fork_r = &data->fork[i];
		pthread_mutex_init(&philos[i]->fork_l->mtx, NULL);
	}
	return (0);
}

void	*checker_philo(void *philos)
{
	t_philo	**ps;
	int		i;

	i = -1;
	ps = philos;
	(void)ps;
	while (get_t() < ps[0]->data->start_s)
		continue ;
	while (++i < ps[0]->data->n[0] && !test_finish(ps[0]->data))
	{
		if (test_last_m(ps[i]) && test_last_m(ps[i]) + ps[i]->data->n[1] < get_t())
			ft_print(1, get_t() - ps[0]->data->start_s, ps[i], "died");
		if (i == ps[0]->data->n[0] - 1)
			i = -1;
		if (i == -1)
			usleep(500);
	}
	return (NULL);
}

static int	init_checker(t_data *data, t_philo *checker, t_philo **philos)
{
	if (!checker)
		return (0);
	checker->data = data;
	pthread_create(&checker->thd, NULL, checker_philo, philos);
	return (0);
}

static int	create_philo(t_data *data)
{
	int		i;
	int		out;
	t_philo	**philos;
	t_philo	*checker;

	i = -1;
	out = 0;
	philos = ft_calloc(sizeof(t_philo), data->n[0]);
	checker = ft_calloc(sizeof(t_philo), 1);
	if (!philos || init_philos(data, philos) || init_checker(data, checker, philos))
		return (free(data->fork), 1);
	while (++i < data->n[0] && !out)
		out = pthread_create(&philos[i]->thd, NULL, philo_routine, philos[i]);
	i = -1;
	while (++i < data->n[0] && !out)
	{
		out = pthread_join(philos[i]->thd, NULL);
		free(philos[i]);
	}
	pthread_join(checker->thd, NULL);
	free(checker);
	free(philos);
	return (0);
}

static t_data	*init(int ac, char **av)
{
	int		i;
	t_data	*data;

	i = -1;
	data = ft_calloc(sizeof(t_data), 1);
	if (!data)
		return (printf("Error: malloc data\n"), NULL);
	while (++i < ac - 1)
		data->n[i] = ft_atoi(av[i + 1]);
	if (ac == 5)
		data->n[4] = INT_MAX;
	data->start_s = get_t() + 300;
	if (data->start_s == 300)
		return (printf("Error: gettimeofdat()\n"), data);
	data->fork = ft_calloc(sizeof(t_fork), data->n[0]);
	if (!data->fork)
		return (printf("Error: malloc fork\n"), data);
	pthread_mutex_init(&data->msg, NULL);
	if (pthread_mutex_init(&data->msg, NULL) || create_philo(data))
		return (free(data->fork), data);
	pthread_mutex_destroy(&data->msg);
	i = -1;
	return (free(data->fork), data);
}

int	main(int ac, char **av)
{
	t_data	*data;

	data = NULL;
	if (is_bad_input(ac, av))
		return (printf("%s\n", STR_USAGE), 1);
	data = init(ac, av);
	if (!data)
		return (1);
	free(data);
	return (0);
}
