/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 18:16:08 by mabimich          #+#    #+#             */
/*   Updated: 2022/09/15 21:56:11 by mabimich         ###   ########.fr       */
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
		if (!(++i % 500) && test_finish(p->data))
			return (0);
		usleep(500);
		if (get_t() > p->last_m + p->data->n[1])
		{
			ft_print(1, get_t() - p->data->start_s, p, "died");
			return (1);
		}
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
	if (get_t() >= p->last_m + p->data->n[1] || test_finish(p->data))
	{
		ft_print(1, get_t() - p->data->start_s, p, "diied");
		pthread_mutex_unlock(&p->fork_r->mtx);
		pthread_mutex_unlock(&p->fork_l->mtx);
		return ;
	}
	p->last_m = get_t();
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
//	printf("==> %d --> %d\n", p->id, p->data->n[2] - p->data->n[3]);
	if (p->data->n[3] < p->data->n[2])
		my_usleep(p, p->data->n[2] - p->data->n[3] + 1);
	else
		my_usleep(p, 1);
}

void	*philo_routine(void *philo)
{
	t_philo	*p;

	p = philo;
	while (get_t() < p->data->start_s)
		continue ;
	p->last_m = get_t();
	if (p->id % 2)
		my_usleep(p, p->data->n[2] / 4);
	while (p->n_of_t_philo_eat && !test_finish(p->data))
	{
		if (p->data->n[0] == 1)
		{
			ft_print(0, get_t() - p->data->start_s, p, "has taken a fork");
			my_usleep(p, LONG_MAX - get_t());
		}
		if (p->last_m + p->data->n[1] < get_t())
		{
			ft_print(1, get_t() - p->data->start_s, p, "diiied");
			return (NULL);
		}
		p_eat(philo);
		p_sleep(philo);
		p_think(philo);
	}
	return (NULL);
}
