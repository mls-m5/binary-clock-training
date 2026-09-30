# Binärklockan

En övningssida för att läsa en binär klocka. Ett C++-program kompileras med
Emscripten till WebAssembly och väljer ett slumpmässigt klockslag samt rättar
svaren. Webbsidan visar 16 bitar i ett 4×4-rutnät: 4 för timmar, 6 för minuter
och 6 för sekunder. Skriv in tiden i de tre fälten för att få återkoppling per
del, eller välj ett nytt klockslag.

**Begränsning:** Fyra bitar kan bara representera 0–15, så övningen använder
klockslag mellan 00:00:00 och 15:59:59 (inte hela dygnet).

## Bygg och kör lokalt

Kräver Podman och Make. Emscripten installeras inte lokalt; samma version
(`3.1.74`) används i Podman och GitHub Actions.

```sh
make podman
python3 -m http.server 8000 --directory build/podman
```

Öppna http://localhost:8000/ i webbläsaren. En webbserver behövs eftersom
webbläsare inte alltid kan ladda WebAssembly via `file://`.

De genererade filerna är `build/podman/index.html`, `index.js` och
`index.wasm`. CMake:s mellanliggande filer ligger i `build/podman/cmake/`.
Podman kör med ditt användar-ID så att byggfilerna kan tas bort utan root.
En vanlig lokal CMake-kompilering fungerar också, men övningssidan kräver
Emscripten.

## Publicera på GitHub Pages

Workflowen [`.github/workflows/pages.yml`](.github/workflows/pages.yml) bygger
med Emscripten och publicerar `index.html`, `index.js` och `index.wasm` vid
push till `main`. Den kan även startas manuellt via **Actions → Publish
binary clock → Run workflow**. Den publicerar bara byggresultatet, inte CMake:s
mellanliggande filer.

1. Skapa ett GitHub-repo och pusha projektet till `main` (ändra workflowens
   `branches` om du använder en annan standardgren).
2. Välj **Settings → Pages → Build and deployment → Source: GitHub Actions**.
3. Pusha en ändring eller starta workflowen manuellt. Adressen visas under
   **Settings → Pages** och i workflowens deploy-steg; för ett vanligt
   projektrepo är den `https://<användare>.github.io/<repo>/`.

Om organisationen begränsar Actions eller Pages måste de också tillåtas i
repo-/organisationsinställningarna.
