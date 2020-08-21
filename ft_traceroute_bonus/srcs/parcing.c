/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/20 16:12:34 by lde-batz          #+#    #+#             */
/*   Updated: 2020/06/20 16:12:40 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

void	get_ip_by_hostname(t_traceroute *tcrt)
{
	char				*host;
	struct addrinfo		hints;
	struct addrinfo		*res;
	struct sockaddr_in	*host_sockaddr;

	ft_memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	if (getaddrinfo(tcrt->hostname, NULL, &hints, &res) != 0)
		exit_tcrt("Error getaddrinfo()", tcrt);
	host_sockaddr = (struct sockaddr_in *)res->ai_addr;
	host = inet_ntoa(host_sockaddr->sin_addr);
	tcrt->host = ft_strdup(host);
	freeaddrinfo(res);
}

void	parcing_bad_opt(t_traceroute *tcrt, char **argv, t_parcing *p)
{
	if (!(p->bad_opt = ft_strslice(argv[p->i], p->j - 1)))
		exit_tcrt("Error malloc()", tcrt);
	printf("Bad option '-%s' (argc %i)\n", p->bad_opt, p->i);
	free(p->bad_opt);
	exit_tcrt(NULL, tcrt);
}

void	parsing_option(t_traceroute *tcrt, int argc, char **argv, t_parcing *p)
{
	p->val_opt = 1;
	p->j = 0;
	p->finish = 0;
	while (!p->finish && argv[p->i][++p->j])
	{
		p->c = argv[p->i][p->j];
		if (p->c == 'f')
			parcing_option_f(tcrt, argc, argv, p);
		else if (p->c == 'h')
			exit_help(NULL);
		else if (p->c == 'm')
			parcing_option_m(tcrt, argc, argv, p);
		else if (p->c == 'n')
			tcrt->opt_n = 1;
		else if (p->c == 'q')
			parcing_option_q(tcrt, argc, argv, p);
		else if (p->c == 'z')
			parcing_option_z(tcrt, argc, argv, p);
		else
			parcing_bad_opt(tcrt, argv, p);
	}
}

void	parcing(t_traceroute *tcrt, int argc, char **argv)
{
	t_parcing	p;

	ft_bzero(&p, sizeof(p));
	while (++p.i < argc)
	{
		if (argv[p.i][0] == '-')
			parsing_option(tcrt, argc, argv, &p);
		else if (tcrt->hostname == NULL)
			tcrt->hostname = argv[p.i];
		else
			exit_help("Error! Only one host");
	}
	if (tcrt->hostname == NULL)
	{
		printf("Specify \"host\" missing argument.\n");
		exit_tcrt(NULL, tcrt);
	}
	get_ip_by_hostname(tcrt);
}
