A UART library for ATmega328P based boards

### Usage

To use as a library with CMake you can follow this code snippet

```cmake
include(FetchContent)
FetchContent_Declare(
	uart-lib
	GIT_REPOSITORY	/home/moon/Projects/arduino/test/
	GIT_TAG			master
)
FetchContent_MakeAvailable(uart-lib)

target_compile_options(uart PUBLIC
	-mmcu=atmega328p
)
target_link_options(uart PUBLIC
	-mmcu=atmega328p
)
target_compile_definitions(uart PUBLIC
	F_CPU=16000000UL
	BAUD=11520UL
	UART_TRAILING_NEWLINE   # Optional
)
```

You must specify everything on the snippet besides `UART_TRAILING_NEWLINE`
