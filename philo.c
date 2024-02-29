/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicoule <tpicoule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 13:43:44 by tpicoule          #+#    #+#             */
/*   Updated: 2024/02/29 14:47:55 by tpicoule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_init(t_all *all)
{
	pthread_mutex_init(&all->data.mutex, NULL);
	pthread_mutex_init(&all->data.mutex_print, NULL);
	pthread_mutex_init(&all->data.mutex_eat, NULL);
	pthread_mutex_lock(&all->data.mutex_print);
	all->is_sim = 1;
	pthread_mutex_unlock(&all->data.mutex_print);
	ft_thread_philo(all);
}

int	main(int argc, char **argv)
{
	t_all	all;

	if (check_args(argc, argv) != 0)
		return (write(1, "bad args\n", 9), 1);
	if (check_args_2(argv, &all) != 0)
		return (write(1, "bad argsss\n", 9), 1);
	all.philos = malloc(sizeof(t_ph) * all.data.nb_philo);
	if (!all.philos)
		return (write(1, "malloc\n", 7), 1);
	ft_init(&all);
	while (1)
	{
		if (ft_check_death(&all) != 0)
			break ;
		ft_usleep(1);
	}
	//printf("%d\n", all.is_sim);
	return (0);
}
