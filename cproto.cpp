#include <cproto.hpp>

using namespace cproto;

#ifdef ARDUINO

    arduino_stream_reader::arduino_stream_reader(Stream& s) : m_stream(s){}

    bool arduino_stream_reader::available()
    {
        if(!m_stream.available()) return false;

        unsigned char size = m_stream.peek();

        return m_stream.available() >= size;
    }

    message arduino_stream_reader::read_message()
    {
        message msg;

        auto size = m_stream.peek();

        m_stream.readBytes((unsigned char*)&msg, size);

        return msg;
    }
#endif
