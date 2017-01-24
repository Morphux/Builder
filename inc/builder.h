/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builder.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhezard <jhezard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/21 17:43:23 by jhezard           #+#    #+#             */
/*   Updated: 2017/01/21 19:30:53 by jhezard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILDER_H
# define BUILDER_H

#ifndef NAME
# define NAME "builder_coverage"
#endif

#ifndef VERSION
# define VERSION "coverage"
#endif

#ifndef MAINTAINER
# define MAINTAINER "morphux@morphux.org"
#endif

# define PID_FILE "/var/run/"NAME".pid"
# define LOG_FILE "/var/log/"NAME".log"

# include <morphux.h>
# include <args.h>

#endif /* BUILDER_H */
