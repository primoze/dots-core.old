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

#ifndef OS_CORE_META_H_
#define OS_CORE_META_H_


#include <dots-core/common.h>

namespace os {

/**
 * A generic integral constant
 */
template <typename T, T _val>
struct __integral_constant
{
    static constexpr T value = _val;
    typedef T value_type;
    typedef __integral_constant type;
};

/**
 * Boolean true
 */
typedef __integral_constant<bool, false> false_type;

/**
 * Boolean false
 */
typedef __integral_constant<bool, true> true_type;

/**
 * Logical not operator
 */
template <bool _val>
struct __not : public false_type { };

template <>
struct __not<false> : public true_type { };

/**
 * Compile-time if
 */
template <bool _val>
struct __if : public false_type { };

template <>
struct __if<true> : public true_type { };

/**
 * Conditional compile-time type declaration.
 */
template <bool _val, typename _result>
struct __enable : public false_type {
};

template <typename _result>
struct __enable<true, _result> : public true_type {
    typedef _result result;
};

/**
 * Check if two types are the same
 */
template <typename T, typename U>
struct __same_type : public false_type {
};

template <typename T>
struct __same_type<T, T> : public true_type { };

/**
 * Check if two types are different
 */
template <typename T, typename U>
using __different_type = __not<__same_type<T, U>::value>;

/**
 * A pair of types
 */
template <typename _first, typename _second>
struct __pair {
    typedef _first first;
    typedef _second second;
};

/**
 * A list of types, with a head and a non-empty tail
 */
template <typename _head, typename... _types>
struct __type_list {
    typedef _head head;
    typedef __type_list<_types...> tail;

    static constexpr byte_t size = 1 + tail::size;
};

/**
 * A singleton list of types. Has a void tail
 */
template <typename _type>
struct __type_list<_type> {
    typedef _type head;
    typedef void tail;

    static constexpr byte_t size = 1;
};

/**
 * Get the n-th element of a type list
 */
template <byte_t _n, class _type_list>
struct __nth {
    typedef typename __nth <_n-1, typename _type_list::tail>::result result;
};

template <class _type_list>
struct __nth <0, _type_list> {
    typedef typename _type_list::head result;
};

/**
 * Define the result of a lookup, or continue searching through the list
 */
template <byte_t _n, bool _cmp, typename _key, typename _result, class _pair_list>
struct __lookup_ex;

/**
 * A match has been found. Define the result.
 */
template <byte_t _n, typename _key, typename _result, class _pair_list>
struct __lookup_ex <_n, true, _key, _result, _pair_list> {
    typedef _result result;
};

/**
 * Terminating condition: try to match the last element of the list.
 */
template <typename _key, typename _result, class _pair_list>
struct __lookup_ex <1, false, _key, _result, _pair_list> {
    typedef typename _pair_list::head head;

    typedef typename os::__enable <os::__same_type<typename head::first, _key>::value, typename head::second>::result result;
};

/**
 * Normal case: try to match the next element in the list.
 */
template <byte_t _n, typename _key, typename _result, class _pair_list>
struct __lookup_ex <_n, false, _key, _result, _pair_list> {

    typedef typename _pair_list::head head;
    typedef typename _pair_list::tail tail;

    typedef typename __lookup_ex <
            tail::size,
            __same_type <typename head::first, _key>::value,
            _key,
            typename head::second,
            tail
        >::result result;
};

/**
 * Lookup a value under a key in a list of pairs.
 */
template <typename _key, class _pair_list>
struct __lookup {
    typedef typename __lookup_ex <
            _pair_list::size,
            false,
            _key,
            typename _pair_list::head::second,
            _pair_list
        >::result result;
};

}


#endif // OS_CORE_META_H_
