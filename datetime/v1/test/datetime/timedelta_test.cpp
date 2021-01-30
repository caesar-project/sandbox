#include <caesar/datetime.hpp>

#include <doctest/doctest.h>

namespace cs = caesar;

struct TimeDeltaTest {
    template<typename T>
    using Days = std::chrono::duration<T, std::ratio<86400>>;

    template<typename T>
    using Hours = std::chrono::duration<T, std::ratio<3600>>;

    template<typename T>
    using Minutes = std::chrono::duration<T, std::ratio<60>>;

    template<typename T>
    using Seconds = std::chrono::duration<T>;

    template<typename T>
    using Milliseconds = std::chrono::duration<T, std::milli>;

    template<typename T>
    using Microseconds = std::chrono::duration<T, std::micro>;

    template<typename T>
    using Nanoseconds = std::chrono::duration<T, std::nano>;

    template<typename T>
    using Picoseconds = std::chrono::duration<T, std::pico>;

    template<typename T>
    using Femtoseconds = std::chrono::duration<T, std::femto>;

    // Approximately one trillion years, in seconds
    constexpr static double trillion_years_sec = 1e12 * 365 * 24 * 60 * 60;

    // TimeDelta representing one picosecond
    constexpr static auto one_picosec = cs::TimeDelta::picoseconds(1);
};

TEST_CASE_FIXTURE(TimeDeltaTest, "datetime.timedelta.default_construct")
{
    const auto dt = cs::TimeDelta();
    CHECK_EQ(dt.count(), 0);
}

TEST_CASE_FIXTURE(TimeDeltaTest, "datetime.timedelta.from_chrono_duration")
{
    SUBCASE("integer_no_truncation")
    {
        const auto us = Microseconds<long>(123456);
        const auto dt = cs::TimeDelta(us);

        CHECK_EQ(dt.count(), us.count() * 1'000'000);
    }

    SUBCASE("integer_with_truncation")
    {
        const auto fs = Femtoseconds<int>(999);

        const auto dt1 = cs::TimeDelta(fs);
        CHECK_EQ(dt1.count(), 0);

        const auto dt2 = cs::TimeDelta(-fs);
        CHECK_EQ(dt2.count(), 0);
    }

    SUBCASE("floating_point")
    {
        const auto s = Seconds<double>(123.456);
        const auto dt = cs::TimeDelta(s);
        CHECK_EQ(dt.total_seconds(), doctest::Approx(s.count()));
    }
}

TEST_CASE_FIXTURE(TimeDeltaTest, "datetime.timedelta.to_chrono_duration")
{
    SUBCASE("integer")
    {
        const auto us = Microseconds<long>(123456);
        const auto dt = cs::TimeDelta(us);
        CHECK_EQ(Microseconds<long>(dt), us);
    }

    SUBCASE("floating_point")
    {
        const auto s = Seconds<double>(123.456);
        const auto dt = cs::TimeDelta(s);
        CHECK_EQ(Seconds<double>(dt).count(), doctest::Approx(s.count()));
    }
}

TEST_CASE_FIXTURE(TimeDeltaTest, "datetime.timedelta.min")
{
    const auto dt = cs::TimeDelta::min();
    CHECK_LT(dt.total_seconds(), -trillion_years_sec);
}

TEST_CASE_FIXTURE(TimeDeltaTest, "datetime.timedelta.max")
{
    const auto dt = cs::TimeDelta::max();
    CHECK_GT(dt.total_seconds(), trillion_years_sec);
}

TEST_CASE_FIXTURE(TimeDeltaTest, "datetime.timedelta.resolution")
{
    const auto dt = cs::TimeDelta::resolution();
    CHECK_EQ(dt, one_picosec);
}

TEST_CASE_FIXTURE(TimeDeltaTest, "datetime.timedelta.days")
{
    SUBCASE("integer")
    {
        const auto d = Days<int>(123);
        const auto dt1 = cs::TimeDelta(d);
        const auto dt2 = cs::TimeDelta::days(123);

        CHECK_EQ(dt1, dt2);
    }

    SUBCASE("floating_point")
    {
        const auto d = Days<float>(123.456);
        const auto dt1 = cs::TimeDelta(d);
        const auto dt2 = cs::TimeDelta::days(123.456);

        CHECK_EQ(dt2.total_seconds(), doctest::Approx(dt1.total_seconds()));
    }
}

TEST_CASE_FIXTURE(TimeDeltaTest, "datetime.timedelta.hours")
{
    SUBCASE("integer")
    {
        const auto h = Hours<int>(123);
        const auto dt1 = cs::TimeDelta(h);
        const auto dt2 = cs::TimeDelta::hours(123);

        CHECK_EQ(dt1, dt2);
    }

    SUBCASE("floating_point")
    {
        const auto h = Hours<float>(123.456);
        const auto dt1 = cs::TimeDelta(h);
        const auto dt2 = cs::TimeDelta::hours(123.456);

        CHECK_EQ(dt2.total_seconds(), doctest::Approx(dt1.total_seconds()));
    }
}

TEST_CASE_FIXTURE(TimeDeltaTest, "datetime.timedelta.minutes")
{
    SUBCASE("integer")
    {
        const auto m = Minutes<int>(123);
        const auto dt1 = cs::TimeDelta(m);
        const auto dt2 = cs::TimeDelta::minutes(123);

        CHECK_EQ(dt1, dt2);
    }

    SUBCASE("floating_point")
    {
        const auto m = Minutes<float>(123.456);
        const auto dt1 = cs::TimeDelta(m);
        const auto dt2 = cs::TimeDelta::minutes(123.456);

        CHECK_EQ(dt2.total_seconds(), doctest::Approx(dt1.total_seconds()));
    }
}

TEST_CASE_FIXTURE(TimeDeltaTest, "datetime.timedelta.seconds")
{
    SUBCASE("integer")
    {
        const auto s = Seconds<int>(123);
        const auto dt1 = cs::TimeDelta(s);
        const auto dt2 = cs::TimeDelta::seconds(123);

        CHECK_EQ(dt1, dt2);
    }

    SUBCASE("floating_point")
    {
        const auto s = Seconds<float>(123.456);
        const auto dt1 = cs::TimeDelta(s);
        const auto dt2 = cs::TimeDelta::seconds(123.456);

        CHECK_EQ(dt2.total_seconds(), doctest::Approx(dt1.total_seconds()));
    }
}

TEST_CASE_FIXTURE(TimeDeltaTest, "datetime.timedelta.milliseconds")
{
    SUBCASE("integer")
    {
        const auto ms = Milliseconds<int>(123);
        const auto dt1 = cs::TimeDelta(ms);
        const auto dt2 = cs::TimeDelta::milliseconds(123);

        CHECK_EQ(dt1, dt2);
    }

    SUBCASE("floating_point")
    {
        const auto ms = Milliseconds<float>(123.456);
        const auto dt1 = cs::TimeDelta(ms);
        const auto dt2 = cs::TimeDelta::milliseconds(123.456);

        CHECK_EQ(dt2.total_seconds(), doctest::Approx(dt1.total_seconds()));
    }
}

TEST_CASE_FIXTURE(TimeDeltaTest, "datetime.timedelta.microseconds")
{
    SUBCASE("integer")
    {
        const auto us = Microseconds<int>(123);
        const auto dt1 = cs::TimeDelta(us);
        const auto dt2 = cs::TimeDelta::microseconds(123);

        CHECK_EQ(dt1, dt2);
    }

    SUBCASE("floating_point")
    {
        const auto us = Microseconds<float>(123.456);
        const auto dt1 = cs::TimeDelta(us);
        const auto dt2 = cs::TimeDelta::microseconds(123.456);

        CHECK_EQ(dt2.total_seconds(), doctest::Approx(dt1.total_seconds()));
    }
}

TEST_CASE_FIXTURE(TimeDeltaTest, "datetime.timedelta.nanoseconds")
{
    SUBCASE("integer")
    {
        const auto ns = Nanoseconds<int>(123);
        const auto dt1 = cs::TimeDelta(ns);
        const auto dt2 = cs::TimeDelta::nanoseconds(123);

        CHECK_EQ(dt1, dt2);
    }

    SUBCASE("floating_point")
    {
        const auto ns = Nanoseconds<float>(123.456);
        const auto dt1 = cs::TimeDelta(ns);
        const auto dt2 = cs::TimeDelta::nanoseconds(123.456);

        CHECK_EQ(dt2.total_seconds(), doctest::Approx(dt1.total_seconds()));
    }
}

TEST_CASE_FIXTURE(TimeDeltaTest, "datetime.timedelta.picoseconds")
{
    SUBCASE("integer")
    {
        const auto ps = Picoseconds<int>(123);
        const auto dt1 = cs::TimeDelta(ps);
        const auto dt2 = cs::TimeDelta::picoseconds(123);

        CHECK_EQ(dt1, dt2);
    }

    SUBCASE("floating_point")
    {
        const auto dt = cs::TimeDelta::picoseconds(123.456);
        CHECK_EQ(dt.count(), 123);
    }
}

TEST_CASE_FIXTURE(TimeDeltaTest, "datetime.timedelta.unary_plus")
{
    const auto ms = Milliseconds<long>(123456);

    const auto dt1 = cs::TimeDelta(ms);
    const auto dt2 = cs::TimeDelta(-ms);

    CHECK_EQ(+dt1, dt1);
    CHECK_EQ(+dt2, dt2);
}

TEST_CASE_FIXTURE(TimeDeltaTest, "datetime.timedelta.unary_minus")
{
    const auto ms = Milliseconds<long>(123456);

    const auto dt1 = cs::TimeDelta(ms);
    const auto dt2 = cs::TimeDelta(-ms);

    CHECK_EQ(-dt1, dt2);
    CHECK_EQ(-dt2, dt1);
}

TEST_CASE_FIXTURE(TimeDeltaTest, "datetime.timedelta.increment")
{
    cs::TimeDelta dt;

    SUBCASE("prefix")
    {
        CHECK_EQ(++dt, one_picosec);
        CHECK_EQ(dt, one_picosec);
    }

    SUBCASE("postfix")
    {
        CHECK_EQ(dt++, cs::TimeDelta());
        CHECK_EQ(dt, one_picosec);
    }
}

TEST_CASE_FIXTURE(TimeDeltaTest, "datetime.timedelta.decrement")
{
    cs::TimeDelta dt;

    SUBCASE("prefix")
    {
        CHECK_EQ(--dt, -one_picosec);
        CHECK_EQ(dt, -one_picosec);
    }

    SUBCASE("postfix")
    {
        CHECK_EQ(dt--, cs::TimeDelta());
        CHECK_EQ(dt, -one_picosec);
    }
}

TEST_CASE_FIXTURE(TimeDeltaTest, "datetime.timedelta.add")
{
    const auto a = Milliseconds<long long>(123456789);
    const auto b = Days<long long>(12) + Minutes<long long>(34) +
                   Seconds<long long>(56) + Microseconds<long long>(78) +
                   Picoseconds<long long>(90);

    const auto dt1 = cs::TimeDelta(a);
    const auto dt2 = cs::TimeDelta(b);
    const auto sum = cs::TimeDelta(a + b);

    // Compound assignment
    auto tmp = dt1;
    tmp += dt2;
    CHECK_EQ(tmp, sum);

    // Binary operator is commutative.
    CHECK_EQ(dt1 + dt2, sum);
    CHECK_EQ(dt2 + dt1, sum);

    // Adding zero returns identity.
    CHECK_EQ(dt1 + cs::TimeDelta(), dt1);
}

TEST_CASE_FIXTURE(TimeDeltaTest, "datetime.timedelta.subtract")
{
    const auto a = Milliseconds<long long>(123456789);
    const auto b = Days<long long>(12) + Minutes<long long>(34) +
                   Seconds<long long>(56) + Microseconds<long long>(78) +
                   Picoseconds<long long>(90);

    const auto dt1 = cs::TimeDelta(a);
    const auto dt2 = cs::TimeDelta(b);
    const auto diff = cs::TimeDelta(b - a);

    // Compound assignment
    auto tmp = dt2;
    tmp -= dt1;
    CHECK_EQ(tmp, diff);

    // Binary operator
    CHECK_EQ(dt2 - dt1, diff);

    // Adding zero returns identity.
    CHECK_EQ(dt1 - cs::TimeDelta(), dt1);
}

TEST_CASE_FIXTURE(TimeDeltaTest, "datetime.timedelta.multiply")
{
    const auto a = Days<long long>(12) + Minutes<long long>(34) +
                   Seconds<long long>(56) + Microseconds<long long>(78) +
                   Picoseconds<long long>(90);

    const auto dt = cs::TimeDelta(a);
    const int k = 4;
    const auto prod = cs::TimeDelta(k * a);

    // Compound assignment
    auto tmp = dt;
    tmp *= k;
    CHECK_EQ(tmp, prod);

    // Binary operator is commutative.
    CHECK_EQ(k * dt, prod);
    CHECK_EQ(dt * k, prod);

    // Multiplying by one returns identity.
    CHECK_EQ(1 * dt, dt);
}

TEST_CASE_FIXTURE(TimeDeltaTest, "datetime.timedelta.divide")
{
    const auto a = Days<long long>(12) + Minutes<long long>(34) +
                   Seconds<long long>(56) + Microseconds<long long>(78) +
                   Picoseconds<long long>(90);

    const int k = 3;
    const auto dt = cs::TimeDelta(k * a);
    const auto quotient = cs::TimeDelta(a);

    // Compound assignment
    auto tmp = dt;
    tmp /= k;
    CHECK_EQ(tmp, quotient);

    // Binary operator
    CHECK_EQ(dt / k, quotient);

    // Dividing by one returns identity.
    CHECK_EQ(dt / 1, dt);
}

TEST_CASE_FIXTURE(TimeDeltaTest, "datetime.timedelta.modulo")
{
    const auto a = Milliseconds<long long>(123456789);
    const auto b = Days<long long>(12) + Minutes<long long>(34) +
                   Seconds<long long>(56) + Microseconds<long long>(78) +
                   Picoseconds<long long>(90);

    const auto dt1 = cs::TimeDelta(a);
    const auto dt2 = cs::TimeDelta(b);
    const auto remainder = cs::TimeDelta(b % a);

    // Compound assignment
    auto tmp1 = dt2;
    tmp1 %= dt1;
    CHECK_EQ(tmp1, remainder);

    auto tmp2 = dt2;
    tmp2 %= dt1.count();
    CHECK_EQ(tmp2, remainder);

    // Binary operator
    CHECK_EQ(dt2 % dt1, remainder);
    CHECK_EQ(dt2 % dt1.count(), remainder);
}

TEST_CASE_FIXTURE(TimeDeltaTest, "datetime.timedelta.compare_eq")
{
    const auto dt1 = cs::TimeDelta();
    const auto dt2 = cs::TimeDelta();
    const auto dt3 = one_picosec;

    CHECK(dt1 == dt1);
    CHECK(dt1 == dt2);
    CHECK_FALSE(dt1 == dt3);
}

TEST_CASE_FIXTURE(TimeDeltaTest, "datetime.timedelta.compare_ne")
{
    const auto dt1 = cs::TimeDelta();
    const auto dt2 = one_picosec;
    const auto dt3 = one_picosec;

    CHECK(dt1 != dt2);
    CHECK_FALSE(dt2 != dt3);
}

TEST_CASE_FIXTURE(TimeDeltaTest, "datetime.timedelta.compare_lt")
{
    const auto dt1 = cs::TimeDelta();
    const auto dt2 = -one_picosec;
    const auto dt3 = one_picosec;

    CHECK(dt2 < dt1);
    CHECK(dt1 < dt3);
    CHECK_FALSE(dt3 < dt2);
}

TEST_CASE_FIXTURE(TimeDeltaTest, "datetime.timedelta.compare_gt")
{
    const auto dt1 = cs::TimeDelta();
    const auto dt2 = -one_picosec;
    const auto dt3 = one_picosec;

    CHECK(dt1 > dt2);
    CHECK(dt3 > dt1);
    CHECK_FALSE(dt2 > dt3);
}

TEST_CASE_FIXTURE(TimeDeltaTest, "datetime.timedelta.compare_le")
{
    const auto dt1 = cs::TimeDelta();
    const auto dt2 = cs::TimeDelta();
    const auto dt3 = one_picosec;

    CHECK(dt1 <= dt2);
    CHECK(dt1 <= dt3);
    CHECK_FALSE(dt3 <= dt2);
}

TEST_CASE_FIXTURE(TimeDeltaTest, "datetime.timedelta.compare_ge")
{
    const auto dt1 = cs::TimeDelta();
    const auto dt2 = one_picosec;
    const auto dt3 = one_picosec;

    CHECK(dt2 >= dt1);
    CHECK(dt3 >= dt2);
    CHECK_FALSE(dt1 >= dt3);
}

TEST_CASE_FIXTURE(TimeDeltaTest, "datetime.timedelta.abs")
{
    const auto ms = Milliseconds<long>(123456);

    const auto dt1 = cs::TimeDelta(ms);
    const auto dt2 = cs::TimeDelta(-ms);

    CHECK_EQ(cs::abs(dt1), dt1);
    CHECK_EQ(cs::abs(dt2), dt1);
}
