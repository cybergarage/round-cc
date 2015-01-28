/******************************************************************
 *
 * Round for C++
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUNDCC_VECTOR_H_
#define _ROUNDCC_VECTOR_H_

#include <vector>
#include <stdlib.h>

#include <round/common/types.h>
#include <round/common/Mutex.h>

namespace Round {

////////////////////////////////////////
// Vector (Shared)
////////////////////////////////////////
  
template <typename T> class SharedVector : public std::vector< round_shared_ptr<T> > {

public:
    
  SharedVector() {
  }
    
  ~SharedVector() {
  }
    
  // add
    
  bool add(T *obj) {
    if (!obj)
      return false;
    if (0 <= indexOf(obj))
      return false;
    round_shared_ptr<T> sobj(obj);
    std::vector< round_shared_ptr<T> >::push_back(sobj);
    return true;
  }
    
  // insertAt
    
  bool insertAt(T *obj, size_t index) {
    if (!obj)
      return false;
    if (0 <= indexOf(obj))
      return false;
    round_shared_ptr<T> sobj(obj);
    std::vector< round_shared_ptr<T> >::insert((std::vector< round_shared_ptr<T> >::begin() + index), sobj);
    return true;
  }
    
  // get
    
  round_shared_ptr<T> get(size_t index) {
    if (std::vector< round_shared_ptr<T> >::size() < (index+1))
      return round_shared_ptr<T>((T*)NULL);
    return std::vector< round_shared_ptr<T> >::at(index);
  }
    
  // exists
    
  bool exists(round_shared_ptr<T> obj) {
    return (0 <= indexOf(obj)) ? true : false;
  }
    
  bool exists(T *obj) {
    return (0 <= indexOf(obj)) ? true : false;
  }
    
  // indexOf
    
  ssize_t indexOf(round_shared_ptr<T> obj) {
    if (!obj)
      return -1;
    size_t cnt = std::vector< round_shared_ptr<T> >::size();
    for (size_t n = 0; n < cnt; n++) {
      if (obj == std::vector< round_shared_ptr<T> >::at(n))
        return n;
    }
    return -1;
  }
    
  ssize_t indexOf(T *obj) {
    if (!obj)
      return -1;
    size_t cnt = std::vector< round_shared_ptr<T> >::size();
    for (size_t n = 0; n < cnt; n++) {
      round_shared_ptr<T> sobj = std::vector< round_shared_ptr<T> >::at(n);
      if (obj == sobj.get())
        return n;
    }
    return -1;
  }
    
  // remove
    
  bool remove(size_t idx) {
    size_t size = std::vector< round_shared_ptr<T> >::size();
    if ((size <= 0) || (size < (idx+1)))
      return false;
    typename std::vector< round_shared_ptr<T> >::iterator objIt = std::vector< round_shared_ptr<T> >::begin() + idx;
    std::vector< round_shared_ptr<T> >::erase(objIt);
    return true;
  }
    
  bool remove(round_shared_ptr<T> obj) {
    if (!obj)
      return false;
    return remove(indexOf(obj));
  }
    
  bool remove(T *obj) {
    if (!obj)
      return false;
    return remove(indexOf(obj));
  }

  // lock
  
  void lock() const {
    this->mutex.lock();
  }
  
  // unlock
  
  void unlock() const  {
    this->mutex.lock();
  }
  
private:
  
  mutable Mutex mutex;
};
  
////////////////////////////////////////
// Vector (Weak)
////////////////////////////////////////
  
template <typename T> class WeakVector : public std::vector<T*> {
    
public:
  
  WeakVector() {
  }
    
  ~WeakVector() {
  }
    
  // add
    
  bool add(T *obj) {
    if (!obj)
      return false;
    if (0 <= indexOf(obj))
      return false;
    std::vector<T*>::push_back(obj);
    return true;
  }
    
  // insertAt
    
  bool insertAt(T *obj, size_t index) {
    if (!obj)
      return false;
    if (0 <= indexOf(obj))
      return false;
    std::vector<T*>::insert(std::vector<T*>::begin() + index, obj);
    return true;
  }
    
  // get
    
  T *get(size_t index) {
    if (std::vector<T*>::size() < (index+1))
      return NULL;
    return std::vector<T*>::at(index);
  }
    
  // exists
    
  bool exists(void *obj) {
    return (0 <= indexOf(obj)) ? true : false;
  }
    
  // indexOf
    
  ssize_t indexOf(void *obj) {
    if (!obj)
      return -1;
    size_t cnt = std::vector<T*>::size();
    for (size_t n = 0; n < cnt; n++) {
      if (obj == ((T *)std::vector<T*>::at(n)))
        return n;
    }
    return -1;
  }
    
  // remove
    
  bool remove(T *obj) {
    if (!obj)
      return false;
    ssize_t idx = indexOf(obj);
    if (idx < 0)
      return false;
    typename std::vector<T*>::iterator objIt = std::vector<T*>::begin() + idx;
    std::vector<T*>::erase(objIt);
    return true;
  }
  
  // lock
  
  void lock() const {
    this->mutex.lock();
  }
  
  // unlock
  
  void unlock() const {
    this->mutex.lock();
  }
  
private:
  
  mutable Mutex mutex;
};
  
////////////////////////////////////////
// Vector
////////////////////////////////////////
  
template <typename T> class Vector : public WeakVector<T> {
    
public:
    
  Vector() {
    setWeekContainer(false);
  }
    
  ~Vector() {
    clear();
  }
    
  void setWeekContainer(bool flag) {
    this->weekContainerFlag = flag;
  }
    
  bool isWeekContainer() {
    return this->weekContainerFlag;
  }
    
  // remove
    
  bool remove(T *obj) {
    if (!WeakVector<T>::remove(obj))
      return false;
    if (!isWeekContainer()) {
      delete obj;
    }
    return true;
  }
    
  // clear
    
  bool clear() {
    if (!isWeekContainer()) {
      for (typename std::vector<T*>::iterator objIt = std::vector<T*>::begin() ; objIt != std::vector<T*>::end(); ++objIt) {
        T* obj = dynamic_cast<T*>(*objIt);
        if (!obj)
          continue;
        delete obj;
      }
    }
    std::vector<T*>::clear();
    return true;
  }
    
private:
  bool weekContainerFlag;
};

}

#endif
