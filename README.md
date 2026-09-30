# Binary Clock Training

An exercise for reading a binary clock. C++ compiled to WebAssembly with
Emscripten chooses a random time, generates the bits, checks your answer, and
produces feedback in English or Swedish. JavaScript handles the browser UI.
The page displays 16 bits in a 4×4 grid: 4 for hours, 6 for minutes, and 6 for seconds. Enter
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

## Terminal version and native tests

Build the native version with CMake (the first configuration downloads the
pinned doctest 2.5.3 GitHub ZIP for the tests, so an internet connection is
required):

```sh
cmake -S . -B build/native -DCMAKE_BUILD_TYPE=Release
cmake --build build/native
./build/native/binary-training
```

The terminal clock is a 4×4 grid of circles only: `●` is 1 and `○` is 0.
Read left to right, top to bottom: the first 4 bits are hours, the next 6
minutes, and the last 6 seconds. Instructions and the input prompt appear
outside the grid. Enter a time such as `09:23:45` (or `9 23 45`) and press
Enter. It shows which fields are correct; a correct answer starts a new round.
Enter `q` or press Ctrl-D to exit. Hours are limited to 0–15, as on the web
page.

Run the native tests with:

```sh
ctest --test-dir build/native --output-on-failure
```

The WebAssembly build does not fetch or include doctest. GitHub Actions runs
the same native tests on pushes and pull requests to `main` via
[`.github/workflows/native-tests.yml`](.github/workflows/native-tests.yml).
The Pages workflow builds the WebAssembly site separately; it does not run
these native tests.

## Try it online

[Open Binary Clock Training on GitHub Pages](https://mls-m5.github.io/binary-clock-training/).
