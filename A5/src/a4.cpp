#include "a4.hpp"
#include <algorithm>
#include <math.h>

const bool drawBx = false;
const bool AntiAlias = false;
const bool drawAntiAlias = false;

const std::string bg = "../data/simple_background.png";
Image bg_img;
int IMG_width, IMG_height;
double c_thresh = 0.03;

void a4_render(
// What to render
		SceneNode* root,
		// Where to output the image
		const std::string& filename,
		// Image size
		const int width, const int height,
		// Viewing parameters
		const Point3D& eye, const Vector3D& view, const Vector3D& up, double fov,
		// Lighting parameters
		const Colour& ambient, const std::list<Light*>& lights)
{
	std::cerr << "Stub: a4_render(" << root << ",\n     "
	<< filename << ", " << width << ", " << height << ",\n     "
	<< eye << ", " << view << ", " << up << ", " << fov << ",\n     "
	<< ambient << ",\n     {";

	for (std::list<Light*>::const_iterator I = lights.begin(); I != lights.end(); ++I)
		{
			if (I != lights.begin())
				std::cerr << ", ";

				std::cerr << **I;
			}
			std::cerr << "});" << std::endl;

	std::cerr << "reflection depth: " << MAXLEVEL <<std::endl;
	std::cerr << "draw bounding box? " << drawBx <<std::endl;

	// std::cout << acos(0) << " " << acos(-1) << " " << acos(1) << std::endl;

	// set up coordinates
	Vector3D camera_dir = view;
	Vector3D camera_up = up;
	Vector3D camera_right = view.cross(up);

	camera_right.normalize();
	camera_up.normalize();
	camera_dir.normalize();

	// set up img plane
	// assume virtual screen is one unit away in camera direction
	double pixelHeight = 2.0*tan(fov* M_PI/ 360.0);
	pixelHeight = pixelHeight / double(height);

	double pixelWidth  = 2.0*tan(fov* M_PI/ 360.0);
	pixelWidth = pixelWidth / double(width);

	ImgPlane plane(width, height, pixelHeight, pixelWidth);
	Env root_scene = Env(root, eye, camera_dir, camera_right, camera_up, fov,
						 ambient, lights, plane);

	// set up background
	if (!bg_img.loadPng(bg))
		{
			std::cerr << "Failed to load background " << bg << std::endl;
			exit(-1);
		}
	IMG_width = width;
	IMG_height = height;

	// first let all nodes find its BdBox
	BdBox rootBB = root->walk_gl();


	Vector3D scanlineStart;
	Image img(width, height, 3);
	// threads
	int start_line, line_num;
    std::vector<std::thread*> threads;

    for(int i = 0; i < NUM_THREAD; ++i){
        start_line = i * height/NUM_THREAD;
    	if (i == NUM_THREAD - 1)
    		line_num = height - start_line;
    	else
    		line_num = height/NUM_THREAD;


    	threads.push_back(new std::thread(Trace_ray,start_line, line_num, std::ref(root_scene), std::ref(img)));
    	// Trace_ray(start_line, line_num, root_scene, img);
    }

    clock_t t = clock();
    for (size_t i = 0; i < threads.size(); ++i)
    {
        threads[i]->join();
        delete threads[i];
    }
  	t = clock() - t;
    std::cerr << "Takes " << ((float)t)/CLOCKS_PER_SEC << " seconds to complete" << std::endl;


	if (AntiAlias)
	{
		bool** reCast = new bool*[width];
		double avrg_d = 0;
		for(int i = 0; i < width; ++i)
			reCast[i] = new bool[height];

		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				reCast[x][y] = false;
			}
		}

		for (int y = 1; y < height -1; y++)
		{
			for (int x = 1; x < width-1; x++)
			{
				Colour lb = img(x-1,y+1);
				Colour rb = img(x+1,y+1);
				Colour lu = img(x-1,y-1);
				Colour ru = img(x+1,y-1);

				Colour l = img(x-1,y);
				Colour r = img(x+1,y);
				Colour u = img(x,y-1);
				Colour d = img(x,y+1);

				Colour cd1 = lb - img(x, y);
				Colour cd2 = rb - img(x, y);
				Colour cd3 = lu - img(x, y);
				Colour cd4 = ru - img(x, y);

				Colour cd5 = l  - img(x, y);
				Colour cd6 = r  - img(x, y);
				Colour cd7 = u  - img(x, y);
				Colour cd8 = d  - img(x, y);

				double d1 = sqrt(cd1.R()*cd1.R() + cd1.G()*cd1.G() + cd1.B()*cd1.B());
				double d2 = sqrt(cd2.R()*cd2.R() + cd2.G()*cd2.G() + cd2.B()*cd2.B());
				double d3 = sqrt(cd3.R()*cd3.R() + cd3.G()*cd3.G() + cd3.B()*cd3.B());
				double d4 = sqrt(cd4.R()*cd4.R() + cd4.G()*cd4.G() + cd4.B()*cd4.B());

				double d5 = sqrt(cd5.R()*cd5.R() + cd5.G()*cd5.G() + cd5.B()*cd5.B());
				double d6 = sqrt(cd6.R()*cd6.R() + cd6.G()*cd6.G() + cd6.B()*cd6.B());
				double d7 = sqrt(cd7.R()*cd7.R() + cd7.G()*cd7.G() + cd7.B()*cd7.B());
				double d8 = sqrt(cd8.R()*cd8.R() + cd8.G()*cd8.G() + cd8.B()*cd8.B());

				double min_d =d1;
				if (d2 < min_d)
					min_d = d2;
				if (d3 < min_d)
					min_d = d3;
				if (d4 < min_d)
					min_d = d4;
				if (d5 < min_d)
					min_d = d5;
				if (d6 < min_d)
					min_d = d6;
				if (d7 < min_d)
					min_d = d7;
				if (d8 < min_d)
					min_d = d8;

				if (min_d > 1e-6)
					std::cout << min_d << std::endl;
				//avrg_d += max_d;
				if (min_d > c_thresh)
					{
						reCast[x][y] = true;
					}
			}
		}
		//std::cout << " avrg_d : "<< avrg_d / ((height -2) * (width -2))<< std::endl;

		
		for (int y = 1; y < height-1; y++)
		{
			for (int x = 1; x < width-1; x++)
			{
				if (reCast[x][y] == true)
				{
					if (drawAntiAlias)
					{
						img(x, y, 0) = 1;
						img(x, y, 1) = 0;
						img(x, y, 2) = 0;
					}
					else
					{
						Trace_ray_aa(x, y, root_scene, img);
					}
				}
			}
		}
		
	}

	img.savePng(filename);
}

/************************************ Trace_ray  *****************************************/
void Trace_ray(int start_line, int line_num, const Env& root_scene, Image& img)
{
	int width =  root_scene.plane.width;
	int height = root_scene.plane.height;
	double aspect_ratio = double(height)/double(width);

	Ray ray;
	Vector3D scanlineStart;
	int level = 0;
	for (int y = start_line; y < start_line + line_num; y++)
	{

		scanlineStart = (- double(width)/2 + 0.5)*root_scene.plane.pixelWidth * aspect_ratio * root_scene.right
						+ (y - double(height)/2 + 0.5 )* root_scene.plane.pixelHeight * -root_scene.up;

		for (int x = 0; x < width; x++)
		{
			ray.pos = root_scene.eye;
			ray.dir = root_scene.dir + scanlineStart + x * root_scene.plane.pixelWidth * aspect_ratio * root_scene.right;
			ray.dir.normalize();
			level = 0;
			Colour sectColor = castRay(root_scene.root, ray, root_scene.ambient,
										root_scene.lights, level, x, y);

			img(x, y, 0) += sectColor.R();
 			img(x, y, 1) += sectColor.G();
 			img(x, y, 2) += sectColor.B();
		}
	}
}

/************************************ Trace_ray aa  *****************************************/

void Trace_ray_aa(int x_ori, int y_ori, const Env& root_scene, Image& img)
{
	int width =  root_scene.plane.width;
	int height = root_scene.plane.height;
	double aspect_ratio = double(height)/double(width);

	Ray ray;
	Colour aaColor = Colour(0,0,0);
	Vector3D scanlineStart;
	int level = 0;
	for (double y = y_ori-0.5; y <= y_ori+0.5 ; y=+1)
	{
		scanlineStart = (- double(width)/2 + 0.5)*root_scene.plane.pixelWidth * aspect_ratio * root_scene.right
					+ (y - double(height)/2 + 0.5 )* root_scene.plane.pixelHeight * -root_scene.up;
		for (double x = x_ori - 0.5; x <= x_ori+0.5; x=+1)
		{
			ray.pos = root_scene.eye;
			ray.dir = root_scene.dir + scanlineStart + x * root_scene.plane.pixelWidth * aspect_ratio * root_scene.right;
			ray.dir.normalize();
			level = 0;
			if (x != x_ori && y != y_ori)
				aaColor = aaColor + castRay(root_scene.root, ray, root_scene.ambient,
										root_scene.lights, level, x, y);
		}
	}

	img(x_ori, y_ori, 0) += aaColor.R();
	img(x_ori, y_ori, 1) += aaColor.G();
	img(x_ori, y_ori, 2) += aaColor.B();
	
	img(x_ori, y_ori, 0) = img(x_ori, y_ori, 0) / 5;
	img(x_ori, y_ori, 1) = img(x_ori, y_ori, 1) / 5;
	img(x_ori, y_ori, 2) = img(x_ori, y_ori, 2) / 5;
		
	
}

/************************************ castRay  *****************************************/
Colour castRay(SceneNode* root, Ray r, const Colour& ambient,
				const std::list<Light*>& lights, int level, int x, int y)
{
	Colour sectColor = Colour(0,0,0);
	Ray ray = r;

	if (level >= MAXLEVEL)
		return Colour(0,0,0);

	// std::cerr << "gonna calc  closest_interpt" << std::endl;
	InterPoint closest_interpt = root->intersect(ray, drawBx, 1);
	// std::cerr << "main closest_interpt " << closest_interpt.hit << std::endl;

	if(!closest_interpt.hit)
	/************************* background color ************************/
	{
	// 	if (level == 0)
	// 		sectColor = background(x,y);
		return sectColor;
	}

	return performLighting(root, ray, closest_interpt, ambient, lights, level, x, y); // ray is used by specular colour

}


/****************************  performLighting  **********************************/
Colour performLighting(SceneNode* root, Ray r, const InterPoint& closest_interpt,
						const Colour& ambient, const std::list<Light*>& lights, int level, int x, int y)
{
	Material* mat = closest_interpt.obj->get_material();
	if (mat == NULL)
	{
		mat = new PhongMaterial(Colour(0.5,0.5,0.5), Colour(0,0,0), 10, 0, 0);
	}

	Colour ambientColor = Colour(0,0,0);
	if (mat->is3D() == false)
	{
		// if (level == 0)
		ambientColor = mat->getKd() * ambient + mat->getColour(closest_interpt.uv);
	}
	else
	{
		ambientColor = mat->getKd() * ambient + mat->getColour(closest_interpt.obj->get_inverse() * closest_interpt.pos);
	}
	Colour diffuseAndSpecularColor = getDiffuseAndSpecularLighting(root, r, closest_interpt, lights);
	Colour reflectedColor = getReflectiveRefractiveLighting(root, r, closest_interpt, ambient, lights, level, x, y);

	return (ambientColor + diffuseAndSpecularColor + reflectedColor);
}

/****************************  getReflectiveRefractiveLighting  **********************************/
//	Ref: https://github.com/marczych/RayTracer
Colour getReflectiveRefractiveLighting(SceneNode* root, Ray ray, const InterPoint& intersection,
										const Colour& ambient, const std::list<Light*>& lights, int level, int x, int y)
{
	if (level >= MAXLEVEL)
		return Colour(0,0,0);

	Material* mat = intersection.obj->get_material();
	if (mat == NULL)
	{
		mat = new PhongMaterial(Colour(0.5,0.5,0.5), Colour(0,0,0), 10, 0, 0);
	}

	// Default to exclusively reflective values.
	double reflectPercent = mat->getReflect();
	double refractPercent = mat->getRefract();

	// No refract/reflect properties
	if (reflectPercent <= 0 && refractPercent <= 0) {
		return Colour(0,0,0);
	}

	Colour reflectColor = Colour(0,0,0);
	Colour refractColor = Colour(0,0,0);

	bool internal = isInternalRefl(ray, intersection, mat->getRefract());
	if (internal)
	{
		refractPercent = 0;
		if (intersection.obj->name() == "s1")
			std::cout << "s1 total InternalRefl" << std::endl;
	}

	if (reflectPercent > 0)
	{
		Ray reflectedRay = Reflect(ray, intersection);
		reflectColor = castRay(root, reflectedRay, ambient, lights, level+1, x, y) * reflectPercent;
	}

	if (refractPercent > 0)
	{
		Ray refractedRay = Refract(ray, intersection, mat->getRefract());
		// if (intersection.obj->name() == "s1")
		// 	std::cout << "s1 refraction start" << std::endl;
		refractColor = castRay(root, refractedRay, ambient, lights, MAXLEVEL-1, x, y) * 0.8;
	}

	return reflectColor + refractColor;

}

/****************************  Reflect  **********************************/
Ray Reflect(Ray ray, InterPoint closest_interpt)
{
	Ray ray_reflect;
	Vector3D interNorm = closest_interpt.n;
	double cos_ray_N = -1.0 * interNorm.dot(ray.dir) / interNorm.length();
	Vector3D R_ = ray.dir + 2*cos_ray_N/ interNorm.length() * interNorm ;
	ray_reflect.pos = closest_interpt.pos;
	ray_reflect.dir = R_;
	return ray_reflect;
}


/****************************  Refract  **********************************/
Ray Refract(Ray ray, InterPoint closest_interpt, double m_refract_ratio)
{
	Ray ray_refract;
	Vector3D incident = ray.dir;
	incident.normalize();
	Vector3D normal = closest_interpt.n;
	normal.normalize();

	ray_refract.pos = closest_interpt.pos;
	double cosI = normal.dot(incident);

	double itaI;
	double itaT;

	if (cosI < 0) 		// ray is outside refractive mat
	{
		// std::cout << closest_interpt.obj->name() << " intersect ray is outside refractive mat" << std::endl;
		//cosI  = -1.0 * cosI;

		itaI = 1.0;
		itaT = m_refract_ratio;
	}
	else			   // ray is inside refractive mat
	{
		// std::cout << closest_interpt.obj->name() << " intersect ray is inside refractive mat" << std::endl;

		itaT = 1.0;
		itaI = m_refract_ratio;
		normal = -1.0 * normal;
		// std::cout << "ray inside" << std::endl;
	}

	double nRatio = itaI/itaT;
	double sinT_2 = (nRatio*nRatio)*(1- cosI * cosI);
	if (sinT_2 > 1.0) {
		std::cerr << "Bad refraction vector!" << std::endl;
		exit(EXIT_FAILURE);
	}

	double cosT = sqrt(1.0 - sinT_2);
	// ray_refract.dir = nRatio * incident + (nRatio * cosI + cosT) * normal;
	ray_refract.dir = nRatio * incident - nRatio * normal.dot(incident) * normal - cosT * normal;

	return ray_refract;
}

/****************************  isInternalRefl  **********************************/
bool isInternalRefl(Ray ray, InterPoint closest_interpt, double m_refract_ratio)
{
	Vector3D incident = ray.dir;
	incident.normalize();
	Vector3D normal = closest_interpt.n;
	normal.normalize();

	double cosI = normal.dot(incident);

	double itaI;
	double itaT;

	if (cosI < 0) 		// ray is outside refractive mat
		{
			itaI = 1.0;
			itaT = m_refract_ratio;
		}
		else			   // ray is inside refractive mat
		{
			itaT = 1.0;
			itaI = m_refract_ratio;
		}

		double nRatio = itaI/itaT;
		if (nRatio < 1)
			return false;

		double sinT_2 = (nRatio*nRatio)*(1- cosI * cosI);
		if (sinT_2 > 1.0)
			return true;
		else
			return false;
}

/****************************  getReflectance  **********************************/
//  Fresnel reflection
double getReflectance(Ray ray, const InterPoint& intersection, double m_refract_ratio)
{
	Vector3D incident = ray.dir;
	Vector3D normal = intersection.n;
	incident.normalize();
	normal.normalize();
	double cosI = normal.dot(incident);

	double itaI;
	double itaT;


	if (cosI < 0) 		// ray is outside refractive mat
	{
		itaI = 1.0;
		itaT = m_refract_ratio;
	}
	else			   // ray is inside refractive mat
	{
		itaT = 1.0;
		itaI = m_refract_ratio;
	}

	double nRatio = itaI/itaT;
	double sinT_2 = (nRatio*nRatio)*(1- cosI * cosI);
	if (sinT_2 > 1.0) {
		// Total Internal Reflection.
		std::cout <<"node: "<< intersection.obj->name() << " internal reflection" << std::endl;
		return 1.0;

	}

	cosI = fabs(cosI);
	double cosT = sqrt(1.0 - sinT_2);
	double r_0rth = (itaI * cosI - itaT * cosT) / (itaI * cosI + itaT * cosT);
	double r_Par =  (itaI * cosT - itaT * cosI) / (itaI * cosT + itaT * cosI);
	return (r_0rth * r_0rth + r_Par * r_Par) / 2.0;

}
/****************************  getDiffuseAndSpecularLighting  **********************************/
Colour getDiffuseAndSpecularLighting(SceneNode* root, Ray ray, const InterPoint& interpt,
									const std::list<Light*>& lights)
{
	Colour Diff = Colour(0,0,0);
	Colour Spec = Colour(0,0,0);

	Material* mat = interpt.obj->get_material();

	if (mat == NULL)
	{
		mat = new PhongMaterial(Colour(0.5,0.5,0.5), Colour(0,0,0), 10, 0, 0);
	}


	for (lightList::const_iterator it = lights.begin(), end = lights.end(); it != end; it++)
	{
		Light* light = *it;
		if (!light->isArea()) // non AreaLight shading
		{
			// std::cout << "AreaLight" << std::endl;
			Vector3D L = light->position - interpt.pos;
			double Ldist = L.length();
			if (Ldist > LDIST_MAX)
				Ldist = LDIST_MAX;
			else if (Ldist < LDIST_MIN)
				Ldist = LDIST_MIN;

			// if (light->LightFactor(L) != 1.0 && light->LightFactor(L) != 0.0)
			// 	std::cout << light->LightFactor(L) << std::endl;

			double attenua = light->falloff[0] +  light->falloff[1] * Ldist + light->falloff[2] * Ldist*Ldist;

			double cos_L = L.dot(interpt.n)/(L.length() * interpt.n.length()); // cosine of light and norm
			if (cos_L > 0.0)
			//Intersection is facing light
			{
				if (Shadowed(interpt, root, light->position)){		//Position is in shadow of another object - continue with other lights.

					// std::cerr << " in shadow of another object " << std::endl;
					continue;
				}

				// calculate the diffuse
				Diff = Diff + light->LightFactor(L) * 1.0/attenua * cos_L * mat->getKd() * light->colour;

				// calculate the speculate
				Vector3D R = -1.0 / L.length() * L + 2 * cos_L * 1.0 / interpt.n.length() * interpt.n;
				double cos_R = -1.0 * R.dot(ray.dir) / ray.dir.length();  // -1.0 Because ray.dir is opposite as that in course note:
				// it is eye -> intersection point
				if (cos_R > 0)
				{
					Spec = Spec + light->LightFactor(L) * 1.0/attenua * pow(cos_R, mat->getShininess()) * mat->getKs() * light->colour;
				}
			}
		} // end non AreaLight
		else
		{
			Point3D randLightPos;
			AreaLight* area = dynamic_cast<AreaLight*>(light);
			Colour Area_Diff = Colour(0,0,0);
			Colour Area_Spec = Colour(0,0,0);

			double r1,r2;
			for (int i = 0; i< SAMPLE_N; i++)
			{
				r1 = (rand()/(double)(RAND_MAX));
				r2 = (rand()/(double)(RAND_MAX));
				//std::cout << "r1 "<< r1 << "  r2 "<< r2 << std::endl;

				randLightPos = area->position + (0.5 - r1) * area->m_width * area->m_v1 + (0.5 - r2) * area->m_height * area->m_v2;
				// std::cout << "randLightPos " << randLightPos.v_[0]<< " " << randLightPos.v_[1] << " "
						//   << randLightPos.v_[2]<< " " << std::endl;

				Vector3D L = randLightPos - interpt.pos;
				double Ldist = L.length();
				if (Ldist > LDIST_MAX)
					Ldist = LDIST_MAX;
					else if (Ldist < LDIST_MIN)
					Ldist = LDIST_MIN;

				// if (light->LightFactor(L) != 1.0 && light->LightFactor(L) != 0.0)
				// 	std::cout << light->LightFactor(L) << std::endl;

				double attenua = area->falloff[0] +  area->falloff[1] * Ldist + area->falloff[2] * Ldist*Ldist;

				double cos_L = L.dot(interpt.n)/(L.length() * interpt.n.length()); // cosine of light and norm
				if (cos_L > 0.0)
				//Intersection is facing light
				{
					if (Shadowed(interpt, root, randLightPos)) //Position is in shadow of another object - continue with other lights.
					{
						// std::cerr << " in shadow of another object " << std::endl;
						continue;
					}

					// calculate the diffuse
					Area_Diff = Area_Diff + area->LightFactor(L) * 1.0/attenua * cos_L * mat->getKd() * area->colour;
					// std::cout << i << " " << Area_Diff.R() << std::endl;
					// calculate the speculate
					Vector3D R = -1.0 / L.length() * L + 2 * cos_L * 1.0 / interpt.n.length() * interpt.n;
					double cos_R = -1.0 * R.dot(ray.dir) / ray.dir.length();  // -1.0 Because ray.dir is opposite as that in course note:
					// it is eye -> intersection point
					if (cos_R > 0)
					{
						Area_Spec = Area_Spec + area->LightFactor(L) * 1.0/attenua * pow(cos_R, mat->getShininess()) * mat->getKs() * area->colour;
					}
				}
			} // end sampling

			Diff = Diff + 1.0/SAMPLE_N * Area_Diff;
			Spec = Spec + 1.0/SAMPLE_N * Area_Spec;
		}
	}
	// std::cerr << "getDiffuseAndSpecularLighting done " << std::endl;
	return (Diff + Spec);
}

/****************************  Shadowed  **********************************/
bool Shadowed(const InterPoint& closest_interpt, SceneNode* node, const Point3D& light_pos)
{
	Vector3D l_dir = light_pos - closest_interpt.pos;
	l_dir.normalize();
	Ray l_ray = {closest_interpt.pos, l_dir};

	const double dist_LnInterpt = (closest_interpt.pos - light_pos).length();

	// InterPoint light_interpt = node->intersect(l_ray,false);
	InterPoint light_interpt = node->Sh_intersect(l_ray, closest_interpt.obj->name(), drawBx);
	// decide if light_interpt is between light source and intersection point
	if (light_interpt.hit)
	{
		if ( (light_interpt.pos - closest_interpt.pos).length()/dist_LnInterpt < 1 )
			// && light_interpt.nd_name != closest_interpt.nd_name)
			// if ((light_interpt.pos - closest_interpt.pos).length() < dist_LnInterpt - 0.001)
			// if ( (light_interpt.pos - closest_interpt.pos).length()/dist_LnInterpt < 1 )
			return true;

		else
			return false;
		}
	else
	{
		return false;
	}
}

Colour background(int x, int y)
{
	const int width = bg_img.width();
	const int height = bg_img.height();

	// map [0,width/height] to [0,1]
	Point2D uv;
	uv.v_[0] = double(x) /IMG_width;
	uv.v_[1] = double(y) /IMG_height;
	int umin = int(width  * uv.v_[0]);
	int umax = int(width  * uv.v_[0]) + 1;
	int vmin = int(height * uv.v_[1]);
	int vmax = int(height * uv.v_[1]) + 1;

	umin = std::min(std::max(umin, 0), width -1 );
	umax = std::min(std::max(umax, 0), width -1 );
	vmin = std::min(std::max(vmin, 0), height-1);
	vmax = std::min(std::max(vmax, 0), height - 1);

	// 4 samples on square
	Colour p0 = bg_img(umin, vmin);
	Colour p1 = bg_img(umin, vmax);
	Colour p2 = bg_img(umax, vmin);
	Colour p3 = bg_img(umax, vmax);

	double uD = width * uv.v_[0] - umin;
	double vD = height* uv.v_[1] - vmin;

	//4 point interpolation
	Colour finalColour = vD * (uD * p0 + (1.0 - uD) * p1) +	// top points
	(1.0 - vD) * (uD * p2 + (1.0 - uD) * p3);//bottom points

	return finalColour;
}
