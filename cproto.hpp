#pragma once

#include <cstdlib>

#if __cpp_constexpr >= 200704
    #define CPROTO_CONSTEXPR constexpr
#else
    #define CPROTO_CONSTEXPR const
#endif

namespace cproto
{
    struct message
    {
        unsigned char size, checksum;
        unsigned char buffer[256 - sizeof(size) - sizeof(checksum)];

        CPROTO_CONSTEXPR static int buffer_size()
        {
            return 256 - sizeof(size) - sizeof(checksum);
        }

        unsigned char calc_checksum();
        bool is_valid(){ return checksum == calc_checksum(); }
    };

    class stream_reader_base
    {
    public:
        virtual ~stream_reader_base(){}
        virtual bool available() = 0;
        virtual message read_message() = 0;
    };

    class stream_writer_base
    {
    public:
        virtual ~stream_writer_base(){}
        virtual bool write_message(message&) = 0;
        virtual bool write_message(unsigned char*) = 0;
        virtual bool write_message(unsigned char*, size_t) = 0;
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

    class arduino_stream_writer : public stream_writer_base
    {
    public:
        arduino_stream_writer(Stream& str);
        bool write_message(message& msg);
        bool write_message(unsigned char*);
        bool write_message(unsigned char*, size_t);
    private:
        Stream& m_stream;
    };
#endif
}
