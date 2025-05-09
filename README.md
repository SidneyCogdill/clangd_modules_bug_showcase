
Tiny project to demostrate the clangd 21 transitive import bug. Some modules carry around implicit module dependencies, apparently they are not implicitly imported by the consumer.

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

Go to [my_app.cpp](my_app.cpp) file. `import unique_wrapper;` is required to not get the "Module 'unique_fd' not found" error. Relevant clangd log:

```
I[00:35:30.109] Built preamble of size 8041192 for file ./clangd_modules_bug_showcase/my_app.cpp version 334 in 0.75 seconds
E[00:35:30.174] Failed to build module unique_fd; due to Compilation failed
I[00:35:30.174] Built prerequisite modules for file ./clangd_modules_bug_showcase/my_app.cpp in 1.03 seconds
I[00:35:30.175] --> workspace/semanticTokens/refresh(68)
I[00:35:30.177] <-- reply(68)
E[00:35:31.069] Failed to build module unique_fd; due to Compilation failed
I[00:35:31.069] Built prerequisite modules for file ./clangd_modules_bug_showcase/my_app.cpp in 0.96 seconds
I[00:35:31.069] --> workspace/semanticTokens/refresh(69)
```

When clangd fails to build the import modules, the auto completion will not work for the relevant types. This can be observed in [main.cpp](main.cpp) file.

Note that this bug doesn't affect clang. clang can compile the program successfully.
