#include "generator/fractalgen.h"
#include <benchmark/benchmark.h>

static void SierpinskiArgs(benchmark::internal::Benchmark* b)
{
  std::vector<int> runs {2, 4, 8, 10, 12, 14};
  for (auto& level: runs)
      b->Args({level});
}

static void BM_Sierpinski(benchmark::State& state)
{
  for (auto _ : state)
    generateMesh("/home/lukas/documents/coding/python/blender-fractals/examples/standard/sierpinski.txt", state.range(0));
}
BENCHMARK(BM_Sierpinski)->Apply(SierpinskiArgs)->Unit(benchmark::kMicrosecond);


static void BM_Menge(benchmark::State& state)
{
  for (auto _ : state)
    generateMesh("/home/lukas/documents/coding/python/blender-fractals/examples/3d/menge.txt", state.range(0));
}

BENCHMARK(BM_Menge)->Args({1})->Args({2})->Args({3})->Unit(benchmark::kMicrosecond);
