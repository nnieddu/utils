#include <iostream>

#define DUMPSTR_WNAME(os, name, a) \
    do { (os) << (name) << " value is " << (a) << std::endl; } while(false)

#define DUMPSTR(os, a) DUMPSTR_WNAME((os), #a, (a))
#define DUMP(a)        DUMPSTR_WNAME(std::cout, #a, (a))

struct S {
    int a1;
    float a2;
    std::string a3;

    std::ostream& dump(std::ostream& os)
    {
        DUMPSTR(os, a1);
        DUMPSTR(os, a2);
        DUMPSTR(os, a3);
        return os;
    }
};

int main()
{
    S s = { 1, 2, "123" };

    s.dump(std::cout);

    int coucou = 5;
    DUMP(coucou);

    DUMP(s.a1);
    DUMP(s.a2);
    DUMP(s.a3);

    return 0;
}
