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


namespace os {


enum class pin_type : byte_t {
    analog, digital
};

enum class pin_mode : byte_t {
    input, input_pullup, output
};

enum class pin_state : byte_t {
    low, high
};

template <pin_type _type>
struct io_pin {
    io_pin(byte_t p) : pin(p) { }
    io_pin(const io_pin<_type>& o) : pin(o.pin) { }
    const byte_t pin;
};

typedef io_pin<pin_type::analog> apin_t;
typedef io_pin<pin_type::digital> dpin_t;

constexpr byte_t invalid_pin = 0xff;

bool set_pin_mode(dpin_t p, pin_mode m);
bool set_pin_state(dpin_t, pin_state s);

}

OS_INLINE os::dpin_t operator "" _dpin(unsigned long long b) {
    return os::dpin_t((byte_t)b);
}

OS_INLINE os::apin_t operator "" _apin(unsigned long long b) {
    return os::apin_t((byte_t)b);
}


#endif // OS_CORE_PINS_H_
