################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/filter/soloud_bassboostfilter.cpp \
../src/filter/soloud_biquadresonantfilter.cpp \
../src/filter/soloud_dcremovalfilter.cpp \
../src/filter/soloud_echofilter.cpp \
../src/filter/soloud_fftfilter.cpp \
../src/filter/soloud_flangerfilter.cpp \
../src/filter/soloud_lofifilter.cpp 

OBJS += \
./src/filter/soloud_bassboostfilter.o \
./src/filter/soloud_biquadresonantfilter.o \
./src/filter/soloud_dcremovalfilter.o \
./src/filter/soloud_echofilter.o \
./src/filter/soloud_fftfilter.o \
./src/filter/soloud_flangerfilter.o \
./src/filter/soloud_lofifilter.o 

CPP_DEPS += \
./src/filter/soloud_bassboostfilter.d \
./src/filter/soloud_biquadresonantfilter.d \
./src/filter/soloud_dcremovalfilter.d \
./src/filter/soloud_echofilter.d \
./src/filter/soloud_fftfilter.d \
./src/filter/soloud_flangerfilter.d \
./src/filter/soloud_lofifilter.d 


# Each subdirectory must supply rules for building sources it contributes
src/filter/%.o: ../src/filter/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	gcc -DWITH_ALSA -I/home/ludovic/Software/Workspace-cpp/urDrummer/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


