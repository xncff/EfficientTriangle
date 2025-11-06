#include "Triangle.h"

int main()
{
	Point u, v(0, 3), w(4);

	std::cout << "Triangle composing apices======" << '\n';
	Triangle ABC(u, v, w);
	std::cout << "ABC " << ABC;
	std::cout << "median from apex C: " << ABC.median_c() << '\n' << '\n';

	Triangle a, b(2, 0, 2, 2, 0, 2), c(b);

	std::cout << "a " << a;
	std::cout << "median from apex A: " << a.median_a() << '\n';

	std::cout << "b " << b;
	std::cout << "median from apex B: " << b.median_b() << '\n';

	std::cout << "c " << c;
	std::cout << "median from apex C: " << c.median_c() << '\n';

	c = ABC;
	std::cout << "new value of c " << c;
	std::cout << "new median from apex C: " << c.median_c() << '\n' << '\n';

	std::cout << "Triangles " << Triangle::epilog() << '\n';
	std::cout << "Segments  " << Triangle::Segment::epilog() << '\n';
	std::cout << "Points    " << Point::epilog() << '\n';
}
