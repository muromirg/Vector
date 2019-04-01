/*
    Vector class and member  functions declaration.
*/
#include "myexception.hpp"
#include <malloc.h>
#include <initializer_list>
#include <inttypes.h>


const size_t __DATABLOCK = 3; //minimum Vector data size (in DataT units)


template<typename DataT> class Vector{
public:
    Vector();
    ~Vector();
    Vector(int memsize);
    Vector(const Vector<DataT>&  item);
    Vector(      Vector<DataT>&& item);
    Vector(const std::initializer_list<DataT>& arglist);

    size_t size() const;
    size_t mem_size() const;
    void   push_back(const DataT& item);
    void   pop_back();
    void   insert(const DataT& item, const size_t index);
    bool   is_empty() const;
    void   resize(size_t newsize);
    void   shrink();
    void   reserve(size_t new_memsize);

    const DataT& at(size_t index) const;
    DataT&       at(size_t index);

    const DataT&   operator [] (const size_t index) const;
    DataT&         operator [] (const size_t index);
    Vector<DataT>& operator =  (Vector<DataT> item);
    Vector<DataT>& operator =  (Vector<DataT>&& item);

private:
    DataT *_data;
    size_t _memsize;
    size_t _size;
};

void* operator new[] (size_t size, const char file[], int line);

template<typename DataT> bool operator == (const Vector<DataT>& a, const Vector<DataT>& b);
template<typename DataT> bool operator >  (const Vector<DataT>& a, const Vector<DataT>& b);
template<typename DataT> bool operator <  (const Vector<DataT>& a, const Vector<DataT>& b);
template<typename DataT> bool operator != (const Vector<DataT>& a, const Vector<DataT>& b);


class vbool{
public:
    operator bool() const;
    vbool& operator = (bool val);
    vbool() = delete;
    vbool(uint64_t& v_block, int ind);

private:
    uint64_t& target;
    size_t index;
};

template<>
class Vector<bool>{
public:
    Vector();
    ~Vector();
    Vector(int memsize);
    Vector(const Vector<bool>&  item);
    Vector(      Vector<bool>&& item);

    size_t size() const;
    size_t mem_size() const;
    void   push_back(bool item);
    void   pop_back();
    void   insert(const bool& item, const size_t index);
    bool   is_empty() const;
    void   resize(size_t newsize);
    void   shrink();
    void   reserve(size_t new_memsize);

    vbool  at(size_t index);

    vbool         operator [] (size_t index);
    Vector<bool>& operator =  (Vector<bool> item);
    Vector<bool>& operator =  (Vector<bool>&& item);

private:
    uint64_t *_data;
    size_t _memsize;
    size_t _size;
};


#include "vector_impl.hpp"
#include "vector_bool.cpp"
