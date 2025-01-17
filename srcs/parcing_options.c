/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing_options.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/20 16:12:45 by lde-batz          #+#    #+#             */
/*   Updated: 2020/06/20 16:12:48 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

void	init_str_val_opt(t_traceroute *tcrt, int argc,
							char **argv, t_parcing *p)
{
	if (++p->i >= argc)
	{
		printf("Option `-%c' (argc %i) requires an argument", p->c, p->i - 1);
		if (p->c == 'f')
			printf(": `-f first_ttl'\n");
		else if (p->c == 'm')
			printf(": `-m max_ttl'\n");
		else if (p->c == 'q')
			printf(": `-q nqueries'\n");
		else if (p->c == 'm')
			printf(": `-z sendwait'\n");
		exit_tcrt(NULL, tcrt);
	}
	if (!(p->str_val_opt =
			(char *)malloc(sizeof(char) * (ft_strlen(argv[p->i] + 1)))))
		exit_tcrt("Error malloc()", tcrt);
	p->str_val_opt = ft_strcpy(p->str_val_opt, argv[p->i]);
}

void	parcing_option_f(t_traceroute *tcrt, int argc,
							char **argv, t_parcing *p)
{
	p->finish = 1;
	if (argv[p->i][p->j + 1])
	{
		if (!(p->str_val_opt = ft_strslice(argv[p->i], p->j)))
			exit_tcrt("Error malloc()", tcrt);
	}
	else
		init_str_val_opt(tcrt, argc, argv, p);
	if (!ft_atoi_strict(p->str_val_opt, &p->val_opt))
		exit_error_atof(tcrt, p, 'f');
	else if (p->val_opt > 0)
		tcrt->first_ttl = p->val_opt;
	else
	{
		printf("first hop out of range\n");
		free(p->str_val_opt);
		exit_tcrt(NULL, tcrt);
	}
	free(p->str_val_opt);
}

void	parcing_option_m(t_traceroute *tcrt, int argc,
							char **argv, t_parcing *p)
{
	p->finish = 1;
	if (argv[p->i][p->j + 1])
	{
		if (!(p->str_val_opt = ft_strslice(argv[p->i], p->j)))
			exit_tcrt("Error malloc()", tcrt);
	}
	else
		init_str_val_opt(tcrt, argc, argv, p);
	if (!ft_atoi_strict(p->str_val_opt, &p->val_opt))
		exit_error_atof(tcrt, p, 'm');
	else if (p->val_opt > 0 && p->val_opt < 256)
		tcrt->max_ttl = p->val_opt;
	else
	{
		if (p->val_opt == 0)
			printf("first hop out of range\n");
		else
			printf("max hops cannot be more than 255\n");
		free(p->str_val_opt);
		exit_tcrt(NULL, tcrt);
	}
	free(p->str_val_opt);
}

void	parcing_option_q(t_traceroute *tcrt, int argc,
							char **argv, t_parcing *p)
{
	p->finish = 1;
	if (argv[p->i][p->j + 1])
	{
		if (!(p->str_val_opt = ft_strslice(argv[p->i], p->j)))
			exit_tcrt("Error malloc()", tcrt);
	}
	else
		init_str_val_opt(tcrt, argc, argv, p);
	if (!ft_atoi_strict(p->str_val_opt, &p->val_opt))
		exit_error_atof(tcrt, p, 'q');
	else if (p->val_opt > 0 && p->val_opt <= 10)
		tcrt->nqueries = p->val_opt;
	else
	{
		printf("no more than 10 probes per hop\n");
		free(p->str_val_opt);
		exit_tcrt(NULL, tcrt);
	}
	free(p->str_val_opt);
}

void	parcing_option_z(t_traceroute *tcrt, int argc,
							char **argv, t_parcing *p)
{
	double val;

	val = 0;
	p->finish = 1;
	if (argv[p->i][p->j + 1])
	{
		if (!(p->str_val_opt = ft_strslice(argv[p->i], p->j)))
			exit_tcrt("Error malloc()", tcrt);
	}
	else
		init_str_val_opt(tcrt, argc, argv, p);
	if (!ft_atof_strict(p->str_val_opt, &val))
		exit_error_atof(tcrt, p, 'z');
	else if (val >= 10)
		tcrt->sendwait = val * 1000;
	else if (val >= 0)
		tcrt->sendwait = val * 1000000;
	else
	{
		printf("bad sendtime `%s' specified\n", p->str_val_opt);
		free(p->str_val_opt);
		exit_tcrt(NULL, tcrt);
	}
	free(p->str_val_opt);
}
