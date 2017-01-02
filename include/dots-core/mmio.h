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


// 8-bit timers
template <ioaddr_t _base, ioaddr_t _msk>
struct __timer_8bit_regs {
    static constexpr ioaddr_t tccra = _base;
    static constexpr ioaddr_t tccrb = _base+1;
    static constexpr ioaddr_t timsk = _msk;
};

typedef __timer_8bit_regs<0x44, 0x6e> timer_0;
typedef __timer_8bit_regs<0xb0, 0x70> timer_2;

}
}



#endif // OS_CORE_MMIO_H_
