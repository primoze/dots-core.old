# dots-core
Generic core definitions for Arduino

## Overview
The library is a set of template definitions which can be instantiated on a specific platform.

### Timer (16 bit)
```cpp
// timer is parametrized by the base address of its IO registers
// and the address of its interrupt mask register.
template <ioaddr_t _base, ioaddr_t _timsk>
class timer_16bit {
...
```
### Serial
```cpp
// usart is parametrized by the base address of its IO registers.
// An usart writer implementation for stream is also provided.
template <ioaddr_t _base>
class usart {
...
```
### Stream
```cpp
// stream is parametrized by a writer class, and a writer base class. The writer
// must provide a bool write(byte_t) method, while the writer base class provides
// an int write(byte_t*, size_t) method. The writer_base default template argument
// provides one. Provide a different implementation to change the default behaviour.
template <class _writer, template <typename> class _base = writer_base>
class stream {
public:
...
```

## Usage
```cpp

#include <dots-core/usart.h>
#include <dots-core/timer.h>
#include <dots-core/stream.h>

#if defined (__AVR_ATmega328P__)

typedef os::timer::timer_16bit<0x80, 0x6f> timer1_t;
extern timer1_t timer1;

typedef os::usart::usart<0xc0> usart0_t;
typedef os::usart::writer<usart0_t> usart0_writer_t;
typedef os::io::stream<usart0_writer_t> stdout_t;

extern stdout_t stdout;

#endif // __AVR_ATmega328P__
```
