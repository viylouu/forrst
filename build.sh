mkdir -p build

./furry/code_gen.sh 2>/dev/null || ./code_gen.sh 2>/dev/null

COMPILER=("zig" "cc")
CFLAGS="-std=c99"
FLAGS_COMP="-pedantic -Wall -Wextra -Werror -Ifurry -I. -Ideps -Ideps/imgui -Ifurry/deps/imgui -Ifurry/deps -isystem"
FLAGS_LINK=""

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
    FLAGS_COMP+=" -O0 -g -fno-sanitize=undefined"
    FLAGS_LINK+=" -g -fno-lto"
else
    FLAGS_COMP+=" -O3"
    FLAGS_LINK+=" -flto"
fi

if $BUILD_WINDOWS; then
    FLAGS_LINK+=" -lopengl32 -Ldeps/GLFW -lglfw3 -lgdi32 -D_WIN32"
    FLAGS_COMP+=" -target x86_64-windows -fno-sanitize=undefined"
else
    FLAGS_LINK+=" -lGL -lglfw -lEGL -lX11 -lm"
fi

if [ -n "$EXAMPLE" ]; then
    SRC_DIRS=("." "examples/$EXAMPLE")
else
    SRC_DIRS=("forrst" "src")
fi

FILES_C=()
for dir in "${SRC_DIRS[@]}"; do
    while IFS= read -r file; do
        [[ -f "$file" ]] || continue
        case "${file##*.}" in
            c) FILES_C+=("$file") ;;
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
    #else
        #COMP="g++"
        #STD="-std=c++11"
    fi

    CMD="$COMP $STD -pedantic -Wall -Wextra -Werror -Ifurry -I. -Ideps -Ideps/imgui -Ifurry/deps/imgui -Ifurry/deps -c \\\"$file\\\""

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
OBJS=()

#[[ $BUILD_TEST == false ]] && rm -rf build/obj/
#rm -rf build/obj/
mkdir -p build/obj

max_jobs=$(nproc) 

compile_file() {
    local file="$1"
    local compiler=("${!2}")  # pass array name
    local flags="$3"
    
    #obj="$OBJ_DIR/$(basename "$file" ${file##*.}).o"
    #dep="$OBJ_DIR/$(basename "$file" .${file##*.}).d"
    filename=$(basename "$file")
    basename_noext="${filename%.*}"
    obj="$OBJ_DIR/$basename_noext.o"
    #dep="$OBJ_DIR/$basename_noext.d"
    echo "$obj" >> "$OBJ_DIR/objs.tmp"
    #[[ -f "$obj" && "$obj" -nt "$file" ]] && return

    skip_compile=false

    if [[ $BUILD_TEST && -f "$obj" ]]; then
        # check if "deps" is anywhere in the path
        if [[ "$file" == */deps/* ]]; then
            skip_compile=true
        fi
    fi

    if [[ $skip_compile != true ]]; then
        if [[ $file == *.c ]]; then
            #"${COMPILER[@]}" $flags -fno-sanitize=undefined -c "$file" -o "$obj"
            "${COMPILER[@]}" $CFLAGS $FLAGS_COMP \
                -fno-sanitize=undefined -c "$file" -o "$obj"
        #else
            #"${COMPILER_CC[@]}" $flags -fno-sanitize=undefined -c "$file" -o "$obj"
            #"${COMPILER_CC[@]}" $CCFLAGS $FLAGS_COMP \
            #    -fno-sanitize=undefined -c "$file" -o "$obj"
        fi 
    fi
}

> "$OBJ_DIR/objs.tmp"  # clear temp file

for file in "${FILES_C[@]}"; do
    compiler_arr=FILES_C[@]
    flags="$FLAGS_COMP"

    compile_file "$file" compiler_arr "$flags" &

    # limit parallel jobs
    while [ $(jobs -r | wc -l) -ge $max_jobs ]; do
        sleep 0.1
    done
done

wait

mapfile -t OBJS < "$OBJ_DIR/objs.tmp"

rm -f objs.tmp

if $BUILD_WINDOWS; then
    "${COMPILER[@]}" -fuse-ld=lld "${OBJS[@]}" $FLAGS_LINK -o build/out.exe && ( [[ "$OSTYPE" == "linux-gnu" ]] && wine ./build/out.exe || ./build/out.exe )
else
    "${COMPILER[@]}" -fuse-ld=lld "${OBJS[@]}" $FLAGS_LINK -fno-sanitize=undefined -o build/out.game && ./build/out.game
fi
