cmake_minimum_required(VERSION 3.30)

set(PRODUCT_NAME uart_example)
set(PROJECT_VERSION	0.0.1)
project(ArduinoUART VERSION ${PROJECT_VERSION} LANGUAGES C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_C_COMPILER			avr-gcc)
set(CMAKE_C_STANDARD			17)
set(CMAKE_C_STANDARD_REQUIRED	True)
set(C_EXTENSIONS				OFF)

set(ARDUINO_BOARD			uno)
set(ARDUINO_MICROCONTROLER	atmega328p)
set(ARDUINO_BAUD_RATE		115200)
set(ARDUINO_FREQUENCY		16000000)
set(ARDUINO_PROGRAMMER		arduino)
set(ARDUINO_BOARD_PORT		/dev/ttyUSB0)

add_compile_options(
	-mmcu=${ARDUINO_MICROCONTROLER}
	-pedantic
	-Wall
	-Wextra
	-Werror
	-Os
	-funsigned-char
	-funsigned-bitfields
	-DF_CPU=${ARDUINO_FREQUENCY}UL
)

set(C_SOURCES
	src/main.c
)


add_executable(${PRODUCT_NAME}.elf ${C_SOURCES})

add_custom_target(strip ALL avr-strip ${PRODUCT_NAME}.elf -o ${PRODUCT_NAME}_stripped.elf DEPENDS ${PRODUCT_NAME}.elf)
add_custom_target(hex ALL avr-objcopy -R .eeprom -O ihex ${PRODUCT_NAME}_stripped.elf ${PRODUCT_NAME}.hex DEPENDS strip)
add_custom_target(eeprom ALL avr-objcopy -j .eeprom -O ihex ${PRODUCT_NAME}_stripped.elf ${PRODUCT_NAME}.eep DEPENDS strip)

add_custom_target(upload avrdude -c ${ARDUINO_PROGRAMMER} -p ${ARDUINO_MICROCONTROLER} -U flash:w:${PRODUCT_NAME}.hex -P ${ARDUINO_BOARD_PORT} DEPENDS hex)
add_custom_target(upload-eeprom avrdude -c ${ARDUINO_PROGRAMMER} -p ${ARDUINO_MICROCONTROLER} -U eeprom:w:${PRODUCT_NAME}.eep -P ${ARDUINO_BOARD_PORT} DEPENDS eeprom)
