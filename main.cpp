#include <benchmark/benchmark.h>
#include <memory>

class polymorphic_base
{
    protected:
    volatile int i_{0};

    public:
    virtual ~polymorphic_base() = default;
};

class polymorphic_b : public polymorphic_base
{
    public:
    virtual ~polymorphic_b() = default;
};

__attribute__ ((optnone))
polymorphic_b* baseline(polymorphic_b* o)
{
    return o;
}

__attribute__ ((optnone))
polymorphic_b* cast_dynamic(polymorphic_base* o)
{
    return dynamic_cast<polymorphic_b*>(o);
}

__attribute__ ((optnone))
polymorphic_b* cast_static(polymorphic_base* o)
{
    return static_cast<polymorphic_b*>(o);
}

__attribute__ ((optnone))
polymorphic_b* cast_reinterpret(polymorphic_base* o)
{
    return reinterpret_cast<polymorphic_b*>(o);
}

__attribute__ ((optnone))
polymorphic_b* cast_const(const polymorphic_b* o)
{
    return const_cast<polymorphic_b*>(o);
}

__attribute__ ((optnone))
polymorphic_b* cast_c(const polymorphic_base* o)
{
    return (polymorphic_b*) o;
}

static void bm_baseline_no_cast(benchmark::State& state)
{
    polymorphic_b o;
    polymorphic_b* o2;
    for (auto _ : state)
    {
        o2 = baseline(&o);
    }
}

static void bm_cast_dynamic(benchmark::State& state)
{
    polymorphic_b o;
    polymorphic_b* o2;
    for (auto _ : state)
    {
        o2 = cast_dynamic(&o);
    }
}

static void bm_cast_static(benchmark::State& state)
{
    polymorphic_b o;
    polymorphic_b* o2;
    for (auto _ : state)
    {
        o2 = cast_static(&o);
    }
}

static void bm_cast_reinterpret(benchmark::State& state)
{
    polymorphic_b o;
    polymorphic_b* o2;
    for (auto _ : state)
    {
        o2 = cast_reinterpret(&o);
    }
}

static void bm_cast_const(benchmark::State& state)
{
    polymorphic_b o;
    polymorphic_b* o2;
    for (auto _ : state)
    {
        o2 = cast_const(&o);
    }
}

static void bm_cast_c(benchmark::State& state)
{
    polymorphic_b o;
    polymorphic_b* o2;
    for (auto _ : state)
    {
        o2 = cast_c(&o);
    }
}

// Register the function as a benchmark
BENCHMARK(bm_baseline_no_cast);
BENCHMARK(bm_cast_dynamic);
BENCHMARK(bm_cast_static);
BENCHMARK(bm_cast_reinterpret);
BENCHMARK(bm_cast_const);
BENCHMARK(bm_cast_c);

// Run the benchmark
BENCHMARK_MAIN();