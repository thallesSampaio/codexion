/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thasampa <thasampa@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 14:43:10 by thasampa          #+#    #+#             */
/*   Updated: 2026/07/31 14:43:13 by thasampa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	coder_is_first(t_dongle *dongle, int coder_id)
{
	t_request	request;

	if (!heap_peek(dongle->queue, &request))
		return (0);
	return (request.coder_id == coder_id);
}

static int	cooldown_finished(t_dongle *dongle, t_engine *engine,
		long long now)
{
	long long	available_at;

	available_at = dongle->last_released_time
		+ engine->config.dongle_cooldown;
	return (now >= available_at);
}

int	coder_can_take_dongles(t_coder *coder)
{
	t_engine	*engine;
	long long	now;

	engine = coder->engine;
	now = get_time_ms();
	if (coder->left_dongle->is_in_use
		|| coder->right_dongle->is_in_use)
		return (0);
	if (!cooldown_finished(coder->left_dongle, engine, now))
		return (0);
	if (!cooldown_finished(coder->right_dongle, engine, now))
		return (0);
	if (!coder_is_first(coder->left_dongle, coder->id))
		return (0);
	return (coder_is_first(coder->right_dongle, coder->id));
}
