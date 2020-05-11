#include "ft_traceroute.h"

void	display_first_line(t_traceroute *tcrt)
{
	printf("traceroute to %s (%s), %i hops max, 60 byte packets\n",
			tcrt->hostname, tcrt->host, tcrt->max_ttl);
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
