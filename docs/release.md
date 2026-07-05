# Release Checklist

Use this checklist when publishing a new Real Black release.

## Before Building

- Update `CHANGELOG.md`.
- Update `version` in `build.gradle.kts`.
- Update `<version>` and `<change-notes>` in `src/main/resources/META-INF/plugin.xml`.
- Confirm the README install path points at the new `dist/real-black-*.zip`.
- Open `examples/cpp-theme-color-specimen.cpp` in CLion and spot-check C++ colors.

## Validate

```bash
python3 -m json.tool src/main/resources/themes/RealBlack.theme.json >/tmp/real-black-theme.json
xmllint --noout \
  src/main/resources/META-INF/plugin.xml \
  src/main/resources/schemes/RealBlack.xml \
  src/main/resources/META-INF/pluginIcon.svg \
  src/main/resources/META-INF/pluginIcon_dark.svg
```

## Build

```bash
./scripts/package.sh
```

The generated archive will be written to `dist/`.

## Inspect

Replace the version in these commands:

```bash
unzip -l dist/real-black-1.0.0.zip
unzip -p dist/real-black-1.0.0.zip RealBlack/lib/real-black-1.0.0.jar >/tmp/real-black.jar
unzip -p /tmp/real-black.jar META-INF/plugin.xml
unzip -l /tmp/real-black.jar
```

## Publish

- Create a GitHub Release with the matching version tag, for example `v1.0.0`.
- Upload `dist/real-black-1.0.0.zip` as the release asset. This is the file users install in CLion.
- Include the relevant `CHANGELOG.md` entry in the release notes.
- Do not commit files from `dist/`.

A tag alone only gives users GitHub's generated source archives. CLion cannot install those source archives as the plugin. Users need the generated `real-black-*.zip` plugin archive attached to the GitHub Release.
