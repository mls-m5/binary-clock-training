# Binary Clock Training

An exercise for reading a binary clock. C++ compiled to WebAssembly with
Emscripten chooses a random time and checks your answer. The page displays
16 bits in a 4×4 grid: 4 for hours, 6 for minutes, and 6 for seconds. Enter
the time in the three fields for feedback on each part, or try a new time.
The page defaults to English; use the 🇬🇧 / 🇸🇪 buttons to switch between
English and Swedish. Your choice is saved in your browser when local storage
is available.

**Note:** Four bits can only represent hours 0–15, so this exercise uses
times between 00:00:00 and 15:59:59, not a full 24-hour day.

## Build and run locally

Requires Podman and Make. Emscripten is not required on your machine: both
Podman and GitHub Actions use the same pinned version (`3.1.74`).

```sh
make podman
python3 -m http.server 8000 --directory build/podman
```

Open http://localhost:8000/ in a browser. A local web server is needed
because browsers may not load WebAssembly over `file://`.

The generated files are `build/podman/index.html`, `index.js`, and
`index.wasm`. CMake's intermediate files are in `build/podman/cmake/`.
Podman runs with your user ID so you can delete the build files without root.
A native CMake build also works, but the exercise page requires Emscripten.

## Try it online

[Open Binary Clock Training on GitHub Pages](https://mls-m5.github.io/binary-clock-training/).
