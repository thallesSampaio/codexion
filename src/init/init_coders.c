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

void	init_coders(t_engine *engine)
{
	int	i;

	i = 0;
	while (i < engine->config.num_coders)
	{
		engine->coders[i].id = i + 1;
		engine->coders[i].last_compile_start = engine->start_time;
		engine->coders[i].compiles_done = 0;
		engine->coders[i].engine = engine;
		engine->coders[i].left_dongle = &engine->dongles[i];
		engine->coders[i].right_dongle = &engine->dongles[(i + 1)
			% engine->config.num_coders];
		i++;
	}
}
