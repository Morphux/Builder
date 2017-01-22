#include <morphux.h>

TEST(main) {
	int		i = 1;

	TEST_ASSERT(i == 1, "Nope");
	return TEST_SUCCESS;
}

int		main(void) {
	u32_t	ret;

	reg_test("main", main);

	m_info("Beginning tests...\n");
	ret = test_all();
	test_free();

	return ret;
}
