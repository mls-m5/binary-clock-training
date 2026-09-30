# binary-training

## WebAssembly med Podman

Bygg projektet med Emscripten utan att installera Emscripten lokalt:

```sh
make podman
```

Öppna övningen via en lokal webbserver (WebAssembly laddas inte alltid via `file://`):

```sh
python3 -m http.server 8000 --directory build/podman
```

Besök sedan http://localhost:8000/ (eller http://localhost:8000/index.html). Sidan visar 16 bitar
i ett 4×4-rutnät: 4 timmar, 6 minuter och 6 sekunder. Ange tiden i de tre
fälten och kontrollera svaret; du får återkoppling per fält. Eftersom fyra
bitar bara kan visa 0–15 används endast timmarna 00–15.

De genererade filerna (`index.html`, `index.js` och `index.wasm`) hamnar i
`build/podman/`. CMake:s mellanliggande filer ligger i `build/podman/cmake/`.
Podman kör med ditt användar-ID så att du kan ta bort byggfilerna utan root.

C++-källan kan fortfarande kompileras med vanlig CMake lokalt.
