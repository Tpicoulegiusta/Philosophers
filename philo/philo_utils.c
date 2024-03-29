/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicoule <tpicoule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 12:26:09 by tpicoule          #+#    #+#             */
/*   Updated: 2024/03/05 14:04:11 by tpicoule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *str)
{
	int	i;
	int	x;

	x = 0;
	i = 0;
	while ((str[i] >= '\t' && str[i] <= '\r') || (str[i] == 32))
		i++;
	while (str[i] != '\0')
	{
		if (str[i] >= '0' && str[i] <= '9')
			x = x * 10 + str[i] - '0';
		else
			return (x);
		i++;
	}
	return (x);
}
