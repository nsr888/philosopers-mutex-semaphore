/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinistr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 12:39:00 by ksinistr          #+#    #+#             */
/*   Updated: 2020/11/24 12:12:29 by ksinistr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_vars				*init_vars_struct(pthread_t ptr, t_philosophers philo)
{
	t_vars			*vars;

	if (!(vars = malloc(sizeof(*vars))))
		return (NULL);
	vars->ptr = ptr;
	vars->philo = philo;
	return (vars);
}

static void			kill_and_clean(t_philosophers *philo, int *child, \
		t_sem *sem)
{
	int				i;

	i = -1;
	while (++i < philo[0].args.number_of_philosophers)
		kill(child[i], SIGTERM);
	sem_close(sem->write_lock);
	sem_close(sem->forks);
	sem_close(sem->steward);
	free(philo->sem);
	free(philo->shared->time_of_start);
	free(philo->shared->eat_count);
	free(philo->shared->timestamp_last_meal);
	free(philo->shared);
	free(philo);
	free(child);
}

static int			is_input_has_errors(int argc, char **argv)
{
	char			*s1;

	if ((argc != 5 && argc != 6) || ft_atoi(argv[1]) < 2)
	{
		s1 = "Incorrect number of arguments\n";
		write(2, s1, ft_strlen(s1));
		return (1);
	}
	return (0);
}

/*
** if is passed number_of_times_each_philosopher_must_eat and
** philo died too soon, then process exit with status EXIT_FAILURE,
** and then main process kill all childs, otherwise it will wait all childs.
** WNOHANG flag used for nonblocking usage of waitpid in while.
*/

int					main(int argc, char **argv)
{
	t_philosophers	*philo;
	t_argv			args;
	pid_t			*child;
	int				status;

	if (is_input_has_errors(argc, argv))
		return (1);
	args = init_args_struct(++argv);
	philo = init_philo_struct(args);
	if (!(child = malloc(sizeof(int) * args.number_of_philosophers)))
		return (1);
	if (create_processes_and_threads(args, philo, child))
		return (1);
	if (args.number_of_times_each_philosopher_must_eat == -1)
		while (waitpid(-1, NULL, WNOHANG) == 0)
			;
	else
		while (waitpid(-1, &status, WNOHANG) != -1)
			if (WIFEXITED(status))
				if (WEXITSTATUS(status) == EXIT_FAILURE)
					break ;
	kill_and_clean(philo, child, philo[0].sem);
	return (0);
}
