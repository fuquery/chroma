
#pragma once
#include <mutex>
#include <utility>
#include <chroma>

class locked_context {
public:
  explicit locked_context(std::mutex& mtx) : m_mutex(&mtx) { m_mutex->lock(); }

  ~locked_context() {
    if (m_mutex != nullptr) {
      m_mutex->unlock();
    }
  }

  locked_context(locked_context&& other) noexcept
      : m_mutex(std::exchange(other.m_mutex, nullptr)) {}

  locked_context& operator=(locked_context&& other) noexcept {
    if (this != &other) {
      if (m_mutex != nullptr) {
        m_mutex->unlock();
      }
      m_mutex = std::exchange(other.m_mutex, nullptr);
    }
    return *this;
  }

  locked_context(const locked_context&)            = delete;
  locked_context& operator=(const locked_context&) = delete;

  [[nodiscard]] chroma::color<locked_context> context() const {
    if (m_mutex == nullptr) {
      throw std::runtime_error("Invalid context");
    }
    return {};
  }

  static constexpr auto error_message = "not in locked context";

private:
  std::mutex* m_mutex;
};
