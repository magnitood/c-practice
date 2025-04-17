#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//---------- Defined by Serializable ----------//
typedef struct Serializable Serializable;
typedef struct SerializableInterface SerializableInterface;

struct Serializable {
	SerializableInterface *vtable;
};

struct SerializableInterface {
	void (*serialize)(Serializable *);
};

void serialize(Serializable *sr)
{
	sr->vtable->serialize(sr);
}

//---------- Defined by Animal ---------//
typedef struct AnimalInterface AnimalInterface;
typedef struct Animal Animal;

struct AnimalInterface {
	void (*speak)(Animal *);
};

struct Animal {
	const AnimalInterface *vtable; // this vtable will be set up by derived class
};

void animal_speak(Animal *a) { a->vtable->speak(a); };

//---------- Define by Cat ----------//
typedef struct Cat Cat;
struct Cat {
	const AnimalInterface *vtable;
	const char *name;
};

void cat_speak(Cat *cat) { printf("Meow!! I am cat and my name is %s\n", cat->name); }
void cat_animal_speak_(Animal *animal) { cat_speak((Cat *) animal); } // this function is for the vtable entry
Cat *new_cat(char *name) {
	Cat *new = malloc(sizeof(*new));
	char *new_name = malloc(sizeof(*new_name) * (strlen(name)+1));
	if (new == NULL || new_name == NULL)
		return NULL;

	static const AnimalInterface vtable = { cat_animal_speak_ };
	new->vtable = &vtable;
	new->name = strcpy(new_name, name);

	return new;
}

//---------- Defined by Dog ----------//
typedef struct Dog Dog;
struct Dog {
	const AnimalInterface *vtable;
	const char *name;
};

void dog_speak(Dog *Dog) { printf("Bark!! I am dog and my name is %s\n", Dog->name); }
void dog_animal_speak_(Animal *animal) { dog_speak((Dog *) animal); } // this function is for the vtable entry
Dog *new_dog(char *name) {
	Dog *new = malloc(sizeof(*new));
	char *new_name = malloc(sizeof(*new_name) * (strlen(name)+1));
	if (new == NULL || new_name == NULL)
		return NULL;

	static const AnimalInterface vtable = { dog_animal_speak_ };
	new->vtable = &vtable;
	new->name = strcpy(new_name, name);

	return new;
}

int main()
{
	Cat *cat = new_cat("Tim");
	Dog *dog = new_dog("Bulldozer");
	cat_speak(cat);
	dog_speak(dog);

	Animal *animal; 

	animal = (Animal *) cat;
	animal_speak(animal);

	animal = (Animal *) dog;
	animal_speak(animal);
}
