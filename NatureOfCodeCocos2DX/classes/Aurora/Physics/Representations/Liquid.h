#ifndef NatureOfCodeCocos2DX_Liquid_h
#define NatureOfCodeCocos2DX_Liquid_h



#include "IPhysicsRepresentationBase.h"

using namespace Aurora::Math;

namespace Aurora {
	namespace Physics {
		class Liquid : public IPhysicsRepresentationBase
		{
			protected:
				virtual void init() override;
				float coefficientDrag;
				std::vector<VECTOR2D> liquidArea;
				


		public:
			Liquid() = default;
			virtual ~Liquid() = default;

			Liquid(float coefficientDrag);

			
			bool IsInside(const VECTOR2D &value);

			float CoefficientDrag() const { return coefficientDrag; }
			template<typename T>
			void CoefficientDrag(T &&value) { coefficientDrag = std::forward<T>(value); }
			
			std::vector<VECTOR2D> LiquidArea() const { return liquidArea; }
			
			void AddEdgePoint(const VECTOR2D &value);

		};
		
		class ILiquid
		{
		public:
			ILiquid() = default;
			virtual ~ILiquid() = default;

			virtual void Render() = 0;



			//virtual void SetMoverTarget(const VECTOR2D &target);
		};
	};
};

#endif