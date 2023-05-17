#include "Scenes.h"
#include <iostream>

namespace Engine {
	namespace Scenes 
	{
		const std::function<void(Scene*)>& Scene::getSceneChanger() const
		{
			return sceneChanger;
		}

		Scene::Scene(std::function<void(Scene*)> sceneChanger)
		{
			this->sceneChanger = sceneChanger;
		}

		MainMenu::MainMenu(std::function<void(Scene*)> sceneChanger)
			: Scene(sceneChanger), mainLayout({})
		{
			float height = Config::Window::size.height;
			float width = Config::Window::size.width;

			/*sf::Vector2f buttonSize = { 150, 75 };

			Ui::Button* startButton = new Ui::Button("Start");
			startButton->setPosition({ (float)(width / 2 - buttonSize.x / 2), 200 } );
			startButton->setSize(buttonSize);
			
			mainLayout.addWidget(startButton);*/

			Ui::Label* title = new Ui::Label("\tTransylvanian Tales\nShadows of Enchantment");
			title->setPosition({ (float)(width / 2 - 325), 100 });
			title->setSize({ 500, 400 });
			title->setFontSize(50);

			Ui::Button* startButton = new Ui::Button("Start");
			startButton->setPosition({ (float)(width / 2 - 100), 275 });
			startButton->setSize({ 225, 90 });

			Ui::Button* exitButton = new Ui::Button("Exit");
			exitButton->setPosition({ (float)(width / 2 - 100), 526 });
			exitButton->setSize({ 225, 90 });

			Ui::Button* creditsButton = new Ui::Button("Credits");
			creditsButton->setPosition({ (float)(width / 2 - 100), 400 });
			creditsButton->setSize({ 225, 90 });

			mainLayout.addWidget(title);
			mainLayout.addWidget(startButton);
			mainLayout.addWidget(exitButton);
			mainLayout.addWidget(creditsButton);
		}

		void MainMenu::onClick(sf::Vector2f mousePosition)
		{
			if (mainLayout.getWidgets()[1]->isClicked(mousePosition))
				getSceneChanger()(new Scenes::RaycasterTest([](Scenes::Scene*) {}));
			else if (mainLayout.getWidgets()[2]->isClicked(mousePosition))
				exit(0);
			else if (mainLayout.getWidgets()[3]->isClicked(mousePosition))
				std::cout << "Credits" << std::endl;
		}

		void MainMenu::update(float& deltaTime)
		{
		}

		void MainMenu::render(sf::RenderWindow& window) const
		{
			mainLayout.render(window);
		}

		RaycasterTest::RaycasterTest(std::function<void(Scene*)> sceneChanger)
			: Scene(sceneChanger)
		{
			map = std::make_unique<Logics::Map>();
			player = std::make_unique<Logics::Player>();
			player->position = { 100, 100 };
			player->radius = 16;
			entities.push_back(new Logics::StaticEntity(Config::Assets::getAssets().treeTexture, {200.f, 200.f, 20.f}, 30.f));
			raycaster = std::make_unique<Logics::Raycaster>(*player, *map, entities);
		}

		void RaycasterTest::update(float& deltaTime)
		{
			player->update(deltaTime);
		}

		void RaycasterTest::render(sf::RenderWindow& window) const
		{
			raycaster->render(window);
		}
	}

}
