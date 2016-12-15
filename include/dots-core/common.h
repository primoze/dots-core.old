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

#ifndef OS_COMMON_H_
#define OS_COMMON_H_

#include <stdint.h>
#include <stdlib.h>

// Quote
#define Q(s) #s

// Declare C linkage
#define OS_C_ABI extern "C"

// Make sure the compiler realy inlines if we say so
#ifdef inline
#	undef inline
#endif // inline

// Force inline
#define OS_INLINE __attribute__((always_inline)) inline
// Pack structs
#define OS_PACKED __attribute__((packed))


typedef uint8_t byte_t;
typedef byte_t* ptr_t;

typedef uint16_t ioaddr_t;

typedef volatile byte_t * const pioreg_t;
typedef volatile byte_t ioreg_t;

typedef volatile uint16_t * const pioreg16_t;
typedef volatile uint16_t const ioreg16_t;

typedef void (*isr_t)(void);

namespace os {

}

#endif // OS_COMMON_H_
