# 221 Computer Graphics

My assignment project from the computer graphics course at HCMUT, semester 221. Windows binary available in the Releases tab.

https://user-images.githubusercontent.com/40488299/215260271-a4e1a585-434b-4d81-8605-29298bc27a4e.mp4

This works on Windows using MSVC 2022 and/or Ubuntu using Clang.

```bash
$ mkdir build
$ cd build
$ cmake .. # -DCMAKE_EXPORT_COMPILE_COMMANDS=1 if using clangd's LSP
$ cmake --build .
$ ./main
```

Project entry points are [`main.cpp`](main.cpp) and [`scene.cpp`](scene/src/scene.cpp).

## Documents

Assignment specifications and lab materials can be found at [`docs/`](docs/)
