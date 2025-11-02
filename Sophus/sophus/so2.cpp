#include <iostream>
#include "so2.h"
#include "so3.h"

namespace Sophus
{

SO2::SO2()
  : unit_complex_(1.0, 0.0)   // 构造函数初始化成员变量
{}

SO2::SO2(const SO2 & other)
  : unit_complex_(other.unit_complex_) {}

SO2::SO2(const Matrix2d & R)
  : unit_complex_(0.5*(R(0,0)+R(1,1)),
                  0.5*(R(1,0)-R(0,1))) {}

SO2::SO2(const Complexd & complex)
  : unit_complex_(complex)
{
  assert(abs(unit_complex_) != 0);
  normalize();
}

SO2::SO2(double theta)
  : unit_complex_(SO2::exp(theta).unit_complex_) {}

void SO2::operator=(const SO2 & other)
{
  this->unit_complex_ = other.unit_complex_;
}

SO2 SO2::operator*(const SO2& other) const
{
  SO2 result(*this);
  result.unit_complex_ *= other.unit_complex_;
  result.normalize();
  return result;
}

void SO2::operator*=(const SO2& other)
{
  unit_complex_ *= other.unit_complex_;
  normalize();
}

Vector2d SO2::operator*(const Vector2d & xy) const
{
  // 使用局部变量提取 unit_complex_
  double r = unit_complex_.real();
  double i = unit_complex_.imag();
  return Vector2d(r*xy[0] - i*xy[1], i*xy[0] + r*xy[1]);
}

SO2 SO2::inverse() const
{
  return SO2(conj(unit_complex_));
}

Matrix2d SO2::matrix() const
{
  double r = unit_complex_.real();
  double i = unit_complex_.imag();
  Matrix2d R;
  R(0,0) = r;  R(0,1) = -i;
  R(1,0) = i;  R(1,1) = r;
  return R;
}

double SO2::Adj() const
{
  return 1.;
}

Matrix2d SO2::generator(int i)
{
  assert(i==0);
  return hat(1.);
}

double SO2::log() const
{
  return SO2::log(*this);
}

double SO2::log(const SO2 & other)
{
  return atan2(other.unit_complex_.imag(), other.unit_complex_.real());
}

SO2 SO2::exp(double theta)
{
  return SO2(Complexd(cos(theta), sin(theta)));
}

Matrix2d SO2::hat(double v)
{
  Matrix2d Omega;
  Omega <<  0, -v,
            v,  0;
  return Omega;
}

double SO2::vee(const Matrix2d & Omega)
{
  assert(fabs(Omega(1,0)+Omega(0,1))<SMALL_EPS);
  return Omega(1,0);
}

double SO2::lieBracket(double omega1, double omega2)
{
  return 0.;
}

void SO2::setComplex(const Complexd& complex)
{
  assert(abs(complex)!=0);
  unit_complex_ = complex;
  normalize();
}

void SO2::normalize()
{
  unit_complex_ /= abs(unit_complex_);
}

} // namespace Sophus
