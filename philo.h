/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 18:25:49 by mabimich          #+#    #+#             */
/*   Updated: 2022/08/27 21:25:26 by mabimich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "libft/includes/libft.h"
# include <sys/wait.h>
# include <stdio.h>

typedef struct s_data
{
	int		n[5];
	int		n_of_philo;
	int		t_2_die;
	int		t_2_eat;
	int		t_2_sleep;
	int		n_of_t_philo_eat;
}			t_data;

#endif
