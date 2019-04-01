/*
    Vector member functions and operators
    implementation.
*/


//For memory usage logging (UNIX based systems only)
#define NEW(size) new (__FILE__, __LINE__) DataT[size] //operator new[] overloaded

#ifdef LOG_ENABLED
    #include <fstream>
    #include <string>
    #include <sys/time.h>

    timeval tm;
    int c = gettimeofday(&tm, NULL);
    std::ofstream logfile("log/[" + std::to_string((int)tm.tv_usec) + "]-memory_usage.log");

    //operator delete[] cannot be overloaded properly, which leads to using the macros
    #define DELETE(data)    logfile << "Free \t [" << data << "]  \t: \t\t\t| "                             \
                                    << std::string(__FILE__) << '\t' << " line: " << __LINE__ << std::endl; \
                            delete[] data;
#else
    #define DELETE(data) delete[] data;
#endif



//Constructors implementation
template<typename DataT> Vector<DataT>::Vector(): 
    _data(nullptr),
    _memsize(__DATABLOCK),
    _size(0)
{
    _data = NEW(__DATABLOCK)();
}


template<typename DataT> Vector<DataT>::Vector(const Vector<DataT>& item):
    _data(nullptr),
    _memsize(item._memsize),
    _size(item._size)
{
    _data = NEW(item._memsize)();
    for (int i = 0; i < item._size; i++)
        _data[i] = item._data[i];
}


template<typename DataT> Vector<DataT>::Vector(Vector<DataT>&& item):
    _data(item._data),
    _memsize(item._memsize),
    _size(item._size)
{
    item._data = nullptr;
}


template<typename DataT> Vector<DataT>::Vector(int memsize):
    _data(nullptr),
    _memsize(memsize),
    _size(memsize)

{
    _data = NEW(memsize)();
}


template<typename DataT> Vector<DataT>::Vector(const std::initializer_list<DataT>& arglist):
    _data(nullptr),
    _memsize(arglist.size()),
    _size(arglist.size())
{   
    _data = NEW(arglist.size())();
    int i = 0;
    for (const DataT& item : arglist)
    {
        _data[i] = item;
        i++;
    }
}


template<typename DataT> Vector<DataT>::~Vector()
{
    DELETE(_data);
}


//Methods implementation
template<typename DataT> size_t Vector<DataT>::size() const
{
    return _size;
}


template<typename DataT> size_t Vector<DataT>::mem_size() const
{
    return _memsize;
}


template<typename DataT> void Vector<DataT>::resize(size_t newsize)
{
    if (newsize < __DATABLOCK)
        newsize = __DATABLOCK;

    DataT *__tmp = NEW(newsize)();
    
    if (newsize < _size)
        _size = newsize;

    for (int i = 0; i < _size; i++)
        __tmp[i] = _data[i];

    DELETE(_data);
    _data = __tmp;

    _memsize = newsize;
    _size    = newsize;
}


template<typename DataT> void Vector<DataT>::reserve(size_t new_memsize)
{
    if (new_memsize < __DATABLOCK)
        new_memsize = __DATABLOCK;

    DataT *__tmp = NEW(new_memsize);
    
    if (new_memsize < _size)
        throw MyException("Vector::reserve : attempt to lose data.(new_memsize < size)");

    for (int i = 0; i < _size; i++)
        __tmp[i] = _data[i];

    DELETE(_data);
    _data = __tmp;

    _memsize = new_memsize;
}


template<typename DataT> void Vector<DataT>::push_back(const DataT& item)
{
    if (_size >= _memsize)
        reserve(2*_memsize);

    _data[_size] = item;
    _size++;
}


template<typename DataT> void Vector<DataT>::pop_back()
{
    if (_size == 0)
        throw MyException("Delete attempt from empty container");

    _size--;
}


template<typename DataT> bool Vector<DataT>::is_empty() const
{
    return _size == 0;
}


template<typename DataT> const DataT& Vector<DataT>::at(size_t index) const
{
    if (index >= _size)
        throw MyException("Index is out of range");

    return _data[index];
}


template<typename DataT> DataT& Vector<DataT>::at(size_t index)
{
    if (index >= _size)
        throw MyException("Index is out of range");

    return _data[index];
}


template<typename DataT> void Vector<DataT>::insert(const DataT& item, const size_t index)
{
    if (index >= _size)
        throw MyException("Index is out of range");

    if (_size >= _memsize)
        reserve(2*_memsize);
        
    for (int i = _size; i > index; i--)
        _data[i] = _data[i - 1];

    _data[index] = item;
    _size++;
}


template<typename DataT> void Vector<DataT>::shrink()
{
    DataT *__tmp = NEW(_size)();

    for (int i = 0; i < _size; i++)
        __tmp[i] = _data[i];

    DELETE(_data);
    
    _data = __tmp;
    _memsize = _size;
}


//Operators implementation
template<typename DataT> bool operator == (const Vector<DataT>& a, const Vector<DataT>& b)
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


template<typename DataT> bool operator != (const Vector<DataT>& a, const Vector<DataT>& b)
{
    if (a.size() == b.size())
    {
        for(int i = 0; i < a.size(); i++)
            if (a.at(i) != b.at(i))
                return true;
    }
    else return true;

    return false;
}


template<typename DataT> bool operator > (const Vector<DataT>& a, const Vector<DataT>& b)
{
    if (a.size() != b.size())
        return a.size() > b.size();

    for (int i = 0; i < a.size(); i++)
        if (a[i] != b[i])
            return a[i] > b[i];
    
    return false;
}


template<typename DataT> bool operator < (const Vector<DataT>& a, const Vector<DataT>& b)
{
    if (a.size() != b.size())
        return a.size() < b.size();

    for (int i = 0; i < a.size(); i++)
        if (a[i] != b[i])
            return a[i] < b[i];
    
    return false;
}


template<typename DataT> const DataT& Vector<DataT>::operator [] (const size_t index) const
{
    return at(index);
}


template<typename DataT> DataT& Vector<DataT>::operator [] (const size_t index)
{
    return at(index);
}


template<typename DataT> Vector<DataT>& Vector<DataT>::operator = (Vector<DataT> item)
{
    std::swap(this->_data, item._data);
    std::swap(this->_memsize, item._memsize);
    std::swap(this->_size, item._size);

    return *this;
}

template<typename DataT> Vector<DataT>& Vector<DataT>::operator = (Vector<DataT>&& item)
{
    std::swap(this->_data, item._data);
    std::swap(this->_memsize, item._memsize);
    std::swap(this->_size, item._size);

    return *this;
}


void* operator new[] (size_t size, const char file[], int line)
{
    void* tmp = new char[size];

    #ifdef LOG_ENABLED
        logfile << "Alloc \t [" << tmp << "] " << '\t' << ": " << size
                << " bytes" << '\t' << "| " << std::string(file) << '\t' 
                << " line: " << line << std::endl; 
    #endif

    return tmp;
}
