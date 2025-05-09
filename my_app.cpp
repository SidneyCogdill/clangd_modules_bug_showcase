module;

#include <print>

export module my_app;

/// Toggle this comment, then restart clangd to observe the bug.
/// For VS Code: Ctrl + Shift + P -> clangd: Restart language server
///
/// Note that uncommenting the import line causes clangd to be able to parse
/// without a restart. However, commenting the import line again doesn't cause
/// clangd to emit errors, until a full process restart.
///

// import unique_wrapper;
import unique_fd;

/// Also, the import ordering matters: try moving `import unique_wrapper;` after
/// `import unique_fd;` and restart clangd. It will start complaining "module
/// not found".

export struct MyApp {
  MyApp(unsigned long fd) : fd(fd) {}

  auto print_the_fd() { std::println("This app has {}", fd.get()); }

private:
  UniqueFd fd;
};