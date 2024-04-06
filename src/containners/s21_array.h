#ifndef _ARRAY_H_
#define _ARRAY_H_

#include <iostream>


namespace s21 {
    template <class T, std::size_t N>
    class array{
        private:
        value_type array_[N] = {};
        size_type size_ = N;

        //Consr-s
        array();
        array(std::initializer_list<value_type> const &items);
        array(const array &a);
        array(array &&a);

        //Dest-r
        ~array()
            
        //Type
        using value_type = T;
        using reference = T &;
        using const_reference = const T &;
        using iterator = T *;
        using const_iteratir = const T*;
        using size_type = std::size_t;

        //Iter
        iterator data();
        iterator begin();
        iterator end();

        //Operators
        array &operator=(const array &a) noexcept;
        array &operator=(array &&a) noexcept;
        reference operator[](size_type pos);

        //FUNC
        reference at(size_type pos);
        const_reference front();
        const_reference back();
        bool empty();
        size_type size();
        size_type max_size();
        void swap(array &other);
        void fill(const_reference value);

        void print();

        //Realization
        //Constructors
        template <class T, std::size_t N>
        array<T, N>::array() : size(N) {}
        template <class T, std::size_t N>
        array<T, N>::array(std::initializer_list<value_type> const &items) {
            for (auto iter = items.begin(), i = 0; iter != items.end(); ++iter, ++i) {
                array_[i] = *iter;
            }
        }
        template <class T, std::size_t N>
        array<T, N>::array(const array &a) { *this = a; }

        template <class T, std::size_t N>
        array<T, N>::array(array &&a) { *this = std::move(a); }

        //Destr
        template <class T, std::size_t N>
        array<T, N>::~array() { size_ = 0 }

        //Oper-s
        template <class T, std::size_t N>
        array<T, N> &array<T,N>::operator=(const array &a) noexcept {
            std::copy(a.array_, a.array_ + N, array_);
            return *this;
        }
        template <class T, std::size_t N>
        array<T, N> &array<T, N>::operator=(array &&a) noexcept {
        for (size_t i = 0; i < N; ++i) {
            array_[i] = std::move(a.array_[i]);
            a.array_[i] = 0;
            }
            return *this;
        }
        template <class T, std::size_t N>
        typename array<T, N>::reference array<T, N>::operator[](size_type pos) {
            return array_[pos];
        }
        //iter
        template <class T, std::size_t N>
        typename array<T, N>::iterator array<T, N>::data() {
            return N > 0 ? &array_[0] : 0;
        }

        template <class T, std::size_t N>
        typename array<T, N>::iterator array<T, N>::begin() {
            return N > 0 ? &array_[0] : 0;
        }

        template <class T, std::size_t N>
        typename array<T, N>::iterator array<T, N>::end() {
            return N > 0 ? &array_[N] : 0;
        }
        //func
        template <class T, std::size_t N>
        typename array<T, N>::reference array<T, N>::at(size_type pos) {
        if (pos >= N) throw std::out_of_range("Out of range");
        return array_[pos];
        }

        template <class T, std::size_t N>
        typename array<T, N>::const_reference array<T, N>::front() {
        if (empty()) throw "Array is empty";
        return array_[0];
        }

        template <class T, std::size_t N>
        typename array<T, N>::const_reference array<T, N>::back() {
        if (empty()) throw "Array is empty";
            return array_[N - 1];
        }

        template <class T, std::size_t N>
        bool array<T, N>::empty() {
            return N > 0 ? false : true;
        }

        template <class T, std::size_t N>
        typename array<T, N>::size_type array<T, N>::size() {
            return size_;
        }

        template <class T, std::size_t N>
        typename array<T, N>::size_type array<T, N>::max_size() {
            return N;
        }

        template <class T, std::size_t N>
        void array<T, N>::swap(array &other) {
        std::swap(array_, other.array_);
        std::swap(size_, other.size_);
        }

        template <class T, std::size_t N>
        void array<T, N>::fill(const_reference value) {
        for (size_t i = 0; i < N; ++i) {
            array_[i] = value;
        }
        }

        template <class T, std::size_t N>
        void array<T, N>::print() {
        for (size_t i = 0; i < N; ++i) {
            std::cout << array_[i];
        }
        std::cout << std::endl;
        };
    };
}

#endif