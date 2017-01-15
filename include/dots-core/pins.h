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


enum class pin_type : byte_t {
    analog, digital
};

enum class pin_mode : byte_t {
    input, input_pullup, output
};

template <
        class _port_regs,
        os::pin_type _type,
        byte_t _ddr_bit,
        byte_t _port_bit,
        byte_t _pin_bit
    >
struct io_pin : public _port_regs {

    static constexpr os::pin_type type = _type;
    static constexpr byte_t ddr_bit = _ddr_bit;
    static constexpr byte_t port_bit = _port_bit;
    static constexpr byte_t pin_bit = _pin_bit;

    static bool get_state() {
        return os::get_bit(_MMIO_BYTE(_port_regs::pin), pin_bit);
    }

    static void set_state(bool high) {
        os::util::keep_interrupt_flag keep;
        if(high) {
            os::set_bit(_MMIO_BYTE(_port_regs::port), port_bit);
        } else {
            os::clear_bit(_MMIO_BYTE(_port_regs::port), port_bit);
        }
    }

    static void set_mode(os::pin_mode m) {
        os::util::keep_interrupt_flag keep;
        if(os::pin_mode::input == m) {
            os::clear_bit(_MMIO_BYTE(_port_regs::ddr), ddr_bit);
            os::clear_bit(_MMIO_BYTE(_port_regs::port), port_bit);
        } else if(os::pin_mode::input_pullup == m) {
            os::clear_bit(_MMIO_BYTE(_port_regs::ddr), ddr_bit);
            os::set_bit(_MMIO_BYTE(_port_regs::port), port_bit);
        } else if(os::pin_mode::output == m) {
            os::set_bit(_MMIO_BYTE(_port_regs::ddr), port_bit);
        }
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
using digital_pin = io_pin<_port_regs, os::pin_type::digital, _ddr_bit, _port_bit, _pin_bit>;

template <
        class _port_regs,
        byte_t _ddr_bit,
        byte_t _port_bit,
        byte_t _pin_bit
    >
struct analog_pin : public io_pin<_port_regs, os::pin_type::analog, _ddr_bit, _port_bit, _pin_bit> {
    uint_t read_value() {
        // todo
        return 0;
    }

    void write_value(uint_t val) {
        // todo
    }
};


// Ports

enum class port : byte_t {
    b, c, d
};

template <os::port>
struct io_port { };


template <>
struct io_port<os::port::d> {
    typedef digital_pin<os::mmio::port_d, DDD0, PORTD0, PIND0> _0;
    typedef digital_pin<os::mmio::port_d, DDD1, PORTD1, PIND1> _1;
    typedef digital_pin<os::mmio::port_d, DDD2, PORTD2, PIND2> _2;
    typedef digital_pin<os::mmio::port_d, DDD3, PORTD3, PIND3> _3;
    typedef digital_pin<os::mmio::port_d, DDD4, PORTD4, PIND4> _4;
    typedef digital_pin<os::mmio::port_d, DDD5, PORTD5, PIND5> _5;
    typedef digital_pin<os::mmio::port_d, DDD6, PORTD6, PIND6> _6;
    typedef digital_pin<os::mmio::port_d, DDD7, PORTD7, PIND7> _7;
};

template <>
struct io_port<os::port::b> {
    typedef digital_pin<os::mmio::port_b, DDB0, PORTB0, PINB0> _0;
    typedef digital_pin<os::mmio::port_b, DDB1, PORTB1, PINB1> _1;
    typedef digital_pin<os::mmio::port_b, DDB2, PORTB2, PINB2> _2;
    typedef digital_pin<os::mmio::port_b, DDB3, PORTB3, PINB3> _3;
    typedef digital_pin<os::mmio::port_b, DDB4, PORTB4, PINB4> _4;
    typedef digital_pin<os::mmio::port_b, DDB5, PORTB5, PINB5> _5;
};

template <>
struct io_port<os::port::c> {
    typedef analog_pin<os::mmio::port_c, DDC0, PORTC0, PINC0> _0;
    typedef analog_pin<os::mmio::port_c, DDC1, PORTC1, PINC1> _1;
    typedef analog_pin<os::mmio::port_c, DDC2, PORTC2, PINC2> _2;
    typedef analog_pin<os::mmio::port_c, DDC3, PORTC3, PINC3> _3;
    typedef analog_pin<os::mmio::port_c, DDC4, PORTC4, PINC4> _4;
    typedef analog_pin<os::mmio::port_c, DDC5, PORTC5, PINC5> _5;
    typedef analog_pin<os::mmio::port_c, DDC6, PORTC6, PINC6> _6;
};

typedef os::io_port<os::port::b> port_b;
typedef os::io_port<os::port::c> port_c;
typedef os::io_port<os::port::d> port_d;

// Digital pins
typedef port_d::_0 D0;
typedef port_d::_1 D1;
typedef port_d::_2 D2;
typedef port_d::_3 D3;
typedef port_d::_4 D4;
typedef port_d::_5 D5;
typedef port_d::_6 D6;
typedef port_d::_7 D7;

typedef port_b::_0 D8;
typedef port_b::_1 D9;
typedef port_b::_2 D10;
typedef port_b::_3 D11;
typedef port_b::_4 D12;
typedef port_b::_5 D13;

// Analog/Digital pins
typedef port_c::_0 A0;
typedef port_c::_1 A1;
typedef port_c::_2 A2;
typedef port_c::_3 A3;
typedef port_c::_4 A4;
typedef port_c::_5 A5;
typedef port_c::_6 A6;

}


#endif // OS_CORE_PINS_H_
