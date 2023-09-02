

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

//muerte a todos
//detectar 10ms de retraso
//architectura intentar recursiva
//norminette

static int	loopswitch(t_var	*varcpy, int id)
{
	t_localvar	localvar;

	if (setlocalvar(&localvar, varcpy, id))
		return (1);
	if (varcpy->menu == -77)
	{
		while (42)
		{	
			if (brain(varcpy, &localvar, id))
			{
				printf("[ERREUR]\n");
				killphilos(varcpy);
				return (1);
			}
		}
	}
	else
	{
		while (localvar.me->hseaten < varcpy->menu)
		{
			if (brain(varcpy, &localvar, id))
			{
				printf("[ERREUR]\n");
				killphilos(varcpy);
				return (1);
			}
		}
	}
	return (0);
}

void	*oneperson(void *var)
{
	t_var				*varcpy;
	int					id;

	varcpy = (t_var *)var;
	get_next_id(varcpy, &id);
	loopswitch(varcpy, id);
	return (0);
}

int	main(int argc, char **argv)
{
	t_var		var;
	int			i;

	i = -1;
	if (!getargs(argc, argv, &var)) // recuperando todos los args
		exit(1);
	if (maketable(&var))
		exit(1);
	while (++i < var.nbphilo) //creando procesos y llamada a la fucnion
	{
		if (pthread_create(&var.proc[i], NULL, oneperson, (void *)&var))
			exit(1);
	}
	//liberando mallocs de procesos
	//cerrando mutexes e Philos
	i = -1;
	while (++i < var.nbphilo)
		pthread_join(var.proc[i], NULL);
	if (cleantable(&var))
		exit(1);
	return (0);
}
