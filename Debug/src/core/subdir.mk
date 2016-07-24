################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/core/soloud.cpp \
../src/core/soloud_audiosource.cpp \
../src/core/soloud_bus.cpp \
../src/core/soloud_core_3d.cpp \
../src/core/soloud_core_basicops.cpp \
../src/core/soloud_core_faderops.cpp \
../src/core/soloud_core_filterops.cpp \
../src/core/soloud_core_getters.cpp \
../src/core/soloud_core_setters.cpp \
../src/core/soloud_core_voicegroup.cpp \
../src/core/soloud_core_voiceops.cpp \
../src/core/soloud_fader.cpp \
../src/core/soloud_fft.cpp \
../src/core/soloud_fft_lut.cpp \
../src/core/soloud_file.cpp \
../src/core/soloud_filter.cpp \
../src/core/soloud_thread.cpp 

OBJS += \
./src/core/soloud.o \
./src/core/soloud_audiosource.o \
./src/core/soloud_bus.o \
./src/core/soloud_core_3d.o \
./src/core/soloud_core_basicops.o \
./src/core/soloud_core_faderops.o \
./src/core/soloud_core_filterops.o \
./src/core/soloud_core_getters.o \
./src/core/soloud_core_setters.o \
./src/core/soloud_core_voicegroup.o \
./src/core/soloud_core_voiceops.o \
./src/core/soloud_fader.o \
./src/core/soloud_fft.o \
./src/core/soloud_fft_lut.o \
./src/core/soloud_file.o \
./src/core/soloud_filter.o \
./src/core/soloud_thread.o 

CPP_DEPS += \
./src/core/soloud.d \
./src/core/soloud_audiosource.d \
./src/core/soloud_bus.d \
./src/core/soloud_core_3d.d \
./src/core/soloud_core_basicops.d \
./src/core/soloud_core_faderops.d \
./src/core/soloud_core_filterops.d \
./src/core/soloud_core_getters.d \
./src/core/soloud_core_setters.d \
./src/core/soloud_core_voicegroup.d \
./src/core/soloud_core_voiceops.d \
./src/core/soloud_fader.d \
./src/core/soloud_fft.d \
./src/core/soloud_fft_lut.d \
./src/core/soloud_file.d \
./src/core/soloud_filter.d \
./src/core/soloud_thread.d 


# Each subdirectory must supply rules for building sources it contributes
src/core/%.o: ../src/core/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	gcc -DWITH_ALSA -I/home/ludovic/Software/Workspace-cpp/urDrummer/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


