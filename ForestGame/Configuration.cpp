#include "Configuration.h"

namespace Engine
{
	namespace Config
	{
		Assets* Assets::assets = nullptr;

		Assets::Assets()
		{
			executablePath.resize(MAX_PATH);
			GetModuleFileNameA(NULL, (LPSTR)executablePath.c_str(), MAX_PATH);
			executablePath = executablePath.substr(0, executablePath.rfind('\\'));

			defaultFont.loadFromFile(executablePath + "\\assets\\default.ttf");
		}

		Assets& Assets::getAssets()
		{
			if (assets == nullptr)
				assets = new Assets();
			return *assets;
		}
	}
}