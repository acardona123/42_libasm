void test_strlen();
void test_strcmp();
void test_strcpy();
void test_write();
void test_read(int test_std_in);
void test_strdup();

int main()
{
	test_strlen();
	test_strcmp();
	test_strcpy();
	test_write();
	test_read(0);
	test_strdup();
	return 0;
}
