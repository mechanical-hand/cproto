#pragma once
#ifndef ARDUINO

#include <vector>

namespace cproto
{
    class fake_arduino_stream
    {
    public:
        int available()
        {
            return m_data.size() - m_index;
        }

        unsigned char peek()
        {
            return m_data[m_index];
        }

        unsigned char read()
        {
            unsigned char elem = peek();
            m_index++;
            return elem;
        }

        void readBytes(unsigned char* buf, int len)
        {
            for(int i = 0; i < len; i++)
            {
                buf[i] = read();
            }
        }

        size_t write(unsigned char* a, size_t size)
        {
            m_data.reserve(m_data.size() + size);
            for(size_t i = 0; i < size; ++i)
            {
                m_data.push_back(a[i]);
            }
            return size;
        }

        fake_arduino_stream(std::vector<unsigned char> data) : m_data(data), m_index(0){}
    // Left it public for testing purposes
    //private:
        std::vector<unsigned char> m_data;
        int m_index;
    };
}

typedef cproto::fake_arduino_stream Stream;

#endif
