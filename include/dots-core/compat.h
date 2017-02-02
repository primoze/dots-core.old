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

#ifndef OS_CORE_COMPAT_H_
#define OS_CORE_COMPAT_H_


/**
 * This file contains Arduino compatibility definitions.
 */



#include <dots-core/ports.h>


namespace os {
namespace compat {


#if defined (__AVR_ATmega328P__)

// Digital pins
// 0 - 7
typedef port_d::_0 D0;
typedef port_d::_1 D1;
typedef port_d::_2 D2;
typedef port_d::_3 D3;
typedef port_d::_4 D4;
typedef port_d::_5 D5;
typedef port_d::_6 D6;
typedef port_d::_7 D7;

// 8 - 13
typedef port_b::_0 D8;
typedef port_b::_1 D9;
typedef port_b::_2 D10;
typedef port_b::_3 D11;
typedef port_b::_4 D12;
typedef port_b::_5 D13;

// Analog pins
// 0 - 6
typedef port_c::_0 A0;
typedef port_c::_1 A1;
typedef port_c::_2 A2;
typedef port_c::_3 A3;
typedef port_c::_4 A4;
typedef port_c::_5 A5;
typedef port_c::_6 A6;

#endif // defined (__AVR_ATmega328P__)



#if defined (__AVR_ATmega2560__)

// Digital pins
// 0 - 7
typedef port_e::_0 D0;
typedef port_e::_1 D1;
typedef port_e::_4 D2;
typedef port_e::_5 D3;
typedef port_g::_5 D4;
typedef port_e::_3 D5;
typedef port_h::_3 D6;
typedef port_h::_4 D7;

// 8 - 15
typedef port_h::_5 D8;
typedef port_h::_6 D9;
typedef port_b::_4 D10;
typedef port_b::_5 D11;
typedef port_b::_6 D12;
typedef port_b::_7 D13;
typedef port_j::_1 D14;
typedef port_j::_0 D15;

// 16 - 23
typedef port_h::_1 D16;
typedef port_h::_0 D17;
typedef port_d::_3 D18;
typedef port_d::_2 D19;
typedef port_d::_1 D20;
typedef port_d::_0 D21;
typedef port_a::_0 D22;
typedef port_a::_1 D23;

// 24 - 31
typedef port_a::_2 D24;
typedef port_a::_3 D25;
typedef port_a::_4 D26;
typedef port_a::_5 D27;
typedef port_a::_6 D28;
typedef port_a::_7 D29;
typedef port_c::_7 D30;
typedef port_c::_6 D31;

// 32 - 39
typedef port_c::_5 D32;
typedef port_c::_4 D33;
typedef port_c::_3 D34;
typedef port_c::_2 D35;
typedef port_c::_1 D36;
typedef port_c::_0 D37;
typedef port_d::_7 D38;
typedef port_g::_2 D39;

// 40 - 47
typedef port_g::_1 D40;
typedef port_g::_0 D41;
typedef port_l::_7 D42;
typedef port_l::_6 D43;
typedef port_l::_5 D44;
typedef port_l::_4 D45;
typedef port_l::_3 D46;
typedef port_l::_2 D47;

// 48 - 53
typedef port_l::_1 D48;
typedef port_l::_0 D49;
typedef port_b::_3 D50;
typedef port_b::_2 D51;
typedef port_b::_1 D52;
typedef typename port_b::_0 D53;

// Analog pins
// 0 - 7
typedef port_f::_0 A0;
typedef port_f::_1 A1;
typedef port_f::_2 A2;
typedef port_f::_3 A3;
typedef port_f::_4 A4;
typedef port_f::_5 A5;
typedef port_f::_6 A6;
typedef port_f::_7 A7;

// 8 - 15
typedef port_k::_0 A8;
typedef port_k::_1 A9;
typedef port_k::_2 A10;
typedef port_k::_3 A11;
typedef port_k::_4 A12;
typedef port_k::_5 A13;
typedef port_k::_6 A14;
typedef port_k::_7 A15;

#endif // defined (__AVR_ATmega2560__)

}
}


#endif // OS_CORE_COMPAT_H_
