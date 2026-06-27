#include "DataSystem.h"
#include "base/components/DataComponent.h"
#include <bit>
#include <cassert>
#include <iostream>
#include <ostream>
#include <span>

namespace ecs::benchmarks::pico_ecs::systems {

auto DataSystem::updateData(ecs_t* ecs, std::span<ecs_entity_t> entities, void* udata) -> ecs_ret_t {
  (void)ecs;
  EntityManager& uregistry = *static_cast<EntityManager*>(udata);

  for (auto entity_id : entities) {
    auto& data = *static_cast<::ecs::benchmarks::base::components::DataComponent*>(
        ecs_get(uregistry.ecs.get(), entity_id, uregistry.DataComponent));
    BaseSystem::updateData(data, uregistry.currentDt);
  }

  return 0;
}

void DataSystem::init(EntityManager& registry) {
  auto system_update = [](ecs_t* ecs, ecs_entity_t* entities, size_t entity_count, void* udata) -> ecs_ret_t {
    return updateData(ecs, std::span{entities, entity_count}, udata);
  };

  /// @NOTE: lets hope registry is still alive :)
  ecs_sys_desc_t desc{};
  desc.udata = &registry;
  m_system = ecs_define_system(registry.ecs.get(), system_update, &desc);
  ecs_require(registry.ecs.get(), m_system, registry.DataComponent);
}

void DataSystem::update(EntityManager& registry, TimeDelta dt) {
  registry.currentDt = dt;
  ecs_run_system(registry.ecs.get(), m_system, 0);
}

} // namespace ecs::benchmarks::pico_ecs::systems