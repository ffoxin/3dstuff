#include <algorithm>
#include <iostream>
#include <list>
#include <vector>


typedef struct Point2d_s
{
    int x;
    int y;
} Point2d;

typedef std::list<Point2d> Points2dl;
typedef std::vector<Point2d> Points2dv;

std::ostream& operator<<(std::ostream& os, const Point2d& point)
{
    os << "{" << point.x << ", " << point.y << "}";
    return os;
}

void fill_triangle(const Point2d& p1,
                   const Point2d& p2,
                   const Point2d& p3)
{
    Points2dv points({ p1, p2, p3 });

    for (auto& point : points)
    {
        std::cout << point << std::endl;
    }
}

void fill_triangle(const Points2dv& points_)
{
    Points2dl points(points_.begin(), points_.end());
    Points2dv sorted_points(4);

    auto min = std::min_element(points.begin(),
                                points.end(),
                                [](const Point2d& point1, const Point2d& point2)
    {
        return point1.y < point2.y;
    });
    sorted_points[0] = *min;
    points.erase(min);

    auto max = std::max_element(points.begin(),
                                points.end(),
                                [](const Point2d& point1, const Point2d& point2)
    {
        return point1.y < point2.y;
    });
    sorted_points[3] = *max;
    points.erase(max);

    sorted_points[1] = points.front();

    sorted_points[2] = { sorted_points[0].x + (sorted_points[3].x - sorted_points[0].x)*(sorted_points[1].y - sorted_points[0].y) / (sorted_points[3].y - sorted_points[0].y),
        sorted_points[1].y };

    for (auto point : sorted_points)
    {
        std::cout << point << std::endl;
    }
}

int wmain(int argc, wchar_t* argv[])
{
    Point2d points[3] = {
            { 100, 0 },
            { 0, 200 },
            { 200, 300 }
    };

    Points2dv pdv1({ {100, 0}, { 0, 200 }, { 200, 300 } });
    Points2dv pdv2({ {100, 0}, { 200, 300 }, { 0, 200 } });
    Points2dv pdv3({ {0, 200}, { 100, 0 }, { 200, 300 } });
    Points2dv pdv4({ {0, 200}, { 200, 300 }, { 100, 0 } });
    Points2dv pdv5({ {200, 300}, { 100, 0 }, { 0, 200 } });
    Points2dv pdv6({ {200, 300}, { 0, 200 }, { 100, 0 } });

    fill_triangle(pdv1);
    fill_triangle(pdv2);
    fill_triangle(pdv3);
    fill_triangle(pdv4);
    fill_triangle(pdv5);
    fill_triangle(pdv6);

    return 0;
}
