# Contributing

Thanks for taking a look at Real Black.

## Local Setup

Requirements:

- macOS or another system with CLion installed.
- CLion with a bundled JBR/JDK, or any JDK that can compile Java 17.
- `zip`, `jar`, and standard shell tools.

Build the plugin archive:

```bash
./scripts/package.sh
```

By default the package script uses:

```text
/Applications/CLion.app/Contents
```

Use `CLION_HOME` if CLion is installed somewhere else:

```bash
CLION_HOME="/path/to/CLion.app/Contents" ./scripts/package.sh
```

## Theme Editing

- UI shell colors live in `src/main/resources/themes/RealBlack.theme.json`.
- Editor colors live in `src/main/resources/schemes/RealBlack.xml`.
- Plugin metadata lives in `src/main/resources/META-INF/plugin.xml`.
- Extra C++ token coloring lives in `src/main/java/dev/nazimaraz/realblack/BlackCppKeywordAnnotator.java`.

## Versioning

Every visible change should get a new version.

When making a release-oriented change:

1. Update `version` in `build.gradle.kts`.
2. Update `<version>` in `src/main/resources/META-INF/plugin.xml`.
3. Update `CHANGELOG.md`.
4. Run `./scripts/package.sh`.
5. Keep old release ZIPs intact.

## Pull Requests

Please keep changes focused. Good pull requests usually include:

- A short description of the visual or behavior change.
- Before/after screenshots for UI theme changes.
- A note about whether the editor color scheme changed.
- The generated ZIP only as a GitHub Release artifact, not as a committed file.
