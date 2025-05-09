module;

#include <print>

export module unique_fd;

import unique_wrapper;

export struct UniqueFd {
  UniqueFd(unsigned long fd)
      : m_handle(fd,
                 [](unsigned long fd) { std::println("Destroyed {}", fd); }) {}

  auto get() { return m_handle.get(); }

private:
  UniqueWrapper<unsigned long> m_handle;
};
