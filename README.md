# Entity-Component-System Benchmarks

[![Actions Status](https://github.com/abeimler/ecs_benchmark/workflows/ci/badge.svg)](https://github.com/abeimler/ecs_benchmark/actions)
![License](https://img.shields.io/github/license/abeimler/ecs_benchmark)
![Standard](https://img.shields.io/badge/c%2B%2B-20-blue)

This repository contains a collection of benchmarks for popular Entity-Component-System (ECS) frameworks.
The benchmarks cover different aspects of ECS frameworks, such as update systems, component additions/removals, and entity creation/destruction.
It's important to note that different ECS frameworks have different strengths and weaknesses.
For example, some frameworks might excel in adding/removing components, while others might be better at creating/destroying entities or have query support.
Therefore, it's crucial to choose an ECS framework based on your specific requirements.

ECS (Entity-Component-System) Frameworks:

* [EntityX](https://github.com/alecthomas/entityx)
* [EnTT](https://github.com/skypjack/entt)
* [Ginseng](https://github.com/apples/ginseng)
* [mustache](https://github.com/kirillochnev/mustache)
* [flecs](https://github.com/SanderMertens/flecs)
* [pico_ecs](https://github.com/empyreanx/pico_headers)
* [gaia-ecs](https://github.com/richardbiely/gaia-ecs)

## TL;DR Results

Main feature of an ECS is the iterating over a lot of entities and using system to update the components.
The results of these benchmarks should be used as a starting point for your own benchmarking efforts.

### Update systems (for-each entities (with mixed components) in 7 systems)


![ComplexSystemsUpdateMixedEntities Plot](img/ComplexSystemsUpdateMixedEntities.svg)

_Graph shows cost per entity, tables shows total cost. lower is faster._

|                                      | EnTT   | EnTT (runtime)   | EnTT (group)   | EnTT (stable)         | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   | gaia-ecs (SoA)   |
|:-------------------------------------|:-------|:-----------------|:---------------|:----------------------|:----------|:-----------|:--------|:-----------|:-----------|:-----------------|
| Update     1 entities with 7 Systems | 123ns  | 130ns            | 89ns           | 131ns                 | 48ns      | 221ns      | 1741ns  | 67ns       | 227ns      | 225ns            |
| Update     4 entities with 7 Systems | 223ns  | 364ns            | 138ns          | 169ns                 | 106ns     | 475ns      | 2727ns  | 125ns      | 416ns      | 394ns            |
| Update     8 entities with 7 Systems | 310ns  | 684ns            | 203ns          | 237ns                 | 173ns     | 534ns      | 2868ns  | 209ns      | 454ns      | 454ns            |
| Update    16 entities with 7 Systems | 348ns  | 838ns            | 207ns          | 182ns                 | 205ns     | 425ns      | 2663ns  | 209ns      | 355ns      | 332ns            |
| Update    32 entities with 7 Systems | 574ns  | 1622ns           | 304ns          | 237ns                 | 368ns     | 520ns      | 2810ns  | 370ns      | 419ns      | 443ns            |
| Update    64 entities with 7 Systems | 1038ns | 3052ns           | 501ns          | 353ns                 | 728ns     | 661ns      | 2960ns  | 652ns      | 560ns      | 558ns            |

|                                      | EnTT   | EnTT (runtime)   | EnTT (group)   | EnTT (stable)         | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   | gaia-ecs (SoA)   |
|:-------------------------------------|:-------|:-----------------|:---------------|:----------------------|:----------|:-----------|:--------|:-----------|:-----------|:-----------------|
| Update   256 entities with 7 Systems | 7us    | 21us             | 4us            | 4us                   | 4us       | 2us        | 4us     | 5us        | 2us        | 2us              |
| Update   ~1K entities with 7 Systems | 31us   | 91us             | 18us           | 21us                  | 16us      | 7us        | 10us    | 19us       | 9us        | 10us             |
| Update   ~4K entities with 7 Systems | 138us  | 374us            | 89us           | 103us                 | 68us      | 27us       | 30us    | 91us       | 45us       | 45us             |
| Update  ~16K entities with 7 Systems | 569us  | 1455us           | 403us          | 365us                 | 321us     | 113us      | 120us   | 366us      | 219us      | 211us            |

|                                      | EnTT   | EnTT (runtime)   | EnTT (group)   | EnTT (stable)         | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   | gaia-ecs (SoA)   |
|:-------------------------------------|:-------|:-----------------|:---------------|:----------------------|:----------|:-----------|:--------|:-----------|:-----------|:-----------------|
| Update  ~65K entities with 7 Systems | 2ms    | 5ms              | 1ms            | 1ms                   | 1ms       | 0ms        | 0ms     | 1ms        | 1ms        | 1ms              |
| Update  262K entities with 7 Systems | 12ms   | 24ms             | 8ms            | 6ms                   | 6ms       | 3ms        | 3ms     | 6ms        | 7ms        | 7ms              |
| Update   ~1M entities with 7 Systems | 40ms   | 102ms            | 35ms           | 26ms                  | 27ms      | 16ms       | 19ms    | 25ms       | 31ms       | 32ms             |
| Update   ~2M entities with 7 Systems | 85ms   | 184ms            | 87ms           | 51ms                  | 55ms      | 33ms       | 42ms    | 53ms       | 62ms       | 69ms             |



While this benchmark only includes up to 6 components and 7 small systems,
it's important to note that Entity-Component-Systems can become much more complex in the wild,
with hundreds of components and systems.
Therefore, it's crucial to always benchmark your specific cases and systems when necessary and compare results.
Choose an ECS framework based on its features,
for example, EnTT offers [resource management](https://github.com/skypjack/entt/wiki/Crash-Course:-resource-management) and [event handling](https://github.com/skypjack/entt/wiki/Crash-Course:-events,-signals-and-everything-in-between),
while flecs provides useful [add-ons](https://github.com/SanderMertens/flecs#addons) and [querying](https://github.com/SanderMertens/flecs/tree/master/examples/cpp/queries/basics),
and EntityX includes a built-in [world/system manager](https://github.com/alecthomas/entityx#manager-tying-it-all-together=).

To evaluate a framework, look at the examples and API design, and pick the one that suits your needs.


## Details

### Features

All benchmarks are located in the [`benchmark/benchmarks/`](benchmark/benchmarks/) directory and write with with the [google/benchmark](https://github.com/google/benchmark) library.
Each benchmark uses an example application for each framework (see [`src/`](src) directory), and every example application has specific base features implemented (see [`src/base`](src/base)).

#### Components

1. `PositionComponent`: includes `x` and `y` coordinates.
2. `VelocityComponent`: includes `x` and `y` coordinates for movement.
3. `DataComponent`: includes some arbitrary data.
4. `HealthComponent`: Hero/Monster data includes HP/MaxHP and status.
5. `DamageComponent`: Hero/Monster data includes damage.
6. `SpriteComponent`: Hero/Monster ASCII character as sprite.

#### Systems

1. `MovementSystem`: updates the `PositionComponent` with a constant `VelocityComponent`.
2. `DataSystem`: updates the `DataComponent` with arbitrary data.
3. `MoreComplexSystem`: updates components with random data and arbitrary information.
4. `HealthSystem`: update Hero/Monster health (update HP and status).
5. `DamageSystem`: update Hero/Monster health by taking damage.
6. `SpriteSystem`: update Hero/Monster ASCII character depending on health and type.
7. `RenderSystem`: "render"(write) Hero/Monster character sprite into a "frame buffer"(string buffer).



## Additional Benchmarks

Benchmarks for more common features, such as "Creating entities", "Adding and removing components", and others.

### Features tested

* Entity Creation
* Entity Destruction
* Component Retrieval
* Adding and removing components
* Iterating entities/quires


### Environment

* **OS:** Linux 64-Bit (Kernel: 6.10.4)
* **CPU:** 3.13GHz @ 12Cores
* **RAM:** 47GB
* **Compiler:** gcc (GCC) 14.2.1


---

### Create entities


![CreateEntities Plot](img/CreateEntities.svg)

_Graph shows cost per entity, tables shows total cost. lower is faster._

|                                           | EntityX   | EnTT   | Ginseng   | mustache   | Flecs    | pico_ecs   | gaia-ecs   |
|:------------------------------------------|:----------|:-------|:----------|:-----------|:---------|:-----------|:-----------|
| Create     1 entities with two Components | 1368ns    | 2881ns | 10449ns   | 2327ns     | 439949ns | 1331ns     | 4683ns     |
| Create     4 entities with two Components | 1816ns    | 3155ns | 10119ns   | 2692ns     | 444861ns | 1315ns     | 4901ns     |
| Create     8 entities with two Components | 2245ns    | 3461ns | 10313ns   | 3086ns     | 444572ns | 1426ns     | 5522ns     |
| Create    16 entities with two Components | 2995ns    | 3812ns | 10869ns   | 3654ns     | 443523ns | 1555ns     | 6458ns     |
| Create    32 entities with two Components | 4233ns    | 4419ns | 11265ns   | 4838ns     | 448326ns | 1875ns     | 8323ns     |
| Create    64 entities with two Components | 6848ns    | 5706ns | 12227ns   | 7042ns     | 467177ns | 2499ns     | 12369ns    |

|                                           | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:------------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Create   256 entities with two Components | 21us      | 13us   | 16us      | 20us       | 535us   | 6us        | 36us       |
| Create   ~1K entities with two Components | 81us      | 42us   | 34us      | 73us       | 846us   | 21us       | 125us      |
| Create   ~4K entities with two Components | 318us     | 161us  | 101us     | 283us      | 1958us  | 92us       | 481us      |
| Create  ~16K entities with two Components | 1319us    | 623us  | 363us     | 1109us     | 6365us  | 366us      | 1924us     |

|                                           | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:------------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Create  ~65K entities with two Components | 4ms       | 2ms    | 1ms       | 4ms        | 22ms    | 1ms        | 8ms        |
| Create  262K entities with two Components | 20ms      | 10ms   | 8ms       | 18ms       | 109ms   | 6ms        | 36ms       |
| Create   ~1M entities with two Components | 97ms      | 68ms   | 52ms      | 90ms       | 409ms   | 48ms       | 151ms      |
| Create   ~2M entities with two Components | 191ms     | 133ms  | 109ms     | 175ms      | 741ms   | 77ms       | 325ms      |



### Destroy entities


![DestroyEntities Plot](img/DestroyEntities.svg)

_Graph shows cost per entity, tables shows total cost. lower is faster._

|                                            | EntityX   | EnTT   | Ginseng   | Flecs    | pico_ecs   | gaia-ecs   |
|:-------------------------------------------|:----------|:-------|:----------|:---------|:-----------|:-----------|
| Destroy     1 entities with two components | 1008ns    | 904ns  | 1056ns    | 364035ns | 1208ns     | 3074ns     |
| Destroy     4 entities with two components | 1236ns    | 1028ns | 1419ns    | 363733ns | 1241ns     | 3355ns     |
| Destroy     8 entities with two components | 1366ns    | 1196ns | 1975ns    | 381173ns | 1267ns     | 3751ns     |
| Destroy    16 entities with two components | 1660ns    | 1502ns | 2793ns    | 371021ns | 1320ns     | 4752ns     |
| Destroy    32 entities with two components | 2394ns    | 2139ns | 4419ns    | 377250ns | 1438ns     | 6833ns     |
| Destroy    64 entities with two components | 3815ns    | 3372ns | 7731ns    | 376331ns | 1644ns     | 10905ns    |

|                                            | EntityX   | EnTT   | Ginseng   | Flecs   | pico_ecs   | gaia-ecs   |
|:-------------------------------------------|:----------|:-------|:----------|:--------|:-----------|:-----------|
| Destroy   256 entities with two components | 12us      | 11us   | 28us      | 383us   | 2us        | 32us       |
| Destroy   ~1K entities with two components | 48us      | 40us   | 105us     | 415us   | 8us        | 121us      |
| Destroy   ~4K entities with two components | 201us     | 157us  | 434us     | 590us   | 32us       | 487us      |
| Destroy  ~16K entities with two components | 812us     | 627us  | 1743us    | 1243us  | 122us      | 2038us     |

|                                            | EntityX   | EnTT   | Ginseng   | Flecs   | pico_ecs   | gaia-ecs   |
|:-------------------------------------------|:----------|:-------|:----------|:--------|:-----------|:-----------|
| Destroy  ~65K entities with two components | 3ms       | 2ms    | 6ms       | 3ms     | 0ms        | 7ms        |
| Destroy  262K entities with two components | 14ms      | 10ms   | 27ms      | 17ms    | 2ms        | 35ms       |
| Destroy   ~1M entities with two components | 63ms      | 43ms   | 115ms     | 60ms    | 11ms       | 178ms      |
| Destroy   ~2M entities with two components | 124ms     | 86ms   | 227ms     | 118ms   | 19ms       | 398ms      |



### Get one component from entity


![UnpackOneComponent Plot](img/UnpackOneComponent.svg)

_Graph shows cost per entity, tables shows total cost. lower is faster._

|                                        | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:---------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Unpack one component in     1 entities | 3ns       | 3ns    | 1ns       | 13ns       | 13ns    | 1ns        | 2ns        |
| Unpack one component in     4 entities | 14ns      | 12ns   | 7ns       | 47ns       | 57ns    | 5ns        | 10ns       |
| Unpack one component in     8 entities | 28ns      | 25ns   | 13ns      | 84ns       | 112ns   | 11ns       | 20ns       |
| Unpack one component in    16 entities | 57ns      | 51ns   | 28ns      | 174ns      | 212ns   | 27ns       | 40ns       |
| Unpack one component in    32 entities | 115ns     | 107ns  | 59ns      | 376ns      | 415ns   | 49ns       | 84ns       |
| Unpack one component in    64 entities | 231ns     | 204ns  | 118ns     | 655ns      | 856ns   | 90ns       | 164ns      |

|                                        | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:---------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Unpack one component in   256 entities | 0us       | 0us    | 0us       | 2us        | 3us     | 0us        | 0us        |
| Unpack one component in   ~1K entities | 3us       | 3us    | 1us       | 10us       | 12us    | 1us        | 2us        |
| Unpack one component in   ~4K entities | 14us      | 12us   | 7us       | 44us       | 51us    | 5us        | 10us       |
| Unpack one component in  ~16K entities | 59us      | 51us   | 28us      | 203us      | 210us   | 21us       | 42us       |

|                                        | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:---------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Unpack one component in  ~65K entities | 0ms       | 0ms    | 0ms       | 0ms        | 0ms     | 0ms        | 0ms        |
| Unpack one component in  262K entities | 1ms       | 0ms    | 0ms       | 2ms        | 3ms     | 0ms        | 0ms        |
| Unpack one component in   ~1M entities | 4ms       | 3ms    | 2ms       | 11ms       | 13ms    | 1ms        | 3ms        |
| Unpack one component in   ~2M entities | 9ms       | 7ms    | 4ms       | 23ms       | 26ms    | 2ms        | 8ms        |


**Note:**
* Get one non-const component
   1. `PositionComponent`


### Get two components from entity


![UnpackTwoComponents Plot](img/UnpackTwoComponents.svg)

_Graph shows cost per entity, tables shows total cost. lower is faster._

|                                         | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:----------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Unpack two components in     1 entities | 7ns       | 6ns    | 3ns       | 23ns       | 28ns    | 2ns        | 4ns        |
| Unpack two components in     4 entities | 28ns      | 25ns   | 14ns      | 98ns       | 110ns   | 11ns       | 16ns       |
| Unpack two components in     8 entities | 57ns      | 55ns   | 28ns      | 190ns      | 210ns   | 21ns       | 37ns       |
| Unpack two components in    16 entities | 115ns     | 104ns  | 56ns      | 364ns      | 409ns   | 48ns       | 72ns       |
| Unpack two components in    32 entities | 231ns     | 212ns  | 118ns     | 730ns      | 803ns   | 89ns       | 135ns      |
| Unpack two components in    64 entities | 462ns     | 468ns  | 236ns     | 1554ns     | 1599ns  | 171ns      | 267ns      |

|                                         | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:----------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Unpack two components in   256 entities | 1us       | 1us    | 0us       | 5us        | 6us     | 0us        | 1us        |
| Unpack two components in   ~1K entities | 7us       | 6us    | 3us       | 22us       | 25us    | 2us        | 4us        |
| Unpack two components in   ~4K entities | 29us      | 26us   | 14us      | 88us       | 103us   | 10us       | 16us       |
| Unpack two components in  ~16K entities | 118us     | 105us  | 56us      | 368us      | 458us   | 42us       | 68us       |

|                                         | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:----------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Unpack two components in  ~65K entities | 0ms       | 0ms    | 0ms       | 1ms        | 1ms     | 0ms        | 0ms        |
| Unpack two components in  262K entities | 2ms       | 1ms    | 0ms       | 6ms        | 6ms     | 0ms        | 1ms        |
| Unpack two components in   ~1M entities | 9ms       | 7ms    | 3ms       | 24ms       | 26ms    | 2ms        | 5ms        |
| Unpack two components in   ~2M entities | 18ms      | 14ms   | 7ms       | 50ms       | 53ms    | 5ms        | 10ms       |



**Note:**
* Get non-const- and const-component
   1. `PositionComponent`
   2. `const VelocityComponent`


### Get three components from entity


![UnpackThreeComponents Plot](img/UnpackThreeComponents.svg)

_Graph shows cost per entity, tables shows total cost. lower is faster._

|                                           | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:------------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Unpack three components in     1 entities | 7ns       | 12ns   | 6ns       | 23ns       | 59ns    | 3ns        | 9ns        |
| Unpack three components in     2 entities | 14ns      | 24ns   | 12ns      | 44ns       | 125ns   | 7ns        | 17ns       |
| Unpack three components in     8 entities | 57ns      | 100ns  | 48ns      | 193ns      | 449ns   | 35ns       | 75ns       |
| Unpack three components in    16 entities | 115ns     | 196ns  | 97ns      | 384ns      | 888ns   | 69ns       | 142ns      |
| Unpack three components in    32 entities | 231ns     | 431ns  | 195ns     | 767ns      | 1781ns  | 121ns      | 276ns      |
| Unpack three components in    64 entities | 470ns     | 795ns  | 396ns     | 1504ns     | 3588ns  | 237ns      | 546ns      |
| Unpack three components in   128 entities | 927ns     | 1557ns | 841ns     | 2826ns     | 7121ns  | 468ns      | 1084ns     |

|                                           | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:------------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Unpack three components in   512 entities | 3us       | 6us    | 3us       | 11us       | 30us    | 1us        | 4us        |
| Unpack three components in   ~2K entities | 14us      | 25us   | 12us      | 44us       | 112us   | 7us        | 17us       |
| Unpack three components in   ~8K entities | 59us      | 100us  | 50us      | 180us      | 449us   | 29us       | 72us       |

|                                           | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:------------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Unpack three components in  ~32K entities | 0ms       | 0ms    | 0ms       | 0ms        | 1ms     | 0ms        | 0ms        |
| Unpack three components in  131K entities | 1ms       | 1ms    | 0ms       | 2ms        | 7ms     | 0ms        | 1ms        |
| Unpack three components in  524K entities | 4ms       | 6ms    | 3ms       | 12ms       | 28ms    | 1ms        | 5ms        |
| Unpack three components in   ~1M entities | 9ms       | 14ms   | 7ms       | 25ms       | 57ms    | 3ms        | 11ms       |



**Note:**
* Not every entity has three components, some has only two
* Get two non-const- and const-component(s)
   1. `PositionComponent`
   2. `const VelocityComponent`
   3. `DataComponent` (optional)


### Remove and add component


![RemoveAddComponent Plot](img/RemoveAddComponent.svg)

_Graph shows cost per entity, tables shows total cost. lower is faster._

|                                              | EntityX   | EnTT   | Ginseng   | Flecs   | pico_ecs   | gaia-ecs   |
|:---------------------------------------------|:----------|:-------|:----------|:--------|:-----------|:-----------|
| Remove and Add a Component in     1 entities | 15ns      | 24ns   | 11ns      | 246ns   | 8ns        | 130ns      |
| Remove and Add a Component in     4 entities | 59ns      | 109ns  | 43ns      | 957ns   | 42ns       | 535ns      |
| Remove and Add a Component in     8 entities | 125ns     | 204ns  | 93ns      | 1901ns  | 69ns       | 1057ns     |
| Remove and Add a Component in    16 entities | 244ns     | 396ns  | 181ns     | 3751ns  | 132ns      | 2108ns     |
| Remove and Add a Component in    32 entities | 500ns     | 785ns  | 353ns     | 7450ns  | 256ns      | 4192ns     |
| Remove and Add a Component in    64 entities | 951ns     | 1560ns | 703ns     | 14853ns | 505ns      | 8379ns     |

|                                              | EntityX   | EnTT   | Ginseng   | Flecs   | pico_ecs   | gaia-ecs   |
|:---------------------------------------------|:----------|:-------|:----------|:--------|:-----------|:-----------|
| Remove and Add a Component in   256 entities | 3us       | 6us    | 2us       | 59us    | 2us        | 33us       |
| Remove and Add a Component in   ~1K entities | 15us      | 25us   | 11us      | 236us   | 8us        | 134us      |
| Remove and Add a Component in   ~4K entities | 60us      | 104us  | 48us      | 1004us  | 32us       | 536us      |
| Remove and Add a Component in  ~16K entities | 249us     | 408us  | 185us     | 3890us  | 129us      | 2144us     |

|                                              | EntityX   | EnTT   | Ginseng   | Flecs   | pico_ecs   | gaia-ecs   |
|:---------------------------------------------|:----------|:-------|:----------|:--------|:-----------|:-----------|
| Remove and Add a Component in  ~65K entities | 0ms       | 1ms    | 0ms       | 15ms    | 0ms        | 8ms        |
| Remove and Add a Component in  262K entities | 4ms       | 6ms    | 3ms       | 62ms    | 2ms        | 34ms       |
| Remove and Add a Component in   ~1M entities | 16ms      | 26ms   | 12ms      | 250ms   | 8ms        | 137ms      |
| Remove and Add a Component in   ~2M entities | 32ms      | 53ms   | 23ms      | 527ms   | 16ms       | 277ms      |



**Note:**
* Remove and add `PositionComponent`



### Update systems (for-each entities in 2 systems)


  Cost per entity                         |  Cost of all entities
:-------------------------------------------:|:------------------------------------------------------:
  ![SystemsUpdate Plot](img/SystemsUpdate.svg)  |  ![SystemsUpdate Line Plot](img/LineSystemsUpdate.svg)  


_Tables shows total cost. lower is faster._

|                                      | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:-------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Update     1 entities with 2 systems | 39ns      | 27ns   | 13ns      | 68ns       | 1287ns  | 22ns       | 100ns      |
| Update     4 entities with 2 systems | 93ns      | 55ns   | 34ns      | 90ns       | 1262ns  | 41ns       | 91ns       |
| Update     8 entities with 2 systems | 166ns     | 99ns   | 59ns      | 94ns       | 1279ns  | 71ns       | 107ns      |
| Update    16 entities with 2 systems | 314ns     | 161ns  | 109ns     | 122ns      | 1309ns  | 147ns      | 133ns      |
| Update    32 entities with 2 systems | 601ns     | 294ns  | 218ns     | 173ns      | 1358ns  | 257ns      | 188ns      |
| Update    64 entities with 2 systems | 1171ns    | 630ns  | 429ns     | 284ns      | 1467ns  | 490ns      | 289ns      |

|                                      | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:-------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Update   256 entities with 2 systems | 5us       | 2us    | 1us       | 0us        | 2us     | 1us        | 0us        |
| Update   ~1K entities with 2 systems | 18us      | 8us    | 6us       | 3us        | 4us     | 7us        | 3us        |
| Update   ~4K entities with 2 systems | 82us      | 34us   | 29us      | 13us       | 14us    | 30us       | 15us       |
| Update  ~16K entities with 2 systems | 315us     | 140us  | 127us     | 56us       | 56us    | 165us      | 65us       |

|                                      | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:-------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Update  ~65K entities with 2 systems | 1ms       | 0ms    | 0ms       | 0ms        | 0ms     | 0ms        | 0ms        |
| Update  262K entities with 2 systems | 5ms       | 2ms    | 2ms       | 1ms        | 3ms     | 2ms        | 3ms        |
| Update   ~1M entities with 2 systems | 21ms      | 12ms   | 10ms      | 8ms        | 12ms    | 12ms       | 12ms       |
| Update   ~2M entities with 2 systems | 44ms      | 25ms   | 21ms      | 15ms       | 25ms    | 22ms       | 25ms       |



**Note:**
* Systems used
    1. `MovementSystem`
    2. `DataSystem`


### Update systems (for-each entities (with mixed components) in 2 systems)


  Cost per entity                         |  Cost of all entities
:-------------------------------------------:|:------------------------------------------------------:
  ![SystemsUpdateMixedEntities Plot](img/SystemsUpdateMixedEntities.svg)  |  ![SystemsUpdateMixedEntities Line Plot](img/LineSystemsUpdateMixedEntities.svg)  


_Tables shows total cost. lower is faster._

|                                      | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:-------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Update     1 entities with 2 systems | 29ns      | 16ns   | 7ns       | 36ns       | 577ns   | 16ns       | 53ns       |
| Update     4 entities with 2 systems | 75ns      | 45ns   | 28ns      | 126ns      | 1313ns  | 34ns       | 113ns      |
| Update     8 entities with 2 systems | 137ns     | 87ns   | 51ns      | 151ns      | 1475ns  | 55ns       | 133ns      |
| Update    16 entities with 2 systems | 266ns     | 145ns  | 94ns      | 190ns      | 1389ns  | 95ns       | 147ns      |
| Update    32 entities with 2 systems | 534ns     | 278ns  | 198ns     | 242ns      | 1467ns  | 194ns      | 191ns      |
| Update    64 entities with 2 systems | 1080ns    | 555ns  | 404ns     | 357ns      | 1583ns  | 353ns      | 300ns      |

|                                      | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:-------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Update   256 entities with 2 systems | 4us       | 2us    | 1us       | 1us        | 2us     | 1us        | 1us        |
| Update   ~1K entities with 2 systems | 18us      | 8us    | 7us       | 3us        | 4us     | 7us        | 4us        |
| Update   ~4K entities with 2 systems | 82us      | 32us   | 28us      | 14us       | 15us    | 41us       | 15us       |
| Update  ~16K entities with 2 systems | 301us     | 145us  | 132us     | 56us       | 56us    | 165us      | 67us       |

|                                      | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:-------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Update  ~65K entities with 2 systems | 1ms       | 0ms    | 0ms       | 0ms        | 0ms     | 0ms        | 0ms        |
| Update  262K entities with 2 systems | 5ms       | 3ms    | 2ms       | 1ms        | 2ms     | 2ms        | 3ms        |
| Update   ~1M entities with 2 systems | 22ms      | 13ms   | 11ms      | 7ms        | 13ms    | 11ms       | 13ms       |
| Update   ~2M entities with 2 systems | 44ms      | 30ms   | 22ms      | 15ms       | 25ms    | 24ms       | 25ms       |


**Note:**
* Systems used
    1. `MovementSystem`
    2. `DataSystem`
* Not every entity has all three components, some got removed


### Update systems (for-each entities in 7 systems)


  Cost per entity                         |  Cost of all entities
:-------------------------------------------:|:------------------------------------------------------:
  ![ComplexSystemsUpdate Plot](img/ComplexSystemsUpdate.svg)  |  ![ComplexSystemsUpdate Line Plot](img/LineComplexSystemsUpdate.svg)  


_Tables shows total cost. lower is faster._

|                                      | EnTT   | EnTT (runtime)   | EnTT (group)   | EnTT (stable)         | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   | gaia-ecs (SoA)   |
|:-------------------------------------|:-------|:-----------------|:---------------|:----------------------|:----------|:-----------|:--------|:-----------|:-----------|:-----------------|
| Update     1 entities with 7 systems | 138ns  | 174ns            | 93ns           | 121ns                 | 51ns      | 224ns      | 2775ns  | 70ns       | 279ns      | 275ns            |
| Update     4 entities with 7 systems | 293ns  | 525ns            | 174ns          | 239ns                 | 117ns     | 274ns      | 2584ns  | 157ns      | 335ns      | 316ns            |
| Update     8 entities with 7 systems | 479ns  | 1016ns           | 272ns          | 351ns                 | 229ns     | 357ns      | 2626ns  | 288ns      | 384ns      | 384ns            |
| Update    16 entities with 7 systems | 755ns  | 1963ns           | 415ns          | 560ns                 | 399ns     | 394ns      | 2630ns  | 516ns      | 490ns      | 498ns            |
| Update    32 entities with 7 systems | 1357ns | 3664ns           | 775ns          | 1050ns                | 750ns     | 540ns      | 2777ns  | 947ns      | 627ns      | 611ns            |
| Update    64 entities with 7 systems | 2620ns | 7461ns           | 1346ns         | 2214ns                | 1431ns    | 860ns      | 3079ns  | 1808ns     | 974ns      | 932ns            |

|                                      | EnTT   | EnTT (runtime)   | EnTT (group)   | EnTT (stable)         | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   | gaia-ecs (SoA)   |
|:-------------------------------------|:-------|:-----------------|:---------------|:----------------------|:----------|:-----------|:--------|:-----------|:-----------|:-----------------|
| Update   256 entities with 7 systems | 10us   | 28us             | 5us            | 9us                   | 5us       | 2us        | 4us     | 6us        | 3us        | 3us              |
| Update   ~1K entities with 7 systems | 52us   | 100us            | 27us           | 39us                  | 23us      | 8us        | 11us    | 27us       | 14us       | 14us             |
| Update   ~4K entities with 7 systems | 202us  | 493us            | 132us          | 172us                 | 102us     | 37us       | 39us    | 106us      | 72us       | 73us             |
| Update  ~16K entities with 7 systems | 827us  | 1947us           | 592us          | 651us                 | 445us     | 158us      | 189us   | 469us      | 362us      | 347us            |

|                                      | EnTT   | EnTT (runtime)   | EnTT (group)   | EnTT (stable)         | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   | gaia-ecs (SoA)   |
|:-------------------------------------|:-------|:-----------------|:---------------|:----------------------|:----------|:-----------|:--------|:-----------|:-----------|:-----------------|
| Update  ~65K entities with 7 systems | 3ms    | 7ms              | 2ms            | 2ms                   | 1ms       | 0ms        | 0ms     | 1ms        | 1ms        | 1ms              |
| Update  262K entities with 7 systems | 16ms   | 32ms             | 12ms           | 11ms                  | 8ms       | 4ms        | 6ms     | 7ms        | 10ms       | 12ms             |
| Update   ~1M entities with 7 systems | 57ms   | 122ms            | 51ms           | 45ms                  | 35ms      | 21ms       | 25ms    | 31ms       | 43ms       | 43ms             |
| Update   ~2M entities with 7 systems | 112ms  | 237ms            | 127ms          | 89ms                  | 70ms      | 42ms       | 52ms    | 65ms       | 84ms       | 85ms             |



**Note:**
* Systems used
    1. `MovementSystem`
    2. `DataSystem`
    3. `MoreComplexSystem`
    4. `HealthSystem`
    5. `DamageSystem`
    6. `SpriteSystem`
    7. `RenderSystem`
* \*   EnTT iterate components via [views](https://github.com/skypjack/entt/wiki/Crash-Course:-entity-component-system#views=)
* \**  EnTT iterate components via [runtime views](https://github.com/skypjack/entt/wiki/Crash-Course:-entity-component-system#runtime-views=)
* \*** EnTT iterate components via [groups](https://github.com/skypjack/entt/wiki/Crash-Course:-entity-component-system#groups=):
   1. `DataSystem`: No Group, use `registry.view<DataComponent>`. _(Can't group a single component)_
   2. `MovementSystem`: Partial-owning group, `registry.group<PositionComponent>(entt::get<const VelocityComponent>)`
   3. `MoreComplexSystem`: Full-owning group, `registry.group<PositionComponent, VelocityComponent, DataComponent>()`
* \**** EnTT iterate components via view and uses a [stable component](https://github.com/skypjack/entt/wiki/Crash-Course:-entity-component-system#pointer-stability=) (`StablePositionComponent`)
* \***** gaia-ecs (SoA) iterate via [SoA Layout](https://github.com/richardbiely/gaia-ecs?tab=readme-ov-file#data-layouts) using an `Position`- and `Velocity`-SoA-component



### Update systems (for-each entities (with mixed components) in 7 systems)


  Cost per entity                         |  Cost of all entities
:-------------------------------------------:|:------------------------------------------------------:
  ![ComplexSystemsUpdateMixedEntities Plot](img/ComplexSystemsUpdateMixedEntities.svg)  |  ![ComplexSystemsUpdateMixedEntities Line Plot](img/LineComplexSystemsUpdateMixedEntities.svg)  


_Tables shows total cost. lower is faster._

|                                      | EnTT   | EnTT (runtime)   | EnTT (group)   | EnTT (stable)         | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   | gaia-ecs (SoA)   |
|:-------------------------------------|:-------|:-----------------|:---------------|:----------------------|:----------|:-----------|:--------|:-----------|:-----------|:-----------------|
| Update     1 entities with 7 Systems | 123ns  | 130ns            | 89ns           | 131ns                 | 48ns      | 221ns      | 1741ns  | 67ns       | 227ns      | 225ns            |
| Update     4 entities with 7 Systems | 223ns  | 364ns            | 138ns          | 169ns                 | 106ns     | 475ns      | 2727ns  | 125ns      | 416ns      | 394ns            |
| Update     8 entities with 7 Systems | 310ns  | 684ns            | 203ns          | 237ns                 | 173ns     | 534ns      | 2868ns  | 209ns      | 454ns      | 454ns            |
| Update    16 entities with 7 Systems | 348ns  | 838ns            | 207ns          | 182ns                 | 205ns     | 425ns      | 2663ns  | 209ns      | 355ns      | 332ns            |
| Update    32 entities with 7 Systems | 574ns  | 1622ns           | 304ns          | 237ns                 | 368ns     | 520ns      | 2810ns  | 370ns      | 419ns      | 443ns            |
| Update    64 entities with 7 Systems | 1038ns | 3052ns           | 501ns          | 353ns                 | 728ns     | 661ns      | 2960ns  | 652ns      | 560ns      | 558ns            |

|                                      | EnTT   | EnTT (runtime)   | EnTT (group)   | EnTT (stable)         | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   | gaia-ecs (SoA)   |
|:-------------------------------------|:-------|:-----------------|:---------------|:----------------------|:----------|:-----------|:--------|:-----------|:-----------|:-----------------|
| Update   256 entities with 7 Systems | 7us    | 21us             | 4us            | 4us                   | 4us       | 2us        | 4us     | 5us        | 2us        | 2us              |
| Update   ~1K entities with 7 Systems | 31us   | 91us             | 18us           | 21us                  | 16us      | 7us        | 10us    | 19us       | 9us        | 10us             |
| Update   ~4K entities with 7 Systems | 138us  | 374us            | 89us           | 103us                 | 68us      | 27us       | 30us    | 91us       | 45us       | 45us             |
| Update  ~16K entities with 7 Systems | 569us  | 1455us           | 403us          | 365us                 | 321us     | 113us      | 120us   | 366us      | 219us      | 211us            |

|                                      | EnTT   | EnTT (runtime)   | EnTT (group)   | EnTT (stable)         | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   | gaia-ecs (SoA)   |
|:-------------------------------------|:-------|:-----------------|:---------------|:----------------------|:----------|:-----------|:--------|:-----------|:-----------|:-----------------|
| Update  ~65K entities with 7 Systems | 2ms    | 5ms              | 1ms            | 1ms                   | 1ms       | 0ms        | 0ms     | 1ms        | 1ms        | 1ms              |
| Update  262K entities with 7 Systems | 12ms   | 24ms             | 8ms            | 6ms                   | 6ms       | 3ms        | 3ms     | 6ms        | 7ms        | 7ms              |
| Update   ~1M entities with 7 Systems | 40ms   | 102ms            | 35ms           | 26ms                  | 27ms      | 16ms       | 19ms    | 25ms       | 31ms       | 32ms             |
| Update   ~2M entities with 7 Systems | 85ms   | 184ms            | 87ms           | 51ms                  | 55ms      | 33ms       | 42ms    | 53ms       | 62ms       | 69ms             |



**Note:**
* Systems used
    1. `MovementSystem`
    2. `DataSystem`
    3. `MoreComplexSystem`
    4. `HealthSystem`
    5. `DamageSystem`
    6. `SpriteSystem`
    7. `RenderSystem`
* Not every entity has all three components, some got removed
* \*   EnTT iterate components via [views](https://github.com/skypjack/entt/wiki/Crash-Course:-entity-component-system#views=)
* \**  EnTT iterate components via [runtime views](https://github.com/skypjack/entt/wiki/Crash-Course:-entity-component-system#runtime-views=)
* \*** EnTT iterate components via [groups](https://github.com/skypjack/entt/wiki/Crash-Course:-entity-component-system#groups=):
    1. `DataSystem`: No Group, use `registry.view<DataComponent>`. _(Can't group a single component)_
    2. `MovementSystem`: Partial-owning group, `registry.group<PositionComponent>(entt::get<const VelocityComponent>)`
    3. `MoreComplexSystem`: Full-owning group, `registry.group<PositionComponent, VelocityComponent, DataComponent>()`
* \**** EnTT iterate components via view and uses a [stable component](https://github.com/skypjack/entt/wiki/Crash-Course:-entity-component-system#pointer-stability=) (`StablePositionComponent`)
* \***** gaia-ecs (SoA) iterate via [SoA Layout](https://github.com/richardbiely/gaia-ecs?tab=readme-ov-file#data-layouts) using an `Position`- und `Velocity`-SoA-component


## Contributing

If you have any improvements to the ECS-examples for any of the frameworks,
feel free to make a pull request or open an issue.
The example(s) for each framework can be found in [`src/`](src/), and benchmarks are located in [`benchmarks/benchmarks/`](benchmarks/benchmarks/) for more details.

Additionally, you can write tests for the framework example and add some metadata to the [plot.config.json](plot.config.json) file.
Any contributions are greatly appreciated!

_TODO: make more detailed "how to add framework"_

Read [CONTRIBUTING.md](CONTRIBUTING) for more details.

## Run Benchmarks

### Using [Taskfile](https://taskfile.dev/installation/)

0. Install [Taskfile](https://taskfile.dev/installation/)
1. Run Build: `task build`
2. Run (All) Benchmarks: `task benchmark`
3. Plot Graphs: `task plot:all`

Or run `task generate`

You can now find the benchmark-results in [`reports/`](reports/).

_You need python (>=3.8.0) and some [dependencies](scripts/gen-benchmark-report/requirements.txt) to run [gen-benchmark-report](scripts/gen-benchmark-report) (plotting), install [pipx](https://pipx.pypa.io/stable/installation/) and [poetry](https://python-poetry.org/docs/#installing-with-pipx)._

Then install the dependencies for the script:
```bash
cd ./scripts/gen-benchmark-report && poetry install
```

Or run the script directly:
```bash
task plot:all
```

#### Generate README

```bash
task generate:readme
```


### ~~Step-by-Step~~

1. Configure and build benchmarks, see [Building Details](doc/README_building.md):
   1. `cmake -S . -B ./build`
   2. `cmake --build ./build`
2. Run benchmark(s), with [`run-benchmarks.sh`](run-benchmarks.sh) or each:
   * `./build/benchmark/benchmarks/entt/ecs-benchmark-entt` _(console output)_ _(optional)_
   * `./build/benchmark/benchmarks/entt/ecs-benchmark-entt --benchmark_format=json > ./reports/entt.json` _(write json report)_
3. Plot Reports, after generating json reports, see [`plot-results.sh`](plot-results.sh):
   1. `pipx run --spec ./scripts/gen-benchmark-report gen-benchmark-report -i ./info.json gen-plot ./reports/entityx.json ./reports/entt.json ./reports/ginseng.json ./reports/mustache.json ./reports/openecs.json ./reports/flecs.json` _(generate graphs)_
   2. `pipx run --spec ./scripts/gen-benchmark-report gen-benchmark-report -i ./info.json gen-results-md ./reports/entityx.json ./reports/entt.json ./reports/ginseng.json ./reports/mustache.json ./reports/openecs.json ./reports/flecs.json` _(generate full report)_


### Run a single benchmark

```bash
cmake -G Ninja -S . -B build
cmake --build build --target ecs-benchmark-entt -j 4
./build/benchmark/benchmarks/entt/ecs-benchmark-entt
```

You can use `-DCMAKE_BUILD_TYPE=Debug` to enable Sanitizers.


## Links and More

- [Dependency Setup](doc/README_dependencies.md)
- [Building Details](doc/README_building.md)
- Project Template, mix of: [starter_template](https://github.com/cpp-best-practices/gui_starter_template) and [ModernCppStarter](https://github.com/TheLartians/ModernCppStarter)
  - [Forked cpp_vcpkg_project](https://github.com/abeimler/cpp_vcpkg_project)
- [Google benchmark](https://github.com/google/benchmark)
- https://github.com/SanderMertens/ecs-faq
- https://github.com/jslee02/awesome-entity-component-system


### Candidates

#### EntityX by @alecthomas 

> Entity Component Systems (ECS) are a form of decomposition that completely decouples entity logic and data from the entity "objects" themselves. The Evolve your Hierarchy article provides a solid overview of EC systems and why you should use them.

Version: 1.1.2 (Apr 2023)

#### EnTT by @skypjack 

> EnTT is a header-only, tiny and easy to use library for game programming and much more written in modern C++.

Version: v3.13.2

#### Ginseng by @apples 

> Ginseng is an entity-component-system (ECS) library designed for use in games.
> 
> The main advantage over similar libraries is that the component types do not need to be listed or registered. Component types are detected dynamically.
> 
> Any function-like object can be used as a system. The function's parameters are used to determine the required components.

Version: 1.1 (Dec 2021)

#### mustache by @kirillochnev 

> A fast, modern C++ Entity Component System

Version: 0.2 (Feb 2024)

#### OpenEcs by @Gronis 

> Open Ecs is an Entity Component System that uses metaprogramming, cache coherency, and other useful tricks to maximize performance and configurability. It is written in c++11 without further dependencies.

Version: 0.1.101 (Apr 2017)

#### Flecs by @SanderMertens 

> Flecs is a fast and lightweight Entity Component System that lets you build games and simulations with millions of entities.

Version: v4.0.1

#### pico_ecs by @empyreanx 

> A collection of cross-platform single header libraries written in C. Pure and simple ECS.

Version: 2.3 (Sep 2023)

#### gaia-ecs by @richardbiely 

> Gaia-ECS is a fast and easy-to-use ECS framework.

Version: v0.8.6

