#include <Streaming.h>

template<typename T>
class Vector {
  public:
    Vector() : size_(0), capacity_(0), data_(0) {}
    ~Vector() { delete[] data_; }

    void resize() {
      int new_capacity = (capacity_ == 0 ? 1 : 2 * capacity_);
      T *new_data = new T[new_capacity];
      for (int i = 0; i < size_; i++) {
        //Serial << data_[i];
        //Serial << data_[i];
        //Serial << " ";
        //Serial.println();
        new_data[i] = data_[i];
      }
      capacity_ = new_capacity;
      //delete[] data_;
      data_ = new_data;
    }

    void push_back(const T &value) {
      if (size_ >= capacity_) {
        resize();
      }
      data_[size_++] = value;
    }

    void reverse() {
      T nn;
      for (int i = 0; i < size_ / 2; i++) {
        nn = data_[i];
        data_[i] = data_[size_ - i - 1];
        data_[size_ - i - 1] = nn;
      }
    }

    void pop_back() {
      size_--;
    }

    void clear() {
      size_ = 0;
    }

    int size() const { return size_; }
    int capacity() const { return capacity_; }

    T &operator[](int index) { return data_[index]; }
    const T &operator[](int index) const { return data_[index]; }

  private:
    int size_;
    int capacity_;
    T *data_;
};
