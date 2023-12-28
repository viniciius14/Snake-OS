#!/bin/bash

bin_dir="../bin"
gcc_flags="-Wall -Wextra -m32 -nostdlib -fno-builtin -mgeneral-regs-only"

# Create an array to store the list of .o files
object_files=()

# Create the bin dir if it doesn't exist
mkdir -p "$bin_dir"/

# Clear bin folder
rm -f "$bin_dir"/*.bin
rm -f "$bin_dir"/*.o

# Function to recursively find assembly files
find_assembly_files() {
    local dir="$1"
    shopt -s nullglob
    for assembly_file in "$dir"/*.s; do
        if [ -f "$assembly_file" ]; then
            # Exclude start.s
            if [ "$(basename -- "$assembly_file")" == "start.s" ]; then
                nasm -f bin start.s -o "$bin_dir"/start.bin
                continue
            fi

            # Extract the filename without the extension
            file_name=$(basename -- "$assembly_file")
            file_name_without_extension="${file_name%.s}"

            # Assemble the assembly file
            nasm -f elf32 "$assembly_file" -o "$bin_dir"/"${file_name_without_extension}.o"

            # Check if assembly was successful
            if [ $? -eq 0 ]; then
                echo "Compiled ${file_name}"
                # Add the .o file to the array
                object_files+=("${bin_dir}/${file_name_without_extension}.o")
            else
                echo "Error assembling ${file_name}"
            fi
        fi
    done

    # Recursively search subdirectories
    shopt -s dotglob
    for subdir in "$dir"/*/; do
        if [ -d "$subdir" ]; then
            find_assembly_files "$subdir"
        fi
    done
}

# Recursively find assembly files in the current directory and its subdirectories
find_assembly_files .

# Function to recursively find C files
find_c_files() {
    local dir="$1"
    shopt -s nullglob
    for c_file in "$dir"/*.c; do
        if [ -f "$c_file" ]; then
            # Extract the filename without the extension
            file_name=$(basename -- "$c_file")
            file_name_without_extension="${file_name%.c}"

            # Compile the C file with the include path
            i386-elf-gcc $gcc_flags -c "$c_file" -o "$bin_dir"/"${file_name_without_extension}.o"

            # Check if compilation was successful
            if [ $? -eq 0 ]; then
                echo "Compiled ${file_name}"
                object_files+=("${bin_dir}/${file_name_without_extension}.o")
            else
                echo "Error compiling ${file_name}"
            fi
        fi
    done

    # Recursively search subdirectories
    shopt -s dotglob
    for subdir in "$dir"/*/; do
        if [ -d "$subdir" ]; then
            find_c_files "$subdir"
        fi
    done
}

# Recursively find C files in the current directory and its subdirectories
find_c_files .

# Create a variable with the file names to be linked
files_to_link=""
for file_path in "${object_files[@]}"; do
    files_to_link+=" $(basename -- "$file_path")"
done

# Link and build the final kernel binary
echo "Linking:$files_to_link"
ld -m elf_i386 -Ttext 0x1000 -T ../misc/linker.ld "${object_files[@]}" -o "${bin_dir}/kernel.bin" --oformat binary

cat "${bin_dir}"/start.bin "${bin_dir}"/kernel.bin > "${bin_dir}"/f_kernel.bin

qemu-system-x86_64 -drive format=raw,file="${bin_dir}"/f_kernel.bin,index=0,if=floppy -m 128M
