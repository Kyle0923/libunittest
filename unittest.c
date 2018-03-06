/*************************************************
 *
 *      Kyle
 *      2018/Mar/5
 *
 * This header contains macro definitions
 * and assert functions for C unit test
 ************************************************/
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "unittest.h"

funptr_t* test_func_array = NULL;
int num_test = 0;
int failed = 0;

void myAssert(VALUE_TYPE expected, VALUE_TYPE actual, COMPARE compare, int lineNum, const char* description, const char* fileName) {
	printf("[%s]\n", description);
	if (compare(expected, actual)) {
		printf(">>>passed\n");
	} else {
	    failed++;
		printf(">>>failed\n>>>%s Line[%d]: expected [%ld] : actual [%ld]\n", fileName, lineNum, expected, actual);
	}
}

void insert_function_ptr(funptr_t pFun) {
    funptr_t* temp_ptr = test_func_array;
	num_test++;
	test_func_array = calloc(num_test, sizeof(funptr_t));
	if (test_func_array == NULL) {
		exit(-1);
	}
	memcpy(test_func_array, temp_ptr, (num_test - 1) * sizeof(funptr_t));
	test_func_array[num_test - 1] = pFun;
	free(temp_ptr);
}

__attribute__((destructor)) static void memory_clean_up(void) {
    free(test_func_array);
}

#define DEFINE_COMP_FUNC(func_name)           int func_name(VALUE_TYPE exp, VALUE_TYPE actual)
DEFINE_COMP_FUNC(equal) {
    return (exp == actual);
}

DEFINE_COMP_FUNC(not_equal) {
    return (exp != actual);
}

DEFINE_COMP_FUNC(greater) {
    return (exp > actual);
}

DEFINE_COMP_FUNC(greater_equal) {
    return (exp >= actual);
}

DEFINE_COMP_FUNC(less) {
    return (exp < actual);
}

DEFINE_COMP_FUNC(less_equal) {
    return (exp <= actual);
}

#undef DEFINE_COMP_FUNC


