#include "guiao0me.h"

void printP(Person p)
{
    printf("Name: %s\nAge: %d\n", p.name, p.age);
}

int main()
{
    Person p = new_person("Maria", 19);
    printP(p);

    Person clone = clone_person(&p);
    printP(clone);

    person_change_age(&clone, 17);

    printf("person_age(p) = %d\n", person_age(&p));
    printf("person_age(clone) = %d\n", person_age(&clone));

    destroy_person(&p);
    destroy_person(&clone);

    return 0;
}