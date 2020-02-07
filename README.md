# clang2nim

For those who builds llvm and clang for the first time:

git clone https://github.com/llvm/llvm-project

git checkout origin/release/9.x

cd llvm-project

put clang2nim directory under clang/tools/

add_clang_subdirectory(clang2nim)

mkdir build && cd build

cmake -DLLVM_ENABLE_PROJECTS="clang;clang-tools-extra" -DLLVM_TARGETS_TO_BUILD=host -DLLVM_ENABLE_BINDINGS=OFF -DCMAKE_BUILD_TYPE=Release  -DCMAKE_INSTALL_PREFIX=/usr/lib/x86_64-linux-gnu/ -G Ninja ../llvm && time cmake --build . -j8

cmake --install .

vim /etc/ld.so.conf.d/x86_64-linux-gnu

append /usr/lib/x86_64-linux-gnu/lib(where you install llvm and clang libraries)

ldconfig

cmake --build .

bin/clang2nim test.cpp
