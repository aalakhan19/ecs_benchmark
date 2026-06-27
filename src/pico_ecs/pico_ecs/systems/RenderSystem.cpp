#include "RenderSystem.h"
#include "base/components/PositionComponent.h"
#include "base/components/SpriteComponent.h"
#include "base/components/VelocityComponent.h"
#include <bit>
#include <cassert>
#include <span>

namespace ecs::benchmarks::pico_ecs::systems {

auto RenderSystem::renderSprite(ecs_t* ecs, std::span<ecs_entity_t> entities, void* udata) -> ecs_ret_t {
  (void)ecs;
  details::RenderSystemContext& context = *static_cast<details::RenderSystemContext*>(udata);

  for (auto entity_id : entities) {
    const auto& position = *static_cast<::ecs::benchmarks::base::components::PositionComponent*>(
        ecs_get(context.registry->ecs.get(), entity_id, context.registry->PositionComponent));
    const auto& sprite = *static_cast<::ecs::benchmarks::base::components::SpriteComponent*>(
        ecs_get(context.registry->ecs.get(), entity_id, context.registry->SpriteComponent));
    context.system->renderSprite(position, sprite);
  }

  return 0;
}

void RenderSystem::init(EntityManager& registry) {
  auto system_update = [](ecs_t* ecs, ecs_entity_t* entities, size_t entity_count, void* udata) -> ecs_ret_t {
    return renderSprite(ecs, std::span{entities, entity_count}, udata);
  };

  m_context = details::RenderSystemContext{
      .registry = &registry,
      .system = this,
  };
  ecs_sys_desc_t desc{};
  desc.udata = &m_context;
  m_system = ecs_define_system(registry.ecs.get(), system_update, &desc);
  ecs_require(registry.ecs.get(), m_system, registry.PositionComponent);
  ecs_require(registry.ecs.get(), m_system, registry.SpriteComponent);
}

void RenderSystem::update(EntityManager& registry, TimeDelta dt) {
  registry.currentDt = dt;
  ecs_run_system(registry.ecs.get(), m_system, 0);
}

} // namespace ecs::benchmarks::pico_ecs::systems