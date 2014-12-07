#include "primitive.hpp"
#include <vector>

#include "mesh.hpp"
Primitive::~Primitive()
{
}


Sphere::Sphere()
{
	m_sphere = new NonhierSphere(Point3D(0.0, 0.0, 0.0), 1.0);
	m_BdBox = m_sphere->findBdBox();
}

Sphere::~Sphere()
{
	delete m_sphere;
}

BdBox Sphere::findBdBox()
{
	return m_BdBox;
}

InterPoint Sphere::intersect(Ray ray, bool drawBx) {
	return m_sphere->intersect(ray, drawBx);
}

Point2D Sphere::mapUV(Point3D pos)
{
	return m_sphere->mapUV(pos);
}

Cube::Cube()
{
	m_cube = new NonhierBox(Point3D(0,0,0), 1.0);
	m_BdBox = m_cube->findBdBox();
}

Cube::~Cube()
{
	delete m_cube;
}

BdBox Cube::findBdBox()
{
	return m_BdBox;
}

InterPoint Cube::intersect(Ray ray, bool drawBx) {
	return m_cube->intersect(ray,drawBx);
}

Point2D Cube::mapUV(Point3D pos)
{
	return m_cube->mapUV(pos);
}


/******************************  NonhierSphere  *******************************************/
NonhierSphere::~NonhierSphere()
{
}

BdBox NonhierSphere::findBdBox()
{
	Point3D minP = m_pos - Vector3D(m_radius, m_radius, m_radius);
	Point3D maxP = m_pos + Vector3D(m_radius, m_radius, m_radius);
	return BdBox(minP, maxP);
}

InterPoint NonhierSphere::intersect(Ray ray, bool drawBx) {

	InterPoint InterPt;
	/****************************  Bounding box **********************************/
	BdBox bounding = findBdBox();
	bool BoxSected = bounding.IsSected(ray);
	if (!BoxSected)
	{
		// std::cout << "nhSphere BdBox doesn't intersect" << std::endl;
		return InterPt;
	}

	if (drawBx)
	{
		return BBoxIntersect(bounding, ray);
	}
	// std::cout << "BdBox intersect" << std::endl;
	Vector3D sub = ray.pos - m_pos;
	double A = (ray.dir).length2();
	double B = (ray.dir).dot(sub);
	double C = sub.dot(sub) - m_radius * m_radius;
	double Delta = B*B - A*C;
	if (Delta >= 0.0)
	{
		Delta = sqrt(Delta);
		double inter_1 = (-B - Delta)/A;
		double inter_2 = (-B + Delta)/A;

		// if (inter_1 > EPSILON && inter_2 > EPSILON)
		// 	InterPt.t = inter_1;
		//
		// else if (inter_2 > EPSILON)
		// 	InterPt.t = inter_2;
		if (inter_1 > EPSILON && inter_2 > EPSILON)
			InterPt.t = inter_1;

			else if (inter_2 > EPSILON)
			InterPt.t = inter_2;
	}

	if (InterPt.t > 0) {
		InterPt.hit = true;
		// ray.dir.normalize();
		InterPt.pos = ray.pos + ray.dir  * InterPt.t;
		InterPt.n = InterPt.pos - m_pos;

		// Normal needs to be flipped if this is a refractive ray
		// if(InterPt.n.dot(ray.dir) > 0)
		// {
		// 	InterPt.n = -1.0 * InterPt.n;
		// 	std::cout << "sphere normal flipped" <<std::endl;
		// }
		// InterPt.n.normalize();
	}
	return InterPt;
}

Point2D NonhierSphere::mapUV(Point3D pos)
{
	Point2D uv;
	Vector3D pole = Vector3D(0,1,0);
	Vector3D equator = Vector3D(1,0,0);
	Vector3D n = pos - m_pos;
	n.normalize();
	double phi = acos(pole.dot(n));
	uv.v_[0] = phi/M_PI;

	double temp = n.dot(equator)/ sin(phi);
	if(temp > 1)
		temp = 1;
	else if (temp < -1)
		temp = -1;
	double Long = acos(temp) / (2*M_PI);
	if ( n.dot(pole.cross(equator)) > 0 )
		uv.v_[1] = Long;
	else
		uv.v_[1] = 1 - Long;

	return uv;
}

/******************************  NonhierCylinder  *******************************************/
NonhierCylinder::~NonhierCylinder()
{
}

// Ref: http://www.gamedev.net/topic/338522-bounding-box-for-a-cylinder/
BdBox NonhierCylinder::findBdBox()
{
	Point3D endP = m_pos + m_ori * m_height;
	Point3D minP;
	Point3D maxP;

	//x range
	if (m_pos.v_[0] < endP.v_[0])
	{
		minP.v_[0] = m_pos.v_[0] - m_radius;
		maxP.v_[0] =  endP.v_[0] + m_radius;
	}
	else
	{
		minP.v_[0] =  endP.v_[0] - m_radius;
		maxP.v_[0] = m_pos.v_[0] + m_radius;
	}

	//y range
	if (m_pos.v_[1] < endP.v_[1])
	{
		minP.v_[1] = m_pos.v_[1] - m_radius;
		maxP.v_[1] =  endP.v_[1] + m_radius;
	}
	else
	{
		minP.v_[1] =  endP.v_[1] - m_radius;
		maxP.v_[1] = m_pos.v_[1] + m_radius;
	}

	//z range
	if (m_pos.v_[2] < endP.v_[2])
	{
		minP.v_[2] = m_pos.v_[2] - m_radius;
		maxP.v_[2] =  endP.v_[2] + m_radius;
	}
	else
	{
		minP.v_[2] =  endP.v_[2] - m_radius;
		maxP.v_[2] = m_pos.v_[2] + m_radius;
	}

	return BdBox(minP, maxP);
}
/************************
Ref:http://mrl.nyu.edu/~dzorin/cg05/lecture12.pdf
	http://woo4.me/wootracer/cylinder-intersection/
	http://www.cl.cam.ac.uk/teaching/2000/AGraphHCI/SMEG/node2.html#eqn:rectray
************************/
InterPoint NonhierCylinder::intersect(Ray ray, bool drawBx)
{
	InterPoint InterPt;
	std::vector<double> T_set;
	Vector3D delta_p = ray.pos - m_pos;

	double v_dot_mpos = ray.dir.v_[0]*m_ori.v_[0] + ray.dir.v_[1]*m_ori.v_[1] + ray.dir.v_[2]*m_ori.v_[2];
	Vector3D temp = delta_p-delta_p.dot(m_ori) * m_ori;

	double A =   (ray.dir - v_dot_mpos*m_ori).length2();
	double B = 2*(ray.dir - v_dot_mpos*m_ori).dot(temp);
	double C = temp.length2() - m_radius*m_radius;

	double Delta = B*B - 4*A*C;
	if (Delta <0)
		return InterPt;

	Delta = sqrt(Delta);
	double inter_1 = (-B - Delta)/(2*A);
	double inter_2 = (-B + Delta)/(2*A);

	Point3D q1 = ray.pos + inter_1*ray.dir;
	Point3D q2 = ray.pos + inter_2*ray.dir;
	Point3D p1 = m_pos;
	Point3D p2 = m_pos + m_height * m_ori;

	if ((m_ori.dot(q1-p1) > 0.0) && (m_ori.dot(q1-p2) < 0.0))
	{
		T_set.push_back(inter_1);
	}

	if ((m_ori.dot(q2-p1) > 0.0) && (m_ori.dot(q2-p2) < 0.0))
	{
		T_set.push_back(inter_2);
	}

	// check with caps
	Vector3D PsubP_1 = ray.pos - p1;
	double inter_3, inter_4;

	if (m_ori.dot(ray.dir) != 0)
	{
		inter_3 = -1.0 * m_ori.dot(PsubP_1) / m_ori.dot(ray.dir);
		Vector3D PsubP_2 = ray.pos - p2;
		inter_4 = -1.0 * m_ori.dot(PsubP_2) / m_ori.dot(ray.dir);

		Vector3D q3 = PsubP_1 + inter_3*ray.dir;
		Vector3D q4 = PsubP_2 + inter_4*ray.dir;

		if(inter_3 > 0)
		{
			if (q3.length2() < m_radius*m_radius)
			{
				T_set.push_back(inter_3);
			}
		}

		if(inter_4 > 0)
		{
			if (q4.length2() < m_radius*m_radius)
			{
				T_set.push_back(inter_4);
			}
		}
	}
	// find closest intersection
	if (!T_set.empty())
	{
		double min_T = *std::min_element(std::begin(T_set),std::end(T_set));
		InterPt.hit = true;
		InterPt.t = min_T;
		// ray.dir.normalize();
		InterPt.pos = ray.pos + ray.dir * InterPt.t;

		if (min_T == inter_1 || min_T == inter_2)
		// find norm for wall surface
		{
			// std::cerr << "hit wall" <<std::endl;
			Vector3D v = InterPt.pos - m_pos;
			InterPt.n  = v - v.dot(m_ori) * m_ori;
		}
		else if (min_T == inter_3)
		{
			// std::cerr << "hit low cap" <<std::endl;
			InterPt.n  = -1.0 * m_ori;
		}
		else if (min_T == inter_4)
		{
			// std::cerr << "hit upper cap" <<std::endl;
			InterPt.n  = m_ori;
		}
	}

	return InterPt;
}

Point2D NonhierCylinder::mapUV(Point3D pos)
{
	Point2D uv;
	Vector3D C = m_ori;
	C.normalize();

	if (pos.v_[1] <= m_pos.v_[1] || pos.v_[1] >= (m_pos.v_[1]+m_height) ) // cap
	{
		uv.v_[0] = (m_radius - pos.v_[0])/ (2*m_radius);
		uv.v_[1] = (m_radius - pos.v_[2])/ (2*m_radius);
	}
	else
	{
		Vector3D temp = pos - m_pos;
		uv.v_[1] = temp.dot(C)/m_height;

		double tmp = (pos.v_[0] - m_pos.v_[0])/ m_radius; // [-1,1]
		if(tmp > 1)
			tmp = 1;
		else if (tmp < -1)
			tmp = -1;
		uv.v_[0] = acos(tmp) / (M_PI);
	}
	return uv;
}

/******************************  NonhierCone  *******************************************/
// Ref: http://www.ctralie.com/PrincetonUGRAD/Projects/COS426/Assignment3/part1.html#raycylinder
NonhierCone::~NonhierCone()
{
}

BdBox NonhierCone::findBdBox()
{
	Point3D minP;
	Point3D maxP;

	minP.v_[0] = m_pos.v_[0] - m_radius;
	maxP.v_[0] = m_pos.v_[0] + m_radius;

	minP.v_[1] = m_pos.v_[1];
	maxP.v_[1] = m_pos.v_[1] + m_yend;

	minP.v_[2] = m_pos.v_[2] - m_radius;
	maxP.v_[2] = m_pos.v_[2] + m_radius;

	return BdBox(minP, maxP);
}

InterPoint NonhierCone::intersect(Ray ray, bool drawBx)
{
	InterPoint InterPt;
	std::vector<double> T_set;
	Vector3D cap_n = Vector3D(0,1,0);

	double k  = m_radius/m_height;
	double yk = ray.pos.v_[1] - (m_height + m_pos.v_[1]);

	double x0 = ray.pos.v_[0] - m_pos.v_[0];
	double y0 = ray.pos.v_[1] - m_pos.v_[1];
	double z0 = ray.pos.v_[2] - m_pos.v_[2];

	double A = ray.dir.v_[0] * ray.dir.v_[0] + ray.dir.v_[2] * ray.dir.v_[2] - k*k* ray.dir.v_[1] * ray.dir.v_[1];
	double B = 2*(ray.dir.v_[0] * x0 + ray.dir.v_[2] * z0 - k*k* ray.dir.v_[1] * yk);
	double C = x0 * x0 + z0 * z0 - k*k*yk*yk;

	double Delta = B*B - 4*A*C;
	if (Delta <0)
		return InterPt;

	Delta = sqrt(Delta);
	double inter_1 = (-B - Delta)/(2*A);
	double inter_2 = (-B + Delta)/(2*A);

	Point3D q1 = ray.pos + inter_1*ray.dir;
	Point3D q2 = ray.pos + inter_2*ray.dir;
	Point3D p1 = m_pos;
	Point3D p2 = m_pos + m_yend * cap_n;

	if ((cap_n.dot(q1-p1) > 0.0) && (cap_n.dot(q1-p2) < 0.0))
	{
		T_set.push_back(inter_1);
	}

	if ((cap_n.dot(q2-p1) > 0.0) && (cap_n.dot(q2-p2) < 0.0))
	{
		T_set.push_back(inter_2);
	}

	// check with caps
	Vector3D PsubP_1 = ray.pos - p1;
	Vector3D PsubP_2 = ray.pos - p2;
	double inter_3, inter_4;

	if ((ray.dir).dot(cap_n) != 0)
	{
		inter_3 = -1.0 * cap_n.dot(PsubP_1) / cap_n.dot(ray.dir);
		inter_4 = -1.0 * cap_n.dot(PsubP_2) / cap_n.dot(ray.dir);

		Vector3D q3 = PsubP_1 + inter_3*ray.dir;
		Vector3D q4 = PsubP_2 + inter_4*ray.dir;

		if(inter_3 > 0)
		{
			if (q3.length2() < m_radius*m_radius)
			{
				T_set.push_back(inter_3);
			}
		}

		if(inter_4 > 0)
		{
			double rad = k * (m_height - m_yend);
			if (q4.length2() < rad*rad)
			{
				T_set.push_back(inter_4);
			}
		}
	}
	// find closest intersection
	if (!T_set.empty())
	{
		double min_T = *std::min_element(std::begin(T_set),std::end(T_set));
		InterPt.hit = true;
		InterPt.t = min_T;
		InterPt.pos = ray.pos + ray.dir  * InterPt.t;
		Vector3D P  = InterPt.pos - m_pos;
		//determin norm
		if (min_T == inter_1 || min_T == inter_2)
		{
			Vector3D projected_XZ = Vector3D(P.v_[0], 0, P.v_[2]);
			projected_XZ.normalize();
			Vector3D norm_XZ = P.dot(projected_XZ) * projected_XZ;
			InterPt.n = norm_XZ + k * norm_XZ.length() * Vector3D(0,1,0);
		}
		else if (min_T == inter_3)
		{
			// std::cerr << "hit low cap" <<std::endl;
			InterPt.n  = -1.0 * cap_n;
		}
		else if (min_T == inter_4)
		{
			// std::cerr << "hit upper cap" <<std::endl;
			InterPt.n  = cap_n;
		}
	}
	return InterPt;

}

Point2D NonhierCone::mapUV(Point3D pos)
{
	Point2D uv;
	return uv;
}
/******************************  Plane  *******************************************/
// Ref: http://www.ctralie.com/PrincetonUGRAD/Projects/COS426/Assignment3/part1.html#raycylinder
Plane::~Plane()
{
}

BdBox Plane::findBdBox()
{
	Point3D minP;
	Point3D maxP;

	Point3D p0 = m_pos;
	Point3D p1 = m_pos + m_width * m_v1;
	Point3D p2 = m_pos + m_height * m_v2;
	Point3D p3 = m_pos + m_height * m_v2 + m_width * m_v1;

	std::vector<double> TX_set{p0.v_[0],p1.v_[0],p2.v_[0],p3.v_[0]};
	std::vector<double> TY_set{p0.v_[1],p1.v_[1],p2.v_[1],p3.v_[1]};
	std::vector<double> TZ_set{p0.v_[2],p1.v_[2],p2.v_[2],p3.v_[2]};
	minP.v_[0] = *std::min_element(std::begin(TX_set),std::end(TX_set));
	minP.v_[1] = *std::min_element(std::begin(TY_set),std::end(TY_set));
	minP.v_[2] = *std::min_element(std::begin(TZ_set),std::end(TZ_set));

	maxP.v_[0] = *std::max_element(std::begin(TX_set),std::end(TX_set));
	maxP.v_[1] = *std::max_element(std::begin(TY_set),std::end(TY_set));
	maxP.v_[2] = *std::max_element(std::begin(TZ_set),std::end(TZ_set));

	return BdBox(minP, maxP);
}

InterPoint Plane::intersect(Ray ray, bool drawBx)
{
	InterPoint InterPt;
	Point3D p0 = m_pos;
	Point3D p1 = m_pos + m_width * m_v1;
	Point3D p2 = m_pos + m_height * m_v2;
	Point3D p3 = m_pos + m_height * m_v2 + m_width * m_v1;

	std::vector<double> TX_set{p0.v_[0],p1.v_[0],p2.v_[0],p3.v_[0]};
	std::vector<double> TY_set{p0.v_[1],p1.v_[1],p2.v_[1],p3.v_[1]};
	std::vector<double> TZ_set{p0.v_[2],p1.v_[2],p2.v_[2],p3.v_[2]};
	double min_X = *std::min_element(std::begin(TX_set),std::end(TX_set));
	double min_Y = *std::min_element(std::begin(TY_set),std::end(TY_set));
	double min_Z = *std::min_element(std::begin(TZ_set),std::end(TZ_set));

	double max_X = *std::max_element(std::begin(TX_set),std::end(TX_set));
	double max_Y = *std::max_element(std::begin(TY_set),std::end(TY_set));
	double max_Z = *std::max_element(std::begin(TZ_set),std::end(TZ_set));

	if(m_norm.dot(ray.dir) == 0)
		return InterPt;
	double t = m_norm.dot(m_pos - ray.pos)/ m_norm.dot(ray.dir);// assume m_norm is unit length
	if (t < 0)
		return InterPt;

	// determine if intersection point is within the rectangle
	Point3D Pt = ray.pos + t * ray.dir;
	double a = m_norm.v_[0];
	double b = m_norm.v_[1];
	double c = m_norm.v_[2];
	if (fabs(a)>fabs(b) && fabs(a)>fabs(c))
	{
		if ( (min_Y < Pt.v_[1] && Pt.v_[1] < max_Y) && (min_Z < Pt.v_[2] && Pt.v_[2] < max_Z) )
		{
			InterPt.hit = true;
			InterPt.t = t;
			InterPt.pos = Pt;
			InterPt.n = m_norm;
		}
	}

	else if (fabs(b)>fabs(c) && fabs(b)>fabs(a))
	{
		if ( (min_X < Pt.v_[0] && Pt.v_[0] < max_X) && (min_Z < Pt.v_[2] && Pt.v_[2] < max_Z) )
		{
			InterPt.hit = true;
			InterPt.t = t;
			InterPt.pos = Pt;
			InterPt.n = m_norm;
		}
	}

	else if (fabs(c)>fabs(b) && fabs(c)>fabs(a))
	{
		if ( (min_Y < Pt.v_[1] && Pt.v_[1] < max_Y) && (min_X < Pt.v_[0] && Pt.v_[0] < max_X) )
		{
			InterPt.hit = true;
			InterPt.t = t;
			InterPt.pos = Pt;
			InterPt.n = m_norm;
		}
	}

	return InterPt;
}

Point2D Plane::mapUV(Point3D pos)
{
	Point2D uv;
	Vector3D offset = pos - m_pos;
	uv.v_[0] = offset.dot(m_v1)/m_width;
	uv.v_[1] = offset.dot(m_v2)/m_height;
	return uv;
}
/******************************  NonhierBox  *******************************************/
NonhierBox::~NonhierBox()
{
	delete m_mesh;
}

NonhierBox::NonhierBox(const Point3D& pos, double size)
    : m_pos(pos), m_size(size)
{
	// create mesh
	//	 Mesh(const std::vector<Point3D>& verts,
	//	       const std::vector< std::vector<int> >& faces);

		std::vector<Point3D> verts;
		verts.push_back(Point3D(m_pos[0], 			m_pos[1], m_pos[2]));
		verts.push_back(Point3D(m_pos[0] + m_size, 	m_pos[1], m_pos[2]));
		verts.push_back(Point3D(m_pos[0] + m_size, 	m_pos[1], m_pos[2] + m_size));
		verts.push_back(Point3D(m_pos[0], 			m_pos[1], m_pos[2] + m_size));

		verts.push_back(Point3D(m_pos[0], 			m_pos[1] + m_size, m_pos[2]));
		verts.push_back(Point3D(m_pos[0] + m_size, 	m_pos[1] + m_size, m_pos[2]));
		verts.push_back(Point3D(m_pos[0] + m_size, 	m_pos[1] + m_size, m_pos[2] + m_size));
		verts.push_back(Point3D(m_pos[0], 			m_pos[1] + m_size, m_pos[2] + m_size));

		std::vector<std::vector<int> > faces;
		int faceArray[6][4] =
		{
				{0,1,2,3},
				{7,3,2,6},
				{6,2,1,5},
				{5,1,0,4},
				{4,0,3,7},
				{4,7,6,5}
		};

		for (int f = 0 ;f < 6; f++) {
			std::vector<int> polygon;

			for (int v = 0; v < 4; v++) {
				polygon.push_back(faceArray[f][v]);
			}
			faces.push_back(polygon);
		}
		// create the 8 verticies & the 6 faces
		m_mesh = new Mesh(verts, faces);
}

BdBox NonhierBox::findBdBox()
{
	return m_mesh->findBdBox();
}

InterPoint NonhierBox::intersect(Ray ray, bool drawBx)
{

	/**************************  Bounding box  **********************************/
	InterPoint InterPt;
	BdBox bounding = findBdBox();
	bool BoxSected = bounding.IsSected(ray);
	if (!BoxSected)
	{
		// std::cout << "nhBox BdBox doesn't intersect" << std::endl;
		return InterPt;
	}

	return m_mesh->intersect(ray, false);
}

Point2D NonhierBox::mapUV(Point3D pos)
{
	Point2D uv;
	uv.v_[0] = pos.v_[0]/m_size;
	uv.v_[1] = pos.v_[1]/m_size;
	return uv;
}


/******************************  Cuboid  *******************************************/
Cuboid::~Cuboid()
{
	delete m_mesh;
}

Cuboid::Cuboid(const Point3D& pos, double width, double height, double depth)
: m_pos(pos), m_width(width), m_height(height), m_depth(depth)
{
	std::vector<Point3D> verts;
	verts.push_back(Point3D(m_pos[0],			m_pos[1], m_pos[2]));					//0
	verts.push_back(Point3D(m_pos[0] + m_width, m_pos[1], m_pos[2]));					//1
	verts.push_back(Point3D(m_pos[0] + m_width, m_pos[1], m_pos[2] + m_depth));			//2
	verts.push_back(Point3D(m_pos[0], 			m_pos[1], m_pos[2] + m_depth));			//3

	verts.push_back(Point3D(m_pos[0], 			m_pos[1] + m_height, m_pos[2]));
	verts.push_back(Point3D(m_pos[0] + m_width, m_pos[1] + m_height, m_pos[2]));
	verts.push_back(Point3D(m_pos[0] + m_width, m_pos[1] + m_height, m_pos[2] + m_depth));
	verts.push_back(Point3D(m_pos[0], 			m_pos[1] + m_height, m_pos[2] + m_depth));

	std::vector<std::vector<int> > faces;
	int faceArray[6][4] =
	{
		{0,1,2,3},
		{7,3,2,6},
		{6,2,1,5},
		{5,1,0,4},
		{4,0,3,7},
		{4,7,6,5}
	};

	for (int f = 0 ;f < 6; f++) {
		std::vector<int> polygon;

		for (int v = 0; v < 4; v++) {
			polygon.push_back(faceArray[f][v]);
		}
		faces.push_back(polygon);
	}
	// create the 8 verticies & the 6 faces
	m_mesh = new Mesh(verts, faces);
}

BdBox Cuboid::findBdBox()
{
	return m_mesh->findBdBox();
}

InterPoint Cuboid::intersect(Ray ray, bool drawBx)
{

	/**************************  Bounding box  **********************************/
	InterPoint InterPt;
	BdBox bounding = findBdBox();
	bool BoxSected = bounding.IsSected(ray);
	if (!BoxSected)
	{
		// std::cout << "nhBox BdBox doesn't intersect" << std::endl;
		return InterPt;
	}

	return m_mesh->intersect(ray, false);
}

Point2D Cuboid::mapUV(Point3D pos)
{
	Point2D uv;
	double x = pos.v_[0];
	double y = pos.v_[1];
	double z = pos.v_[2];

	double m_x = m_pos.v_[0];
	double m_y = m_pos.v_[1];
	double m_z = m_pos.v_[2];

	// left and right sides
	if ((x == m_x) || (x == m_x + m_width))
	// if (fabs(x - m_x) < EPSILON || fabs(m_x + m_width - x) < EPSILON)
	{
		uv.v_[0] = z/m_depth;
		uv.v_[1] = y/m_height;
		return uv;
	}

	// front and back sides
	if ((z == m_z) || (z == m_z + m_depth))
	// if (fabs(z - m_z) < EPSILON || fabs(m_z + m_depth - z) < EPSILON)
		{
			uv.v_[0] = x/m_width;
			uv.v_[1] = y/m_height;
			return uv;
		}
	// upper and lower sides
	if ((y == m_y) || (y == m_y + m_height))
	if (fabs(y - m_y) < EPSILON || fabs(m_y + m_height - y) < EPSILON)
	{
		uv.v_[0] = x/m_width;
		uv.v_[1] = z/m_depth;
		return uv;
	}

	// // front intersect
	// if (0<=x && x<=m_width && 0<=y && y<=m_height)
	// {
	// 	uv.v_[0] = x/m_width;
	// 	uv.v_[1] = y/m_height;
	// }
	// // side intersect
	// else if (0<=z && z<=m_depth && 0<=y && y<=m_height)
	// {
	// 	uv.v_[0] = z/m_depth;
	// 	uv.v_[1] = y/m_height;
	// }
	// // up intersect
	// else
	// {
	// 	uv.v_[0] = x/m_width;
	// 	uv.v_[1] = z/m_depth;
	// }
	uv.v_[0] = x/m_width;
	uv.v_[1] = y/m_height;
	return uv;
}



InterPoint BBoxIntersect(BdBox bounding, Ray ray)
{
	InterPoint InterPt;
	std::vector<Point3D> verts;
	verts.push_back(Point3D(bounding.m_minP[0], bounding.m_minP[1], bounding.m_minP[2]));
	verts.push_back(Point3D(bounding.m_maxP[0], bounding.m_minP[1], bounding.m_minP[2]));
	verts.push_back(Point3D(bounding.m_maxP[0], bounding.m_minP[1], bounding.m_maxP[2]));
	verts.push_back(Point3D(bounding.m_minP[0], bounding.m_minP[1], bounding.m_maxP[2]));

	verts.push_back(Point3D(bounding.m_minP[0], bounding.m_maxP[1], bounding.m_minP[2]));
	verts.push_back(Point3D(bounding.m_maxP[0], bounding.m_maxP[1], bounding.m_minP[2]));
	verts.push_back(Point3D(bounding.m_maxP[0], bounding.m_maxP[1], bounding.m_maxP[2]));
	verts.push_back(Point3D(bounding.m_minP[0], bounding.m_maxP[1], bounding.m_maxP[2]));

	std::vector<std::vector<int> > faces;
	int faceArray[6][4] =
	{
		{0,1,2,3},
		{7,3,2,6},
		{6,2,1,5},
		{5,1,0,4},
		{4,0,3,7},
		{4,7,6,5}
	};

	for (int f = 0 ;f < 6; f++) {
		std::vector<int> polygon;

		for (int v = 0; v < 4; v++) {
			polygon.push_back(faceArray[f][v]);
		}
		faces.push_back(polygon);
	}
	// create the 8 verticies & the 6 faces
	Mesh* m_mesh = new Mesh(verts, faces);
	InterPt = m_mesh->intersect(ray, false);

	return InterPt;
}
