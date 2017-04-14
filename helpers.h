#pragma once

#include <type_traits>
#include <atomic>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace boost::posix_time;

inline QString toQString(const time_duration &t)
{
    return QString("%1").arg(t.total_seconds() / 60);
    if (t.hours()) {
        return QString("%1:%2").arg(t.hours()).arg(t.minutes(), 2, 10, QChar('0'));
    }
    return QString("%1").arg(t.minutes());
}

template<class ENUM, class UNDERLYING=typename std::underlying_type<ENUM>::type>
class Enumeration
{
public:
    explicit Enumeration() : value(0) {}
    explicit Enumeration(ENUM singleFlag) : value(singleFlag) {}
    Enumeration(const Enumeration &rhs) : value(rhs.value) {}

    explicit operator UNDERLYING() { return value; }
    explicit operator bool() { return value != 0; }

    bool test(ENUM rhs) const { return value & rhs; }
    Enumeration& set(ENUM rhs) { value |= rhs; return *this; }
    Enumeration& reset(ENUM rhs) { value &= ~rhs; return *this; }

private:
    std::atomic<UNDERLYING> value;
};
