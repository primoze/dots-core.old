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

#include <dots-core/util.h>
#include <avr/io.h>
#include <avr/interrupt.h>

namespace os {
namespace util {

keep_interrupt_flag::keep_interrupt_flag() : sreg(SREG) {
    cli();
}

keep_interrupt_flag::~keep_interrupt_flag() {
    SREG = sreg;
}


}
}



