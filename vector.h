#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#include <ctime>
#include <chrono>

template <class T>
class MyVector {
public:
    MyVector() : _data(nullptr), _size(0), _capacity(0) {}

    ~MyVector() {
        for(size_t i = 0; i < _size; ++i)
            _alloc.destroy(_data + i);
        _alloc.deallocate(_data, _capacity);
    }

    MyVector(const MyVector& other) : _data(nullptr), _size(0), _capacity(0) {
        for (size_t i = 0; i < other._size; ++i)
            push_back(other._data[i]);
    }

    MyVector& operator=(const MyVector& other) {
        if (this != &other) {
            clear();
            for (size_t i = 0; i < other._size; ++i)
                push_back(other._data[i]);
        }
        return *this;
    }

     void push_back(const T& value) {
        if (_size >= _capacity) {
            size_t new_capacity = (_capacity == 0) ? 1 : _capacity * 2;
            T* new_data = _alloc.allocate(new_capacity);

            for (size_t i = 0; i < _size; ++i) {
                _alloc.construct(new_data + i, std::move_if_noexcept(_data[i]));
                _alloc.destroy(_data + i);
            }

            _alloc.deallocate(_data, _capacity);
            _data = new_data;
            _capacity = new_capacity;
        }

        _alloc.construct(_data + _size++, value);
    }
    T& operator[](size_t index) {
        return _data[index];
    }

    const T& operator[](size_t index) const {
        return _data[index];
    }

    size_t size() const {
        return _size;
    }
    void assign(size_t count, const T& value) {
        clear();
        ensure_capacity(count);
        for (_size = 0; _size < count; ++_size)
            _alloc.construct(_data + _size, value);
    }

    std::allocator<T>& get_allocator() {
        return _alloc;
    }
    void pop_back() {
        if (!empty()) {
            _alloc.destroy(_data + --_size);
        }
    }

    void swap(MyVector& other) noexcept {
        std::swap(_data, other._data);
        std::swap(_size, other._size);
        std::swap(_capacity, other._capacity);
    }
    T& at(size_t index) {
        if (index >= _size)
            throw std::out_of_range("index out of range");
        return _data[index];
    }

    const T& at(size_t index) const {
        if (index >= _size)
            throw std::out_of_range("index out of range");
        return _data[index];
    }

    T& front() { return at(0); }
    const T& front() const { return at(0); }

    T& back() { return at(_size - 1); }
    const T& back() const { return at(_size - 1); }

    T* data() noexcept { return _data; }
    const T* data() const noexcept { return _data; }

    bool empty() const noexcept { return _size == 0; }



    size_t capacity() const noexcept { return _capacity; }

    void resize(size_t count, const T& value = T()) {
        if (count > _size) {
            ensure_capacity(count);
            while (_size < count)
                push_back(value);
        } else if (count < _size) {
            for (size_t i = count; i < _size; ++i)
                _alloc.destroy(_data + i);
            _size = count;
        }
    }

private:
    std::allocator<T> _alloc;
    T* _data;
    size_t _size;
    size_t _capacity;

    void clear() {
        for (size_t i = 0; i < _size; ++i)
            _alloc.destroy(_data + i);
        _alloc.deallocate(_data, _capacity);
        _data = nullptr;
        _size = 0;
        _capacity = 0;
    }

    void ensure_capacity(size_t new_capacity) {
        if (new_capacity > _capacity) {
            T* new_data = _alloc.allocate(new_capacity);
            for (size_t i = 0; i < _size; ++i) {
                _alloc.construct(new_data + i, std::move_if_noexcept(_data[i]));
                _alloc.destroy(_data + i);
            }
            _alloc.deallocate(_data, _capacity);
            _data = new_data;
            _capacity = new_capacity;
        }
    }

};
class Timer {
    private:
        std::chrono::time_point<std::chrono::high_resolution_clock> start;
    public:
        Timer() : start{std::chrono::high_resolution_clock::now()} {}
        void reset() {
        start = std::chrono::high_resolution_clock::now();
        }
        double elapsed() const {
            return std::chrono::duration<double>
            (std::chrono::high_resolution_clock::now() - start).count();
    }
};

#endif // VECTOR_H_INCLUDED
