/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_dongles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thasampa <thasampa@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 16:15:09 by thasampa          #+#    #+#             */
/*   Updated: 2026/07/29 16:15:13 by thasampa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	init_one_dongle(t_engine *engine, int index)
{
	t_dongle	*dongle;

	dongle = &engine->dongles[index];
	if (pthread_mutex_init(&dongle->mutex, NULL) != 0)
		return (0);
	if (pthread_cond_init(&dongle->cond, NULL) != 0)
	{
		pthread_mutex_destroy(&dongle->mutex);
		return (0);
	}
	dongle->queue = heap_create(engine->config.num_coders);
	if (!dongle->queue)
	{
		pthread_cond_destroy(&dongle->cond);
		pthread_mutex_destroy(&dongle->mutex);
		return (0);
	}
	return (1);
}

static void	destroy_initialized_dongles(t_engine *engine, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		heap_destroy(engine->dongles[i].queue);
		pthread_cond_destroy(&engine->dongles[i].cond);
		pthread_mutex_destroy(&engine->dongles[i].mutex);
		engine->dongles[i].queue = NULL;
		i++;
	}
}

int	init_dongles(t_engine *engine)
{
	int	i;

	i = 0;
	while (i < engine->config.num_coders)
	{
		if (!init_one_dongle(engine, i))
		{
			destroy_initialized_dongles(engine, i);
			return (0);
		}
		engine->dongles[i].is_in_use = 0;
		engine->dongles[i].last_released_time = 0;
		i++;
	}
	return (1);
}
