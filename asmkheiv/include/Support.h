#ifndef SUPPORT_H
#define SUPPORT_H
#include <memory>
template <typename U, typename T>
std::unique_ptr<U> dynamic_unique_cast(std::unique_ptr<T> &&ptr) {
  return std::unique_ptr<U>(dynamic_cast<U *>(ptr.release()));
}

#endif