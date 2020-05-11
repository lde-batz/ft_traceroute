#ifndef FT_PING_H
# define FT_PING_H

# include "libft.h"

# include <stdio.h>				// printf()
# include <sys/types.h>			// socket()
# include <sys/socket.h>		// socket()
# include <netinet/in.h>		// inet_ntoa()
# include <arpa/inet.h>			// inet_pton()
# include <netinet/udp.h>		// struct udphdr
# include <netinet/ip.h>		// struct iphdr
# include <netinet/ip_icmp.h>	// struct icmphdr
# include <unistd.h>			// select()
# include <sys/time.h>			// gettimeofday()
# include <netdb.h>				// getaddrinfo()

# define TCRT_PKT_LEN 40

typedef struct s_parcing
{
	int		i;
	int		j;
	int		val_opt;
	char	c;
	char	finish;
	char	*str_val_opt;
	char	*bad_opt;
}				t_parcing;

typedef struct	s_tcrt_pkt
{
	struct icmphdr	hdr;
	char			msg[TCRT_PKT_LEN - sizeof(struct udphdr)];
}				t_tcrt_pkt;

typedef struct s_traceroute
{
	char		*hostname;
	char		*host;
	char		*host_tmp;

	struct addrinfo hints;
	struct addrinfo *res;

	int				first_ttl;
	int				max_ttl;
	char			opt_n;
	int				nqueries;
	int				sendwait;

	int				port;
	int				ttl;
}				t_traceroute;

/*   parcing.c   */
void			parcing(t_traceroute *tcrt, int argc, char **argv);

/*   parcing_options.c   */
void			parcing_option_f(t_traceroute *tcrt, int argc, char **argv, t_parcing *p);
void			parcing_option_m(t_traceroute *tcrt, int argc, char **argv, t_parcing *p);
void			parcing_option_q(t_traceroute *tcrt, int argc, char **argv, t_parcing *p);
void			parcing_option_z(t_traceroute *tcrt, int argc, char **argv, t_parcing *p);

/*   traceroute.c   */
void			traceroute(t_traceroute *tcrt);

/*   socket.c   */
int				open_socket_receive(t_traceroute *tcrt);
void			send_pkt(t_traceroute *tcrt);

/*   display.c   */
void			display_first_line(t_traceroute *tcrt);
void			display_recv(struct timeval *time_send);

/*   help.c   */
void			exit_help(char *msg);
void			exit_error_atof(t_traceroute *tcrt, t_parcing *p, char opt);
void			exit_tcrt(char *msg, t_traceroute *tcrt);

/*   tools.c   */
char			*ft_strslice(char *str, int slice);
int				*ft_atoi_strict(char *str, int *nb);
double			*ft_atof_strict(char *str, double *nb);



#endif