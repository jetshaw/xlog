#ifndef __xDOUBLE_BUFFER_H__
#define __xDOUBLE_BUFFER_H__

template <typename T>
class xdouble_buffer {
public:
    xdouble_buffer() : _cur_index(0){}
    ~xdouble_buffer(){}
public:
    typedef T DataType;
    DataType& get() { return buffer[_cur_index]; }
    DataType& get_next() { return buffer[1-_cur_index]; }
    void alter(){ _cur_index = 1-_cur_index;}
private:
    int _cur_index;
    DataType buffer[2];
};
#endif //__xDOUBLE_BUFFER_H__
