#include "gtest/gtest.h"
#include "../inc/shakespeare.h"

class Shakespeare_Test : public ::testing::Test
{
    protected:
    virtual void SetUp() { }

};

// Some test 
TEST_F(Shakespeare_Test, SomeTest)
{
    ASSERT_EQ(
        'a', // expected
        'b'  // actual
    ); 
}

// Some test 
TEST_F(Shakespeare_Test, CatchBadFilepath)
{    
    FILE *test_log;
    test_log = fopen(get_filename("./test folder","TestProcess",".log").c_str(),"a");
    ASSERT_EQ(
        'a', // expected
        'b'  // actual
    ); 
}

// Some test 
TEST_F(Shakespeare_Test, GetCustomTimeTest)
{
    ASSERT_EQ(
        'a', // expected
        'b'  // actual
    ); 
}
