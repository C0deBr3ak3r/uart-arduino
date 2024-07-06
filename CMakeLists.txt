cmake_minimum_required(VERSION 3.30)

set(PROJECT_VERSION	0.0.1)
project(ArduinoUART VERSION ${PROJECT_VERSION} LANGUAGES C)

set(LIBNAME	uart)
set(EXNAME	uart_example)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_C_COMPILER			avr-gcc)
set(CMAKE_C_STANDARD			17)
set(CMAKE_C_STANDARD_REQUIRED	True)
set(C_EXTENSIONS				ON)

set(ARDUINO_BOARD			uno)
set(ARDUINO_MICROCONTROLER	atmega328p)
set(ARDUINO_BAUD_RATE		11520)
set(ARDUINO_FREQUENCY		16000000)
set(ARDUINO_PROGRAMMER		arduino)
set(ARDUINO_BOARD_PORT		/dev/ttyUSB0)

add_compile_options(
	-Wall
	-Wextra
	-Werror
	-Os
	-DF_CPU=${ARDUINO_FREQUENCY}UL
	-DBAUD=${ARDUINO_BAUD_RATE}UL
	-mmcu=${ARDUINO_MICROCONTROLER}
	-DUART_TRAILING_NEWLINE
)

add_link_options(
	-mmcu=${ARDUINO_MICROCONTROLER}
)

add_library(${LIBNAME} STATIC src/uart.c)

add_executable(${EXNAME}.elf src/uart_example.c)
target_link_libraries(${EXNAME}.elf ${LIBNAME})

add_custom_target(hex ALL
	avr-objcopy
	-S
	-R .eeprom
	-O ihex
	${EXNAME}.elf
	${EXNAME}.hex
	DEPENDS ${EXNAME}.elf
)

add_custom_target(upload
	avrdude
	-c ${ARDUINO_PROGRAMMER}
	-p ${ARDUINO_MICROCONTROLER}
	-U flash:w:${EXNAME}.hex
	-P ${ARDUINO_BOARD_PORT}
	DEPENDS hex
)
