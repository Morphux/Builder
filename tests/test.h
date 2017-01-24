#ifndef TEST_H
# define TEST_H

# include <morphux.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>

# define DUP_ALL_OUTPUTS(name) dup2(name[1], 1); dup2(name[1], 2); close(name[1]);
# define WAIT_AND_CLOSE(pid, status, fd) pid = waitpid(pid, &status, 0); close(fd[1]);

# define BIN "../builder"

#endif /* TEST_H */
