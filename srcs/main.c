/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/20 16:12:17 by lde-batz          #+#    #+#             */
/*   Updated: 2020/06/20 16:12:27 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

void	check_root(void)
{
	if (getuid() != 0)
	{
		printf("Error user: only root is permitted\n");
		exit(EXIT_FAILURE);
	}
}

void	init_traceroute(t_traceroute *tcrt)
{
	ft_bzero(tcrt, sizeof(tcrt));
	tcrt->hostname = NULL;
	tcrt->host = NULL;
	if (!(tcrt->host_tmp = (char *)malloc(sizeof(char) * 16)))
		exit_tcrt("Error malloc()", tcrt);
	tcrt->first_ttl = 1;
	tcrt->max_ttl = 30;
	tcrt->opt_n = 0;
	tcrt->nqueries = 3;
	tcrt->sendwait = 0;
	tcrt->port = 33434;
}

int		main(int argc, char **argv)
{
	t_traceroute	tcrt;

	if (argc <= 1)
		exit_help(NULL);
	else
	{
		check_root();
		init_traceroute(&tcrt);
		parcing(&tcrt, argc, argv);
	}
	traceroute(&tcrt);
	exit_tcrt(NULL, &tcrt);
	return (0);
}
