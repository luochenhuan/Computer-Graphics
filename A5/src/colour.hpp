#ifndef COLOUR_HPP
#define COLOUR_HPP

#include <iostream>
/***********************  Colour  **********************************/
class Colour
{
public:
  Colour(double r, double g, double b)
    : r_(r)
    , g_(g)
    , b_(b)
  {}
  Colour(double c)
    : r_(c)
    , g_(c)
    , b_(c)
  {}
  Colour(const Colour& other)
    : r_(other.r_)
    , g_(other.g_)
    , b_(other.b_)
  {}

  Colour& operator =(const Colour& other)
  {
    r_ = other.r_;
    g_ = other.g_;
    b_ = other.b_;
    return *this;
  }

  double R() const
  {
    return r_;
  }
  double G() const
  {
    return g_;
  }
  double B() const
  {
    return b_;
  }


  double r_;
  double g_;
  double b_;
};

inline Colour operator *(double s, const Colour& a)
{
  return Colour(s*a.R(), s*a.G(), s*a.B());
}

inline Colour operator *(const Colour& a, const Colour& b)
{
  return Colour(a.R()*b.R(), a.G()*b.G(), a.B()*b.B());
}

inline Colour operator +(const Colour& a, const Colour& b)
{
  return Colour(a.R()+b.R(), a.G()+b.G(), a.B()+b.B());
}

inline Colour operator -(const Colour& a, const Colour& b)
{
    return Colour(a.R()-b.R(), a.G()-b.G(), a.B()-b.B());
}

inline std::ostream& operator <<(std::ostream& os, const Colour& c)
{
  return os << "c<" << c.R() << "," << c.G() << "," << c.B() << ">";
}

#endif
