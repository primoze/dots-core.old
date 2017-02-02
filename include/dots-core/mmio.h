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

#ifndef OS_CORE_MMIO_H_
#define OS_CORE_MMIO_H_

#include <dots-core/common.h>

#include <avr/io.h>

#define OS_PIOREG(p)            (pioreg_t)(p)

namespace os {
namespace mmio {


template <ioaddr_t _addr>
struct __io_reg {
    static constexpr ioaddr_t addr = _addr;
};

// Ports

template <
        class _pin,
        class _ddr,
        class _port
    >
struct __port_regs {
    typedef _pin pin;
    typedef _ddr ddr;
    typedef _port port;
};


// USART
template <
        class _udr,
        class _ucsra,
        class _ucsrb,
        class _ucsrc,
        class _ubrr
    >
struct __usart_regs {
    typedef _udr udr;
    typedef _ucsra ucsra;
    typedef _ucsrb ucsrb;
    typedef _ucsrc ucsrc;
    typedef _ubrr ubrr;
};

// External interrupts
template <
        class _pin,
        class _eicr,
        class _eimsk,
        class _eifr
    >
struct __ei_regs {
    typedef _pin pin;
    typedef _eicr eicr;
    typedef _eimsk eimsk;
    typedef _eifr eifr;
};

// Timers
template <
        class _tccra,
        class _tccrb,
        class _tcnt,
        class _ocra,
        class _ocrb,
        class _timsk,
        class _tifr
    >
struct __timer_8bit_regs {
    typedef _tccra tccra;
    typedef _tccrb tccrb;
    typedef _tcnt tcnt;
    typedef _ocra ocra;
    typedef _ocrb ocrb;
    typedef _timsk timsk;
    typedef _tifr tifr;
};


template <
        class _tccra,
        class _tccrb,
        class _tccrc,
        class _tcnt,
        class _ocra,
        class _ocrb,
        class _icr,
        class _timsk,
        class _tifr
    >
struct __timer_16bit_regs : public __timer_8bit_regs <_tccra, _tccrb, _tcnt, _ocra, _ocrb, _timsk, _tifr> {
    typedef _tccrc tccrc;
    typedef _icr icr;
};



}
}



#endif // OS_CORE_MMIO_H_
