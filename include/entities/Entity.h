#ifndef DX_ENTITY_H
#define DX_ENTITY_H
namespace dx
{
	class Entity
	{
		public:
            unsigned long id;
            unsigned long mask;

            Entity(unsigned long id) :id(id), mask(0UL) {};
            ~Entity() {};
	};
}
#endif // ENTITY_H
