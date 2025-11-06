#include "Triangle.h"
#include <cassert>

int Triangle::_call = 0;
std::ofstream Triangle::_out("Triangle.txt");

Triangle::Triangle(const double x1, const double y1, const double x2, const double y2, const double x3, const double y3) :
	_a(x1, y1), _b(x2, y2), _c(x3, y3), 
	_ab(nullptr), _bc(nullptr), _ca(nullptr),
	_midAb(nullptr), _midBc(nullptr), _midCa(nullptr),
	_medA(nullptr), _medB(nullptr), _medC(nullptr)
{
	++_call;
	assert(area() != 0);
	return;
}

Triangle::Triangle(const Point& a, const Point& b, const Point& c) :
	_a(a), _b(b), _c(c), 
	_ab(nullptr), _bc(nullptr), _ca(nullptr),
	_midAb(nullptr), _midBc(nullptr), _midCa(nullptr),
	_medA(nullptr), _medB(nullptr), _medC(nullptr)
{
	++_call;
	std::cout << area() << '\n';
	assert(area() > 0);
	return;
}

Triangle::Triangle(const Triangle& t) :
	_a(t._a), _b(t._b), _c(t._c), 
	_ab(nullptr), _bc(nullptr), _ca(nullptr),
	_midAb(nullptr), _midBc(nullptr), _midCa(nullptr),
	_medA(nullptr), _medB(nullptr), _medC(nullptr)
{
	++_call;
	return;
}

Triangle::~Triangle()
{
	++_call;
	// checking for nullptr value might be faster than deleting even if it is nullptr 
	if (_ab != nullptr) delete _ab;
	if (_bc != nullptr) delete _bc;
	if (_ca != nullptr) delete _ca;

	if (_medA != nullptr)
	{
		delete _medA;
		delete _midBc;
	}
	if (_medB != nullptr)
	{
		delete _medB;
		delete _midCa;
	}
	if (_medC != nullptr)
	{
		delete _medC;
		delete _midAb;
	}

	return;
}

Triangle& Triangle::operator= (const Triangle& t)
{
	++_call;
	if (this == &t) return *this;

	setA(t.getA());
	setB(t.getB());
	setC(t.getC());
	update();

	return *this;
}

double Triangle::perimeter() const
{
	++_call;
	return side_a().length() + side_b().length() + side_c().length();
}


double Triangle::area() const
{
	++_call;
	double a = side_a().length();
	double b = side_b().length();
	double c = side_c().length();
	double p = (a + b + c) * 0.5;
	return sqrt(p * (p - a) * (p - b) * (p - c));
}

const Point Triangle::findMiddle(const Point& a, const Point& b) const 
{
	++_call;
	return { (a.x() + b.x()) / 2, (a.y() + b.y()) / 2 };
}

inline const Point& Triangle::getA() const
{
	++_call;
	return _a;
}

inline const Point& Triangle::getB() const
{
	++_call;
	return _b;
}

inline const Point& Triangle::getC() const
{
	++_call;
	return _c;
}

inline void Triangle::setA(const Point& p)
{
	++_call;
	_a.x() = p.x();
	_a.y() = p.y();
	update();
}

inline void Triangle::setA(int x, int y)
{
	++_call;
	_a.x() = x;
	_a.y() = y;
	update();
}

inline void Triangle::setB(const Point& p)
{
	++_call;
	_b.x() = p.x();
	_b.y() = p.y();
	update();
}

inline void Triangle::setB(int x, int y)
{
	++_call;
	_b.x() = x;
	_b.y() = y;
	update();
}

inline void Triangle::setC(const Point& p)
{
	++_call;
	_c.x() = p.x();
	_c.y() = p.y();
	update();
}

inline void Triangle::setC(int x, int y)
{
	++_call;
	_c.x() = x;
	_c.y() = y;
	update();
}

const Triangle::Segment & Triangle::side_a() const
{
	++_call;
	if (_bc == nullptr)
	{
		_bc = new Segment(getB(), getC());
	}
	return *_bc;
}

const Triangle::Segment& Triangle::side_b() const  
{
	++_call;
	if (_ca == nullptr)
	{
		_ca = new Segment(getC(), getA());
	}
	return *_ca;
}

const Triangle::Segment& Triangle::side_c() const
{
	++_call;
	if (_ab == nullptr)
	{
		_ab = new Segment(getA(), getB());
	}
	return *_ab;
}

const Triangle::Segment& Triangle::median_a() const
{
	++_call;
	if (_medA == nullptr)
	{
		_midBc = new Point( findMiddle(getB(), getC()) );
		_medA = new Segment(getA(), *_midBc);
	}
	return *_medA;
}

const Triangle::Segment& Triangle::median_b() const
{
	++_call;
	if (_medB == nullptr)
	{
		_midCa = new Point( findMiddle(getC(), getA()) );
		_medB = new Segment(getB(), *_midCa);
	}
	return *_medB;
}

const Triangle::Segment& Triangle::median_c() const
{
	++_call;
	if (_medC == nullptr)
	{
		_midAb = new Point( findMiddle(getA(), getB()) );
		_medC = new Segment(getC(), *_midAb);
	}
	return *_medC;
}

void Triangle::update()
{
	++_call;
	if (_medC != nullptr)
	{
		*_midAb = findMiddle(getA(), getB());
	}
	if (_medA != nullptr)
	{
		*_midBc = findMiddle(getB(), getC());
	}
	if (_medB != nullptr)
	{
		*_midCa = findMiddle(getC(), getA());
	}
}

std::ostream& Triangle::show(std::ostream& os) const
{
	os << "Triangle: " << getA() << getB() << getC() << '\n';
	os << side_a();
	os << side_b();
	os << side_c();
	os << "perimeter " << perimeter() << '\n';
	os << "area      " << area() << '\n';
	return os;
}

std::ostream& operator<<(std::ostream& os, const Triangle::Segment& u)
{
	os << u.getID() << '[' << u.start() << ',' << u.end() << ']' << '\n';
	return os;
}

int Triangle::epilog()
{
	_out << "N calls " << _call << '\n';
	return _call;
}

std::ostream& operator<<(std::ostream& os, const Triangle& t)
{
	return t.show(os);
}