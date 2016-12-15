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

#ifndef OS_ARRAY_H_
#define OS_ARRAY_H_

#include <dots-core/common.h>


namespace os {
namespace util {


template <typename T>
class func_types {
public:
    typedef void(*ctor_t)(T& t);
    typedef void(*iter_t)(T& t);
};


template <typename T, size_t _sz>
class array {
public:
    typedef typename func_types<T>::ctor_t ctor_t;
    typedef typename func_types<T>::iter_t iter_t;

    array() : ctor(0) { }
    array(ctor_t c) :
        ctor(c)
    {
        for_each(ctor);
    }

    void for_each(iter_t it) {
        for(size_t i=0; i<_sz; ++i) {
            it(store[i]);
        }
    }

    OS_INLINE T& operator[] (size_t n) {
        return store[n];
    }

    OS_INLINE size_t size() {
        return _sz;
    }

    static constexpr size_t SIZE = _sz;

private:
    T store[_sz];
    ctor_t ctor;
};


}
}


#endif // OS_ARRAY_H_
