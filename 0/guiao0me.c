#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "guiao0me.h"

Person new_person(char *name, int age)
{
    Person new;

    new.name = malloc(strlen(name) * sizeof(char) + 1);
    strcpy(new.name, name);
    new.age = age;

    return new;
}

Person clone_person(Person*p)
{
    Person new;
    new.name = strdup(p->name);
    new.age = p->age;
    return new;
}

void destroy_person(Person*p)
{
    free(p->name);
}

int person_age(Person*p)
{
    return p->age;
}

void person_change_age(Person*p, int age)
{
    p->age = age;
}