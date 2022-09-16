/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 04:29:33 by manuel            #+#    #+#             */
/*   Updated: 2022/09/16 18:06:25 by mabimich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
/*
int	test_finish(t_data *data)
{	
	pthread_mutex_lock(&data->msg);
	if (data->finish)
		return (pthread_mutex_unlock(&data->msg), 1);
	else
		return (pthread_mutex_unlock(&data->msg), 0);
}*/

time_t	test_last_m(t_philo *p)
{	
	time_t	out;

	pthread_mutex_lock(&p->m_last_m);
	out = p->last_m;
	return (pthread_mutex_unlock(&p->m_last_m), out);
}

void	set_last_m(t_philo *p, time_t l_m)
{	
	pthread_mutex_lock(&p->m_last_m);
	p->last_m = l_m;
	pthread_mutex_unlock(&p->m_last_m);
}

int	set_get_finish(t_data *data, int i)
{	
	int	out;

	pthread_mutex_lock(&data->msg);
	if (i < 0)
		out = data->finish;
	else if (i > 0)
		data->finish = 1;
	else if (!i)
		data->finish = 0;
	pthread_mutex_unlock(&data->msg);
	if (i < 0)
		return (out);
	else
		return (-1);
}

int	set_get_n_of_t_ph_eat(t_philo *p, int i)
{	
	int	out;

	pthread_mutex_lock(&p->m_noft);
	if (!i)
		out = p->n_of_t_philo_eat;
	else if (i == -1 && p->n_of_t_philo_eat > 0)
		p->n_of_t_philo_eat--;
	else if (i > 0)
		p->n_of_t_philo_eat = i;
	pthread_mutex_unlock(&p->m_noft);
	if (!i)
		return (out);
	else
		return (-1);
}

time_t	get_t(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (0);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
