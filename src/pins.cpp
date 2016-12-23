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

#include <dots-core/pins.h>
#include <dots-core/bits.h>
#include <dots-core/util.h>

#include <avr/pgmspace.h>
#include <avr/io.h>
#include <avr/interrupt.h>

namespace os {
namespace {


struct pin_descriptor {
    pioreg_t ddr;
    pioreg_t port;
    byte_t pin;
    pioreg_t input;
    byte_t in_pin;
} OS_PACKED;


const pin_descriptor digital_pins[] PROGMEM = {
        // Port D: Pins 0 - 7
        { &DDRD, &PORTD, PORTD0, &PIND, PIND0 },
        { &DDRD, &PORTD, PORTD1, &PIND, PIND1 },
        { &DDRD, &PORTD, PORTD2, &PIND, PIND2 },
        { &DDRD, &PORTD, PORTD3, &PIND, PIND3 },
        { &DDRD, &PORTD, PORTD4, &PIND, PIND4 },
        { &DDRD, &PORTD, PORTD5, &PIND, PIND5 },
        { &DDRD, &PORTD, PORTD6, &PIND, PIND6 },
        { &DDRD, &PORTD, PORTD7, &PIND, PIND7 },
        // Port B: Pins 8 - 13
        { &DDRB, &PORTB, PORTB0, &PINB, PINB0 },
        { &DDRB, &PORTB, PORTB1, &PINB, PINB1 },
        { &DDRB, &PORTB, PORTB2, &PINB, PINB2 },
        { &DDRB, &PORTB, PORTB3, &PINB, PINB3 },
        { &DDRB, &PORTB, PORTB4, &PINB, PINB4 },
        { &DDRB, &PORTB, PORTB5, &PINB, PINB5 },
        { &DDRB, &PORTB, PORTB6, &PINB, PINB6 },
        { &DDRB, &PORTB, PORTB7, &PINB, PINB7 }
};

constexpr byte_t digital_pin_count = sizeof(digital_pins) / sizeof(digital_pins[0]);

OS_INLINE pioreg_t get_ddr(pin_descriptor* p) {
    return (pioreg_t)pgm_read_word(&p->ddr);
}

OS_INLINE pioreg_t get_port(pin_descriptor* p) {
    return (pioreg_t)pgm_read_word(&p->port);
}

OS_INLINE byte_t get_pin(pin_descriptor* p) {
    return pgm_read_byte(&p->pin);
}

OS_INLINE pioreg_t get_input(pin_descriptor* p) {
    return (pioreg_t)pgm_read_word(&p->input);
}

OS_INLINE byte_t get_in_pin(pin_descriptor* p) {
    return pgm_read_byte(&p->in_pin);
}

OS_INLINE pin_descriptor* get_pin_descriptor(dpin_t p) {
    if(p.pin > digital_pin_count) {
        return nullptr;
    }
    return (pin_descriptor*)digital_pins + p.pin;
}




} // namespace {}


using os::util::keep_interrupt_flag;


bool set_pin_mode(dpin_t p, pin_mode m) {
    auto desc = get_pin_descriptor(p);
    if(!desc) {
        return false;
    }

    pioreg_t ddr = get_ddr(desc);
    pioreg_t port = get_port(desc);
    byte_t pin = get_pin(desc);

    keep_interrupt_flag keep;
    if(pin_mode::input == m) {
        os::clear_bit(*ddr, pin);
        os::clear_bit(*port, pin);
    } else if(pin_mode::input_pullup == m) {
        os::clear_bit(*port, pin);
        os::set_bit(*port, pin);
    } else if(pin_mode::output == m) {
        os::set_bit(*ddr, pin);
    } else {
        return false;
    }

    return true;
}

bool set_pin_state(dpin_t p, pin_state s) {
    auto desc = get_pin_descriptor(p);
    if(!desc) {
        return false;
    }

    pioreg_t port = get_port(desc);
    byte_t bit = get_pin(desc);

    keep_interrupt_flag keep;
    if(s == pin_state::low) {
        os::clear_bit(*port, bit);
    } else if(s == pin_state::high) {
        os::set_bit(*port, bit);
    } else {
        return false;
    }

    return true;
}

bool get_pin_state(dpin_t p, pin_state& s) {
    auto desc = get_pin_descriptor(p);
    if(!desc) {
        return false;
    }

    pioreg_t port = get_input(desc);
    byte_t bit = get_in_pin(desc);

    keep_interrupt_flag keep;
    s = os::get_bit(*port, bit) ? pin_state::high : pin_state::low;
    return true;
}


}


