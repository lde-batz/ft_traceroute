/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traceroute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/20 16:13:14 by lde-batz          #+#    #+#             */
/*   Updated: 2020/08/21 23:22:56 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

void	wait_time(t_traceroute *tcrt, struct timeval *time_send)
{
	double			interval;
	struct timeval	time;

	interval = 0;
	if (time_send->tv_sec == 0)
		return ;
	while (interval < tcrt->sendwait)
	{
		gettimeofday(&time, NULL);
		interval = time.tv_sec - time_send->tv_sec;
		interval *= 1000000;
		interval += time.tv_usec - time_send->tv_usec;
	}
}

char	receive_pkt(t_traceroute *tcrt, int fd_recv, struct timeval *time_send)
{
	t_recv	recv;

	recv.tv.tv_sec = 2;
	recv.tv.tv_usec = 0;
	FD_ZERO(&recv.rfds);
	FD_SET(fd_recv, &recv.rfds);
	recv.ret_select = select(fd_recv + 1, &recv.rfds, NULL, NULL, &recv.tv);
	if (recv.ret_select < 0)
		exit_tcrt("Error select()", tcrt);
	else if (recv.ret_select == 0)
		printf(" *");
	else
	{
		recv.ip = (struct ip *)recv.buff_recv;
		recv.r_addr_len = sizeof(recv.r_addr);
		if (recvfrom(fd_recv, recv.buff_recv, 256, 0, (struct sockaddr *)
				&recv.r_addr, (socklen_t *)&recv.r_addr_len) <= 0)
			exit_tcrt("Error recvfrom", tcrt);
		recv.recv_pkt_host = inet_ntoa(recv.ip->ip_src);
		display_host(tcrt, &recv);
		display_recv(time_send);
		if (ft_strcmp(tcrt->host, recv.recv_pkt_host) == 0)
			return (1);
	}
	return (0);
}

int		loop_queries(t_traceroute *tcrt, int *fd_recv, int *queries,
										struct timeval *time_send)
{
	int finish;

	if (*queries == 1)
		printf("%i ", tcrt->ttl);
	wait_time(tcrt, time_send);
	gettimeofday(time_send, NULL);
	send_pkt(tcrt);
	finish = receive_pkt(tcrt, *fd_recv, time_send);
	tcrt->port++;
	return (finish);
}

void	traceroute(t_traceroute *tcrt)
{
	int				fd_recv;
	int				queries;
	char			finish;
	struct timeval	time_send;

	tcrt->ttl = tcrt->first_ttl;
	time_send.tv_sec = 0;
	display_first_line(tcrt);
	fd_recv = open_socket_receive(tcrt);
	finish = 0;
	while (!finish && tcrt->ttl <= tcrt->max_ttl)
	{
		queries = 0;
		ft_bzero(tcrt->host_tmp, sizeof(tcrt->host_tmp));
		while (queries++ < tcrt->nqueries)
			finish = loop_queries(tcrt, &fd_recv, &queries, &time_send);
		printf("\n");
		tcrt->ttl++;
	}
}
