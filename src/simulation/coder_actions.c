/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thasampa <thasampa@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 14:45:01 by thasampa          #+#    #+#             */
/*   Updated: 2026/07/31 14:45:12 by thasampa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	coder_compile(t_coder *coder)
{
	if (!acquire_coder_dongles(coder))
		return (0);
	coder_start_compile(coder);
	log_state(coder, "is compiling");
	precise_sleep(coder->engine,
		coder->engine->config.time_to_compile);
	release_coder_dongles(coder);
	if (simulation_should_stop(coder->engine))
		return (0);
	coder_finish_compile(coder);
	return (1);
}

static int	coder_debug(t_coder *coder)
{
	if (simulation_should_stop(coder->engine))
		return (0);
	log_state(coder, "is debugging");
	precise_sleep(coder->engine,
		coder->engine->config.time_to_debug);
	return (!simulation_should_stop(coder->engine));
}

static int	coder_refactor(t_coder *coder)
{
	if (simulation_should_stop(coder->engine))
		return (0);
	log_state(coder, "is refactoring");
	precise_sleep(coder->engine,
		coder->engine->config.time_to_refactor);
	return (!simulation_should_stop(coder->engine));
}

int	run_coder_cycle(t_coder *coder)
{
	if (!coder_compile(coder))
		return (0);
	if (!coder_debug(coder))
		return (0);
	if (!coder_refactor(coder))
		return (0);
	return (1);
}
