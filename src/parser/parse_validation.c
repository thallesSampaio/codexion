/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thasampa <thasampa@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 15:56:11 by thasampa          #+#    #+#             */
/*   Updated: 2026/07/29 15:56:17 by thasampa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	parse_numeric_args(char **argv, t_config *config)
{
	if (!parse_positive_int(argv[1], &config->num_coders))
		return (0);
	if (!parse_positive_ll(argv[2], &config->time_to_burnout))
		return (0);
	if (!parse_positive_ll(argv[3], &config->time_to_compile))
		return (0);
	if (!parse_positive_ll(argv[4], &config->time_to_debug))
		return (0);
	if (!parse_positive_ll(argv[5], &config->time_to_refactor))
		return (0);
	if (!parse_positive_int(argv[6], &config->num_compiles_required))
		return (0);
	if (!parse_positive_ll(argv[7], &config->dongle_cooldown))
		return (0);
	return (1);
}

int	validate_numeric_values(t_config *config)
{
	if (config->num_coders <= 0)
		return (0);
	if (config->time_to_burnout <= 0)
		return (0);
	if (config->num_compiles_required <= 0)
		return (0);
	return (1);
}

int	parse_scheduler(const char *str, t_sched *scheduler)
{
	if (strcmp(str, "fifo") == 0)
		*scheduler = CX_SCHED_FIFO;
	else if (strcmp(str, "edf") == 0)
		*scheduler = CX_SCHED_EDF;
	else
		return (0);
	return (1);
}

void	print_parser_error(void)
{
	write(2, "Error: invalid arguments\n", 25);
}
