#include "boundBox.hpp"


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
