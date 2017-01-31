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


/**
 * Contains common definitions used throughout the code.
 */

#include <stdint.h>
#include <stdlib.h>

/// Quote a token
#define Q(s) #s

/// Declare C linkage
#define OS_C_ABI extern "C"

#define OS_NO_RETURN __attribute__((noreturn))

/// Make sure the compiler really takes the hint if we say so.
#ifdef inline
#	undef inline
#endif // inline

/// Force inline
#define OS_INLINE __attribute__((always_inline)) inline
/// Pack structs
#define OS_PACKED __attribute__((packed))

/// A byte
typedef uint8_t byte_t;
/// A pointer
typedef byte_t* ptr_t;

/// A native int
typedef int int_t;
/// A native unsigned int
typedef unsigned int uint_t;

/// An io-mapped address
typedef uint16_t ioaddr_t;

/// A memory-mapped 8bit register address
typedef volatile byte_t * const pioreg_t;

/// A memory mapped 16bit register address
typedef volatile uint16_t * const pioreg16_t;

/// An insterrupt service routine
typedef void (*isr_t)(void);

namespace os {

}

#endif // OS_COMMON_H_
