#pragma once
#define COLOR_THRESHOLD 400
#define WHITE_COLOR 1
#define BLUE_COLOR 2
#define BLACK_COLOR 3
#define SILVER_COLOR 4

template<typename T>
class Vector {
  public:
    Vector() : size_(0), capacity_(0), data_(0) {}
    ~Vector() {
      delete[] data_;
    }

    void resize() {
      long int new_capacity = (capacity_ == 0 ? 1 : 2 * capacity_);
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
    long int size_;
    long int capacity_;
    T *data_;
};

class pair {
  public:
    int8_t first, second;

    pair() {
      first = 0;
      second = 0;
    }

    pair(int8_t a, int8_t b) {
      first = a;
      second = b;
    }

    bool isEqual(pair p1) {
      return first == p1.first && second == p1.second;
    }
};

class Vec3b {
  public:
    float r, g, b;
    
    Vec3b(float r, float g, float b) {
      this->r = r;
      this->g = g;
      this->b = b;
    }

    Vec3b() {
      this->r = 0;
      this->g = 0;
      this->b = 0;
    }

    float module() {
      return sqrt(this->r * this->r + this->g * this->g + this->b * this->b);
    }

    float cosBetweenColors(Vec3b _color) {
      return (this->r * _color.r + this->g * _color.g + this->b * _color.b) / (this->module() * _color.module());
    }

    int getColor() {
      Vec3b color = Vec3b(this->r, this->g, this->b);
      Vec3b blackColor = Vec3b(-21000, -15000, -15000);
      Vec3b blueColor = Vec3b(-7800, -4000, -4000); //-8300 -2250 -1750
      Vec3b whiteColor = Vec3b(-1800, -1300, -1500);

      if(this->r < -12000) return BLACK_COLOR; //-15000
      else if(this->r + this->g + this->b > -2000) return SILVER_COLOR;//silver;
      else if(this->cosBetweenColors(blueColor) > this->cosBetweenColors(blackColor)) return BLUE_COLOR;//blue;
      else return WHITE_COLOR;
    }
};

class Trio {
  public:
    int8_t first;
    int8_t second;
    int8_t floor;

    Trio(int8_t first, int8_t second, int8_t floor) {
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

class CameraParams {
  public:
    int8_t first, second, floor, dir;
    bool camera;
    char letter;
    CameraParams(int8_t first, int8_t second, int8_t floor, int8_t dir, bool cam) {
      this->first = first;
      this->second = second;
      this->floor = floor;
      this->dir = dir;
      this->camera = cam;
      //this->letter = letter;
    }

    CameraParams() {
      this->first = 0;
      this->second = 0;
      this->floor = 0;
      this->dir = 0;
      this->camera = 0;
      //this->letter = '0';
    }

    bool isEqual(int first, int second, int fl, int dir, bool cam) {
      return this->first == first && this->second == second && this->floor == fl
             && this->dir == dir && this->camera == cam;
    }
};
