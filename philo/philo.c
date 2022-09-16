/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 18:16:08 by mabimich          #+#    #+#             */
/*   Updated: 2022/09/17 00:25:32 by mabimich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	my_usleep(t_philo *p, time_t t)
{
	time_t	start;
	int		i;

	start = get_t();
	i = -1;
	while (get_t() < start + t)
	{
		if (!(++i % 500) && set_get_finish(p->data, -1))
			return (0);
		usleep(500);
	}
	return (0);
}

static void	p_eat(t_philo *p)
{
	if (p->id == p->data->n[0])
	{
		pthread_mutex_lock(&p->fork_r->mtx);
		pthread_mutex_lock(&p->fork_l->mtx);
	}
	else
	{
		pthread_mutex_lock(&p->fork_l->mtx);
		pthread_mutex_lock(&p->fork_r->mtx);
	}
	if (get_t() > (long)test_last_m(p) + p->data->n[1])
	{
		ft_print(1, get_t() - p->data->start_s, p, "died");
		pthread_mutex_unlock(&p->fork_r->mtx);
		pthread_mutex_unlock(&p->fork_l->mtx);
		return ;
	}
	set_last_m(p, get_t());
	ft_print(0, get_t() - p->data->start_s, p, NULL);
	my_usleep(p, p->data->n[2]);
	pthread_mutex_unlock(&p->fork_r->mtx);
	pthread_mutex_unlock(&p->fork_l->mtx);
}

static void	p_sleep(t_philo *p)
{
	ft_print(0, get_t() - p->data->start_s, p, "is sleeping");
	my_usleep(p, p->data->n[3]);
}

static void	p_think(t_philo *p)
{
	ft_print(0, get_t() - p->data->start_s, p, "is thinking");
	if (!p->data->n[2] || !p->data->n[3])
		usleep(5);
	my_usleep(p, p->data->n[2] - p->data->n[3] + 1);
}

void	*philo_routine(void *philo)
{
	t_philo	*p;

	p = philo;
	set_last_m(p, p->data->start_s);
	while (get_t() < p->data->start_s)
		continue ;
	if (p->id % 2 && p->data->n[0] != 1)
		my_usleep(p, p->data->n[2] / 4);
	while (!set_get_finish(p->data, -1) && p->n_of_t_philo_eat)
	{
		if (p->data->n[0] == 1)
		{
			ft_print(0, get_t() - p->data->start_s, p, "has taken a fork");
			my_usleep(p, LONG_MAX - get_t());
			return (NULL);
		}
		p_eat(philo);
		if (!p->n_of_t_philo_eat)
			my_usleep(p, LONG_MAX - get_t());
		p_sleep(philo);
		p_think(philo);
	}
	return (NULL);
}
