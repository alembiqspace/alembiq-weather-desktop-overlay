// ==WindhawkMod==
// @id              alembiq-weather-desktop-overlay
// @name            Desktop Weather & Particles Overlay
// @description     Weather effects (snow, rain, fog, wind, clear) and seasonal particles (snow, rain, leaves, poplar fluff, sakura) under desktop icons with window accumulation and shake physics.
// @version         0.3.2
// @author          alembiq
// @github          https://github.com/duschkopf/alembiq-weather-desktop-overlay/
// @include         explorer.exe
// @compilerOptions -ld2d1 -ldwrite -lwininet -luser32 -lgdi32 -lshell32 -lole32
// ==/WindhawkMod==

// ==WindhawkModSettings==
/*
# --- 1. SYSTEM & LAYER ---
- layerAttachMode: auto
  $name: "[System] Layer attach mode"
  $description: "Controls Z-order placement of the overlay. Allowed: auto, progman_direct, desktop_bottom. Default: auto."
  $options:
    - auto: Auto (below SHELLDLL_DefView icons)
    - progman_direct: Progman reference
    - desktop_bottom: Bottom of Z-order (HWND_BOTTOM)
- bottomBoundaryMode: above_taskbar
  $name: "[System] Bottom boundary mode"
  $description: "Sets the bottom reference line for fallen objects/puddles. Allowed: above_taskbar, screen_bottom, custom_offset. Default: above_taskbar."
  $options:
    - above_taskbar: Above taskbar (Shell_TrayWnd)
    - screen_bottom: Bottom edge of screen
    - custom_offset: Custom offset from bottom (px)
- bottomOffsetPx: 0
  $name: "[System] Custom bottom offset (px)"
  $description: "Vertical offset in px above bottom edge when bottomBoundaryMode is custom_offset. Range: -500 to 1000. Invalid input resets to 0."
- multiMonitorMode: primary
  $name: "[System] Monitors"
  $description: "Render on primary monitor or full virtual screen. Allowed: primary, all. Default: primary."
  $options:
    - primary: Primary monitor
    - all: All monitors (virtual screen)

# --- 2. WEATHER SOURCES & SEASONS ---
- primarySource: open_meteo
  $name: "[Weather] Primary source"
  $description: "Primary forecast provider for auto modes. Allowed: open_meteo, custom_api, local_file. Default: open_meteo."
  $options:
    - open_meteo: Open-Meteo API
    - custom_api: Custom JSON URL
    - local_file: Local file
- fallbackSource: off
  $name: "[Weather] Fallback source"
  $description: "Backup forecast source if primary fails. Allowed: off, open_meteo, local_file. Default: off."
  $options:
    - off: Off
    - open_meteo: Open-Meteo API
    - local_file: Local file
- latitude: "44.7866"
  $name: "[Weather] Latitude"
  $description: "Latitude in decimal degrees (-90.0 to 90.0). Invalid input resets to 44.7866."
- longitude: "20.4489"
  $name: "[Weather] Longitude"
  $description: "Longitude in decimal degrees (-180.0 to 180.0). Invalid input resets to 20.4489."
- customApiUrl: ""
  $name: "[Weather] Custom JSON API URL"
  $description: "HTTP/HTTPS JSON endpoint (weather_code, condition, wind_speed_10m, wind_direction_10m). Default: empty."
- localWeatherPath: ""
  $name: "[Weather] Local weather file path"
  $description: "Path to local JSON or text weather file. Default: empty."
- updateIntervalMin: 30
  $name: "[Weather] Update interval (min)"
  $description: "Forecast refresh period in minutes (1 to 1440). Out-of-range/invalid resets to 30."
- springStart: "01.03"
  $name: "[Seasons] Spring start (DD.MM)"
  $description: "Spring start date in DD.MM format (01.01 to 31.12). Invalid format resets to 01.03."
- springEnd: "31.05"
  $name: "[Seasons] Spring end (DD.MM)"
  $description: "Spring end date in DD.MM format (01.01 to 31.12). Invalid format resets to 31.05."
- summerStart: "01.06"
  $name: "[Seasons] Summer start (DD.MM)"
  $description: "Summer start date in DD.MM format (01.01 to 31.12). Invalid format resets to 01.06."
- summerEnd: "31.08"
  $name: "[Seasons] Summer end (DD.MM)"
  $description: "Summer end date in DD.MM format (01.01 to 31.12). Invalid format resets to 31.08."
- autumnStart: "01.09"
  $name: "[Seasons] Autumn start (DD.MM)"
  $description: "Autumn start date in DD.MM format (01.01 to 31.12). Invalid format resets to 01.09."
- autumnEnd: "30.11"
  $name: "[Seasons] Autumn end (DD.MM)"
  $description: "Autumn end date in DD.MM format (01.01 to 31.12). Invalid format resets to 30.11."
- winterStart: "01.12"
  $name: "[Seasons] Winter start (DD.MM)"
  $description: "Winter start date in DD.MM format (supports year wrap). Invalid format resets to 01.12."
- winterEnd: "29.02"
  $name: "[Seasons] Winter end (DD.MM)"
  $description: "Winter end date in DD.MM format (supports year wrap). Invalid format resets to 29.02."

# --- 3. PRECIPITATION (RAIN / SNOW / HAIL) ---
- precipitationMode: auto
  $name: "[Precip] Mode"
  $description: "Precipitation layer mode. Allowed: off, auto, rain, snow, hail. Default: auto."
  $options:
    - off: Off
    - auto: Auto (forecast)
    - rain: Rain
    - snow: Snow
    - hail: Hail
- precipFallDirection: auto
  $name: "[Precip] Fall direction"
  $description: "Falling direction for precipitation. Allowed: auto, down, down_left, down_right. Default: auto."
  $options:
    - auto: Auto (forecast)
    - down: Down
    - down_left: Down-left
    - down_right: Down-right
- precipFallSpeedMps: "6.5"
  $name: "[Precip] Fall speed (m/s)"
  $description: "Fall speed in m/s (0.1 to 50.0). Invalid/out-of-range resets to 6.5."
- rainIntensity: 25
  $name: "[Precip] Rain intensity (%)"
  $description: "Rain intensity (0..100). Any value outside 0..100 or invalid resets to 25."
- snowIntensity: 25
  $name: "[Precip] Snow intensity (%)"
  $description: "Snow intensity (0..100). Any value outside 0..100 or invalid resets to 25."
- hailIntensity: 25
  $name: "[Precip] Hail intensity (%)"
  $description: "Hail intensity (0..100). Any value outside 0..100 or invalid resets to 25."
- rainMaxAccumulated: 180
  $name: "[Precip] Rain puddles max count"
  $description: "Max rain puddle elements on screen (0..2000; 0 disables). Invalid/out-of-range resets to 180."
- snowMaxAccumulated: 260
  $name: "[Precip] Snow max accumulated"
  $description: "Max accumulated snow items on screen (0..2000; 0 disables). Invalid/out-of-range resets to 260."
- hailMaxAccumulated: 220
  $name: "[Precip] Hail max accumulated"
  $description: "Max accumulated hail items on screen (0..2000; 0 disables). Invalid/out-of-range resets to 220."
- rainLifetimeMin: "3.0"
  $name: "[Precip] Rain puddles lifetime (min)"
  $description: "Auto-disappear time in minutes (-1 to 1440; -1 = never). Invalid resets to 3.0."
- snowLifetimeMin: "15.0"
  $name: "[Precip] Snow lifetime (min)"
  $description: "Auto-disappear time in minutes (-1 to 1440; -1 = never). Invalid resets to 15.0."
- hailLifetimeMin: "10.0"
  $name: "[Precip] Hail lifetime (min)"
  $description: "Auto-disappear time in minutes (-1 to 1440; -1 = never). Invalid resets to 10.0."
- colorRain: ""
  $name: "[Precip] Rain color (#RRGGBB)"
  $description: "Custom HEX (#RRGGBB) or empty for default sky-blue. Invalid HEX resets to default."
- colorSnow: ""
  $name: "[Precip] Snow color (#RRGGBB)"
  $description: "Custom HEX (#RRGGBB) or empty for default white. Invalid HEX resets to default."
- colorHail: ""
  $name: "[Precip] Hail color (#RRGGBB)"
  $description: "Custom HEX (#RRGGBB) or empty for default ice-blue. Invalid HEX resets to default."

# --- 4. SEASONAL OBJECTS (LEAVES / EXTRA SNOW / PETALS) ---
- seasonalObjectMode: auto
  $name: "[SeasonObj] Mode"
  $description: "Seasonal falling objects mode. Allowed: off, auto, autumn_leaves, extra_snow, petals. Default: auto."
  $options:
    - off: Off
    - auto: Auto (season)
    - autumn_leaves: Autumn leaves
    - extra_snow: Snow (extra)
    - petals: Petals
- seasonalFallDirection: auto
  $name: "[SeasonObj] Fall direction"
  $description: "Fall direction for seasonal objects. Allowed: auto, down, down_left, down_right. Default: auto."
  $options:
    - auto: Auto (forecast)
    - down: Down
    - down_left: Down-left
    - down_right: Down-right
- seasonalFallSpeedMps: "2.2"
  $name: "[SeasonObj] Fall speed (m/s)"
  $description: "Fall speed in m/s (0.1 to 30.0). Invalid/out-of-range resets to 2.2."
- autumnLeavesIntensity: 25
  $name: "[SeasonObj] Autumn leaves intensity (%)"
  $description: "Autumn leaves intensity (0..100). Outside 0..100 or invalid resets to 25."
- extraSnowIntensity: 25
  $name: "[SeasonObj] Extra snow intensity (%)"
  $description: "Extra snow intensity (0..100). Outside 0..100 or invalid resets to 25."
- petalsIntensity: 25
  $name: "[SeasonObj] Petals intensity (%)"
  $description: "Petals intensity (0..100). Outside 0..100 or invalid resets to 25."
- autumnLeavesMaxAccumulated: 220
  $name: "[SeasonObj] Autumn leaves max accumulated"
  $description: "Max accumulated leaves on screen (0..2000; 0 disables). Invalid/out-of-range resets to 220."
- extraSnowMaxAccumulated: 240
  $name: "[SeasonObj] Extra snow max accumulated"
  $description: "Max accumulated extra snow items (0..2000; 0 disables). Invalid/out-of-range resets to 240."
- petalsMaxAccumulated: 220
  $name: "[SeasonObj] Petals max accumulated"
  $description: "Max accumulated petals on screen (0..2000; 0 disables). Invalid/out-of-range resets to 220."
- autumnLeavesLifetimeMin: "20.0"
  $name: "[SeasonObj] Autumn leaves lifetime (min)"
  $description: "Auto-disappear time in minutes (-1 to 1440; -1 = never). Invalid resets to 20.0."
- extraSnowLifetimeMin: "15.0"
  $name: "[SeasonObj] Extra snow lifetime (min)"
  $description: "Auto-disappear time in minutes (-1 to 1440; -1 = never). Invalid resets to 15.0."
- petalsLifetimeMin: "12.0"
  $name: "[SeasonObj] Petals lifetime (min)"
  $description: "Auto-disappear time in minutes (-1 to 1440; -1 = never). Invalid resets to 12.0."
- colorAutumnLeaves: ""
  $name: "[SeasonObj] Autumn leaves color (#RRGGBB)"
  $description: "Custom HEX (#RRGGBB) or empty for default amber/orange. Invalid HEX resets to default."
- colorExtraSnow: ""
  $name: "[SeasonObj] Extra snow color (#RRGGBB)"
  $description: "Custom HEX (#RRGGBB) or empty for default snow-white. Invalid HEX resets to default."
- colorPetals: ""
  $name: "[SeasonObj] Petals color (#RRGGBB)"
  $description: "Custom HEX (#RRGGBB) or empty for default soft pink. Invalid HEX resets to default."

# --- 5. GENERAL EFFECTS ---
- effectsIntensity: 25
  $name: "[Effects] General intensity (%)"
  $description: "Strength/opacity for general effects (0..100). Outside 0..100 or invalid resets to 25."
- effectClear: auto
  $name: "[Effects] Clear"
  $description: "Clear sky sunlight glow. Allowed: auto, on, off. Can stack with other effects."
  $options:
    - auto: Auto (forecast)
    - on: On
    - off: Off
- effectPartlyCloudy: auto
  $name: "[Effects] Partly cloudy"
  $description: "Soft cloud layer. Allowed: auto, on, off. Can stack with other effects."
  $options:
    - auto: Auto (forecast)
    - on: On
    - off: Off
- effectOvercast: auto
  $name: "[Effects] Overcast"
  $description: "Overcast sky veil. Allowed: auto, on, off. Can stack with other effects."
  $options:
    - auto: Auto (forecast)
    - on: On
    - off: Off
- effectDust: auto
  $name: "[Effects] Dust"
  $description: "Airborne dust haze. Allowed: auto, on, off. Can stack with other effects."
  $options:
    - auto: Auto (forecast)
    - on: On
    - off: Off
- effectFog: auto
  $name: "[Effects] Fog"
  $description: "Soft mist/fog layer. Allowed: auto, on, off. Can stack with other effects."
  $options:
    - auto: Auto (forecast)
    - on: On
    - off: Off
- effectSmog: auto
  $name: "[Effects] Smog"
  $description: "Smog layer. Allowed: auto, on, off. Can stack with other effects."
  $options:
    - auto: Auto (forecast)
    - on: On
    - off: Off
- effectThunderstorm: auto
  $name: "[Effects] Thunderstorm"
  $description: "Storm atmosphere with branched lightning flashes. Allowed: auto, on, off."
  $options:
    - auto: Auto (forecast)
    - on: On
    - off: Off
- effectAurora: auto
  $name: "[Effects] Aurora"
  $description: "Smooth animated aurora curtains in upper screen area. Allowed: auto, on, off."
  $options:
    - auto: Auto (forecast)
    - on: On
    - off: Off
- effectMirage: auto
  $name: "[Effects] Mirage"
  $description: "Soft horizon shimmer wave band. Allowed: auto, on, off."
  $options:
    - auto: Auto (forecast)
    - on: On
    - off: Off
- effectRainbow: auto
  $name: "[Effects] Rainbow"
  $description: "Multi-band rainbow arc with soft edge fade. Allowed: auto, on, off."
  $options:
    - auto: Auto (forecast)
    - on: On
    - off: Off
- rainbowCenterX: 50
  $name: "[Rainbow] Center X (%)"
  $description: "Horizontal center from left to right in % of screen width (0..100). Outside 0..100 or invalid resets to 50."
- rainbowCenterY: 15
  $name: "[Rainbow] Center Y (%)"
  $description: "Vertical center from bottom to top in % of screen height (0..100). Outside 0..100 or invalid resets to 15."
- rainbowRadius: 55
  $name: "[Rainbow] Radius (%)"
  $description: "Arc radius in % (0..100; 0 = off, 100 = min(screenWidth, screenHeight)). Outside 0..100 or invalid resets to 55."
- effectHalo: auto
  $name: "[Effects] Halo"
  $description: "Soft luminous atmospheric halo ring. Allowed: auto, on, off."
  $options:
    - auto: Auto (forecast)
    - on: On
    - off: Off
- haloCenterX: 50
  $name: "[Halo] Center X (%)"
  $description: "Horizontal center from left to right in % of screen width (0..100). Outside 0..100 or invalid resets to 50."
- haloCenterY: 72
  $name: "[Halo] Center Y (%)"
  $description: "Vertical center from bottom to top in % of screen height (0..100). Outside 0..100 or invalid resets to 72."
- haloRadius: 24
  $name: "[Halo] Radius (%)"
  $description: "Halo radius in % (0..100; 0 = off, 100 = min(screenWidth, screenHeight)). Outside 0..100 or invalid resets to 24."
- colorClear: ""
  $name: "[Effects] Clear color (#RRGGBB)"
  $description: "Custom HEX (#RRGGBB) or empty for default warm sunlight."
- colorPartlyCloudy: ""
  $name: "[Effects] Partly cloudy color (#RRGGBB)"
  $description: "Custom HEX (#RRGGBB) or empty for default soft cloud."
- colorOvercast: ""
  $name: "[Effects] Overcast color (#RRGGBB)"
  $description: "Custom HEX (#RRGGBB) or empty for default slate gray."
- colorDust: ""
  $name: "[Effects] Dust color (#RRGGBB)"
  $description: "Custom HEX (#RRGGBB) or empty for default sand dust."
- colorFog: ""
  $name: "[Effects] Fog color (#RRGGBB)"
  $description: "Custom HEX (#RRGGBB) or empty for default mist."
- colorSmog: ""
  $name: "[Effects] Smog color (#RRGGBB)"
  $description: "Custom HEX (#RRGGBB) or empty for default smog."
- colorThunderstorm: ""
  $name: "[Effects] Thunderstorm color (#RRGGBB)"
  $description: "Custom HEX (#RRGGBB) or empty for default lightning white-blue."
- colorAurora: ""
  $name: "[Effects] Aurora color (#RRGGBB)"
  $description: "Custom HEX (#RRGGBB) or empty for default aurora green."
- colorMirage: ""
  $name: "[Effects] Mirage color (#RRGGBB)"
  $description: "Custom HEX (#RRGGBB) or empty for default warm shimmer."
- colorRainbow: ""
  $name: "[Effects] Rainbow color (#RRGGBB)"
  $description: "Custom HEX (#RRGGBB) or empty for default multi-color spectrum."
- colorHalo: ""
  $name: "[Effects] Halo color (#RRGGBB)"
  $description: "Custom HEX (#RRGGBB) or empty for default pale halo."

# --- 6. CURSOR & WINDOW PHYSICS ---
- cursorAction: move
  $name: "[Cursor] Action on fallen objects"
  $description: "Affects fallen objects only (never falling particles). move = push along cursor movement; clear = erase touched fallen items; none = ignore cursor."
  $options:
    - move: Move (push in movement direction)
    - clear: Clear (erase on touch)
    - none: None (ignore cursor)
- cursorRadiusPx: 95
  $name: "[Cursor] Radius (px)"
  $description: "Cursor action radius in pixels (10 to 500). Invalid/out-of-range resets to 95."
- windowShakeSensitivity: 55
  $name: "[Windows] Shed sensitivity (1..100)"
  $description: "Sensitivity for detaching fallen items when moving windows (1..100). Invalid/out-of-range resets to 55."
- windowInertiaFactor: "0.75"
  $name: "[Windows] Shed inertia factor"
  $description: "Horizontal inertia transferred to detached fallen items (0.0 to 3.0). Invalid resets to 0.75."
- particleScale: "1.0"
  $name: "[Objects] Size scale"
  $description: "Size multiplier for falling and fallen objects (0.3 to 4.0). Invalid resets to 1.0."

# --- 7. PERFORMANCE ---
- targetFps: 60
  $name: "[Perf] Target FPS (30 or 60)"
  $description: "Target frame rate (30 or 60). Any other value resets to 60."
- pauseOnFullscreen: true
  $name: "[Perf] Pause on fullscreen apps"
  $description: "Pauses rendering while a fullscreen app is active. Default: true."
- excludedProcesses: "obs64.exe, ApplicationFrameHost.exe"
  $name: "[Perf] Excluded processes"
  $description: "Comma-separated executable names excluded from window accumulation/shedding."
*/
// ==/WindhawkModSettings==

#include <windows.h>
#include <wininet.h>
#include <d2d1.h>
#include <dwmapi.h>
#include <atomic>
#include <chrono>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <mutex>
#include <random>
#include <sstream>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

namespace {

enum class ObjectKind {
    Rain,
    Snow,
    Hail,
    AutumnLeaves,
    ExtraSnow,
    Petals
};

enum class PrecipMode {
    Off,
    Auto,
    Rain,
    Snow,
    Hail
};

enum class SeasonalMode {
    Off,
    Auto,
    AutumnLeaves,
    ExtraSnow,
    Petals
};

enum class TriStateMode {
    Auto,
    On,
    Off
};

enum class FallDirMode {
    Auto,
    Down,
    DownLeft,
    DownRight
};

enum class CursorActionMode {
    Move,
    Clear,
    None
};

struct GeneralEffectsState {
    bool clear = false;
    bool partlyCloudy = false;
    bool overcast = false;
    bool dust = false;
    bool fog = false;
    bool smog = false;
    bool thunderstorm = false;
    bool aurora = false;
    bool mirage = false;
    bool rainbow = false;
    bool halo = false;
};

struct DayMonth {
    int day = 1;
    int month = 1;
};

struct Settings {
    std::wstring layerAttachMode = L"auto";
    std::wstring bottomBoundaryMode = L"above_taskbar";
    int bottomOffsetPx = 0;
    std::wstring multiMonitorMode = L"primary";

    std::wstring primarySource = L"open_meteo";
    std::wstring fallbackSource = L"off";
    double latitude = 44.7866;
    double longitude = 20.4489;
    std::wstring customApiUrl;
    std::wstring localWeatherPath;
    int updateIntervalMin = 30;

    DayMonth springStart{1, 3};
    DayMonth springEnd{31, 5};
    DayMonth summerStart{1, 6};
    DayMonth summerEnd{31, 8};
    DayMonth autumnStart{1, 9};
    DayMonth autumnEnd{30, 11};
    DayMonth winterStart{1, 12};
    DayMonth winterEnd{29, 2};

    PrecipMode precipitationMode = PrecipMode::Auto;
    FallDirMode precipFallDirection = FallDirMode::Auto;
    double precipFallSpeedMps = 6.5;

    int rainIntensity = 25;
    int snowIntensity = 25;
    int hailIntensity = 25;

    int rainMaxAccumulated = 180;
    int snowMaxAccumulated = 260;
    int hailMaxAccumulated = 220;

    double rainLifetimeMin = 3.0;
    double snowLifetimeMin = 15.0;
    double hailLifetimeMin = 10.0;

    SeasonalMode seasonalObjectMode = SeasonalMode::Auto;
    FallDirMode seasonalFallDirection = FallDirMode::Auto;
    double seasonalFallSpeedMps = 2.2;

    int autumnLeavesIntensity = 25;
    int extraSnowIntensity = 25;
    int petalsIntensity = 25;

    int autumnLeavesMaxAccumulated = 220;
    int extraSnowMaxAccumulated = 240;
    int petalsMaxAccumulated = 220;

    double autumnLeavesLifetimeMin = 20.0;
    double extraSnowLifetimeMin = 15.0;
    double petalsLifetimeMin = 12.0;

    int effectsIntensity = 25;
    TriStateMode effectClear = TriStateMode::Auto;
    TriStateMode effectPartlyCloudy = TriStateMode::Auto;
    TriStateMode effectOvercast = TriStateMode::Auto;
    TriStateMode effectDust = TriStateMode::Auto;
    TriStateMode effectFog = TriStateMode::Auto;
    TriStateMode effectSmog = TriStateMode::Auto;
    TriStateMode effectThunderstorm = TriStateMode::Auto;
    TriStateMode effectAurora = TriStateMode::Auto;
    TriStateMode effectMirage = TriStateMode::Auto;
    TriStateMode effectRainbow = TriStateMode::Auto;
    TriStateMode effectHalo = TriStateMode::Auto;

    int rainbowCenterX = 50;
    int rainbowCenterY = 15;
    int rainbowRadius = 55;

    int haloCenterX = 50;
    int haloCenterY = 72;
    int haloRadius = 24;

    D2D1_COLOR_F colorRain = D2D1::ColorF(0.42f, 0.72f, 1.0f, 0.78f);
    D2D1_COLOR_F colorSnow = D2D1::ColorF(0.96f, 0.98f, 1.0f, 0.92f);
    D2D1_COLOR_F colorHail = D2D1::ColorF(0.76f, 0.90f, 1.0f, 0.95f);
    D2D1_COLOR_F colorAutumnLeaves = D2D1::ColorF(0.88f, 0.44f, 0.12f, 0.92f);
    D2D1_COLOR_F colorExtraSnow = D2D1::ColorF(0.92f, 0.96f, 1.0f, 0.88f);
    D2D1_COLOR_F colorPetals = D2D1::ColorF(1.0f, 0.74f, 0.84f, 0.90f);

    bool hasCustomClearColor = false;
    D2D1_COLOR_F colorClear = D2D1::ColorF(1.0f, 0.92f, 0.65f, 0.25f);
    bool hasCustomPartlyCloudyColor = false;
    D2D1_COLOR_F colorPartlyCloudy = D2D1::ColorF(0.88f, 0.91f, 0.95f, 0.22f);
    bool hasCustomOvercastColor = false;
    D2D1_COLOR_F colorOvercast = D2D1::ColorF(0.55f, 0.59f, 0.65f, 0.35f);
    bool hasCustomDustColor = false;
    D2D1_COLOR_F colorDust = D2D1::ColorF(0.84f, 0.68f, 0.45f, 0.28f);
    bool hasCustomFogColor = false;
    D2D1_COLOR_F colorFog = D2D1::ColorF(0.82f, 0.86f, 0.90f, 0.35f);
    bool hasCustomSmogColor = false;
    D2D1_COLOR_F colorSmog = D2D1::ColorF(0.56f, 0.50f, 0.42f, 0.36f);
    bool hasCustomThunderstormColor = false;
    D2D1_COLOR_F colorThunderstorm = D2D1::ColorF(0.84f, 0.92f, 1.0f, 0.95f);
    bool hasCustomAuroraColor = false;
    D2D1_COLOR_F colorAurora = D2D1::ColorF(0.22f, 0.92f, 0.62f, 0.32f);
    bool hasCustomMirageColor = false;
    D2D1_COLOR_F colorMirage = D2D1::ColorF(0.98f, 0.86f, 0.66f, 0.25f);
    bool hasCustomRainbowColor = false;
    D2D1_COLOR_F colorRainbow = D2D1::ColorF(1.0f, 0.78f, 0.35f, 0.35f);
    bool hasCustomHaloColor = false;
    D2D1_COLOR_F colorHalo = D2D1::ColorF(0.98f, 0.95f, 0.82f, 0.32f);

    CursorActionMode cursorAction = CursorActionMode::Move;
    int cursorRadiusPx = 95;
    int windowShakeSensitivity = 55;
    double windowInertiaFactor = 0.75;
    double particleScale = 1.0;

    int targetFps = 60;
    bool pauseOnFullscreen = true;
    std::wstring excludedProcesses = L"obs64.exe, ApplicationFrameHost.exe";
};

struct FallingItem {
    ObjectKind kind = ObjectKind::Snow;
    bool isSeasonalLayer = false;
    float x = 0.0f;
    float y = 0.0f;
    float size = 6.0f;
    float angle = 0.0f;
    float spin = 0.0f;
    float swayPhase = 0.0f;
    float alpha = 0.9f;
};

struct FallenItem {
    ObjectKind kind = ObjectKind::Snow;
    bool isSeasonalLayer = false;
    bool onWindow = false;
    HWND hostWindow = nullptr;
    float relX = 0.0f;
    float relY = 0.0f;
    float vx = 0.0f;
    float vy = 0.0f;
    float size = 6.0f;
    float angle = 0.0f;
    float alpha = 0.92f;
    float ageSec = 0.0f;
    bool fallingOff = false;
};

struct LightningFlash {
    float timer = 0.0f;
    float xStart = 0.0f;
    float xEnd = 0.0f;
};

struct WindowMotion {
    RECT rect = {};
    float prevCenterX = 0.0f;
    float prevCenterY = 0.0f;
    bool hasPrev = false;
};

std::mutex g_mutex;
Settings g_settings;

bool g_hasForecastPrecip = false;
ObjectKind g_forecastPrecip = ObjectKind::Rain;
int g_forecastWindDirSign = 0;
double g_forecastWindSpeedKmh = 0.0;
GeneralEffectsState g_forecastEffects;

HWND g_overlayHwnd = nullptr;
std::thread g_renderThread;
std::thread g_weatherThread;
std::atomic<bool> g_running{false};

ID2D1Factory* g_d2dFactory = nullptr;
ID2D1DCRenderTarget* g_dcRenderTarget = nullptr;
HDC g_memDC = nullptr;
HBITMAP g_dibBitmap = nullptr;
HGDIOBJ g_oldBitmap = nullptr;
int g_dibWidth = 0;
int g_dibHeight = 0;

int g_canvasLeft = 0;
int g_canvasTop = 0;
int g_canvasWidth = 0;
int g_canvasHeight = 0;

std::vector<FallingItem> g_falling;
std::vector<FallenItem> g_fallen;
LightningFlash g_lightning;
std::unordered_map<HWND, WindowMotion> g_windows;

std::wstring ToLower(std::wstring s) {
    for (auto& ch : s) ch = static_cast<wchar_t>(towlower(ch));
    return s;
}

std::wstring Trim(const std::wstring& s) {
    size_t a = s.find_first_not_of(L" \t\r\n");
    if (a == std::wstring::npos) return L"";
    size_t b = s.find_last_not_of(L" \t\r\n");
    return s.substr(a, b - a + 1);
}

bool TryParseDoubleStrict(const std::wstring& raw, double& outVal) {
    std::wstring s = Trim(raw);
    if (s.empty()) return false;
    for (wchar_t& c : s) {
        if (c == L',') c = L'.';
    }
    wchar_t* endPtr = nullptr;
    errno = 0;
    double v = std::wcstod(s.c_str(), &endPtr);
    if (errno != 0 || endPtr == s.c_str()) return false;
    while (*endPtr != L'\0') {
        if (!iswspace(*endPtr)) return false;
        ++endPtr;
    }
    if (!std::isfinite(v)) return false;
    outVal = v;
    return true;
}

int ParseIntRangeOrDefault(int rawVal, int minVal, int maxVal, int defVal) {
    if (rawVal < minVal || rawVal > maxVal) return defVal;
    return rawVal;
}

double ParseDoubleRangeOrDefault(const std::wstring& raw, double minVal, double maxVal, double defVal) {
    double v = 0.0;
    if (!TryParseDoubleStrict(raw, v)) return defVal;
    if (v < minVal || v > maxVal) return defVal;
    return v;
}

int SanitizePercent(int rawVal) {
    return ParseIntRangeOrDefault(rawVal, 0, 100, 25);
}

int DaysInMonthSafe(int month) {
    switch (month) {
        case 2: return 29;
        case 4: case 6: case 9: case 11: return 30;
        default: return 31;
    }
}

DayMonth ParseDayMonthStrict(const std::wstring& raw, DayMonth defVal) {
    std::wstring s = Trim(raw);
    size_t sep = s.find(L'.');
    if (sep == std::wstring::npos) sep = s.find(L'/');
    if (sep == std::wstring::npos) return defVal;
    std::wstring dPart = Trim(s.substr(0, sep));
    std::wstring mPart = Trim(s.substr(sep + 1));
    if (dPart.empty() || mPart.empty()) return defVal;
    for (wchar_t c : dPart) if (!iswdigit(c)) return defVal;
    for (wchar_t c : mPart) if (!iswdigit(c)) return defVal;
    try {
        int d = std::stoi(dPart);
        int m = std::stoi(mPart);
        if (m < 1 || m > 12) return defVal;
        if (d < 1 || d > DaysInMonthSafe(m)) return defVal;
        return DayMonth{d, m};
    } catch (...) {
        return defVal;
    }
}

int ToMonthDayKey(int month, int day) {
    return month * 100 + day;
}

bool IsDateInRange(int curKey, DayMonth start, DayMonth end) {
    int sKey = ToMonthDayKey(start.month, start.day);
    int eKey = ToMonthDayKey(end.month, end.day);
    if (sKey <= eKey) return curKey >= sKey && curKey <= eKey;
    return curKey >= sKey || curKey <= eKey;
}

SeasonalMode DetectSeasonByDates(const Settings& cfg) {
    std::time_t now = std::time(nullptr);
    std::tm tmLocal = {};
    localtime_s(&tmLocal, &now);
    int curKey = ToMonthDayKey(tmLocal.tm_mon + 1, tmLocal.tm_mday);

    if (IsDateInRange(curKey, cfg.springStart, cfg.springEnd)) return SeasonalMode::Petals;
    if (IsDateInRange(curKey, cfg.summerStart, cfg.summerEnd)) return SeasonalMode::Off;
    if (IsDateInRange(curKey, cfg.autumnStart, cfg.autumnEnd)) return SeasonalMode::AutumnLeaves;
    if (IsDateInRange(curKey, cfg.winterStart, cfg.winterEnd)) return SeasonalMode::ExtraSnow;
    return SeasonalMode::Off;
}

PrecipMode ParsePrecipMode(const std::wstring& s) {
    std::wstring v = ToLower(Trim(s));
    if (v == L"off") return PrecipMode::Off;
    if (v == L"rain") return PrecipMode::Rain;
    if (v == L"snow") return PrecipMode::Snow;
    if (v == L"hail") return PrecipMode::Hail;
    return PrecipMode::Auto;
}

SeasonalMode ParseSeasonalMode(const std::wstring& s) {
    std::wstring v = ToLower(Trim(s));
    if (v == L"off") return SeasonalMode::Off;
    if (v == L"autumn_leaves" || v == L"leaves") return SeasonalMode::AutumnLeaves;
    if (v == L"extra_snow" || v == L"snow") return SeasonalMode::ExtraSnow;
    if (v == L"petals" || v == L"sakura") return SeasonalMode::Petals;
    return SeasonalMode::Auto;
}

TriStateMode ParseTriState(const std::wstring& s) {
    std::wstring v = ToLower(Trim(s));
    if (v == L"on") return TriStateMode::On;
    if (v == L"off") return TriStateMode::Off;
    return TriStateMode::Auto;
}

FallDirMode ParseFallDir(const std::wstring& s) {
    std::wstring v = ToLower(Trim(s));
    if (v == L"down") return FallDirMode::Down;
    if (v == L"down_left" || v == L"left") return FallDirMode::DownLeft;
    if (v == L"down_right" || v == L"right") return FallDirMode::DownRight;
    return FallDirMode::Auto;
}

CursorActionMode ParseCursorAction(const std::wstring& s) {
    std::wstring v = ToLower(Trim(s));
    if (v == L"clear") return CursorActionMode::Clear;
    if (v == L"none") return CursorActionMode::None;
    return CursorActionMode::Move;
}

int WindDegToSign(double deg) {
    double norm = std::fmod(deg, 360.0);
    if (norm < 0.0) norm += 360.0;
    if (norm >= 45.0 && norm < 225.0) return 1;
    return -1;
}

bool TryParseHexColorStrict(const std::wstring& hexRaw, float defaultAlpha, D2D1_COLOR_F& outColor) {
    std::wstring s = Trim(hexRaw);
    if (s.empty()) return false;
    if (s[0] == L'#') s.erase(0, 1);
    if (s.size() != 6) return false;
    for (wchar_t c : s) {
        if (!iswxdigit(c)) return false;
    }
    try {
        unsigned long rgb = std::stoul(s, nullptr, 16);
        float r = ((rgb >> 16) & 0xFF) / 255.0f;
        float g = ((rgb >> 8) & 0xFF) / 255.0f;
        float b = (rgb & 0xFF) / 255.0f;
        outColor = D2D1::ColorF(r, g, b, defaultAlpha);
        return true;
    } catch (...) {
        return false;
    }
}

std::vector<std::wstring> SplitExcluded(const std::wstring& raw) {
    std::vector<std::wstring> result;
    std::wstringstream ss(raw);
    std::wstring item;
    while (std::getline(ss, item, L',')) {
        std::wstring t = ToLower(Trim(item));
        if (!t.empty()) result.push_back(t);
    }
    return result;
}

void LoadSettingsFromWh() {
    Settings next;
    auto readStr = [](LPCWSTR name, const std::wstring& defVal) -> std::wstring {
        PCWSTR raw = Wh_GetStringSetting(name);
        if (!raw) return defVal;
        std::wstring out(raw);
        Wh_FreeStringSetting(raw);
        return out;
    };

    next.layerAttachMode = readStr(L"layerAttachMode", L"auto");
    next.bottomBoundaryMode = readStr(L"bottomBoundaryMode", L"above_taskbar");
    next.bottomOffsetPx = ParseIntRangeOrDefault(Wh_GetIntSetting(L"bottomOffsetPx"), -500, 1000, 0);
    next.multiMonitorMode = readStr(L"multiMonitorMode", L"primary");

    next.primarySource = readStr(L"primarySource", L"open_meteo");
    next.fallbackSource = readStr(L"fallbackSource", L"off");
    next.latitude = ParseDoubleRangeOrDefault(readStr(L"latitude", L"44.7866"), -90.0, 90.0, 44.7866);
    next.longitude = ParseDoubleRangeOrDefault(readStr(L"longitude", L"20.4489"), -180.0, 180.0, 20.4489);
    next.customApiUrl = Trim(readStr(L"customApiUrl", L""));
    next.localWeatherPath = Trim(readStr(L"localWeatherPath", L""));
    next.updateIntervalMin = ParseIntRangeOrDefault(Wh_GetIntSetting(L"updateIntervalMin"), 1, 1440, 30);

    next.springStart = ParseDayMonthStrict(readStr(L"springStart", L"01.03"), DayMonth{1, 3});
    next.springEnd = ParseDayMonthStrict(readStr(L"springEnd", L"31.05"), DayMonth{31, 5});
    next.summerStart = ParseDayMonthStrict(readStr(L"summerStart", L"01.06"), DayMonth{1, 6});
    next.summerEnd = ParseDayMonthStrict(readStr(L"summerEnd", L"31.08"), DayMonth{31, 8});
    next.autumnStart = ParseDayMonthStrict(readStr(L"autumnStart", L"01.09"), DayMonth{1, 9});
    next.autumnEnd = ParseDayMonthStrict(readStr(L"autumnEnd", L"30.11"), DayMonth{30, 11});
    next.winterStart = ParseDayMonthStrict(readStr(L"winterStart", L"01.12"), DayMonth{1, 12});
    next.winterEnd = ParseDayMonthStrict(readStr(L"winterEnd", L"29.02"), DayMonth{29, 2});

    next.precipitationMode = ParsePrecipMode(readStr(L"precipitationMode", L"auto"));
    next.precipFallDirection = ParseFallDir(readStr(L"precipFallDirection", L"auto"));
    next.precipFallSpeedMps = ParseDoubleRangeOrDefault(readStr(L"precipFallSpeedMps", L"6.5"), 0.1, 50.0, 6.5);

    next.rainIntensity = SanitizePercent(Wh_GetIntSetting(L"rainIntensity"));
    next.snowIntensity = SanitizePercent(Wh_GetIntSetting(L"snowIntensity"));
    next.hailIntensity = SanitizePercent(Wh_GetIntSetting(L"hailIntensity"));

    next.rainMaxAccumulated = ParseIntRangeOrDefault(Wh_GetIntSetting(L"rainMaxAccumulated"), 0, 2000, 180);
    next.snowMaxAccumulated = ParseIntRangeOrDefault(Wh_GetIntSetting(L"snowMaxAccumulated"), 0, 2000, 260);
    next.hailMaxAccumulated = ParseIntRangeOrDefault(Wh_GetIntSetting(L"hailMaxAccumulated"), 0, 2000, 220);

    auto readLifetime = [&](LPCWSTR key, double defMin) -> double {
        double v = 0.0;
        if (!TryParseDoubleStrict(readStr(key, L""), v)) return defMin;
        if (v < 0.0) {
            return (std::abs(v + 1.0) < 1e-6) ? -1.0 : defMin;
        }
        if (v > 1440.0) return defMin;
        return std::max(0.05, v);
    };
    next.rainLifetimeMin = readLifetime(L"rainLifetimeMin", 3.0);
    next.snowLifetimeMin = readLifetime(L"snowLifetimeMin", 15.0);
    next.hailLifetimeMin = readLifetime(L"hailLifetimeMin", 10.0);

    next.seasonalObjectMode = ParseSeasonalMode(readStr(L"seasonalObjectMode", L"auto"));
    next.seasonalFallDirection = ParseFallDir(readStr(L"seasonalFallDirection", L"auto"));
    next.seasonalFallSpeedMps = ParseDoubleRangeOrDefault(readStr(L"seasonalFallSpeedMps", L"2.2"), 0.1, 30.0, 2.2);

    next.autumnLeavesIntensity = SanitizePercent(Wh_GetIntSetting(L"autumnLeavesIntensity"));
    next.extraSnowIntensity = SanitizePercent(Wh_GetIntSetting(L"extraSnowIntensity"));
    next.petalsIntensity = SanitizePercent(Wh_GetIntSetting(L"petalsIntensity"));

    next.autumnLeavesMaxAccumulated = ParseIntRangeOrDefault(Wh_GetIntSetting(L"autumnLeavesMaxAccumulated"), 0, 2000, 220);
    next.extraSnowMaxAccumulated = ParseIntRangeOrDefault(Wh_GetIntSetting(L"extraSnowMaxAccumulated"), 0, 2000, 240);
    next.petalsMaxAccumulated = ParseIntRangeOrDefault(Wh_GetIntSetting(L"petalsMaxAccumulated"), 0, 2000, 220);

    next.autumnLeavesLifetimeMin = readLifetime(L"autumnLeavesLifetimeMin", 20.0);
    next.extraSnowLifetimeMin = readLifetime(L"extraSnowLifetimeMin", 15.0);
    next.petalsLifetimeMin = readLifetime(L"petalsLifetimeMin", 12.0);

    next.effectsIntensity = SanitizePercent(Wh_GetIntSetting(L"effectsIntensity"));
    next.effectClear = ParseTriState(readStr(L"effectClear", L"auto"));
    next.effectPartlyCloudy = ParseTriState(readStr(L"effectPartlyCloudy", L"auto"));
    next.effectOvercast = ParseTriState(readStr(L"effectOvercast", L"auto"));
    next.effectDust = ParseTriState(readStr(L"effectDust", L"auto"));
    next.effectFog = ParseTriState(readStr(L"effectFog", L"auto"));
    next.effectSmog = ParseTriState(readStr(L"effectSmog", L"auto"));
    next.effectThunderstorm = ParseTriState(readStr(L"effectThunderstorm", L"auto"));
    next.effectAurora = ParseTriState(readStr(L"effectAurora", L"auto"));
    next.effectMirage = ParseTriState(readStr(L"effectMirage", L"auto"));
    next.effectRainbow = ParseTriState(readStr(L"effectRainbow", L"auto"));
    next.effectHalo = ParseTriState(readStr(L"effectHalo", L"auto"));

    next.rainbowCenterX = ParseIntRangeOrDefault(Wh_GetIntSetting(L"rainbowCenterX"), 0, 100, 50);
    next.rainbowCenterY = ParseIntRangeOrDefault(Wh_GetIntSetting(L"rainbowCenterY"), 0, 100, 15);
    next.rainbowRadius = ParseIntRangeOrDefault(Wh_GetIntSetting(L"rainbowRadius"), 0, 100, 55);

    next.haloCenterX = ParseIntRangeOrDefault(Wh_GetIntSetting(L"haloCenterX"), 0, 100, 50);
    next.haloCenterY = ParseIntRangeOrDefault(Wh_GetIntSetting(L"haloCenterY"), 0, 100, 72);
    next.haloRadius = ParseIntRangeOrDefault(Wh_GetIntSetting(L"haloRadius"), 0, 100, 24);

    TryParseHexColorStrict(readStr(L"colorRain", L""), 0.78f, next.colorRain);
    TryParseHexColorStrict(readStr(L"colorSnow", L""), 0.92f, next.colorSnow);
    TryParseHexColorStrict(readStr(L"colorHail", L""), 0.95f, next.colorHail);
    TryParseHexColorStrict(readStr(L"colorAutumnLeaves", L""), 0.92f, next.colorAutumnLeaves);
    TryParseHexColorStrict(readStr(L"colorExtraSnow", L""), 0.88f, next.colorExtraSnow);
    TryParseHexColorStrict(readStr(L"colorPetals", L""), 0.90f, next.colorPetals);

    next.hasCustomClearColor = TryParseHexColorStrict(readStr(L"colorClear", L""), 0.25f, next.colorClear);
    next.hasCustomPartlyCloudyColor = TryParseHexColorStrict(readStr(L"colorPartlyCloudy", L""), 0.22f, next.colorPartlyCloudy);
    next.hasCustomOvercastColor = TryParseHexColorStrict(readStr(L"colorOvercast", L""), 0.35f, next.colorOvercast);
    next.hasCustomDustColor = TryParseHexColorStrict(readStr(L"colorDust", L""), 0.28f, next.colorDust);
    next.hasCustomFogColor = TryParseHexColorStrict(readStr(L"colorFog", L""), 0.35f, next.colorFog);
    next.hasCustomSmogColor = TryParseHexColorStrict(readStr(L"colorSmog", L""), 0.36f, next.colorSmog);
    next.hasCustomThunderstormColor = TryParseHexColorStrict(readStr(L"colorThunderstorm", L""), 0.95f, next.colorThunderstorm);
    next.hasCustomAuroraColor = TryParseHexColorStrict(readStr(L"colorAurora", L""), 0.32f, next.colorAurora);
    next.hasCustomMirageColor = TryParseHexColorStrict(readStr(L"colorMirage", L""), 0.25f, next.colorMirage);
    next.hasCustomRainbowColor = TryParseHexColorStrict(readStr(L"colorRainbow", L""), 0.35f, next.colorRainbow);
    next.hasCustomHaloColor = TryParseHexColorStrict(readStr(L"colorHalo", L""), 0.32f, next.colorHalo);

    next.cursorAction = ParseCursorAction(readStr(L"cursorAction", L"move"));
    next.cursorRadiusPx = ParseIntRangeOrDefault(Wh_GetIntSetting(L"cursorRadiusPx"), 10, 500, 95);
    next.windowShakeSensitivity = ParseIntRangeOrDefault(Wh_GetIntSetting(L"windowShakeSensitivity"), 1, 100, 55);
    next.windowInertiaFactor = ParseDoubleRangeOrDefault(readStr(L"windowInertiaFactor", L"0.75"), 0.0, 3.0, 0.75);
    next.particleScale = ParseDoubleRangeOrDefault(readStr(L"particleScale", L"1.0"), 0.3, 4.0, 1.0);

    int fpsRaw = Wh_GetIntSetting(L"targetFps");
    next.targetFps = (fpsRaw == 30 || fpsRaw == 60) ? fpsRaw : 60;
    next.pauseOnFullscreen = Wh_GetIntSetting(L"pauseOnFullscreen") != 0;
    next.excludedProcesses = readStr(L"excludedProcesses", L"obs64.exe, ApplicationFrameHost.exe");

    std::lock_guard<std::mutex> lock(g_mutex);
    g_settings = next;
}

std::string HttpGetUtf8(const std::wstring& url) {
    URL_COMPONENTSW parts = {};
    parts.dwStructSize = sizeof(parts);
    wchar_t host[256] = {};
    wchar_t path[2048] = {};
    parts.lpszHostName = host;
    parts.dwHostNameLength = _countof(host);
    parts.lpszUrlPath = path;
    parts.dwUrlPathLength = _countof(path);

    if (!InternetCrackUrlW(url.c_str(), 0, 0, &parts)) return {};

    HINTERNET hSession = InternetOpenW(L"WindhawkWeatherMod/0.5", INTERNET_OPEN_TYPE_PRECONFIG, nullptr, nullptr, 0);
    if (!hSession) return {};

    DWORD flags = INTERNET_FLAG_RELOAD | INTERNET_FLAG_NO_CACHE_WRITE;
    if (parts.nScheme == INTERNET_SCHEME_HTTPS) {
        flags |= INTERNET_FLAG_SECURE;
    }

    HINTERNET hConnect = InternetConnectW(
        hSession, host, parts.nPort, nullptr, nullptr, INTERNET_SERVICE_HTTP, 0, 0);
    if (!hConnect) {
        InternetCloseHandle(hSession);
        return {};
    }

    HINTERNET hRequest = HttpOpenRequestW(
        hConnect, L"GET", path, nullptr, nullptr, nullptr, flags, 0);
    std::string response;
    if (hRequest && HttpSendRequestW(hRequest, nullptr, 0, nullptr, 0)) {
        char buf[4096];
        DWORD bytesRead = 0;
        while (InternetReadFile(hRequest, buf, sizeof(buf), &bytesRead) && bytesRead > 0) {
            response.append(buf, bytesRead);
        }
    }

    if (hRequest) InternetCloseHandle(hRequest);
    InternetCloseHandle(hConnect);
    InternetCloseHandle(hSession);
    return response;
}

void ApplyForecastCode(int code, bool& hasPrecip, ObjectKind& precipKind, GeneralEffectsState& fx) {
    hasPrecip = false;
    fx = GeneralEffectsState{};

    if (code == 0) {
        fx.clear = true;
    } else if (code == 1 || code == 2) {
        fx.partlyCloudy = true;
    } else if (code == 3) {
        fx.overcast = true;
    } else if (code == 45 || code == 48) {
        fx.fog = true;
    } else if (code == 71 || code == 73 || code == 75 || code == 77 || code == 85 || code == 86) {
        hasPrecip = true;
        precipKind = ObjectKind::Snow;
    } else if (code == 96 || code == 99) {
        hasPrecip = true;
        precipKind = ObjectKind::Hail;
        fx.thunderstorm = true;
    } else if (code == 95) {
        hasPrecip = true;
        precipKind = ObjectKind::Rain;
        fx.thunderstorm = true;
    } else if ((code >= 51 && code <= 67) || (code >= 80 && code <= 82)) {
        hasPrecip = true;
        precipKind = ObjectKind::Rain;
    }
}

bool ParseWeatherJson(const std::string& json, bool& hasPrecip, ObjectKind& precipKind,
                      GeneralEffectsState& fx, double& windSpeed, int& windSign) {
    auto extractNumber = [&](const std::string& key, double& val) -> bool {
        size_t pos = json.find("\"" + key + "\"");
        if (pos == std::string::npos) return false;
        pos = json.find(':', pos);
        if (pos == std::string::npos) return false;
        pos++;
        while (pos < json.size() && (json[pos] == ' ' || json[pos] == '\t')) pos++;
        try {
            val = std::stod(json.substr(pos));
            return std::isfinite(val);
        } catch (...) {
            return false;
        }
    };

    auto extractString = [&](const std::string& key, std::string& val) -> bool {
        size_t pos = json.find("\"" + key + "\"");
        if (pos == std::string::npos) return false;
        pos = json.find(':', pos);
        if (pos == std::string::npos) return false;
        pos = json.find('"', pos);
        if (pos == std::string::npos) return false;
        size_t end = json.find('"', pos + 1);
        if (end == std::string::npos) return false;
        val = json.substr(pos + 1, end - pos - 1);
        return true;
    };

    double spd = 0.0;
    if (extractNumber("wind_speed_10m", spd) || extractNumber("windspeed", spd) || extractNumber("wind_speed", spd)) {
        windSpeed = std::max(0.0, spd);
    }

    double deg = -1.0;
    if (extractNumber("wind_direction_10m", deg) || extractNumber("winddirection", deg) || extractNumber("wind_deg", deg)) {
        windSign = (windSpeed > 0.2) ? WindDegToSign(deg) : 0;
    } else {
        windSign = 0;
    }

    double wmo = -999.0;
    if (extractNumber("weather_code", wmo) || extractNumber("weathercode", wmo)) {
        ApplyForecastCode(static_cast<int>(wmo), hasPrecip, precipKind, fx);
        return true;
    }

    std::string cond;
    if (extractString("condition", cond) || extractString("weather", cond)) {
        for (auto& c : cond) c = static_cast<char>(tolower(c));
        hasPrecip = false;
        fx = GeneralEffectsState{};
        if (cond.find("hail") != std::string::npos) { hasPrecip = true; precipKind = ObjectKind::Hail; }
        else if (cond.find("snow") != std::string::npos) { hasPrecip = true; precipKind = ObjectKind::Snow; }
        else if (cond.find("rain") != std::string::npos) { hasPrecip = true; precipKind = ObjectKind::Rain; }

        if (cond.find("clear") != std::string::npos || cond.find("sun") != std::string::npos) fx.clear = true;
        if (cond.find("partly") != std::string::npos) fx.partlyCloudy = true;
        if (cond.find("overcast") != std::string::npos || cond.find("cloud") != std::string::npos) fx.overcast = true;
        if (cond.find("dust") != std::string::npos) fx.dust = true;
        if (cond.find("fog") != std::string::npos || cond.find("mist") != std::string::npos) fx.fog = true;
        if (cond.find("smog") != std::string::npos) fx.smog = true;
        if (cond.find("thunder") != std::string::npos || cond.find("storm") != std::string::npos) fx.thunderstorm = true;
        if (cond.find("aurora") != std::string::npos) fx.aurora = true;
        if (cond.find("mirage") != std::string::npos) fx.mirage = true;
        if (cond.find("rainbow") != std::string::npos) fx.rainbow = true;
        if (cond.find("halo") != std::string::npos) fx.halo = true;
        return true;
    }
    return false;
}

bool FetchWeatherSource(const std::wstring& src, const Settings& cfg, bool& hasPrecip,
                        ObjectKind& precipKind, GeneralEffectsState& fx,
                        double& windSpeed, int& windSign) {
    if (src == L"off") return false;
    if (src == L"open_meteo") {
        std::wstringstream url;
        url << L"https://api.open-meteo.com/v1/forecast?latitude=" << cfg.latitude
            << L"&longitude=" << cfg.longitude
            << L"¤t=weather_code,wind_speed_10m,wind_direction_10m";
        std::string body = HttpGetUtf8(url.str());
        if (body.empty()) return false;
        return ParseWeatherJson(body, hasPrecip, precipKind, fx, windSpeed, windSign);
    }
    if (src == L"custom_api") {
        if (cfg.customApiUrl.empty()) return false;
        std::string body = HttpGetUtf8(cfg.customApiUrl);
        if (body.empty()) return false;
        return ParseWeatherJson(body, hasPrecip, precipKind, fx, windSpeed, windSign);
    }
    if (src == L"local_file") {
        if (cfg.localWeatherPath.empty()) return false;
        HANDLE hFile = CreateFileW(cfg.localWeatherPath.c_str(), GENERIC_READ, FILE_SHARE_READ,
                                     nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
        if (hFile == INVALID_HANDLE_VALUE) return false;
        DWORD size = GetFileSize(hFile, nullptr);
        std::string content;
        if (size > 0 && size < 1024 * 1024) {
            content.resize(size);
            DWORD read = 0;
            ReadFile(hFile, content.data(), size, &read, nullptr);
            content.resize(read);
        }
        CloseHandle(hFile);
        if (content.empty()) return false;
        return ParseWeatherJson(content, hasPrecip, precipKind, fx, windSpeed, windSign);
    }
    return false;
}

void WeatherWorkerLoop() {
    while (g_running.load()) {
        Settings cfg;
        int intervalSec = 1800;
        {
            std::lock_guard<std::mutex> lock(g_mutex);
            cfg = g_settings;
            intervalSec = cfg.updateIntervalMin * 60;
        }

        bool hasP = false;
        ObjectKind pKind = ObjectKind::Rain;
        GeneralEffectsState fx;
        double wSpd = 0.0;
        int wSign = 0;

        bool ok = FetchWeatherSource(cfg.primarySource, cfg, hasP, pKind, fx, wSpd, wSign);
        if (!ok && cfg.fallbackSource != L"off" && cfg.fallbackSource != cfg.primarySource) {
            ok = FetchWeatherSource(cfg.fallbackSource, cfg, hasP, pKind, fx, wSpd, wSign);
        }

        if (ok) {
            std::lock_guard<std::mutex> lock(g_mutex);
            g_hasForecastPrecip = hasP;
            g_forecastPrecip = pKind;
            g_forecastEffects = fx;
            g_forecastWindSpeedKmh = wSpd;
            g_forecastWindDirSign = wSign;
        }

        for (int i = 0; i < intervalSec && g_running.load(); ++i) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
}

void UpdateCanvasGeometry(const Settings& cfg) {
    if (cfg.multiMonitorMode == L"all") {
        g_canvasLeft = GetSystemMetrics(SM_XVIRTUALSCREEN);
        g_canvasTop = GetSystemMetrics(SM_YVIRTUALSCREEN);
        g_canvasWidth = std::max(1, GetSystemMetrics(SM_CXVIRTUALSCREEN));
        g_canvasHeight = std::max(1, GetSystemMetrics(SM_CYVIRTUALSCREEN));
    } else {
        g_canvasLeft = 0;
        g_canvasTop = 0;
        g_canvasWidth = std::max(1, GetSystemMetrics(SM_CXSCREEN));
        g_canvasHeight = std::max(1, GetSystemMetrics(SM_CYSCREEN));
    }
}

int ComputeBottomLimitY(const Settings& cfg) {
    int baseBottom = g_canvasTop + g_canvasHeight;
    if (cfg.bottomBoundaryMode == L"above_taskbar") {
        HWND hTray = FindWindowW(L"Shell_TrayWnd", nullptr);
        RECT trayRect = {};
        if (hTray && GetWindowRect(hTray, &trayRect)) {
            baseBottom = std::min(baseBottom, static_cast<int>(trayRect.top));
        }
    } else if (cfg.bottomBoundaryMode == L"custom_offset") {
        baseBottom -= cfg.bottomOffsetPx;
    }
    return std::clamp(baseBottom, g_canvasTop + 10, g_canvasTop + g_canvasHeight);
}

bool IsFullscreenAppActive() {
    HWND fg = GetForegroundWindow();
    if (!fg || fg == g_overlayHwnd) return false;
    wchar_t cls[128] = {};
    GetClassNameW(fg, cls, _countof(cls));
    std::wstring clsStr = cls;
    if (clsStr == L"Progman" || clsStr == L"WorkerW" || clsStr == L"Shell_TrayWnd") return false;

    RECT fgRect = {};
    if (!GetWindowRect(fg, &fgRect)) return false;
    HMONITOR mon = MonitorFromWindow(fg, MONITOR_DEFAULTTOPRIMARY);
    MONITORINFO mi = {sizeof(mi)};
    if (!GetMonitorInfoW(mon, &mi)) return false;

    return (fgRect.left <= mi.rcMonitor.left &&
            fgRect.top <= mi.rcMonitor.top &&
            fgRect.right >= mi.rcMonitor.right &&
            fgRect.bottom >= mi.rcMonitor.bottom);
}

std::wstring GetProcessBaseNameLower(DWORD pid) {
    HANDLE hProc = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pid);
    if (!hProc) return {};
    wchar_t path[MAX_PATH] = {};
    DWORD len = _countof(path);
    std::wstring name;
    if (QueryFullProcessImageNameW(hProc, 0, path, &len)) {
        std::wstring full(path, len);
        size_t slash = full.find_last_of(L"\\/");
        name = ToLower((slash == std::wstring::npos) ? full : full.substr(slash + 1));
    }
    CloseHandle(hProc);
    return name;
}

struct EnumCtx {
    const std::vector<std::wstring>* excluded;
    std::vector<HWND>* outWindows;
};

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam) {
    auto* ctx = reinterpret_cast<EnumCtx*>(lParam);
    if (!IsWindowVisible(hwnd) || IsIconic(hwnd)) return TRUE;
    if (hwnd == g_overlayHwnd) return TRUE;

    LONG exStyle = GetWindowLongW(hwnd, GWL_EXSTYLE);
    if (exStyle & WS_EX_TOOLWINDOW) return TRUE;
    if (GetWindow(hwnd, GW_OWNER) != nullptr) return TRUE;

    BOOL cloaked = FALSE;
    DwmGetWindowAttribute(hwnd, DWMWA_CLOAKED, &cloaked, sizeof(cloaked));
    if (cloaked) return TRUE;

    wchar_t cls[128] = {};
    GetClassNameW(hwnd, cls, _countof(cls));
    std::wstring clsStr = cls;
    if (clsStr == L"Progman" || clsStr == L"WorkerW" || clsStr == L"Shell_TrayWnd" ||
        clsStr == L"Windows.UI.Core.CoreWindow") {
        return TRUE;
    }

    DWORD pid = 0;
    GetWindowThreadProcessId(hwnd, &pid);
    if (pid != 0 && ctx->excluded && !ctx->excluded->empty()) {
        std::wstring procName = GetProcessBaseNameLower(pid);
        if (!procName.empty()) {
            for (const auto& ex : *ctx->excluded) {
                if (procName == ex) return TRUE;
            }
        }
    }

    RECT r = {};
    if (GetWindowRect(hwnd, &r) && (r.right - r.left) >= 80 && (r.bottom - r.top) >= 40) {
        ctx->outWindows->push_back(hwnd);
    }
    return TRUE;
}

HWND FindShellDefViewHost() {
    HWND progman = FindWindowW(L"Progman", nullptr);
    if (progman && FindWindowExW(progman, nullptr, L"SHELLDLL_DefView", nullptr)) {
        return progman;
    }
    HWND workerW = nullptr;
    while ((workerW = FindWindowExW(nullptr, workerW, L"WorkerW", nullptr)) != nullptr) {
        if (FindWindowExW(workerW, nullptr, L"SHELLDLL_DefView", nullptr)) {
            return workerW;
        }
    }
    return progman;
}

void PositionOverlayBelowIcons(HWND overlay, const std::wstring& mode) {
    if (!overlay) return;
    HWND insertAfter = HWND_BOTTOM;
    if (mode == L"auto") {
        HWND host = FindShellDefViewHost();
        if (host) insertAfter = host;
    } else if (mode == L"progman_direct") {
        HWND progman = FindWindowW(L"Progman", nullptr);
        if (progman) insertAfter = progman;
    }
    SetWindowPos(
        overlay,
        insertAfter,
        g_canvasLeft,
        g_canvasTop,
        g_canvasWidth,
        g_canvasHeight,
        SWP_NOACTIVATE | SWP_SHOWWINDOW);
}

LRESULT CALLBACK OverlayWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (msg == WM_ERASEBKGND) return 1;
    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

int GetIntensityForKind(const Settings& cfg, ObjectKind kind, bool isSeasonal) {
    if (!isSeasonal) {
        if (kind == ObjectKind::Rain) return cfg.rainIntensity;
        if (kind == ObjectKind::Snow) return cfg.snowIntensity;
        if (kind == ObjectKind::Hail) return cfg.hailIntensity;
    } else {
        if (kind == ObjectKind::AutumnLeaves) return cfg.autumnLeavesIntensity;
        if (kind == ObjectKind::ExtraSnow) return cfg.extraSnowIntensity;
        if (kind == ObjectKind::Petals) return cfg.petalsIntensity;
    }
    return 25;
}

int GetMaxAccumulatedForKind(const Settings& cfg, ObjectKind kind, bool isSeasonal) {
    if (!isSeasonal) {
        if (kind == ObjectKind::Rain) return cfg.rainMaxAccumulated;
        if (kind == ObjectKind::Snow) return cfg.snowMaxAccumulated;
        if (kind == ObjectKind::Hail) return cfg.hailMaxAccumulated;
    } else {
        if (kind == ObjectKind::AutumnLeaves) return cfg.autumnLeavesMaxAccumulated;
        if (kind == ObjectKind::ExtraSnow) return cfg.extraSnowMaxAccumulated;
        if (kind == ObjectKind::Petals) return cfg.petalsMaxAccumulated;
    }
    return 0;
}

double GetLifetimeMinForKind(const Settings& cfg, ObjectKind kind, bool isSeasonal) {
    if (!isSeasonal) {
        if (kind == ObjectKind::Rain) return cfg.rainLifetimeMin;
        if (kind == ObjectKind::Snow) return cfg.snowLifetimeMin;
        if (kind == ObjectKind::Hail) return cfg.hailLifetimeMin;
    } else {
        if (kind == ObjectKind::AutumnLeaves) return cfg.autumnLeavesLifetimeMin;
        if (kind == ObjectKind::ExtraSnow) return cfg.extraSnowLifetimeMin;
        if (kind == ObjectKind::Petals) return cfg.petalsLifetimeMin;
    }
    return -1.0;
}

D2D1_COLOR_F GetColorForKind(const Settings& cfg, ObjectKind kind) {
    switch (kind) {
        case ObjectKind::Rain: return cfg.colorRain;
        case ObjectKind::Snow: return cfg.colorSnow;
        case ObjectKind::Hail: return cfg.colorHail;
        case ObjectKind::AutumnLeaves: return cfg.colorAutumnLeaves;
        case ObjectKind::ExtraSnow: return cfg.colorExtraSnow;
        case ObjectKind::Petals: return cfg.colorPetals;
    }
    return cfg.colorSnow;
}

void SpawnFallingItem(FallingItem& item, std::mt19937& rng, ObjectKind kind, bool isSeasonal,
                      double scale, bool randomY) {
    std::uniform_real_distribution<float> xDist(-60.0f, static_cast<float>(g_canvasWidth) + 60.0f);
    std::uniform_real_distribution<float> yDist(0.0f, static_cast<float>(g_canvasHeight));
    std::uniform_real_distribution<float> phaseDist(0.0f, 6.2831853f);
    std::uniform_real_distribution<float> alphaDist(0.68f, 0.96f);

    item.kind = kind;
    item.isSeasonalLayer = isSeasonal;
    item.x = xDist(rng);
    item.y = randomY ? yDist(rng) : -24.0f;
    item.swayPhase = phaseDist(rng);
    item.angle = phaseDist(rng);
    item.alpha = alphaDist(rng);

    float s = static_cast<float>(scale);
    if (kind == ObjectKind::Rain) {
        item.size = 13.0f * s;
        item.spin = 0.0f;
    } else if (kind == ObjectKind::Hail) {
        item.size = (5.5f + (rng() % 30) * 0.1f) * s;
        item.spin = ((rng() % 100) - 50) * 0.05f;
    } else if (kind == ObjectKind::Petals) {
        item.size = (8.0f + (rng() % 35) * 0.1f) * s;
        item.spin = ((rng() % 100) - 50) * 0.04f;
    } else if (kind == ObjectKind::AutumnLeaves) {
        item.size = (9.5f + (rng() % 45) * 0.1f) * s;
        item.spin = ((rng() % 100) - 50) * 0.05f;
    } else {
        item.size = (5.5f + (rng() % 40) * 0.1f) * s;
        item.spin = ((rng() % 100) - 50) * 0.025f;
    }
}

void DrawItemShape(ID2D1DCRenderTarget* rt, ID2D1SolidColorBrush* brush,
                   ObjectKind kind, float x, float y, float size, float angle, float vx, float alpha) {
    brush->SetOpacity(std::clamp(alpha, 0.05f, 1.0f));
    if (kind == ObjectKind::Rain) {
        rt->DrawLine(D2D1::Point2F(x, y), D2D1::Point2F(x + vx * 0.02f, y + size), brush, 1.5f);
        return;
    }

    D2D1::Matrix3x2F oldXform;
    rt->GetTransform(&oldXform);
    rt->SetTransform(D2D1::Matrix3x2F::Rotation(angle * 57.29578f, D2D1::Point2F(x, y)) * oldXform);

    if (kind == ObjectKind::Petals) {
        rt->FillEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), size * 0.65f, size * 0.35f), brush);
    } else if (kind == ObjectKind::AutumnLeaves) {
        rt->FillEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), size * 0.78f, size * 0.38f), brush);
    } else if (kind == ObjectKind::Hail) {
        rt->FillRectangle(D2D1::RectF(x - size * 0.45f, y - size * 0.45f, x + size * 0.45f, y + size * 0.45f), brush);
    } else {
        rt->FillEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), size * 0.5f, size * 0.5f), brush);
    }

    rt->SetTransform(oldXform);
}

void DrawRainPuddle(ID2D1DCRenderTarget* rt, ID2D1SolidColorBrush* brush, float x, float y, float size, float alpha) {
    brush->SetOpacity(std::clamp(alpha * 0.55f, 0.05f, 0.75f));
    float width = std::max(8.0f, size * 1.4f);
    float height = 2.0f;
    rt->FillEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), width * 0.5f, height * 0.5f), brush);
}

void CleanupSurfaceResources() {
    if (g_dcRenderTarget) {
        g_dcRenderTarget->Release();
        g_dcRenderTarget = nullptr;
    }
    if (g_memDC) {
        if (g_oldBitmap) {
            SelectObject(g_memDC, g_oldBitmap);
            g_oldBitmap = nullptr;
        }
        DeleteDC(g_memDC);
        g_memDC = nullptr;
    }
    if (g_dibBitmap) {
        DeleteObject(g_dibBitmap);
        g_dibBitmap = nullptr;
    }
    g_dibWidth = 0;
    g_dibHeight = 0;
}

bool EnsureLayeredSurface(int width, int height) {
    if (!g_d2dFactory) {
        D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &g_d2dFactory);
    }
    if (!g_d2dFactory) return false;

    if (g_dcRenderTarget && g_memDC && g_dibBitmap && g_dibWidth == width && g_dibHeight == height) {
        return true;
    }

    CleanupSurfaceResources();

    HDC screenDC = GetDC(nullptr);
    g_memDC = CreateCompatibleDC(screenDC);
    ReleaseDC(nullptr, screenDC);
    if (!g_memDC) return false;

    BITMAPINFO bmi = {};
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = width;
    bmi.bmiHeader.biHeight = -height;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biCompression = BI_RGB;

    void* bits = nullptr;
    g_dibBitmap = CreateDIBSection(g_memDC, &bmi, DIB_RGB_COLORS, &bits, nullptr, 0);
    if (!g_dibBitmap) {
        CleanupSurfaceResources();
        return false;
    }

    g_oldBitmap = SelectObject(g_memDC, g_dibBitmap);
    g_dibWidth = width;
    g_dibHeight = height;

    D2D1_RENDER_TARGET_PROPERTIES props = D2D1::RenderTargetProperties(
        D2D1_RENDER_TARGET_TYPE_DEFAULT,
        D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED));

    if (FAILED(g_d2dFactory->CreateDCRenderTarget(&props, &g_dcRenderTarget)) || !g_dcRenderTarget) {
        CleanupSurfaceResources();
        return false;
    }
    return true;
}

void DrawVerticalGradientTint(ID2D1DCRenderTarget* rt, D2D1_COLOR_F topCol, D2D1_COLOR_F botCol,
                              float topY, float botY, float factor) {
    topCol.a = std::clamp(topCol.a * factor, 0.0f, 0.85f);
    botCol.a = std::clamp(botCol.a * factor, 0.0f, 0.85f);
    if (topCol.a <= 0.003f && botCol.a <= 0.003f) return;

    D2D1_GRADIENT_STOP stops[2] = {
        {0.0f, topCol},
        {1.0f, botCol}
    };
    ID2D1GradientStopCollection* stopCol = nullptr;
    if (FAILED(rt->CreateGradientStopCollection(stops, 2, D2D1_GAMMA_2_2, D2D1_EXTEND_MODE_CLAMP, &stopCol)) || !stopCol) {
        return;
    }
    ID2D1LinearGradientBrush* grad = nullptr;
    if (SUCCEEDED(rt->CreateLinearGradientBrush(
            D2D1::LinearGradientBrushProperties(D2D1::Point2F(0.0f, topY), D2D1::Point2F(0.0f, botY)),
            stopCol, &grad)) && grad) {
        rt->FillRectangle(D2D1::RectF(0.0f, topY, static_cast<float>(g_canvasWidth), botY), grad);
        grad->Release();
    }
    stopCol->Release();
}

void DrawSmoothRainbow(ID2D1DCRenderTarget* rt, const Settings& cfg, float strength, double timeSec) {
    if (cfg.rainbowRadius <= 0 || strength <= 0.004f) return;

    float minSide = static_cast<float>(std::min(g_canvasWidth, g_canvasHeight));
    float radius = minSide * (static_cast<float>(cfg.rainbowRadius) / 100.0f);
    if (radius < 4.0f) return;

    // X: 0..100 слева направо; Y: 0..100 снизу вверх
    float cx = static_cast<float>(g_canvasWidth) * (static_cast<float>(cfg.rainbowCenterX) / 100.0f);
    float cy = static_cast<float>(g_canvasHeight) * (1.0f - static_cast<float>(cfg.rainbowCenterY) / 100.0f);

    const D2D1_COLOR_F spectrum[6] = {
        D2D1::ColorF(1.0f, 0.22f, 0.28f, 0.24f),
        D2D1::ColorF(1.0f, 0.58f, 0.15f, 0.24f),
        D2D1::ColorF(1.0f, 0.90f, 0.20f, 0.24f),
        D2D1::ColorF(0.20f, 0.85f, 0.42f, 0.24f),
        D2D1::ColorF(0.22f, 0.62f, 1.0f, 0.24f),
        D2D1::ColorF(0.60f, 0.34f, 0.96f, 0.24f)
    };

    float bandThickness = std::max(4.0f, radius * 0.035f);
    float shimmer = 0.92f + 0.08f * static_cast<float>(std::sin(timeSec * 1.4));

    for (int i = 0; i < 6; ++i) {
        D2D1_COLOR_F c = cfg.hasCustomRainbowColor ? cfg.colorRainbow : spectrum[i];
        float bandFade = 1.0f - std::abs(i - 2.5f) * 0.14f;
        c.a = std::clamp(c.a * strength * bandFade * shimmer, 0.0f, 0.65f);
        if (c.a <= 0.003f) continue;

        float r = radius - i * (bandThickness * 0.85f);
        if (r <= 2.0f) break;

        ID2D1SolidColorBrush* b = nullptr;
        if (SUCCEEDED(rt->CreateSolidColorBrush(c, &b)) && b) {
            rt->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(cx, cy), r, r), b, bandThickness);
            b->Release();
        }
    }
}

void DrawSmoothHalo(ID2D1DCRenderTarget* rt, const Settings& cfg, float strength, double timeSec) {
    if (cfg.haloRadius <= 0 || strength <= 0.004f) return;

    float minSide = static_cast<float>(std::min(g_canvasWidth, g_canvasHeight));
    float radius = minSide * (static_cast<float>(cfg.haloRadius) / 100.0f);
    if (radius < 4.0f) return;

    float cx = static_cast<float>(g_canvasWidth) * (static_cast<float>(cfg.haloCenterX) / 100.0f);
    float cy = static_cast<float>(g_canvasHeight) * (1.0f - static_cast<float>(cfg.haloCenterY) / 100.0f);

    D2D1_COLOR_F base = cfg.hasCustomHaloColor ? cfg.colorHalo : D2D1::ColorF(1.0f, 0.96f, 0.84f, 0.30f);
    float pulse = 0.94f + 0.06f * static_cast<float>(std::sin(timeSec * 1.8));

    // Мягкое радиальное свечение внутри ореола + тонкое кольцо на границе радиуса
    D2D1_COLOR_F innerCol = base;
    innerCol.a = std::clamp(base.a * 0.35f * strength * pulse, 0.0f, 0.5f);
    D2D1_COLOR_F outerCol = base;
    outerCol.a = 0.0f;

    D2D1_GRADIENT_STOP stops[2] = {
        {0.0f, innerCol},
        {1.0f, outerCol}
    };
    ID2D1GradientStopCollection* stopsCol = nullptr;
    if (SUCCEEDED(rt->CreateGradientStopCollection(stops, 2, D2D1_GAMMA_2_2, D2D1_EXTEND_MODE_CLAMP, &stopsCol)) && stopsCol) {
        ID2D1RadialGradientBrush* radBrush = nullptr;
        if (SUCCEEDED(rt->CreateRadialGradientBrush(
                D2D1::RadialGradientBrushProperties(D2D1::Point2F(cx, cy), D2D1::Point2F(0.0f, 0.0f), radius, radius),
                stopsCol, &radBrush)) && radBrush) {
            rt->FillEllipse(D2D1::Ellipse(D2D1::Point2F(cx, cy), radius, radius), radBrush);
            radBrush->Release();
        }
        stopsCol->Release();
    }

    D2D1_COLOR_F ringCol = base;
    ringCol.a = std::clamp(base.a * 0.85f * strength * pulse, 0.0f, 0.75f);
    ID2D1SolidColorBrush* ringBrush = nullptr;
    if (SUCCEEDED(rt->CreateSolidColorBrush(ringCol, &ringBrush)) && ringBrush) {
        rt->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(cx, cy), radius, radius), ringBrush, std::max(2.0f, radius * 0.025f));
        ringBrush->Release();
    }
}

void DrawSmoothAurora(ID2D1DCRenderTarget* rt, const Settings& cfg, float strength, double timeSec) {
    if (strength <= 0.004f) return;
    D2D1_COLOR_F base = cfg.hasCustomAuroraColor ? cfg.colorAurora : D2D1::ColorF(0.20f, 0.94f, 0.62f, 0.28f);
    float bandHeight = std::max(90.0f, static_cast<float>(g_canvasHeight) * 0.22f);

    for (int ribbon = 0; ribbon < 2; ++ribbon) {
        D2D1_COLOR_F cTop = base;
        cTop.a = std::clamp(base.a * (ribbon == 0 ? 1.0f : 0.65f) * strength, 0.0f, 0.65f);
        D2D1_COLOR_F cBot = cTop;
        cBot.a = 0.0f;

        float y0 = (ribbon == 0) ? 16.0f : 44.0f;
        float y1 = y0 + bandHeight;
        DrawVerticalGradientTint(rt, cTop, cBot, y0, y1, 1.0f);

        ID2D1SolidColorBrush* waveBrush = nullptr;
        D2D1_COLOR_F waveCol = cTop;
        waveCol.a = std::clamp(cTop.a * 1.15f, 0.0f, 0.75f);
        if (SUCCEEDED(rt->CreateSolidColorBrush(waveCol, &waveBrush)) && waveBrush) {
            float prevX = 0.0f;
            float prevY = y0 + static_cast<float>(std::sin(timeSec * 1.1 + ribbon)) * 14.0f;
            for (float x = 24.0f; x <= static_cast<float>(g_canvasWidth); x += 24.0f) {
                float curY = y0 + static_cast<float>(std::sin(x * 0.0045f + timeSec * (1.1 + ribbon * 0.3))) * 18.0f;
                rt->DrawLine(D2D1::Point2F(prevX, prevY), D2D1::Point2F(x, curY), waveBrush, 3.0f);
                prevX = x;
                prevY = curY;
            }
            waveBrush->Release();
        }
    }
}

void DrawSmoothMirage(ID2D1DCRenderTarget* rt, const Settings& cfg, float strength, int bottomLimitY, double timeSec) {
    if (strength <= 0.004f) return;
    float botY = static_cast<float>(bottomLimitY - g_canvasTop);
    float bandH = std::max(50.0f, static_cast<float>(g_canvasHeight) * 0.14f);
    float topY = std::max(0.0f, botY - bandH);

    D2D1_COLOR_F base = cfg.hasCustomMirageColor ? cfg.colorMirage : D2D1::ColorF(1.0f, 0.88f, 0.68f, 0.25f);
    D2D1_COLOR_F topCol = base;
    topCol.a = 0.0f;
    D2D1_COLOR_F botCol = base;
    botCol.a = std::clamp(base.a * strength, 0.0f, 0.55f);

    DrawVerticalGradientTint(rt, topCol, botCol, topY, botY, 1.0f);

    ID2D1SolidColorBrush* shimmerBrush = nullptr;
    D2D1_COLOR_F shCol = base;
    shCol.a = std::clamp(base.a * 0.75f * strength, 0.0f, 0.5f);
    if (SUCCEEDED(rt->CreateSolidColorBrush(shCol, &shimmerBrush)) && shimmerBrush) {
        for (int line = 0; line < 3; ++line) {
            float baseLineY = topY + bandH * (0.35f + line * 0.25f);
            float prevX = 0.0f;
            float prevY = baseLineY + static_cast<float>(std::sin(timeSec * 2.4 + line * 1.7)) * 3.0f;
            for (float x = 20.0f; x <= static_cast<float>(g_canvasWidth); x += 20.0f) {
                float curY = baseLineY + static_cast<float>(std::sin(x * 0.012f + timeSec * 2.4 + line * 1.7)) * 3.5f;
                rt->DrawLine(D2D1::Point2F(prevX, prevY), D2D1::Point2F(x, curY), shimmerBrush, 1.5f);
                prevX = x;
                prevY = curY;
            }
        }
        shimmerBrush->Release();
    }
}

void RenderFrame(const Settings& cfg, const GeneralEffectsState& fx, int bottomLimitY, float precipVx, double timeSec) {
    if (!g_overlayHwnd || !IsWindow(g_overlayHwnd)) return;
    if (!EnsureLayeredSurface(g_canvasWidth, g_canvasHeight)) return;

    RECT bindRect = {0, 0, g_canvasWidth, g_canvasHeight};
    g_dcRenderTarget->BindDC(g_memDC, &bindRect);

    g_dcRenderTarget->BeginDraw();
    g_dcRenderTarget->Clear(D2D1::ColorF(0.0f, 0.0f, 0.0f, 0.0f));

    float k = static_cast<float>(cfg.effectsIntensity) / 25.0f;
    float hFloat = static_cast<float>(g_canvasHeight);

    if (fx.clear) {
        D2D1_COLOR_F cTop = cfg.hasCustomClearColor ? cfg.colorClear : D2D1::ColorF(1.0f, 0.94f, 0.72f, 0.16f);
        D2D1_COLOR_F cBot = cTop;
        cBot.a *= 0.2f;
        DrawVerticalGradientTint(g_dcRenderTarget, cTop, cBot, 0.0f, hFloat, k);
    }
    if (fx.partlyCloudy) {
        D2D1_COLOR_F cTop = cfg.hasCustomPartlyCloudyColor ? cfg.colorPartlyCloudy : D2D1::ColorF(0.90f, 0.93f, 0.97f, 0.18f);
        D2D1_COLOR_F cBot = cTop;
        cBot.a *= 0.35f;
        DrawVerticalGradientTint(g_dcRenderTarget, cTop, cBot, 0.0f, hFloat, k);
    }
    if (fx.overcast) {
        D2D1_COLOR_F cTop = cfg.hasCustomOvercastColor ? cfg.colorOvercast : D2D1::ColorF(0.50f, 0.55f, 0.62f, 0.28f);
        D2D1_COLOR_F cBot = cTop;
        cBot.a *= 0.65f;
        DrawVerticalGradientTint(g_dcRenderTarget, cTop, cBot, 0.0f, hFloat, k);
    }
    if (fx.dust) {
        D2D1_COLOR_F cTop = cfg.hasCustomDustColor ? cfg.colorDust : D2D1::ColorF(0.84f, 0.68f, 0.45f, 0.10f);
        D2D1_COLOR_F cBot = cfg.hasCustomDustColor ? cfg.colorDust : D2D1::ColorF(0.84f, 0.68f, 0.45f, 0.26f);
        DrawVerticalGradientTint(g_dcRenderTarget, cTop, cBot, 0.0f, hFloat, k);
    }
    if (fx.fog) {
        D2D1_COLOR_F cTop = cfg.hasCustomFogColor ? cfg.colorFog : D2D1::ColorF(0.84f, 0.88f, 0.92f, 0.14f);
        D2D1_COLOR_F cBot = cfg.hasCustomFogColor ? cfg.colorFog : D2D1::ColorF(0.84f, 0.88f, 0.92f, 0.34f);
        DrawVerticalGradientTint(g_dcRenderTarget, cTop, cBot, 0.0f, hFloat, k);
    }
    if (fx.smog) {
        D2D1_COLOR_F cTop = cfg.hasCustomSmogColor ? cfg.colorSmog : D2D1::ColorF(0.54f, 0.48f, 0.40f, 0.16f);
        D2D1_COLOR_F cBot = cfg.hasCustomSmogColor ? cfg.colorSmog : D2D1::ColorF(0.54f, 0.48f, 0.40f, 0.36f);
        DrawVerticalGradientTint(g_dcRenderTarget, cTop, cBot, 0.0f, hFloat, k);
    }
    if (fx.aurora) {
        DrawSmoothAurora(g_dcRenderTarget, cfg, k, timeSec);
    }
    if (fx.mirage) {
        DrawSmoothMirage(g_dcRenderTarget, cfg, k, bottomLimitY, timeSec);
    }
    if (fx.rainbow) {
        DrawSmoothRainbow(g_dcRenderTarget, cfg, k, timeSec);
    }
    if (fx.halo) {
        DrawSmoothHalo(g_dcRenderTarget, cfg, k, timeSec);
    }
    if (fx.thunderstorm && g_lightning.timer > 0.0f) {
        D2D1_COLOR_F tc = cfg.hasCustomThunderstormColor ? cfg.colorThunderstorm : D2D1::ColorF(0.86f, 0.93f, 1.0f, 0.95f);
        tc.a = std::clamp(g_lightning.timer * 4.2f * std::max(0.25f, k), 0.0f, 1.0f);
        ID2D1SolidColorBrush* tb = nullptr;
        if (SUCCEEDED(g_dcRenderTarget->CreateSolidColorBrush(tc, &tb)) && tb) {
            float curX = g_lightning.xStart;
            float curY = 0.0f;
            int segs = 14;
            float stepY = std::max(20.0f, (bottomLimitY - g_canvasTop) * 0.72f / segs);
            for (int i = 0; i < segs; ++i) {
                float t = static_cast<float>(i + 1) / segs;
                float nextX = g_lightning.xStart + (g_lightning.xEnd - g_lightning.xStart) * t + ((i % 2 == 0) ? 16.0f : -16.0f);
                float nextY = curY + stepY;
                g_dcRenderTarget->DrawLine(D2D1::Point2F(curX, curY), D2D1::Point2F(nextX, nextY), tb, 2.8f);
                curX = nextX;
                curY = nextY;
            }
            tb->Release();
        }
    }

    ID2D1SolidColorBrush* brush = nullptr;
    if (SUCCEEDED(g_dcRenderTarget->CreateSolidColorBrush(D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.0f), &brush)) && brush) {
        for (const auto& p : g_falling) {
            brush->SetColor(GetColorForKind(cfg, p.kind));
            DrawItemShape(g_dcRenderTarget, brush, p.kind, p.x, p.y, p.size, p.angle, precipVx, p.alpha);
        }

        float bottomRelY = static_cast<float>(bottomLimitY - g_canvasTop);
        for (const auto& fo : g_fallen) {
            float drawX = fo.relX;
            float drawY = fo.relY;
            if (fo.onWindow) {
                auto it = g_windows.find(fo.hostWindow);
                if (it == g_windows.end()) continue;
                drawX = static_cast<float>(it->second.rect.left - g_canvasLeft) + fo.relX;
                drawY = static_cast<float>(it->second.rect.top - g_canvasTop) + fo.relY;
            } else if (!fo.fallingOff) {
                drawY = bottomRelY + fo.relY;
            }
            brush->SetColor(GetColorForKind(cfg, fo.kind));
            if (!fo.onWindow && !fo.fallingOff && fo.kind == ObjectKind::Rain) {
                DrawRainPuddle(g_dcRenderTarget, brush, drawX, bottomRelY - 1.0f, fo.size, fo.alpha);
            } else {
                DrawItemShape(g_dcRenderTarget, brush, fo.kind, drawX, drawY, fo.size, fo.angle, fo.vx, fo.alpha);
            }
        }

        brush->Release();
    }

    if (FAILED(g_dcRenderTarget->EndDraw())) {
        CleanupSurfaceResources();
        return;
    }

    POINT ptDst = {g_canvasLeft, g_canvasTop};
    SIZE sizeWnd = {g_canvasWidth, g_canvasHeight};
    POINT ptSrc = {0, 0};
    BLENDFUNCTION blend = {};
    blend.BlendOp = AC_SRC_OVER;
    blend.SourceConstantAlpha = 255;
    blend.AlphaFormat = AC_SRC_ALPHA;

    UpdateLayeredWindow(g_overlayHwnd, nullptr, &ptDst, &sizeWnd, g_memDC, &ptSrc, 0, &blend, ULW_ALPHA);
}

float ComputeHorizontalSpeedPxPerSec(FallDirMode dirMode, double mpsSpeed, int forecastSign, double forecastWindKmh) {
    float basePx = static_cast<float>(mpsSpeed) * 26.0f;
    if (dirMode == FallDirMode::Down) return 0.0f;
    if (dirMode == FallDirMode::DownLeft) return -basePx;
    if (dirMode == FallDirMode::DownRight) return basePx;

    if (forecastSign == 0 || forecastWindKmh <= 0.2) return 0.0f;
    float windFactor = std::clamp(static_cast<float>(forecastWindKmh) / 20.0f, 0.25f, 2.5f);
    return static_cast<float>(forecastSign) * basePx * windFactor;
}

void RenderWorkerLoop() {
    WNDCLASSEXW wc = {};
    wc.cbSize = sizeof(wc);
    wc.lpfnWndProc = OverlayWndProc;
    wc.hInstance = GetModuleHandleW(nullptr);
    wc.lpszClassName = L"WindhawkDesktopWeatherOverlayClass";
    RegisterClassExW(&wc);

    std::mt19937 rng(static_cast<unsigned>(GetTickCount64()));
    auto startTime = std::chrono::steady_clock::now();
    auto lastTime = startTime;
    int zOrderTick = 0;

    POINT prevCursorPt = {};
    GetCursorPos(&prevCursorPt);
    bool hasPrevCursor = true;

    while (g_running.load()) {
        Settings cfg;
        bool hasForecastP = false;
        ObjectKind forecastP = ObjectKind::Rain;
        GeneralEffectsState forecastFx;
        double forecastWindSpd = 0.0;
        int forecastWindSign = 0;
        {
            std::lock_guard<std::mutex> lock(g_mutex);
            cfg = g_settings;
            hasForecastP = g_hasForecastPrecip;
            forecastP = g_forecastPrecip;
            forecastFx = g_forecastEffects;
            forecastWindSpd = g_forecastWindSpeedKmh;
            forecastWindSign = g_forecastWindDirSign;
        }

        if (cfg.pauseOnFullscreen && IsFullscreenAppActive()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(250));
            lastTime = std::chrono::steady_clock::now();
            continue;
        }

        UpdateCanvasGeometry(cfg);

        if (!g_overlayHwnd) {
            DWORD exStyle = WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_NOACTIVATE | WS_EX_TOOLWINDOW;
            g_overlayHwnd = CreateWindowExW(
                exStyle, wc.lpszClassName, L"DesktopWeatherOverlay", WS_POPUP,
                g_canvasLeft, g_canvasTop, g_canvasWidth, g_canvasHeight,
                nullptr, nullptr, wc.hInstance, nullptr);
            PositionOverlayBelowIcons(g_overlayHwnd, cfg.layerAttachMode);
        } else if (++zOrderTick >= 30) {
            zOrderTick = 0;
            PositionOverlayBelowIcons(g_overlayHwnd, cfg.layerAttachMode);
        }

        MSG msg;
        while (PeekMessageW(&msg, g_overlayHwnd, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        }

        auto now = std::chrono::steady_clock::now();
        float dt = std::chrono::duration<float>(now - lastTime).count();
        double timeSec = std::chrono::duration<double>(now - startTime).count();
        lastTime = now;
        dt = std::clamp(dt, 0.001f, 0.05f);

        bool activePrecip = false;
        ObjectKind precipKind = ObjectKind::Rain;
        if (cfg.precipitationMode == PrecipMode::Rain) { activePrecip = true; precipKind = ObjectKind::Rain; }
        else if (cfg.precipitationMode == PrecipMode::Snow) { activePrecip = true; precipKind = ObjectKind::Snow; }
        else if (cfg.precipitationMode == PrecipMode::Hail) { activePrecip = true; precipKind = ObjectKind::Hail; }
        else if (cfg.precipitationMode == PrecipMode::Auto && hasForecastP) { activePrecip = true; precipKind = forecastP; }

        bool activeSeasonal = false;
        ObjectKind seasonalKind = ObjectKind::AutumnLeaves;
        if (cfg.seasonalObjectMode == SeasonalMode::AutumnLeaves) { activeSeasonal = true; seasonalKind = ObjectKind::AutumnLeaves; }
        else if (cfg.seasonalObjectMode == SeasonalMode::ExtraSnow) { activeSeasonal = true; seasonalKind = ObjectKind::ExtraSnow; }
        else if (cfg.seasonalObjectMode == SeasonalMode::Petals) { activeSeasonal = true; seasonalKind = ObjectKind::Petals; }
        else if (cfg.seasonalObjectMode == SeasonalMode::Auto) {
            SeasonalMode detected = DetectSeasonByDates(cfg);
            if (detected == SeasonalMode::AutumnLeaves) { activeSeasonal = true; seasonalKind = ObjectKind::AutumnLeaves; }
            else if (detected == SeasonalMode::ExtraSnow) { activeSeasonal = true; seasonalKind = ObjectKind::ExtraSnow; }
            else if (detected == SeasonalMode::Petals) { activeSeasonal = true; seasonalKind = ObjectKind::Petals; }
        }

        auto resolveEffect = [&](TriStateMode mode, bool autoVal) -> bool {
            if (mode == TriStateMode::On) return true;
            if (mode == TriStateMode::Off) return false;
            return autoVal;
        };
        GeneralEffectsState activeFx;
        activeFx.clear = resolveEffect(cfg.effectClear, forecastFx.clear);
        activeFx.partlyCloudy = resolveEffect(cfg.effectPartlyCloudy, forecastFx.partlyCloudy);
        activeFx.overcast = resolveEffect(cfg.effectOvercast, forecastFx.overcast);
        activeFx.dust = resolveEffect(cfg.effectDust, forecastFx.dust);
        activeFx.fog = resolveEffect(cfg.effectFog, forecastFx.fog);
        activeFx.smog = resolveEffect(cfg.effectSmog, forecastFx.smog);
        activeFx.thunderstorm = resolveEffect(cfg.effectThunderstorm, forecastFx.thunderstorm);
        activeFx.aurora = resolveEffect(cfg.effectAurora, forecastFx.aurora);
        activeFx.mirage = resolveEffect(cfg.effectMirage, forecastFx.mirage);
        activeFx.rainbow = resolveEffect(cfg.effectRainbow, forecastFx.rainbow);
        activeFx.halo = resolveEffect(cfg.effectHalo, forecastFx.halo);

        if (activeFx.thunderstorm) {
            if (g_lightning.timer > 0.0f) {
                g_lightning.timer = std::max(0.0f, g_lightning.timer - dt);
            } else if ((static_cast<float>(rng() % 10000) / 10000.0f) < 0.35f * dt) {
                g_lightning.timer = 0.22f;
                g_lightning.xStart = static_cast<float>(100 + rng() % std::max(120, g_canvasWidth - 200));
                g_lightning.xEnd = g_lightning.xStart + static_cast<float>((rng() % 160) - 80);
            }
        } else {
            g_lightning.timer = 0.0f;
        }

        float precipVx = ComputeHorizontalSpeedPxPerSec(cfg.precipFallDirection, cfg.precipFallSpeedMps, forecastWindSign, forecastWindSpd);
        float precipVy = static_cast<float>(cfg.precipFallSpeedMps) * 42.0f * static_cast<float>(cfg.particleScale);

        float seasonalVx = ComputeHorizontalSpeedPxPerSec(cfg.seasonalFallDirection, cfg.seasonalFallSpeedMps, forecastWindSign, forecastWindSpd);
        float seasonalVy = static_cast<float>(cfg.seasonalFallSpeedMps) * 32.0f * static_cast<float>(cfg.particleScale);

        size_t targetP = activePrecip
            ? static_cast<size_t>((g_canvasWidth / 1000.0) * GetIntensityForKind(cfg, precipKind, false) * 1.4)
            : 0;
        size_t targetS = activeSeasonal
            ? static_cast<size_t>((g_canvasWidth / 1000.0) * GetIntensityForKind(cfg, seasonalKind, true) * 1.2)
            : 0;

        std::vector<FallingItem> nextFalling;
        nextFalling.reserve(targetP + targetS);
        size_t curP = 0, curS = 0;

        for (const auto& item : g_falling) {
            if (!item.isSeasonalLayer && activePrecip && item.kind == precipKind && curP < targetP) {
                nextFalling.push_back(item);
                ++curP;
            } else if (item.isSeasonalLayer && activeSeasonal && item.kind == seasonalKind && curS < targetS) {
                nextFalling.push_back(item);
                ++curS;
            }
        }
        while (curP < targetP) {
            FallingItem it;
            SpawnFallingItem(it, rng, precipKind, false, cfg.particleScale, true);
            nextFalling.push_back(it);
            ++curP;
        }
        while (curS < targetS) {
            FallingItem it;
            SpawnFallingItem(it, rng, seasonalKind, true, cfg.particleScale, true);
            nextFalling.push_back(it);
            ++curS;
        }
        g_falling.swap(nextFalling);

        std::vector<std::wstring> excluded = SplitExcluded(cfg.excludedProcesses);
        std::vector<HWND> activeHwnds;
        EnumCtx ctx{&excluded, &activeHwnds};
        EnumWindows(EnumWindowsProc, reinterpret_cast<LPARAM>(&ctx));

        float shakeThreshold = 1350.0f - (cfg.windowShakeSensitivity * 11.0f);
        shakeThreshold = std::max(120.0f, shakeThreshold);

        for (HWND h : activeHwnds) {
            RECT r = {};
            if (!GetWindowRect(h, &r)) continue;
            auto& wm = g_windows[h];
            wm.rect = r;
            float cx = (r.left + r.right) * 0.5f;
            float cy = (r.top + r.bottom) * 0.5f;

            if (wm.hasPrev) {
                float vx = (cx - wm.prevCenterX) / dt;
                float vy = (cy - wm.prevCenterY) / dt;
                float speed = std::hypot(vx, vy);
                if (speed > shakeThreshold) {
                    float shedProb = std::clamp((speed - shakeThreshold) / 1800.0f, 0.08f, 0.75f);
                    for (auto& fo : g_fallen) {
                        if (fo.onWindow && fo.hostWindow == h && !fo.fallingOff && fo.kind != ObjectKind::Rain) {
                            if ((rng() % 100) < static_cast<int>(shedProb * 100.0f)) {
                                fo.onWindow = false;
                                fo.fallingOff = true;
                                fo.relX = static_cast<float>(r.left - g_canvasLeft) + fo.relX;
                                fo.relY = static_cast<float>(r.top - g_canvasTop) + fo.relY;
                                fo.vx = vx * 0.18f * static_cast<float>(cfg.windowInertiaFactor);
                                fo.vy = std::max(60.0f, vy * 0.18f);
                            }
                        }
                    }
                }
            }
            wm.prevCenterX = cx;
            wm.prevCenterY = cy;
            wm.hasPrev = true;
        }

        for (auto it = g_windows.begin(); it != g_windows.end();) {
            if (std::find(activeHwnds.begin(), activeHwnds.end(), it->first) == activeHwnds.end()) {
                HWND closedHwnd = it->first;
                RECT lastRect = it->second.rect;
                for (auto& fo : g_fallen) {
                    if (fo.onWindow && fo.hostWindow == closedHwnd) {
                        fo.onWindow = false;
                        fo.fallingOff = true;
                        fo.relX = static_cast<float>(lastRect.left - g_canvasLeft) + fo.relX;
                        fo.relY = static_cast<float>(lastRect.top - g_canvasTop) + fo.relY;
                        fo.vy = 70.0f;
                    }
                }
                it = g_windows.erase(it);
            } else {
                ++it;
            }
        }

        int bottomLimitY = ComputeBottomLimitY(cfg);
        float bottomRelY = static_cast<float>(bottomLimitY - g_canvasTop);

        auto countAccumulated = [&](ObjectKind k, bool isS) -> int {
            int c = 0;
            for (const auto& fo : g_fallen) {
                if (fo.kind == k && fo.isSeasonalLayer == isS) ++c;
            }
            return c;
        };

        for (size_t i = 0; i < g_falling.size(); ++i) {
            FallingItem& p = g_falling[i];
            float vx = p.isSeasonalLayer ? seasonalVx : precipVx;
            float vy = p.isSeasonalLayer ? seasonalVy : precipVy;
            p.swayPhase += dt * 3.0f;
            p.angle += p.spin * dt * 20.0f;

            float sway = (p.kind == ObjectKind::Rain) ? 0.0f : std::sin(p.swayPhase) * 18.0f;
            p.x += (vx + sway) * dt;
            p.y += vy * dt;

            int maxAcc = GetMaxAccumulatedForKind(cfg, p.kind, p.isSeasonalLayer);
            bool landed = false;

            if (maxAcc > 0 && countAccumulated(p.kind, p.isSeasonalLayer) < maxAcc) {
                // На окнах копят только твердые/сезонные объекты (не дождь)
                if (p.kind != ObjectKind::Rain) {
                    for (const auto& kv : g_windows) {
                        const RECT& wr = kv.second.rect;
                        float wLeft = static_cast<float>(wr.left - g_canvasLeft);
                        float wRight = static_cast<float>(wr.right - g_canvasLeft);
                        float wTop = static_cast<float>(wr.top - g_canvasTop);
                        if (p.x >= wLeft + 4.0f && p.x <= wRight - 4.0f && p.y >= wTop - 4.0f && p.y <= wTop + 5.0f) {
                            FallenItem fo;
                            fo.kind = p.kind;
                            fo.isSeasonalLayer = p.isSeasonalLayer;
                            fo.onWindow = true;
                            fo.hostWindow = kv.first;
                            fo.relX = p.x - wLeft;
                            fo.relY = -p.size * 0.35f;
                            fo.size = p.size;
                            fo.angle = p.angle;
                            fo.alpha = p.alpha;
                            g_fallen.push_back(fo);
                            landed = true;
                            break;
                        }
                    }
                }

                if (!landed && p.y >= bottomRelY - p.size * 0.35f) {
                    FallenItem fo;
                    fo.kind = p.kind;
                    fo.isSeasonalLayer = p.isSeasonalLayer;
                    fo.onWindow = false;
                    fo.hostWindow = nullptr;
                    fo.relX = p.x;
                    fo.relY = (p.kind == ObjectKind::Rain) ? -1.0f : (-p.size * 0.35f);
                    fo.size = p.size;
                    fo.angle = p.angle;
                    fo.alpha = p.alpha;
                    g_fallen.push_back(fo);
                    landed = true;
                }
            }

            if (landed || p.y > g_canvasHeight + 30.0f || p.x < -120.0f || p.x > g_canvasWidth + 120.0f) {
                SpawnFallingItem(p, rng, p.kind, p.isSeasonalLayer, cfg.particleScale, false);
            }
        }

        POINT cursorPt = {};
        GetCursorPos(&cursorPt);
        float cX = static_cast<float>(cursorPt.x - g_canvasLeft);
        float cY = static_cast<float>(cursorPt.y - g_canvasTop);
        float cDx = hasPrevCursor ? static_cast<float>(cursorPt.x - prevCursorPt.x) : 0.0f;
        float cDy = hasPrevCursor ? static_cast<float>(cursorPt.y - prevCursorPt.y) : 0.0f;
        prevCursorPt = cursorPt;
        hasPrevCursor = true;

        float cRad = static_cast<float>(cfg.cursorRadiusPx);
        float cMoveLen = std::hypot(cDx, cDy);

        for (size_t i = 0; i < g_fallen.size();) {
            FallenItem& fo = g_fallen[i];
            fo.ageSec += dt;

            double lifeMin = GetLifetimeMinForKind(cfg, fo.kind, fo.isSeasonalLayer);
            if (lifeMin >= 0.0) {
                float lifeSec = static_cast<float>(lifeMin * 60.0);
                if (fo.ageSec >= lifeSec) {
                    fo.alpha -= dt * 1.5f;
                }
                if (fo.alpha <= 0.03f) {
                    g_fallen.erase(g_fallen.begin() + i);
                    continue;
                }
            }

            float absX = fo.relX;
            float absY = fo.relY;
            if (fo.onWindow) {
                auto it = g_windows.find(fo.hostWindow);
                if (it != g_windows.end()) {
                    absX = static_cast<float>(it->second.rect.left - g_canvasLeft) + fo.relX;
                    absY = static_cast<float>(it->second.rect.top - g_canvasTop) + fo.relY;
                }
            } else if (!fo.fallingOff) {
                absY = bottomRelY + fo.relY;
            }

            float dist = std::hypot(absX - cX, absY - cY);
            if (cfg.cursorAction == CursorActionMode::Clear && dist < cRad) {
                g_fallen.erase(g_fallen.begin() + i);
                continue;
            }

            // Для луж дождя внизу экрана не делаем сугробов/кучек при движении
            bool isPuddle = (!fo.onWindow && !fo.fallingOff && fo.kind == ObjectKind::Rain);

            if (cfg.cursorAction == CursorActionMode::Move && !isPuddle && dist > 0.1f && dist < cRad) {
                float weight = (1.0f - dist / cRad);
                float dirX = (cMoveLen > 0.5f) ? (cDx / cMoveLen) : ((absX - cX) / dist);
                float pushSpeed = (cMoveLen > 0.5f) ? std::min(420.0f, cMoveLen * 18.0f + 90.0f) : 140.0f;
                float shiftX = dirX * pushSpeed * weight * dt;

                if (fo.onWindow) {
                    auto it = g_windows.find(fo.hostWindow);
                    if (it != g_windows.end()) {
                        int w = it->second.rect.right - it->second.rect.left;
                        fo.relX = std::clamp(fo.relX + shiftX, 2.0f, static_cast<float>(std::max(3, w - 2)));
                        if (absX + shiftX < it->second.rect.left - g_canvasLeft ||
                            absX + shiftX > it->second.rect.right - g_canvasLeft) {
                            fo.onWindow = false;
                            fo.fallingOff = true;
                            fo.relX = absX + shiftX;
                            fo.relY = absY;
                            fo.vx = dirX * 110.0f;
                            fo.vy = 85.0f;
                        }
                    }
                } else if (!fo.fallingOff) {
                    fo.relX = std::clamp(fo.relX + shiftX, 0.0f, static_cast<float>(g_canvasWidth));
                } else {
                    fo.vx += dirX * weight * 180.0f * dt;
                }
            }

            if (fo.fallingOff) {
                fo.vy += 320.0f * dt;
                fo.relX += fo.vx * dt;
                fo.relY += fo.vy * dt;
                fo.angle += 2.5f * dt;
                if (fo.relY >= bottomRelY - fo.size * 0.35f) {
                    fo.fallingOff = false;
                    fo.onWindow = false;
                    fo.vx = 0.0f;
                    fo.vy = 0.0f;
                    fo.relY = -fo.size * 0.35f;
                }
            }

            ++i;
        }

        RenderFrame(cfg, activeFx, bottomLimitY, precipVx, timeSec);

        int frameMs = 1000 / cfg.targetFps;
        std::this_thread::sleep_for(std::chrono::milliseconds(frameMs));
    }

    if (g_overlayHwnd) {
        DestroyWindow(g_overlayHwnd);
        g_overlayHwnd = nullptr;
    }
    CleanupSurfaceResources();
    if (g_d2dFactory) {
        g_d2dFactory->Release();
        g_d2dFactory = nullptr;
    }
    UnregisterClassW(L"WindhawkDesktopWeatherOverlayClass", GetModuleHandleW(nullptr));
}

} // namespace

BOOL Wh_ModInit() {
    LoadSettingsFromWh();
    g_running.store(true);
    g_weatherThread = std::thread(WeatherWorkerLoop);
    g_renderThread = std::thread(RenderWorkerLoop);
    return TRUE;
}

void Wh_ModUninit() {
    g_running.store(false);
    if (g_weatherThread.joinable()) g_weatherThread.join();
    if (g_renderThread.joinable()) g_renderThread.join();
}

void Wh_ModSettingsChanged() {
    LoadSettingsFromWh();
}