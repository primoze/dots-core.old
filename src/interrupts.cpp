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

#include <dots-core/interrupts.h>
#include <dots-core/bits.h>
#include <dots-core/pins.h>
#include <dots-core/array.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>

namespace os {
namespace {

template <class... _pins>
struct __hwi_handlers {
  typedef os::util::array<isr_t, sizeof...(_pins)> array_t;
  static array_t array;
};

template <class... _pins>
os::util::array<isr_t, sizeof...(_pins)> __hwi_handlers<_pins...>::array;


typedef __hwi_handlers<hwi0, hwi1> hwi_handlers;

void invoke_handler(byte_t vect) {
  if(hwi_handlers::array[vect]) {
    hwi_handlers::array[vect]();
  }
}

}

OS_C_ABI void __os_set_interrupt_handler(byte_t vect, isr_t h) {
  if(vect < hwi_handlers::array_t::SIZE) {
    hwi_handlers::array[vect] = h;
  }
}

OS_C_ABI void __os_clear_interrupt_handler(byte_t vect) {
  if(vect < hwi_handlers::array_t::SIZE) {
    hwi_handlers::array[vect] = nullptr;
  }
}

#if defined (__AVR_ATmega328P__) || defined (__AVR_ATmega2560__)

ISR(INT0_vect) {
    invoke_handler(0);
}

ISR(INT1_vect) {
    invoke_handler(1);
}

#endif // defined (__AVR_ATmega328P___) || defined (__AVR_ATmega2560__)


#if defined (__AVR_ATmega2560__)

ISR(INT2_vect) {
    invoke_handler(2);
}

ISR(INT3_vect) {
    invoke_handler(3);
}

ISR(INT4_vect) {
    invoke_handler(4);
}

ISR(INT5_vect) {
    invoke_handler(5);
}

ISR(INT6_vect) {
    invoke_handler(6);
}

ISR(INT7_vect) {
    invoke_handler(7);
}

#endif // defined (__AVR_ATmega2560__)


}


