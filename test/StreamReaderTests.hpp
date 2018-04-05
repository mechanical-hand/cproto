#include <cxxtest/TestSuite.h>
#include <fake_arduino_stream.hpp>
#define ARDUINO 100
#include <cproto.hpp>
#include <cproto.cpp>

class StreamReaderTests : public CxxTest::TestSuite
{
    std::vector<unsigned char> m_stream_data;
    Stream* m_stream;
    cproto::arduino_stream_reader* m_reader;
public:
    void setUp()
    {

        unsigned char data[] = {3, 0, 102, 4, 0, 219, 2};
        m_stream_data = std::vector<unsigned char>(data, data + 7);

        m_stream = new Stream(m_stream_data);

        m_reader = new cproto::arduino_stream_reader(*m_stream);
    }

    void tearDown()
    {
        delete m_stream;
        delete m_reader;
    }

    void testData()
    {
        unsigned char data[] = {3, 0, 102, 4, 0, 219, 2};
        TS_ASSERT_SAME_DATA(data, m_stream_data.data(), m_stream_data.size());
        TS_ASSERT_SAME_DATA(data, m_stream->m_data.data(), m_stream->m_data.size());
    }

    void testAvailable()
    {
        TS_ASSERT(m_reader->available());
    }

    void testMessage()
    {
        auto msg = m_reader->read_message();
        TS_ASSERT_EQUALS(msg.size, 3);
        TS_ASSERT_EQUALS(msg.checksum, 0);
        TS_ASSERT_EQUALS(msg.buffer[0], 102);

        TS_ASSERT(m_reader->available());

        msg = m_reader->read_message();

        TS_ASSERT_EQUALS(msg.size, 4);
        TS_ASSERT_EQUALS(msg.checksum, 0);
        TS_ASSERT_EQUALS(msg.buffer[0], 219);
        TS_ASSERT_EQUALS(msg.buffer[1], 2);

        TS_ASSERT(!m_reader->available());
    }
};
