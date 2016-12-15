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


namespace os {
namespace timer {

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
class timer_16bit {
public:
    timer_16bit() :
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
