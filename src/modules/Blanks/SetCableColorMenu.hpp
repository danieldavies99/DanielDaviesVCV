#pragma once

#include "utilities/SafeMenuItem.hpp"
#include <rack.hpp>
#include <string>

struct SetCableColorMenu : SafeMenuItem
{
   SetCableColorMenu(std::string selectedColorScheme = rack::settings::preferDarkPanels ? "Dark" : "Light")
        : SafeMenuItem(
              "Use DD cable color scheme - " + selectedColorScheme,
              [=]
              {
                  if (rack::settings::preferDarkPanels)
                  {
                      rack::settings::cableColors = std::vector<NVGcolor>{
                          // nvgRGB(11, 32, 39), // dark panel color
                          nvgRGB(69, 105, 144),  // alt dark color (avoid using dark panel color because hard to see on dark panel)
                          nvgRGB(237, 106, 90),  // orange
                          nvgRGB(155, 193, 188), // green
                          nvgRGB(244, 241, 187), // yellow
                          nvgRGB(249, 250, 251), // light panel color
                      };
                  }
                  else
                  {
                      rack::settings::cableColors = std::vector<NVGcolor>{
                          nvgRGB(11, 32, 39),    // dark panel color
                          nvgRGB(237, 106, 90),  // orange
                          nvgRGB(155, 193, 188), // green
                          nvgRGB(244, 241, 187), // yellow
                          // nvgRGB(249, 250, 251), // light panel color
                          nvgRGB(89, 95, 114), // alt light color (avoid using light panel color because hard to see on light panels)
                      };
                  }
              },
              true,
              "This option will override your current cable color scheme.")
    {
    }

};