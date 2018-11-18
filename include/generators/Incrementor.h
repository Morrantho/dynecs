#ifndef DX_INCREMENTOR_H
#define DX_INCREMENTOR_H
namespace dx
{
	class Incrementor
	{
		public:
			static unsigned long componentId;
	};
}
unsigned long dx::Incrementor::componentId = 0;
#endif // DX_INCREMENTOR_H
