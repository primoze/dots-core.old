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

#ifndef OS_TIMER_H_
#define OS_TIMER_H_

#include <avr/io.h>

#include <dots-core/common.h>
#include <dots-core/mmio.h>
#include <dots-core/meta.h>

namespace os {
namespace timer {


/**
 * Timer mode.
 */
enum class mode : byte_t {
    normal, ctc, fast_pwm, pc_pwm, pfc_pwm
};


/**
 * TC 8-Bit Control Register A
 */
template <ioaddr_t _addr, byte_t _wgm0, byte_t _wgm1, byte_t _coma0, byte_t _coma1, byte_t _comb0, byte_t _comb1>
struct tccra_8bit : public os::mmio::__io_reg <_addr> {

    static constexpr byte_t wgm0 = _wgm0;
    static constexpr byte_t wgm1 = _wgm1;

    static constexpr byte_t coma0 = _coma0;
    static constexpr byte_t coma1 = _coma1;

    static constexpr byte_t comb0 = _comb0;
    static constexpr byte_t comb1 = _comb1;
};


/**
 * TC 16-Bit Control Register A
 */
template <ioaddr_t _addr, byte_t _wgm0, byte_t _wgm1, byte_t _coma0, byte_t _coma1, byte_t _comb0, byte_t _comb1>
using tccra_16bit = tccra_8bit <_addr, _wgm0, _wgm1, _coma0, _coma1, _comb0, _comb1>;


/**
 * TC 8-Bit Control Register B
 */
template <ioaddr_t _addr, byte_t _cs0, byte_t _cs1, byte_t _cs2, byte_t _wgm2, byte_t _foca, byte_t _focb>
struct tccrb_8bit : public os::mmio::__io_reg <_addr> {

    static constexpr byte_t cs0 = _cs0;
    static constexpr byte_t cs1 = _cs1;
    static constexpr byte_t cs2 = _cs2;

    static constexpr byte_t wgm2 = _wgm2;

    static constexpr byte_t foca = _foca;
    static constexpr byte_t focb = _focb;
};


/**
 * TC 16-Bit Control Register B
 */
template <ioaddr_t _addr, byte_t _cs0, byte_t _cs1, byte_t _cs2, byte_t _wgm2, byte_t _wgm3, byte_t _icnc, byte_t _ices>
struct tccrb_16bit : public os::mmio::__io_reg <_addr> {

    static constexpr byte_t cs0 = _cs0;
    static constexpr byte_t cs1 = _cs1;
    static constexpr byte_t cs2 = _cs2;

    static constexpr byte_t wgm2 = _wgm2;
    static constexpr byte_t wgm3 = _wgm3;

    static constexpr byte_t icnc = _icnc;
    static constexpr byte_t ices = _ices;
};


/**
 * TC 16-Bit Control Register C
 */
template <ioaddr_t _addr, byte_t _foca, byte_t _focb>
struct tccrc_16bit : public os::mmio::__io_reg <_addr> {

    static constexpr byte_t foca = _foca;
    static constexpr byte_t focb = _focb;
};


/**
 * TC 8-Bit Timer Counter Register
 */
template <ioaddr_t _addr>
using tcnt_8bit = os::mmio::__io_reg <_addr>;

/**
 * TC 16-Bit Timer Counter Register
 */
template <ioaddr_t _addr>
using tcnt_16bit = os::mmio::__io_reg <_addr>;

/**
 * TC 8-Bit Output Compare Registers
 */
template <ioaddr_t _addr>
using ocr_8bit = os::mmio::__io_reg <_addr>;

/**
 * TC 8-Bit Output Compare Registers
 */
template <ioaddr_t _addr>
using ocr_16bit = os::mmio::__io_reg <_addr>;

/**
 * TC 16-Bit Input Capture Register
 */
template <ioaddr_t _addr>
using icr_16bit = os::mmio::__io_reg <_addr>;

/**
 * TC 8-Bit Interrupt Register Base
 */
template <ioaddr_t _addr, byte_t _toi, byte_t _ocia, byte_t _ocib>
struct __ti_reg_8bit : public os::mmio::__io_reg <_addr> {

    static constexpr byte_t toi = _toi;
    static constexpr byte_t ocia = _ocia;
    static constexpr byte_t ocib = _ocib;
};

/**
 * TC 16-Bit Interrupt Register Base
 */
template <ioaddr_t _addr, byte_t _toi, byte_t _ocia, byte_t _ocib, byte_t _ici>
struct __ti_reg_16bit : public __ti_reg_8bit <_addr, _toi, _ocia, _ocib> {

    static constexpr byte_t ici = _ici;
};

/**
 * TC 8-Bit Interrupt Mask Register
 */
template <ioaddr_t _addr, byte_t _toie, byte_t _ociea, byte_t _ocieb>
using timsk_8bit = __ti_reg_8bit <_addr, _toie, _ociea, _ocieb>;

/**
 * TC 16-Bit Interrupt Mask Register
 */
template <ioaddr_t _addr, byte_t _toie, byte_t _ociea, byte_t _ocieb, byte_t _icie>
using timsk_16bit = __ti_reg_16bit <_addr, _toie, _ociea, _ocieb, _icie>;

/**
 * TC 8-Bit Interrupt Flag Register
 */
template <ioaddr_t _addr, byte_t _tov, byte_t _ocfa, byte_t _ocfb>
using tifr_8bit = __ti_reg_8bit <_addr, _tov, _ocfa, _ocfb>;

/**
 * TC 16-Bit Interrupt Flag Register
 */
template <ioaddr_t _addr, byte_t _tov, byte_t _ocfa, byte_t _ocfb, byte_t _icf>
using tifr_16bit = __ti_reg_16bit <_addr, _tov, _ocfa, _ocfb, _icf>;


#if defined (__AVR_ATmega328P__)

// TC0
typedef os::mmio::__timer_8bit_regs <
        os::timer::tccra_8bit <0x44, WGM00, WGM01, COM0A0, COM0A1, COM0B0, COM0B1>,
        os::timer::tccrb_8bit <0x45, CS00, CS01, CS02, WGM02, FOC0A, FOC0B>,
        os::timer::tcnt_8bit <0x46>,
        os::timer::ocr_8bit <0x47>,
        os::timer::ocr_8bit <0x48>,
        os::timer::timsk_8bit <0x6e, TOIE0, OCIE0A, OCIE0B>,
        os::timer::tifr_8bit <0x35, TOV0, OCF0A, OCF0B>
    > timer0_regs;

// TC2
typedef os::mmio::__timer_8bit_regs <
        os::timer::tccra_8bit <0xb0, WGM20, WGM21, COM2A0, COM2A1, COM2B0, COM2B1>,
        os::timer::tccrb_8bit <0xb1, CS20, CS21, CS22, WGM22, FOC2A, FOC2B>,
        os::timer::tcnt_8bit <0xb2>,
        os::timer::ocr_8bit <0xb3>,
        os::timer::ocr_8bit <0xb4>,
        os::timer::timsk_8bit <0x70, TOIE2, OCIE2A, OCIE2B>,
        os::timer::tifr_8bit <0x37, TOV2, OCF2A, OCF2B>
    > timer2_regs;

// TC1
typedef os::mmio::__timer_16bit_regs <
        os::timer::tccra_16bit <0x80, WGM10, WGM11, COM1A0, COM1A1, COM1B0, COM1B1>,
        os::timer::tccrb_16bit <0x81, CS10, CS11, CS12, WGM12, WGM13, ICNC1, ICES1>,
        os::timer::tccrc_16bit <0x82, FOC1A, FOC1B>,
        os::timer::tcnt_16bit <0x84>,
        os::timer::ocr_16bit <0x88>,
        os::timer::ocr_16bit <0x8a>,
        os::timer::ocr_16bit <0x8c>,
        os::timer::icr_16bit <0x86>,
        os::timer::timsk_16bit <0x6f, TOIE1, OCIE1A, OCIE1B, ICIE1>,
        os::timer::tifr_16bit <0x36, TOV1, OCF1A, OCF1B, ICF1>
    > timer1_regs;

typedef os::__type_list <timer0_regs, timer2_regs> timer8_list;
typedef os::__type_list <timer1_regs> timer16_list;

#endif // defined (__AVR_ATmega328P__)

#if defined (__AVR_ATmega2560__)

// TC0
typedef os::mmio::__timer_8bit_regs <
        os::timer::tccra_8bit <0x44, WGM00, WGM01, COM0A0, COM0A1, COM0B0, COM0B1>,
        os::timer::tccrb_8bit <0x45, CS00, CS01, CS02, WGM02, FOC0A, FOC0B>,
        os::timer::tcnt_8bit <0x46>,
        os::timer::ocr_8bit <0x47>,
        os::timer::ocr_8bit <0x48>,
        os::timer::timsk_8bit <0x6e, TOIE0, OCIE0A, OCIE0B>,
        os::timer::tifr_8bit <0x35, TOV0, OCF0A, OCF0B>
    > timer0_regs;

// TC2
typedef os::mmio::__timer_8bit_regs <
        os::timer::tccra_8bit <0xb0, WGM20, WGM21, COM2A0, COM2A1, COM2B0, COM2B1>,
        os::timer::tccrb_8bit <0xb1, CS20, CS21, CS22, WGM22, FOC2A, FOC2B>,
        os::timer::tcnt_8bit <0xb2>,
        os::timer::ocr_8bit <0xb3>,
        os::timer::ocr_8bit <0xb4>,
        os::timer::timsk_8bit <0x70, TOIE2, OCIE2A, OCIE2B>,
        os::timer::tifr_8bit <0x37, TOV2, OCF2A, OCF2B>
    > timer2_regs;

// TC1
typedef os::mmio::__timer_16bit_regs <
        os::timer::tccra_16bit <0x80, WGM10, WGM11, COM1A0, COM1A1, COM1B0, COM1B1>,
        os::timer::tccrb_16bit <0x81, CS10, CS11, CS12, WGM12, WGM13, ICNC1, ICES1>,
        os::timer::tccrc_16bit <0x82, FOC1A, FOC1B>,
        os::timer::tcnt_16bit <0x84>,
        os::timer::ocr_16bit <0x88>,
        os::timer::ocr_16bit <0x8a>,
        os::timer::ocr_16bit <0x8c>,
        os::timer::icr_16bit <0x86>,
        os::timer::timsk_16bit <0x6f, TOIE1, OCIE1A, OCIE1B, ICIE1>,
        os::timer::tifr_16bit <0x36, TOV1, OCF1A, OCF1B, ICF1>
    > timer1_regs;

// TC3
typedef os::mmio::__timer_16bit_regs <
        os::timer::tccra_16bit <0x90, WGM30, WGM31, COM3A0, COM3A1, COM3B0, COM3B1>,
        os::timer::tccrb_16bit <0x91, CS30, CS31, CS32, WGM32, WGM33, ICNC3, ICES3>,
        os::timer::tccrc_16bit <0x92, FOC3A, FOC3B>,
        os::timer::tcnt_16bit <0x94>,
        os::timer::ocr_16bit <0x98>,
        os::timer::ocr_16bit <0x9a>,
        os::timer::ocr_16bit <0x9c>,
        os::timer::icr_16bit <0x96>,
        os::timer::timsk_16bit <0x71, TOIE3, OCIE3A, OCIE3B, ICIE3>,
        os::timer::tifr_16bit <0x38, TOV3, OCF3A, OCF3B, ICF3>
    > timer3_regs;

// TC4
typedef os::mmio::__timer_16bit_regs <
        os::timer::tccra_16bit <0xa0, WGM40, WGM41, COM4A0, COM4A1, COM4B0, COM4B1>,
        os::timer::tccrb_16bit <0xa1, CS40, CS41, CS42, WGM42, WGM43, ICNC4, ICES4>,
        os::timer::tccrc_16bit <0xa2, FOC4A, FOC4B>,
        os::timer::tcnt_16bit <0xa4>,
        os::timer::ocr_16bit <0xa8>,
        os::timer::ocr_16bit <0xaa>,
        os::timer::ocr_16bit <0xac>,
        os::timer::icr_16bit <0xa6>,
        os::timer::timsk_16bit <0x72, TOIE4, OCIE4A, OCIE4B, ICIE4>,
        os::timer::tifr_16bit <0x39, TOV4, OCF4A, OCF4B, ICF4>
    > timer4_regs;

// TC5
typedef os::mmio::__timer_16bit_regs <
        os::timer::tccra_16bit <0x120, WGM50, WGM51, COM5A0, COM5A1, COM5B0, COM5B1>,
        os::timer::tccrb_16bit <0x121, CS50, CS51, CS52, WGM52, WGM53, ICNC5, ICES5>,
        os::timer::tccrc_16bit <0x122, FOC5A, FOC5B>,
        os::timer::tcnt_16bit <0x124>,
        os::timer::ocr_16bit <0x128>,
        os::timer::ocr_16bit <0x12a>,
        os::timer::ocr_16bit <0x12c>,
        os::timer::icr_16bit <0x126>,
        os::timer::timsk_16bit <0x73, TOIE5, OCIE5A, OCIE5B, ICIE5>,
        os::timer::tifr_16bit <0x3a, TOV5, OCF5A, OCF5B, ICF5>
    > timer5_regs;

typedef os::__type_list <timer0_regs, timer2_regs> timer8_list;
typedef os::__type_list <timer1_regs, timer3_regs, timer4_regs, timer5_regs> timer16_list;

#endif //  defined (__AVR_ATmega2560__)


}
}


#endif // OS_TIMER_H_
