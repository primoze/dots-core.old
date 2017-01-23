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

#ifndef OS_CORE_REGS_H_
#define OS_CORE_REGS_H_


#include <dots-core/common.h>


namespace os {
namespace regs {


template <ioaddr_t _addr>
struct __io_reg {
    static constexpr ioaddr_t addr = _addr;
};



}
}



#endif // OS_CORE_REGS_H_
