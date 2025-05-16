
Tiny project to demostrate the clangd 21 `ixx` module file import bug. The module exporting interfaces in the global fragment cannot be built when it's declared in a file with `.ixx` file extension. The issue is gone when the file extension is changed to either `.cpp` or `.cppm`.

The bug is reliably reproducible using with following version (installed from LLVM's apt repository):

```
~> clangd-21 --version
Ubuntu clangd version 21.0.0 (++20250501084208+9b1051281e43-1~exp1~20250501084221.26)
Features: linux+grpc
Platform: x86_64-pc-linux-gnu
```

clangd is started with the following additional arguments (which is also provided in `.vscode/settings.json` for VS Code user):

```
clangd \
    --compile-commands-dir=<relative path to build folder> \
    --experimental-modules-support \
    --header-insertion=never \
    --background-index \
    -j=6 \
    --pch-storage=disk
```

Pull the project using the following command:

```sh
git clone \
  --single-branch \
  --branch clangd_ixx_bug \
  --recursive \
  https://github.com/SidneyCogdill/clangd_modules_bug_showcase.git 
```

Go to [main.cpp](main.cpp) file. `import proxy;` emits the `Module 'proxy' not found` error. Relevant clangd log:

```
E[07:09:48.126] Failed to build module proxy; due to Failed to build compiler invocation
I[07:09:48.126] Built prerequisite modules for file ./main.cpp in 0.28 seconds
```

Note that this bug doesn't affect clang. clang can compile the program successfully.
