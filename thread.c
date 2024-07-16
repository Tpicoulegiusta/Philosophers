/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicoule <tpicoule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 09:44:14 by tpicoule          #+#    #+#             */
/*   Updated: 2024/02/28 10:14:38 by tpicoule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print(t_all *all, int id, char *str)
{
	pthread_mutex_lock(&all->data.mutex_print);
	if (all->is_sim == 1)
		printf("%ld Philo %d %s\n", actual_time_ms() - all->data.start_time, (id + 1), str);
	pthread_mutex_unlock(&all->data.mutex_print);
}

void	ft_take_fork(t_all *all, int id)
{

	pthread_mutex_lock(&all->philos[id].left_fork);
	ft_print(all, id, "has taken a fork");
	pthread_mutex_lock(&all->philos[(id + 1) % all->data.nb_philo].left_fork);
	ft_print(all, id, "has taken a fork");
 }
 
void	ft_drop_fork(t_all *all, int id)
{
 	pthread_mutex_unlock(&all->philos[(id + 1) % all->data.nb_philo].left_fork);
	pthread_mutex_unlock(&all->philos[id].left_fork);
}

void	ft_eat(t_all *all, int id)
{
	ft_take_fork(all, id);
	ft_print(all, id, "is eating");
	all->philos[id].tab_lmeal = actual_time_ms();
	ft_usleep(all->data.teat);
	ft_drop_fork(all, id);
	all->philos[id].count_eat += 1;
	
}

void lil_check(t_all all, int id)
{
	if (all.data.nb_philo != 1)
	{
		if(id % 2)
			ft_usleep(60);
	}
}

// int	ft_check_eat(t_all all, int argc, char **argv)
// {
// 	int i;
// 	i = 0;
// 	if(argc == 6)
// 	{
// 		while(i != all.data.nb_philo)
// 		{
// 			if(all.philos->count_eat == argv[5])
// 				break;
// 		}
// 	}
	
// }

int	ft_check_death(t_all *all)
{
	int		i;
	int		j;
	int		nb_eat;
	long	diff;

	i = 0;
	j = 0;
	nb_eat = 0;
	while(i < all->data.nb_philo)
	{
		diff = actual_time_ms() - all->philos[i].tab_lmeal;
		if (diff > all->data.tdie)
		{
			pthread_mutex_lock(&all->data.mutex_print);
			all->is_sim = 0;
			pthread_mutex_unlock(&all->data.mutex_print);
			printf("ivan %d died at %ld\n", (i + 1), diff);
			return(write(1, "death\n", 6), 1);
		}
		if (all->philos[i].count_eat == all->data.meat)
			nb_eat++;
		i++;
	}
	//printf("nb_eat=%d\n", nb_eat);
	if (nb_eat >= all->data.nb_philo)
	{
		pthread_mutex_lock(&all->data.mutex_print);
		all->is_sim = 0;
		pthread_mutex_unlock(&all->data.mutex_print);
		printf("Ils ont magnged/n\n");
		return (1);
	}
	return(0);
}

void routine(t_all *all)
{
	static int	static_id;
	int			id;

	id = static_id;
	static_id++;
	lil_check(*all, id);
	while(1)
	{
		pthread_mutex_lock(&all->data.mutex_print);
		if (all->is_sim == 0)
			break;
		pthread_mutex_unlock(&all->data.mutex_print);
		ft_eat(all, id);
		ft_print(all, id, "is sleeping");
		ft_usleep(all->data.tslp);
		ft_print(all, id, "is thinking");
	}
}

void ft_thread_philo(t_all *all)
{
    int i;

    i = 0;
	all->data.start_time = actual_time_ms();
	while (i < all->data.nb_philo)
	{
		all->philos[i].count_eat = 0;
		all->philos[i].tab_lmeal = all->data.start_time;
		pthread_mutex_init(&all->philos[i].left_fork, NULL);
		pthread_create(&all->philos[i].philo_thread, NULL, (void*) &routine, all);
		i++;
	}
	//puts("soleil");
}

