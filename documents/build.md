                  CMakeLists.txt
                        │
                        ▼
                 ┌─────────────┐
                 │    CMake    │
                 └──────┬──────┘
                        │
                        ▼
                 Build system
                    (Ninja)
                        │
                        ▼
                 C++ compiler
                   (GCC/Clang)
                        │s
                        ▼
                  Object files
                        │
                        ▼
                     Linker
                        │
                        ▼
                  build/lynx



* How the code gets the final build
        Your C++ source
            ↓
            CMake
            ↓
        Build system
        (Ninja)
            ↓
        Compiler
        (g++/clang++)
            ↓
            Linker
            ↓
        Executable



                  