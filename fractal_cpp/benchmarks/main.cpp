#include "generator/fractalgen.h"
#include <benchmark/benchmark.h>

static void BM_Sierpinsky(benchmark::State& state)
{
  for (auto _ : state)
    auto x = generateMesh("/home/lukas/documents/coding/python/blender-fractals/examples/standard/sierpinski.txt", state.range(0));
}
BENCHMARK(BM_Sierpinsky)->Args({4})->Args({8})->Args({10})->Args({11})->Args({12})->Args({14})->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();
