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

#ifndef OS_BITS_H
#define OS_BITS_H

#include <dots-core/common.h>
#include <avr/io.h>

namespace os {

// Get bit 'bit' of 't'.
template <typename T>
OS_INLINE bool get_bit(T& t, byte_t bit);

template <typename T>
bool get_bit(T& t, byte_t bit) {
    return t & (T)_BV(bit);
}

// Get 'mask' << 'bit' of 't'
template <typename T, typename U>
OS_INLINE T get_mask(T& t, const U& mask, byte_t bit, bool shift = true);

template <typename T, typename U>
T get_mask(T& t, const U& mask, byte_t bit, bool shift) {
    T ret = t & (T)(mask << bit);
    return shift ? (T)(ret >> bit) : ret;
}


// Set bit 'bit' of 't'.
template <typename T>
OS_INLINE void set_bit(T& t, byte_t bit);

template <typename T>
void set_bit(T& t, byte_t bit) {
  t |= (T)_BV(bit);
}


// Mask 't' with 'mask' << 'bit'
template <typename T, typename U>
OS_INLINE void set_mask(T& t, const U& mask, byte_t bit);

template <typename T, typename U>
void set_mask(T& t, const U& mask, byte_t bit) {
  t |= (T)(mask << bit);
}



// Clear bit 'bit' of 't'.
template <typename T>
OS_INLINE void clear_bit(T& t, byte_t bit);

template <typename T>
void clear_bit(T& t, byte_t bit) {
  t &= (T)~_BV(bit);
}

// Unmask 't' with 'mask' << 't'
template <typename T, typename U>
OS_INLINE void clear_mask(T& t, const U& mask, byte_t bit);

template <typename T, typename U>
void clear_mask(T& t, const U& mask, byte_t bit) {
      t &= (T)~(mask << bit);
}

}




#endif // OS_BITS_H
