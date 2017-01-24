#include "test.h"

TEST(main) {
	int			st, fd[2];
	pid_t		pid;

	pipe(fd);
	if ((pid = fork()) == 0) {
		DUP_ALL_OUTPUTS(fd);
		execl(BIN, BIN, "--help", NULL);
		exit(1);
	} else {
		WAIT_AND_CLOSE(pid, st, fd);
	}
	return TEST_SUCCESS;
}

TEST(main2) {
	int			st, fd[2];
	pid_t		pid;

	pipe(fd);
	if ((pid = fork()) == 0) {
		DUP_ALL_OUTPUTS(fd);
		execl(BIN, BIN, NULL);
		exit(1);
	} else {
		WAIT_AND_CLOSE(pid, st, fd);
	}
	return TEST_SUCCESS;

}


int		main(void) {
	u32_t	ret;

	reg_test("main", main);
	reg_test("main", main2);

	m_info("Beginning tests...\n");
	ret = test_all();
	test_free();

	return ret;
}
