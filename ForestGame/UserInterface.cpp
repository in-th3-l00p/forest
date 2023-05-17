#include <cmath>
#include "UserInterface.h"
#include "Configuration.h"

sf::Vector2f Engine::Ui::Widget::getPosition() const
{
	return position;
}

sf::Vector2f Engine::Ui::Widget::getSize() const
{
	return size;
}

void Engine::Ui::Widget::setPosition(sf::Vector2f position)
{
	this->position = position;
}

void Engine::Ui::Widget::setSize(sf::Vector2f size)
{
	this->size = size;
}

Engine::Ui::Button::Button(std::string text, sf::Vector2f positon, sf::Vector2f size)
{
	this->text = text;
	this->position = position;
	this->size = size;

	border.setFillColor(borderColor);
	border.setSize(size);
	border.setPosition(position);

	background.setFillColor(backgroundColor);
	background.setSize({ size.x - borderSize * 2, size.y - borderSize * 2 });
	background.setPosition({ position.x + borderSize, position.y + borderSize });

	textShape.setString(L"Hello world");
	textShape.setFont(Engine::Config::Assets::getAssets().defaultFont);
	textShape.setCharacterSize(fontSize);
	textShape.setPosition({ 
		position.x + size.x / 2 - textShape.getLocalBounds().width / 2, 
		position.y + size.y / 2 - textShape.getLocalBounds().height / 2 
		});
	textShape.setFillColor(textColor);
}

void Engine::Ui::Button::render(sf::RenderWindow& window) const
{
	window.draw(border);
	window.draw(background);
	window.draw(textShape);
}

void Engine::Ui::Button::setPosition(sf::Vector2f position)
{
	this->position = position;
	border.setPosition(position);
	background.setPosition({ position.x + borderSize, position.y + borderSize });
	textShape.setPosition({ 
		position.x + size.x / 2 - textShape.getLocalBounds().width / 2, 
		position.y + size.y / 2 - textShape.getLocalBounds().height / 2 
		});

}

void Engine::Ui::Button::setSize(sf::Vector2f size)
{
	this->size = size;
	border.setSize(size);
	background.setSize({ size.x - borderSize * 2, size.y - borderSize * 2});
	textShape.setPosition({
		position.x + size.x / 2 - textShape.getLocalBounds().width / 2, 
		position.y + size.y / 2 - textShape.getLocalBounds().height / 2 
		});
}

Engine::Ui::Label::Label(std::string text, sf::Vector2f positon, sf::Vector2f size)
{
	this->text = text;
	this->position = position;
	this->size = size;

	textShape.setString(L"Hello world");
	textShape.setFont(Engine::Config::Assets::getAssets().defaultFont);
	textShape.setCharacterSize(fontSize);
	textShape.setPosition(position);
	textShape.setFillColor(textColor);
}

void Engine::Ui::Label::render(sf::RenderWindow& window) const
{
	window.draw(textShape);
}

Engine::Ui::HorizontalLayout::HorizontalLayout(std::vector<Widget*> widgets, sf::Vector2f position, int spacing)
{
	// set members
	this->widgets = widgets;
	this->position = position;
	this->spacing = spacing;

	size.x = 0;
	size.y = 0;
	for (auto widget : widgets)
	{
		size.x += widget->getSize().x;
		size.y = std::max(size.y, widget->getSize().y);
	}
	size.x += spacing * (widgets.size() - 1);

	int currentX = position.x;
	for (auto widget : widgets)
	{
		widget->setPosition({ (float)currentX, position.y + size.y / 2 - widget->getSize().y / 2 });
		currentX += widget->getSize().x + spacing;
	}
}

Engine::Ui::HorizontalLayout::~HorizontalLayout()
{
	for (auto& widget : widgets)
		delete widget;
}

void Engine::Ui::HorizontalLayout::update(float& deltaTime) {
	for (auto& widget : widgets)
		widget->update(deltaTime);
}

void Engine::Ui::HorizontalLayout::render(sf::RenderWindow& window) const
{
	for (auto& widget : widgets)
		widget->render(window);
}

void Engine::Ui::HorizontalLayout::addWidget(Widget* widget)
{
	widgets.push_back(widget);
}
