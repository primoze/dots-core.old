/*
 * Copyright 2017 Primoz Erjavec
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

#ifndef OS_CORE_PORTS_H_
#define OS_CORE_PORTS_H_


#include <dots-core/mmio.h>
#include <dots-core/pins.h>

namespace os {



template <class _port_regs>
struct __io_port {
    typedef os::digital_pin<_port_regs, 0, 0, 0> _0;
    typedef os::digital_pin<_port_regs, 1, 1, 1> _1;
    typedef os::digital_pin<_port_regs, 2, 2, 2> _2;
    typedef os::digital_pin<_port_regs, 3, 3, 3> _3;
    typedef os::digital_pin<_port_regs, 4, 4, 4> _4;
    typedef os::digital_pin<_port_regs, 5, 5, 5> _5;
    typedef os::digital_pin<_port_regs, 6, 6, 6> _6;
    typedef os::digital_pin<_port_regs, 7, 7, 7> _7;
};


// Define things 328p and 2560 have in common
#if defined (__AVR_ATmega328P__) || defined (__AVR_ATmega2560__)


typedef os::mmio::__port_regs <
        os::mmio::__io_reg <0x23>,
        os::mmio::__io_reg <0x24>,
        os::mmio::__io_reg <0x25>
    > port_b_regs;

typedef os::mmio::__port_regs <
        os::mmio::__io_reg <0x26>,
        os::mmio::__io_reg <0x27>,
        os::mmio::__io_reg <0x28>
    > port_c_regs;

typedef os::mmio::__port_regs <
        os::mmio::__io_reg <0x29>,
        os::mmio::__io_reg <0x2a>,
        os::mmio::__io_reg <0x2b>
    > port_d_regs;

typedef __io_port <port_b_regs> port_b;
typedef __io_port <port_d_regs> port_d;

#if defined (__AVR_ATmega328P__)

// Port C only has 7 pins on 328p
struct port_c {
    typedef digital_pin<port_c_regs, 0, 0, 0> _0;
    typedef digital_pin<port_c_regs, 1, 1, 1> _1;
    typedef digital_pin<port_c_regs, 2, 2, 2> _2;
    typedef digital_pin<port_c_regs, 3, 3, 3> _3;
    typedef digital_pin<port_c_regs, 4, 4, 4> _4;
    typedef digital_pin<port_c_regs, 5, 5, 5> _5;
    typedef digital_pin<port_c_regs, 6, 6, 6> _6;
};

#elif defined (__AVR_ATmega2560__)

// On 2560 it has all 8 pins
typedef __io_port <port_c_regs> port_c;

#endif // #elif defined (__AVR_ATmega2560__)

#endif // defined (__AVR_ATmega328P__) || defined (__AVR_ATmega2560__)



#if defined (__AVR_ATmega2560__)


typedef os::mmio::__port_regs <
        os::mmio::__io_reg <0x20>,
        os::mmio::__io_reg <0x21>,
        os::mmio::__io_reg <0x22>
    > port_a_regs;

typedef os::mmio::__port_regs <
        os::mmio::__io_reg <0x2c>,
        os::mmio::__io_reg <0x2d>,
        os::mmio::__io_reg <0x2e>
    > port_e_regs;

typedef os::mmio::__port_regs <
        os::mmio::__io_reg <0x2f>,
        os::mmio::__io_reg <0x30>,
        os::mmio::__io_reg <0x31>
    > port_f_regs;

typedef os::mmio::__port_regs <
        os::mmio::__io_reg <0x32>,
        os::mmio::__io_reg <0x33>,
        os::mmio::__io_reg <0x34>
    > port_g_regs;

typedef os::mmio::__port_regs <
        os::mmio::__io_reg <0x100>,
        os::mmio::__io_reg <0x101>,
        os::mmio::__io_reg <0x102>
    > port_h_regs;

typedef os::mmio::__port_regs <
        os::mmio::__io_reg <0x103>,
        os::mmio::__io_reg <0x104>,
        os::mmio::__io_reg <0x105>
    > port_j_regs;

typedef os::mmio::__port_regs <
        os::mmio::__io_reg <0x106>,
        os::mmio::__io_reg <0x107>,
        os::mmio::__io_reg <0x108>
    > port_k_regs;

typedef os::mmio::__port_regs <
        os::mmio::__io_reg <0x109>,
        os::mmio::__io_reg <0x10a>,
        os::mmio::__io_reg <0x10b>
    > port_l_regs;

typedef __io_port <port_a_regs> port_a;
typedef __io_port <port_e_regs> port_e;
typedef __io_port <port_f_regs> port_f;
typedef __io_port <port_h_regs> port_h;
typedef __io_port <port_j_regs> port_j;
typedef __io_port <port_k_regs> port_k;
typedef __io_port <port_l_regs> port_l;

// Port G only has 6 pins
struct port_g {
    typedef digital_pin<port_c_regs, 0, 0, 0> _0;
    typedef digital_pin<port_c_regs, 1, 1, 1> _1;
    typedef digital_pin<port_c_regs, 2, 2, 2> _2;
    typedef digital_pin<port_c_regs, 3, 3, 3> _3;
    typedef digital_pin<port_c_regs, 4, 4, 4> _4;
    typedef digital_pin<port_c_regs, 5, 5, 5> _5;
};


#endif // defined (__AVR_ATmega2560__)


}


#endif // OS_CORE_PORTS_H_
