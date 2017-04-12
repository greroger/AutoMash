#pragma once

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
