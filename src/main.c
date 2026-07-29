/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thasampa <thasampa@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 16:42:11 by thasampa          #+#    #+#             */
/*   Updated: 2026/07/24 16:42:14 by thasampa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	main(int argc, char **argv)
{
	t_config	config;
	t_engine	engine;

	if (!parse_args(argc, argv, &config))
		return (1);
	if (!init_engine(&engine, config))
		return (1);
	cleanup_engine(&engine);
	return (0);
}
