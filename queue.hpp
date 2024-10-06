#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <cstddef>
#include <cstdlib>
#include <stdexcept>

template <typename T> struct Queue {
private:
  size_t start;
  size_t end;
  size_t capacity;
  T *buffer;

public:
  Queue() : start(0), end(0), capacity(0), buffer(nullptr) {}

  ~Queue() {
    if (buffer != nullptr) {
      free(buffer);
    }
  }

  size_t len() const {
    if (this->capacity == 0)
      return 0;
    return (end - start + capacity) % capacity;
  }

  void enqueue(const T &t) {
    if (capacity == 0) {
      capacity = 8;
      buffer = (T *)malloc(sizeof(T) * capacity);
      if (!buffer) {
        throw std::bad_alloc();
      }
    } else if (len() == capacity - 1) {
      // Resize and copy elements over
      size_t new_capacity = capacity * 2;
      T *new_buffer = (T *)malloc(sizeof(T) * new_capacity);
      if (!new_buffer) {
        throw std::bad_alloc();
      }

      // Copy elements from start to end
      for (size_t i = 0; i < len(); ++i) {
        new_buffer[i] = buffer[(start + i) % capacity];
      }

      free(buffer);
      buffer = new_buffer;
      start = 0;
      end = capacity - 1; // Reposition end correctly
      capacity = new_capacity;
    }

    buffer[end] = t;
    end = (end + 1) % capacity;
  }

  T dequeue() {
    if (len() == 0) {
      throw std::out_of_range("Queue is empty");
    }
    T value = buffer[start];
    start = (start + 1) % capacity;
    return value;
  }

  T &peek() const {
    if (len() == 0) {
      throw std::out_of_range("Queue is empty");
    }
    return buffer[start];
  }

  bool is_empty() const { return this->len() == 0; }
};

#endif // QUEUE_HPP
