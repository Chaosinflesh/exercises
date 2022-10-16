#!/bin/sh
# Mega-build script for single-file compilations.
set -e

# Assumes the existence of a single . in the path.
SOURCE="${1}"
TARGET="${SOURCE%.*}"
EXTENSION="${SOURCE##*.}" # Assumes only a single . in the path.
FOLDER="${SOURCE%/*}"
FILE="${TARGET##*/}"

echo "Compiling ${SOURCE} -> ${TARGET}"

case "${EXTENSION}" in
    a68)    # Algol68
            a68g "${SOURCE}"
            ;;

    adb)    # ADA
            gnatmake -f "${SOURCE}" -o "${TARGET}"
            ./"${TARGET}"
            ;;

    apl)    # APL
            apl -f "${SOURCE}"
            ;;

    awk)    # AWK
            awk -f "${SOURCE}"
            ;;

    bas)    # BASIC
            fbc "${SOURCE}"
            ./"${TARGET}"
            ;;

    C)      # C
            clang -Wall -Werror -pedantic "${SOURCE}" -o "${TARGET}"
            ./"${TARGET}"
            ;;

    clj)    # Clojure
            clojure "${SOURCE}"
            ;;

    cobol)  # COBOL
            cobc -x "${SOURCE}" -o "${TARGET}"
            ./"${TARGET}"
            ;;

    cpp)    # C++
            clang++ -Wall -Werror -pedantic "${SOURCE}" -o "${TARGET}"
            ./"${TARGET}"
            ;;

    cs)     # C#
            mcs -out"${TARGET}"  "${SOURCE}"
            mono "${TARGET}"
            ;;

    dart)   # Dart
            dart --disable-analytics run "${SOURCE}"
            ;;

    elm)    # elm
            echo "TODO: Figure out how to script elm nicely."
            ;;

    exs)    # Elixir
            elixir "${SOURCE}"
            ;;

    f95)    # FORTRAN
            gfortran "${SOURCE}" -o "${TARGET}"
            ./"${TARGET}"
            ;;

    fth)    # FORTH
            gforth "${SOURCE}"
            ;;

    go)     # go
            go run "${SOURCE}"
            ;;

    groovy) # groovy
            groovy "${SOURCE}"
            ;;

    java)   # Java
            java "${SOURCE}"
            ;;

    jl)     # Julia
            julia "${SOURCE}"
            ;;

    js)     # JavaScript
            rhino "${SOURCE}"
            ;;

    kt)     # Kotlin
            kotlinc "${SOURCE}" -include-runtime -d "${TARGET}.jar"
            java -jar "${TARGET}.jar"
            ;;

    kts)    # Kotlin (as script)
            kotlinc -script "${SOURCE}" -- -d "${FOLDER}"
            ;;

    lisp)   # Lisp
            clisp "${SOURCE}"
            ;;

    logo)   # LOGO
            ucblogo "${SOURCE}"
            ;;

    lua)    # Lua
            lua "${SOURCE}"
            ;;

    ml)     # ML
            polyc "${SOURCE}" -o "${TARGET}"
            ./"${TARGET}"
            ;;

    mod)    # Modula-2
            echo "TODO: Figure out why gm2 libraries are absent on my system."
            ;;

    nim)    # Nim
            nim c -r --verbosity:0 "${SOURCE}"
            ;;

    pas)    # Pascal
            fpc "${SOURCE}" -o"${TARGET}"
            ./"${TARGET}"
            ;;

    perl)   # PERL
            perl "${SOURCE}"
            ;;

    php)    # PHP
            php -f "${SOURCE}"
            ;;

    pl)     # Prolog
            echo "Use gprolog + TODO: further instructions."
            ;;

    ps1)    # Powershell
            pwsh "${SOURCE}"
            ;;

    py)     # Python
            python3 "${SOURCE}"
            ;;

    rb)     # Ruby
            ruby "${SOURCE}"
            ;;

    rs)     # Rust
            rustc "${SOURCE}" -o "${TARGET}"
            ./"${TARGET}"
            ;;

    s)      # Assembly
            gcc "${SOURCE}" -no-pie -o "${TARGET}"
            ./"${TARGET}"
            ;;

    scala)  # Scala
            scalac -d "${FOLDER}" "${SOURCE}"
            scala -classpath "${FOLDER}" "${FILE}"
            ;;

    scandi) # scandi
            echo "TODO: Finish LLVM implementation before running me!"
            ;;

    sh)     # bash
            sh "${SOURCE}"
            ;;

    sim)    # Simula67
            echo "TODO: Fix segmentation fault in cim first!"
            ;;

    sql)    # SQL
            mysql -p -Bse "$(cat ""${SOURCE}"")"
            ;;

    st)     # SmallTalk
            gst "${SOURCE}"
            ;;

    swift)  # Swift (as script)
            PATH="${SWIFT_PATH}" swift "${SOURCE}"
            ;;

    ts)     # TypeScript
            tsc "${SOURCE}" -outFile "${TARGET}.gen.js"
            rhino "${TARGET}.gen.js"
            rm "${TARGET}.gen.js"
            ;;

    v)      # V
            v run "${SOURCE}"
            ;;

    zig)    # Zig
            zig run "${SOURCE}"
            ;;

    *)      # UNDEFINED
            echo "TODO: UNDEFINED SOURCE EXTENSION"
            ;;

esac

