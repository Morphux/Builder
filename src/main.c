/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhezard <jhezard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/21 17:04:29 by jhezard           #+#    #+#             */
/*   Updated: 2017/01/21 17:09:56 by jhezard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <morphux.h>

int main(int ac, const char *av[]) {
	(void)ac;
	(void)av;
	set_program_name(NAME);
	set_version(VERSION);
	set_maintainer(MAINTAINER);
	return 0;
}
