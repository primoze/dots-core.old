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
#include <dots-core/mmio.h>


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
struct usart {
    bool init(uint32_t rate) {

        uint32_t brr_val = F_CPU / (16*rate) - 1;

        // Set baud rate
        _MMIO_BYTE(_base+UBRRH) = (byte_t)(brr_val >> 8);
        _MMIO_BYTE(_base+UBRRL) = (byte_t)brr_val;

        // Disable Rx/Tx
        os::clear_bit(_MMIO_BYTE(_base+UCSRB), RXEN0);
        os::clear_bit(_MMIO_BYTE(_base+UCSRB), TXEN0);

        // Sync mode
        os::clear_bit(_MMIO_BYTE(_base+UCSRC), UMSEL00);
        os::clear_bit(_MMIO_BYTE(_base+UCSRC), UMSEL01);
        // 8 data bits
        os::set_bit(_MMIO_BYTE(_base+UCSRC), UCSZ00);
        os::set_bit(_MMIO_BYTE(_base+UCSRC), UCSZ01);
        os::clear_bit(_MMIO_BYTE(_base+UCSRB), UCSZ02);
        // No parity bits
        os::clear_bit(_MMIO_BYTE(_base+UCSRC), UPM00);
        os::clear_bit(_MMIO_BYTE(_base+UCSRC), UPM01);
        // 2 stop bits
        os::set_bit(_MMIO_BYTE(_base+UCSRC), USBS0);
        // Enable Rx/Tx
        os::set_bit(_MMIO_BYTE(_base+UCSRB), RXEN0);
        os::set_bit(_MMIO_BYTE(_base+UCSRB), TXEN0);
        return true;
    }

    bool transmit(const byte_t& b) {
        // Wait for empty transmit buffer
        while (!os::get_bit(_MMIO_BYTE(_base+UCSRA), UDRE0) && !os::get_bit(_MMIO_BYTE(_base+UCSRA), TXC0)) { }
        // Write data
        _MMIO_BYTE(_base+UDR) = b;
        return true;
    }

private:
    OS_INLINE void write_raw(byte_t b) {
        _MMIO_BYTE(_base+UDR) = b;
    }

    OS_INLINE byte_t read_raw() {
        return _MMIO_BYTE(_base+UDR);
    }

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
