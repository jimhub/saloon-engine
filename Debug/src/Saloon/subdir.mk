################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Saloon/BMFont.cpp \
../src/Saloon/BMFontChar.cpp \
../src/Saloon/Debug.cpp \
../src/Saloon/LTimer.cpp \
../src/Saloon/SDLHelpers.cpp \
../src/Saloon/Saloon.cpp \
../src/Saloon/TiledMap.cpp \
../src/Saloon/TiledMapLayer.cpp \
../src/Saloon/TiledMapTile.cpp \
../src/Saloon/TiledMapTileset.cpp \
../src/Saloon/glHelpers.cpp \
../src/Saloon/tinyxml2.cpp 

OBJS += \
./src/Saloon/BMFont.o \
./src/Saloon/BMFontChar.o \
./src/Saloon/Debug.o \
./src/Saloon/LTimer.o \
./src/Saloon/SDLHelpers.o \
./src/Saloon/Saloon.o \
./src/Saloon/TiledMap.o \
./src/Saloon/TiledMapLayer.o \
./src/Saloon/TiledMapTile.o \
./src/Saloon/TiledMapTileset.o \
./src/Saloon/glHelpers.o \
./src/Saloon/tinyxml2.o 

CPP_DEPS += \
./src/Saloon/BMFont.d \
./src/Saloon/BMFontChar.d \
./src/Saloon/Debug.d \
./src/Saloon/LTimer.d \
./src/Saloon/SDLHelpers.d \
./src/Saloon/Saloon.d \
./src/Saloon/TiledMap.d \
./src/Saloon/TiledMapLayer.d \
./src/Saloon/TiledMapTile.d \
./src/Saloon/TiledMapTileset.d \
./src/Saloon/glHelpers.d \
./src/Saloon/tinyxml2.d 


# Each subdirectory must supply rules for building sources it contributes
src/Saloon/%.o: ../src/Saloon/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


