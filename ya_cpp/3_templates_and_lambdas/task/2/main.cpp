#include <cstddef>   // std::byte, std::size_t
#include <iterator>  // std::distance
#include <memory>

template <typename T>
class Span {
public:
    using reference = T&;
    using const_reference = const T&;
    using pointer = T*;
    using const_pointer = const T*;
    using size_type = std::size_t;



    template <typename It>
    Span(It first, size_type count);

    template <typename It1, typename It2>
    Span(It1 first, It2 last);

    reference operator[](size_type idx);
    const_reference operator[](size_type idx) const;

    bool empty() const;

    pointer data();
    const_pointer data() const;

    size_type size() const;

    Span subspan(size_type offset, size_type count) {
        return Span{data_ + offset, count};
    }

private:
    pointer data_;
    size_type size_;
};

template <typename T>
Span<const std::byte> as_bytes(Span<T> span); 

template <typename T>
template <typename It>
Span<T>::Span(It first, size_type count) : data_(std::to_address(first)), size_(count) {
}

template <typename T>
template <typename It1, typename It2>
Span<T>::Span(It1 first, It2 last)
    : data_(std::to_address(first)),
      size_(static_cast<size_type>(std::distance(first, last))) {}

template <typename T>
typename Span<T>::reference Span<T>::operator[](size_type idx) {
    return data_[idx];
}

template <typename T>
typename Span<T>::const_reference Span<T>::operator[](size_type idx) const {
    return data_[idx];
}

template <typename T>
bool Span<T>::empty() const {
    return size_ == 0;
}

template <typename T>
typename Span<T>::pointer Span<T>::data() {
    return data_;
}

template <typename T>
typename Span<T>::const_pointer Span<T>::data() const {
    return data_;
}

template <typename T>
typename Span<T>::size_type Span<T>::size() const {
    return size_;
}

template <typename T>
Span<const std::byte> as_bytes(Span<T> span) {
    return {reinterpret_cast<const std::byte *>(span.data()), span.size() * sizeof(T)};
} 
