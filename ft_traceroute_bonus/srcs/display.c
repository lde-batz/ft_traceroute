/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/20 16:11:51 by lde-batz          #+#    #+#             */
/*   Updated: 2020/08/22 11:33:05 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

void	display_first_line(t_traceroute *tcrt)
{
	printf("traceroute to %s (%s), %i hops max, 60 byte packets\n",
			tcrt->hostname, tcrt->host, tcrt->max_ttl);
}

void	display_host(t_traceroute *tcrt, t_recv *recv)
{
	if (ft_strcmp(tcrt->host_tmp, recv->recv_pkt_host) != 0)
	{
		ft_strcpy(tcrt->host_tmp, recv->recv_pkt_host);
		if (tcrt->opt_n)
			printf(" %s", recv->recv_pkt_host);
		else
		{
			recv->recv_pkt_hostname = get_hostname_by_ip(recv->ip->ip_src);
			printf(" %s (%s)", recv->recv_pkt_hostname, recv->recv_pkt_host);
		}
	}
}

void	display_recv(struct timeval *time_send)
{
	double			interval;
	struct timeval	time;

	gettimeofday(&time, NULL);
	interval = time.tv_sec - time_send->tv_sec;
	interval *= 1000000;
	interval += time.tv_usec - time_send->tv_usec;
	interval /= 1000;
	printf("  %.3f ms", interval);
}
