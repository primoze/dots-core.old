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

#ifndef OS_CORE_PINS_H_
#define OS_CORE_PINS_H_


#include <dots-core/common.h>
#include <dots-core/util.h>
#include <dots-core/bits.h>
#include <dots-core/mmio.h>


namespace os {

enum class pin_mode : byte_t {
    input, input_pullup, output
};

struct pin_ops {
    static OS_INLINE bool get_state(ioaddr_t pin, byte_t bit) {
        return os::get_bit(_MMIO_BYTE(pin), bit);
    }

    static OS_INLINE void set_state(bool high, ioaddr_t port, byte_t bit) {
        os::util::keep_interrupt_flag keep;
        if(high) {
            os::set_bit(_MMIO_BYTE(port), bit);
        } else {
            os::clear_bit(_MMIO_BYTE(port), bit);
        }
    }

    static void set_mode(os::pin_mode m, ioaddr_t ddr, byte_t ddr_bit, ioaddr_t port, byte_t port_bit) {
        os::util::keep_interrupt_flag keep;
        if(os::pin_mode::input == m) {
            os::clear_bit(_MMIO_BYTE(ddr), ddr_bit);
            os::clear_bit(_MMIO_BYTE(port), port_bit);
        } else if(os::pin_mode::input_pullup == m) {
            os::clear_bit(_MMIO_BYTE(ddr), ddr_bit);
            os::set_bit(_MMIO_BYTE(port), port_bit);
        } else if(os::pin_mode::output == m) {
            os::set_bit(_MMIO_BYTE(ddr), ddr_bit);
        }
    }
};

template <
        class _port_regs,
        byte_t _ddr_bit,
        byte_t _port_bit,
        byte_t _pin_bit
    >
struct io_pin : public _port_regs {

    typedef pin_ops _pin_ops_type;

    static constexpr byte_t ddr_bit = _ddr_bit;
    static constexpr byte_t port_bit = _port_bit;
    static constexpr byte_t pin_bit = _pin_bit;

    static OS_INLINE bool get_state() {
        return _pin_ops_type::get_state(_port_regs::pin::addr, pin_bit);
    }

    static OS_INLINE void set_state(bool high) {
        _pin_ops_type::set_state(high, _port_regs::port::addr, port_bit);
    }

    static OS_INLINE void set_mode(os::pin_mode m) {
        _pin_ops_type::set_mode(m, _port_regs::ddr::addr, ddr_bit, _port_regs::port::addr, port_bit);
    }

protected:
    constexpr io_pin() { }
};


template <
        class _port_regs,
        byte_t _ddr_bit,
        byte_t _port_bit,
        byte_t _pin_bit
    >
using digital_pin = io_pin<_port_regs, _ddr_bit, _port_bit, _pin_bit>;

template <
        class _port_regs,
        byte_t _ddr_bit,
        byte_t _port_bit,
        byte_t _pin_bit
    >
struct analog_pin : public io_pin<_port_regs, _ddr_bit, _port_bit, _pin_bit> {
    uint_t read_value() {
        // todo
        return 0;
    }

    void write_value(uint_t val) {
        // todo
    }
};

}


#endif // OS_CORE_PINS_H_
