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

#ifndef OS_CORE_INTERRUPTS_H_
#define OS_CORE_INTERRUPTS_H_

#include <dots-core/common.h>
#include <dots-core/bits.h>
#include <dots-core/pins.h>
#include <dots-core/mmio.h>

namespace os {

// HWI trigger mode
enum class trigger_mode : byte_t {
    low, change, falling, rising
};

// Specifies no HWI vector for a given pin
constexpr byte_t no_hwi_vect = 0xff;

// External dependencies
OS_C_ABI void __os_set_interrupt_handler(byte_t vect, isr_t h);
OS_C_ABI void __os_clear_interrupt_handler(byte_t vect);

// HWI vector base
template <class _pin, byte_t _vect_num, ioaddr_t _eicr, byte_t _iscn, ioaddr_t _eimsk, byte_t _intn>
struct __hwi_vect {
    typedef _pin pin;
    static constexpr byte_t vect_num = _vect_num;

    static void set_interrupt_handler(isr_t h, trigger_mode m) {
        __os_set_interrupt_handler(vect_num, h);

        pioreg_t eicr = &_MMIO_BYTE(_eicr);
        pioreg_t eimsk = &_MMIO_BYTE(_eimsk);

        os::clear_mask(*eicr, 2, _iscn);
        os::set_mask(*eicr, (byte_t)m, _iscn);
        os::set_bit(*eimsk, _intn);
    }

    static void clear_interrupt_handler() {
        pioreg_t eicr = &_MMIO_BYTE(_eicr);
        os::clear_mask(*eicr, 2, _iscn);
        __os_clear_interrupt_handler(vect_num);
    }
};

template <class _pin>
struct __hwi_vect<_pin, no_hwi_vect, 0, 0, 0, 0> { };

// Generic HWI vector - doesn't exist
template <class _pin>
struct hwi_vect : public __hwi_vect<_pin, no_hwi_vect, 0, 0, 0, 0> { };

// D2 - HWI 0
template <>
struct hwi_vect<port_d::_2> : public __hwi_vect<port_d::_2, 0, os::mmio::eia::cr, ISC00, os::mmio::eia::msk, INT0> { };

// D3 - HWI 1
template <>
struct hwi_vect<port_d::_3> : public __hwi_vect<port_d::_3, 1, os::mmio::eia::cr, ISC10, os::mmio::eia::msk, INT1> { };

// Shorthand
typedef hwi_vect<port_d::_2> hwi0;
typedef hwi_vect<port_d::_3> hwi1;

}



#endif // OS_CORE_INTERRUPTS_H_
