template<typename Derived>
class Comparable {
public:
    bool operator != (const Derived& rhs) const{
        return !(static_cast<const Derived&>(*this) == rhs);
    }
};