#ifndef ECS_BENCHMARKS_PICO_ECS_SPRITESYSTEM_H_
#define ECS_BENCHMARKS_PICO_ECS_SPRITESYSTEM_H_

#include "base/systems/SpriteSystem.h"
#include "pico_ecs/entities/EntityFactory.h"
#include <pico_ecs.h>
#include <span>

namespace ecs::benchmarks::pico_ecs::systems {

class SpriteSystem final
    : public ecs::benchmarks::base::systems::SpriteSystem<ecs::benchmarks::pico_ecs::entities::details::EntityManager,
                                                          float> {
public:
  using BaseSystem =
      ::ecs::benchmarks::base::systems::SpriteSystem<ecs::benchmarks::pico_ecs::entities::details::EntityManager,
                                                     TimeDelta>;

  void init(EntityManager& /*registry*/) override;
  void update(EntityManager& registry, TimeDelta dt) override;

  [[nodiscard]] inline ecs_system_t id() const noexcept { return m_system; }

private:
  ecs_system_t m_system;

  static auto updateSprite(ecs_t* ecs, std::span<ecs_entity_t> entities, void* udata) -> ecs_ret_t;
};

} // namespace ecs::benchmarks::pico_ecs::systems

#endif