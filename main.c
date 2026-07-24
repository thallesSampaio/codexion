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

#include "codexion.h"

static void	print_success(t_engine *engine)
{
	char	*sched_str;

	if (engine->config.scheduler == CX_SCHED_FIFO)
		sched_str = "FIFO";
	else
		sched_str = "EDF";
	printf("Parsing OK! Coders: %d, Burnout: %lldms, Sched: %s\n",
		engine->config.num_coders,
		engine->config.time_to_burnout,
		sched_str);
}

int	main(int argc, char **argv)
{
	t_config	config;
	t_engine	engine;

	if (!parse_args(argc, argv, &config))
		return (1);
	if (!init_engine(&engine, config))
	{
		write(2, "Error: Engine initialization failed.\n", 36);
		cleanup_engine(&engine);
		return (1);
	}
	print_success(&engine);
	cleanup_engine(&engine);
	return (0);
}
