
template <typename Derived> class Cloneable {
  public:
    Derived clone() const {
        return static_cast<const Derived&>(*this);
    }
};