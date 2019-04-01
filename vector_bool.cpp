/*
    Vector<bool> (compact bit dynamic array) class members implementation
*/ 

const int _BYTESIZE = 8;
const int _BLOCKSIZE = 64;


vbool::vbool(uint64_t& v_block, int ind) noexcept:
    target(v_block),
    index(ind % _BLOCKSIZE)
{ }


vbool::operator bool() const noexcept
{
    uint64_t tmp = 1;
    tmp <<= (_BLOCKSIZE - index - 1);
    tmp &= target;
    tmp >>= (_BLOCKSIZE - index - 1);
    return static_cast<bool>(tmp);
}


void vbool::set_index(size_t ind) noexcept
{
    index = ind % _BLOCKSIZE;
}


vbool& vbool::operator = (bool val) noexcept
{
    uint64_t tmp = 1;
    if (val){
        tmp <<= (_BLOCKSIZE - index - 1);
        target |= tmp;
    }
    else{
        tmp <<= (_BLOCKSIZE - index - 1);
        tmp = ~tmp;
        target &= tmp;
    }
    return *this;
}


vbool& vbool::operator = (vbool val) noexcept
{
    operator = (bool(val));
    set_index(val.index);
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


Vector<bool>::Vector(Vector<bool>&& item) noexcept:
    _data(item._data),
    _memsize(item._memsize),
    _size(item._size)
{
    item._data = nullptr;
}


Vector<bool>::Vector(int memsize):
    _data(nullptr),
    _memsize(memsize),
    _size(memsize*_BLOCKSIZE)
{
    _data = new (__FILE__, __LINE__) uint64_t[_memsize]();
}


Vector<bool>::Vector(const std::initializer_list<bool>& arglist):
    _data(nullptr),
    _size(0),
    _memsize(0)
{
    Vector<bool>();   
    for (auto item : arglist)
        push_back(item);
}


Vector<bool>::~Vector() noexcept
{
    DELETE(_data);
}


void Vector<bool>::push_back(bool item)
{
    if (_size == _memsize*_BLOCKSIZE)
        reserve(_memsize + 1);
    
    ++_size;
    at(_size - 1) = item;
}


void Vector<bool>::pop_back()
{
    _size--;
}


void Vector<bool>::resize(size_t newsize)
{
    if (!newsize)
        throw MyException("Memory size shouldn't be 0.");

    uint64_t *__tmp = new (__FILE__, __LINE__) uint64_t[newsize]();
    
    if (newsize*_BLOCKSIZE < _size)
        _size = newsize*_BLOCKSIZE;

    for (int i = 0; i < newsize; i++)
        __tmp[i] = _data[i];

    DELETE(_data);
    _data = __tmp;

    _memsize = newsize;
    _size    = newsize * _BLOCKSIZE;
}


void Vector<bool>::reserve(size_t new_memsize)
{
    if (new_memsize*_BLOCKSIZE < _size)
        throw MyException("Vector::reserve : attempt to lose data.");
    
    uint64_t *__tmp = new (__FILE__, __LINE__) uint64_t[new_memsize];

    for (int i = 0; i < _memsize; i++)
        __tmp[i] = _data[i];

    DELETE(_data);
    _data = __tmp;

    _memsize = new_memsize;
}


void Vector<bool>::insert(bool item, size_t index)
{
    if (index >= _size)
        throw MyException("Index is out of range");

    push_back(0);
    for (int i = _size - 1; i > index; i--)
        at(i) = at(i - 1);

    at(index) = item;
}


vbool Vector<bool>::at(size_t index)
{
    if (index >= _size)
        throw MyException("Index is out of range.");
    
    return {_data[index / (_BLOCKSIZE)],
            (int) index % ((int)_BLOCKSIZE)};
}


const vbool Vector<bool>::at(size_t index) const
{
    if (index >= _size)
        throw MyException("Index is out of range.");
    
    return {_data[index / (_BLOCKSIZE)],
            (int) index % ((int)_BLOCKSIZE)};
}


bool Vector<bool>::is_empty() const noexcept
{
    return _size == 0;
}

//measured in bits
size_t Vector<bool>::size() const noexcept
{
    return _size;
}

//measured in 64-bit blocks
size_t Vector<bool>::mem_size() const noexcept
{
    return _memsize;
}


void Vector<bool>::shrink()
{
    uint64_t *__tmp = new (__FILE__, __LINE__) uint64_t[_size / (sizeof(uint64_t)*8) + 1];

    for (int i = 0; i < _size / _BLOCKSIZE + 1; i++)
        __tmp[i] = _data[i];

    DELETE(_data);
    
    _data = __tmp;
    _memsize = _size / (sizeof(uint64_t)*8) + 1;
}


Vector<bool>& Vector<bool>::operator = (Vector<bool> item) noexcept
{
    std::swap(this->_data, item._data);
    std::swap(this->_memsize, item._memsize);
    std::swap(this->_size, item._size);

    return *this;
}

Vector<bool>& Vector<bool>::operator = (Vector<bool>&& item) noexcept
{
    std::swap(this->_data, item._data);
    std::swap(this->_memsize, item._memsize);
    std::swap(this->_size, item._size);

    return *this;
}


vbool Vector<bool>::operator [] (size_t index)
{
    return at(index);
}


const vbool Vector<bool>::operator [] (size_t index) const
{
    return at(index);
}


bool operator == (const Vector<bool>& a, const Vector<bool>& b)
{
    if (a.size() == b.size())
    {
        for(int i = 0; i < a.size(); i++)
            if (a.at(i) != b.at(i))
                return false;
    }
    else return false;

    return true;
}
