cmake_minimum_required(VERSION 3.30)

project(ArduinoUART VERSION 0.0.1 LANGUAGES C)

set(CMAKE_C_COMPILER			avr-gcc)
set(CMAKE_C_STANDARD			17)
set(CMAKE_C_STANDARD_REQUIRED	True)
set(C_EXTENSIONS				ON)

add_library(uart STATIC uart.c)
target_compile_options(uart PUBLIC
	-Wall
	-Wextra
	-Werror
	-Os
)

target_include_directories(uart PUBLIC ./)

### Developemnt options
option(UART_DEV OFF)
if(UART_DEV)
	set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

	target_link_options(uart PUBLIC
		-mmcu=atmega328p
	)
	target_compile_options(uart PUBLIC
		-mmcu=atmega328p
	)

	target_compile_definitions(uart PUBLIC
		F_CPU=16000000UL
		BAUD=9600UL
		UART_TRAILING_NEWLINE
	)

	add_executable(uart_example.elf uart_example.c)
	target_link_libraries(uart_example.elf uart)

	add_custom_target(hex ALL
		avr-objcopy
		-S
		-R .eeprom
		-O ihex
		uart_example.elf
		uart_example.hex
		DEPENDS uart_example.elf
	)

	add_custom_target(upload
		avrdude
		-c arduino					# Programmer
		-p atmega328p				# MCU
		-U flash:w:uart_example.hex
		-P /dev/ttyUSB0
		-v -v
		DEPENDS hex
	)
endif()
