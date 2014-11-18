#ifndef NatureOfCodeCocos2DX_ObjectBase_h
#define NatureOfCodeCocos2DX_ObjectBase_h


#include "RandomBase.h"



namespace Aurora {
    namespace Random {

		class IObjectBaseBasic //: public IRandomBase
        {
            protected:
                
            public:
				IObjectBaseBasic() = default;
				virtual ~IObjectBaseBasic() = default;
                virtual void Render() = 0;

				/*IObjectBaseBasic& operator=(const IObjectBaseBasic& value);
				IObjectBaseBasic(IObjectBaseBasic &&value);
				IObjectBaseBasic & operator=(IObjectBaseBasic && value);*/

				/*virtual void init() override;
				virtual void init(RandomNumberMode randomNumberMode);*/

		};

		}; // END OF NAMESPACE Random
}; // END OF NAMESPACE Aurora


#endif