set(LLVM_LINK_COMPONENTS support)


add_clang_executable(clang2nim
  clang2nim.cpp
  )

target_link_libraries(clang2nim
  PRIVATE
  clangAST
  clangTooling
  clangToolingCore
  clangBasic
  clangASTMatchers
  clangCodeGen
  clangDriver
  clangFrontend
  clangFrontendTool
  clangSerialization
  )
