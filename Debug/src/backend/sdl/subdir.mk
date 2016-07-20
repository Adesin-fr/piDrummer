################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/backend/sdl/soloud_sdl.cpp 

C_SRCS += \
../src/backend/sdl/soloud_sdl_dll.c 

OBJS += \
./src/backend/sdl/soloud_sdl.o \
./src/backend/sdl/soloud_sdl_dll.o 

CPP_DEPS += \
./src/backend/sdl/soloud_sdl.d 

C_DEPS += \
./src/backend/sdl/soloud_sdl_dll.d 


# Each subdirectory must supply rules for building sources it contributes
src/backend/sdl/%.o: ../src/backend/sdl/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DWITH_ALSA -I/home/ludovic/Software/Workspace-cpp/urDrummer/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/backend/sdl/%.o: ../src/backend/sdl/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


