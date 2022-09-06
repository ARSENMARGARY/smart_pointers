#include <iostream>
#include "unique_ptr.hpp"

// param ctor
template <typename T>
Uniq_ptr<T>::Uniq_ptr(T* ptr)
{
    m_ptr = ptr;
}

// move ctor
template <typename T>
Uniq_ptr<T>::Uniq_ptr(Uniq_ptr&& rhs)
{
    m_ptr = std::move(rhs.m_ptr);
    rhs.m_ptr = nullptr;
}

// move assignement operator

template <typename T>
Uniq_ptr<T>& Uniq_ptr<T>::operator=(Uniq_ptr<T>&& rhs)
{
    m_ptr = std::move(rhs.m_ptr);
    rhs.m_ptr = nullptr;
    return *this;
}

//dtor

template <typename T>
Uniq_ptr<T>::~Uniq_ptr()
{
    if (m_ptr)
    {
        delete m_ptr;
    }
    m_ptr = nullptr;
}

// operator*

template <typename T>
T& Uniq_ptr<T>::operator*()
{
    return *m_ptr;
}

// operator->

template <typename T>
T* Uniq_ptr<T>::operator->()
{
    return m_ptr;
}

// methods (release)

template <typename T>
T* Uniq_ptr<T>::release()
{
    if (!m_ptr)
    {
        return nullptr;
    }
    T* ptr = m_ptr;
    m_ptr = nullptr;
    return ptr;
}