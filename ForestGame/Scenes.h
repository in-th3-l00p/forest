#pragma once

#include <map>
#include <memory>
#include <functional>
#include <SFML/Graphics.hpp>
#include "UserInterface.h"
#include "Raycaster.h"
#include "Entity.h"

namespace Engine
{
	namespace Scenes
	{
		class Scene
		{
		private:
			std::function<void(Scene*)> sceneChanger;
		protected:
			const std::function<void(Scene*)>& getSceneChanger() const;
			std::map<int, Logics::Entity*> entities;

		public:
			Scene(std::function<void(Scene*)> sceneChanger);
			virtual ~Scene();

			virtual void update(float& deltaTime) = 0;
			virtual void render(sf::RenderWindow& window) const = 0;

			virtual void onResize(int width, int height) {};
		};

		class MainMenu : public Scene
		{
		private:
			Engine::Ui::HorizontalLayout mainLayout;

		public:
			MainMenu(std::function<void(Scene*)> sceneChanger);

			void update(float& deltaTime) override;
			void render(sf::RenderWindow& window) const override;
		};

		class RaycasterTest : public Scene
		{
		private:
			sf::Vector2i windowSize;
			std::unique_ptr<Logics::Map> map;
			std::unique_ptr<Logics::Player> player;
			std::unique_ptr<Logics::Raycaster> raycaster;

		public:
			RaycasterTest(std::function<void(Scene*)> sceneChanger);
			void update(float& deltaTime) override;
			void render(sf::RenderWindow& window) const override;
		};
	}
}
