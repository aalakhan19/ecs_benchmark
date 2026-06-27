#include "HealthSystem.h"
#include <bit>
#include <cassert>
#include <span>

namespace ecs::benchmarks::pico_ecs::systems {

auto HealthSystem::updateHealth(ecs_t* ecs, std::span<ecs_entity_t> entities, void* udata) -> ecs_ret_t {
  (void)ecs;
  EntityManager& uregistry = *static_cast<EntityManager*>(udata);

  for (auto entity_id : entities) {
    auto& health = *static_cast<ecs::benchmarks::base::components::HealthComponent*>(
        ecs_get(uregistry.ecs.get(), entity_id, uregistry.HealthComponent));
    BaseSystem::updateHealth(health);
  }

  return 0;
}
void HealthSystem::init(EntityManager& registry) {
  auto system_update = [](ecs_t* ecs, ecs_entity_t* entities, size_t entity_count, void* udata) -> ecs_ret_t {
    return updateHealth(ecs, std::span{entities, entity_count}, udata);
  };

  /// @NOTE: lets hope registry is still alive :)
  ecs_sys_desc_t desc{};
  desc.udata = &registry;
  m_system = ecs_define_system(registry.ecs.get(), system_update, &desc);
  ecs_require(registry.ecs.get(), m_system, registry.HealthComponent);
}
void HealthSystem::update(EntityManager& registry, TimeDelta dt) {
  registry.currentDt = dt;
  ecs_run_system(registry.ecs.get(), m_system, 0);
}

} // namespace ecs::benchmarks::pico_ecs::systems