#include <cproto.hpp>
#include <string.h>

unsigned char cproto::message::calc_checksum()
{
    unsigned char result = 0;
    for(int i = 0; i < size; i++)
    {
        result += buffer[i];
    }
    return result;
}

#ifdef ARDUINO

    cproto::arduino_stream_reader::arduino_stream_reader(Stream& s) : m_stream(s){}

    bool cproto::arduino_stream_reader::available()
    {
        if(!m_stream.available()) return false;

        unsigned char size = m_stream.peek();

        return m_stream.available() >= size;
    }

    cproto::message cproto::arduino_stream_reader::read_message()
    {
        cproto::message msg;

        auto size = m_stream.peek();

        m_stream.readBytes((unsigned char*)&msg, size);

        return msg;
    }

    cproto::arduino_stream_writer::arduino_stream_writer(Stream& s) : m_stream(s){}

    bool cproto::arduino_stream_writer::write_message(cproto::message& msg)
    {
        return m_stream.write((unsigned char*)&msg, msg.size);
    }

    bool cproto::arduino_stream_writer::write_message(unsigned char* msg, size_t size)
    {
        cproto::message m;
        if(size < m.buffer_size())
            m.size = size;
        else
            m.size = m.buffer_size();

        memcpy(m.buffer, msg, m.size);

        m.checksum = m.calc_checksum();
        return write_message(m);
    }

    bool cproto::arduino_stream_writer::write_message(unsigned char* msg)
    {
        return write_message(msg, strlen((char*)msg));
    }
#endif
