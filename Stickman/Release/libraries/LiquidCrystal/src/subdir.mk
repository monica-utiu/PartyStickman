################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
C:\Users\monic\Downloads\V4.4.1_win64.2022-09-05_06-48-31\Sloeber\arduinoPlugin\libraries\LiquidCrystal\1.0.7\src\LiquidCrystal.cpp 

LINK_OBJ += \
.\libraries\LiquidCrystal\src\LiquidCrystal.cpp.o 

CPP_DEPS += \
.\libraries\LiquidCrystal\src\LiquidCrystal.cpp.d 


# Each subdirectory must supply rules for building sources it contributes
libraries\LiquidCrystal\src\LiquidCrystal.cpp.o: C:\Users\monic\Downloads\V4.4.1_win64.2022-09-05_06-48-31\Sloeber\arduinoPlugin\libraries\LiquidCrystal\1.0.7\src\LiquidCrystal.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:\Users\monic\Downloads\V4.4.1_win64.2022-09-05_06-48-31\Sloeber\arduinoPlugin\packages\arduino\tools\avr-gcc\7.3.0-atmel3.6.1-arduino7/bin/avr-g++" -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10812 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR     -I"C:\Users\monic\Downloads\V4.4.1_win64.2022-09-05_06-48-31\Sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.8.6\cores\arduino" -I"C:\Users\monic\Downloads\V4.4.1_win64.2022-09-05_06-48-31\Sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.8.6\variants\standard" -I"C:\Users\monic\Downloads\V4.4.1_win64.2022-09-05_06-48-31\Sloeber\arduinoPlugin\libraries\LiquidCrystal\1.0.7\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"   -o "$@"
	@echo 'Finished building: $<'
	@echo ' '


