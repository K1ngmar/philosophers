/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_one.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ikole <ikole@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/15 16:37:53 by ikole         #+#    #+#                 */
/*   Updated: 2020/11/22 16:50:05 by ikole         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include "colors.h"
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h> //

# define MSG_EATING "] " COLOR_EATING "is eating" COLOR_RESET "\n"
# define MSG_SLEEP "] " COLOR_SLEEPING "is sleeping" COLOR_RESET "\n"
# define MSG_PICK_FORK "] " COLOR_PICK_FORK "picked up a fork" COLOR_RESET "\n"
# define MSG_DROP_FORK "] " COLOR_DROP_FORK "dropped a fork" COLOR_RESET "\n"
# define MSG_THINKING "] " COLOR_THINKING "is thinking" COLOR_RESET "\n"
# define MSG_DONE "] " COLOR_GREEN "is done eating" COLOR_RESET "\n"
# define MSG_APPEAR "] " COLOR_APPEAR "appeard for an epic feast" COLOR_RESET "\n"
# define MSG_DIED "] " COLOR_RED "died" COLOR_RESET "\n"

typedef struct  s_data
{
    unsigned int	phil_amount;
	char			**colors;
	unsigned long	ttdie;
	unsigned int	tteat;
	unsigned int	ttsleep;
	unsigned int	must_eat;
	unsigned int	done_eating;
	unsigned long	start_time;
	bool			dead;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write;
	pthread_mutex_t frick;
}               t_data;

typedef struct	s_phil
{
	unsigned int	id;
	unsigned int	times_eaten;
	unsigned long	last_eaten;
	unsigned int	l_fork;
	unsigned int	r_fork;
	bool			done;
	pthread_mutex_t	eat;
	t_data			*data;
}				t_phil;

void			phil_stuff(void *);

/*
**	Init
*/
int				data_init(char **, t_data *);
int				phil_init(t_phil *, int, t_data *);
void			destroy_fucking_mutex_godamnit(pthread_mutex_t *);
void			destroy_mutex_babies(pthread_mutex_t *, int);

/*
**	Helpers
*/
unsigned long	get_time();
void			phil_msg(t_phil *, char *, bool);
int				ft_atoi(char *);
void			zzz(unsigned long);
bool			check_death(t_data *);

#endif
