/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhezard <jhezard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/21 19:21:05 by jhezard           #+#    #+#             */
/*   Updated: 2017/01/21 19:30:05 by jhezard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARGS_H
# define ARGS_H

typedef struct		s_opts {
	bool			verbose;
	bool			detach;
	bool			quiet;
	u32_t			port;
	char			*pid_file;
}					opts_t;


#endif /* ARGS_H */
