################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/audiosource/tedsid/sid.cpp \
../src/audiosource/tedsid/soloud_tedsid.cpp \
../src/audiosource/tedsid/ted.cpp 

OBJS += \
./src/audiosource/tedsid/sid.o \
./src/audiosource/tedsid/soloud_tedsid.o \
./src/audiosource/tedsid/ted.o 

CPP_DEPS += \
./src/audiosource/tedsid/sid.d \
./src/audiosource/tedsid/soloud_tedsid.d \
./src/audiosource/tedsid/ted.d 


# Each subdirectory must supply rules for building sources it contributes
src/audiosource/tedsid/%.o: ../src/audiosource/tedsid/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	gcc -DWITH_ALSA -I/home/ludovic/Software/Workspace-cpp/urDrummer/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


