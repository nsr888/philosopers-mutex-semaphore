/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinistr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 12:39:00 by ksinistr          #+#    #+#             */
/*   Updated: 2020/11/20 13:29:28 by anasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_vars		*init_vars_struct(t_argv args, t_philosophers *philo, \
		pthread_t *ptr)
{
	t_vars			*vars;

	if (!(vars = malloc(sizeof(*vars))))
		return (NULL);
	vars->ptr = ptr;
	vars->args = args;
	vars->mtx = philo[0].mtx;
	vars->shared = philo[0].shared;
	return (vars);
}

static void			free_all(t_philosophers *philo, pthread_t *ptr)
{
	free(philo->mtx->forks);
	free(philo->mtx);
	free(philo->shared->time_of_start);
	free(philo->shared->eat_count);
	free(philo->shared->timestamp_last_meal);
	free(philo);
	free(ptr);
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

static void			destroy_mutexes(t_philosophers *philo)
{
	int				i;

	i = 0;
	while (i < philo[0].args.number_of_philosophers)
	{
		pthread_mutex_destroy(&(philo[0].mtx->forks[i]));
		i++;
	}
	pthread_mutex_destroy(&(philo[0].mtx->mutex_write_lock));
}

int					main(int argc, char **argv)
{
	t_philosophers	*philo;
	t_argv			args;
	t_vars			*vars;
	pthread_t		*ptr;
	int				i;

	if (is_input_has_errors(argc, argv))
		return (1);
	args = init_args_struct(++argv);
	philo = init_philo_struct(args);
	if (!(ptr = malloc(sizeof(*ptr) * (args.number_of_philosophers + 1))))
		return (1);
	i = -1;
	while (++i < args.number_of_philosophers)
		if (pthread_create(&(ptr[i]), NULL, &philo_work, &(philo[i])) != 0)
			return (1);
	vars = init_vars_struct(args, philo, ptr);
	if (pthread_create(&(ptr[i]), NULL, &check_threads, (void *)vars) != 0)
		return (1);
	if (pthread_join(ptr[i], NULL) != 0)
		return (1);
	destroy_mutexes(philo);
	free_all(philo, ptr);
	return (0);
}
