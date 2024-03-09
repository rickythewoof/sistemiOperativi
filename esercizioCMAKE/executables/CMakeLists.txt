# TODO compile executable that will be run  
add_executable(${PROJECT_NAME} many_object_in_stack_example.cpp)

# Link libraries of core_library inside src
target_link_libraries(${PROJECT_NAME} core_library)