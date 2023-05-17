#include <string>
#include "pch.h"
#include <Container.h>

TEST(Container, ContainerIterator)
{
	Data::Container<Person> container;
	Person* person1, * person2, * person3, * person4;

	person1 = new Person{ "John", "john@gmail.com", 34 };
	person2 = new Person{ "Mary", "mary@gmail.com", 28 };
	person3 = new Person{ "Peter", "peter@gmail.com", 42 };
	person4 = new Person{ "Jane", "jane@gmail.com", 19 };
	container.add(person1);
	container.add(person2);
	container.add(person3);
	container.add(person4);

	std::set<Person> persons;
	for (auto& person : container)
		persons.insert(person);
	EXPECT_NE(persons.find(*person1), persons.end());
	EXPECT_NE(persons.find(*person2), persons.end());
	EXPECT_NE(persons.find(*person3), persons.end());
	EXPECT_NE(persons.find(*person4), persons.end());
}
