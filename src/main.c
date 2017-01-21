/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhezard <jhezard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/21 17:04:29 by jhezard           #+#    #+#             */
/*   Updated: 2017/01/21 18:04:29 by jhezard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <builder.h>

void	force(const char *str) {
	m_info("%s\n", str);
}

int		list_opt_free(void *tofree) {
	opts_t		*tmp = tofree;
	if (tofree)
		free(tmp->str);
	return 0;
}

int		main(int ac, char *av[]) {
	margs_t		opts[] = {
		{'f', "force", "Do not launch the program as a daemon.", false, &force},
		ARGS_EOL
	};
	opts_t		*opts2;
	opts_t		*opts_tmp = NULL;
	mlist_t		*opt_lst = NULL;
	mlist_t		*tmp_lst = NULL;

	set_program_name(NAME);
	set_version(VERSION);
	set_maintainer(MAINTAINER);
	read_opt(ac, av, opts);

	opts2 = malloc(sizeof(opts_t));

	opts2->force = true;
	opts2->str = strdup("toto");
	list_add(opt_lst, &opts2, sizeof(opts2));
	free(opts2);

	m_info("lstsize : %d\n", list_size(opt_lst));

	list_for_each(opt_lst, tmp_lst, opts_tmp) {
		m_info("bool : %d|%s\n", opts_tmp->force, opts_tmp->str);
	}
	list_free(opt_lst, &list_opt_free);
	return 0;
}
