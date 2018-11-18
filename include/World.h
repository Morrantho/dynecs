#ifndef DX_WORLD_H
#define DX_WORLD_H
#include <iostream>

namespace dx
{
	template<int iE, int iC, int iS>
	class World
	{
	public:
		std::array< std::shared_ptr< dx::Entity >, iE > entities;
		std::array< std::array< std::shared_ptr< dx::Component >, iE>, iC > components;
		std::array< std::unique_ptr< dx::System >, iS> systems;

		std::shared_ptr<Entity> CreateEntity()
		{
			for(unsigned long i=0; i < entities.size(); i++)
			{
				if(entities[i] != nullptr) continue;
				entities[i] = std::make_shared<Entity>(i);
				entities[i].get()->mask = 0;
				return entities[i];
			}
			return nullptr;
		}

		template<typename S>
		void QueueSystem(unsigned long mask)
		{
			for(unsigned long i=0; i < systems.size(); i++)
			{
				if(systems[i] != nullptr) continue;
				systems[i] = std::make_unique<S>(mask);
				return;
			}
		}

		template<typename C>
		bool HasComponent( const std::shared_ptr<Entity> &e )
		{
			return components[ C::ID() ][ e->id ] != nullptr;
		}

		template<typename C>
		std::shared_ptr<C> AddComponent( const std::shared_ptr<Entity> &e )
		{
			e->mask |= C::Mask();
			components[ C::ID() ][ e->id ] = std::make_shared<C>();

			for(unsigned long i = 0; i < systems.size(); i++)
			{
				if( systems[i] == nullptr ) continue;

				if( (systems[i]->mask & e->mask) == systems[i]->mask )
				{
					std::cout << "Adding entity: " << e->id << " to system: " << systems[i]->mask << "\n";
					systems[i]->entities.insert({ { e->id, e } });
				}
			}

			return std::static_pointer_cast<C>(components[ C::ID() ][ e->id ]);
		}

		template<typename C>
		void RemoveComponent(const std::shared_ptr<Entity>& e)
		{
			e->mask ^= C::Mask();
			components[ C::ID() ][ e->id ] = nullptr;

			for(unsigned long i = 0; i < systems.size(); i++)
			{
				if(systems[i] == nullptr) continue;

				if( ( systems[i]->mask & e->mask ) != systems[i]->mask )
				{
					std::cout << "Removing entity: " << e->id << " from system: " << systems[i]->mask << "\n";
					bool exists = systems[i]->entities.find( e->id ) == systems[i]->entities.end() ? 0:1;
					if(exists) systems[i]->entities.erase( e->id );
				}
			}
		}

		template<typename C>
		std::shared_ptr<C> GetComponent(const std::shared_ptr<Entity>& e)
		{
			return components[ C::ID() ][ e->id ];
		}
	};
}
#endif // DX_WORLD_H
