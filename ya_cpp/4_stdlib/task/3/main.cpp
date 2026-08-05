#include <vector>
#include <algorithm>
#include <iostream>
#include <cstdio>

struct Point {
    int x = 0;
    int y = 0;

    bool operator<(const Point& other) const {
        if (x != other.x) {
            return x < other.x;
        }
        return y < other.y;
    }
};

void GUI_Plot(Point* points, size_t n) {
    for (size_t i = 0; i < n; ++i) {
        printf("%d : %d\n", points[i].x, points[i].y);
    }
}

int main() {
    size_t n;
    std::cin >> n;

    std::vector<Point> points;
    points.reserve(n);

    for (size_t i = 0; i < n; ++i) {
        Point p;
        std::cin >> p.x >> p.y;

        points.emplace_back(p);
    }

    std::sort(points.begin(), points.end());

    GUI_Plot(points.data(), points.size());

    return 0;
} 