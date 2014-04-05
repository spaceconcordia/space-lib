#include "gtest/gtest.h"
#include "../inc/fletcher.h"

class Fletcher_Test : public ::testing::Test
{
    protected:
    virtual void SetUp() { }

    size_t z; // assert loop index
};

// will be tested in following tests, but isolate some 
// test null bytes, passing wrong length, etc

/**
 * Kevin Brown's Fletcher checksum, use to compare to ours
 */
struct fletcher_checksum
fletcher_KBPayloadChecksum (unsigned char *data, size_t size)
{
    size_t i = 0;
    uint8_t ck_a = 0;
    uint8_t ck_b = 0;

    for( i = 0; i < size; i++ )
    {
        ck_a += data[i];
        ck_b += ck_a;
    }

    fletcher_checksum r;
        
    r.sum1 = ck_a;
    r.sum2 = ck_b;

    return r;
}

// Test the various bitshifting operations occuring in the library
/*
TEST_F(Fletcher_Test, GoodBits)
{
    fletcher_fastSetPA (int fdin, int power_level);
    ASSERT_EQ(
               
    );
}
*/

/*
// Test the fletcher checksum
// NOTE: reality on the fletcher is subjective and strange
//EXPECTED http://www.lammertbies.nl/comm/info/crc-calculation.html
TEST_F(Fletcher_Test, FletcherChecksum)
{

    // unsigned char *checksum_bytes[97] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcedefghjklmnopqrstuvwxyz~!@#$%^&*()_+`1234567890-={}\\|:\"<>?[];',./";
    
    //ACTUAL
    unsigned char checksum_bytes[56] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcedefghjklmnopqrstuvwxyz~!@";
    fletcher_checksum checksum_result = fletcher_checksum16(checksum_bytes,56);
    
    fletcher_checksum expected_result;
    expected_result.sum1 = 0x27;
    expected_result.sum2 = 0xD3;

    ASSERT_EQ(
        checksum_result.sum1,
        expected_result.sum1 
    ); 
    ASSERT_EQ(
        checksum_result.sum2,
        expected_result.sum2
    );
}
*/

// Compare our fletcher algorithm with Kevin Brown's
TEST_F(Fletcher_Test, BrownVsWorld)
{
    unsigned char checksum_bytes[56] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcedefghjklmnopqrstuvwxyz~!@";
    fletcher_checksum our_result = fletcher_checksum16(checksum_bytes,56);
    fletcher_checksum his_result = fletcher_KBPayloadChecksum(checksum_bytes,56);
    
    ASSERT_EQ(
        his_result.sum1,
        our_result.sum1
    ); 
    ASSERT_EQ(
        his_result.sum2,
        our_result.sum2
    );  
}

// test against sample checksum calculated by the transceiver. This is not reliable, likely to change due to firmware issues on the board
TEST_F(Fletcher_Test, TestIncomingChecksum)
{
    unsigned char checksum_bytes[33] = {0x20,0x04,0x00,0x00,0x1a,0x3e,0xa6,0x86,0xa2,0x40,0x40,0x40,0x40,0x60,0xac,0x8a,0x64,0x86,0xaa,0x82,0xe1,0x03,0xf0,0x6b,0x65,0x6e,0x77,0x6f,0x6f,0x64,0x0d,0x8d,0x08};
    fletcher_checksum actual_result = fletcher_checksum16(checksum_bytes,33);
    
    ASSERT_EQ(
        0x63,
        actual_result.sum1
    ); 
    ASSERT_EQ(
        0x9f,
        actual_result.sum2
    );  
}
