/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_state.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thasampa <thasampa@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 14:19:36 by thasampa          #+#    #+#             */
/*   Updated: 2026/07/31 14:19:39 by thasampa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	simulation_should_stop(t_engine *engine)
{
	int	stop;

	pthread_mutex_lock(&engine->state_mutex);
	stop = engine->simulation_stop;
	pthread_mutex_unlock(&engine->state_mutex);
	return (stop);
}

int	stop_simulation(t_engine *engine)
{
	int	changed;

	pthread_mutex_lock(&engine->state_mutex);
	changed = !engine->simulation_stop;
	engine->simulation_stop = 1;
	pthread_mutex_unlock(&engine->state_mutex);
	return (changed);
}

void	wake_all_coders(t_engine *engine)
{
	int	i;

	i = 0;
	while (i < engine->config.num_coders)
	{
		pthread_mutex_lock(&engine->dongles[i].mutex);
		pthread_cond_broadcast(&engine->dongles[i].cond);
		pthread_mutex_unlock(&engine->dongles[i].mutex);
		i++;
	}
}
