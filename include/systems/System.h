#ifndef DX_SYSTEM_H
#define DX_SYSTEM_H
namespace dx
{
	class System
	{
	public:
		unsigned long mask;
		/* Entity Masks are keys, weak pointers to them are values */
		std::unordered_map< unsigned long, std::weak_ptr< dx::Entity > > entities;

		System(unsigned long _mask) : mask(_mask) {}
		~System() {}

		virtual void Tick() = 0;
		virtual void Render() = 0;
	};
}
#endif // DX_SYSTEM_H
