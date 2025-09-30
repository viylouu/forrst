mkdir -p build

./forrst/code_gen.sh 2>/dev/null || ./code_gen.sh 2>/dev/null

COMPILER=("zig" "cc")
CFLAGS="-std=c99 -Wall -Wextra -Iforrst -I. -Ideps -Iforrst/deps -isystem"

BUILD_TEST=false
EXAMPLE=""

[[ "$OSTYPE" == "linux-gnu" ]] && BUILD_WINDOWS=false || BUILD_WINDOWS=true

for arg in "$@"; do
    if [ "$arg" = "-t" ]; then
        BUILD_TEST=true
    elif [ "$arg" = "-w" ]; then
        BUILD_WINDOWS=true
    else
        EXAMPLE="$arg"
    fi
done

if ! $BUILD_TEST && ! zig cc --version &> /dev/null; then
    echo "zig cc not installed / not in path!"
    exit 1
elif $BUILD_TEST && ! tcc --version &> /dev/null; then
    echo "tcc not installed / not in path!"
    exit
fi

if $BUILD_TEST; then
    COMPILER=("tcc")
    CFLAGS+=" -O0 -g -fno-lto"
else
    CFLAGS+=" -O3 -flto"
fi

if $BUILD_WINDOWS; then
    CFLAGS+=" -target x86_64-windows-gnu -lopengl32"
else
    CFLAGS+=" -lGL -lglfw"
fi

if [ -n "$EXAMPLE" ]; then
    SRC_DIRS=("." "examples/$EXAMPLE")
else
    SRC_DIRS=("forrst" "src")
fi

FILES=()
for dir in "${SRC_DIRS[@]}"; do
    while IFS= read -r file; do
        FILES+=("$file")
    done < <(find "$dir" -name "*.c" ! -path "*/examples/*")
done

echo -e "COMPILING: ${FILES[@]}\n"

if $BUILD_WINDOWS; then
    "${COMPILER[@]}" "${FILES[@]}" $CFLAGS -o build/out.exe
    if [[ "$OSTYPE" == "linux-gnu" ]]; then
        wine ./build/out.exe
    else
        ./build/out.exe
    fi
else
    "${COMPILER[@]}" "${FILES[@]}" $CFLAGS -o build/out.game && ./build/out.game
fi
