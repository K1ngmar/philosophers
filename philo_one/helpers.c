/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   helpers.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ikole <ikole@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/15 16:52:58 by ikole         #+#    #+#                 */
/*   Updated: 2020/12/05 15:27:54 by ikole         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>

bool		check_death(t_data *data)
{
	pthread_mutex_lock(&(data->check_death));
	if (data->dead == true)
	{
		pthread_mutex_unlock(&(data->check_death));
		return (true);
	}
	pthread_mutex_unlock(&(data->check_death));
	return (false);
}

static void	ft_putnbr(unsigned long n)
{
	char print[1];

	if (n >= 10)
		ft_putnbr(n / 10);
	*print = n % 10 + 48;
	write(1, print, 1);
}

int			ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void		phil_msg(t_phil *phil, char *msg, bool force_write)
{
	unsigned long	time;

	pthread_mutex_lock(&(phil->data->write));
	if (check_death(phil->data) == false || force_write == true)
	{
		time = get_time();
		ft_putnbr(time - phil->data->start_time);
		write(1, phil->data->colors[phil->id % 8],
			ft_strlen(phil->data->colors[phil->id % 8]));
		write(1, "\t[", 2);
		ft_putnbr(phil->id);
		write(1, msg, ft_strlen(msg));
	}
	pthread_mutex_unlock(&(phil->data->write));
}

int			ft_atoi(char *str)
{
	int	nb;
	int i;

	nb = 0;
	i = 0;
	while (str[i])
	{
		nb = nb * 10 + str[i] - '0';
		i++;
	}
	return (nb);
}
