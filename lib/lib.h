/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <smagniny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 17:41:11 by smagniny          #+#    #+#             */
/*   Updated: 2023/09/19 18:24:19 by smagniny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_H
# define LIB_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

# define EAT "is eating\n"
# define SLEEP "is sleeping\n"
# define THINK "is thinking\n"
# define DIE "has died\n"

typedef struct s_philo
{
	struct timeval	ts;
	pthread_mutex_t	tmutex;
	struct timeval	tinit;
	int				id;
	int				haseat;
	int				loneliness;
	int				thinkflag;
	int				time_die;
	int				time_eat;
	int				time_slp;
	pthread_mutex_t	deadwrap;
	int				dead;
	pthread_mutex_t	*lefork;
	int				lfk;
	pthread_mutex_t	*rifork;
	int				rfk;
}	t_philos;

//variables de main y params pasados a cada proceso
typedef struct s_var
{
	pthread_t		*proc;
	t_philos		*philos;
	int				nb;
	int				time_die;
	int				time_eat;
	int				time_slp;				
	int				menu;
	pthread_mutex_t	endwrap;
	int				end;
	struct timeval	tinit;
	pthread_mutex_t	*forks;
	int				id;
}	t_var;

//initializing
//parse input and enter values to main struct.
int				getargs(int argc, char **argv, t_var *var);
int				alloc(t_var *var);
void			init_mutexes(t_var *var);
//routina
void			*routine(void *varp);
void			*alone(t_philos *philo);
int				ft_strcmp(const char *s1, const char *s2);
int				theyhaveeat(t_philos *philo);
int				ft_sleep(t_philos *philo, int time);
void			ft_printf(t_philos *philo, char *action);
void			philoconstructor(t_var *var);
//Gestión de errores
long long		timenow(struct timeval *te);
long long		elapsedtime(struct timeval *ts);
int				seedeadval(t_philos *philo);
int				diestarvation(t_philos *philo);
void			checkdeath(t_var *var);
int				ft_exit(t_var *var, int freeallocs, int freemutex, char *str);
#endif