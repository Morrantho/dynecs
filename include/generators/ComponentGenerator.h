#ifndef DX_COMPONENTGENERATOR_H
#define DX_COMPONENTGENERATOR_H
namespace dx
{
	template<typename T>
	class ComponentGenerator
	{
		public:
			static unsigned long ID()
			{
				static unsigned long id = dx::Incrementor::componentId++;
				return id;
			}

			static unsigned long Mask()
			{
				return 1UL << ID();
			}
	};
}
#endif // DX_COMPONENTGENERATOR_H
