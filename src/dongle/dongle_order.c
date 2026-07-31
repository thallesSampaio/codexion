/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle_order.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thasampa <thasampa@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 14:41:44 by thasampa          #+#    #+#             */
/*   Updated: 2026/07/31 14:41:49 by thasampa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	order_coder_dongles(t_coder *coder, t_dongle **first,
		t_dongle **second)
{
	if (coder->left_dongle < coder->right_dongle)
	{
		*first = coder->left_dongle;
		*second = coder->right_dongle;
	}
	else
	{
		*first = coder->right_dongle;
		*second = coder->left_dongle;
	}
}

void	lock_coder_dongles(t_coder *coder)
{
	t_dongle	*first;
	t_dongle	*second;

	order_coder_dongles(coder, &first, &second);
	pthread_mutex_lock(&first->mutex);
	pthread_mutex_lock(&second->mutex);
}

void	unlock_coder_dongles(t_coder *coder)
{
	t_dongle	*first;
	t_dongle	*second;

	order_coder_dongles(coder, &first, &second);
	pthread_mutex_unlock(&second->mutex);
	pthread_mutex_unlock(&first->mutex);
}
