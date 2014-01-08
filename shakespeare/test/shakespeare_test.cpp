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
