#include <iostream>

#pragma once

class Time
{
private:
    int m_hour;
    int m_minute;
public:
    int getHour() const
    {
        return m_hour;
    }
    void setHour(const int hour)
    {
        if (Validate::validate(hour, UPPER_HOUR, LOWER_TIME))
        {
            m_hour = hour;
        }
    }
    int getMinute() const
    {
        return m_minute;
    }
    void setMinute(const int minute)
    {
        if (Validate::validate(minute, UPPER_MINUTE, LOWER_TIME))
        {
            m_minute = minute;
        }
    }
    bool operator== (const Time& t1)
    {
        return (t1.getHour() == getHour() && t1.getMinute() == getMinute());
    }
    Time& operator= (const Time& time)
    {
        m_hour = time.getHour();
        m_minute = time.getMinute();
        return *this;
    }
    Time()
    {
        setHour(0);
        setMinute(0);
    }
    Time(const int hour, const int minute)
    {
        setHour(hour);
        setMinute(minute);
    }
    Time(const Time& time)
    {
        setHour(time.m_hour);
        setMinute(time.m_minute);
    }
};
class Date
{
private:
    int m_day;
    int m_month;
    int m_year;
public:
    int getDay() const
    {
        return m_day;
    }
    void setDay(const int day)
    {
        if (Validate::validate(day, UPPER_DAY, LOWER_DATE))
        {
            m_day = day;
        }
    }
    int getMonth() const
    {
        return m_month;
    }
    void setMonth(const int month)
    {
        if (Validate::validate(month, UPPER_MONTH, LOWER_DATE))
        {
            m_month = month;
        }
    }
    int getYear() const
    {
        return m_year;
    }
    void setYear(const int year)
    {
        if (Validate::validate(year, UPPER_YEAR, LOWER_DATE))
        {
            m_year = year;
        }
    }
    bool operator== (const Date& d1)
    {
        return (d1.getDay() == getDay() && d1.getMonth() == getMonth() && d1.getYear() == getYear());
    }
    Date& operator= (const Date& date)
    {
        m_day = date.getDay();
        m_month = date.getMonth();
        m_year = date.getYear();
        return *this;
    }
    Date()
    {
        setDay(1);
        setMonth(1);
        setYear(2000);
    }
    Date(const int day, const int month, const int year)
    {
        setDay(day);
        setMonth(month);
        setYear(year);
    }
    Date(const Date& dt)
    {
        setDay(dt.m_day);
        setMonth(dt.m_month);
        setYear(dt.m_year);
    }
};

