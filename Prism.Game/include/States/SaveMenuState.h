#pragma once

#include <utility>
#include <string>
#include <array>

#include <State.h>
#include <Variables.h>
#include <Menu/Menu.h>
#include <Menu/MenuRenderer.h>
#include "World/WorldLoader.h"
#include "Menu/MenuBuilder.h"

namespace States {
	class SaveMenuState : public State {
	public:
		SaveMenuState() = default;
		~SaveMenuState() = default;

		void onInit(Context &context) override;

		void onUpdate(Context &context) override;

	private:
		void makeButtons(Context& context);
		std::unique_ptr<Menu::Menu> menu;
		Menu::MenuRenderer menuRenderer;
		std::string levelDirectory = Variables::Resources::SAVES;
		std::vector<std::string> savedGames{ "" };
		Renderer::Graphics::RenderDevice *renderDevice{ nullptr };
		int currentPage{ 0 };
		static constexpr int pageSize{ Variables::Visual::LevelSelection::ROWS * Variables::Visual::LevelSelection::COLUMNS };
		float ASPECT;
		bool shouldUpdateButtons = false;
	};
}
