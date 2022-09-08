/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 22:18:02 by mabimich          #+#    #+#             */
/*   Updated: 2022/09/06 22:46:28 by mabimich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isdigit(int c)
{
	if (c > 47 && c < 58)
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int			i;
	size_t		r;
	int			m;

	i = 0;
	r = 0;
	m = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			m = -1;
	while (ft_isdigit((int)str[i]))
	{
		if ((r * 10) + sizeof(char) > LONG_MAX)
		{
			if (m > 0)
				return (-1);
			else
				return (0);
		}
		r = r * 10 + str[i++] - '0';
	}
	return (m * r);
}

void	*ft_calloc(size_t count, size_t size)
{
	int				*out;
	unsigned char	*cc;
	size_t			len;

	len = count * size;
	out = (void *)malloc(len);
	if (!out)
		return (NULL);
	cc = (unsigned char *)out;
	while (len--)
		cc[len] = 0;
	out = (void *)cc;
	return (out);
}

void	ft_print(int dead, time_t t, t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->data->msg);
	if (!philo->data->finish)
		printf("%ld\t%d\t%s\n", t, philo->id, str);
	if (dead)
		philo->data->finish = 1;
	pthread_mutex_unlock(&philo->data->msg);
}

time_t	get_time_in_ms(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (0);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
