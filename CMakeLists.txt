cmake_minimum_required(VERSION 3.27.4)
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")
project(nyctalis)

#add_subdirectory(standard)
add_subdirectory(veil)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/output)

file(COPY ${CMAKE_SOURCE_DIR}/fakeroot/ DESTINATION ${EXECUTABLE_OUTPUT_PATH}/x86_64/)

add_custom_target(create_folders
  COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_SOURCE_DIR}/dist/x86_64
)

add_custom_target(create_iso ALL
  DEPENDS create_folders
  COMMAND grub-mkrescue /usr/lib/grub/i386-pc -o ${CMAKE_SOURCE_DIR}/dist/x86_64/nyctalis.iso ${EXECUTABLE_OUTPUT_PATH}/x86_64
)

add_custom_command(
  TARGET create_iso
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E echo "Creating ISO..."
)
