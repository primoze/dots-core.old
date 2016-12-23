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

#include <dots-core/bits.h>
#include <dots-core/pins.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <dots-core/hwi.h>

namespace os {
namespace hwi {

namespace {

struct hwi_descriptor {
    pioreg_t eicr;
    byte_t iscn;
    pioreg_t eimsk;
    byte_t intn;
} OS_PACKED;

const hwi_descriptor pin_interrupts[] PROGMEM = {
        { &EICRA, ISC00, &EIMSK, INT0 },
        { &EICRA, ISC10, &EIMSK, INT1 }
};

constexpr byte_t num_interrupts = 2;
isr_t interrupt_handlers[num_interrupts] = { nullptr, };

typedef byte_t vect_t;
constexpr vect_t no_vector = 0xff;

OS_INLINE vect_t get_pin_vector(dpin_t p) {
    switch(p.pin) {
    case 2: return 0;
    case 3: return 1;
    }
    return no_vector;
}

OS_INLINE const hwi_descriptor* get_isr_descriptor(dpin_t p) {
    vect_t v = get_pin_vector(p);
    if(no_vector == v) {
        return nullptr;
    }

    return pin_interrupts + v;
}

OS_INLINE pioreg_t get_eicr(const hwi_descriptor* p) {
    return (pioreg_t)pgm_read_word(&p->eicr);
}

OS_INLINE byte_t get_iscn(const hwi_descriptor* p) {
    return pgm_read_byte(&p->iscn);
}

OS_INLINE pioreg_t get_eimsk(const hwi_descriptor* p) {
    return (pioreg_t)pgm_read_word(&p->eimsk);
}

OS_INLINE byte_t get_intn(const hwi_descriptor* p) {
    return pgm_read_byte(&p->intn);
}

OS_INLINE void invoke_handler(vect_t v) {
    if(interrupt_handlers[v]) {
        interrupt_handlers[v]();
    }
}

}

bool set_interrupt_handler(dpin_t p, isr_t h, trigger_mode m) {
    const hwi_descriptor* desc = get_isr_descriptor(p);
    if(!desc) {
        return false;
    }

    vect_t v = get_pin_vector(p);
    if(no_vector == v) {
        return false;
    }

    interrupt_handlers[v] = h;

    pioreg_t eicr = get_eicr(desc);
    byte_t iscn = get_iscn(desc);
    pioreg_t eimsk = get_eimsk(desc);
    byte_t intn = get_intn(desc);

    os::clear_mask(*eicr, 2, iscn);
    os::set_mask(*eicr, (byte_t)m, iscn);
    os::set_bit(*eimsk, intn);
    return true;
}

void clear_interrupt_handler(dpin_t p) {
    vect_t v = get_pin_vector(p);
    if(no_vector == v) {
        return;
    }
    interrupt_handlers[v] = nullptr;
}

ISR(INT0_vect) {
    invoke_handler(0);
}

ISR(INT1_vect) {
    invoke_handler(1);
}


}
}


