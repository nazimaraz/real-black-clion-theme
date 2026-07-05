#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
BUILD_DIR="$ROOT/build/manual"
DIST_DIR="$ROOT/dist"
PLUGIN_DIR="$BUILD_DIR/plugin/RealBlack"
VERSION="$(sed -n 's:.*<version>\(.*\)</version>.*:\1:p' "$ROOT/src/main/resources/META-INF/plugin.xml" | head -n 1)"
JAR_NAME="real-black-$VERSION.jar"
ZIP_NAME="real-black-$VERSION.zip"
CLION_HOME="${CLION_HOME:-/Applications/CLion.app/Contents}"
JAVAC="${JAVAC:-}"

if [[ -z "$JAVAC" ]]; then
    if [[ -x "$CLION_HOME/jbr/Contents/Home/bin/javac" ]]; then
        JAVAC="$CLION_HOME/jbr/Contents/Home/bin/javac"
    else
        JAVAC="javac"
    fi
fi

rm -rf "$BUILD_DIR"
mkdir -p "$BUILD_DIR/jar" "$BUILD_DIR/classes" "$PLUGIN_DIR/lib" "$DIST_DIR"

cp -R "$ROOT/src/main/resources/." "$BUILD_DIR/jar/"

JAVA_SOURCES=()
while IFS= read -r source_file; do
    JAVA_SOURCES+=("$source_file")
done < <(find "$ROOT/src/main/java" -type f -name '*.java' | sort)

if ((${#JAVA_SOURCES[@]})); then
    CLION_CLASSPATH="$(find "$CLION_HOME/lib" -maxdepth 2 -type f -name '*.jar' | sort | tr '\n' ':')"
    "$JAVAC" \
        --release 17 \
        -cp "$CLION_CLASSPATH" \
        -d "$BUILD_DIR/classes" \
        "${JAVA_SOURCES[@]}"
    cp -R "$BUILD_DIR/classes/." "$BUILD_DIR/jar/"
fi

(
    cd "$BUILD_DIR/jar"
    jar cf "$PLUGIN_DIR/lib/$JAR_NAME" .
)

(
    cd "$BUILD_DIR/plugin"
    zip -qr "$DIST_DIR/$ZIP_NAME" "RealBlack"
)

printf '%s\n' "$DIST_DIR/$ZIP_NAME"
