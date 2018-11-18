# dynecs
A Header Only C++ Entity Component System.

## Description:

dynecs is a simple C++ ECS. It uses smart pointers where dynamic allocation is necessary. The world class is a container for holding entities, component data and systems for manipulating specific entities. You must first create a world to begin using the API:

```c++
#include <dynecs.h>

int main(){
	World <8,4,3>world;

	return 0;
}
```
The world class is a template, accepting number of entities, components and systems respectively that can exist within your world as indicated in the above snippet upon instantiation. 

### Systems:

From this point, Queue Systems that you want to run in a specific order while also defining each system's mask so that it only operates on entities with the specified components:

```c++
world.QueueSystem<dx::RenderSystem>(
	dx::Transform::Mask() |
	dx::Sprite::Mask()
);
```

Systems can be defined by extending <code> dx::System </code>. The system class is purely virtual, so you'll need to provide your own <code>Tick()</code> and <code>Render()</code> methods. System masks are defined upon Queueing them into a world as indicated above:

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

Entities can be defined by extending <code> dx::Entity </code>. In doing so, an <code>Init()</code> callback is provided to supplying you with a world reference and the ability to add components to your entity.

```c++
class Player: public dx::Entity
{
	public:		
		void Init(World& world){
			world.AddComponent< dx::Input >(this);
			world.AddComponent< dx::Sprite >(this);
			world.AddComponent< dx::Physics >(this);
			world.AddComponent< dx::Health >(this);
			world.AddComponent< dx::Collider >(this);
			world.AddComponent< dx::Motion >(this);
		}
};
```


### World:
