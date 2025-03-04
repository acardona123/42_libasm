
#include "test_bonus.h"

static char	bases_ref[] = "0123456789abcdefghijklmnopqrstuvwxyz";
static int	max_number_of_whitespaces = 3;
static int	max_number_of_extra_signs = 3;
static int	max_number_of_extra_non_digits= 30;


static int _test_atoi_base_manual();
static int _test_valid_bases_16_10_8_random_numbers();
static int _test_atoi_invalid_bases();

int	test_atoi_base()
{
	int	error_cpt;

	logged_printf(true, "=== Tests of ft_atoi_base ===\n\n");

	error_cpt = 0;
	// error_cpt += _test_atoi_base_manual();
	error_cpt += _test_valid_bases_16_10_8_random_numbers();
	error_cpt += _test_atoi_invalid_bases();

	test_display_results(error_cpt);
	logged_printf(true, "--- End ---\n");
	return error_cpt;
}



// ======================================================

// 					MANUAL CUSTOMS TESTS

// ======================================================


static int _test_atoi_base_manual()
{
	char	base[] = "0123456789abcdef";
	char	src[] = "137448cd=B)i$<CT xR";
	int		expected_res = 326387917;
	int		obtained_res;

	logged_printf(true, "--- Manual test ---\n");
	obtained_res = ft_atoi_base(src, base);
	logged_printf(true, " base: \"%s\"\n str: \"%s\"\n expected result (manually entered): %d\n obtained result: %d\n=> %s\n\n", base, src, expected_res, obtained_res, expected_res == obtained_res ? "OK" : "KO");
	return expected_res != obtained_res;
}



// ======================================================

// 			TESTS OF CONVERSIONS ON VALID ARGUMENTS

// ======================================================




// ==== GET BASE ====

//generate a base compatible with the bases used by itoa. Used later for auto-generation of the string associated to an in
static void	_get_base(char *dst, int base_len)
{
	if ((base_len != 16 && base_len != 10 && base_len != 8))
	{
		logged_printf(true, "Warning: fail in _get_base, test aborted\n");
		*dst = 0;
		return;
	}
	strncpy(dst, bases_ref, base_len);
	dst[base_len] = 0;
}


// ==== TESTS ON VALID BASE 16, 10 or 8 ====

static int _test_base_multiple_random_numbers(int number_of_tests, int base_size);

static int _test_valid_bases_16_10_8_random_numbers()
{
	int	number_of_tests_each_base = 10;
	int	bases_tested[] = {16, 10, 8, 0};
	int	error_cpt;
	int	i;

	logged_printf(true, " --- Tests on valid bases and numbers ---\n");
	error_cpt = 0;
	i = 0;
	while (bases_tested[i])
		error_cpt += _test_base_multiple_random_numbers(number_of_tests_each_base, bases_tested[i++]);

	logged_printf(true, "Results on valid basis:\n");
	if (error_cpt)
		logged_printf(true, " Failure : error(s) in %d base%s among %d base%s tested\n\n", error_cpt, error_cpt > 1 ? "s" : "", i, i >1 ? "s" : "");
	else
		logged_printf(true, " Success\n\n");
	return error_cpt != 0;
}


static int	_test_base_one_random_number(char *base);

static int _test_base_multiple_random_numbers(int number_of_tests, int base_size)
{
	int		error;
	char	base[17];

	logged_printf(true, "- Test on %d numbers in base %d:\n", number_of_tests, base_size);
	if (base_size != 16 && base_size != 10 && base_size != 8)
	{
		logged_printf(true,  "Warning: incompatible base size for autotesting multiple random numbers. The base size must be 16, 10 or 8.\n");
		return 0;
	}

	srand(time(NULL));
	_get_base(base, base_size);
	if (!*base)
		return 0;

	error = 0;
	for (int i =0; i < number_of_tests; ++i)
		error += _test_base_one_random_number(base);

	if (!error)
		logged_printf(true, " => OK\n");
	else
		logged_printf(true, " => KO: %d / %d errors in the multiple random lists test\n", error, number_of_tests);
	return error != 0;
}


// ==== GENERAL TEST ON ANY NUMBER IN ATOI-COMPATIBLE BASE ====

static void _base_itoa_with_whitespaces_and_signs(char *dst, char *base, int num);
static int _check_and_display_atoi_base_results(int	expected_num, int atoi_base_result, char *num_str, char *base);

static int	_test_base_one_random_number(char *base)
{
	int		num;
	char	num_str[1024] = {};
	int		atoi_base_result;

	num = rand() - RAND_MAX / 2;
	_base_itoa_with_whitespaces_and_signs(num_str, base, num);
	atoi_base_result = ft_atoi_base(num_str, base);
	return _check_and_display_atoi_base_results(num, atoi_base_result, num_str, base);
}


// ==== STRING NUMBER CONSTRUCTION ====

//Construction of a char corresponding to a num in a given base (extracted from bases_ref for itoa compatibility)

static int _add_random_whitespaces_to_str(char *dst);
static int _add_random_signs_to_str(char *dst);
static int _add_num_conversion(char *dst, char *base, int num);
static int _add_random_non_digits_to_str(char *dst, char *base);

static void _base_itoa_with_whitespaces_and_signs(char *dst, char *base, int num)
{
	int		offset;

	offset = 0;
	offset += _add_random_whitespaces_to_str(dst);
	offset += _add_random_signs_to_str(dst + offset);
	offset += _add_num_conversion(dst + offset, base, num);
	_add_random_non_digits_to_str(dst + offset, base);
}


// --- Adding whitespaces at the beginning of str ---

static char	_get_random_whitespace();

static int _add_random_whitespaces_to_str(char *dst)
{
	int	number_of_ws;
	int	i;

	number_of_ws = rand() % max_number_of_whitespaces;
	i = 0;
	while (i < number_of_ws)
		dst [i++] = _get_random_whitespace();	
	return number_of_ws;
}

static char	_get_random_whitespace()
{
	static char whitespaces[] = " \f\n\r\t\v";
	static int	whitespaces_number = 6;

	return (whitespaces[rand()%whitespaces_number]);
}


// --- Adding + and - at the beginning of str without changing the result sign (even number of - ) ---

static char	_get_random_sign();

static int _add_random_signs_to_str(char *dst)
{
	int	number_of_signs;
	int	i;
	int sign_changed;

	number_of_signs = rand() % max_number_of_extra_signs;
	if (!number_of_signs)
		return 0;
	sign_changed = 0;
	i = 0;
	while (i < number_of_signs - 1)
	{
		dst [i] = _get_random_sign();	
		if (dst[i] == '-')
			sign_changed |= 1;
		++i;
	}
	dst[i] = sign_changed ? '-' : '+';
	return number_of_signs;
}
	
static char	_get_random_sign()
{
	return (rand() % 2 ? '+' : '-');
}


// --- Adding the num conversion to str ---

static int _add_num_conversion(char *dst, char *base, int num)
{
	size_t	base_len;

	base_len = strlen(base);
	if (base_len == 16)
		sprintf(dst, "%x", num);
	else if (base_len == 10)
		sprintf(dst, "%d", num);
	else if (base_len == 8)
		sprintf(dst, "%o", num);
	else
		*dst = 0;
	return ((int) strlen(dst));
}


// --- Adding non-digit chars at the end of str ---

static char	_get_random_non_digits(char *base);

static int _add_random_non_digits_to_str(char *dst, char *base)
{
	int	number_of_non_digits;
	int	i;

	number_of_non_digits = rand() % max_number_of_extra_non_digits;
	i = 0;
	while (i < number_of_non_digits)
		dst [i++] = _get_random_non_digits(base);	
	return number_of_non_digits;
}

static char	_get_random_non_digits(char *base)
{
	char c;

	c = *base;
	while (strchr(base, c))
		c = 1 + rand() % 127;
	return c;
}


// ==== RESULTS ANALYSIS ====

static int _check_and_display_atoi_base_results(int	expected_num, int atoi_base_result, char *num_str, char *base)
{
	if (expected_num == atoi_base_result)
	{
		logged_printf(false, "  Test OK:\n   base: base%ld = \"%s\"\n   src:  \"%s\"\n   expected result: %d\n   obtained result: %d\n", strlen(base), base, num_str, expected_num, atoi_base_result);
		return 0;
	}
	logged_printf(true, "  Test KO:\n   base: base%ld = \"%s\"\n   src:  \"%s\"\n   expected result: %d\n   obtained result: %d\n", strlen(base), base, num_str, expected_num, atoi_base_result);

	return 1;
}




// ======================================================

// 				TESTS INVALID BASE

// ======================================================


static int	_test_invalid_base_whitespaces();
static int	_test_invalid_base_signs();
static int	_test_invalid_base_duplicate_char();
static int	_test_invalid_base_too_small();

static int _test_atoi_invalid_bases()
{
	int	error_cpt;

	logged_printf(true, " --- Tests on invalid bases ---\n");
	error_cpt = 0;
	error_cpt += _test_invalid_base_whitespaces();
	error_cpt += _test_invalid_base_signs();
	error_cpt += _test_invalid_base_duplicate_char();
	error_cpt += _test_invalid_base_too_small();
	logged_printf(true, "Results on invalid basis:\n");
	if (error_cpt)
		logged_printf(true, " Failure : error(s) in %d invalid base%s\n\n", error_cpt, error_cpt > 1 ? "s" : "");
	else
		logged_printf(true, " Success\n\n");
	return error_cpt != 0;
}

static int	_test_one_invalid_base(char *base, char *description)
{
	int	res;

	logged_printf(false, " base tested: \"%s\" [description: %s]\n ->", base, description);
	res = ft_atoi_base("  ", base);
	if (!res)
	{
		logged_printf(false, " ok\n");
		return 0;
	}
	logged_printf(true, " ko:%s%s\n  base: %s\n  result expected: 0\n  result obtained: %d\n", description ? "\ndescription: " : "", description ? description : "", base, res);
	return 1;
}


static int	_test_base_ending_with_whitespace(char whitespace);

static int	_test_invalid_base_whitespaces()
{
	char	whitespaces[] = " \f\n\r\t\v";

	int		error;

	logged_printf(true, "- test of bases with whitespaces:\n");
	error = 0;
	for (int i = 0; whitespaces[i]; ++i)
		error += _test_base_ending_with_whitespace(whitespaces[i]);
	if (error)
	{
		logged_printf(true, " => KO: whitespace%s not detected/processed properly\n", error > 1 ? "s" : "");
		return 1;
	}
	logged_printf(true, " => OK\n");
	return error != 0;
}

static int	_test_base_ending_with_whitespace(char whitespace)
{
	char	base[] = {'a', 'b', whitespace, 0};
	char	description[50];

	sprintf(description, "whitespace %d present", whitespace);
	return _test_one_invalid_base(base, description);
}


static int	_test_base_ending_with_sign(char sign_char);

static int	_test_invalid_base_signs()
{
	int		error;

	logged_printf(true, "- test of bases with sign:\n");
	error = 0;
	error += _test_base_ending_with_sign('+');
	error += _test_base_ending_with_sign('-');
	if (error)
	{
		logged_printf(true, " => KO: sign%s not detected/processed properly\n", error > 1 ? "s" : "");
		return 1;
	}
	logged_printf(true, " => OK\n");
	return error != 0;
}

static int	_test_base_ending_with_sign(char sign_char)
{
	char	base[] = {'a', 'b', sign_char, 0};
	char	description[20];

	sprintf(description, "sign %c present", sign_char);
	return _test_one_invalid_base(base, description);
}


static int	_test_invalid_base_duplicate_char()
{
	char	base[] = {'a', 'b', 'c', 'b', 0};
	int		error;

	logged_printf(true, "- test of bases with duplicated char:\n =>");
	error = _test_one_invalid_base(base, NULL);
	if (!error)
		logged_printf(true, " OK\n");
	return error;
}


static int	_test_invalid_base_too_small()
{
	char	base[4] = {'a', 0};
	int		error;

	logged_printf(true, "- test of bases too small (size 1):\n =>");
	error = _test_one_invalid_base(base, NULL);
	if (!error)
		logged_printf(true, " OK\n");
	return error;
}


