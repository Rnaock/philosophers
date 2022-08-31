/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 18:16:08 by mabimich          #+#    #+#             */
/*   Updated: 2022/08/31 23:01:50 by mabimich         ###   ########.fr       */
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

void	*philo_routine(void *philo)
{
	t_philo *p = philo;
	printf("%sThread [%ld]: Le plus grand ennui c'est d'exister sans vivre.%d\t%s\n", YELLOW, p->thd, p->n[0], NC);
	return (NULL);
}


t_philo	**init_philo(t_data *data)
{
	int		i;
	t_philo **philo;

	i = -1;

	philo = ft_calloc(sizeof(t_philo), data->n[0]);
	if (!philo)
		return (NULL);
	while (++i < data->n[0])
	{
		philo[i] = ft_calloc(sizeof(t_philo), 1);
		fprintf(stderr, "%d\n", i);
		philo[i]->id = i;
		philo[i]->thd = pthread_self();
		philo[i]->n[0] = data->n[0];
	}
	return (philo);
}

t_data	*create_philo(t_data *data)
{
	int	i;
	int	out;

	i = -1;
	out = 0;
	data->philo = init_philo(data);
	while (++i < data->n[0] && !out)
	{
		printf("%d) Thread [%ld]: %d\n", i, data->philo[i]->thd, out);
		out = pthread_create(&data->philo[i]->thd, NULL, philo_routine, data->philo[i]);
	}
	i = -1;
	while (++i < data->n[0] && !out)
	{
		printf("%d) join [%ld]\n", i, data->philo[i]->thd);
		out = pthread_join(data->philo[i]->thd, NULL);
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
		data->n[i] = ft_atoi(av[i + 1]);
	data = create_philo(data);
	if (!data->philo)
	{
		free(data);
		ft_putendl_fd("Erreur 1malloc", 2);
		return (NULL);
	}
	data->fork = ft_calloc(sizeof(t_fork), data->n[0]);
	if (!data->fork)
	{
		free(data->philo);
		free(data);
		ft_putendl_fd("Erreur 2malloc", 2);
		return (NULL);
	}
	data->start_t = get_time_in_ms();
	data->philo[0]->id = 1;
	return (data);
}

static int	is_bad_input(int ac, char **av)
{
	int	i;

	i = 0;
	while (++i < ac - 1)
		if (ft_atoi(av[i + 1]) < 1)
			return (1);
	return (0);
}

int	main(int ac, char **av)
{
	int		i;
	t_data	*data;

	i = -1;
	data = NULL;
	if (ac != 5 && ac != 6)
		return (ft_putendl_fd(STR_USAGE, 2), 1);
	if (is_bad_input(ac, av))
		return (ft_putendl_fd(STR_USAGE, 2), 1);
	data = init(ac, av);
	if (!data || !data->start_t)
		return (1);
	free(data);
	return (0);
}
