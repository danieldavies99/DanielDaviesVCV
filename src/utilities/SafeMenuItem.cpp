#include "SafeMenuItem.hpp"

void SafeMenuItem::onAction (const rack::event::Action& e) {
    auto menu = rack::createMenu ();
    menu->addChild (rack::createMenuLabel (confirmText));
    menu->addChild (rack::createMenuItem (confirmButtonText, "", action, false, alwaysConsume));

    if (alwaysConsume)
        e.consume (this);
}