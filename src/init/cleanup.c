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

static void	destroy_dongles(t_engine *engine)
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
	free(engine->dongles);
	engine->dongles = NULL;
}

void	cleanup_engine(t_engine *engine)
{
	if (!engine)
		return ;
	if (engine->dongles)
		destroy_dongles(engine);
	if (engine->coders)
	{
		free(engine->coders);
		engine->coders = NULL;
	}
	pthread_mutex_destroy(&engine->state_mutex);
	pthread_mutex_destroy(&engine->log_mutex);
}
