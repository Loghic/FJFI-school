## To run
```
mkdir -p build && cd build && cmake .. && cmake --build .
```
and then just run ./space_invaders which will be crated in build folder

## to create "compile_commands.json"
Useful when you want to edit .cpp or .hpp files, so your editor would have
reference for the existing files.

Must be run from build directory

```
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON .
```
