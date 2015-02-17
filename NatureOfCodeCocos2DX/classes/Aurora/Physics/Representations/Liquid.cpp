#include "Liquid.h"

namespace Aurora {
	namespace Physics {
		


		void Liquid::init()
		{
			
		}

		bool Liquid::IsInside(const VECTOR2D &value)
		{
			bool isInside = false;

			// A polygon must have atleast 3 point to be a polygon, if it does not have then do not process it
			if (this->liquidArea.size() < 3)
				return isInside;

			// Below Algorithm: Copyright (c) 1970-2003, Wm. Randolph Franklin
			// http://www.ecse.rpi.edu/Homepages/wrf/Research/Short_Notes/pnpoly.html
			for (unsigned int i = 0, j = this->liquidArea.size() - 1; i < this->liquidArea.size(); j = i++) {
				if (((this->liquidArea[i].Y > value.Y) != (this->liquidArea[j].Y > value.Y)) &&
					(value.X < (this->liquidArea[j].X - this->liquidArea[i].X) * (value.Y - this->liquidArea[i].Y) / (this->liquidArea[j].Y - this->liquidArea[i].Y) + this->liquidArea[i].X))
					isInside = !isInside;
			}

			return(isInside);
		}

		Liquid::Liquid(float coefficientDrag)
		{
			
			this->coefficientDrag = coefficientDrag;
		}

		void Liquid::AddEdgePoint(const VECTOR2D &value)
		{
			this->liquidArea.push_back(value);
		}

		void ILiquid::Render()
		{
			
		}

	

	};
};
