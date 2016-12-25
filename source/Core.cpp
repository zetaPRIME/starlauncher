#include "Core.h"

#include <3ds.h>

#include "starlight/InputManager.h"
#include "starlight/ThemeManager.h"
#include "starlight/GFXManager.h"
#include "starlight/gfx/RenderCore.h"

#include "starlight/ui/ScrollField.h"
#include "starlight/ui/Button.h"

using starlight::Vector2;
using starlight::VRect;
using starlight::Color;
using starlight::InputManager;
using starlight::GFXManager;
using starlight::ThemeManager;
using starlight::gfx::RenderCore;

using starlight::Application;

void Core::Init() {
    consoleInit(GFX_TOP, consoleGetDefault());
    
    auto container = std::make_shared<starlight::ui::ScrollField>(VRect(0,0,320-0,240-0));
    auto button = std::make_shared<starlight::ui::Button>(VRect(64,80,128,32));
    touchScreen->Add(container);
    container->Add(button);
    button->label = "I'm a button.";
    button->eOnTap = [](auto& btn){
        btn.label = "I was pressed!";
        btn.eOnTap = [](auto& btn){
            btn.label = "Event swap!";
            btn.eOnTap = [](auto& btn){
                //quit = true;
                btn.label = "Clicked again!\nBunch of lines!\nNow testing scrollarea fling with some extra size!\n\n\nPotato.\nCalamari sandwich on rye with a side of octagonal pimento; a jar of butter?";
                btn.rect.size.y = 573;
            };
        };
    };
    
    clearColor = Color(0.0f, 0.5f, 0.5f);
    
    //
}

void Core::End() {
    
}

void Core::Update() {
    if (InputManager::Held(KEY_Y) || InputManager::Pressed(KEY_START)) Application::Quit();
}

