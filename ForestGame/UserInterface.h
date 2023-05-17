#pragma once

#include <string>
#include <SFML/Graphics.hpp>

namespace Engine 
{
	namespace Ui 
	{
		class Widget
		{
		protected:
			sf::Vector2f position;
			sf::Vector2f size;

		public:
			virtual void update(float& deltaTime) = 0;
			virtual void render(sf::RenderWindow& window) const = 0;

			sf::Vector2f getPosition() const;
			sf::Vector2f getSize() const;
			virtual void setPosition(sf::Vector2f position);
			virtual void setSize(sf::Vector2f size);
			virtual bool isClicked(sf::Vector2f mousePosition);
		};

		class Button: public Widget
		{
		private:
			sf::Color backgroundColor = sf::Color::Black;
			sf::Color textColor = sf::Color::White;
			sf::Color borderColor = sf::Color::White;
			int borderSize = 4;
			int fontSize = 30;

			std::string text;

			sf::RectangleShape border;
			sf::RectangleShape background;
			sf::Text textShape;

		public:
			Button(std::string text, sf::Vector2f positon = {0, 0}, sf::Vector2f size = {180, 80});
			
			void update(float& deltaTime) override {};
			void render(sf::RenderWindow& window) const override;

			void setPosition(sf::Vector2f position) override;
			void setSize(sf::Vector2f position) override;

			bool isClicked(sf::Vector2f mousePosition) override;

			void setFontSize(int fontSize);
			void setText(std::string text);
			void setBackgroundColor(sf::Color color);
			void setTextColor(sf::Color color);
			void setBorderColor(sf::Color color);
		};

		class Label : public Widget
		{
		private:
			sf::Color textColor = sf::Color::White;
			int fontSize = 24;
			std::string text;
			sf::Text textShape;

		public:
			Label(std::string text, sf::Vector2f positon = { 0, 0 }, sf::Vector2f size = { 180, 80 });
			void update(float& deltaTime) override {};
			void render(sf::RenderWindow& window) const override;

			void setPosition(sf::Vector2f position) override;
			void setSize(sf::Vector2f position) override;

			void setText(std::string text);
			void setFontSize(int fontSize);
			void setTextColor(sf::Color color);
		};

		class HorizontalLayout : public Widget
		{
		private:
			std::vector<Widget*> widgets;
			int spacing;

		public:
			HorizontalLayout(
				std::vector<Widget*> widgets,
				sf::Vector2f position = { 0, 0 },
				int spacing = 10
			);
			~HorizontalLayout();

			void update(float& deltaTime) override;
			void render(sf::RenderWindow& window) const override;

			void addWidget(Widget* widget);

			std::vector<Widget*> getWidgets() const;
		};
	}
}
