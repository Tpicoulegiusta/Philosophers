/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicoule <tpicoule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 13:43:44 by tpicoule          #+#    #+#             */
/*   Updated: 2024/02/19 17:36:58 by tpicoule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_init(t_all *all)
{
	pthread_mutex_init(&all->data.mutex, NULL);
    ft_thread_philo(all);
    pthread_mutex_destroy(&all->data.mutex);
}

int main(int argc, char **argv)
{
    t_all   all;

    if (check_args(argc, argv) != 0)
        return(write(1, "bad args\n", 9), 1);
    if (check_args_2(argv, &all) != 0)
        return(write(1, "bad argsss\n", 9), 1);
    all.philos = malloc(sizeof(t_ph) * all.data.nb_philo);
    if (!all.philos)
		return(write(1,"malloc", 6), 1);
	ft_init(&all);
	while(1)
	{
		//check mort
		//mort = temps actuel - temps du last meal
		
	}
}
