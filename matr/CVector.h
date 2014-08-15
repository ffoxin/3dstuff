#pragma once
#pragma warning(disable: 4351)

#include <functional>


template<typename T, size_t size>
class CVector
{
public:
    CVector() :
        _vector{ }
    {
        
    }
    CVector(const T* array_)
    {
        Copy(array_);
    }
    CVector(const CVector& vector_)
    {
        Copy(vector_._vector);
    }
    ~CVector()
    {

    }

    CVector& operator=(const CVector& vector_)
    {
        if (this != &vector_)
        {
            Copy(vector_._vector);
        }

        return *this;
    }
    CVector& operator=(const T* array_)
    {
        Copy(array_);

        return *this;
    }

    CVector& operator+=(const CVector& vector_)
    {
        Process(vector_._vector, [](T& item1, const T& item2)
        {
            item1 += item2;
        });

        return *this;
    }
    CVector& operator-=(const CVector& vector_)
    {
        Process(vector_._vector, [](T& item1, const T& item2)
        {
            item1 -= item2;
        });

        return *this;
    }
    CVector& operator*=(const T& value_)
    {
        for (size_t i = 0;
             i < size;
             ++i)
        {
            _vector[i] *= value_;
        }

        return *this;
    }

    T& operator[](size_t index_)
    {
        return _vector[index_];
    }
    const T& operator[](size_t index_) const
    {
        return _vector[index_];
    }

    template<typename T, size_t size>
    friend T operator*(const CVector<T, size>& vector1_, const CVector<T, size>& vector2_);

private:
    void Process(const T* vector_, std::function<void(T&, const T&)> lambda_)
    {
        for (size_t index = 0;
             index < size;
             ++index)
        {
            lambda_(_vector[index], vector_[index]);
        }
    }
    void Process(const T* vector_, std::function<void(const T&, const T&)> lambda_) const
    {
        for (size_t index = 0;
             index < size;
             ++index)
        {
            lambda_(_vector[index], vector_[index]);
        }
    }
    void Copy(const T* vector_)
    {
        Process(vector_, [](T& item1, const T& item2)
        {
            item1 = item2;
        });
    }

private:
    T _vector[size];

};

template<typename T, size_t size>
T operator*(const CVector<T, size>& vector1_, const CVector<T, size>& vector2_)
{
    T result = T();
        
    vector1_.Process(vector2_._vector, [&](const T& item1, const T& item2)
    {
        result += item1 * item2;
    });

    return result;
}

template<typename T, size_t size>
std::ostream& operator<<(std::ostream& os_, const CVector<T, size>& vector_)
{
    for (size_t index = 0;
         index < size;
         ++index)
    {
        os_ << vector_[index] << ", ";
    }

    return os_;
}

template<typename T, size_t size>
CVector<T, size> operator*(const CVector<T, size>& vector_, const T& value_)
{
    CVector<T, size> result = vector_;
    result *= value_;
    return result;
}
