#include <stdexcept>
#include <exception>
#include <cstring>

struct ex_info{
    char* file;
    char* function;
    int line;
};

class MyException : public std::runtime_error {
public:
    MyException(const char* msg, const char* file, const char* function, const int line):
        std::runtime_error(msg),
        _file(),
        _func(),
        _line(line)
    {
        strcpy(_file, file);
        strcpy(_func, function);
    }
    
    MyException(const MyException& e) = default;
    MyException& operator = (const MyException& e) = delete;

    ex_info get_info()
    {
        return {_file, _func, _line};
    }

private:
    char _file[100];
    char _func[100];
    int  _line;
};

#define MyException(msg) MyException(msg, __FILE__, __FUNCTION__, __LINE__);
