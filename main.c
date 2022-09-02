/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 18:16:08 by mabimich          #+#    #+#             */
/*   Updated: 2022/09/02 20:31:16 by mabimich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

# define NC	"\e[0m"
# define YELLOW	"\e[1;33m"

void	ft_print(int dead, t_philo *philo, time_t t, char *str)
{
	pthread_mutex_lock(&philo->data->msg);
	if (!philo->data->finish)
		printf("%ld\t%d\t%s\n", t, philo->id, str);
	if (dead)
		philo->data->finish = 1;
	pthread_mutex_unlock(&philo->data->msg);
}

time_t	get_time_in_ms(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (0);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

t_philo	**init_philos(t_data *data)
{
	int		i;
	t_philo **philos;

	i = -1;

	philos = ft_calloc(sizeof(t_philo), data->n[0]);
	if (!philos)
		return (NULL);
	while (++i < data->n[0])
	{
		philos[i] = ft_calloc(sizeof(t_philo), 1);
		if (!philos[i])
		{
			while (--i >= 0)
				free(philos[i]);
			free(philos);
			return (NULL);
		}
		philos[i]->id = i + 1;
		philos[i]->n[0] = data->n[0];
		philos[i]->n[1] = data->n[1];
		philos[i]->n[2] = data->n[2];
		philos[i]->n[3] = data->n[3];
		philos[i]->n[4] = data->n[4];
		philos[i]->data = data;
		if (philos[i]->id == 1)
			philos[i]->fork_l = &data->fork[data->n[0]];
		else
			philos[i]->fork_l = &data->fork[philos[i]->id - 1];
	//	if (philos[i]->id == data->n[0])
	//		philos[i]->fork[1] = data->fork[data->n[0]];
	//	else
		philos[i]->fork_r = &data->fork[philos[i]->id];

	}
	return (philos);
}

int create_philo(t_data *data)
{
	int	i;
	int	out;
	t_philo **philos;

	i = -1;
	out = 0;
	philos = init_philos(data);
	if (!philos)
		return (free(data), 1);
	while (++i < data->n[0] && !out)
	{
		out = pthread_create(&philos[i]->thd, NULL, philo_routine, philos[i]);
	//	printf("%d) Thread [%ld]: %d\n", i + 1, philos[i]->thd, out);
	}
	i = -1;
	while (++i < data->n[0] && !out)
	{
//		printf("%d) join [%ld]\n", i + 1, philos[i]->thd);
		out = pthread_join(philos[i]->thd, NULL);
	}
	return (0);
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
	if (ac == 5)
		data->n[4] = 10;
	data->finish = 0;//  n et n+1 (au moins a descendre plus tard)
	data->start_s = get_time_in_ms() + 300;// (il faudra attendre que tout les philo soit ok puis avant de lancer la simu on met ces info? a reflchir?
/*	if (!philos)
	{
		free(data);
		ft_putendl_fd("Erreur 1malloc", 2);
		return (NULL);
	}
*/	data->fork = ft_calloc(sizeof(t_fork), data->n[0]);
	if (!data->fork)
	{
		free(data);
		ft_putendl_fd("Erreur malloc", 2);
		return (NULL);
	}
	if (!data || create_philo(data))
		return (NULL);
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
	if (!data || !data->start_s)
		return (1);
	free(data);
	return (0);
}
