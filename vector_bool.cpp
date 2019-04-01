//#include "myvector.hpp"

const int _BYTESIZE = 8;


vbool::vbool(uint64_t& v_block, int ind):
    target(v_block),
    index(ind)
{ }


vbool::operator bool() const
{
    uint64_t tmp = 1;
    tmp <<= (sizeof(uint64_t)*_BYTESIZE - index - 1);
    tmp &= target;
    tmp >>= (sizeof(uint64_t)*_BYTESIZE - index - 1);
    return static_cast<bool>(tmp);
}


vbool& vbool::operator = (bool val)
{
    uint64_t tmp = 1;
    if (val){
        tmp <<= (sizeof(uint64_t)*_BYTESIZE - index - 1);
        target |= tmp;
    }
    else{
        tmp <<= (sizeof(uint64_t)*_BYTESIZE - index - 1);
        tmp = ~tmp;
        target &= tmp;
    }
    return *this;
}


Vector<bool>::Vector(): 
    _data(nullptr),
    _memsize(1),
    _size(0)
{
    _data = new (__FILE__, __LINE__) uint64_t[_memsize]();
}


Vector<bool>::Vector(const Vector<bool>& item):
    _data(nullptr),
    _memsize(item._memsize),
    _size(item._size)
{
    _data = new (__FILE__, __LINE__) uint64_t[item._memsize]();
    for (int i = 0; i < item._memsize; i++)
        _data[i] = item._data[i];
}


Vector<bool>::Vector(int memsize):
    _data(nullptr),
    _memsize(memsize),
    _size(memsize*sizeof(uint64_t)*_BYTESIZE)
{
    _data = new (__FILE__, __LINE__) uint64_t[_memsize]();
}


Vector<bool>::~Vector()
{
    DELETE(_data);
}


void Vector<bool>::push_back(bool item)
{
    if (_size == _memsize)
        reserve(_memsize + 1);
    
    ++_size;
    at(_size - 1) = item;
}


vbool Vector<bool>::operator [] (size_t index)
{
    return at(index);
}


vbool Vector<bool>::at(size_t index)
{
    if (index >= _size)
        throw MyException("Index is out of range.");
    
    return {_data[index / (sizeof(uint64_t)*_BYTESIZE)],
            (int) index % ((int)sizeof(uint64_t)*_BYTESIZE)};
}


void Vector<bool>::resize(size_t newsize)
{
    if (!newsize)
        throw MyException("Memory size shouldn't be 0.");

    uint64_t *__tmp = new (__FILE__, __LINE__) uint64_t[newsize]();
    
    if (newsize*sizeof(uint64_t)*_BYTESIZE < _size)
        _size = newsize*sizeof(uint64_t)*_BYTESIZE;

    for (int i = 0; i < newsize; i++)
        __tmp[i] = _data[i];

    DELETE(_data);
    _data = __tmp;

    _memsize = newsize;
    _size    = newsize * sizeof(uint64_t)*_BYTESIZE;
}


void Vector<bool>::reserve(size_t new_memsize)
{
    if (new_memsize*sizeof(uint64_t)*_BYTESIZE < _size)
        throw MyException("Vector::reserve : attempt to lose data.");
    
    uint64_t *__tmp = new (__FILE__, __LINE__) uint64_t[new_memsize];

    for (int i = 0; i < _memsize; i++)
        __tmp[i] = _data[i];

    DELETE(_data);
    _data = __tmp;

    _memsize = new_memsize;
}


bool Vector<bool>::is_empty() const
{
    return _size == 0;
}

//measured in bits
size_t Vector<bool>::size() const
{
    return _size;
}

//measured in 64-bit blocks
size_t Vector<bool>::mem_size() const 
{
    return _memsize;
}


void Vector<bool>::shrink()
{
    uint64_t *__tmp = new (__FILE__, __LINE__) uint64_t[_size / (sizeof(uint64_t)*8) + 1];

    for (int i = 0; i < _size; i++)
        __tmp[i] = _data[i];

    DELETE(_data);
    
    _data = __tmp;
    _memsize = _size / (sizeof(uint64_t)*8) + 1;
}


Vector<bool>& Vector<bool>::operator = (Vector<bool> item)
{
    std::swap(this->_data, item._data);
    std::swap(this->_memsize, item._memsize);
    std::swap(this->_size, item._size);

    return *this;
}

Vector<bool>& Vector<bool>::operator = (Vector<bool>&& item){
    std::swap(this->_data, item._data);
    std::swap(this->_memsize, item._memsize);
    std::swap(this->_size, item._size);

    return *this;
}
