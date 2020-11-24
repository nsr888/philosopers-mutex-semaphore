/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinistr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 12:53:59 by ksinistr          #+#    #+#             */
/*   Updated: 2020/11/24 10:28:43 by ksinistr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct		s_mtx{
	pthread_mutex_t	mutex_write_lock;
	pthread_mutex_t	*forks;
}					t_mtx;

typedef struct		s_argv{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
}					t_argv;

typedef struct		s_shared{
	long long		*time_of_start;
	int				*timestamp_last_meal;
	int				*eat_count;
}					t_shared;

typedef struct		s_philosophers{
	int				current_philo;
	t_mtx			*mtx;
	t_argv			args;
	t_shared		*shared;
	int				number_of_times_current_philosopher_eat;
}					t_philosophers;

typedef struct		s_forks{
	int				left;
	int				right;
}					t_forks;

typedef struct		s_vars{
	pthread_t		*ptr;
	t_argv			args;
	t_shared		*shared;
	t_mtx			*mtx;
}					t_vars;

int					ft_atoi(const char *str);
char				*ft_itoa(int n);
char				*ft_strjoin(char const *s1, char const *s2);
size_t				ft_strlen(const char *s);
void				*ft_calloc(size_t count, int size);
void				ft_usleep(int ms);

/*
** init_structures.c
*/

t_mtx				*init_mtx_struct(int number_of_philosophers);
t_argv				init_args_struct(char **argv);
t_shared			*init_shared_struct(int number_of_philosophers);
t_philosophers		*init_philo_struct(t_argv args);

/*
** print_timestamp.c
*/

void				print_timestamp(char *s, int current_philo, int timestamp);
int					print_timestamp_philo(char *s, t_philosophers *philo);
int					get_timestamp(long long time_of_start);
long long			get_current_time_in_ms(void);

/*
** philo_work.c
*/

void				*philo_work(void *ptr);

/*
** check_threads.c
*/

void				*check_threads(void *p);

#endif
