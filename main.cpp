
class Point3d
{
public:

	float i, j, k;

	Point3d()
	{ }

	Point3d(float x, float y, float z)
	{
		i = x;
		j = y;
		k = z;
	}

	Point3d operator+ (const Point3d &point) const 
	{
		Point3d p;
		p.i = i + point.i;
		p.j = j + point.j;
		p.k = k + point.k;
		return p;
	}

	Point3d operator- (const Point3d &point) const 
	{
		Point3d p;
		p.i = i - point.i;
		p.j = j - point.j;
		p.k = k - point.k;
		return p;
	}

	Point3d operator* (float f) const
	{
		Point3d p;
		p.i = i * f;
		p.j = j * f;
		p.k = k * f;
		return p;
	}

	float dotProduct (const Point3d &point) const
	{
		float ret = (i * point.i) + (j * point.j) + (k * point.k);
		return ret;
	}

	Point3d crossProduct(const Point3d &point) const
	{
		Point3d p;
		p.i = (point.k * j) - (point.j * k);
		p.j = (point.i * k) - (point.k * i);
		p.k = (point.j * i) - (point.i * j);
		return p;
	}
};

#include "iostream"

class Quaternion
{
public:

	float scalar;
	Point3d vector;
	const char *name;

	Quaternion()
	{ }

	Quaternion(const char *n, float w, Point3d vec)
	{
		name = n;
		scalar = w;
		vector = vec;
	}

	void printQuat() const
	{
		printf("--> [ %.2f , %.2fi %.2fj %.2fk ]\n", scalar, vector.i, vector.j, vector.k);
	}

	const Quaternion &operator+= (const Quaternion& q)
	{
		scalar += q.scalar;
		vector.i += q.vector.i;
		vector.j += q.vector.j;
		vector.k += q.vector.k;
		return (*this);
	}

	 Quaternion operator+ (const Quaternion& q) const
	{
		Quaternion p;
		p.name = name;
		p.scalar = scalar + q.scalar;
		p.vector.i = vector.i + q.vector.i;
		p.vector.j = vector.j + q.vector.j;
		p.vector.k = vector.k + q.vector.k;
		return p;
	}

	 Quaternion operator- (const Quaternion& q) const
	 {
		 Quaternion p;
		 p.name = name;
		 p.scalar = scalar - q.scalar;
		 p.vector.i = vector.i - q.vector.i;
		 p.vector.j = vector.j - q.vector.j;
		 p.vector.k = vector.k - q.vector.k;
		 return p;
	 }

	 Quaternion &operator-()
	 {
		 scalar = -scalar;
		 vector.i = -vector.i;
		 vector.j = -vector.j;
		 vector.k = -vector.k;
		 return (*this);
	 }

	Quaternion operator* (Quaternion &quat) const
	{
		Quaternion q;
		q.scalar = (scalar * quat.scalar) - (vector.dotProduct(quat.vector));
		q.vector = (quat.vector * scalar) + (vector * quat.scalar) + (vector.crossProduct(quat.vector));
		return q;
	}

	Quaternion &inverse()
	{
		vector.i = -vector.i;
		vector.j = -vector.j;
		vector.k = -vector.k;
		return (*this);
	}
};

#define _USE_MATH_DEFINES
#include <math.h>

int main(int argc, char **argv)
{
	//  - - - - - Data - - - - - 
	// Angles
	float alpha = M_PI / 5;
	float beta = 2 * M_PI / 19;
	float theta = M_PI / 5;

	// Coeficients
	float a0 = cos(alpha / 2.0f) * cos(beta / 2.0f) * cos(theta / 2.0f) - sin(alpha / 2.0f) * sin(beta / 2.0f) * sin(theta / 2.0f);
	float b0 = sin(alpha / 2.0f) * cos(beta / 2.0f) * cos(theta / 2.0f) + cos(alpha / 2.0f) * sin(beta / 2.0f) * sin(theta / 2.0f);
	float c0 = cos(alpha / 2.0f) * sin(beta / 2.0f) * cos(theta / 2.0f) - sin(alpha / 2.0f) * cos(beta / 2.0f) * sin(theta / 2.0f);
	float d0 = cos(alpha / 2.0f) * cos(beta / 2.0f) * sin(theta / 2.0f) + sin(alpha / 2.0f) * sin(beta / 2.0f) * cos(theta / 2.0f);

	float a1 = 0;
	float b1 = cos(alpha) * sin(beta);
	float c1 = sin(alpha) * sin(beta);
	float d1 = cos(beta);

	float a2 = cos(theta / 2.0f);
	float b2 = cos(alpha) * sin(beta) * sin(theta / 2.0f);
	float c2 = sin(alpha) * sin(beta) * sin(theta / 2.0f);
	float d2 = cos(beta) * sin(theta / 2.0f);

	float a3 = 0;
	float b3 = -sin(alpha) * sin(beta);
	float c3 = cos(alpha) * sin(beta);
	float d3 = 0;

	float a4 = 0;
	float b4 = cos(alpha) * cos(beta);
	float c4 = sin(alpha) * cos(beta);
	float d4 = -sin(beta);

	Quaternion q0("q0", a0, { b0, c0, d0 });
	Quaternion q1("q1", a1, { b1, c1, d1 });
	Quaternion q2("q2", a2, { b2, c2, d2 });
	Quaternion q3("q3", a3, { b3, c3, d3 });
	Quaternion q4("q4", a4, { b4, c4, d4 });
	Quaternion q5("q5", 0 , { 0, 4.0f, 1.0f });
	Quaternion p0("p0", 0, { 9.0f, 8.0f, 0.0f });
	Quaternion p1("p0", 0, { 10.0f, 7.0f, 1.0f });

	printf("List of quaternion operations:\n");
	(q1 * q2).printQuat();
	(q2 * q1).printQuat();
	(q0 - (q1*q2)).printQuat();
	(q0 - (q2*q1)).printQuat();
	(q2 * q1).printQuat();
	q2.inverse().printQuat();
	(q2 * (-p0) * q2.inverse()).printQuat();
	(q2 * p1 * q2.inverse()).printQuat();
	(q2 * (p1 - p0) * q2.inverse()).printQuat();
	(q2 * q1 * q2.inverse()).printQuat();
	(q2 * q1.inverse() * q2.inverse()).printQuat();
	(q2 * q3 * q2.inverse()).printQuat();
	(q2 * q4 * q2.inverse());
	(q2 * (q1 + q2) * q2.inverse()).printQuat();
	(q2 * (q1 + q4) * q2.inverse()).printQuat();
	(q2 * (p1 - p0) * q2.inverse() + q5).printQuat();
	(q2 * q1 * q2.inverse() + q5).printQuat();
	(q2 * (q1 + q2) * q2.inverse() + q5).printQuat();
	(q2 * (q1 + q4) * q2.inverse() + q5).printQuat();	
	getchar();

	return 0;
}