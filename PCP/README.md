# Zig Build System for School Projects

Simple build system that automatically compiles all `.c` and `.cpp` files in a specified directory.

## 📁 Project Structure

```
project/
├── build.zig          # Build script
├── build.sh           # Build wrapper with logging (recommended)
├── lesson1/           # Lesson 1
│   ├── ex1/           # Exercise 1
│   │   └── main.cpp
│   └── ex2/           # Exercise 2
│       └── main.cpp
├── lesson2/           # Lesson 2
│   ├── main.c
│   └── utils.c
├── build-logs/        # Error logs (auto-created)
│   ├── lesson1-ex1-20260219-143022.log
│   └── lesson1-ex2-20260219-143145.log
└── zig-out/          # Output binaries (created automatically)
    └── bin/
        ├── lesson1-ex1
        ├── lesson1-ex2
        └── lesson2
```

## 🚀 Basic Usage

### Compilation

```bash
# Compile a specific lesson
zig build -Dlesson=lesson1

# Compile nested subdirectories (exercises)
zig build -Dlesson=lesson1/ex1
zig build -Dlesson=lesson1/ex2

# Default lesson (if no parameter specified)
zig build
```

### With Automatic Error Logging (Recommended)

Use the `build.sh` script for automatic error logging:

```bash
# Make it executable (first time only)
chmod +x build.sh

# Build with logging
./build.sh lesson1/ex1

# Build and run immediately
./build.sh lesson1/ex1 run

# All errors are saved to build-logs/ directory
```

**Features:**
- ✅ Colored output for better readability
- ✅ Automatic error logging to `build-logs/`
- ✅ Shows last 15 lines of errors on failure
- ✅ Displays binary size on success
- ✅ Can run program immediately after build
- ✅ Auto-cleans old logs (keeps last 10)

### Compile and Run

```bash
# Compile and run
zig build run -Dlesson=lesson1

# Run specific exercises
zig build run -Dlesson=lesson1/ex1
zig build run -Dlesson=lesson1/ex2

# Different lessons
zig build run -Dlesson=lesson2
```

### Direct Execution

```bash
# After compilation, run directly
./zig-out/bin/lesson1
./zig-out/bin/lesson1-ex1
./zig-out/bin/lesson1-ex2
```

## 📂 Working with Nested Subdirectories

### Scenario: Multiple exercises per lesson

If you have multiple exercises in one lesson:

```
lesson1/
├── ex1/
│   ├── main.cpp
│   └── helper.cpp
└── ex2/
    ├── main.cpp
    └── utils.cpp
```

**Compile each exercise separately:**

```bash
# Exercise 1
zig build -Dlesson=lesson1/ex1
./zig-out/bin/lesson1-ex1

# Exercise 2
zig build -Dlesson=lesson1/ex2
./zig-out/bin/lesson1-ex2
```

### Important Notes:

- ✅ **Nested paths work:** You can use any subdirectory path
- ✅ **Recursive search:** All `.c`/`.cpp` files in the directory are compiled together
- ⚠️ **Single executable:** All files in a directory compile into ONE program
- 💡 **Separate exercises:** Put each exercise in its own subdirectory

## ⚙️ Advanced Usage

### Compile with Program Arguments

```bash
# Pass arguments to the program (after --)
zig build run -Dlesson=lesson1/ex1 -- arg1 arg2 arg3
```

### Optimization Levels

```bash
# Debug mode (default) - with debugging symbols
zig build -Dlesson=lesson1 -Doptimize=Debug

# Release mode - faster program
zig build -Dlesson=lesson1 -Doptimize=ReleaseFast

# Release with smaller size
zig build -Dlesson=lesson1 -Doptimize=ReleaseSmall
```

### Clean Build Cache

```bash
# Delete build cache and output files
rm -rf .zig-cache/ zig-out/

# Then recompile
zig build -Dlesson=lesson1
```

### View Build Logs

```bash
# List all logs
ls -lt build-logs/

# View latest log
cat build-logs/$(ls -t build-logs/ | head -n1)

# View specific lesson's latest log
cat build-logs/$(ls -t build-logs/ | grep lesson1 | head -n1)

# Search for errors across all logs
grep -r "error:" build-logs/
```

## 📝 Creating New Lessons/Exercises

### Simple lesson structure

```bash
# Create new lesson
mkdir lesson3
touch lesson3/main.cpp

# Compile
zig build -Dlesson=lesson3
```

### Multiple exercises per lesson

```bash
# Create lesson with exercises
mkdir -p lesson3/ex1 lesson3/ex2
touch lesson3/ex1/main.cpp
touch lesson3/ex2/main.cpp

# Compile each exercise
zig build run -Dlesson=lesson3/ex1
zig build run -Dlesson=lesson3/ex2
```

## ✨ Features

- ✅ Automatically finds all `.c`, `.cpp`, `.cc`, `.cxx` files
- ✅ Recursively searches subdirectories
- ✅ Auto-detects C vs C++ and links correct libraries
- ✅ Supports compiler warnings (`-Wall -Wextra`)
- ✅ Easy project switching with `-Dlesson=`
- ✅ Works with nested directory structures

## 🛠️ Supported Languages

### C Files
- `.c` - Standard C files
- Compiles with `-std=c11`
- Links with `libc`

### C++ Files
- `.cpp`, `.cc`, `.cxx` - C++ files
- Compiles with `-std=c++17`
- Links with `libc++` (includes iostream, etc.)

## 🔧 Troubleshooting

### No source files found
```
WARNING: No source files found in lesson1
```
**Solution:** Check that the directory exists and contains `.c` or `.cpp` files.

### Compilation error
```bash
# Clean cache and try again
rm -rf .zig-cache/
zig build -Dlesson=lesson1
```

### Multiple main() functions
If you get "multiple definition of main" error, it means you have multiple files with `main()` in the same directory.

**Solution:** Each exercise should be in its own subdirectory:
```bash
# Wrong - both have main()
lesson1/ex1.cpp
lesson1/ex2.cpp

# Correct - separate directories
lesson1/ex1/main.cpp
lesson1/ex2/main.cpp
```

### Changing C/C++ Standard
Open `build.zig` and modify:
```zig
const std_flag = if (is_cpp) "-std=c++17" else "-std=c11";
```

## 📚 Examples

### Quick workflow for a lesson

```bash
# Create new project with exercises
mkdir -p lesson5/ex1 lesson5/ex2

# Exercise 1
echo '#include <iostream>
int main() { std::cout << "Exercise 1\\n"; }' > lesson5/ex1/main.cpp

# Exercise 2
echo '#include <iostream>
int main() { std::cout << "Exercise 2\\n"; }' > lesson5/ex2/main.cpp

# Build and run with logging
./build.sh lesson5/ex1 run
./build.sh lesson5/ex2 run
```

### Using build.sh vs direct zig build

```bash
# Method 1: Direct zig build (no logging)
zig build run -Dlesson=lesson1/ex1

# Method 2: With build.sh (automatic logging)
./build.sh lesson1/ex1 run

# Check logs later
ls build-logs/
cat build-logs/lesson1-ex1-20260219-143022.log
```

### Compile all lessons/exercises

```bash
# Compile everything
zig build -Dlesson=lesson1/ex1
zig build -Dlesson=lesson1/ex2
zig build -Dlesson=lesson2
zig build -Dlesson=lesson3/ex1

# Run them
./zig-out/bin/lesson1-ex1
./zig-out/bin/lesson1-ex2
./zig-out/bin/lesson2
./zig-out/bin/lesson3-ex1
```

### Batch compilation script

Create `build-all.sh`:
```bash
#!/bin/bash
LESSONS=("lesson1/ex1" "lesson1/ex2" "lesson2" "lesson3/ex1")

echo "🔨 Building all lessons..."
echo ""

SUCCESS=0
FAILED=0

for lesson in "${LESSONS[@]}"; do
    echo "Building $lesson..."
    if ./build.sh "$lesson" > /dev/null 2>&1; then
        echo "  ✅ Success"
        ((SUCCESS++))
    else
        echo "  ❌ Failed - check build-logs/"
        ((FAILED++))
    fi
done

echo ""
echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
echo "📊 Results: $SUCCESS success, $FAILED failed"
echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
```

```bash
chmod +x build-all.sh
./build-all.sh
```

## 💡 Tips

1. **Default lesson:** Change `orelse "hodina1"` in `build.zig` for different default
2. **Shell alias:** Add to `.bashrc` or `.zshrc`:
   ```bash
   alias zb='zig build run -Dlesson='
   # Usage: zb lesson1/ex1
   ```
3. **VSCode:** Add to `tasks.json` for build task:
   ```json
   {
     "label": "Zig Build",
     "type": "shell",
     "command": "zig build run -Dlesson=${input:lesson}",
     "inputs": [{
       "id": "lesson",
       "type": "promptString",
       "description": "Lesson path"
     }]
   }
   ```

## 🎯 Recommended Directory Structure

For school with multiple exercises per lesson:

```
project/
├── build.zig
├── lesson1/
│   ├── ex1/          # Each exercise = separate program
│   │   ├── main.cpp
│   │   └── helper.cpp
│   └── ex2/
│       └── main.cpp
├── lesson2/
│   ├── ex1/
│   │   └── main.c
│   └── ex2/
│       ├── main.c
│       └── utils.c
└── lesson3/
    └── project/      # Final project for the lesson
        ├── main.cpp
        ├── game.cpp
        └── game.h
```

Compile with:
```bash
zig build run -Dlesson=lesson1/ex1
zig build run -Dlesson=lesson2/ex1
zig build run -Dlesson=lesson3/project
```

## 🆘 Help

```bash
# Show available build options
zig build --help

# Verbose output
zig build -Dlesson=lesson1 --verbose

# List all built binaries
ls -lh zig-out/bin/

# View all error logs
ls -lh build-logs/

# Clean everything
rm -rf .zig-cache/ zig-out/ build-logs/
```

---

**Created for:** Zig 0.15.x
**Compatible with:** C11, C++17
**Works with:** Nested directory structures ✅
**Error logging:** Automatic with `build.sh` ✅
