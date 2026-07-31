/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thasampa <thasampa@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 16:15:41 by thasampa          #+#    #+#             */
/*   Updated: 2026/07/29 16:15:46 by thasampa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	destroy_all_dongles(t_engine *engine)
{
	int	i;

	i = 0;
	while (i < engine->config.num_coders)
	{
		heap_destroy(engine->dongles[i].queue);
		pthread_cond_destroy(&engine->dongles[i].cond);
		pthread_mutex_destroy(&engine->dongles[i].mutex);
		i++;
	}
}

static void	destroy_all_coders(t_engine *engine)
{
	int	i;

	i = 0;
	while (i < engine->config.num_coders)
	{
		pthread_mutex_destroy(&engine->coders[i].state_mutex);
		i++;
	}
}

void	cleanup_engine(t_engine *engine)
{
	if (!engine)
		return ;
	if (engine->dongles)
	{
		destroy_all_dongles(engine);
		free(engine->dongles);
	}
	if (engine->coders)
	{
		destroy_all_coders(engine);
		free(engine->coders);
	}
	pthread_mutex_destroy(&engine->state_mutex);
	pthread_mutex_destroy(&engine->log_mutex);
}
