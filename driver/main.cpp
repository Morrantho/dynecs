#include <dynecs.h>

int main(){
    /* Create a world with 4 dynamically allocated entities, components and systems */
    dx::World <4,4,4>w;
    /* Queue the first system and define its mask */
    w.QueueSystem<dx::RenderSystem>(
        dx::Transform::Mask() |
        dx::Physics::Mask()
    );
    /* Creating an Entity */
    std::shared_ptr<dx::Entity> e = w.CreateEntity();
    /* Adding components to an Entity */
    std::shared_ptr<dx::Transform> t = w.AddComponent<dx::Transform>(e);
    std::shared_ptr<dx::Physics> p = w.AddComponent<dx::Physics>(e);
    /*  
        At this point, the entity shouldve been added to 
        the RenderSystem as it now matches the system's mask. 
    */

    /* Determining if an entity contains a component */
    std::cout << w.HasComponent<dx::Transform>(e) << "\n";

    /* Removing components */
    /*
        This entities' mask no longer matches the render system's mask,
        so it is removed from that system.
    */
    w.RemoveComponent<dx::Transform>(e);

    return 0;
}