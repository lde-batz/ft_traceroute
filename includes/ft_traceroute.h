#ifndef FT_TRACEROUTE_H
# define FT_TRACEROUTE_H

# include "libft.h"

# include <stdio.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <netinet/udp.h>
# include <netinet/ip.h>
# include <netinet/ip_icmp.h>
# include <unistd.h>
# include <sys/time.h>
# include <netdb.h>

# define TCRT_PKT_LEN 40

typedef struct	s_parcing
{
	int		i;
	int		j;
	int		val_opt;
	char	c;
	char	finish;
	char	*str_val_opt;
	char	*bad_opt;
}				t_parcing;

typedef struct	s_recv
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
}				t_recv;

typedef struct	s_tcrt_pkt
{
	struct icmphdr	hdr;
	char			msg[TCRT_PKT_LEN - sizeof(struct udphdr)];
}				t_tcrt_pkt;

typedef struct	s_traceroute
{
	char			*hostname;
	char			*host;
	char			*host_tmp;

	struct addrinfo	hints;
	struct addrinfo	*res;

	int				first_ttl;
	int				max_ttl;
	char			opt_n;
	int				nqueries;
	int				sendwait;

	int				port;
	int				ttl;
}				t_traceroute;

void			parcing(t_traceroute *tcrt, int argc, char **argv);

void			parcing_option_f(t_traceroute *tcrt, int argc,
									char **argv, t_parcing *p);
void			parcing_option_m(t_traceroute *tcrt, int argc,
									char **argv, t_parcing *p);
void			parcing_option_q(t_traceroute *tcrt, int argc,
									char **argv, t_parcing *p);
void			parcing_option_z(t_traceroute *tcrt, int argc,
									char **argv, t_parcing *p);

void			traceroute(t_traceroute *tcrt);
char			*get_hostname_by_ip(struct in_addr ip);

int				open_socket_receive(t_traceroute *tcrt);
void			send_pkt(t_traceroute *tcrt);

void			display_first_line(t_traceroute *tcrt);
void			display_host(t_traceroute *tcrt, t_recv *recv);
void			display_recv(struct timeval *time_send);

void			exit_help(char *msg);
void			exit_error_atof(t_traceroute *tcrt, t_parcing *p, char opt);
void			exit_tcrt(char *msg, t_traceroute *tcrt);

char			*ft_strslice(char *str, int slice);
int				*ft_atoi_strict(char *str, int *nb);
double			*ft_atof_strict(char *str, double *nb);

#endif
