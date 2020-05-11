#include "ft_traceroute.h"

int		open_socket_receive(t_traceroute *tcrt)
{
	int fd;

	if ((fd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) < 0)
		exit_tcrt("Error socket()", tcrt);
	return (fd);
}

void	send_pkt(t_traceroute *tcrt)
{
	int		fd;
	int		i;
	char	msg[32];
	char	*port;

	ft_bzero(&tcrt->hints, sizeof(tcrt->hints));
	tcrt->hints.ai_family = AF_INET;
	tcrt->hints.ai_socktype = SOCK_DGRAM;
	tcrt->hints.ai_protocol = IPPROTO_UDP;

	port = ft_itoa(tcrt->port);
	if (getaddrinfo(tcrt->host, port, &tcrt->hints, &tcrt->res) < 0)
		exit_tcrt("Error getaddrinfo()", tcrt);

	fd = socket(tcrt->res->ai_family, tcrt->res->ai_socktype, tcrt->res->ai_protocol);
	if (fd < 0)
		exit_tcrt("Error socket()", tcrt);
	if (setsockopt(fd, IPPROTO_IP, IP_TTL, &tcrt->ttl, sizeof(tcrt->ttl)) != 0)
		exit_tcrt("Error setsockopt()", tcrt);

	i = 0;
	while ((unsigned long)i++ < sizeof(msg) - 1)
		msg[i] = i + '0';
	msg[i] = 0;

	if (sendto(fd, msg, sizeof(msg), 0,
				tcrt->res->ai_addr, tcrt->res->ai_addrlen) < 0)
		exit_tcrt("Error sendto()", tcrt);
	close(fd);
	freeaddrinfo(tcrt->res);
	free(port);
}
