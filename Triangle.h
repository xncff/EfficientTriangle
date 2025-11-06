#pragma once

#include "Point.h"

class Triangle
{
public:
	class Segment;

	Triangle(const double x1 = 0, const double y1 = 0,
			 const double x2 = 1, const double y2 = 0,
			 const double x3 = 0, const double y3 = 1);

	Triangle(const Point& a,
			 const Point& b,
			 const Point& c);

	Triangle(const Triangle&);
	~Triangle();
	Triangle& operator= (const Triangle&);

	double perimeter() const;
	double area() const;

	inline const Point& getA() const;
	inline const Point& getB() const;
	inline const Point& getC() const;

	inline void setA(const Point& p);
	inline void setA(int x, int y);
	inline void setB(const Point& p);
	inline void setB(int x, int y);
	inline void setC(const Point& p);
	inline void setC(int x, int y);

	const Segment& side_a() const;
	const Segment& side_b() const;
	const Segment& side_c() const;

	const Segment& median_a() const;
	const Segment& median_b() const;
	const Segment& median_c() const;

	static int epilog();

	std::ostream& show(std::ostream& os) const;

private:
	static std::ofstream _out;
	static int _call;
	Point _a, _b, _c;
	mutable Point *_midAb, *_midBc, *_midCa;
	mutable Segment *_ab, *_bc, *_ca;
	mutable Segment *_medA, *_medB, *_medC;

	void update();
	const Point findMiddle(const Point& a, const Point& b) const;
};

class Triangle::Segment
{
private:
	static int _call;
	static std::ofstream _out;
	static int _freeID;
	int _myId;
	const Point &_a, &_b;
public:
	Segment(const Point& start, const Point& end);
	Segment(const Segment&);
	~Segment();
	Segment& operator=(const Segment&) = delete;
	const Point& start() const;
	const Point& end() const;
	double length() const;
	const int getID() const { return _myId; }
	static int epilog();
};

std::ostream& operator<<(std::ostream&, const Triangle&);
std::ostream& operator<<(std::ostream&, const Triangle::Segment&);

