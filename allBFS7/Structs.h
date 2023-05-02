template<typename T>
class Vector {
  public:
    Vector() : size_(0), capacity_(0), data_(0) {}
    ~Vector() {
      delete[] data_;
    }

    void resize() {
      int new_capacity = (capacity_ == 0 ? 1 : 2 * capacity_);
      T *new_data = new T[new_capacity];
      for (int i = 0; i < size_; i++) {
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

    int size() const {
      return size_;
    }
    int capacity() const {
      return capacity_;
    }

    T &operator[](int index) {
      return data_[index];
    }
    const T &operator[](int index) const {
      return data_[index];
    }
  private:
    int size_;
    int capacity_;
    T *data_;
};

class pair {
  public:
    int first, second;

    pair() {
      first = 0;
      second = 0;
    }

    pair(int a, int b) {
      first = a;
      second = b;
    }

    bool isEqual(pair p1) {
      return first == p1.first && second == p1.second;
    }
};

class Vec3b {
  public:
    short int r, g, b;

    Vec3b(int r, int g, int b) {
      this->r = r;
      this->g = g;
      this->b = b;
    }

    Vec3b() {
      this->r = 0;
      this->g = 0;
      this->b = 0;
    }

    bool isThisColor(Vec3b c) {
      int pro = c.r * r + c.g * g + c.b * b;
      float lenColor = sqrt((float)(c.r ^ 2 + c.g ^ 2 + c.b ^ 2));
      float lenBase = sqrt((float)(r ^ 2 + g ^ 2 + b ^ 2));

      float angle = acos(pro / (lenColor * lenBase));
      return abs(angle) < 0.2;
    }
};

class Trio {
  public:
    int first;
    int second;
    int floor;

    Trio(int first, int second, int floor) {
      this->first = first;
      this->second = second;
      this->floor = floor;
    }

    Trio() {
      this->first = 0;
      this->second = 0;
      this->floor = 0;
    }

    bool absEqual(Trio t) {
      return this->first == t.first && this->second == t.second && floor == t.floor;
    }

    bool coordsEqual(Trio t) {
      return this->first == t.first && this->second == t.second;
    }

    bool slideDetection(Trio t1) {
      return t1.floor == 1 || t1.floor == 2 || this->floor == 1 || this->floor == 2;
    }
};
