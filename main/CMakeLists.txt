add_executable(main main.c)
add_executable(receiver receiver.c)

# pull in common dependencies
target_link_libraries(main pico_stdlib)
target_link_libraries(receiver pico_stdlib)

# create map/bin/hex/uf2 file etc.
pico_add_extra_outputs(main)
pico_add_extra_outputs(receiver)
