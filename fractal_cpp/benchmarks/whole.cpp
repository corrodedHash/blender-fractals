#include "generator/fractalgen.h"
#include <benchmark/benchmark.h>
#include "config.h"

static void BM_Sierpinski(benchmark::State& state)
{
  for (auto _ : state) {
    frac::generateFractal(grammarpath + "/standard/sierpinski.txt", state.range(0));
  }
}
BENCHMARK(BM_Sierpinski)->Range(2, 14)->Unit(benchmark::kMicrosecond);

static void BM_Menge(benchmark::State& state)
{
  for (auto _ : state) {
    frac::generateFractal(grammarpath + "/3d/menge.txt", state.range(0));
  }
}

BENCHMARK(BM_Menge)->Args({ 1 })->Args({ 2 })->Args({ 3 })->Unit(benchmark::kMicrosecond);

static void BM_Dragon(benchmark::State& state)
{
  for (auto _ : state) {
    frac::generateFractal(grammarpath + "/standard/dragon.txt", state.range(0));
  }
}

BENCHMARK(BM_Dragon)->Range(2, 14)->Unit(benchmark::kMicrosecond);
