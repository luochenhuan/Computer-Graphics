#include "a4.hpp"

#include <algorithm>

#include "image.hpp"
#include "primitive.hpp"
#include "material.hpp"
#include <math.h>
bool drawBx = true;

void a4_render(
// What to render
		SceneNode* root,
		// Where to output the image
		const std::string& filename,
		// Image size
		int width, int height,
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
	std::cerr << "bounding box: " << drawBx <<std::endl;

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
	
	double aspect_ratio = double(height)/double(width);

	Ray ray;
	Vector3D scanlineStart;

	Image img(width, height, 3);
	int percentage = 0 ;

	int portion = ceil(height / 10);

	for (int y = 0; y < height; y++)
	{
		if (y % portion == 0 && percentage != 100)
		{
			std::cout<< "-------" << percentage << "\% done" << std::endl;
			percentage+= 10;
		}

		scanlineStart = (- double(width)/2 + 0.5)*pixelWidth * aspect_ratio * camera_right + (y - double(height)/2 + 0.5 )* pixelHeight * -camera_up;
		for (int x = 0; x < width; x++)
		{
			ray.pos = eye;
			ray.dir = camera_dir + scanlineStart + x * pixelWidth * aspect_ratio * camera_right; 						  
			ray.dir.normalize();
			int level = 0;
			// bool intersected= false;
			while (level < MAXLEVEL) 
			{
				InterPoint closest_interpt = root->intersect(ray,drawBx);
				if(!closest_interpt.hit) // background color
				{
					img(x, y, 0) += 0.3* (double)y / height;
					img(x, y, 1) += 0.3* (double)y / height;
			        img(x, y, 2) += 0.5* (double)y / height;
				}
				else
				{
					// flip the norm if it is facing away the eye
					Colour sectColor = Colour(0,0,0);

					PhongMaterial *ph_mat = dynamic_cast<PhongMaterial*>(closest_interpt.mat);

					// if (closest_interpt.n.dot(ray.dir) > 0)
					// {
					// 	closest_interpt.n.v_[0] = -closest_interpt.n.v_[0];
					// 	closest_interpt.n.v_[1] = -closest_interpt.n.v_[1];
					// 	closest_interpt.n.v_[2] = -closest_interpt.n.v_[2];
					// }

					for (lightList::const_iterator it = lights.begin(), end = lights.end(); it != end; it++)
			  		{
						// decide if the intersection point is in shadow
						bool shadowed = Shadowed(closest_interpt, root, (*it));
						if (!shadowed) 
							sectColor = sectColor + shading(ray, closest_interpt, (*it));
						else // shadow
						{
							// Vector3D L = (*it)->position - closest_interpt.pos;
							// double attenua = (*it)->falloff[0] +  (*it)->falloff[1] * L.length() + (*it)->falloff[2] * L.length2();
							// sectColor = sectColor + 1.0 / attenua * ph_mat->m_kd * ambient;
						}
					}
					if (level == 0)
						sectColor = sectColor + ph_mat->m_kd * ambient;
					
					img(x, y, 0) += sectColor.R(); 
		 			img(x, y, 1) += sectColor.G(); 
		 			img(x, y, 2) += sectColor.B();
		 		}

		 		level++;
		 		Vector3D interNorm = closest_interpt.n;
	 			double cos_ray_N = -1.0 * interNorm.dot(ray.dir) / interNorm.length();
				Vector3D R_ = ray.dir + 2*cos_ray_N / interNorm.length() * interNorm ;
				ray.pos = closest_interpt.pos;
				ray.dir = R_;
  			}
		}// x iteration
	}
	img.savePng(filename);

}


bool Shadowed(InterPoint closest_interpt, SceneNode* node, const Light* light)
{
	Vector3D l_dir = light->position - closest_interpt.pos;
	l_dir.normalize();
	Ray l_ray = {closest_interpt.pos, l_dir};

	const double dist_LnInterpt = (closest_interpt.pos - light->position).length();

	// InterPoint light_interpt = node->intersect(l_ray,false);
	InterPoint light_interpt = node->Sh_intersect(l_ray, closest_interpt.nd_name);
	// decide if light_interpt is between light source and intersection point
	if (light_interpt.hit)
	{
		if ( (light_interpt.pos - closest_interpt.pos).length()/dist_LnInterpt < 1 )
			  // && light_interpt.nd_name != closest_interpt.nd_name)
		// if ((light_interpt.pos - closest_interpt.pos).length() < dist_LnInterpt - 0.001)
		// if ( (light_interpt.pos - closest_interpt.pos).length()/dist_LnInterpt < 1 )

		{
			return true;
		}
		else
			return false;
	}
	else 
	{
		return false;
	}
}

/****************************  shading  **********************************/
Colour shading(const Ray ray, InterPoint interpt, const Light* light)
{

	Colour Diff = Colour(0,0,0);
	Colour Spec = Colour(0,0,0);

    // interpt.n.normalize();

	PhongMaterial *ph_mat = dynamic_cast<PhongMaterial*>(interpt.mat);
	Vector3D L = light->position - interpt.pos;
	// double attenua = light->falloff[0] +  light->falloff[1] * L.length() + light->falloff[2] * L.length2();

	// Ambi = ph_mat->m_kd * ambient;
	// calculate the diffuse 
	double cos_L = L.dot(interpt.n)/(L.length() * interpt.n.length()); // cosine of light and norm
	if (cos_L > 0)
	{
	  Diff = cos_L * ph_mat->m_kd * light->colour;

	}
	// std::cout << "Diff " << " R:"<<Diff.R()
					 	//  << " G:"<<Diff.G()
					 	//  << " B:"<<Diff.B() << std::endl;

	// calculate the speculate
	Vector3D R = -1.0 / L.length() * L + 2 * cos_L * 1.0 / interpt.n.length() * interpt.n;
	double cos_R = -1.0 * R.dot(ray.dir) / ray.dir.length();  // -1.0 Because ray.dir is opposite as that in course note: 
										   						// it is eye -> intersection point
	if (cos_R > 0)
	{
	  Spec = pow(cos_R, ph_mat->m_shininess) * ph_mat->m_ks * light->colour;
	}
	// std::cout << "Spec " << " R:"<<Spec.R()
	// 				 	    << " G:"<<Spec.G()
	 				 	 // << " B:"<<Spec.B() << std::endl;

	return Colour( Diff + Spec);
}

