#include "MoreComplexSystem.h"
#include "base/components/DataComponent.h"
#include "base/components/PositionComponent.h"
#include "base/components/VelocityComponent.h"
#include <bit>
#include <cassert>
#include <span>

namespace ecs::benchmarks::pico_ecs::systems {

auto MoreComplexSystem::updateMoreComplex(ecs_t* ecs, std::span<ecs_entity_t> entities, void* udata)
    -> ecs_ret_t {
  (void)ecs;
  EntityManager& uregistry = *static_cast<EntityManager*>(udata);

  for (auto entity_id : entities) {
    auto& position = *static_cast<ecs::benchmarks::base::components::PositionComponent*>(
        ecs_get(uregistry.ecs.get(), entity_id, uregistry.PositionComponent));
    auto& direction = *static_cast<ecs::benchmarks::base::components::VelocityComponent*>(
        ecs_get(uregistry.ecs.get(), entity_id, uregistry.VelocityComponent));
    auto& data = *static_cast<ecs::benchmarks::base::components::DataComponent*>(
        ecs_get(uregistry.ecs.get(), entity_id, uregistry.DataComponent));
    BaseSystem::updateComponents(position, direction, data);
  }

  return 0;
}
void MoreComplexSystem::init(EntityManager& registry) {
  auto system_update = [](ecs_t* ecs, ecs_entity_t* entities, size_t entity_count, void* udata) -> ecs_ret_t {
    return updateMoreComplex(ecs, std::span{entities, entity_count}, udata);
  };

  ecs_sys_desc_t desc{};
  desc.udata = &registry;
  m_system = ecs_define_system(registry.ecs.get(), system_update, &desc);
  ecs_require(registry.ecs.get(), m_system, registry.PositionComponent);
  ecs_require(registry.ecs.get(), m_system, registry.VelocityComponent);
  ecs_require(registry.ecs.get(), m_system, registry.DataComponent);
}
void MoreComplexSystem::update(EntityManager& registry, TimeDelta dt) {
  registry.currentDt = dt;
  ecs_run_system(registry.ecs.get(), m_system, 0);
}

} // namespace ecs::benchmarks::pico_ecs::systems