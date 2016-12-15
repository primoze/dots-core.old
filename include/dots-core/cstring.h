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

#ifndef OS_CSTRING_H_
#define OS_CSTRING_H_

#include <avr/pgmspace.h>
#include <dots-core/common.h>

namespace os {

typedef const char* cstring_t;

class __flash_cstring_t;
typedef const __flash_cstring_t* flash_cstring_t;

#define OS_MK_FSTR(str) reinterpret_cast<os::flash_cstring_t>(PSTR(str))
#define OS_FSTR(str) reinterpret_cast<os::flash_cstring_t>(str)

template <size_t _sz>
OS_INLINE os::flash_cstring_t fstr_cast(const char str[_sz]) {
    return OS_FSTR(str);
}

OS_INLINE os::flash_cstring_t fstr_cast(os::cstring_t str) {
    return OS_FSTR(str);
}




}

#endif // OS_CSTRING_H_
