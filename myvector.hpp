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
    ~Vector() noexcept;
    Vector(int memsize);
    Vector(const Vector<DataT>&  item);
    Vector(      Vector<DataT>&& item) noexcept;
    Vector(const std::initializer_list<DataT>& arglist);

    size_t size() const noexcept;
    size_t mem_size() const noexcept;
    void   push_back(const DataT& item);
    void   pop_back();
    void   insert(const DataT& item, const size_t index);
    bool   is_empty() const noexcept;
    void   resize(size_t newsize);
    void   shrink();
    void   reserve(size_t new_memsize);

    const DataT& at(size_t index) const;
    DataT&       at(size_t index);

    const DataT&   operator [] (const size_t index) const;
    DataT&         operator [] (const size_t index);
    Vector<DataT>& operator =  (Vector<DataT> item)   noexcept;
    Vector<DataT>& operator =  (Vector<DataT>&& item) noexcept;

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
    operator bool() const             noexcept;
    vbool& operator = (bool val)      noexcept;
    vbool& operator = (vbool val)     noexcept;
    vbool() = delete;
    vbool(uint64_t& v_block, int ind) noexcept;
    void set_index(size_t ind)        noexcept;

private:
    uint64_t& target;
    size_t index;
};


/*
    Bit compact Vector<bool> class specification
*/
template<>
class Vector<bool>{
public:
    Vector();
    ~Vector() noexcept;
    Vector(int memsize);
    Vector(const Vector<bool>&  item);
    Vector(      Vector<bool>&& item) noexcept;
    Vector(const std::initializer_list<bool>& arglist);

    size_t size() const noexcept;
    size_t mem_size() const noexcept;
    void   push_back(bool item);
    void   pop_back();
    void   insert(bool item, size_t index);
    bool   is_empty() const noexcept;
    void   resize(size_t newsize);
    void   shrink();
    void   reserve(size_t new_memsize);

    vbool       at(size_t index);
    const vbool at(size_t index) const;


    vbool         operator [] (size_t index);
    const vbool   operator [] (size_t index) const;
    Vector<bool>& operator =  (Vector<bool> item) noexcept;
    Vector<bool>& operator =  (Vector<bool>&& item) noexcept;
    

private:
    uint64_t *_data;
    size_t _memsize;
    size_t _size;
};


#include "vector_impl.hpp"
#include "vector_bool.cpp"
