#pragma once

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
    int r;
    int g;
    int b;

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

    double cosBetweenColors(Vec3b color2) {
      return (r * color2.r + g * color2.g + b * color2.b) / (Vec3b(r, g, b).module() * Vec3b(r, g, b).module());
    }

    double module() {
      return sqrt(r * r + g * g + b * b);
    }

    int getColor(Vec3b whiteColor, Vec3b blueColor, Vec3b blackColor) {
      if (whiteColor.cosBetweenColors(Vec3b(r, g, b)) > 0.998) {
        Serial.println("WHITE");
        return 1;
      }
      else if (blueColor.cosBetweenColors(Vec3b(r, g, b)) > 0.998) {
        Serial.println("BLUE");
        return 2;
        //state = 7;
        //colorBase = 1;
      } else if (blackColor.cosBetweenColors(Vec3b(r, g, b)) > 0.998) {
        Serial.println("BLACK");
        return 3;
      }
      else {
        Serial.println("NO COLOR");
        return 0;
      }
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

class CameraParams {
  public:
    int first, second, floor, dir;
    bool camera;
    char letter;
    CameraParams(int first, int second, int floor, int dir, bool cam, char letter) {
      this->first = first;
      this->second = second;
      this->floor = floor;
      this->dir = dir;
      this->camera = cam;
      this->letter = letter;
    }

    CameraParams() {
      this->first = 0;
      this->second = 0;
      this->floor = 0;
      this->dir = 0;
      this->camera = 0;
      this->letter = '0';
    }

    bool isEqual(int first, int second, int fl, int dir, bool cam, char letter) {
      return this->first == first && this->second == second && this->floor == fl 
            && this->dir == dir && this->camera == cam && this->letter == letter;
    }
};
