/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 18:16:08 by mabimich          #+#    #+#             */
/*   Updated: 2022/09/08 18:54:38 by mabimich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	my_usleep(t_philo *p, time_t t)
{
	time_t	start;
	int		i;

	start = get_t();
	i = 0;
	while (get_t() < start + t)
	{
		usleep(1000);
		if (get_t() > p->last_m + p->data->n[1])
		{
			ft_print(1, get_t() - p->data->start_s, p, "is died");
			return (1);
		}
		if (!(++i % 1000) && p->data->finish)
			return (0);
	}
	return (0);
}

static void	p_eat(t_philo *p)
{
	while (1)
	{
		if (!p->fork_l->in_use)
		{
			pthread_mutex_lock(&p->fork_l->mtx);
			p->fork_l->in_use = 1;
		}
		if (!p->fork_r->in_use)
		{
			pthread_mutex_lock(&p->fork_r->mtx);
			p->last_m = get_t();
			ft_print(0, p->last_m - p->data->start_s, p, NULL);
			my_usleep(p, p->data->n[2]);
			p->fork_l->in_use = 0;
			pthread_mutex_unlock(&p->fork_l->mtx);
			pthread_mutex_unlock(&p->fork_r->mtx);
			return ;
		}
		else
		{
			p->fork_l->in_use = 0;
			pthread_mutex_unlock(&p->fork_l->mtx);
			usleep(5);
		}
	}
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
	while (p->n_of_t_philo_eat-- && !p->data->finish)
	{
		if (p->data->n[0] == 1)
		{
			ft_print(0, get_t() - p->data->start_s, p, "has taken a fork");
			my_usleep(p, LONG_MAX - get_t());
		}
		if (p->last_m + p->data->n[1] < get_t())
		{
			ft_print(1, get_t() - p->data->start_s, p, "is died");
			return (NULL);
		}
		p_eat(philo);
		p_sleep(philo);
		p_think(philo);
	}
	return (NULL);
}
