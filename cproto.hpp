#pragma once

#include <cstdlib>

namespace cproto
{
    struct message
    {
        unsigned char size, checksum;
        unsigned char buffer[256 - sizeof(size) - sizeof(checksum)];
    };

    class stream_reader_base
    {
    public:
        virtual ~stream_reader_base(){}
        virtual bool available() = 0;
        virtual message read_message() = 0;
    };

#ifdef ARDUINO
    class arduino_stream_reader : public stream_reader_base
    {
    public:
        arduino_stream_reader(Stream& str);
        bool available();
        message read_message();
    private:
        Stream& m_stream;
    };
#endif
}
