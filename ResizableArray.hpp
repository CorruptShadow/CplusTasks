template <typename T>
class ResizableArray {
 private:
  int capacity_;  // maximale Kapazität
  T* array_;      // Zeiger auf das C-Array an sich
 public:
  ResizableArray(int initial_capacity = 4)
      : capacity_{initial_capacity}, n_{0} {
    array_ = new T[capacity_];  // allokiere den Speicher für das Array
  }

  ~ResizableArray() { delete[] array_; }

  // füge x am Ende des Arrays ein (verdoppelt evtl. die Kapazität)
  void push_back(T x) {
    if (n_ == capacity_) {
      capacity_ *= 2;                   // verdoppele capacity_
      T* tmp_array = new T[capacity_];  // fordere neuen Speicherbereich an
                                        // (doppelt so gross)
      for (int i = 0; i < n_; ++i)
        tmp_array[i] = array_[i];  // kopiere Elemente
      delete[] array_;  // loesche alten Speicher, da nicht mehr beoetigt
      array_ = tmp_array;
    }
    array_[n_++] = x;  // speichert den Wert x am Ende des Arrays
  }

  // entferne das letzte Element des Arrays und gib es zurück
  T pop_back() {
    if (n_ > 0) {
      T lastElement = array_[n_ - 1];
      n_--;

      if (n_ < capacity_ / 4 && capacity_ > 4) {
        capacity_ /= 2;
        T* tmp_array = new T[capacity_];
        for (int i = 0; i < n_; i++) {
          tmp_array[i] = array_[i];
        }
        delete[] array_;
        array_= tmp_array;
      }
      return lastElement;

    } else {
      return T();
    }
  }

  T operator[](int i) { return read(i); }  // Indexoperator

  T operator()() {
    printf("Hallo\n");
    return T();
  }  // Klammeroperator sinnlos

  T read(int i) const {
    if (i < 0 || i > n_ - 1) return T();  // index out of bounds
    return array_[i];
  }

  void write(int i, T x) {
    if (i < 0 || i > n_ - 1) return;
    array_[i] = x;  // speichere an der Stelle i den Wert x
  }

  int n_;  // # Elemente im Array
};