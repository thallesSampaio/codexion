/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle_release.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thasampa <thasampa@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 14:43:59 by thasampa          #+#    #+#             */
/*   Updated: 2026/07/31 14:44:02 by thasampa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	release_coder_dongles(t_coder *coder)
{
	long long	now;

	now = get_time_ms();
	lock_coder_dongles(coder);
	coder->left_dongle->is_in_use = 0;
	coder->right_dongle->is_in_use = 0;
	coder->left_dongle->last_released_time = now;
	coder->right_dongle->last_released_time = now;
	pthread_cond_broadcast(&coder->left_dongle->cond);
	pthread_cond_broadcast(&coder->right_dongle->cond);
	unlock_coder_dongles(coder);
}
