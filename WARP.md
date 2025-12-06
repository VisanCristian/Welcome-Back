# WARP.md

This file provides guidance to WARP (warp.dev) when working with code in this repository.

## Build and run

The project is a C++23 console/SFML project configured with CMake and helper scripts.

### Configure

Use the provided helper script (preferred):

```bash path=null start=null
./scripts/cmake.sh configure -c Debug
```

This is equivalent to:

```bash path=null start=null
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
```

On Windows with Ninja:

```bash path=null start=null
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -G Ninja
```

### Build

Using the helper script:

```bash path=null start=null
./scripts/cmake.sh build -c Debug
```

or directly with CMake:

```bash path=null start=null
cmake --build build --config Debug --parallel 6
```

### Install artifacts

Installs the built executable under `install_dir/bin/` (default):

```bash path=null start=null
./scripts/cmake.sh install -c Debug -i install_dir
# or
cmake --install build --config Debug --prefix install_dir
```

### Run the game

After building, run the main executable (`oop`):

```bash path=null start=null
./build/oop
# or, after install
./install_dir/bin/oop
```

The file `tastatura.txt` contains sample input that can be piped into the executable if needed.

```bash path=null start=null
cat tastatura.txt | ./build/oop
```

## Static analysis and runtime checks

### Cppcheck

The project includes scripts to build and run `cppcheck` locally.

Build a local cppcheck binary (once):

```bash path=null start=null
./scripts/build_cppcheck.sh -b build
```

Run cppcheck using `compile_commands.json` from the CMake build (expects a configured build in `build/`):

```bash path=null start=null
./scripts/run_cppcheck.sh
```

If `compile_commands.json` is missing, reconfigure CMake with export enabled, for example via:

```bash path=null start=null
./scripts/cmake.sh configure -e "-DCMAKE_EXPORT_COMPILE_COMMANDS=ON"
```

### Valgrind

`run_valgrind.sh` wraps valgrind around the built executable.

Non-interactive (feeds `tastatura.txt` to the program by default):

```bash path=null start=null
./scripts/run_valgrind.sh
```

Interactive run:

```bash path=null start=null
RUN_INTERACTIVE=true ./scripts/run_valgrind.sh
```

You can override defaults via environment variables, e.g. `EXECUTABLE_NAME`, `BUILD_DIR`, or by passing a custom binary directory as the first argument.

### CI and linters

GitHub Actions workflow `.github/workflows/cmake.yml` runs:

- `cppcheck` via a custom action
- `clang-tidy` via a custom action
- Multi-platform CMake builds (Linux/macOS/Windows) with optional AddressSanitizer and MemorySanitizer
- Valgrind-based runtime checks on Linux

Local changes should keep the code buildable with CMake and compatible with these CI checks.

## High-level architecture

### Overview

The game models a narrative puzzle experience where a player collects keys by solving randomly assigned puzzles. Core gameplay is text-based for now but in the future, the game will be 2D, where the player is in the room of a hotel, has a computer where he needs to  solve the puzzles and every once in a while, can be attacked by an enemy, which can kill the player if he doesn't respond accordingly for each one.; SFML is already integrated as an external dependency via CMake but is not yet heavily used in the provided sources.

Key mechanics:
- **Puzzles** : Each milestone, the player is presented a series of puzzles that each have their own worth. At the end of the milestone, the player needs to purchase a key in order to continue to the next milestone.
  1. ButtonsInOrder: The player must press the buttons in the correct order based on the number they display.
  2. TagZones: The player must create islands in the presented grid, based on the number of '-1' keys displayed.
- **Killers** : 
  1. Noir : The player needs to stand still and face away from the killer for 10 seconds.
  2. Michael : The player has 7 seconds to hide and then wait for another 5 seconds in order to him to leave.

Key components:

- **Entry point (`main.cpp`)**: Creates a `Player`, a `Computer` bound to that player, then a `gameObject` that orchestrates the game, and calls `game.start()`.
- **Game orchestration (`gameObject`)**:
  - Owns the current `Player` and `Computer` instances and tracks `milestone`, puzzle number, and key price.
  - Encapsulates progression logic: checkpoints, pricing of keys per milestone, game-over and win conditions, and final key generation from collected keys.
  - Currently, `start()` delegates to `Computer::eventLoop` using the current `milestone`.
- **Player state (`Player`)**:
  - Tracks collected per-puzzle keys (`std::vector<std::string>`), total points, and a final aggregated key string.
  - Provides copy semantics, simple getters/setters, and a stream insertion operator for debugging/inspection.
- **Puzzle framework (`Puzzle` and derived classes)**:
  - `Puzzle` is an abstract base class that encapsulates common puzzle data: generated key string, points awarded, puzzle layout, user answer, correct answer, and atomic flags `solved`/`timeUp`.
  - Derived classes implement specific puzzle mechanics and I/O:
    - `buttonsInOrder`: generates a shuffled sequence of digits 0–9, writes the correct order to `rightAnswears.txt`, reads user input, and checks whether the user’s answer matches the stored correct sequence.
    - `tagZones`: generates a 3×3 grid of zones, computes connected components to assign region tags, writes the resulting labels to `rightAnswears.txt`, reads user input, and checks for equality with the computed correct labeling.
  - Both puzzles set their own `points` and `timeLimit` and call the base `generateKey()` to produce a per-puzzle key string.
- **Computer (`Computer`)**:
  - Holds a `Player` copy and a pointer to the currently active `Puzzle`.
  - `generatePuzzle(int milestone)` randomly chooses a specific puzzle type (`buttonsInOrder` or `tagZones`), using the milestone as the puzzle’s time limit.
  - `eventLoop(int milestone)` orchestrates a full puzzle round: generate puzzle, display puzzle, collect user input, check the answer, then award points and a key to the player or terminate the game on failure.
  - `buyKey` and `timerThread` exist as stubs/placeholders, indicating planned support for purchasing keys and time-limited puzzles (potentially using multithreading).
- **Helper utilities (`generated/include/Helper.h`, `generated/src/Helper.cpp`)**:
  - Currently a thin `Helper::help()` stub, wired into CMake as a separate generated module and added as a `SYSTEM` include directory.

### Build system and external libraries

- **CMake configuration**:
  - Top-level `CMakeLists.txt` defines the project and main executable (`oop`), sets `CMAKE_CXX_STANDARD 23`, and includes shared CMake modules under `cmake/`.
  - `Options.cmake` defines common toggles: `WARNINGS_AS_ERRORS`, `USE_ASAN`, `USE_MSAN`, and the install destination directory (`bin`).
  - `CompilerFlags.cmake` applies consistent warning flags and optionally sanitizers via `set_compiler_flags`.
  - `CopyHelper.cmake` provides the `copy_files` function to copy runtime data (e.g., `tastatura.txt`) to the build and install directories.
- **External dependencies**:
  - SFML 3.0.0 is fetched via `FetchContent` and linked into the main executable (`SFML::Graphics`, `SFML::Window`, `SFML::System`, `SFML::Audio`).
  - `Threads::Threads` is found and linked on non-Apple Unix platforms.

Any significant structural change (e.g., new executables or libraries) should normally be reflected in `CMakeLists.txt` and, if needed, in GitHub Actions and helper scripts so CI continues to function.

## Project-specific guidelines and constraints

These constraints are enforced by the course template and README and should be respected when generating or editing code:

- Avoid global variables and public data members; prefer encapsulated state with clear interfaces.
- Keep most of the project logic in modern C++ (the course expects a high percentage of student-written C++ code).
- For later stages (Tema 2/3), data should come from files or external sources rather than being hard-coded in the code; `tastatura.txt` and puzzle-related files are examples.
- The project uses multiple external libraries (SFML plus additional libraries as the project evolves); new features should integrate them via CMake and, when appropriate, via the existing helper modules and CI workflows.
- For small changes and reviews, they should be applied directly inside the files I created. For bigger changes and add-ons, they should be saved in a sepparate file inside `generated/` directory.

When proposing changes, prefer designs that keep the puzzle framework extensible (new `Puzzle` subclasses, additional puzzle types) without requiring invasive edits to existing code.
