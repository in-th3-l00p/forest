//
// pch.h
//

#pragma once

#include "gtest/gtest.h"

// dummy object
struct Person {
	std::string name;
	std::string email;
	int age;

	bool operator<(const Person& other) const {
		return name < other.name;
	}

	bool operator>(const Person& other) const {
		return name > other.name;
	}

	bool operator==(const Person& other) const {
		return name == other.name;
	}

	bool operator!=(const Person& other) const {
		return !(*this == other);
	}
};

