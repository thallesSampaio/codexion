/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_simulation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thasampa <thasampa@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 17:22:05 by thasampa          #+#    #+#             */
/*   Updated: 2026/07/29 17:22:54 by thasampa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	join_coder_threads(t_engine *engine, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_join(engine->coders[i].thread, NULL);
		i++;
	}
}

static int	create_coder_threads(t_engine *engine, int *created)
{
	int	i;

	i = 0;
	while (i < engine->config.num_coders)
	{
		if (pthread_create(&engine->coders[i].thread, NULL,
				coder_routine, &engine->coders[i]) != 0)
		{
			*created = i;
			return (0);
		}
		i++;
	}
	*created = i;
	return (1);
}

int	run_simulation(t_engine *engine)
{
	int	created;

	created = 0;
	if (!create_coder_threads(engine, &created))
	{
		join_coder_threads(engine, created);
		return (0);
	}
	join_coder_threads(engine, created);
	return (1);
}
