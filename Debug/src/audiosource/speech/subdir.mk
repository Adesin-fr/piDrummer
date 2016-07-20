################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/audiosource/speech/darray.cpp \
../src/audiosource/speech/klatt.cpp \
../src/audiosource/speech/resonator.cpp \
../src/audiosource/speech/soloud_speech.cpp \
../src/audiosource/speech/tts.cpp 

OBJS += \
./src/audiosource/speech/darray.o \
./src/audiosource/speech/klatt.o \
./src/audiosource/speech/resonator.o \
./src/audiosource/speech/soloud_speech.o \
./src/audiosource/speech/tts.o 

CPP_DEPS += \
./src/audiosource/speech/darray.d \
./src/audiosource/speech/klatt.d \
./src/audiosource/speech/resonator.d \
./src/audiosource/speech/soloud_speech.d \
./src/audiosource/speech/tts.d 


# Each subdirectory must supply rules for building sources it contributes
src/audiosource/speech/%.o: ../src/audiosource/speech/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DWITH_ALSA -I/home/ludovic/Software/Workspace-cpp/urDrummer/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


