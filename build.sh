mkdir -p build

./forrst/code_gen.sh 2>/dev/null || ./code_gen.sh 2>/dev/null

COMPILER=("zig" "cc")
COMPILER_CC=("g++")
CFLAGS="-std=c99"
CCFLAGS="-std=gnu++98"
FLAGS_COMP="-Wno-narrowing -Wall -Iforrst -I. -Ideps -Iforrst/deps -isystem"
FLAGS_LINK=""
CFLAGS_COMP=""

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
    COMPILER=("gcc")
    if ! gcc --version &> /dev/null; then
        COMPILER=("clang")
        if ! clang --version &> /dev/null; then
            COMPILER=("cc")
            if ! cc --version &> /dev/null; then
                echo "WHAT FUCKING COMPILER DO YOU HAVE?!?!"
            fi
        fi
    fi
    exit 1
elif $BUILD_TEST && ! tcc --version &> /dev/null; then
    COMPILER=("zig" "cc")
    if ! zig cc --version &> /dev/null; then
        COMPILER=("gcc")
        if ! gcc --version &> /dev/null; then
            COMPILER=("clang")
            if ! clang --version &> /dev/null; then
                COMPILER=("cc")
                if ! cc --version &> /dev/null; then
                    echo "WHAT FUCKING COMPILER DO YOU HAVE?!?!"
                fi
            fi
        fi
    fi
    exit 1
fi

if $BUILD_TEST; then
    #COMPILER=("tcc")
    COMPILER_CC=("g++")
    FLAGS_COMP+=" -O0 -g"
    FLAGS_LINK+=" -g -fno-lto"
    CFLAGS_COMP+=" -fno-sanitize=undefined"
else
    FLAGS_COMP+=" -O3"
    FLAGS_LINK+=" -flto"
fi

if $BUILD_WINDOWS; then
    COMPILER_CC=("x86_64-w64-mingw32-g++")
    FLAGS_LINK+=" -lopengl32 -Ldeps/GLFW -lglfw3 -lgdi32 -D_WIN32"
    CFLAGS_COMP="-target x86_64-windows -fno-sanitize=undefined"
    FLAGS_COMP+=" -D_WIN32"
else
    FLAGS_LINK+=" -lGL -lglfw -lEGL -lX11 -lm"
fi

if [ -n "$EXAMPLE" ]; then
    SRC_DIRS=("." "examples/$EXAMPLE")
else
    SRC_DIRS=("forrst" "src")
fi

FILES_C=()
FILES_CC=()
for dir in "${SRC_DIRS[@]}"; do
    while IFS= read -r file; do
        [[ -f "$file" ]] || continue
        case "${file##*.}" in
            c) FILES_C+=("$file") ;;
            cpp|cc) FILES_CC+=("$file") ;;
        esac
    done < <(find "$dir" -type f ! -path "*/examples/*")
done


OUT="compile_commands.json"
echo "[" > "$OUT"

FIRST=1
for file in "${FILES_C[@]}" "${FILES_CC[@]}"; do 
    if [[ $file == *.c ]]; then
        COMP="gcc" # not really
        STD="-std=c99"
    else
        COMP="g++"
        STD="-std=gnu++98"
    fi

    CMD="$COMP $STD -Iforrst -I. -Ideps -Iforrst/deps -c \\\"$file\\\""

    if [ $FIRST -eq 1 ]; then
        FIRST=0
    else
        echo "," >> "$OUT"
    fi

    echo -ne "\t{
        \"directory\": \"$(pwd)\",
        \"command\": \"$CMD\",
        \"file\": \"$(pwd)/${file#./}\"
    }" >> "$OUT"
done

echo -e "\n]" >> "$OUT"


echo -e "COMPILING: ${FILES_C[@]} ${FILES_CC[@]}\n"

OBJ_DIR="build/obj"
mkdir -p "$OBJ_DIR"
OBJS=()

rm -rf build/obj/
mkdir build/obj

for file in "${FILES_C[@]}"; do
    obj="$OBJ_DIR/$(basename "$file" .c).o"
    "${COMPILER[@]}" $CFLAGS $FLAGS_COMP $CFLAGS_COMP -c "$file" -o "$obj"
    OBJS+=("$obj")
done

for file in "${FILES_CC[@]}"; do
    obj="$OBJ_DIR/$(basename "$file" .cc).o"
    "${COMPILER_CC[@]}" $CCFLAGS $FLAGS_COMP -c "$file" -o "$obj"
    OBJS+=("$obj")
done

if $BUILD_WINDOWS; then
    #"${COMPILER[@]}" "${FILES[@]}" $CFLAGS -o build/out.exe
    #if [[ "$OSTYPE" == "linux-gnu" ]]; then
    #    wine ./build/out.exe
    #else
    #    ./build/out.exe
    #fi
    "${COMPILER_CC[@]}" "${OBJS[@]}" $FLAGS_LINK -o build/out.exe && ( [[ "$OSTYPE" == "linux-gnu" ]] && wine ./build/out.exe || ./build/out.exe )
else
    #"${COMPILER[@]}" "${FILES[@]}" $CFLAGS -o build/out.game && ./build/out.game
    "${COMPILER_CC[@]}" "${OBJS[@]}" $FLAGS_LINK -o build/out.game && ./build/out.game
fi
