/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicoule <tpicoule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 15:10:34 by tpicoule          #+#    #+#             */
/*   Updated: 2024/03/05 14:21:26 by tpicoule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data
{
	int				nb_ph;
	int				teat;
	int				tdie;
	int				tslp;
	int				meat;
	long int		start_t;
	pthread_mutex_t	mutex;
	pthread_mutex_t	tab_lmeal_mutex;
	pthread_mutex_t	static_mutex;
	pthread_mutex_t	mutex_print;
	pthread_mutex_t	mutex_eat;
	pthread_mutex_t	mutex_count_eat;
}	t_data;

typedef struct s_ph
{
	int				count_eat;
	int				done;
	long int		tab_lmeal;
	pthread_mutex_t	l_fork;
	pthread_t		philo_thread;
}	t_ph;

typedef struct s_all
{
	t_data	data;
	t_ph	*philos;
	int		is_sim;
}	t_all;

int			check_args(int argc, char **argv);
int			check_args_2(char **argv, t_all *all);
int			ft_strlen(char *s);
int			ft_nb(char **argv);
int			ft_atoi(char *str);
void		ft_thread_philo(t_all *all);
void		routine(t_all *all);
void		ft_init(t_all *all);
long int	actual_time_ms(void);
int			ft_check_death(t_all *all);
void		ft_usleep(int time);
void		lil_check(t_all all, int id);
void		ft_drop_fork(t_all *all, int id);
void		ft_print(t_all *all, int id, char *str);
void		ft_eat(t_all *all, int id);
void		ft_take_fork(t_all *all, int id);
void		ft_drop_fork(t_all *all, int id);
void		destroy_all(t_all *all);
void		ft_check_thread(t_all *all);
void		ft_try(t_all *all, int id);

#endif