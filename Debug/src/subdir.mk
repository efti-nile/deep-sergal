################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/DeepSergal.cpp \
../src/main.cpp 

OBJS += \
./src/DeepSergal.o \
./src/main.o 

CPP_DEPS += \
./src/DeepSergal.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D_GLIBCXX_USE_CXX11_ABI=0 -DUSE_OPENCV -I/home/cristopher/workspace/caffe/distribute/include -I/usr/include/ -O0 -g3 -Wall -c -fmessage-length=0 -lboost_system -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/main.o: ../src/main.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D_GLIBCXX_USE_CXX11_ABI=0 -DUSE_OPENCV -I/home/cristopher/workspace/caffe/distribute/include -I/usr/include/ -O0 -g3 -Wall -c -fmessage-length=0 -lboost_system -MMD -MP -MF"$(@:%.o=%.d)" -MT"src/main.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


