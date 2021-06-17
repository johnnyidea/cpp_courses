
#pragma once


class Singleton
{
public:

    static Singleton & instance()
    {
        static Singleton s;
        return s;
    }

    //Data & get_data()
    //{
    //    return _data;
    //}

private:
    
    Singleton(){};
    Singleton(const Singleton&);
    
    Singleton& operator = (const Singleton& s);

    //Data _data;
};
