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

		void onInit(Context &context) override;

		void onUpdate(Context &context) override;

		void onLeave(Context &context) override;

		void onEnter(Context &context) override;

	protected:
		void drawMenu(Context &context);

	private:
		std::unique_ptr<Menu::Menu> menu;
		Menu::MenuRenderer menuRenderer;
		std::string levelDirectory{Variables::Resources::SAVES};
		std::vector<std::string> levels{""};
		Renderer::Graphics::RenderDevice *renderDevice{nullptr};
		bool nightmareMode{false};
		int currentPage{0};
		static constexpr int pageSize{Variables::Visual::WorldSelection::ROWS * Variables::Visual::WorldSelection::COLUMNS};
	};
}
