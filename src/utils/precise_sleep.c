/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precise_sleep.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thasampa <thasampa@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 14:31:58 by thasampa          #+#    #+#             */
/*   Updated: 2026/07/31 14:32:03 by thasampa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	precise_sleep(t_engine *engine, long long duration)
{
	long long	end;

	end = get_time_ms() + duration;
	while (!simulation_should_stop(engine))
	{
		if (get_time_ms() >= end)
			break ;
		usleep(200);
	}
}
