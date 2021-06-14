//-----------------------------------------------------------------------------

#include <iostream>

//-----------------------------------------------------------------------------

using namespace std;

//-----------------------------------------------------------------------------
#include <algorithm> // std::swap
#include <cstddef>   // size_t
#include <cstring>   // strlen, strcpy

struct String {
    String(const char *str = "")
            : size(strlen(str))
            , str(strcpy(new char[strlen(str) + 1], str))
    {}

    /* Реализуйте этот конструктор */
    String(size_t n, char c)
    {
        this->size = n;
        str = new char [n + 1];
        int i = 0;
        while ( i < n ){
            *(str + i) = c;
            i++;
        }
    }

    String(const String &other);

    /* и деструктор */
    ~String(){
        delete [] str;
    }

    /* Реализуйте оператор присваивания */
    String &operator=(const String &other)
    {
        if (this != &other)
        {
            delete [] str;

            size = other.size;

            str = new char[size + 1];
            strcpy(this->str, other.str);

        }
        return *this;
    }


    void append(String &appd_str){
        int i = 0, j = 0;

        while (*(this->str + i) !='\0' ) {
            i++;
        }

        while ( *(appd_str.str + j) !='\0' ) {
            j++;
        }

        this->size = i + j;

        char * updated_Str = new char[this ->size + 1];

        strcpy(updated_Str, this->str);
        strcpy(updated_Str+i, appd_str.str);

        delete [] this->str;
        this->str = new char [this ->size + 1];
        strcpy(this->str , updated_Str);

        delete [] updated_Str;
    }

//    int & operator [](int i) const
//    {
//        return i;
//    }

    String operator[](int i) const
    {
        auto tmp = str;
        return str;
    }

    char & operator [](int j) const
    {
        String res;
        return res;//str[j];
    }

    size_t size;
    char *str;
};



//-----------------------------------------------------------------------------

int main()
{
    String const hello("hello");

    String const hell = hello[0][4]; // теперь в hell хранится подстрока "hell"

//    String const ell  = hello[1][4]; // теперь в ell хранится подстрока "ell"

    return 0;
}
