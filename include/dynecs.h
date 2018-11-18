#ifndef DX_H
#define DX_H
/* Std Lib */
#include <memory>
#include <vector>
#include <unordered_map>
#include <array>

namespace dx{
    template<int iE, int iC, int iS>
    class World;
}
/* Headers */
/* ID Generators */
#include "generators/Incrementor.h"
#include "generators/ComponentGenerator.h"
/* Entities */
#include "entities/Entity.h"
/* Components */
#include "components/Component.h"
#include "components/Transform.h"
#include "components/Physics.h"
#include "components/Sprite.h"
/* Systems*/
#include "systems/System.h"
#include "systems/RenderSystem.h"
#include "systems/PhysicsSystem.h"
#include "World.h"
#endif // DX_H
