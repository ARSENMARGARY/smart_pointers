#ifndef SHARED_PTR
#define SHARED_PTR
#include <cstddef>
#include <ostream>

template <typename T>
class Shared_ptr
{
public:
    Shared_ptr();
    Shared_ptr(T*);
    Shared_ptr(const Shared_ptr&);
    Shared_ptr& operator=(const Shared_ptr&);
    Shared_ptr(Shared_ptr&&);
    Shared_ptr& operator=(Shared_ptr&&);
    ~Shared_ptr();
public:
    T* operator->();
    T& operator*();
    template <typename U, typename V>
    friend bool operator==(const Shared_ptr<U>&, const Shared_ptr<V>&);
    template <typename U, typename V>
    friend bool operator<(const Shared_ptr<U>&,const Shared_ptr<V>&);
    template <typename U, typename V>
    friend bool operator>(const Shared_ptr<U>&,const Shared_ptr<V>&);
    template <typename U, typename V>
    friend bool operator<=(const Shared_ptr<U>&,const Shared_ptr<V>&);
    template <typename U, typename V>
    friend bool operator>=(const Shared_ptr<U>&,const Shared_ptr<V>&);
    template <typename U, typename V>
    friend bool operator!=(const Shared_ptr<U>&,const Shared_ptr<V>&);
public:
    void reset();
    void swap(Shared_ptr&);
    T* get() const;
    Shared_ptr& operator[](std::ptrdiff_t);
    uint get_count() const;
    bool unique() const;
private:
    T* m_ptr = nullptr;
    uint* m_count_ptr = nullptr;
private:
    void clean_up();
};

// ctors

//default ctor
template <typename T>
Shared_ptr<T>::Shared_ptr() : m_ptr{nullptr}, m_count_ptr{new uint(0)}{}

// param ctor
template <typename T>
Shared_ptr<T>::Shared_ptr(T* ptr): m_ptr{ptr}, m_count_ptr{new uint(1)}{}

// copy ctor 
template <typename T>
Shared_ptr<T>::Shared_ptr(const Shared_ptr<T>& obj)
{
    this->m_ptr = obj.m_ptr;
    this->m_count_ptr = obj.m_count_ptr;
    if (obj.m_ptr)
    {
        ++(*this -> m_count_ptr);
    }
}

// copy assignment

template <typename T>
Shared_ptr<T>& Shared_ptr<T>::operator=(const Shared_ptr<T>& obj)
{
    clean_up();
    this->m_ptr = obj.m_ptr;
    this->m_count_ptr = obj.m_count_ptr;
    if (obj.m_ptr)
    {
        ++(*this -> m_count_ptr);
    }
}

// move ctor
template <typename T>
Shared_ptr<T>::Shared_ptr(Shared_ptr<T>&& obj)
{
    this->m_ptr = obj.m_ptr;
    this->m_count_ptr = obj.m_count_ptr;
    obj.m_ptr = obj.m_count_ptr = nullptr;
}

// copy assignment

template <typename T>
Shared_ptr<T>& Shared_ptr<T>::operator=(Shared_ptr<T>&& obj)
{
    clean_up();
    this->m_ptr = obj.m_ptr;
    this->m_count_ptr = obj.m_count_ptr;
    obj.m_ptr = obj.m_count_ptr = nullptr;
}

// dtor
template <typename T>
Shared_ptr<T>::~Shared_ptr()
{
    clean_up();
}

// operators 

// operator ->
template <typename T>
T* Shared_ptr<T>::operator->()
{
    return this->m_ptr;
}

// operator *
template <typename T>
T& Shared_ptr<T>::operator*()
{
    return this->m_ptr;
}

// methods

// reset
template <typename T>
void Shared_ptr<T>::reset()
{
    m_ptr = nullptr;
    m_count_ptr ? --m_count_ptr : ~Shared_ptr();
}

// swap
template <typename T>
void Shared_ptr<T>::swap(Shared_ptr<T>& obj)
{
    std::swap(m_ptr, obj.m_ptr);
    std::swap(m_count_ptr, obj.m_count_ptr);
}

// get

template <typename T>
T* Shared_ptr<T>::get() const
{
    return m_ptr;
}

// get_count

template <typename T>
uint Shared_ptr<T>::get_count() const
{
    return *m_count_ptr;
}

// unique

template <typename T>
bool Shared_ptr<T>::unique() const
{
    return (*m_count_ptr == 1);
}

// clean up

template <typename T>
void Shared_ptr<T>::clean_up()
{
    --(*m_count_ptr);
		if (!(*m_count_ptr))
		{
			if (m_ptr)
            {
				delete m_ptr;
            }
			delete m_count_ptr;
		}
}

// compare operators

// operator ==
template <typename U, typename V>
bool operator==(const Shared_ptr<U>& lhs, const Shared_ptr<V>& rhs)
{
    return lhs.get() == rhs.get();
}

// operator <
template <typename U, typename V>
bool operator<(const Shared_ptr<U>& lhs, const Shared_ptr<V>& rhs)
{
    return lhs.get() < rhs.get();
}

// operator >
template <typename U, typename V>
bool operator>(const Shared_ptr<U>& lhs, const Shared_ptr<V>& rhs)
{
    return lhs.get() > rhs.get();
}

// operator <=
template <typename U, typename V>
bool operator<=(const Shared_ptr<U>& lhs, const Shared_ptr<V>& rhs)
{
    return lhs.get() <= rhs.get();
}

// operator >=
template <typename U, typename V>
bool operator>=(const Shared_ptr<U>& lhs, const Shared_ptr<V>& rhs)
{
    return lhs.get() >= rhs.get();
}

// operator !=
template <typename U, typename V>
bool operator!=(const Shared_ptr<U>& lhs, const Shared_ptr<V>& rhs)
{
    return lhs.get() != rhs.get();
}

#endif