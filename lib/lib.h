/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <santi.mag777@student.42madrid    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 17:41:11 by smagniny          #+#    #+#             */
/*   Updated: 2023/09/19 09:34:27 by smagniny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_H
# define LIB_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <string.h> ///////////////quitar

# define EAT "is eating\n"
# define SLEEP "is sleeping\n"
# define THINK "is thinking\n"
# define DIE "has died\n"
//variables locales de cada rutina 
//junto con variables mutex para coordinación de las variables forks.

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
	pthread_t		*proc;// alloc
	t_philos		*philos;// alloc
	int				nb;
	int				time_die;
	int				time_eat;
	int				time_slp;				
	int				menu;
	pthread_mutex_t	endwrap;
	int				end;
	struct timeval	tinit; // initializar tINITT
	pthread_mutex_t	*forks; //alloc && initmutex
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
int				diestarvation(t_philos *philo);
//Utils
int				ft_sleep(t_philos *philo, int time);
int				seedeadval(t_philos *philo);
void			ft_printf(t_philos *philo, char *action);
long	long	unsigned	timenow(struct timeval *te);
long	long	elapsedtime(struct timeval *ts);
void			philoconstructor(t_var *var);
//Gestión de errores
void			checkdeath(t_var *var);
int 			ft_exit(t_var *var, int freeallocs, int freemutex, char *str);
#endif