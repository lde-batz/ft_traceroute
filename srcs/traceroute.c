#include "ft_traceroute.h"

void	wait_time(t_traceroute *tcrt, struct timeval *time_send)
{
	double			interval = 0;
	struct timeval	time;

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

char	*get_hostname_by_ip(struct in_addr ip)
{
	struct hostent *hostent;

	hostent = gethostbyaddr(&ip, sizeof(ip), AF_INET);
	if (hostent)
		return (hostent->h_name);
	return (inet_ntoa(ip));
}

char	receive_pkt(t_traceroute *tcrt, int fd_recv, struct timeval *time_send)
{
	int					ret_select;
	int					r_addr_len;
	char				buff_recv[256];
	char				*recv_pkt_host;
	char				*recv_pkt_hostname;

	fd_set				rfds;
	struct timeval		tv;
	struct ip			*ip;
	struct sockaddr_in	r_addr;

	tv.tv_sec = 2;
	tv.tv_usec = 0;
	FD_ZERO(&rfds);
	FD_SET(fd_recv, &rfds);
	ret_select = select(fd_recv + 1, &rfds, NULL, NULL, &tv);

	if (ret_select < 0)
		exit_tcrt("Error select()", tcrt);
	else if (ret_select == 0)
		printf(" *");
	else
	{
		ip = (struct ip *)buff_recv;
		r_addr_len = sizeof(r_addr);
		if (recvfrom(fd_recv, buff_recv, 256, 0,
				(struct sockaddr *)&r_addr, (socklen_t *)&r_addr_len) <= 0)
			exit_tcrt("Error recvfrom", tcrt);
		recv_pkt_host = inet_ntoa(ip->ip_src);
		if (strcmp(tcrt->host_tmp, recv_pkt_host) != 0)
		{
			ft_strcpy(tcrt->host_tmp, recv_pkt_host);
			if (tcrt->opt_n)
				printf(" %s", recv_pkt_host);
			else
			{
				recv_pkt_hostname = get_hostname_by_ip(ip->ip_src);
				printf(" %s (%s)", recv_pkt_hostname, recv_pkt_host);
			}
		}
		display_recv(time_send);
		if (ft_strcmp(tcrt->host, recv_pkt_host) == 0)
			return (1);
	}
	return (0);
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
		{
			if (queries == 1)
				printf("%i ", tcrt->ttl);
			wait_time(tcrt, &time_send);
			gettimeofday(&time_send, NULL);
			send_pkt(tcrt);
			
			finish = receive_pkt(tcrt, fd_recv, &time_send);
			tcrt->port++;
		}
		putchar('\n');
		tcrt->ttl++;
	}
}
