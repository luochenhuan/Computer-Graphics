#include "primitive.hpp"
#include <vector>

#include "mesh.hpp"
Primitive::~Primitive()
{
}

/**** Ref: http://www.siggraph.org/education/materials/HyperGraph/raytrace/rtinter3.htm *****/
bool BdBox::IsSected(Ray ray)
{
	Ray tempRay = ray;
	// tempRay.dir.normalize();

	double Tnear = -1.0 * FAR;
	double Tfar  = 1.0 * FAR;

	double Tx_1  ;
	double Tx_2  ;
	double Tx_min;
	double Tx_max;

	double Ty_1  ;
	double Ty_2  ;
	double Ty_min;
	double Ty_max;

	double Tz_1  ;
	double Tz_2  ;
	double Tz_min;
	double Tz_max;
	
	// X slabs (perpendicular to X axis)
	if ((tempRay.dir).dot(Vector3D(1.0, 0, 0)) == 0)		// notice!!!!
		//  parallel to x slabs
	{
		if (tempRay.pos[0] < m_minP[0] || tempRay.pos[0] > m_maxP[0])
		{
			// std::cout << "parallel to x slabs" << std::endl;
			return false;
		}
	}
	else
	{
		Tx_1   = (m_minP[0] - tempRay.pos[0]) / tempRay.dir[0];
		Tx_2   = (m_maxP[0] - tempRay.pos[0]) / tempRay.dir[0];
		Tx_min = (Tx_1 < Tx_2) ? Tx_1: Tx_2;
		Tx_max = (Tx_1 < Tx_2) ? Tx_2: Tx_1;
		if (Tx_max < 0)
			return false;
	}

	// Y slabs
	if ((tempRay.dir).dot(Vector3D(0, 1.0, 0)) == 0)		
		//  parallel to Y slabs
	{
		if (tempRay.pos[1] < m_minP[1] || tempRay.pos[1] > m_maxP[1])
		{
			// std::cout << "parallel to y slabs" << std::endl;
			return false;
		}
	}
	else
	{
		Ty_1   = (m_minP[1] - tempRay.pos[1]) / tempRay.dir[1];
		Ty_2   = (m_maxP[1] - tempRay.pos[1]) / tempRay.dir[1];
		Ty_min = (Ty_1 < Ty_2) ? Ty_1: Ty_2;
		Ty_max = (Ty_1 < Ty_2) ? Ty_2: Ty_1;
		if (Ty_max < 0)
			return false;
	}

	// Z slabs
	if ((tempRay.dir).dot(Vector3D( 0, 0, 1.0)) == 0)		
		//  parallel to z slabs
	{
		if (tempRay.pos[2] < m_minP[2] || tempRay.pos[2] > m_maxP[2])
		{
			// std::cout << "parallel to z slabs" << std::endl;
			return false;
		}
	}
	else
	{
		Tz_1   = (m_minP[2] - tempRay.pos[2]) / tempRay.dir[2];
		Tz_2   = (m_maxP[2] - tempRay.pos[2]) / tempRay.dir[2];
		Tz_min = (Tz_1 < Tz_2) ? Tz_1: Tz_2;
		Tz_max = (Tz_1 < Tz_2) ? Tz_2: Tz_1;
		if (Tz_max < 0)
			return false;
	}

	Tnear = Tnear < Tx_min? Tx_min : Tnear;
	Tnear = Tnear < Ty_min? Ty_min : Tnear;
	Tnear = Tnear < Tz_min? Tz_min : Tnear;

	Tfar = Tfar > Tx_max? Tx_max : Tfar;
	Tfar = Tfar > Ty_max? Ty_max : Tfar;
	Tfar = Tfar > Tz_max? Tz_max : Tfar;

	if (Tfar < Tnear)
		return false;

	return true;

}
Sphere::Sphere()
{
	m_sphere = new NonhierSphere(Point3D(0.0, 0.0, 0.0), 1.0);
}

Sphere::~Sphere()
{
	delete m_sphere;
}

BdBox Sphere::findBdBox()
{
	return m_sphere->findBdBox();
}

InterPoint Sphere::intersect(Ray ray, bool drawBx) {
	return m_sphere->intersect(ray, drawBx);
}

Cube::Cube()
{
	m_cube = new NonhierBox(Point3D(0,0,0), 1.0);
}

Cube::~Cube()
{
	delete m_cube;
}

BdBox Cube::findBdBox()
{
	return m_cube->findBdBox();
}

InterPoint Cube::intersect(Ray ray, bool drawBx) {
	return m_cube->intersect(ray,drawBx);
}

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
	/******************************  Bounding box  *******************************************/
	BdBox bounding = findBdBox();
	bool Boxsected = bounding.IsSected(ray);
	if (!Boxsected)
	{
		// std::cout << "nhSphere BdBox doesn't intersect" << std::endl;
		return InterPt;
	}

	// std::cout << "BdBox intersect" << std::endl;
	Vector3D sub = ray.pos - m_pos;
	double A = (ray.dir).length2();
	double B = (ray.dir).dot(sub);
	double C = sub.dot(sub) - m_radius * m_radius;
	double Delta = B*B - A*C;
	if (Delta >= 0)
	{
		Delta = sqrt(Delta);
		double inter_1 = (-B - Delta)/A;
		double inter_2 = (-B + Delta)/A;

		if (inter_1 > EPSILON && inter_2 > EPSILON)
			InterPt.t = inter_1;

		else if (inter_2 > EPSILON)
			InterPt.t = inter_2;

	}

	if (InterPt.t > 0) {
		InterPt.hit = true;
		InterPt.pos = ray.pos + ray.dir * InterPt.t;
		InterPt.n = InterPt.pos - m_pos;
		// InterPt.n.normalize();
	}
	return InterPt;
}


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
	
	/******************************  Bounding box  *******************************************/
	InterPoint InterPt;
	BdBox bounding = findBdBox();
	bool Boxsected = bounding.IsSected(ray);
	if (!Boxsected)
	{
		// std::cout << "nhBox BdBox doesn't intersect" << std::endl;
		return InterPt;
	}

	return m_mesh->intersect(ray, false);
}

