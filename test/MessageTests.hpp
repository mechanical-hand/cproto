#include <cxxtest/TestSuite.h>
#include <cproto.hpp>
#include <type_traits>

class MessageTests : public CxxTest::TestSuite
{
public:
    void testMessageSize()
    {
        TS_ASSERT_EQUALS(sizeof(cproto::message), 256);
    }

    void testMessageIsPOD()
    {
        TS_ASSERT(std::is_pod<cproto::message>::value);
    }

    void testMessageLayout()
    {
        unsigned char data[] = {1,2,3};
        cproto::message msg;
        msg.size = 1;
        msg.checksum = 2;
        msg.buffer[0] = 3;
        TS_ASSERT_SAME_DATA(&msg, data, 3);
    }
};
