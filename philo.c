/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 18:16:08 by mabimich          #+#    #+#             */
/*   Updated: 2022/09/05 14:44:42 by mabimich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		my_usleep(t_philo *p, time_t t)
{
	time_t	start;
	int		i;

	start = get_time_in_ms();
	i = 0;
	while (get_time_in_ms() < start + t )
	{
		usleep(1000);
		if (get_time_in_ms() > p->last_m + p->n[1])
			return (ft_print(1,  get_time_in_ms() - p->data->start_s, p, "is died"), 1);
		if (!i++ % 100 && p->data->finish)
			return (0);			
	}
	return (0);
}

void	p_eat(t_philo *p)
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
			p->last_m = get_time_in_ms();
			ft_print(0, get_time_in_ms() - p->data->start_s, p,"is eating");
			fprintf(stdout, "%ld\t%d 0 --\n", get_time_in_ms() - p->data->start_s, p->id);
			my_usleep(p, p->n[2]);
			fprintf(stdout, "%ld\t%d 1 --\n", get_time_in_ms() - p->data->start_s, p->id);
			pthread_mutex_unlock(&p->fork_l->mtx);
			pthread_mutex_unlock(&p->fork_r->mtx);
			p->fork_l->in_use = 0;
			return ;
		}
		else
		{
			pthread_mutex_unlock(&p->fork_l->mtx);
			p->fork_l->in_use = 0;
		}
	}
}

void	p_sleep(t_philo *p)
{
	ft_print(0, get_time_in_ms() - p->data->start_s, p,"is sleping");
	my_usleep(p, p->n[3]);
}

void	p_think(t_philo *p)
{
	ft_print(0, get_time_in_ms() - p->data->start_s, p, "is thinking");
//	my_usleep(p, (p->n[1] - p->n[2]) / 4); //a reflechir
}

void	*philo_routine(void *philo)
{
	t_philo *p = philo;
	while (get_time_in_ms() < p->data->start_s)
		continue ;
	p->last_m = get_time_in_ms();
	if (p->id % 2)
		usleep(100);
	while (p->n[4]-- && !p->data->finish)
	{
		if (p->last_m + p->n[1] < get_time_in_ms())
			return (ft_print(1, get_time_in_ms() - p->data->start_s, p, "is died"), NULL);
		p_eat(philo);
		p_sleep(philo);
		p_think(philo);
	}
	return (NULL);
}
