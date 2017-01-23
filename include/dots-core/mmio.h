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


// Ports
template <ioaddr_t _base>
struct __port_regs {
    static constexpr ioaddr_t pin = _base;
    static constexpr ioaddr_t ddr = _base+1;
    static constexpr ioaddr_t port = _base+2;
};

typedef __port_regs<0x23> port_b;
typedef __port_regs<0x26> port_c;
typedef __port_regs<0x29> port_d;


// External interrupts
template <ioaddr_t _cr, ioaddr_t _msk>
struct __ei_regs {
    static constexpr ioaddr_t cr = _cr;
    static constexpr ioaddr_t msk = _msk;
};

typedef __ei_regs<0x69, 0x3d> eia;


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
