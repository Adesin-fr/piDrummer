################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/backend/portaudio/soloud_portaudio.cpp 

C_SRCS += \
../src/backend/portaudio/soloud_portaudio_dll.c 

OBJS += \
./src/backend/portaudio/soloud_portaudio.o \
./src/backend/portaudio/soloud_portaudio_dll.o 

CPP_DEPS += \
./src/backend/portaudio/soloud_portaudio.d 

C_DEPS += \
./src/backend/portaudio/soloud_portaudio_dll.d 


# Each subdirectory must supply rules for building sources it contributes
src/backend/portaudio/%.o: ../src/backend/portaudio/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	gcc -DWITH_ALSA -I/home/ludovic/Software/Workspace-cpp/urDrummer/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/backend/portaudio/%.o: ../src/backend/portaudio/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


