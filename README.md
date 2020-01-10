# clang2nim

git clone https://github.com/llvm/llvm-project

git checkout origin/release/9.x

cd llvm-project

mkdir build && cd build

cmake -DLLVM_ENABLE_PROJECTS="clang;clang-tools-extra" -DLLVM_TARGETS_TO_BUILD=host -DLLVM_ENABLE_BINDINGS=OFF -DCMAKE_BUILD_TYPE=Release  -DCMAKE_INSTALL_PREFIX=/usr/lib/x86_64-linux-gnu/ -G Ninja ../llvm && time cmake --build . -j8

bin/clang2nim test.cpp
