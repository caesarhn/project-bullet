# how to build
## on windows
enter the build folder: 'cd build'
execute CMakeList.txt: 'cmake ..'
build the code: 'cmake --build .'

# Compile shader with glslang
example for compiling vertex shader
command: 'glslang -V shader.vert -o vert.spv' or
command: 'glslangValidator -V shaders/shader.frag -o shaders/frag.spv'

# Build on Android

## setup
1. Make folder structure for android
2. run 'gradle wrapper'
3. make build script

## build
run build_android.sh command: './build_android.sh'
