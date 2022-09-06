/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 18:25:49 by mabimich          #+#    #+#             */
/*   Updated: 2022/09/06 23:02:42 by mabimich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/wait.h>
# include <sys/time.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

# define STR_USAGE "Usage: 'number_of_philosophers time_to_die time_to_eat \
time_to_sleep [number_of_times_each_philosopher_must_eat]"

typedef struct s_fork
{
	pthread_mutex_t	mtx;
	int				in_use;
}					t_fork;

typedef struct s_data
{
	int				n[5];
	time_t			start_s;
	int				finish;
	pthread_mutex_t	msg;
	t_fork			*fork;
	int				n_of_philo;
	int				t_2_die;
	int				t_2_eat;
	int				t_2_sleep;
	int				n_of_t_philo_eat;
}					t_data;

typedef struct s_philo
{
	t_data		*data;
	int			id;
	pthread_t	thd;
	t_fork		*fork_l;
	t_fork		*fork_r;
	time_t		start_t;
	time_t		last_m;
	int			n_of_philo;
	int			t_2_die;
	int			t_2_eat;
	int			t_2_sleep;
	int			n_of_t_philo_eat;
}				t_philo;

void	ft_print(int dead, time_t t, t_philo *philo, char *str);
time_t	get_time_in_ms(void);
void	*philo_routine(void *philo);
int		ft_atoi(const char *str);
void	*ft_calloc(size_t count, size_t size);

#endif
