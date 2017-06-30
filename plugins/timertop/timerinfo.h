/*
  timerinfo.h

  This file is part of GammaRay, the Qt application inspection and
  manipulation tool.

  Copyright (C) 2010-2017 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Thomas McGuire <thomas.mcguire@kdab.com>

  Licensees holding valid commercial KDAB GammaRay licenses may use this file in
  accordance with GammaRay Commercial License Agreement provided with the Software.

  Contact info@kdab.com if any conditions of this licensing are not clear to you.

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef GAMMARAY_TIMERTOP_TIMERINFO_H
#define GAMMARAY_TIMERTOP_TIMERINFO_H

#include <QPointer>
#include <QHash>
#include <QMetaType>

QT_BEGIN_NAMESPACE
class QTimer;
QT_END_NAMESPACE

namespace GammaRay {
/*
 */
class TimerId
{
    friend uint qHash(const TimerId &);

public:
    enum Type {
        InvalidType,
        // A QObject, no timer id
        QQmlTimerType,
        // A QObject, unstable timerId across stop/start
        QTimerType,
        // A timerId attached to a QObject
        QObjectType
    };

    TimerId();
    explicit TimerId(QObject *timer);
    explicit TimerId(int timerId);

    bool isValid() const;

    Type type() const;
    quintptr address() const;
    QTimer *timer() const;
    QObject *timerObject() const;
    int timerId() const;

    bool operator==(const TimerId &other) const;
    bool operator==(QObject *timer) const;
    bool operator==(int timerId) const;
    bool operator<(const TimerId &other) const;

private:
    Type m_type;
    quintptr m_timerAddress;
    QPointer<QObject> m_timer;
    int m_timerId;
};

struct TimerIdInfo
{
    TimerIdInfo()
        : timerId(-1)
        , totalWakeups(0)
    { }

    TimerIdInfo(const TimerId &id, QObject *receiver = nullptr);
    virtual ~TimerIdInfo() { }

    virtual void update(const TimerId &id, QObject *receiver = nullptr);

    int timerId;
    int totalWakeups;

    QString objectName;
    QString state;
    QString wakeupsPerSec;
    QString timePerWakeup;
    QString maxWakeupTime;
};

typedef QHash<TimerId, TimerIdInfo> TimerIdInfoHash;

uint qHash(const TimerId &id);
}

Q_DECLARE_METATYPE(GammaRay::TimerId)
Q_DECLARE_METATYPE(GammaRay::TimerIdInfo)
Q_DECLARE_METATYPE(GammaRay::TimerIdInfoHash)

#endif // GAMMARAY_TIMERINFO_H
