/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 18:25:49 by mabimich          #+#    #+#             */
/*   Updated: 2022/09/01 19:45:21 by mabimich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "libft/includes/libft.h"
# include <sys/wait.h>
# include <sys/time.h>
# include <stdio.h>
# include <pthread.h>

# define STR_USAGE "Usage: 'number_of_philosophers time_to_die time_to_eat \
time_to_sleep [number_of_times_each_philosopher_must_eat]"

typedef	struct s_fork
{
	pthread_mutex_t	fork_mtx;
	size_t			in_use;
}	t_fork;

typedef struct s_data
{
	int			n[5];
	t_fork		*fork;
	time_t		start_t;
	int			finish;
	int			n_of_philo;
	int			t_2_die;
	int			t_2_eat;
	int			t_2_sleep;
	int			n_of_t_philo_eat;
}				t_data;

typedef struct s_philo
{
	t_data		*data;
	int			id;
	int			n[5];
	pthread_t	thd;
	t_fork		*fork;
	time_t		start_t;
	int			finish;
	int			n_of_philo;
	int			t_2_die;
	int			t_2_eat;
	int			t_2_sleep;
	int			n_of_t_philo_eat;
}				t_philo;

#endif
