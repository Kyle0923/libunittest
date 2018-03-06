/*************************************************
 *
 *      Kyle
 *      2018/Mar/5
 *
 * This header contains macro definitions
 * and assert functions for C unit test
 ************************************************/
#ifndef KYLE_UNITTEST_H_
#define KYLE_UNITTEST_H_

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#define FILENAME (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)

#define TEST(name)	\
void name();\
__attribute__((constructor(101 + __COUNTER__))) static void insert_function_ptr_##name(void) { \
    insert_function_ptr(&name);\
} \
void name()

/** Equal **/
#define EXPECT_EQ(expect, actual)   \
                myAssert(expect, actual, &equal, __LINE__ , __func__, FILENAME)
/** Not Equal **/
#define EXPECT_NE(expect, actual)   \
                myAssert(expect, actual, &not_equal, __LINE__ , __func__, FILENAME)
/** Greater Than **/
#define EXPECT_GT(expect, actual)   \
                myAssert(expect, actual, &greater, __LINE__ , __func__, FILENAME)
/** Greater than or equal to **/
#define EXPECT_GE(expect, actual)   \
                myAssert(expect, actual, &greater_equal, __LINE__ , __func__, FILENAME)
/** Less Than**/
#define EXPECT_LT(expect, actual)   \
                myAssert(expect, actual, &less, __LINE__ , __func__, FILENAME)
/** Less than or equal to **/
#define EXPECT_LE(expect, actual)   \
                myAssert(expect, actual, &less_equal, __LINE__ , __func__, FILENAME)

#define RUN_ALL_TEST() 		\
do {\
    int ctr = 0; \
    for (; ctr < num_test; ctr++) { \
        test_func_array[ctr](); \
    } \
    printf("\n## Total tests = %d, Failed = %d\n", num_test, failed);\
} while(0)

typedef int64_t VALUE_TYPE;

typedef void (*funptr_t)();
typedef int (*COMPARE)(VALUE_TYPE, VALUE_TYPE);
extern int num_test;
extern int failed;
extern funptr_t* test_func_array;
extern void myAssert(int64_t, int64_t, COMPARE, int, const char*, const char*);
extern void insert_function_ptr(funptr_t pFun);

// compare functions
#define DECL_COMP_FUNC(func_name)           int func_name(VALUE_TYPE, VALUE_TYPE);
DECL_COMP_FUNC(equal)
DECL_COMP_FUNC(not_equal)
DECL_COMP_FUNC(greater)
DECL_COMP_FUNC(greater_equal)
DECL_COMP_FUNC(less)
DECL_COMP_FUNC(less_equal)
#undef DECL_COMP_FUNC

#endif /* KYLE_UNITTEST_H_ */
