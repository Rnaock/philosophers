/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 18:16:08 by mabimich          #+#    #+#             */
/*   Updated: 2022/09/02 18:25:41 by mabimich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

# define NC	"\e[0m"
# define YELLOW	"\e[1;33m"

void	p_eat(t_philo *p)
{
	time_t	start;

	start = get_time_in_ms();
	p->last_m = start;	
	ft_print(0, p, get_time_in_ms() - p->data->start_s , "is eating");
	while (get_time_in_ms() < start + p->n[2])
		continue ;
}

void	p_sleep(t_philo *p)
{
	time_t	start;

	start = get_time_in_ms();
	ft_print(0, p, get_time_in_ms() - p->data->start_s , "is sleping");
	while (get_time_in_ms() < start + p->n[3])
		continue ;
}

void	p_think(t_philo *p)
{
	ft_print(0, p, get_time_in_ms() - p->data->start_s , "is thinking");
}

void	*philo_routine(void *philo)
{
	t_philo *p = philo;
	while (get_time_in_ms() < p->data->start_s)
		continue ;
	if (p->n[0] % 2 && p->id % 2)
		usleep(2);
	ft_print(0, p, get_time_in_ms() - p->data->start_s , "Le plus grand ennui c'est d'exister sans manger des PATES");
	while (p->n[4]-- && !p->data->finish)
	{
		fprintf(stderr, "== %d ==\n", p->n[1]);
		if (p->last_m + p->n[1] > get_time_in_ms())// probleme d unité entre last_m p->n[1] et get_time_in ms
			return (ft_print(1, p, get_time_in_ms() - p->data->start_s , "is died"), NULL);
		p_eat(philo);
		p_sleep(philo);
		p_think(philo);
	}
//	printf("%sThread [%ld]: Le plus grand ennui c'est d'exister sans vivre.%d\t%s\n", YELLOW, p->thd, p->n[0], NC);
	return (NULL);
}
