/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 16:17:10 by mabimich          #+#    #+#             */
/*   Updated: 2022/09/17 01:55:09 by mabimich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*checker_philo(void *philos)
{
	t_philo	**ps;
	int		i;
	int		n_meal;

	n_meal = 0;
	i = -1;
	ps = philos;
	while (get_t() < ps[0]->data->start_s)
		continue ;
	while (++i < ps[0]->data->n[0] && !set_get_finish(ps[0]->data, -1))
	{
		n_meal += set_get_n_of_t_ph_eat(ps[i], 0);
		if (test_last_m(ps[i]) && \
				test_last_m(ps[i]) + ps[i]->data->n[1] <= get_t())
			ft_print(1, get_t() - ps[0]->data->start_s, ps[i], "died");
		if (i == ps[0]->data->n[0] - 1)
		{
			i = -1;
			if (!n_meal)
				set_get_finish(ps[0]->data, 1);
			n_meal = 0;
			usleep(2000);
		}
	}
	return (NULL);
}

int	init_checker(t_data *data, t_philo *checker, t_philo **philos)
{
	int	out;

	if (!checker)
		return (0);
	checker->data = data;
	out = pthread_create(&checker->thd, NULL, checker_philo, philos);
	return (out);
}
