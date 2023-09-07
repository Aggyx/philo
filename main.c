

#include "utils.h"

/*
1 800 200 200
a philo should die
4 310 200 100
a philo should die
4 200 205 200
a philo should die
5 800 200 200 7
no one should die, simulation should stop after 7 eats
4 410 200 200 10
no one should die, simulation should stop after 10 eats
-5 600 200 200
should error and not run (no crashing)
4 -5 200 200
should error and not run (no crashing)
4 600 -5 200
should error and not run (no crashing)
4 600 200 -5
should error and not run (no crashing)
4 600 200 200 -5
should error and not run (no crashing)

5 800 200 200
no one should die
5 600 150 150
no one should die
4 410 200 200
no one should die
100 800 200 200
no one should die
105 800 200 200
no one should die
200 800 200 200
no one should die

Black \033[0;30m
Red \033[0;31m
Green \033[0;32m
Yellow \033[0;33m
Blue \033[0;34m
Purple \033[0;35m
Cyan \033[0;36m
White \033[0;37m
*/

//cosas por hacer
//muchas cosas
//muerte de todos despues de una muerte
//detectar 10ms de retraso
//norminette

static int	loopswitch(t_var	*varcpy, t_localvar *lvar)
{
	if (varcpy->menu == -77)
	{	
		pthread_mutex_lock(&varcpy->endwrap);
		while (42 && !varcpy->end)
		{
			pthread_mutex_unlock(&varcpy->endwrap);
			if (brain(varcpy, lvar, lvar->me->id))
			{
				while (diestarvation(varcpy, lvar, lvar->me->id,  1) != 1)
					;
				return (1);
			}
		}
		pthread_mutex_unlock(&varcpy->endwrap);
	}
	else
	{
		pthread_mutex_lock(&lvar->me->deadwrap);
		while (lvar->me->hseaten < varcpy->menu && !lvar->me->dead)
		{
			pthread_mutex_unlock(&lvar->me->deadwrap);
			if (brain(varcpy, lvar, lvar->me->id))
			{
				// if (pthread_mutex_lock(&localvar.me->deathwrap))
				// 	return (1);
				// localvar.me->deathflag = 1;
				// if (pthread_mutex_unlock(&localvar.me->deathwrap))
				// 	return (1);
				while (diestarvation(varcpy, lvar, lvar->me->id, 1) != 1)
					;
				return (1);
			}
		}
		pthread_mutex_unlock(&lvar->me->deadwrap);
	}

	return (0);
}

void	*oneperson(void *var)
{
	t_var				*varcpy;
	t_localvar			localvar;
	int					id;

	varcpy = (t_var *)var;
	id = get_next_id(varcpy, &localvar);
	if (id % 2 == 0)
		usleep(10);
	if (setlocalvar(&localvar, varcpy, id))
		return (0);
	loopswitch(varcpy, &localvar);
	return (0);
}

int	main(int argc, char **argv)
{
	t_var		var;
	int			i;

	i = -1;
	if (!getargs(argc, argv, &var))
		exit(1);
	if (maketable(&var))
		exit(1);
	while (++i < var.nbphilo)
	{
		if (pthread_create(&var.proc[i], NULL, oneperson, (void *)&var))
			exit(1);
	}
	checkdeath(&var);
	i = -1;
	while (++i < var.nbphilo)
		pthread_join(var.proc[i], NULL);
	if (cleantable(&var))
		exit(1);
	return (0);
}
