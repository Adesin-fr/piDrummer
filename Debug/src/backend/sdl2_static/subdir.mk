################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/backend/sdl2_static/soloud_sdl2_static.cpp 

OBJS += \
./src/backend/sdl2_static/soloud_sdl2_static.o 

CPP_DEPS += \
./src/backend/sdl2_static/soloud_sdl2_static.d 


# Each subdirectory must supply rules for building sources it contributes
src/backend/sdl2_static/%.o: ../src/backend/sdl2_static/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	gcc -DWITH_ALSA -I/home/ludovic/Software/Workspace-cpp/urDrummer/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


