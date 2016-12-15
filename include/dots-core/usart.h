/*
 * Copyright 2016 Primoz Erjavec
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef OS_USART_H_
#define OS_USART_H_

#include <avr/interrupt.h>
#include <dots-core/common.h>
#include <dots-core/cstring.h>
#include <dots-core/bits.h>


namespace os {
namespace usart {



// Writer for os::stream
template <class _usart>
class writer {
public:
    bool write(const byte_t b) {
        return usart.transmit(b);
    }
private:
    _usart usart;
};



template <ioaddr_t _base>
class usart {
public:

    usart() :
        ucsra(&_MMIO_BYTE(_base + UCSRA)),
        ucsrb(&_MMIO_BYTE(_base + UCSRB)),
        ucsrc(&_MMIO_BYTE(_base + UCSRC)),
        ubrrl(&_MMIO_BYTE(_base + UBRRL)),
        ubrrh(&_MMIO_BYTE(_base + UBRRH)),
        udr(&_MMIO_BYTE(_base + UDR))
    {
    }

    bool init(uint32_t rate) {

        uint32_t brr_val = F_CPU / (16*rate) - 1;

        // Set baud rate
        *ubrrh = (byte_t)(brr_val >> 8);
        *ubrrl = (byte_t)brr_val;

        // Disable Rx/Tx
        os::clear_bit(*ucsrb, RXEN0);
        os::clear_bit(*ucsrb, TXEN0);

        // Sync mode
        os::clear_bit(*ucsrc, UMSEL00);
        os::clear_bit(*ucsrc, UMSEL01);
        // 8 data bits
        os::set_bit(*ucsrc, UCSZ00);
        os::set_bit(*ucsrc, UCSZ01);
        os::clear_bit(*ucsrb, UCSZ02);
        // No parity bits
        os::clear_bit(*ucsrc, UPM00);
        os::clear_bit(*ucsrc, UPM01);
        // 2 stop bits
        os::set_bit(*ucsrc, USBS0);
        // Enable Rx/Tx
        os::set_bit(*ucsrb, RXEN0);
        os::set_bit(*ucsrb, TXEN0);
        return true;
    }

    bool transmit(const byte_t& b) {
        // Wait for empty transmit buffer
        while (!os::get_bit(*ucsra, UDRE0) && !os::get_bit(*ucsra, TXC0)) { }
        // Write data
        *udr = b;
        return true;
    }

private:
    pioreg_t ucsra;
    pioreg_t ucsrb;
    pioreg_t ucsrc;
    pioreg_t ubrrl;
    pioreg_t ubrrh;
    pioreg_t udr;

private:
    static constexpr byte_t UCSRA = 0;
    static constexpr byte_t UCSRB = 1;
    static constexpr byte_t UCSRC = 2;
    static constexpr byte_t UBRRL = 4;
    static constexpr byte_t UBRRH = 5;
    static constexpr byte_t UDR = 6;

};




}
}



#endif // OS_USART_H_
