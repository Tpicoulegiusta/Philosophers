/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dest_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicoule <tpicoule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:20:42 by tpicoule          #+#    #+#             */
/*   Updated: 2024/03/01 14:42:14 by tpicoule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    destroy_all(t_all *all)
{
    pthread_mutex_destroy(&all->data.mutex);
	pthread_mutex_destroy(&all->data.tab_lmeal_mutex);
	pthread_mutex_destroy(&all->data.static_mutex);
	// pthread_mutex_destroy(&all->data.mutex_print);
	pthread_mutex_destroy(&all->data.mutex_eat);
}
