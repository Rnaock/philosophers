/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 18:25:49 by mabimich          #+#    #+#             */
/*   Updated: 2022/08/29 20:36:49 by mabimich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "libft/includes/libft.h"
# include <sys/wait.h>
# include <stdio.h>
# include <pthread.h>

typedef	struct s_fork
{
	pthread_mutex_t	count_mutex;
	unsigned int	count;
}			 		t_fork;

typedef struct s_data
{
	int			n[5];
	pthread_t	*thd;
	t_fork		*fork
	int			finish;
	int			n_of_philo;
	int			t_2_die;
	int			t_2_eat;
	int			t_2_sleep;
	int			n_of_t_philo_eat;
}				t_data;

#endif
