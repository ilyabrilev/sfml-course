#pragma once
#include <vector>
#include <stdexcept>

template<typename T>
class TemplatedContainer
{
public:
    TemplatedContainer() {}
    virtual ~TemplatedContainer() {}

    void push_back(const T& value) { m_values.push_back(value); }

    const std::vector<T>& get_values() const { return m_values; }

    size_t size() const { return m_values.size(); }

    void clear() { m_values.clear(); }

    virtual void erase(int pos) { m_values.erase(m_values.begin() + pos); }

    T& operator[](size_t pos) { return m_values[pos]; }

    const T& operator[](size_t pos) const { return m_values[pos]; }

    T& at(size_t pos)
    {
        if (pos >= m_values.size()) 
        {
            throw std::out_of_range("Out of range");
        }
        return m_values[pos];
    }

    const T& at(size_t pos) const
    {
        if (pos >= m_values.size())
        {
            throw std::out_of_range("Out of range");
        }
        return m_values[pos];
    }

private:
    std::vector<T> m_values;
};

