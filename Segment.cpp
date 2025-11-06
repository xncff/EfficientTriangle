#include "Triangle.h"
#include <cassert>
#include <cmath>

std::ofstream Triangle::Segment::_out("Segment.txt");
int Triangle::Segment::_freeID = 0;
int Triangle::Segment::_call = 0;

Triangle::Segment::Segment(const Point& a, const Point& b) :
	_a(a), _b(b), _myId(++_freeID)
{
	++_call;
#ifndef NDEBUG
	_out << _myId << ": a Segment was created: " << *this;
#endif
}

Triangle::Segment::Segment(const Triangle::Segment& s) : _a(s._a), _b(s._b), _myId(++_freeID)
{
	++_call;
#ifndef NDEBUG
	_out << _myId << ": a Segment was copied: " << *this;
#endif
}

Triangle::Segment::~Segment()
{
	++_call;
#ifndef NDEBUG
	_out << _myId << ": a Segment was deleted: " << *this;
#endif
}

double Triangle::Segment::length() const
{
	++_call;
	return sqrt((_a.x() - _b.x()) * (_a.x() - _b.x()) + (_a.y() - _b.y()) * (_a.y() - _b.y()));
}

const Point& Triangle::Segment::start() const
{
	++_call;
	return _a;
}
const Point& Triangle::Segment::end() const
{
	++_call;
	return _b;
}

int Triangle::Segment::epilog()
{
	_out << "N calls " << _call << " Total amount of created Segments " << _freeID << '\n';
	return _freeID;
}
