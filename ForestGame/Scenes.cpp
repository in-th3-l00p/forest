#include "Scenes.h"

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
			: Scene(sceneChanger), mainLayout({ new Ui::Button("Start"), new Ui::Button("Test")})
		{
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
