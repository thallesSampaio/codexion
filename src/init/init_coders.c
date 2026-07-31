/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_coders.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thasampa <thasampa@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 16:15:28 by thasampa          #+#    #+#             */
/*   Updated: 2026/07/29 16:15:32 by thasampa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	set_coder_data(t_engine *engine, int index)
{
	t_coder	*coder;

	coder = &engine->coders[index];
	coder->id = index + 1;
	coder->last_compile_start = engine->start_time;
	coder->compiles_done = 0;
	coder->engine = engine;
	coder->left_dongle = &engine->dongles[index];
	coder->right_dongle = &engine->dongles[(index + 1)
		% engine->config.num_coders];
}

void	destroy_coder_mutexes(t_engine *engine, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(&engine->coders[i].state_mutex);
		i++;
	}
}

int	init_coders(t_engine *engine)
{
	int	i;

	i = 0;
	while (i < engine->config.num_coders)
	{
		set_coder_data(engine, i);
		if (pthread_mutex_init(&engine->coders[i].state_mutex, NULL) != 0)
		{
			destroy_coder_mutexes(engine, i);
			return (0);
		}
		i++;
	}
	return (1);
}
