# dynecs
A Header Only C++ Entity Component System.

## Description:

dynecs is a simple C++ ECS.

### Systems:

Systems can be defined by extending <code> dx::System </code>. The system class is purely virtual, so you'll need to provide your own <code>Tick()</code> and <code>Render()</code> methods.

```c++
class CollisionSystem : public dx::System
{
public:
	CollisionSystem(unsigned long mask): System(mask) {}

	void Tick()
	{
		for( Entity a: entities ){
			for( Entity b: entities ){
				if( a.intersects(b) ){
					// You get the idea.
				}
			}
		}
	}

	void Render()
	{

	}
};
```

### Components:

Components can be defined by extending <code>dx::Component</code> and <code>dx::ComponentGenerator</code> to generate unique class ID's:

```c++
class Input: public Component, public dx::ComponentGenerator<Input>
{
	public:
		int direction;
		int mouseX;
		int mouseY;
};
```

### Entities:

Entities can be defined by extending <code> dx::Entity </code>. By implementing a virtual <code>Init()</code> method, you're supplied with a const world reference. This method is called by the world once you've created an entity via: <code>world.CreateEntity<YourEntity>()</code> With this, you add the components that this entity should be comprised of: 

```c++
class Player: public dx::Entity
{
	public:		
		void Init(const World& world){
			world.AddComponent< dx::Input >(this);
			world.AddComponent< dx::Sprite >(this);
			world.AddComponent< dx::Physics >(this);
			world.AddComponent< dx::Health >(this);
			world.AddComponent< dx::Collider >(this);
			world.AddComponent< dx::Motion >(this);
		}
};
```
### World API:

#### std::shared_ptr<Entity> CreateEntity()

Returns a shared pointer to an entity that gets stored into the world's entity list. 

#### std::shared_ptr<E> CreateEntity()

Returns a shared pointer to a <strong>derived</strong> entity that gets stored into the world's entity array.

#### void QueueSystem<S>(unsigned long mask)
	
Queues a <strong>derived</strong> system into the world's system array, only operating on future entities that have the same mask as the supplied mask. The order in which systems are queued is important. For instance, you wouldn't queue a RenderSystem before an InputSystem.

#### bool HasComponent<C>(const std::shared_ptr<Entity> &e)
	
Determines if the supplied entity contains the supplied component.

#### std::shared_ptr<C> AddComponent(const std::shared_ptr<Entity> &e)

Adds the supplied component to the supplied entity if it doesn't already contain it. In adding a component, it may now match an existing system's mask. If this is true, the entity will be placed into that system's list of entities for future operation.

#### void RemoveComponent<C>(const std::shared_ptr<Entity> &e)
	
Removes the supplied component from the supplied entity if it contains it. In removing a component, it may no longder match an existing system's mask. If this is true, the entity will be removed from that system's list of entities.


#### std::shared_ptr<C> GetComponent(const std::shared_ptr<Entity> &e)
	
Returns a shared pointer to the supplied component for the supplied entity if this entity contains this component. Otherwise, returning null.
