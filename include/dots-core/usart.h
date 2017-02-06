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
#include <dots-core/meta.h>


namespace os {
namespace usart {

/**
 * USART Data Register
 */
template <ioaddr_t _addr>
using udr = os::mmio::__io_reg <_addr>;

/**
 * USART Status and Control Register A
 */
template <
        ioaddr_t _addr,
        byte_t _mpcm,
        byte_t _u2x,
        byte_t _upe,
        byte_t _dor,
        byte_t _fe,
        byte_t _udre,
        byte_t _txc,
        byte_t _rxc
    >
struct ucsra : public os::mmio::__io_reg <_addr> {
    static constexpr byte_t mpcm = _mpcm;
    static constexpr byte_t u2x = _u2x;
    static constexpr byte_t upe = _upe;
    static constexpr byte_t dor = _dor;
    static constexpr byte_t fe = _fe;
    static constexpr byte_t udre = _udre;
    static constexpr byte_t rxc = _rxc;
    static constexpr byte_t txc = _txc;
};

/**
 * USART Status and Control Register B
 */
template <
        ioaddr_t _addr,
        byte_t _txb8,
        byte_t _rxb8,
        byte_t _ucsz2,
        byte_t _txen,
        byte_t _rxen,
        byte_t _udrie,
        byte_t _txcie,
        byte_t _rxcie
    >
struct ucsrb : public os::mmio::__io_reg <_addr> {
    static constexpr byte_t mpcm = _txb8;
    static constexpr byte_t u2x = _rxb8;
    static constexpr byte_t upe = _ucsz2;
    static constexpr byte_t dor = _txen;
    static constexpr byte_t fe = _rxen;
    static constexpr byte_t udre = _udrie;
    static constexpr byte_t rxc = _txcie;
    static constexpr byte_t txc = _rxcie;
};

/**
 * USART Status and Control Register C
 */
template <
        ioaddr_t _addr,
        byte_t _ucpol,
        byte_t _ucsz0,
        byte_t _ucsz1,
        byte_t _usbs,
        byte_t _upm0,
        byte_t _upm1,
        byte_t _umsel0,
        byte_t _umsel1
    >
struct ucsrc : public os::mmio::__io_reg <_addr> {
    static constexpr byte_t mpcm = _ucpol;
    static constexpr byte_t u2x = _ucsz0;
    static constexpr byte_t upe = _ucsz1;
    static constexpr byte_t dor = _usbs;
    static constexpr byte_t fe = _upm0;
    static constexpr byte_t udre = _upm1;
    static constexpr byte_t rxc = _umsel0;
    static constexpr byte_t txc = _umsel1;
};

/**
 * USART Data Register
 */
template <ioaddr_t _addr>
using udr = os::mmio::__io_reg <_addr>;

/**
 * USART Baud Rate Register
 */
template <ioaddr_t _addr>
using ubrr = os::mmio::__io_reg <_addr>;


#if defined (__AVR_ATmega328P__)

typedef os::mmio::__usart_regs <
        os::usart::udr <0xc6>,
        os::usart::ucsra <0xc0, MPCM0, U2X0, UPE0, DOR0, FE0, UDRE0, TXC0, RXC0>,
        os::usart::ucsrb <0xc1, TXB80, RXB80, UCSZ02, TXEN0, RXEN0, UDRIE0, TXCIE0, RXCIE0>,
        os::usart::ucsrc <0xc2, UCPOL0, UCSZ00, UCSZ01, USBS0, UPM00, UPM01, UMSEL00, UMSEL01>,
        os::usart::ubrr <0xc4>
    > usart0_regs;

typedef os::__type_list <usart0_regs> usart_list;

#endif // defined (__AVR_ATmega328P__)

#if defined (__AVR_ATmega2560__)

typedef os::mmio::__usart_regs <
        os::usart::udr <0xc6>,
        os::usart::ucsra <0xc0, MPCM0, U2X0, UPE0, DOR0, FE0, UDRE0, TXC0, RXC0>,
        os::usart::ucsrb <0xc1, TXB80, RXB80, UCSZ02, TXEN0, RXEN0, UDRIE0, TXCIE0, RXCIE0>,
        os::usart::ucsrc <0xc2, UCPOL0, UCSZ00, UCSZ01, USBS0, UPM00, UPM01, UMSEL00, UMSEL01>,
        os::usart::ubrr <0xc4>
    > usart0_regs;

typedef os::mmio::__usart_regs <
        os::usart::udr <0xce>,
        os::usart::ucsra <0xc8, MPCM1, U2X1, UPE1, DOR1, FE1, UDRE1, TXC1, RXC1>,
        os::usart::ucsrb <0xc9, TXB81, RXB81, UCSZ12, TXEN1, RXEN1, UDRIE1, TXCIE1, RXCIE1>,
        os::usart::ucsrc <0xca, UCPOL1, UCSZ10, UCSZ11, USBS1, UPM10, UPM11, UMSEL10, UMSEL11>,
        os::usart::ubrr <0xcc>
    > usart1_regs;

typedef os::mmio::__usart_regs <
        os::usart::udr <0xd6>,
        os::usart::ucsra <0xd0, MPCM2, U2X2, UPE2, DOR2, FE2, UDRE2, TXC2, RXC2>,
        os::usart::ucsrb <0xd1, TXB82, RXB82, UCSZ22, TXEN2, RXEN2, UDRIE2, TXCIE2, RXCIE2>,
        os::usart::ucsrc <0xd2, UCPOL2, UCSZ20, UCSZ21, USBS2, UPM20, UPM21, UMSEL20, UMSEL21>,
        os::usart::ubrr <0xd4>
    > usart2_regs;

typedef os::mmio::__usart_regs <
        os::usart::udr <0x136>,
        os::usart::ucsra <0x130, MPCM2, U2X2, UPE2, DOR2, FE2, UDRE2, TXC2, RXC2>,
        os::usart::ucsrb <0x131, TXB82, RXB82, UCSZ22, TXEN2, RXEN2, UDRIE2, TXCIE2, RXCIE2>,
        os::usart::ucsrc <0x132, UCPOL2, UCSZ20, UCSZ21, USBS2, UPM20, UPM21, UMSEL20, UMSEL21>,
        os::usart::ubrr <0x134>
    > usart3_regs;

typedef os::__type_list <usart0_regs, usart1_regs, usart2_regs, usart3_regs> usart_list;

#endif // defined (__AVR_ATmega2560__)



}
}



#endif // OS_USART_H_
