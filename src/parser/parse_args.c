/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thasampa <thasampa@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 15:56:33 by thasampa          #+#    #+#             */
/*   Updated: 2026/07/29 15:56:37 by thasampa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	parse_args(int argc, char **argv, t_config *config)
{
	if (argc != 9)
	{
		print_parser_error();
		return (0);
	}
	if (!parse_numeric_args(argv, config))
	{
		print_parser_error();
		return (0);
	}
	if (!validate_numeric_values(config))
	{
		print_parser_error();
		return (0);
	}
	if (!parse_scheduler(argv[8], &config->scheduler))
	{
		print_parser_error();
		return (0);
	}
	return (1);
}
