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
#include <dots-core/ports.h>
#include <dots-core/mmio.h>
#include <dots-core/meta.h>

namespace os {

// HWI trigger mode
enum class trigger_mode : byte_t {
    low, change, falling, rising
};

/**
 * External Interrupt Control Register
 */
template <ioaddr_t _addr, byte_t _isc0, byte_t _isc1>
struct hwi_cr : public os::mmio::__io_reg <_addr> {
    static constexpr byte_t isc0 = _isc0;
    static constexpr byte_t isc1 = _isc1;
};

/**
 * External Interrupt Mask Register
 */
template <ioaddr_t _addr, byte_t _intn>
struct hwi_msk : public os::mmio::__io_reg <_addr> {
    static constexpr byte_t intn = _intn;
};

/**
 * External Interrupt Flag Register
 */
template <ioaddr_t _addr, byte_t _intfn>
struct hwi_ifr : public os::mmio::__io_reg <_addr> {
    static constexpr byte_t intfn = _intfn;
};



// Specifies no HWI vector for a given pin
constexpr byte_t no_hwi_vect = 0xff;

// External dependencies
OS_C_ABI void __os_set_interrupt_handler(byte_t vect, isr_t h);
OS_C_ABI void __os_clear_interrupt_handler(byte_t vect);


template <class _hwi_regs, byte_t _vect>
struct __hwi_vect {

    typedef typename _hwi_regs::pin _pin_type;

    static constexpr byte_t vect = _vect;

    static void set_interrupt_handler(isr_t h, trigger_mode m) {
        __os_set_interrupt_handler(vect, h);

        os::clear_mask(_MMIO_BYTE(_hwi_regs::eicr::addr), 2, _hwi_regs::eicr::isc0);
        os::set_mask(_MMIO_BYTE(_hwi_regs::eicr::addr), (byte_t)m, _hwi_regs::eicr::isc0);
        os::set_bit(_MMIO_BYTE(_hwi_regs::eimsk::addr), _hwi_regs::eimsk::intn);
    }

    static void clear_interrupt_handler() {
        os::clear_mask(_MMIO_BYTE(_hwi_regs::eicr::addr), 2, _hwi_regs::eicr::iscn);
        __os_clear_interrupt_handler(_hwi_regs::eicr::vect);
    }
};



#if defined (__AVR_ATmega328P__)

typedef os::mmio::__ei_regs <
        os::port_d::_2,
        os::hwi_cr <0x69, ISC00, ISC01>,
        os::hwi_msk <0x3d, INT0>,
        os::hwi_ifr <0x3c, INTF0>
> hwi0_regs;

typedef os::mmio::__ei_regs <
        os::port_d::_3,
        os::hwi_cr <0x69, ISC10, ISC11>,
        os::hwi_msk <0x3d, INT1>,
        os::hwi_ifr <0x3c, INTF1>
> hwi1_regs;

typedef __hwi_vect <hwi0_regs, 0u> hwi0;
typedef __hwi_vect <hwi1_regs, 1u> hwi1;

typedef os::__type_list <hwi0, hwi1> hwi_list;

#endif // defined (__AVR_ATmega328P__)


#if defined (__AVR_ATmega2560__)

typedef os::mmio::__ei_regs <
        os::port_d::_0,
        os::hwi_cr <0x69, ISC00, ISC01>,
        os::hwi_msk <0x3d, INT0>,
        os::hwi_ifr <0x3c, INTF0>
> hwi0_regs;

typedef os::mmio::__ei_regs <
        os::port_d::_1,
        os::hwi_cr <0x69, ISC10, ISC11>,
        os::hwi_msk <0x3d, INT1>,
        os::hwi_ifr <0x3c, INTF1>
> hwi1_regs;

typedef os::mmio::__ei_regs <
        os::port_d::_2,
        os::hwi_cr <0x69, ISC20, ISC21>,
        os::hwi_msk <0x3d, INT2>,
        os::hwi_ifr <0x3c, INTF2>
> hwi2_regs;

typedef os::mmio::__ei_regs <
        os::port_d::_3,
        os::hwi_cr <0x69, ISC30, ISC31>,
        os::hwi_msk <0x3d, INT3>,
        os::hwi_ifr <0x3c, INTF3>
> hwi3_regs;

typedef os::mmio::__ei_regs <
        os::port_e::_4,
        os::hwi_cr <0x6a, ISC40, ISC41>,
        os::hwi_msk <0x3d, INT4>,
        os::hwi_ifr <0x3c, INTF4>
> hwi4_regs;

typedef os::mmio::__ei_regs <
        os::port_e::_5,
        os::hwi_cr <0x6a, ISC50, ISC51>,
        os::hwi_msk <0x3d, INT5>,
        os::hwi_ifr <0x3c, INTF5>
> hwi5_regs;

typedef os::mmio::__ei_regs <
        os::port_e::_6,
        os::hwi_cr <0x6a, ISC60, ISC61>,
        os::hwi_msk <0x3d, INT6>,
        os::hwi_ifr <0x3c, INTF6>
> hwi6_regs;

typedef os::mmio::__ei_regs <
        os::port_e::_7,
        os::hwi_cr <0x6a, ISC70, ISC71>,
        os::hwi_msk <0x3d, INT7>,
        os::hwi_ifr <0x3c, INTF7>
> hwi7_regs;

typedef __hwi_vect <hwi0_regs, 0u> hwi0;
typedef __hwi_vect <hwi1_regs, 1u> hwi1;
typedef __hwi_vect <hwi2_regs, 2u> hwi2;
typedef __hwi_vect <hwi3_regs, 3u> hwi3;
typedef __hwi_vect <hwi4_regs, 4u> hwi4;
typedef __hwi_vect <hwi5_regs, 5u> hwi5;
typedef __hwi_vect <hwi6_regs, 6u> hwi6;
typedef __hwi_vect <hwi7_regs, 7u> hwi7;

typedef os::__type_list <hwi0, hwi1, hwi2, hwi3, hwi4, hwi5, hwi6, hwi7> hwi_list;


#endif // defined (__AVR_ATmega2560__)

}



#endif // OS_CORE_INTERRUPTS_H_
