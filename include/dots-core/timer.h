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
#include <avr/interrupt.h>

#include <dots-core/common.h>
#include <dots-core/bits.h>
#include <dots-core/mmio.h>

namespace os {
namespace timer {


/**
 * Timer mode.
 */
enum class mode : byte_t {
    normal, ctc, fast_pwm, pc_pwm, pfc_pwm
};


template <
        byte_t _wgm0,
        byte_t _wgm1,
        byte_t _wgm2,
        byte_t _coma0,
        byte_t _coma1,
        byte_t _comb0,
        byte_t _comb1,
        byte_t _cs0,
        byte_t _cs1,
        byte_t _cs2,
        byte_t _foca,
        byte_t _focb,
        byte_t _toie,
        byte_t _ocfa,
        byte_t _ocfb,
        byte_t _tov
    >
struct __timer_bits {
    static constexpr byte_t wgm0 = _wgm0;
    static constexpr byte_t wgm1 = _wgm1;
    static constexpr byte_t wgm2 = _wgm2;

    static constexpr byte_t coma1 = _coma0;
    static constexpr byte_t coma0 = _coma1;

    static constexpr byte_t comb0 = _comb0;
    static constexpr byte_t comb1 = _comb1;

    static constexpr byte_t cs0 = _cs0;
    static constexpr byte_t cs1 = _cs1;
    static constexpr byte_t cs2 = _cs2;

    static constexpr byte_t foca = _foca;
    static constexpr byte_t focb = _focb;

    static constexpr byte_t toie = _toie;
    static constexpr byte_t ocfa = _ocfa;
    static constexpr byte_t ocfb = _ocfb;
    static constexpr byte_t tov = _tov;
};

/**
 * 8bit Timer/Counter registers and bits.
 */
template <
        class _timer_8bit_regs,
        byte_t _wgm0,
        byte_t _wgm1,
        byte_t _wgm2,
        byte_t _coma0,
        byte_t _coma1,
        byte_t _comb0,
        byte_t _comb1,
        byte_t _cs0,
        byte_t _cs1,
        byte_t _cs2,
        byte_t _foca,
        byte_t _focb,
        byte_t _toie,
        byte_t _ocfa,
        byte_t _ocfb,
        byte_t _tov
    >
struct timer_8bit : public __timer_bits <_wgm0, _wgm1, _wgm2, _coma0, _coma1, _comb0, _comb1, _cs0, _cs1, _cs2, _foca, _focb, _toie, _ocfa, _ocfb, _tov>, public _timer_8bit_regs {
    static constexpr uint32_t resolution = 0x100;
};


typedef os::timer::timer_8bit<os::mmio::timer_0, WGM00, WGM01, WGM02, COM0A0, COM0A1, COM0B0, COM0B1, CS00, CS01, CS02, FOC0A, FOC0B, TOIE0, OCF0A, OCF0B, TOV0> timer0;
typedef os::timer::timer_8bit<os::mmio::timer_2, WGM20, WGM21, WGM22, COM2A0, COM2A1, COM2B0, COM2B1, CS20, CS21, CS22, FOC2A, FOC2B, TOIE2, OCF2A, OCF2B, TOV2> timer2;


/**
 * 16bit Timer/Counter registers and bits.
 */
template <
        class _timer_16bit_regs,
        byte_t _wgm0,
        byte_t _wgm1,
        byte_t _wgm2,
        byte_t _wgm3,
        byte_t _coma0,
        byte_t _coma1,
        byte_t _comb0,
        byte_t _comb1,
        byte_t _cs0,
        byte_t _cs1,
        byte_t _cs2,
        byte_t _icnc,
        byte_t _ices,
        byte_t _foca,
        byte_t _focb,
        byte_t _toie,
        byte_t _ocfa,
        byte_t _ocfb,
        byte_t _tov
    >
struct timer_16bit : public __timer_bits <_wgm0, _wgm1, _wgm2, _coma0, _coma1, _comb0, _comb1, _cs0, _cs1, _cs2, _foca, _focb, _toie, _ocfa, _ocfb, _tov>, public _timer_16bit_regs {
    static constexpr uint32_t resolution = 0x10000;

    static constexpr byte_t wgm3 = _wgm3;
    static constexpr byte_t icnc = _icnc;
    static constexpr byte_t ices = _ices;
};

typedef os::timer::timer_16bit<os::mmio::timer_1, WGM10, WGM11, WGM12, WGM13, COM1A0, COM1A1, COM1B0, COM1B1, CS10, CS11, CS12, ICNC1, ICES1, FOC1A, FOC1B, TOIE1, OCF1A, OCF1B, TOV1> timer1;


constexpr uint32_t TIMER_8 = 0x100;
constexpr uint32_t TIMER_16 = 0x10000;

// class timer_contract {
//     bool init(uint32_t)
//     isr_t set_handler(isr_t);
//     bool enable()
//     void disable()
//     uint32_t get_us;
//     void tick();
// };

template <ioaddr_t _base, ioaddr_t _timsk>
class timer_16bit2 {
public:
    timer_16bit2() :
        tccra(&_MMIO_BYTE(_base + TCCRA)),
        tccrb(&_MMIO_BYTE(_base + TCCRB)),
        ticr(&_MMIO_WORD(_base + TICR)),
        timsk(&_MMIO_BYTE(_timsk)),
        isr(0)
    { }

    bool init(uint32_t us) {
        if(!us) {
            return false;
        }

        disable();
        get_config(us);
        return enable();
    }

    OS_INLINE isr_t set_handler(isr_t i) {
        isr_t ret = isr;
        isr = i;
        return ret;
    }

    OS_INLINE bool enable() {
        if(!config.us) {
            return false;
        }
        ICR1 = config.top;
        // Set prescaler bits and enable P&F Correct mode
        *tccrb = _BV(WGM3) | config.prescaler_bits;
        *timsk = _BV(TOIE);
        return true;
    }

    OS_INLINE void disable() {
        *timsk = 0;
        *tccrb = 0;
        *tccra = 0;
    }

    OS_INLINE uint32_t get_us() {
        return config.us;
    }

    OS_INLINE void tick() {
        if(isr) {
            isr();
        }
    }

private:
    void get_config(uint32_t us) {
        const uint32_t cycles = (F_CPU / 2000000) * us;
        config.us = us;
        if (cycles < RESOLUTION) {
            config.prescaler_bits = _BV(CS0);
            config.top = (uint16_t)cycles;
        } else if (cycles < RESOLUTION * 8) {
            config.prescaler_bits = _BV(CS1);
            config.top = (uint16_t)(cycles / 8);
        } else if (cycles < RESOLUTION * 64) {
            config.prescaler_bits = _BV(CS1) | _BV(CS0);
            config.top = (uint16_t)(cycles / 64);
        } else if (cycles < RESOLUTION * 256) {
            config.prescaler_bits = _BV(CS2);
            config.top = (uint16_t)(cycles / 256);
        } else if (cycles < RESOLUTION * 1024) {
            config.prescaler_bits = _BV(CS2) | _BV(CS0);
            config.top = (uint16_t)(cycles / 1024);
        } else {
            config.prescaler_bits = _BV(CS2) | _BV(CS0);
            config.top = RESOLUTION - 1;
        }
    }

private:
    struct {
        uint32_t us = 0;
        uint8_t prescaler_bits = 0;
        uint16_t top = 0;
    } config;

    pioreg_t tccra;
    pioreg_t tccrb;
    pioreg16_t ticr;
    pioreg_t timsk;

    isr_t isr;

private:
    static constexpr byte_t TCCRA = 0;
    static constexpr byte_t TCCRB = 1;
    static constexpr byte_t TICR = 6;

    static constexpr byte_t WGM3 = WGM13;
    static constexpr byte_t CS0 = CS10;
    static constexpr byte_t CS1 = CS11;
    static constexpr byte_t CS2 = CS12;
    static constexpr byte_t TOIE = TOIE1;

    static constexpr uint32_t RESOLUTION = os::timer::TIMER_16;
};


}
}


#endif // OS_TIMER_H_
