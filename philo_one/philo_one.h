/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_one.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ikole <ikole@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/15 16:37:53 by ikole         #+#    #+#                 */
/*   Updated: 2020/12/05 16:06:26 by ikole         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <pthread.h>
# include <stdbool.h>

/*
** COLOR DEFINES
*/
# define COLOR_RED 		"\e[38;5;196m"
# define COLOR_GREEN	"\e[38;5;46m"
# define COLOR_BLUE 	"\e[38;5;51m"
# define COLOR_BLU		"\e[38;5;190m"
# define COLOR_ORANGE	"\e[38;5;214m"
# define COLOR_PURPLE	"\e[38;5;98m"
# define COLOR_YELLOW	"\e[38;5;220m"
# define COLOR_PINK		"\e[38;5;205m"
# define COLOR_YOS		"\e[38;5;226"

/*
** COLORED PIHLO MESSAGES
*/
# define MSG_EATING		"] \e[38;5;113mis eating\e[37m\n"
# define MSG_SLEEP		"] \e[38;5;117mis sleeping\e[37m\n"
# define MSG_PICK_FORK	"] \e[38;5;218mpicked up a fork\e[37m\n"
# define MSG_DROP_FORK	"] \e[38;5;166mdropped a fork\e[37m\n"
# define MSG_THINKING	"] \e[38;5;101mis thinking\e[37m\n"
# define MSG_DONE		"] \e[38;5;46mis done eating\e[37m\n"
# define MSG_APPEAR		"] \e[38;5;198mappeard for an epic feast\e[37m\n"
# define MSG_DIED		"] \e[38;5;196mdied\e[37m\n"

/*
** ERROR MESSAGES
*/
# define ERR_MISSARG	"\e[38;5;196mYou are missing some arguments\n"
# define ERR_PHILAMT	"\e[38;5;196mYou need atleast two philosophers\n"
# define ERR_TOOMANY	"\e[38;5;196mOver 200 philosophers is prohibited\n"
# define ERR_TTDIE		"\e[38;5;196mTime to die needs te be atleast 60ms\n"
# define ERR_TTEAT		"\e[38;5;196mTime to sleep needs te be atleast 60ms\n"
# define ERR_TTSLEEP	"\e[38;5;196mTime to eat needs te be atleast 60ms\n"
# define ERR_NOEAT		"\e[38;5;196mEating zero times is weird\n"
# define ERR_NAN		"\e[38;5;196mNOT A DIGIT <3 ABEL\n"
# define ERR_IMPOSSIBLE	"\e[38;5;220m<WARNING> \e[38;5;196mDeath is comming!\n"

typedef struct	s_data
{
	size_t			phil_amount;
	char			**colors;
	size_t			ttdie;
	size_t			tteat;
	size_t			ttsleep;
	size_t			must_eat;
	size_t			done_eating;
	size_t			start_time;
	bool			dead;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write;
	pthread_mutex_t check_death;
}				t_data;

typedef struct	s_phil
{
	size_t			id;
	size_t			times_eaten;
	size_t			last_eaten;
	size_t			l_fork;
	size_t			r_fork;
	bool			done;
	pthread_mutex_t	eat;
	t_data			*data;
}				t_phil;

void			phil_stuff(void *v_phil);

/*
**	Init
*/
int				data_init(char **arg, t_data *data);
int				phil_init(t_phil *phil, int id, t_data *data);

/*
** Destruction
*/
void			destroy_mutex(pthread_mutex_t *mutex);
void			destroy_mutex_babies(pthread_mutex_t *forks, int i);

/*
**	Helpers
*/
size_t			get_time(void);
int				ft_strlen(char *str);
void			phil_msg(t_phil *phil, char *msg, bool force_write);
int				ft_atoi(char *nb);
void			zzz(size_t sleep_time);
bool			check_death(t_data *data);

/*
** Errors
*/
bool			error(char *msg);
bool			validate_input(char **arg, t_data *dat);

#endif
