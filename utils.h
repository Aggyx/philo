/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <santi.mag777@student.42madrid    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 17:41:11 by smagniny          #+#    #+#             */
/*   Updated: 2023/08/30 15:55:31 by smagniny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

//datos de cada nodo  que no se comparten aparte los mutex

typedef struct s_philo
{
	int				id;
	int				is_eating;
	int				hseaten;
	pthread_mutex_t	mfkwrap;
	int				fkwrap;
	pthread_mutex_t	fork;
	int				fk;
	struct s_philo	*prev;
	struct s_philo	*next;
}		t_philo;
//mesa
typedef struct s_table
{
	struct s_philo	*top;
}		t_table;
//variables de main y param compartidos a cada proceso
typedef struct s_var
{
	pthread_t		*proc;
	t_table			*table;
	int				nbphilo;
	int				timedie;
	int				time_eat;
	int				time_slp;
	int				menu;
	struct timeval	ts;
	struct timeval	tinit;
	pthread_mutex_t	idwrap;
	int				id;
}	t_var;

//variables de funciones de cada proceso de nodo
typedef struct s_localvar
{
	t_philo			*neighbor;
	t_philo			*neighbol;
	t_philo			*me;
	int				thinkflag;
}	t_localvar;

//init
int		getargs(int argc, char **argv, t_var *var);
int		maketable(t_var *var);
int		cleantable(t_var *var);
//philos stuff
int		setlocalvar(t_localvar *localvar, t_var	*varcpy, int id);
int		killphilos(t_var *varcpy);
int		diestarvation(t_var *shrd, int id);
int		getstatusphilo(t_philo	*philo);
t_philo	*getphilo(t_table *table, int id);
int		binarymutexlock(t_philo *me, t_philo *neighbor);
int		binarymutexunlock(t_philo *me, t_philo *neighbor);
int		eat(t_philo *me, t_philo *neighbor);
int		finisheat(t_philo *me, t_philo *neighbor, int id, struct timeval *ts);
int		brain(t_var *varcpy, t_localvar *lvar, int id);
unsigned long	elapsedtime(struct timeval *ts);
//track philo id
void	get_next_id(t_var *var, int *id);
//helpfuncs
int		push(t_table *table, int id);
int		lstsize(t_table *table);
t_philo	*lastelem(t_table	*stack);

#endif