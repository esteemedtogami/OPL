template <typename T>
class Pointer;

template <typename T>
Pointer<T> free(Pointer<T>&); 


template <class T>
class Pointer {
public:
  Pointer<T>() {Tombstone();} // default constructor

  Pointer<T>(Pointer<T>& P)
    {this.Tombstone.get_data() = P->Tombstone.get_data();} // copy constructor

  Pointer<T>(T* P) {new Pointer<T>(P);} // bootstrapping constructor
 // argument should always be a call to new

  ~Pointer<T>(){delete this;} // destructor

  T& operator*() const {return *this.Tombstone.get_data();} // dereferencing
  
  T* operator->() const {return this.Tombstone.get_data();}
  //field dereferencing

  Pointer<T>& operator=(const Pointer<T>& P)
    {return *this = P;} // assignment

  friend void free(Pointer<T>& P){P->~Tombstone();}
  // delete pointed-at object
 // This is essentially the inverse of the new inside the call to
 // the bootstrapping constructor. It should delete the pointed-to
 // object (which should in turn call its destructor).

 // equality comparisons:

 bool operator==(const Pointer<T>& P) const {return this == P;}

 bool operator!=(const Pointer<T>& P) const {return this != P;}

 bool operator==(const int n) const
 {if(this.Tombstone.get_data()==0 && n==0)return true;else return false;}
 // true iff Pointer is null and int is zero

 bool operator!=(const int n) const
 {if(this.Tombstone.get_data()==0 && n==0)return false;else return true;}
 // false iff Pointer is null and int is zero

 private:
 class Tombstone
 {
 public:
   Tombstone() {data = 0;}
   Tombstone(T obj) {data = obj;}
   ~Tombstone(){delete &data;}
   void set_data(T obj) {data = obj;}
   T get_data() {return data;}
 private:
   T data;
 };
};

template <class T>
bool operator==(const int n, const Pointer<T>& t) { return t == n; }
template <class T>
bool operator!=(const int n, const Pointer<T>& t) { return t != n; }
