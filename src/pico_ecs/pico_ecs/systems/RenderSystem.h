#ifndef ECS_BENCHMARKS_PICO_ECS_RENDERSYSTEM_H_
#define ECS_BENCHMARKS_PICO_ECS_RENDERSYSTEM_H_

#include "base/systems/RenderSystem.h"
#include "pico_ecs/entities/EntityFactory.h"
#include <pico_ecs.h>
#include <span>

namespace ecs::benchmarks::pico_ecs::systems {

namespace details {

struct RenderSystemContext {
  ecs::benchmarks::pico_ecs::entities::details::EntityManager* registry{nullptr};
  ecs::benchmarks::base::systems::RenderSystem<ecs::benchmarks::pico_ecs::entities::details::EntityManager, float>*
      system{nullptr};
};

} // namespace details

class RenderSystem final
    : public ecs::benchmarks::base::systems::RenderSystem<ecs::benchmarks::pico_ecs::entities::details::EntityManager,
                                                          float> {
public:
  using BaseSystem =
      ::ecs::benchmarks::base::systems::RenderSystem<ecs::benchmarks::pico_ecs::entities::details::EntityManager,
                                                     TimeDelta>;

  RenderSystem() = delete;
  explicit RenderSystem(base::FrameBuffer& frameBuffer)
      : ecs::benchmarks::base::systems::RenderSystem<ecs::benchmarks::pico_ecs::entities::details::EntityManager,
                                                     TimeDelta>(frameBuffer) {}

  void init(EntityManager& /*registry*/) override;
  void update(EntityManager& registry, TimeDelta dt) override;

  [[nodiscard]] inline ecs_system_t id() const noexcept { return m_system; }

private:
  ecs_system_t m_system;
  details::RenderSystemContext m_context;

  static auto renderSprite(ecs_t* ecs, std::span<ecs_entity_t> entities, void* udata) -> ecs_ret_t;
};

} // namespace ecs::benchmarks::pico_ecs::systems

#endif