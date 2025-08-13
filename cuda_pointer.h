#include <assert.h>
// #include <cutil.h>

template <typename T>
struct cudaPointer{
  T *dev_pointer;
  T *host_pointer;
  int size;
  cudaPointer(){
    dev_pointer = NULL;
    host_pointer = NULL;
    size = 0;
  }
  //  ~cudaPointer(){
  // free();
  //  }
  void allocate(int _size){
    size = _size;
    void *p;
    cudaMalloc(&p, size * sizeof(T));
    assert(p);
    dev_pointer = (T*)p;
    cudaMallocHost(&p, size * sizeof(T));
    assert(p);
    host_pointer = (T*)p;
  }
  void free(){
    cudaFree(dev_pointer);
    cudaFreeHost(host_pointer);
    dev_pointer = NULL;
    host_pointer = NULL;
    size = 0;
  }
  void htod(int count){
    cudaMemcpy(dev_pointer, host_pointer, count * sizeof(T), cudaMemcpyHostToDevice);
  }
  void htod(){
    this->htod(size);
  }
  void dtoh(int count){
    cudaMemcpy(host_pointer, dev_pointer, count * sizeof(T), cudaMemcpyDeviceToHost);
  }
  void dtoh(){
    this->dtoh(size);
  }
  T &operator [] (int i){
    return host_pointer[i];
  }
  operator T* (){
    return dev_pointer;
  }
};
