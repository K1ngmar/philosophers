/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   phil_stuff.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ikole <ikole@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/15 17:20:42 by ikole         #+#    #+#                 */
/*   Updated: 2020/11/23 17:02:35 by ikole         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"
#include <stdbool.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <signal.h>
#include <stdlib.h>

static void	state_sleep(t_phil *phil)
{
	phil_msg(phil, MSG_SLEEP, false);
	zzz(phil->data->ttsleep);
}

static bool	take_forks(t_phil *phil)
{
	sem_wait(phil->data->forks);
	if (check_death(phil->data) == true)
	{
		sem_post(phil->data->forks);
		return (false);
	}
	phil_msg(phil, MSG_PICK_FORK, false);
	sem_wait(phil->data->forks);
	if (check_death(phil->data) == true)
	{
		sem_post(phil->data->forks);
		sem_post(phil->data->forks);
		return (false);
	}
	phil_msg(phil, MSG_PICK_FORK, false);
	return (true);
}

static void	state_eat(t_phil *phil)
{
	if (take_forks(phil) == false)
		return ;
	sem_wait(phil->eat);
	phil_msg(phil, MSG_EATING, false);
	phil->times_eaten++;
	phil->last_eaten = get_time();
	sem_post(phil->eat);
	zzz(phil->data->tteat);
	sem_post(phil->data->forks);
	phil_msg(phil, MSG_DROP_FORK, false);
	sem_post(phil->data->forks);
	phil_msg(phil, MSG_DROP_FORK, false);
}

static void	phil_stuff(void *v_phil)
{
	t_phil		*phil;

	phil = (t_phil*)v_phil;
	usleep(phil->id % 2 * 100);
	phil_msg(phil, MSG_APPEAR, false);
	while (1)
	{
		phil_msg(phil, MSG_THINKING, false);
		if (check_death(phil->data) == true)
			break ;
		state_eat(phil);
		if (check_death(phil->data) == true)
			exit(1);
		if (phil->times_eaten > 0 && phil->times_eaten == phil->data->must_eat)
		{
			phil_msg(phil, MSG_DONE, false);
			phil->data->done_eating++;
			phil->done = true;
			break ;
		}
		state_sleep(phil);
	}
}

void		monitor(t_phil *phil)
{
	unsigned long	time;
	pthread_t		thread;

	if (pthread_create(&(thread), NULL, (void*)phil_stuff, phil))
		exit(1);
	while (1)
	{
		sem_wait(phil->eat);
		time = get_time();
		if (time - phil->last_eaten >= phil->data->ttdie && phil->done == false)
		{
			sem_wait(phil->data->die_lock);
			phil->data->dead = true;
			sem_post(phil->data->die_lock);
			phil_msg(phil, MSG_DIED, true);
			sem_post(phil->eat);
			exit(1);
		}
		else if (phil->done == true)
			exit(0);
		sem_post(phil->eat);
		usleep(200);
	}
}
