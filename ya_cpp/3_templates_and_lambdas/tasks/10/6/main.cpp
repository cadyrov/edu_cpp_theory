template<typename Any>
class Comparable {
public:
    friend bool operator!=(const Any& a, const Any& b) {
        return !(a == b);
    }
};  


class Point: public Comparable<Point>{
public:
    int x_ = 0;
    int y_ = 0;

    friend bool operator==(const Point& a, const Point& b) {
        return a.x_ == b.x_ && a.y_ == b.y_;
    }
};