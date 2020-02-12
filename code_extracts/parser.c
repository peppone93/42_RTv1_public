/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apula <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 23:54:01 by apula             #+#    #+#             */
/*   Updated: 2019/06/28 02:22:32 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static char	*clean_first_spaces(char *str)
{
	unsigned int	i;
	unsigned int	j;
	int				stop;
	char			*all;

	i = ft_strlen(str);
	if (!(all = (char*)malloc(sizeof(char) * (i + 1))))
		error(2);
	i = 0;
	j = 0;
	stop = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ':')
			stop = 1;
		if (str[i] == '\n')
			stop = 0;
		while (str[i] && (str[i] == ' ' || str[i] == '\t') && stop == 0)
			i++;
		all[j++] = str[i++];
	}
	all[j] = '\0';
	ft_strdel(&str);
	return (all);
}

static char	*clean_newlines(char *str)
{
	int		i;
	int		j;
	char	*all;

	i = ft_strlen(str);
	if (!(all = (char*)malloc(sizeof(char) * (i + 1))))
		error(2);
	j = 0;
	i = 0;
	while (str[i] != '\0')
	{
		while (str[i] != '\0' && str[i] == '\n' && str[i + 1] == '\n')
			i++;
		all[j] = str[i];
		i++;
		j++;
	}
	all[j] = '\0';
	ft_strdel(&str);
	return (all);
}

static void	check_brackets(char *str)
{
	int i;
	int op;
	int cl;

	i = -1;
	op = 0;
	cl = 0;
	while (str[++i] != 0)
	{
		if (str[i] == '{')
			op++;
		if (str[i] == '}')
			cl++;
	}
	if (op != cl)
		error(1);
}

static void	check_clean(t_scene *s, char *st)
{
	char	**blocks;
	char	*all;

	(void)st;
	all = clean_first_spaces(st);
	all = clean_newlines(all);
	check_brackets(all);
	blocks = block_to_blocks(all);
	differentiate_blocks(s, blocks);
	check_collected_data(s);
}

void		parse(t_scene *s, char *av)
{
	int		fd;
	int		rd;
	char	*all;
	char	*str;
	char	*st;

	if ((fd = open(av, O_RDONLY)) < 0)
		error(1);
	if (!(str = (char*)malloc(sizeof(char) * (MAXL + 1))))
		error(2);
	st = ft_strjoin("", "\0");
	rd = MAXL;
	while (rd == MAXL)
	{
		if ((rd = read(fd, str, MAXL)) == -1 || str[0] == '\0')
			error(1);
		str[rd] = '\0';
		all = st;
		st = ft_strjoin(st, str);
		ft_strdel(&all);
	}
	ft_strdel(&str);
	check_clean(s, st);
}
