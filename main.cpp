
/// Occasionally the same bug can be observed in `main.cpp`.

// import unique_wrapper;
// import unique_fd;
import my_app;

int main() {
  MyApp app{123};
  app.print_the_fd(); // Try to trigger auto completion here while "Module
                      // 'my_app' not found" error is present. `print_the_fd`
                      // won't be available.
  return 0;
}
