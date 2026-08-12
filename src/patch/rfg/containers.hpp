#pragma once

#include "os/timestamp.hpp"
#include <cstddef>

namespace rfg {
template <class T> class base_array {
  public:
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using iterator = T*;
    using const_iterator = const T*;
    using size_type = std::size_t;

    T& operator[](int index) { return elements[index]; }

    int size() { return num_elements; }
    int length() { return num_elements; }
    int capacity() { return array_size; }

    // Returns pointer to start of elements
    T* begin() { return elements; }

    // Returns pointer to start of elements
    const T* begin() const { return elements; }

    // Returns pointer to end of elements
    // To get the last member, use back() instead.
    T* end() { return elements + num_elements; }

    // Returns pointer to end of elements
    // To get the last member, use back() instead.
    const T* end() const { return elements + num_elements; }

    // Returns reference to first member of elements
    T& front() { return *elements; }

    // Returns reference to first member of elements
    const T& front() const { return *elements; }

    // Returns reference to last member of elements
    T& back() { return elements[array_size - 1]; }

    // Returns reference to last member of elements
    const T& back() const { return elements[array_size - 1]; }

  private:
    void* virtual_function_Ptr;
    T* elements;
    int array_size;
    int num_elements;
};

// Todo: Reverse the constructor for this to make sure this is correct.
// Todo: Make sure that the index operator [] is working for this.
template <class T, unsigned int InitialSize> class farray : public base_array<T> {
  public:
    T data[InitialSize];
};

template <class T> class __attribute__((aligned(4))) object_stream_resource {
  public:
    bool loaded() { return m_loaded; }
    T* get_data() { return m_loaded ? &m_data : nullptr; }

  private:
    T m_data;
    bool m_loaded = false;
};

template <class T, unsigned int unknown> class et_ptr_offset {
  public:
    int m_offset;
};

template <class T> class multi_sim_state {
  public:
    int m_states_used;
    T m_states[25];
    rfg::timestamp m_apply_correction_timestamp;
};

template <class T, unsigned int size> class circ_array {
  public:
    T data[size];
    int num;
    int offset;
};

template <class T, unsigned int size> class circ_array_queue {
  public:
    circ_array<T, size> array;
    int num;
};
} // namespace rfg