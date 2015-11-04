
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

	Point3d &operator+ (const Point3d &point)
	{
		Point3d p;
		p.i = i + point.i;
		p.j = j + point.j;
		p.k = k + point.k;
		return p;
	}

	Point3d &operator- (const Point3d &point)
	{
		Point3d p;
		p.i = i - point.i;
		p.j = j - point.j;
		p.k = k - point.k;
		return p;
	}

	float dotProduct (Point3d &point) const
	{
		float ret = (i * point.i) + (j * point.j) + (k * point.k);
		return ret;
	}

	Point3d crossProduct(Point3d &point) const
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
		printf("%s --> [ %f , %fi %fj %fk ]\n", name, scalar, vector.i, vector.j, vector.k);
	}

	const Quaternion &operator+= (const Quaternion& q)
	{
		scalar += q.scalar;
		vector.i += q.vector.i;
		vector.j += q.vector.j;
		vector.k += q.vector.k;
		return (*this);
	}

	Quaternion operator* (Quaternion &quat) const
	{
		Quaternion q;
		q.scalar = (scalar * quat.scalar) - (vector.dotProduct(quat.vector));

		return q;
	}
};

int main(int argc, char **argv)
{
	Quaternion q1("q1", 34, { 3, 2, 5 });
	Quaternion q2("q2", 34, { 3, 2, 5 });

	printf("List of quaternion operations:");
	q1 += q2;
	q1.printQuat();

	getchar();

	return 0;
}