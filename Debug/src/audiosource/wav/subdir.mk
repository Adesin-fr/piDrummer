################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/audiosource/wav/soloud_wav.cpp \
../src/audiosource/wav/soloud_wavstream.cpp 

C_SRCS += \
../src/audiosource/wav/stb_vorbis.c 

OBJS += \
./src/audiosource/wav/soloud_wav.o \
./src/audiosource/wav/soloud_wavstream.o \
./src/audiosource/wav/stb_vorbis.o 

CPP_DEPS += \
./src/audiosource/wav/soloud_wav.d \
./src/audiosource/wav/soloud_wavstream.d 

C_DEPS += \
./src/audiosource/wav/stb_vorbis.d 


# Each subdirectory must supply rules for building sources it contributes
src/audiosource/wav/%.o: ../src/audiosource/wav/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DWITH_ALSA -I/home/ludovic/Software/Workspace-cpp/urDrummer/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/audiosource/wav/stb_vorbis.o: ../src/audiosource/wav/stb_vorbis.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I/home/ludovic/Software/Workspace-cpp/urDrummer/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"src/audiosource/wav/stb_vorbis.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


