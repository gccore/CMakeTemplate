#include <benchmark/benchmark.h>

#include <string>

namespace {
void BenchmarkStringCreation(benchmark::State &state) {
  while (state.KeepRunning()) {
    benchmark::DoNotOptimize(std::string(100, 'A'));
  }
}
} // namespace

BENCHMARK(BenchmarkStringCreation);
BENCHMARK_MAIN();
