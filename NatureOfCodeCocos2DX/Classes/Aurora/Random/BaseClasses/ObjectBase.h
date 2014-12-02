#ifndef NatureOfCodeCocos2DX_ObjectBase_h
#define NatureOfCodeCocos2DX_ObjectBase_h


#include "../../Physics/PhysicsOperations.h"
#include "RandomBase.h"


namespace Aurora {
    namespace Random {

		class IObjectBaseBasic //: public IRandomBase
        {
            protected:
				std::shared_ptr<Physics::Force> objectPhysics;
				virtual void init();
            public:
				IObjectBaseBasic() = default;
				virtual ~IObjectBaseBasic() = default;
                virtual void Render() = 0;

				/*IObjectBaseBasic& operator=(const IObjectBaseBasic& value);
				IObjectBaseBasic(IObjectBaseBasic &&value);
				IObjectBaseBasic & operator=(IObjectBaseBasic && value);*/

				/*virtual void init() override;
				virtual void init(RandomNumberMode randomNumberMode);*/

				std::shared_ptr<Physics::Force> ObjectPhysics() const { return objectPhysics; }
				template<typename T>
				void ObjectPhysics(T &&value) { objectPhysics = std::forward<T>(value); }
		};

		}; // END OF NAMESPACE Random
}; // END OF NAMESPACE Aurora


#endif