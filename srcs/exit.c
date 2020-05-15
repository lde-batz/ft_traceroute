#include "ft_traceroute.h"

void	exit_help(char *msg)
{
	if (msg)
		printf("%s\n", msg);
	printf("Usage:\n");
	printf("  traceroute [ -hn ] [ -f first_ttl ] [ -m max_ttl]");
	printf(" [ -q nqueries ] [ -z sendwait ] host\n");
	printf("Options:\n");
	printf("  -f first_ttl          Start from the fisrt_ttl hop (instead from 1)\n");
	printf("  -h                    Read this help and exit\n");
	printf("  -m max_ttl            Set the max number of hops (max TTL to be\n");
	printf("                        reached). Default is 30\n");
	printf("  -n                    Do not resolve IP addresses to their domain names\n");
	printf("  -q nqueries           Set the number of probes per each hop. Default is\n");
	printf("                        3\n");
	printf("  -z sendwait           Minimal time interval between probes (default 0).\n");
	printf("                        If the value is more than 10, then it specifies a\n");
	printf("                        number in milliseconds, else it is a number of\n");
	printf("                        seconds (float point values allowed too)\n");
	exit(EXIT_SUCCESS);
}

void	exit_error_atof(t_traceroute *tcrt, t_parcing *p, char opt)
{
	printf("Cannot handle `-%c' option with arg `%s' (argc %i)\n", opt, p->str_val_opt, p->i);
	free(p->str_val_opt);
	exit_tcrt(NULL, tcrt);
}

void	exit_tcrt(char *msg, t_traceroute *tcrt)
{
	if (msg)
		perror(msg);
	if (tcrt->host)
		free(tcrt->host);
	if (tcrt->host_tmp)
		free(tcrt->host_tmp);
	exit(EXIT_FAILURE);
}
