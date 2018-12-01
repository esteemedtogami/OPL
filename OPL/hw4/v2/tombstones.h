template <class T>
class Tombstone
{
 public:
  Tombstone<T>(){data = NULL;}
  ~Tombstone<T>(){delete data;}
  T get_data() {return data;}
  void set_data(T arg) {data = arg;}
  T* data;
};


template <class T>
class Pointer {
public:
  Pointer<T>() {} // default constructor
 
  Pointer<T>(Pointer<T>& arg) {tomb->data = arg.tomb->data;}
  // copy constructor
 
  Pointer<T>(T* arg) {tomb->data = arg;} // bootstrapping constructor
 // argument should always be a call to new
 
  ~Pointer<T>() {delete tomb;} // destructor
 
  T& operator*() const {return *(tomb->data);} // dereferencing
 
  T* operator->() const {return (tomb->data);} // field dereferencing
 
 Pointer<T>& operator=(const Pointer<T>& arg)
   {tomb->data = arg.tomb->data; return *this;}
 // assignment

 friend void free(Pointer<T>& arg) {arg.tomb->~Tombstone<T>();}
 // delete pointed-at object
 // This is essentially the inverse of the new inside the call to
 // the bootstrapping constructor. It should delete the pointed-to
 // object (which should in turn call its destructor).
 
 // equality comparisons:
 
 bool operator==(const Pointer<T>& arg) const
 {return tomb->data == arg.tomb->data;}
 
 bool operator!=(const Pointer<T>& arg) const
 {return tomb->data != arg.tomb->data;}
 
 bool operator==(const int arg) const
 {if(tomb->data == NULL && arg == 0)return true; else return false;}
 // true iff Pointer is null and int is zero
 
 bool operator!=(const int arg) const
 {if(tomb->data == NULL && arg == 0)return false; else return true;}
 // false iff Pointer is null and int is zero

 private:
 Tombstone<T>* tomb;
};
template <class T>
bool operator==(const int n, const Pointer<T>& t) { return t == n; }
template <class T>
bool operator!=(const int n, const Pointer<T>& t) { return t != n; }
