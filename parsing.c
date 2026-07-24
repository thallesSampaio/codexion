/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thasampa <thasampa@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 16:35:25 by thasampa          #+#    #+#             */
/*   Updated: 2026/07/24 16:35:28 by thasampa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static long long	ft_atoll(const char *str)
{
	long long	res;
	int			i;

	res = 0;
	i = 0;
	if (!str || !str[0])
		return (-1);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res);
}

static int	validate_nums(t_config *config)
{
	if (config->num_coders <= 0 || config->time_to_burnout < 0
		|| config->time_to_compile < 0 || config->time_to_debug < 0
		|| config->time_to_refactor < 0 || config->num_compiles_required <= 0
		|| config->dongle_cooldown < 0)
	{
		write(2, "Error: Invalid numeric arguments.\n", 34);
		return (0);
	}
	return (1);
}

int	parse_args(int argc, char **argv, t_config *config)
{
	if (argc != 9)
	{
		write(2, "Error: Invalid number of arguments.\n", 36);
		return (0);
	}
	config->num_coders = (int)ft_atoll(argv[1]);
	config->time_to_burnout = ft_atoll(argv[2]);
	config->time_to_compile = ft_atoll(argv[3]);
	config->time_to_debug = ft_atoll(argv[4]);
	config->time_to_refactor = ft_atoll(argv[5]);
	config->num_compiles_required = (int)ft_atoll(argv[6]);
	config->dongle_cooldown = ft_atoll(argv[7]);
	if (!validate_nums(config))
		return (0);
	if (strcmp(argv[8], "fifo") == 0)
		config->scheduler = CX_SCHED_FIFO;
	else if (strcmp(argv[8], "edf") == 0)
		config->scheduler = CX_SCHED_EDF;
	else
	{
		write(2, "Error: Scheduler must be fifo or edf.\n", 38);
		return (0);
	}
	return (1);
}
