#pragma once

namespace Data {
	template<typename T>
	class RedBlackContainer
	{
	private:
		enum Color {
			Black,
			Red
		};

		struct Node {
			T* data;
			Color color = Color.Black;
			Node *left, *right;

			Node(
			)
		};
	};
}
