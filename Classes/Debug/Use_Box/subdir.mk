################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Use_Box/GLES-Render.cpp \
../Use_Box/UseBox.cpp 

OBJS += \
./Use_Box/GLES-Render.o \
./Use_Box/UseBox.o 

CPP_DEPS += \
./Use_Box/GLES-Render.d \
./Use_Box/UseBox.d 


# Each subdirectory must supply rules for building sources it contributes
Use_Box/%.o: ../Use_Box/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


