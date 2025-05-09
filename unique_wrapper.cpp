module;

#include <functional>
#include <stdexcept>
#include <type_traits>

export module unique_wrapper;

export template <typename Handle>
  requires(std::is_default_constructible_v<Handle> &&
           std::is_trivially_copyable_v<Handle>)
struct UniqueWrapper {
public:
  explicit UniqueWrapper(Handle p,
                         std::move_only_function<void(Handle &&)> deleter)
      : m_ptr(p), m_deleter(std::move(deleter)) {}

  UniqueWrapper(const UniqueWrapper &) = delete;
  UniqueWrapper &operator=(const UniqueWrapper &) = delete;

  UniqueWrapper(UniqueWrapper &&other) noexcept
      : m_ptr(other.m_ptr), m_deleter(std::move(other.m_deleter)) {
    other.m_ptr = Handle{};
  }

  UniqueWrapper &operator=(UniqueWrapper &&other) noexcept {
    if (this != &other) {
      this->delete_();
      m_ptr = other.m_ptr;
      other.m_ptr = Handle{};

      m_deleter = std::move(other.m_deleter);
    }
    return *this;
  }

  ~UniqueWrapper() { this->delete_(); }

  Handle operator*() const
    requires requires(Handle a) { *a; }
  {
    if (m_ptr == Handle{})
      throw std::logic_error("Dereferencing null handle");
    return m_ptr;
  }

  Handle *operator->() const
    requires std::is_pointer_v<Handle> || requires(Handle a) { a.operator->(); }
  {
    if (m_ptr == Handle{})
      throw std::logic_error("Dereferencing null handle");
    return m_ptr;
  }

  Handle get() const { return m_ptr; }

  void reset(Handle p = Handle{}) {
    if (m_ptr != p) {
      this->delete_();
      m_ptr = p;
    }
  }

  auto release() {
    Handle tmp = std::move(m_ptr);
    m_ptr = Handle{};
    return tmp;
  }

private:
  auto delete_() {
    if (m_ptr != Handle{}) {
      if (m_deleter) [[likely]]
        m_deleter(std::move(m_ptr));
      else [[unlikely]]
        throw std::runtime_error("Deleter is empty, but handle isn't null.");
      m_ptr = Handle{};
    }
  }

private:
  Handle m_ptr;
  std::move_only_function<void(Handle &&)> m_deleter;
};