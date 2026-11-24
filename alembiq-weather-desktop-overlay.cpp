// ==WindhawkMod==
// @id              alembiq-weather-desktop-overlay
// @name            Desktop Weather & Particles Overlay
// @description     Weather effects (snow, rain, fog, wind, clear) and seasonal particles (snow, rain, leaves, poplar fluff, sakura) under desktop icons with window accumulation and shake physics.
// @version         0.6.0
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
  $description: "Controls Z-order placement of the main desktop overlay. Allowed: auto, progman_direct, desktop_bottom. Default: auto."
  $options:
    - auto: Auto (below SHELLDLL_DefView icons)
    - progman_direct: Progman reference
    - desktop_bottom: Bottom of Z-order (HWND_BOTTOM)
- bottomBoundaryMode: above_taskbar
  $name: "[System] Bottom boundary mode"
  $description: "Sets bottom reference line for fallen items/puddles. Allowed: above_taskbar, screen_bottom, custom_offset. Default: above_taskbar."
  $options:
    - above_taskbar: Above taskbar (Shell_TrayWnd)
    - screen_bottom: Bottom edge of screen
    - custom_offset: Custom offset from bottom (px)
- bottomOffsetPx: 0
  $name: "[System] Custom bottom offset (px)"
  $description: "Vertical offset in px above bottom edge when bottomBoundaryMode is custom_offset. Range: -500 to 1000. Invalid resets to 0."
- multiMonitorMode: primary
  $name: "[System] Monitors"
  $description: "Render on primary monitor or full virtual screen. Allowed: primary, all. Default: primary."
  $options:
    - primary: Primary monitor
    - all: All monitors (virtual screen)
- targetFps: 60
  $name: "[System] Target FPS (30 or 60)"
  $description: "Target frame rate (30 or 60). Any other value resets to 60."
- pauseOnFullscreen: true
  $name: "[System] Pause on fullscreen apps"
  $description: "Pauses rendering while a fullscreen app is active. Default: true."
- excludedProcesses: "obs64.exe, ApplicationFrameHost.exe"
  $name: "[System] Excluded processes"
  $description: "Comma-separated executable names excluded from window accumulation/shedding."
- cursorAction: clear
  $name: "[System] Cursor action"
  $description: "Affects fallen objects/snow caps only. clear = erase on touch (default); move = 1 snowball & 1 leaf/petal pile per surface; none = ignore cursor."
  $options:
    - clear: Clear (erase on touch)
    - move: Move (1 snowball & 1 pile per surface)
    - none: None (ignore cursor)
- cursorRadiusPx: 95
  $name: "[System] Cursor radius (px)"
  $description: "Cursor action radius in pixels (10 to 500). Invalid/out-of-range resets to 95."

# --- 2. ACCUMULATION TOGGLES ---
- enableBottomAccumulation: true
  $name: "[Accum] Bottom accumulation"
  $description: "Enables/disables accumulation at the bottom boundary. When off (along with window accumulation), nothing accumulates even with side wind."
- enableWindowAccumulation: true
  $name: "[Accum] Window top accumulation"
  $description: "Enables/disables accumulation on top edges of visible windows rendered on a click-through layer above windows."

# --- 3. WEATHER SOURCES & SEASONS ---
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
- coords: "44.7866/20.4489"
  $name: "[Weather] Latitude/Longitude"
  $description: "Format: lat/lon (e.g. 44.7866/20.4489). Latitude -90..90, longitude -180..180. Invalid resets to 44.7866/20.4489."
- customApiUrl: ""
  $name: "[Weather] Custom JSON API URL"
  $description: "HTTP/HTTPS JSON endpoint (weather_code, condition, wind_speed_10m, wind_direction_10m, temperature_2m, cloud_cover, visibility, is_day)."
- localWeatherPath: ""
  $name: "[Weather] Local weather file path"
  $description: "Path to local JSON or text weather file. Default: empty."
- updateIntervalMin: 30
  $name: "[Weather] Update interval (min)"
  $description: "Forecast refresh period in minutes (1 to 1440). Invalid/out-of-range resets to 30."
- seasonsRange: "01.03-31.05/01.06-31.08/01.09-30.11/01.12-29.02"
  $name: "[Seasons] Spring/Summer/Autumn/Winter (DD.MM-DD.MM)"
  $description: "Four DD.MM-DD.MM ranges separated by '/'. Invalid format resets to 01.03-31.05/01.06-31.08/01.09-30.11/01.12-29.02."

# --- 4. PRECIPITATION (RAIN / SNOW / HAIL) ---
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
  $description: "Fall direction for precipitation. Allowed: auto, down, down_left, down_right. Default: auto."
  $options:
    - auto: Auto (forecast)
    - down: Down
    - down_left: Down-left
    - down_right: Down-right
- precipFallSpeedMps: "6.5"
  $name: "[Precip] Fall speed (m/s)"
  $description: "Fall speed in m/s (0.1 to 50.0). Invalid/out-of-range resets to 6.5."
- precipIntensity: 25
  $name: "[Precip] Intensity (%)"
  $description: "Shared intensity for rain, snow, and hail (0..100). Any value outside 0..100 or invalid resets to 25."
- precipMaxAccumulated: 220
  $name: "[Precip] Max accumulated"
  $description: "Shared max accumulated count/cap height scale for precipitation (0..2000; 0 disables). Invalid/out-of-range resets to 220."
- precipLifetimeMin: "10.0"
  $name: "[Precip] Lifetime (min)"
  $description: "Shared auto-disappear/melt time for accumulated precipitation in minutes (-1 to 1440; -1 = never). Invalid resets to 10.0."

# --- 5. SEASONAL OBJECTS (LEAVES / EXTRA SNOW / PETALS) ---
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
- seasonalIntensity: 25
  $name: "[SeasonObj] Intensity (%)"
  $description: "Shared intensity for autumn leaves, extra snow, and petals (0..100). Any value outside 0..100 or invalid resets to 25."
- seasonalMaxAccumulated: 220
  $name: "[SeasonObj] Max accumulated"
  $description: "Shared max accumulated count for seasonal objects (0..2000; 0 disables). Invalid/out-of-range resets to 220."
- seasonalLifetimeMin: "15.0"
  $name: "[SeasonObj] Lifetime (min)"
  $description: "Shared auto-disappear time for accumulated seasonal objects in minutes (-1 to 1440; -1 = never). Invalid resets to 15.0."

# --- 6. GENERAL EFFECTS ---
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
  $description: "Airborne dust haze (auto triggers on strong dry wind or low visibility). Allowed: auto, on, off."
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
  $description: "Smog layer (auto triggers on calm wind with reduced visibility/haze). Allowed: auto, on, off."
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
  $description: "Smooth animated aurora curtains in upper screen area (auto triggers at night with clear/low clouds). Allowed: auto, on, off."
  $options:
    - auto: Auto (forecast)
    - on: On
    - off: Off
- effectMirage: auto
  $name: "[Effects] Mirage"
  $description: "Soft horizon shimmer wave band (auto triggers on hot clear daytime weather). Allowed: auto, on, off."
  $options:
    - auto: Auto (forecast)
    - on: On
    - off: Off
- effectRainbow: auto
  $name: "[Effects] Rainbow"
  $description: "Multi-band rainbow arc (auto triggers on daytime partly-cloudy/post-rain/misty conditions). Allowed: auto, on, off."
  $options:
    - auto: Auto (forecast)
    - on: On
    - off: Off
- rainbowGeometry: "55-50/15"
  $name: "[Rainbow] Radius-Center X/Center Y"
  $description: "Format: radius-centerX/centerY in % (0..100; radius 0 = off, 100 = min(width, height); X left->right, Y bottom->top). Default: 55-50/15."
- effectHalo: auto
  $name: "[Effects] Halo"
  $description: "Soft luminous atmospheric halo ring (auto triggers on thin/mid cloud cover without heavy precip). Allowed: auto, on, off."
  $options:
    - auto: Auto (forecast)
    - on: On
    - off: Off
- haloGeometry: "24-50/72"
  $name: "[Halo] Radius-Center X/Center Y"
  $description: "Format: radius-centerX/centerY in % (0..100; radius 0 = off, 100 = min(width, height); X left->right, Y bottom->top). Default: 24-50/72."

# --- 7. PILES, SNOWBALLS & WINDOW PHYSICS ---
- snowballMaxRadiusPx: 34
  $name: "[Snowballs] Max radius (px)"
  $description: "Maximum radius of the single snowball per surface grown by absorbing snow (8 to 120). Invalid/out-of-range resets to 34."
- leafPileMaxHeightPx: 54
  $name: "[Foliage Piles] Max height (px)"
  $description: "Maximum height of the single leaf/petal mound per surface in pixels (8 to 250). Invalid/out-of-range resets to 54."
- windowShakeSensitivity: 55
  $name: "[Windows] Shed sensitivity (1..100)"
  $description: "Sensitivity for detaching snow caps/fallen items/snowballs when moving/shaking windows (1..100). Invalid/out-of-range resets to 55."
- windowInertiaFactor: "0.75"
  $name: "[Windows] Shed inertia factor"
  $description: "Horizontal & toss inertia transferred to detached snow/items (0.0 to 3.0). Invalid resets to 0.75."
- particleScale: "1.0"
  $name: "[Objects] Size scale"
  $description: "Size multiplier for falling and fallen objects (0.3 to 4.0). Invalid resets to 1.0."

# --- 8. COLORS ---
- colorRain: ""
  $name: "[Color] Rain (#RRGGBB)"
  $description: "Custom HEX (#RRGGBB) or empty for default sky-blue. Invalid HEX resets to default."
- colorSnow: ""
  $name: "[Color] Snow (#RRGGBB)"
  $description: "Custom HEX (#RRGGBB) or empty for default natural white-blue snow. Invalid HEX resets to default."
- colorHail: ""
  $name: "[Color] Hail (#RRGGBB)"
  $description: "Custom HEX (#RRGGBB) or empty for default ice-blue. Invalid HEX resets to default."
- colorAutumnLeaves: ""
  $name: "[Color] Autumn leaves (#RRGGBB)"
  $description: "Custom HEX (#RRGGBB) or empty for default maple orange-amber. Invalid HEX resets to default."
- colorExtraSnow: ""
  $name: "[Color] Extra snow (#RRGGBB)"
  $description: "Custom HEX (#RRGGBB) or empty for default snow-white. Invalid HEX resets to default."
- colorPetals: ""
  $name: "[Color] Petals (#RRGGBB)"
  $description: "Custom HEX (#RRGGBB) or empty for default soft pink. Invalid HEX resets to default."
- colorClear: ""
  $name: "[Color] Clear (#RRGGBB)"
  $description: "Custom HEX (#RRGGBB) or empty for default warm sunlight."
- colorPartlyCloudy: ""
  $name: "[Color] Partly cloudy (#RRGGBB)"
  $description: "Custom HEX (#RRGGBB) or empty for default soft cloud."
- colorOvercast: ""
  $name: "[Color] Overcast (#RRGGBB)"
  $description: "Custom HEX (#RRGGBB) or empty for default slate gray."
- colorDust: ""
  $name: "[Color] Dust (#RRGGBB)"
  $description: "Custom HEX (#RRGGBB) or empty for default sand dust."
- colorFog: ""
  $name: "[Color] Fog (#RRGGBB)"
  $description: "Custom HEX (#RRGGBB) or empty for default mist."
- colorSmog: ""
  $name: "[Color] Smog (#RRGGBB)"
  $description: "Custom HEX (#RRGGBB) or empty for default smog."
- colorThunderstorm: ""
  $name: "[Color] Thunderstorm (#RRGGBB)"
  $description: "Custom HEX (#RRGGBB) or empty for default lightning white-blue."
- colorAurora: ""
  $name: "[Color] Aurora (#RRGGBB)"
  $description: "Custom HEX (#RRGGBB) or empty for default aurora green."
- colorMirage: ""
  $name: "[Color] Mirage (#RRGGBB)"
  $description: "Custom HEX (#RRGGBB) or empty for default warm shimmer."
- colorRainbow: ""
  $name: "[Color] Rainbow (#RRGGBB)"
  $description: "Custom HEX (#RRGGBB) or empty for default multi-color spectrum."
- colorHalo: ""
  $name: "[Color] Halo (#RRGGBB)"
  $description: "Custom HEX (#RRGGBB) or empty for default pale halo."
*/
// ==/WindhawkModSettings==

#include <windows.h>
#include <wininet.h>
#include <d2d1.h>
#include <dwmapi.h>
#include <atomic>
#include <chrono>
#include <cmath>
#include <cstdint>
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

constexpr float kGravity = 2200.0f;
constexpr float kHangSeconds = 0.12f;
constexpr float kTossFactor = 0.5f;
constexpr float kMinTossSpeed = 240.0f;
constexpr float kMaxTossSpeed = 540.0f;
constexpr float kBounceSpeed = 340.0f;
constexpr float kCapEdgeTaper = 8.0f;
constexpr float kSnowKernel[] = {0.10f, 0.25f, 0.50f, 0.80f, 1.00f, 0.80f, 0.50f, 0.25f, 0.10f};
constexpr float kSnowKernelSum = 4.30f;

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
    Clear,
    Move,
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

struct ArcGeometry {
    int radius = 50;
    int centerX = 50;
    int centerY = 50;
};

struct Settings {
    std::wstring layerAttachMode = L"auto";
    std::wstring bottomBoundaryMode = L"above_taskbar";
    int bottomOffsetPx = 0;
    std::wstring multiMonitorMode = L"primary";

    int targetFps = 60;
    bool pauseOnFullscreen = true;
    std::wstring excludedProcesses = L"obs64.exe, ApplicationFrameHost.exe";

    CursorActionMode cursorAction = CursorActionMode::Clear;
    int cursorRadiusPx = 95;

    bool enableBottomAccumulation = true;
    bool enableWindowAccumulation = true;

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

    int precipIntensity = 25;
    int precipMaxAccumulated = 220;
    double precipLifetimeMin = 10.0;

    SeasonalMode seasonalObjectMode = SeasonalMode::Auto;
    FallDirMode seasonalFallDirection = FallDirMode::Auto;
    double seasonalFallSpeedMps = 2.2;

    int seasonalIntensity = 25;
    int seasonalMaxAccumulated = 220;
    double seasonalLifetimeMin = 15.0;

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

    ArcGeometry rainbowGeom{55, 50, 15};
    ArcGeometry haloGeom{24, 50, 72};

    int snowballMaxRadiusPx = 34;
    int leafPileMaxHeightPx = 54;
    int windowShakeSensitivity = 55;
    double windowInertiaFactor = 0.75;
    double particleScale = 1.0;

    bool hasCustomSnowColor = false;
    D2D1_COLOR_F colorRain = D2D1::ColorF(0.42f, 0.72f, 1.0f, 0.78f);
    D2D1_COLOR_F colorSnow = D2D1::ColorF(0.98f, 0.99f, 1.0f, 0.96f);
    D2D1_COLOR_F colorHail = D2D1::ColorF(0.76f, 0.90f, 1.0f, 0.95f);
    D2D1_COLOR_F colorAutumnLeaves = D2D1::ColorF(0.88f, 0.44f, 0.12f, 0.94f);
    D2D1_COLOR_F colorExtraSnow = D2D1::ColorF(0.94f, 0.97f, 1.0f, 0.92f);
    D2D1_COLOR_F colorPetals = D2D1::ColorF(1.0f, 0.74f, 0.84f, 0.92f);

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
};

struct VisibleWindow {
    HWND hwnd = nullptr;
    RECT rect = {};
};

struct SnowColumn {
    float h = 0.0f;
    float lift = 0.0f;
    float vel = 0.0f;
    float hang = 0.0f;
};

struct SnowCap {
    bool isBottom = false;
    HWND hwnd = nullptr;
    RECT lastRect = {};
    uint32_t seed = 0;
    int offset = 0;
    float vx = 0.0f;
    float vy = 0.0f;
    float carry = 0.0f;
    float squash = 0.0f;
    float squashVel = 0.0f;
    float shakeDir = 0.0f;
    float shakeTime = 0.0f;
    float shakeSpeed = 0.0f;
    bool airborne = false;
    std::vector<SnowColumn> cols;
};

struct SnowChunk {
    float x = 0.0f;
    float y = 0.0f;
    float vx = 0.0f;
    float vy = 0.0f;
    float area = 4.0f;
    float size = 4.0f;
    HWND ignoreHwnd = nullptr;
    bool ignoreBottom = false;
};

struct FallingItem {
    ObjectKind kind = ObjectKind::Snow;
    bool isSeasonalLayer = false;
    float x = 0.0f;
    float y = 0.0f;
    float size = 6.0f;
    float angle = 0.0f;
    float spin = 0.0f;
    float flip = 0.0f;
    float flipSpeed = 2.5f;
    float swayPhase = 0.0f;
    float alpha = 0.9f;
    int shadeIdx = 0;
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
    float flip = 0.8f;
    float alpha = 0.92f;
    float ageSec = 0.0f;
    int shadeIdx = 0;
    bool fallingOff = false;
};

struct Snowball {
    ObjectKind kind = ObjectKind::Snow;
    bool isSeasonalLayer = false;
    bool onWindow = false;
    HWND hostWindow = nullptr;
    float relX = 0.0f;
    float relY = 0.0f;
    float vx = 0.0f;
    float vy = 0.0f;
    float radius = 8.0f;
    float squash = 0.0f;
    float squashVel = 0.0f;
    float alpha = 0.96f;
    float ageSec = 0.0f;
    bool fallingOff = false;
};

struct PileMember {
    float dx = 0.0f;
    float dy = 0.0f;
    float size = 8.0f;
    float angle = 0.0f;
    float flip = 0.7f;
    float alpha = 0.92f;
    int shadeIdx = 0;
};

struct FoliagePile {
    ObjectKind kind = ObjectKind::AutumnLeaves;
    bool isSeasonalLayer = false;
    bool onWindow = false;
    HWND hostWindow = nullptr;
    float centerX = 0.0f;
    float vx = 0.0f;
    float halfWidth = 42.0f;
    float height = 10.0f;
    float ageSec = 0.0f;
    std::vector<PileMember> members;
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
    float prevVx = 0.0f;
    float shakeDir = 0.0f;
    float shakeTimer = 0.0f;
    bool hasPrev = false;
};

struct LayeredSurface {
    ID2D1DCRenderTarget* rt = nullptr;
    HDC memDC = nullptr;
    HBITMAP dib = nullptr;
    HGDIOBJ oldBmp = nullptr;
    ID2D1Bitmap* flakeSprite = nullptr;
    D2D1_COLOR_F spriteColor = D2D1::ColorF(0, 0, 0, 0);
    int width = 0;
    int height = 0;
};

constexpr float kLeafPalette[][3] = {
    {0.93f, 0.49f, 0.13f},
    {0.82f, 0.24f, 0.12f},
    {0.95f, 0.73f, 0.20f},
    {0.68f, 0.36f, 0.14f},
    {0.88f, 0.38f, 0.11f},
};
constexpr float kPetalPalette[][3] = {
    {1.00f, 0.80f, 0.87f},
    {0.98f, 0.70f, 0.80f},
    {1.00f, 0.90f, 0.94f},
    {0.96f, 0.62f, 0.75f},
};

std::mutex g_mutex;
Settings g_settings;

bool g_hasForecastPrecip = false;
ObjectKind g_forecastPrecip = ObjectKind::Rain;
int g_forecastWindDirSign = 0;
double g_forecastWindSpeedKmh = 0.0;
GeneralEffectsState g_forecastEffects;

HWND g_desktopOverlayHwnd = nullptr;
HWND g_topWindowsOverlayHwnd = nullptr;
std::thread g_renderThread;
std::thread g_weatherThread;
std::atomic<bool> g_running{false};

ID2D1Factory* g_d2dFactory = nullptr;
LayeredSurface g_desktopSurface;
LayeredSurface g_topWindowsSurface;

int g_canvasLeft = 0;
int g_canvasTop = 0;
int g_canvasWidth = 0;
int g_canvasHeight = 0;

std::vector<FallingItem> g_falling;
std::vector<FallenItem> g_fallen;
std::vector<Snowball> g_snowballs;
std::vector<FoliagePile> g_piles;
std::vector<SnowChunk> g_chunks;
SnowCap g_bottomSnowCap;
std::unordered_map<HWND, SnowCap> g_windowSnowCaps;
LightningFlash g_lightning;
std::unordered_map<HWND, WindowMotion> g_windows;

uint32_t Hash32(uint32_t x) {
    x ^= x >> 16;
    x *= 0x7feb352d;
    x ^= x >> 15;
    x *= 0x846ca68b;
    x ^= x >> 16;
    return x;
}

float SmoothNoise(uint32_t seed, float x) {
    float cell = std::floor(x);
    uint32_t i = static_cast<uint32_t>(static_cast<int>(cell));
    float t = x - cell;
    t = t * t * (3.0f - 2.0f * t);
    float a = (Hash32(seed + i * 0x9E3779B1u) & 0xFFFFFF) / 16777216.0f;
    float b = (Hash32(seed + (i + 1) * 0x9E3779B1u) & 0xFFFFFF) / 16777216.0f;
    return a + (b - a) * t;
}

float CapNoise(const SnowCap& cap, int col, uint32_t salt, float scale) {
    return SmoothNoise(cap.seed + salt * 0x51ED27u, static_cast<float>(col + cap.offset) / scale);
}

float SnowColumnLimit(const SnowCap& cap, int col, float maxHeight, float scale) {
    float n = 0.65f * CapNoise(cap, col, 1, 70.0f * scale) +
              0.35f * CapNoise(cap, col, 2, 23.0f * scale);
    n = std::clamp((n - 0.5f) * 1.8f + 0.5f, 0.0f, 1.0f);
    return maxHeight * (0.32f + 0.68f * n);
}

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

void ParseCoordsString(const std::wstring& raw, double& outLat, double& outLon) {
    double defLat = 44.7866;
    double defLon = 20.4489;
    std::wstring s = Trim(raw);
    size_t sep = s.find(L'/');
    if (sep == std::wstring::npos) sep = s.find(L',');
    if (sep == std::wstring::npos) {
        outLat = defLat;
        outLon = defLon;
        return;
    }
    double lat = 0.0, lon = 0.0;
    if (!TryParseDoubleStrict(s.substr(0, sep), lat) || !TryParseDoubleStrict(s.substr(sep + 1), lon) ||
        lat < -90.0 || lat > 90.0 || lon < -180.0 || lon > 180.0) {
        outLat = defLat;
        outLon = defLon;
        return;
    }
    outLat = lat;
    outLon = lon;
}

int DaysInMonthSafe(int month) {
    switch (month) {
        case 2: return 29;
        case 4: case 6: case 9: case 11: return 30;
        default: return 31;
    }
}

bool TryParseDayMonthStrict(const std::wstring& raw, DayMonth& outDm) {
    std::wstring s = Trim(raw);
    size_t sep = s.find(L'.');
    if (sep == std::wstring::npos) sep = s.find(L'/');
    if (sep == std::wstring::npos) return false;
    std::wstring dPart = Trim(s.substr(0, sep));
    std::wstring mPart = Trim(s.substr(sep + 1));
    if (dPart.empty() || mPart.empty()) return false;
    for (wchar_t c : dPart) if (!iswdigit(c)) return false;
    for (wchar_t c : mPart) if (!iswdigit(c)) return false;
    try {
        int d = std::stoi(dPart);
        int m = std::stoi(mPart);
        if (m < 1 || m > 12) return false;
        if (d < 1 || d > DaysInMonthSafe(m)) return false;
        outDm = DayMonth{d, m};
        return true;
    } catch (...) {
        return false;
    }
}

bool TryParseDateRangePair(const std::wstring& raw, DayMonth& outStart, DayMonth& outEnd) {
    size_t dash = raw.find(L'-');
    if (dash == std::wstring::npos) return false;
    return TryParseDayMonthStrict(raw.substr(0, dash), outStart) &&
           TryParseDayMonthStrict(raw.substr(dash + 1), outEnd);
}

void ParseSeasonsRangeString(const std::wstring& raw, Settings& cfg) {
    DayMonth defSpS{1, 3}, defSpE{31, 5};
    DayMonth defSuS{1, 6}, defSuE{31, 8};
    DayMonth defAuS{1, 9}, defAuE{30, 11};
    DayMonth defWiS{1, 12}, defWiE{29, 2};

    std::vector<std::wstring> parts;
    std::wstringstream ss(raw);
    std::wstring item;
    while (std::getline(ss, item, L'/')) {
        parts.push_back(Trim(item));
    }

    DayMonth spS = defSpS, spE = defSpE, suS = defSuS, suE = defSuE, auS = defAuS, auE = defAuE, wiS = defWiS, wiE = defWiE;
    if (parts.size() != 4 ||
        !TryParseDateRangePair(parts[0], spS, spE) ||
        !TryParseDateRangePair(parts[1], suS, suE) ||
        !TryParseDateRangePair(parts[2], auS, auE) ||
        !TryParseDateRangePair(parts[3], wiS, wiE)) {
        cfg.springStart = defSpS; cfg.springEnd = defSpE;
        cfg.summerStart = defSuS; cfg.summerEnd = defSuE;
        cfg.autumnStart = defAuS; cfg.autumnEnd = defAuE;
        cfg.winterStart = defWiS; cfg.winterEnd = defWiE;
        return;
    }

    cfg.springStart = spS; cfg.springEnd = spE;
    cfg.summerStart = suS; cfg.summerEnd = suE;
    cfg.autumnStart = auS; cfg.autumnEnd = auE;
    cfg.winterStart = wiS; cfg.winterEnd = wiE;
}

void ParseArcGeometryString(const std::wstring& raw, ArcGeometry defGeom, ArcGeometry& outGeom) {
    outGeom = defGeom;
    std::wstring s = Trim(raw);
    size_t dash = s.find(L'-');
    size_t slash = s.find(L'/');
    if (dash == std::wstring::npos || slash == std::wstring::npos || slash <= dash) return;

    std::wstring rPart = Trim(s.substr(0, dash));
    std::wstring xPart = Trim(s.substr(dash + 1, slash - dash - 1));
    std::wstring yPart = Trim(s.substr(slash + 1));

    auto isIntStr = [](const std::wstring& p) -> bool {
        if (p.empty()) return false;
        for (wchar_t c : p) if (!iswdigit(c)) return false;
        return true;
    };
    if (!isIntStr(rPart) || !isIntStr(xPart) || !isIntStr(yPart)) return;

    try {
        int r = std::stoi(rPart);
        int x = std::stoi(xPart);
        int y = std::stoi(yPart);
        if (r < 0 || r > 100 || x < 0 || x > 100 || y < 0 || y > 100) return;
        outGeom.radius = r;
        outGeom.centerX = x;
        outGeom.centerY = y;
    } catch (...) {
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
    if (v == L"move") return CursorActionMode::Move;
    if (v == L"none") return CursorActionMode::None;
    return CursorActionMode::Clear;
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

    int fpsRaw = Wh_GetIntSetting(L"targetFps");
    next.targetFps = (fpsRaw == 30 || fpsRaw == 60) ? fpsRaw : 60;
    next.pauseOnFullscreen = Wh_GetIntSetting(L"pauseOnFullscreen") != 0;
    next.excludedProcesses = readStr(L"excludedProcesses", L"obs64.exe, ApplicationFrameHost.exe");

    next.cursorAction = ParseCursorAction(readStr(L"cursorAction", L"clear"));
    next.cursorRadiusPx = ParseIntRangeOrDefault(Wh_GetIntSetting(L"cursorRadiusPx"), 10, 500, 95);

    next.enableBottomAccumulation = Wh_GetIntSetting(L"enableBottomAccumulation") != 0;
    next.enableWindowAccumulation = Wh_GetIntSetting(L"enableWindowAccumulation") != 0;

    next.primarySource = readStr(L"primarySource", L"open_meteo");
    next.fallbackSource = readStr(L"fallbackSource", L"off");
    ParseCoordsString(readStr(L"coords", L"44.7866/20.4489"), next.latitude, next.longitude);
    next.customApiUrl = Trim(readStr(L"customApiUrl", L""));
    next.localWeatherPath = Trim(readStr(L"localWeatherPath", L""));
    next.updateIntervalMin = ParseIntRangeOrDefault(Wh_GetIntSetting(L"updateIntervalMin"), 1, 1440, 30);

    ParseSeasonsRangeString(
        readStr(L"seasonsRange", L"01.03-31.05/01.06-31.08/01.09-30.11/01.12-29.02"),
        next);

    next.precipitationMode = ParsePrecipMode(readStr(L"precipitationMode", L"auto"));
    next.precipFallDirection = ParseFallDir(readStr(L"precipFallDirection", L"auto"));
    next.precipFallSpeedMps = ParseDoubleRangeOrDefault(readStr(L"precipFallSpeedMps", L"6.5"), 0.1, 50.0, 6.5);

    next.precipIntensity = SanitizePercent(Wh_GetIntSetting(L"precipIntensity"));
    next.precipMaxAccumulated = ParseIntRangeOrDefault(Wh_GetIntSetting(L"precipMaxAccumulated"), 0, 2000, 220);

    auto readLifetime = [&](LPCWSTR key, double defMin) -> double {
        double v = 0.0;
        if (!TryParseDoubleStrict(readStr(key, L""), v)) return defMin;
        if (v < 0.0) {
            return (std::abs(v + 1.0) < 1e-6) ? -1.0 : defMin;
        }
        if (v > 1440.0) return defMin;
        return std::max(0.05, v);
    };
    next.precipLifetimeMin = readLifetime(L"precipLifetimeMin", 10.0);

    next.seasonalObjectMode = ParseSeasonalMode(readStr(L"seasonalObjectMode", L"auto"));
    next.seasonalFallDirection = ParseFallDir(readStr(L"seasonalFallDirection", L"auto"));
    next.seasonalFallSpeedMps = ParseDoubleRangeOrDefault(readStr(L"seasonalFallSpeedMps", L"2.2"), 0.1, 30.0, 2.2);

    next.seasonalIntensity = SanitizePercent(Wh_GetIntSetting(L"seasonalIntensity"));
    next.seasonalMaxAccumulated = ParseIntRangeOrDefault(Wh_GetIntSetting(L"seasonalMaxAccumulated"), 0, 2000, 220);
    next.seasonalLifetimeMin = readLifetime(L"seasonalLifetimeMin", 15.0);

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

    ParseArcGeometryString(readStr(L"rainbowGeometry", L"55-50/15"), ArcGeometry{55, 50, 15}, next.rainbowGeom);
    ParseArcGeometryString(readStr(L"haloGeometry", L"24-50/72"), ArcGeometry{24, 50, 72}, next.haloGeom);

    next.snowballMaxRadiusPx = ParseIntRangeOrDefault(Wh_GetIntSetting(L"snowballMaxRadiusPx"), 8, 120, 34);
    next.leafPileMaxHeightPx = ParseIntRangeOrDefault(Wh_GetIntSetting(L"leafPileMaxHeightPx"), 8, 250, 54);
    next.windowShakeSensitivity = ParseIntRangeOrDefault(Wh_GetIntSetting(L"windowShakeSensitivity"), 1, 100, 55);
    next.windowInertiaFactor = ParseDoubleRangeOrDefault(readStr(L"windowInertiaFactor", L"0.75"), 0.0, 3.0, 0.75);
    next.particleScale = ParseDoubleRangeOrDefault(readStr(L"particleScale", L"1.0"), 0.3, 4.0, 1.0);

    TryParseHexColorStrict(readStr(L"colorRain", L""), 0.78f, next.colorRain);
    next.hasCustomSnowColor = TryParseHexColorStrict(readStr(L"colorSnow", L""), 0.96f, next.colorSnow);
    TryParseHexColorStrict(readStr(L"colorHail", L""), 0.95f, next.colorHail);
    TryParseHexColorStrict(readStr(L"colorAutumnLeaves", L""), 0.94f, next.colorAutumnLeaves);
    TryParseHexColorStrict(readStr(L"colorExtraSnow", L""), 0.92f, next.colorExtraSnow);
    TryParseHexColorStrict(readStr(L"colorPetals", L""), 0.92f, next.colorPetals);

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

    HINTERNET hSession = InternetOpenW(L"WindhawkWeatherMod/1.1", INTERNET_OPEN_TYPE_PRECONFIG, nullptr, nullptr, 0);
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

void ApplyForecastMetrics(int code, double windKmh, double tempC, int cloudCover,
                          double visibilityM, bool isDay,
                          bool& hasPrecip, ObjectKind& precipKind, GeneralEffectsState& fx) {
    hasPrecip = false;
    fx = GeneralEffectsState{};

    bool isRainCode = (code >= 51 && code <= 67) || (code >= 80 && code <= 82);
    bool isSnowCode = (code == 71 || code == 73 || code == 75 || code == 77 || code == 85 || code == 86);
    bool isStormCode = (code == 95 || code == 96 || code == 99);
    bool isFogCode = (code == 45 || code == 48);

    if (code == 0) fx.clear = true;
    else if (code == 1 || code == 2) fx.partlyCloudy = true;
    else if (code == 3) fx.overcast = true;
    else if (isFogCode) fx.fog = true;

    if (isSnowCode) {
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
    } else if (isRainCode) {
        hasPrecip = true;
        precipKind = ObjectKind::Rain;
    }

    if (!hasPrecip && !isStormCode && windKmh >= 28.0 && (visibilityM <= 0.0 || visibilityM < 8000.0)) {
        fx.dust = true;
    }
    if (!hasPrecip && windKmh < 12.0 && visibilityM > 0.0 && visibilityM < 6000.0) {
        fx.smog = true;
    }
    if (isDay && !hasPrecip && !isStormCode && tempC >= 28.0 && cloudCover <= 30) {
        fx.mirage = true;
    }
    if (isDay && !isStormCode && (isRainCode || isFogCode || (cloudCover >= 15 && cloudCover <= 65 && !hasPrecip))) {
        fx.rainbow = true;
    }
    if (!hasPrecip && !isStormCode && cloudCover >= 20 && cloudCover <= 75) {
        fx.halo = true;
    }
    if (!isDay && !hasPrecip && !isStormCode && cloudCover <= 35) {
        fx.aurora = true;
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

    double tempC = 15.0;
    extractNumber("temperature_2m", tempC);
    double cloud = 20.0;
    extractNumber("cloud_cover", cloud);
    double vis = 12000.0;
    extractNumber("visibility", vis);
    double isDayNum = 1.0;
    extractNumber("is_day", isDayNum);

    double wmo = -999.0;
    if (extractNumber("weather_code", wmo) || extractNumber("weathercode", wmo)) {
        ApplyForecastMetrics(static_cast<int>(wmo), windSpeed, tempC, static_cast<int>(cloud),
                             vis, isDayNum > 0.5, hasPrecip, precipKind, fx);
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
            << L"¤t=weather_code,wind_speed_10m,wind_direction_10m,temperature_2m,cloud_cover,visibility,is_day";
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
    if (!fg || fg == g_desktopOverlayHwnd || fg == g_topWindowsOverlayHwnd) return false;
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
    std::vector<VisibleWindow>* outWindows;
};

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam) {
    auto* ctx = reinterpret_cast<EnumCtx*>(lParam);
    if (!IsWindowVisible(hwnd) || IsIconic(hwnd)) return TRUE;
    if (hwnd == g_desktopOverlayHwnd || hwnd == g_topWindowsOverlayHwnd) return TRUE;

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
    if (FAILED(DwmGetWindowAttribute(hwnd, DWMWA_EXTENDED_FRAME_BOUNDS, &r, sizeof(r)))) {
        if (!GetWindowRect(hwnd, &r)) return TRUE;
    }
    if ((r.right - r.left) >= 80 && (r.bottom - r.top) >= 40) {
        RECT rel = {r.left - g_canvasLeft, r.top - g_canvasTop, r.right - g_canvasLeft, r.bottom - g_canvasTop};
        ctx->outWindows->push_back(VisibleWindow{hwnd, rel});
    }
    return TRUE;
}

bool IsPointOccludedAbove(const std::vector<VisibleWindow>& windows, size_t targetIdx, float x, float y) {
    int ix = static_cast<int>(std::floor(x));
    int iy = static_cast<int>(std::floor(y));
    for (size_t i = 0; i < targetIdx; ++i) {
        const RECT& r = windows[i].rect;
        if (ix >= r.left && ix < r.right && iy >= r.top && iy < r.bottom) {
            return true;
        }
    }
    return false;
}

int FindTopWindowLanding(const std::vector<VisibleWindow>& windows, float x, float prevY, float curY) {
    int ix = static_cast<int>(std::floor(x));
    for (size_t i = 0; i < windows.size(); ++i) {
        const RECT& r = windows[i].rect;
        if (ix < r.left || ix >= r.right) continue;
        if (curY >= static_cast<float>(r.top) && curY < static_cast<float>(r.bottom)) {
            if (prevY <= static_cast<float>(r.top) + 12.0f) {
                return static_cast<int>(i);
            }
            return -1;
        }
    }
    return -1;
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

void PositionDesktopOverlay(HWND overlay, const std::wstring& mode) {
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

void PositionTopWindowsOverlay(HWND overlay) {
    if (!overlay) return;
    SetWindowPos(
        overlay,
        HWND_TOPMOST,
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

int GetIntensityForKind(const Settings& cfg, bool isSeasonal) {
    return isSeasonal ? cfg.seasonalIntensity : cfg.precipIntensity;
}

int GetMaxAccumulatedForKind(const Settings& cfg, bool isSeasonal) {
    return isSeasonal ? cfg.seasonalMaxAccumulated : cfg.precipMaxAccumulated;
}

double GetLifetimeMinForKind(const Settings& cfg, bool isSeasonal) {
    return isSeasonal ? cfg.seasonalLifetimeMin : cfg.precipLifetimeMin;
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

float ComputeMaxCapHeightPx(const Settings& cfg, bool isBottom) {
    int maxAcc = cfg.precipMaxAccumulated;
    if (maxAcc <= 0) return 0.0f;
    float base = std::clamp(8.0f + (maxAcc / 2000.0f) * 26.0f, 8.0f, 34.0f) * static_cast<float>(cfg.particleScale);
    return isBottom ? (base * 1.45f) : base;
}

void AddSnowToCap(SnowCap& cap, int column, float amount, float maxCapHeight, float scale) {
    int width = static_cast<int>(cap.cols.size());
    if (width < 4 || maxCapHeight <= 0.1f) return;

    constexpr int kReach = 14;
    int from = std::max(column - kReach, 1);
    int to = std::min(column + kReach, width - 2);
    if (from > to) return;

    float limit[2 * kReach + 1];
    for (int c = from; c <= to; ++c) {
        limit[c - from] = SnowColumnLimit(cap, c, maxCapHeight, scale);
    }

    for (int i = 0; i < 9; ++i) {
        int c = column + i - 4;
        if (c >= from && c <= to) {
            cap.cols[c].h = std::min(limit[c - from], cap.cols[c].h + amount * kSnowKernel[i]);
        }
    }
    for (int pass = 0; pass < 2; ++pass) {
        for (int c = from; c <= to; ++c) {
            float h = cap.cols[c].h * 0.5f + (cap.cols[c - 1].h + cap.cols[c + 1].h) * 0.25f;
            cap.cols[c].h = std::min(h, limit[c - from]);
        }
    }
}

void SpawnSnowChunk(float x, float y, float area, float vx, float vy, HWND ignoreHwnd, bool ignoreBottom, float scale) {
    if (g_chunks.size() >= 1200 || area < 0.5f) return;
    SnowChunk ch;
    ch.x = x;
    ch.y = y;
    ch.vx = vx;
    ch.vy = vy;
    ch.area = area;
    ch.size = std::clamp(std::sqrt(area) * 0.55f, 1.5f * scale, 5.0f * scale);
    ch.ignoreHwnd = ignoreHwnd;
    ch.ignoreBottom = ignoreBottom;
    g_chunks.push_back(ch);
}

void DropCapRangeToChunks(SnowCap& cap, int baseLeft, int baseTop, int first, int count, HWND ignoreHwnd) {
    int width = static_cast<int>(cap.cols.size());
    int end = std::min(width, first + count);
    for (int c = std::max(0, first); c < end; c += 3) {
        float area = 0.0f, top = 0.0f, lift = 0.0f;
        for (int k = c; k < std::min(c + 3, end); ++k) {
            area += cap.cols[k].h;
            top = std::max(top, cap.cols[k].h);
            lift = std::max(lift, cap.cols[k].lift);
            cap.cols[k].h = 0.0f;
        }
        if (area > 0.4f) {
            SpawnSnowChunk(static_cast<float>(baseLeft + c + 1), static_cast<float>(baseTop) - lift - top * 0.5f,
                           area, 0.0f, 10.0f, ignoreHwnd, false, 1.0f);
        }
    }
}

void SyncSnowCapWidth(SnowCap& cap, const RECT& newRect, int baseLeft, int baseTop) {
    int newW = std::max(1, static_cast<int>(newRect.right - newRect.left));
    int oldW = static_cast<int>(cap.cols.size());
    if (oldW == 0) {
        cap.cols.assign(newW, SnowColumn{});
        cap.lastRect = newRect;
        return;
    }
    if (oldW == newW) {
        cap.offset += static_cast<int>(newRect.left - cap.lastRect.left);
        cap.lastRect = newRect;
        return;
    }
    int dl = static_cast<int>(newRect.left - cap.lastRect.left);
    int dr = static_cast<int>(newRect.right - cap.lastRect.right);
    if (dl != 0 && dr != 0) {
        std::vector<SnowColumn> old = std::move(cap.cols);
        cap.cols.assign(newW, SnowColumn{});
        for (int c = 0; c < newW; ++c) {
            size_t src = static_cast<size_t>(c) * old.size() / newW;
            cap.cols[c].h = old[src].h;
        }
    } else {
        if (dl > 0) {
            int n = std::min(dl, static_cast<int>(cap.cols.size()));
            DropCapRangeToChunks(cap, baseLeft, baseTop, 0, n, cap.hwnd);
            cap.cols.erase(cap.cols.begin(), cap.cols.begin() + n);
        } else if (dl < 0) {
            cap.cols.insert(cap.cols.begin(), -dl, SnowColumn{});
        }
        cap.offset += dl;
        if (dr < 0) {
            int n = std::min(-dr, static_cast<int>(cap.cols.size()));
            int first = static_cast<int>(cap.cols.size()) - n;
            DropCapRangeToChunks(cap, baseLeft, baseTop, first, n, cap.hwnd);
            cap.cols.resize(first);
        }
        cap.cols.resize(newW, SnowColumn{});
    }
    cap.lastRect = newRect;
}

void SpawnFallingItem(FallingItem& item, std::mt19937& rng, ObjectKind kind, bool isSeasonal,
                      double scale, float vx, bool randomY) {
    std::uniform_real_distribution<float> phaseDist(0.0f, 6.2831853f);
    std::uniform_real_distribution<float> alphaDist(0.65f, 0.96f);

    item.kind = kind;
    item.isSeasonalLayer = isSeasonal;
    item.swayPhase = phaseDist(rng);
    item.angle = phaseDist(rng);
    item.flip = phaseDist(rng);
    item.alpha = alphaDist(rng);

    if (kind == ObjectKind::Petals) {
        item.shadeIdx = static_cast<int>(rng() % _countof(kPetalPalette));
    } else {
        item.shadeIdx = static_cast<int>(rng() % _countof(kLeafPalette));
    }

    if (randomY) {
        std::uniform_real_distribution<float> xDist(-40.0f, static_cast<float>(g_canvasWidth) + 40.0f);
        std::uniform_real_distribution<float> yDist(0.0f, static_cast<float>(g_canvasHeight));
        item.x = xDist(rng);
        item.y = yDist(rng);
    } else if (vx < -25.0f && ((rng() % 100) < 35)) {
        std::uniform_real_distribution<float> ySide(0.0f, static_cast<float>(g_canvasHeight) * 0.75f);
        item.x = static_cast<float>(g_canvasWidth) + 20.0f;
        item.y = ySide(rng);
    } else if (vx > 25.0f && ((rng() % 100) < 35)) {
        std::uniform_real_distribution<float> ySide(0.0f, static_cast<float>(g_canvasHeight) * 0.75f);
        item.x = -20.0f;
        item.y = ySide(rng);
    } else {
        std::uniform_real_distribution<float> xTop(-60.0f, static_cast<float>(g_canvasWidth) + 60.0f);
        item.x = xTop(rng);
        item.y = -24.0f;
    }

    float s = static_cast<float>(scale);
    if (kind == ObjectKind::Rain) {
        item.size = 13.0f * s;
        item.spin = 0.0f;
        item.flipSpeed = 0.0f;
    } else if (kind == ObjectKind::Hail) {
        item.size = (5.0f + (rng() % 30) * 0.1f) * s;
        item.spin = ((rng() % 100) - 50) * 0.05f;
        item.flipSpeed = 0.0f;
    } else if (kind == ObjectKind::Petals) {
        item.size = (6.5f + (rng() % 30) * 0.1f) * s;
        item.spin = ((rng() % 100) - 50) * 0.06f;
        item.flipSpeed = (2.5f + (rng() % 30) * 0.1f) * ((rng() % 2 == 0) ? 1.0f : -1.0f);
    } else if (kind == ObjectKind::AutumnLeaves) {
        item.size = (10.5f + (rng() % 45) * 0.1f) * s;
        item.spin = ((rng() % 100) - 50) * 0.04f;
        item.flipSpeed = (1.8f + (rng() % 25) * 0.1f) * ((rng() % 2 == 0) ? 1.0f : -1.0f);
    } else {
        float depth = static_cast<float>(rng() % 1000) / 1000.0f;
        item.size = (2.4f + depth * depth * 5.2f) * s;
        item.spin = 0.0f;
        item.flipSpeed = 0.0f;
    }
}

void CleanupSurface(LayeredSurface& surf) {
    if (surf.flakeSprite) {
        surf.flakeSprite->Release();
        surf.flakeSprite = nullptr;
    }
    if (surf.rt) {
        surf.rt->Release();
        surf.rt = nullptr;
    }
    if (surf.memDC) {
        if (surf.oldBmp) {
            SelectObject(surf.memDC, surf.oldBmp);
            surf.oldBmp = nullptr;
        }
        DeleteDC(surf.memDC);
        surf.memDC = nullptr;
    }
    if (surf.dib) {
        DeleteObject(surf.dib);
        surf.dib = nullptr;
    }
    surf.width = 0;
    surf.height = 0;
}

bool RebuildFlakeSprite(LayeredSurface& surf, D2D1_COLOR_F snowCol, bool hasCustomColor) {
    if (!surf.rt) return false;
    if (surf.flakeSprite) {
        surf.flakeSprite->Release();
        surf.flakeSprite = nullptr;
    }

    auto shade = [&](float r, float g, float b, float a) -> D2D1_COLOR_F {
        if (!hasCustomColor) return D2D1::ColorF(r, g, b, a);
        float br = (r + g + b) / 3.0f;
        return D2D1::ColorF(snowCol.r * br, snowCol.g * br, snowCol.b * br, a);
    };

    constexpr UINT32 kSize = 32;
    ID2D1BitmapRenderTarget* bmpRt = nullptr;
    if (FAILED(surf.rt->CreateCompatibleRenderTarget(D2D1::SizeF(static_cast<float>(kSize), static_cast<float>(kSize)), &bmpRt)) || !bmpRt) {
        return false;
    }

    D2D1_GRADIENT_STOP stops[4] = {
        {0.00f, shade(1.00f, 1.00f, 1.00f, 1.00f)},
        {0.42f, shade(0.98f, 0.99f, 1.00f, 0.95f)},
        {0.62f, shade(0.75f, 0.82f, 0.95f, 0.36f)},
        {1.00f, shade(0.60f, 0.70f, 0.85f, 0.00f)}
    };
    ID2D1GradientStopCollection* stopCol = nullptr;
    ID2D1RadialGradientBrush* radBrush = nullptr;
    if (SUCCEEDED(bmpRt->CreateGradientStopCollection(stops, 4, D2D1_GAMMA_2_2, D2D1_EXTEND_MODE_CLAMP, &stopCol)) && stopCol) {
        bmpRt->CreateRadialGradientBrush(
            D2D1::RadialGradientBrushProperties(D2D1::Point2F(16.0f, 16.0f), D2D1::Point2F(0.0f, 0.0f), 16.0f, 16.0f),
            stopCol, &radBrush);
    }

    bmpRt->BeginDraw();
    bmpRt->Clear(D2D1::ColorF(0.0f, 0.0f, 0.0f, 0.0f));
    if (radBrush) {
        bmpRt->FillRectangle(D2D1::RectF(0.0f, 0.0f, 32.0f, 32.0f), radBrush);
    }
    bmpRt->EndDraw();

    if (radBrush) radBrush->Release();
    if (stopCol) stopCol->Release();

    bmpRt->GetBitmap(&surf.flakeSprite);
    bmpRt->Release();
    surf.spriteColor = snowCol;
    return surf.flakeSprite != nullptr;
}

bool EnsureSurface(LayeredSurface& surf, int width, int height, D2D1_COLOR_F snowCol, bool hasCustomSnow) {
    if (!g_d2dFactory) {
        D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &g_d2dFactory);
    }
    if (!g_d2dFactory) return false;

    if (!surf.rt || !surf.memDC || !surf.dib || surf.width != width || surf.height != height) {
        CleanupSurface(surf);

        HDC screenDC = GetDC(nullptr);
        surf.memDC = CreateCompatibleDC(screenDC);
        ReleaseDC(nullptr, screenDC);
        if (!surf.memDC) return false;

        BITMAPINFO bmi = {};
        bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        bmi.bmiHeader.biWidth = width;
        bmi.bmiHeader.biHeight = -height;
        bmi.bmiHeader.biPlanes = 1;
        bmi.bmiHeader.biBitCount = 32;
        bmi.bmiHeader.biCompression = BI_RGB;

        void* bits = nullptr;
        surf.dib = CreateDIBSection(surf.memDC, &bmi, DIB_RGB_COLORS, &bits, nullptr, 0);
        if (!surf.dib) {
            CleanupSurface(surf);
            return false;
        }

        surf.oldBmp = SelectObject(surf.memDC, surf.dib);
        surf.width = width;
        surf.height = height;

        D2D1_RENDER_TARGET_PROPERTIES props = D2D1::RenderTargetProperties(
            D2D1_RENDER_TARGET_TYPE_DEFAULT,
            D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED));

        if (FAILED(g_d2dFactory->CreateDCRenderTarget(&props, &surf.rt)) || !surf.rt) {
            CleanupSurface(surf);
            return false;
        }
    }

    if (!surf.flakeSprite ||
        std::abs(surf.spriteColor.r - snowCol.r) > 0.01f ||
        std::abs(surf.spriteColor.g - snowCol.g) > 0.01f ||
        std::abs(surf.spriteColor.b - snowCol.b) > 0.01f) {
        RebuildFlakeSprite(surf, snowCol, hasCustomSnow);
    }
    return true;
}

void DrawMapleLeafWithFlip(ID2D1DCRenderTarget* rt, ID2D1SolidColorBrush* brush,
                           float x, float y, float r, float angle, float flip,
                           D2D1_COLOR_F baseColor, float alpha) {
    float widthScale = std::cos(flip);
    float shade = (widthScale < 0.0f) ? 0.80f : 1.0f;
    float squashY = std::max(0.18f, std::abs(widthScale));

    D2D1::Matrix3x2F oldXform;
    rt->GetTransform(&oldXform);
    rt->SetTransform(
        D2D1::Matrix3x2F::Scale(1.0f, squashY) *
        D2D1::Matrix3x2F::Rotation(angle * 57.29578f) *
        D2D1::Matrix3x2F::Translation(x, y) * oldXform);

    brush->SetColor(D2D1::ColorF(baseColor.r * shade, baseColor.g * shade, baseColor.b * shade, std::clamp(alpha, 0.05f, 1.0f)));
    D2D1_POINT_2F pts[10] = {
        {0.0f, -r},
        {r * 0.30f, -r * 0.42f},
        {r * 0.92f, -r * 0.35f},
        {r * 0.52f, r * 0.14f},
        {r * 0.72f, r * 0.68f},
        {0.0f, r * 0.40f},
        {-r * 0.72f, r * 0.68f},
        {-r * 0.52f, r * 0.14f},
        {-r * 0.92f, -r * 0.35f},
        {-r * 0.30f, -r * 0.42f}
    };
    for (int i = 0; i < 10; ++i) {
        int next = (i + 1) % 10;
        rt->DrawLine(pts[i], pts[next], brush, std::max(1.4f, r * 0.22f));
    }
    rt->FillEllipse(D2D1::Ellipse(D2D1::Point2F(0.0f, 0.0f), r * 0.48f, r * 0.48f), brush);

    brush->SetColor(D2D1::ColorF(baseColor.r * 0.58f * shade, baseColor.g * 0.58f * shade, baseColor.b * 0.58f * shade, std::clamp(alpha * 0.85f, 0.05f, 1.0f)));
    rt->DrawLine(D2D1::Point2F(0.0f, -r * 0.55f), D2D1::Point2F(0.0f, r * 1.18f), brush, std::max(1.1f, r * 0.15f));

    rt->SetTransform(oldXform);
}

void DrawNotchedPetalWithFlip(ID2D1DCRenderTarget* rt, ID2D1SolidColorBrush* brush,
                              float x, float y, float r, float angle, float flip,
                              D2D1_COLOR_F baseColor, float alpha) {
    float widthScale = std::cos(flip);
    float shade = (widthScale < 0.0f) ? 0.84f : 1.0f;
    float squashY = std::max(0.20f, std::abs(widthScale));

    D2D1::Matrix3x2F oldXform;
    rt->GetTransform(&oldXform);
    rt->SetTransform(
        D2D1::Matrix3x2F::Scale(1.0f, squashY) *
        D2D1::Matrix3x2F::Rotation(angle * 57.29578f) *
        D2D1::Matrix3x2F::Translation(x, y) * oldXform);

    brush->SetColor(D2D1::ColorF(baseColor.r * shade, baseColor.g * shade, baseColor.b * shade, std::clamp(alpha, 0.05f, 1.0f)));
    rt->FillEllipse(D2D1::Ellipse(D2D1::Point2F(0.0f, 0.0f), r * 0.92f, r * 0.54f), brush);
    brush->SetColor(D2D1::ColorF(std::min(1.0f, baseColor.r * 1.04f), baseColor.g * 0.90f, baseColor.b * 0.92f, std::clamp(alpha * 0.55f, 0.05f, 0.8f)));
    rt->DrawLine(D2D1::Point2F(-r * 0.55f, 0.0f), D2D1::Point2F(r * 0.45f, 0.0f), brush, std::max(0.9f, r * 0.10f));

    rt->SetTransform(oldXform);
}

void DrawItemShape(LayeredSurface& surf, ID2D1SolidColorBrush* brush, const Settings& cfg,
                   ObjectKind kind, float x, float y, float size, float angle, float flip,
                   float vx, float alpha, int shadeIdx) {
    if (kind == ObjectKind::Rain) {
        brush->SetColor(cfg.colorRain);
        brush->SetOpacity(std::clamp(alpha, 0.05f, 1.0f));
        surf.rt->DrawLine(D2D1::Point2F(x, y), D2D1::Point2F(x + vx * 0.02f, y + size), brush, 1.5f);
        return;
    }

    if (kind == ObjectKind::Snow || kind == ObjectKind::ExtraSnow) {
        if (surf.flakeSprite) {
            float r = size * 1.35f;
            surf.rt->DrawBitmap(
                surf.flakeSprite,
                D2D1::RectF(x - r, y - r, x + r, y + r),
                std::clamp(alpha, 0.05f, 1.0f),
                D2D1_BITMAP_INTERPOLATION_MODE_LINEAR);
            return;
        }
        brush->SetColor(GetColorForKind(cfg, kind));
        brush->SetOpacity(std::clamp(alpha, 0.05f, 1.0f));
        surf.rt->FillEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), size * 0.5f, size * 0.5f), brush);
        return;
    }

    if (kind == ObjectKind::AutumnLeaves) {
        D2D1_COLOR_F col = cfg.colorAutumnLeaves;
        if (std::abs(col.r - 0.88f) < 0.01f && std::abs(col.g - 0.44f) < 0.01f) {
            const float* rgb = kLeafPalette[shadeIdx % _countof(kLeafPalette)];
            col = D2D1::ColorF(rgb[0], rgb[1], rgb[2], col.a);
        }
        DrawMapleLeafWithFlip(surf.rt, brush, x, y, size * 0.65f, angle, flip, col, alpha);
        return;
    }

    if (kind == ObjectKind::Petals) {
        D2D1_COLOR_F col = cfg.colorPetals;
        if (std::abs(col.r - 1.0f) < 0.01f && std::abs(col.g - 0.74f) < 0.01f) {
            const float* rgb = kPetalPalette[shadeIdx % _countof(kPetalPalette)];
            col = D2D1::ColorF(rgb[0], rgb[1], rgb[2], col.a);
        }
        DrawNotchedPetalWithFlip(surf.rt, brush, x, y, size * 0.68f, angle, flip, col, alpha);
        return;
    }

    D2D1::Matrix3x2F oldXform;
    surf.rt->GetTransform(&oldXform);
    surf.rt->SetTransform(D2D1::Matrix3x2F::Rotation(angle * 57.29578f, D2D1::Point2F(x, y)) * oldXform);
    brush->SetColor(cfg.colorHail);
    brush->SetOpacity(std::clamp(alpha, 0.05f, 1.0f));
    surf.rt->FillRectangle(D2D1::RectF(x - size * 0.45f, y - size * 0.45f, x + size * 0.45f, y + size * 0.45f), brush);
    surf.rt->SetTransform(oldXform);
}

void DrawSnowCapSurface(ID2D1DCRenderTarget* rt, const SnowCap& cap, float left, float top,
                        D2D1_COLOR_F snowCol, bool hasCustomColor, float scale) {
    int width = static_cast<int>(cap.cols.size());
    if (width < 4) return;

    float highest = 0.0f;
    float liftSum = 0.0f;
    int snowyCount = 0;
    for (const auto& c : cap.cols) {
        highest = std::max(highest, c.h);
        if (c.h > 0.2f) {
            liftSum += c.lift;
            ++snowyCount;
        }
    }
    if (highest < 0.25f) return;

    ID2D1PathGeometry* path = nullptr;
    ID2D1GeometrySink* sink = nullptr;
    if (FAILED(g_d2dFactory->CreatePathGeometry(&path)) || !path) return;
    if (FAILED(path->Open(&sink)) || !sink) {
        path->Release();
        return;
    }

    float squashScale = 1.0f + cap.squash;
    auto colH = [&](int idx) -> float {
        float edge = static_cast<float>(std::min(idx, width - 1 - idx));
        float taper = std::clamp(edge / (kCapEdgeTaper * scale), 0.0f, 1.0f);
        return cap.cols[idx].h * squashScale * taper;
    };

    constexpr float kMinH = 0.3f;
    for (int c = 0; c < width;) {
        if (colH(c) < kMinH) {
            ++c;
            continue;
        }
        int first = c;
        while (c < width && colH(c) >= kMinH) ++c;
        int last = c - 1;

        float x0 = left + first;
        float x1 = left + last + 1.0f;
        sink->BeginFigure(D2D1::Point2F(x0, top - cap.cols[first].lift), D2D1_FIGURE_BEGIN_FILLED);
        for (int k = first; k <= last; k += 2) {
            sink->AddLine(D2D1::Point2F(left + k + 0.5f, top - cap.cols[k].lift - colH(k)));
        }
        sink->AddLine(D2D1::Point2F(x1 - 0.5f, top - cap.cols[last].lift - colH(last)));
        sink->AddLine(D2D1::Point2F(x1, top - cap.cols[last].lift));
        if (cap.airborne) {
            for (int k = last; k >= first; k -= 2) {
                sink->AddLine(D2D1::Point2F(left + k + 0.5f, top - cap.cols[k].lift));
            }
        }
        sink->EndFigure(D2D1_FIGURE_END_CLOSED);
    }

    if (FAILED(sink->Close())) {
        sink->Release();
        path->Release();
        return;
    }
    sink->Release();

    D2D1_COLOR_F topCol = hasCustomColor ? snowCol : D2D1::ColorF(0.99f, 0.995f, 1.0f, 0.96f);
    D2D1_COLOR_F botCol = hasCustomColor
        ? D2D1::ColorF(snowCol.r * 0.82f, snowCol.g * 0.85f, snowCol.b * 0.92f, 0.96f)
        : D2D1::ColorF(0.78f, 0.85f, 0.94f, 0.96f);

    float avgLift = snowyCount ? (liftSum / snowyCount) : 0.0f;
    float baseLine = top - avgLift;
    D2D1_GRADIENT_STOP stops[2] = {
        {0.0f, topCol},
        {1.0f, botCol}
    };
    ID2D1GradientStopCollection* stopCol = nullptr;
    if (SUCCEEDED(rt->CreateGradientStopCollection(stops, 2, D2D1_GAMMA_2_2, D2D1_EXTEND_MODE_CLAMP, &stopCol)) && stopCol) {
        ID2D1LinearGradientBrush* grad = nullptr;
        if (SUCCEEDED(rt->CreateLinearGradientBrush(
                D2D1::LinearGradientBrushProperties(D2D1::Point2F(0.0f, baseLine - highest * squashScale), D2D1::Point2F(0.0f, baseLine)),
                stopCol, &grad)) && grad) {
            rt->FillGeometry(path, grad);
            grad->Release();
        }
        stopCol->Release();
    }
    path->Release();
}

void DrawRainPuddle(ID2D1DCRenderTarget* rt, ID2D1SolidColorBrush* brush, D2D1_COLOR_F rainCol, float x, float y, float size, float alpha) {
    brush->SetColor(rainCol);
    brush->SetOpacity(std::clamp(alpha * 0.55f, 0.05f, 0.75f));
    float width = std::max(8.0f, size * 1.4f);
    rt->FillEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), width * 0.5f, 1.0f), brush);
}

void DrawFoliagePileShape(LayeredSurface& surf, ID2D1SolidColorBrush* brush, const Settings& cfg,
                          const FoliagePile& pile, float drawCenterX, float drawBaseY) {
    D2D1_COLOR_F baseCol = GetColorForKind(cfg, pile.kind);
    baseCol.a = 0.24f;
    brush->SetColor(baseCol);
    surf.rt->FillEllipse(
        D2D1::Ellipse(
            D2D1::Point2F(drawCenterX, drawBaseY - pile.height * 0.28f),
            pile.halfWidth,
            std::max(4.0f, pile.height * 0.45f)),
        brush);

    for (const auto& m : pile.members) {
        DrawItemShape(surf, brush, cfg, pile.kind, drawCenterX + m.dx, drawBaseY + m.dy, m.size, m.angle, m.flip, 0.0f, m.alpha, m.shadeIdx);
    }
}

void AddItemToFoliagePile(FoliagePile& pile, float itemAbsX, float itemSize, float itemAngle,
                          float itemFlip, float itemAlpha, int shadeIdx, float maxPileH, std::mt19937& rng) {
    float offsetX = std::clamp(itemAbsX - pile.centerX, -pile.halfWidth * 0.85f, pile.halfWidth * 0.85f);
    float normX = std::abs(offsetX) / std::max(1.0f, pile.halfWidth);
    float domeFactor = std::max(0.25f, 1.0f - normX * normX);

    int layerIdx = static_cast<int>(pile.members.size()) / 5;
    float lift = std::min(maxPileH, (layerIdx + 1) * (itemSize * 0.42f) * domeFactor);
    pile.height = std::max(pile.height, lift);

    PileMember pm;
    pm.dx = offsetX + static_cast<float>((rng() % 10) - 5) * 0.4f;
    pm.dy = -itemSize * 0.35f - lift;
    pm.size = itemSize;
    pm.angle = itemAngle + static_cast<float>((rng() % 40) - 20) * 0.01f;
    pm.flip = itemFlip;
    pm.alpha = itemAlpha;
    pm.shadeIdx = shadeIdx;

    if (pile.members.size() < 64) {
        pile.members.push_back(pm);
    } else {
        pile.members[rng() % pile.members.size()] = pm;
    }
}

void DrawSnowballShape(LayeredSurface& surf, ID2D1SolidColorBrush* brush, const Settings& cfg,
                       const Snowball& sb, float x, float y) {
    float rx = sb.radius * (1.0f + sb.squash * 0.35f);
    float ry = std::max(2.0f, sb.radius * (1.0f - sb.squash * 0.35f));
    if (surf.flakeSprite) {
        surf.rt->DrawBitmap(
            surf.flakeSprite,
            D2D1::RectF(x - rx * 1.25f, y - ry * 1.25f, x + rx * 1.25f, y + ry * 1.25f),
            std::clamp(sb.alpha, 0.1f, 1.0f),
            D2D1_BITMAP_INTERPOLATION_MODE_LINEAR);
        return;
    }
    brush->SetColor(GetColorForKind(cfg, sb.kind));
    brush->SetOpacity(std::clamp(sb.alpha, 0.1f, 1.0f));
    surf.rt->FillEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), rx, ry), brush);
}

void PresentSurface(HWND hwnd, LayeredSurface& surf) {
    if (!hwnd || !IsWindow(hwnd) || !surf.memDC) return;
    POINT ptDst = {g_canvasLeft, g_canvasTop};
    SIZE sizeWnd = {g_canvasWidth, g_canvasHeight};
    POINT ptSrc = {0, 0};
    BLENDFUNCTION blend = {};
    blend.BlendOp = AC_SRC_OVER;
    blend.SourceConstantAlpha = 255;
    blend.AlphaFormat = AC_SRC_ALPHA;
    UpdateLayeredWindow(hwnd, nullptr, &ptDst, &sizeWnd, surf.memDC, &ptSrc, 0, &blend, ULW_ALPHA);
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
    if (cfg.rainbowGeom.radius <= 0 || strength <= 0.004f) return;

    float minSide = static_cast<float>(std::min(g_canvasWidth, g_canvasHeight));
    float radius = minSide * (static_cast<float>(cfg.rainbowGeom.radius) / 100.0f);
    if (radius < 4.0f) return;

    float cx = static_cast<float>(g_canvasWidth) * (static_cast<float>(cfg.rainbowGeom.centerX) / 100.0f);
    float cy = static_cast<float>(g_canvasHeight) * (1.0f - static_cast<float>(cfg.rainbowGeom.centerY) / 100.0f);

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
    if (cfg.haloGeom.radius <= 0 || strength <= 0.004f) return;

    float minSide = static_cast<float>(std::min(g_canvasWidth, g_canvasHeight));
    float radius = minSide * (static_cast<float>(cfg.haloGeom.radius) / 100.0f);
    if (radius < 4.0f) return;

    float cx = static_cast<float>(g_canvasWidth) * (static_cast<float>(cfg.haloGeom.centerX) / 100.0f);
    float cy = static_cast<float>(g_canvasHeight) * (1.0f - static_cast<float>(cfg.haloGeom.centerY) / 100.0f);

    D2D1_COLOR_F base = cfg.hasCustomHaloColor ? cfg.colorHalo : D2D1::ColorF(1.0f, 0.96f, 0.84f, 0.30f);
    float pulse = 0.94f + 0.06f * static_cast<float>(std::sin(timeSec * 1.8));

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

void RenderFrames(const Settings& cfg, const GeneralEffectsState& fx,
                  const std::vector<VisibleWindow>& windows,
                  int bottomLimitY, float precipVx, double timeSec) {
    float bottomRelY = static_cast<float>(bottomLimitY - g_canvasTop);
    float s = static_cast<float>(cfg.particleScale);

    if (g_desktopOverlayHwnd && EnsureSurface(g_desktopSurface, g_canvasWidth, g_canvasHeight, cfg.colorSnow, cfg.hasCustomSnowColor)) {
        RECT bindRect = {0, 0, g_canvasWidth, g_canvasHeight};
        g_desktopSurface.rt->BindDC(g_desktopSurface.memDC, &bindRect);
        g_desktopSurface.rt->BeginDraw();
        g_desktopSurface.rt->Clear(D2D1::ColorF(0.0f, 0.0f, 0.0f, 0.0f));

        float k = static_cast<float>(cfg.effectsIntensity) / 25.0f;
        float hFloat = static_cast<float>(g_canvasHeight);

        if (fx.clear) {
            D2D1_COLOR_F cTop = cfg.hasCustomClearColor ? cfg.colorClear : D2D1::ColorF(1.0f, 0.94f, 0.72f, 0.16f);
            D2D1_COLOR_F cBot = cTop; cBot.a *= 0.2f;
            DrawVerticalGradientTint(g_desktopSurface.rt, cTop, cBot, 0.0f, hFloat, k);
        }
        if (fx.partlyCloudy) {
            D2D1_COLOR_F cTop = cfg.hasCustomPartlyCloudyColor ? cfg.colorPartlyCloudy : D2D1::ColorF(0.90f, 0.93f, 0.97f, 0.18f);
            D2D1_COLOR_F cBot = cTop; cBot.a *= 0.35f;
            DrawVerticalGradientTint(g_desktopSurface.rt, cTop, cBot, 0.0f, hFloat, k);
        }
        if (fx.overcast) {
            D2D1_COLOR_F cTop = cfg.hasCustomOvercastColor ? cfg.colorOvercast : D2D1::ColorF(0.50f, 0.55f, 0.62f, 0.28f);
            D2D1_COLOR_F cBot = cTop; cBot.a *= 0.65f;
            DrawVerticalGradientTint(g_desktopSurface.rt, cTop, cBot, 0.0f, hFloat, k);
        }
        if (fx.dust) {
            D2D1_COLOR_F cTop = cfg.hasCustomDustColor ? cfg.colorDust : D2D1::ColorF(0.84f, 0.68f, 0.45f, 0.10f);
            D2D1_COLOR_F cBot = cfg.hasCustomDustColor ? cfg.colorDust : D2D1::ColorF(0.84f, 0.68f, 0.45f, 0.26f);
            DrawVerticalGradientTint(g_desktopSurface.rt, cTop, cBot, 0.0f, hFloat, k);
        }
        if (fx.fog) {
            D2D1_COLOR_F cTop = cfg.hasCustomFogColor ? cfg.colorFog : D2D1::ColorF(0.84f, 0.88f, 0.92f, 0.14f);
            D2D1_COLOR_F cBot = cfg.hasCustomFogColor ? cfg.colorFog : D2D1::ColorF(0.84f, 0.88f, 0.92f, 0.34f);
            DrawVerticalGradientTint(g_desktopSurface.rt, cTop, cBot, 0.0f, hFloat, k);
        }
        if (fx.smog) {
            D2D1_COLOR_F cTop = cfg.hasCustomSmogColor ? cfg.colorSmog : D2D1::ColorF(0.54f, 0.48f, 0.40f, 0.16f);
            D2D1_COLOR_F cBot = cfg.hasCustomSmogColor ? cfg.colorSmog : D2D1::ColorF(0.54f, 0.48f, 0.40f, 0.36f);
            DrawVerticalGradientTint(g_desktopSurface.rt, cTop, cBot, 0.0f, hFloat, k);
        }
        if (fx.aurora) DrawSmoothAurora(g_desktopSurface.rt, cfg, k, timeSec);
        if (fx.mirage) DrawSmoothMirage(g_desktopSurface.rt, cfg, k, bottomLimitY, timeSec);
        if (fx.rainbow) DrawSmoothRainbow(g_desktopSurface.rt, cfg, k, timeSec);
        if (fx.halo) DrawSmoothHalo(g_desktopSurface.rt, cfg, k, timeSec);

        if (fx.thunderstorm && g_lightning.timer > 0.0f) {
            D2D1_COLOR_F tc = cfg.hasCustomThunderstormColor ? cfg.colorThunderstorm : D2D1::ColorF(0.86f, 0.93f, 1.0f, 0.95f);
            tc.a = std::clamp(g_lightning.timer * 4.2f * std::max(0.25f, k), 0.0f, 1.0f);
            ID2D1SolidColorBrush* tb = nullptr;
            if (SUCCEEDED(g_desktopSurface.rt->CreateSolidColorBrush(tc, &tb)) && tb) {
                float curX = g_lightning.xStart;
                float curY = 0.0f;
                int segs = 14;
                float stepY = std::max(20.0f, (bottomLimitY - g_canvasTop) * 0.72f / segs);
                for (int i = 0; i < segs; ++i) {
                    float t = static_cast<float>(i + 1) / segs;
                    float nextX = g_lightning.xStart + (g_lightning.xEnd - g_lightning.xStart) * t + ((i % 2 == 0) ? 16.0f : -16.0f);
                    float nextY = curY + stepY;
                    g_desktopSurface.rt->DrawLine(D2D1::Point2F(curX, curY), D2D1::Point2F(nextX, nextY), tb, 2.8f);
                    curX = nextX;
                    curY = nextY;
                }
                tb->Release();
            }
        }

        ID2D1SolidColorBrush* brush = nullptr;
        if (SUCCEEDED(g_desktopSurface.rt->CreateSolidColorBrush(D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.0f), &brush)) && brush) {
            for (const auto& p : g_falling) {
                DrawItemShape(g_desktopSurface, brush, cfg, p.kind, p.x, p.y, p.size, p.angle, p.flip, precipVx, p.alpha, p.shadeIdx);
            }

            for (const auto& ch : g_chunks) {
                DrawItemShape(g_desktopSurface, brush, cfg, ObjectKind::Snow, ch.x, ch.y, ch.size * 1.4f, 0.0f, 0.0f, ch.vx, 0.94f, 0);
            }

            if (cfg.enableBottomAccumulation) {
                DrawSnowCapSurface(g_desktopSurface.rt, g_bottomSnowCap, 0.0f, bottomRelY, cfg.colorSnow, cfg.hasCustomSnowColor, s);

                for (const auto& fo : g_fallen) {
                    if (fo.onWindow) continue;
                    float drawY = fo.fallingOff ? fo.relY : (bottomRelY + fo.relY);
                    if (!fo.fallingOff && fo.kind == ObjectKind::Rain) {
                        DrawRainPuddle(g_desktopSurface.rt, brush, cfg.colorRain, fo.relX, bottomRelY - 1.0f, fo.size, fo.alpha);
                    } else {
                        DrawItemShape(g_desktopSurface, brush, cfg, fo.kind, fo.relX, drawY, fo.size, fo.angle, fo.flip, fo.vx, fo.alpha, fo.shadeIdx);
                    }
                }
                for (const auto& pile : g_piles) {
                    if (pile.onWindow) continue;
                    DrawFoliagePileShape(g_desktopSurface, brush, cfg, pile, pile.centerX, bottomRelY);
                }
                for (const auto& sb : g_snowballs) {
                    if (sb.onWindow) continue;
                    float drawY = sb.fallingOff ? sb.relY : (bottomRelY - sb.radius);
                    DrawSnowballShape(g_desktopSurface, brush, cfg, sb, sb.relX, drawY);
                }
            }
            brush->Release();
        }

        if (FAILED(g_desktopSurface.rt->EndDraw())) {
            CleanupSurface(g_desktopSurface);
        } else {
            PresentSurface(g_desktopOverlayHwnd, g_desktopSurface);
        }
    }

    if (g_topWindowsOverlayHwnd && EnsureSurface(g_topWindowsSurface, g_canvasWidth, g_canvasHeight, cfg.colorSnow, cfg.hasCustomSnowColor)) {
        RECT bindRect = {0, 0, g_canvasWidth, g_canvasHeight};
        g_topWindowsSurface.rt->BindDC(g_topWindowsSurface.memDC, &bindRect);
        g_topWindowsSurface.rt->BeginDraw();
        g_topWindowsSurface.rt->Clear(D2D1::ColorF(0.0f, 0.0f, 0.0f, 0.0f));

        if (cfg.enableWindowAccumulation && !windows.empty()) {
            ID2D1SolidColorBrush* brush = nullptr;
            if (SUCCEEDED(g_topWindowsSurface.rt->CreateSolidColorBrush(D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.0f), &brush)) && brush) {
                for (size_t i = windows.size(); i-- > 0;) {
                    const VisibleWindow& vw = windows[i];
                    g_topWindowsSurface.rt->PushAxisAlignedClip(
                        D2D1::RectF(static_cast<float>(vw.rect.left), static_cast<float>(vw.rect.top),
                                    static_cast<float>(vw.rect.right), static_cast<float>(vw.rect.bottom)),
                        D2D1_ANTIALIAS_MODE_ALIASED);
                    g_topWindowsSurface.rt->Clear(D2D1::ColorF(0.0f, 0.0f, 0.0f, 0.0f));
                    g_topWindowsSurface.rt->PopAxisAlignedClip();

                    auto capIt = g_windowSnowCaps.find(vw.hwnd);
                    if (capIt != g_windowSnowCaps.end()) {
                        DrawSnowCapSurface(g_topWindowsSurface.rt, capIt->second,
                                           static_cast<float>(vw.rect.left), static_cast<float>(vw.rect.top),
                                           cfg.colorSnow, cfg.hasCustomSnowColor, s);
                    }

                    for (const auto& fo : g_fallen) {
                        if (!fo.onWindow || fo.hostWindow != vw.hwnd) continue;
                        float drawX = static_cast<float>(vw.rect.left) + fo.relX;
                        float drawY = static_cast<float>(vw.rect.top) + fo.relY;
                        DrawItemShape(g_topWindowsSurface, brush, cfg, fo.kind, drawX, drawY, fo.size, fo.angle, fo.flip, fo.vx, fo.alpha, fo.shadeIdx);
                    }
                    for (const auto& pile : g_piles) {
                        if (!pile.onWindow || pile.hostWindow != vw.hwnd) continue;
                        float drawX = static_cast<float>(vw.rect.left) + pile.centerX;
                        float drawY = static_cast<float>(vw.rect.top);
                        DrawFoliagePileShape(g_topWindowsSurface, brush, cfg, pile, drawX, drawY);
                    }
                    for (const auto& sb : g_snowballs) {
                        if (!sb.onWindow || sb.hostWindow != vw.hwnd) continue;
                        float drawX = static_cast<float>(vw.rect.left) + sb.relX;
                        float drawY = static_cast<float>(vw.rect.top) - sb.radius;
                        DrawSnowballShape(g_topWindowsSurface, brush, cfg, sb, drawX, drawY);
                    }
                }
                brush->Release();
            }
        }

        if (FAILED(g_topWindowsSurface.rt->EndDraw())) {
            CleanupSurface(g_topWindowsSurface);
        } else {
            PresentSurface(g_topWindowsOverlayHwnd, g_topWindowsSurface);
        }
    }
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

void UpdateCapPhysics(SnowCap& cap, int baseLeft, int baseTop, float vx, float vy, float dTop,
                      float shakeSpeedThreshold, float inertia, float scale, float dt, std::mt19937& rng) {
    int width = static_cast<int>(cap.cols.size());
    if (width < 4) return;

    float prevVy = cap.vy;
    cap.vx = cap.vx * 0.5f + vx * 0.5f;
    cap.vy = cap.vy * 0.5f + vy * 0.5f;

    cap.shakeTime += dt;
    if (std::abs(cap.vx) > shakeSpeedThreshold) {
        float dir = (cap.vx > 0.0f) ? 1.0f : -1.0f;
        if (cap.shakeDir != 0.0f && dir != cap.shakeDir && cap.shakeTime < 0.32f) {
            float share = std::clamp(cap.shakeSpeed / (scale * 2400.0f), 0.22f, 0.65f);
            for (int c = 0; c + 3 <= width; c += 3) {
                float area = 0.0f, top = 0.0f;
                for (int k = c; k < c + 3; ++k) top = std::max(top, cap.cols[k].h);
                if (top < 0.5f || ((rng() % 100) > static_cast<int>(share * 100.0f))) continue;
                for (int k = c; k < c + 3; ++k) {
                    area += cap.cols[k].h;
                    cap.cols[k].h = 0.0f;
                }
                SpawnSnowChunk(static_cast<float>(baseLeft + c + 1), static_cast<float>(baseTop) - top,
                               area, cap.shakeDir * cap.shakeSpeed * 0.28f * inertia,
                               -60.0f - static_cast<float>(rng() % 140), cap.hwnd, false, scale);
            }
        }
        if (dir != cap.shakeDir) cap.shakeSpeed = 0.0f;
        cap.shakeDir = dir;
        cap.shakeTime = 0.0f;
        cap.shakeSpeed = std::max(cap.shakeSpeed, std::abs(cap.vx));
    } else if (cap.shakeTime > 0.32f) {
        cap.shakeDir = 0.0f;
    }

    float minToss = kMinTossSpeed * scale;
    float maxToss = kMaxTossSpeed * scale;
    bool launch = false;
    float tossSpeed = 0.0f;
    if (cap.vy < cap.carry) {
        cap.carry = cap.vy;
    } else if (cap.carry < -minToss && cap.vy > cap.carry * 0.35f) {
        launch = true;
        tossSpeed = std::max(cap.carry * kTossFactor * inertia, -maxToss);
        cap.carry = 0.0f;
    } else if (cap.vy > -minToss * 0.5f) {
        cap.carry = 0.0f;
    }

    float excess = dTop - std::max(prevVy, 0.0f) * dt;
    bool drop = excess > 3.0f * scale;
    float hang = (excess > 8.0f * scale)
        ? kHangSeconds * std::clamp((excess - 8.0f * scale) / (20.0f * scale), 0.3f, 1.0f)
        : 0.0f;

    if (cap.squash != 0.0f || cap.squashVel != 0.0f) {
        cap.squashVel += (-220.0f * cap.squash - 16.0f * cap.squashVel) * dt;
        cap.squash = std::clamp(cap.squash + cap.squashVel * dt, -0.35f, 0.35f);
        if (std::abs(cap.squash) < 0.002f && std::abs(cap.squashVel) < 0.02f) {
            cap.squash = cap.squashVel = 0.0f;
        }
    }

    if (!cap.airborne && !launch && !drop) return;

    bool anyInAir = false;
    float impact = 0.0f;
    for (int c = 0; c < width; ++c) {
        SnowColumn& col = cap.cols[c];
        bool inAir = (col.lift > 0.0f || col.vel < 0.0f || col.hang > 0.0f);
        if (inAir) {
            col.lift += dTop;
        } else if (drop) {
            col.lift = dTop;
            col.vel = std::max(prevVy, 0.0f);
            col.hang = hang * (0.8f + 0.4f * CapNoise(cap, c, 3, 60.0f * scale));
        } else if (launch) {
            col.vel = tossSpeed;
            col.lift = 0.0f;
        } else {
            continue;
        }

        if (col.lift < 0.0f) {
            col.lift = 0.0f;
            col.hang = 0.0f;
            col.vel = std::max(std::min(col.vel, cap.vy), -maxToss);
        }
        if (col.hang > 0.0f) {
            col.hang -= dt;
            anyInAir = true;
            continue;
        }
        col.vel += kGravity * scale * dt;
        col.lift -= col.vel * dt;
        if (col.lift <= 0.0f) {
            col.lift = 0.0f;
            if (col.vel > kBounceSpeed * scale) {
                impact = std::max(impact, col.vel / scale);
                col.vel *= -0.2f;
            } else {
                col.vel = 0.0f;
            }
        }
        if (col.lift > 0.0f || col.vel < 0.0f) anyInAir = true;
    }
    cap.airborne = anyInAir;
    if (launch) cap.squashVel += 1.4f;
    if (impact > 0.0f) cap.squashVel -= std::min(impact * 0.003f, 3.5f);
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

    g_bottomSnowCap.isBottom = true;
    g_bottomSnowCap.seed = Hash32(0x12345678u);

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

        DWORD exStyle = WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_NOACTIVATE | WS_EX_TOOLWINDOW;
        if (!g_desktopOverlayHwnd) {
            g_desktopOverlayHwnd = CreateWindowExW(
                exStyle, wc.lpszClassName, L"DesktopWeatherDesktopOverlay", WS_POPUP,
                g_canvasLeft, g_canvasTop, g_canvasWidth, g_canvasHeight,
                nullptr, nullptr, wc.hInstance, nullptr);
            PositionDesktopOverlay(g_desktopOverlayHwnd, cfg.layerAttachMode);
        }
        if (!g_topWindowsOverlayHwnd) {
            g_topWindowsOverlayHwnd = CreateWindowExW(
                exStyle, wc.lpszClassName, L"DesktopWeatherTopWindowsOverlay", WS_POPUP,
                g_canvasLeft, g_canvasTop, g_canvasWidth, g_canvasHeight,
                nullptr, nullptr, wc.hInstance, nullptr);
            PositionTopWindowsOverlay(g_topWindowsOverlayHwnd);
        }

        if (++zOrderTick >= 30) {
            zOrderTick = 0;
            PositionDesktopOverlay(g_desktopOverlayHwnd, cfg.layerAttachMode);
            PositionTopWindowsOverlay(g_topWindowsOverlayHwnd);
        }

        MSG msg;
        while (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        }

        auto now = std::chrono::steady_clock::now();
        float dt = std::chrono::duration<float>(now - lastTime).count();
        double timeSec = std::chrono::duration<double>(now - startTime).count();
        lastTime = now;
        dt = std::clamp(dt, 0.001f, 0.05f);
        float s = static_cast<float>(cfg.particleScale);

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
        float precipVy = static_cast<float>(cfg.precipFallSpeedMps) * 42.0f * s;

        float seasonalVx = ComputeHorizontalSpeedPxPerSec(cfg.seasonalFallDirection, cfg.seasonalFallSpeedMps, forecastWindSign, forecastWindSpd);
        float seasonalVy = static_cast<float>(cfg.seasonalFallSpeedMps) * 32.0f * s;

        size_t targetP = activePrecip
            ? static_cast<size_t>((g_canvasWidth / 1000.0) * GetIntensityForKind(cfg, false) * 1.4)
            : 0;
        size_t targetS = activeSeasonal
            ? static_cast<size_t>((g_canvasWidth / 1000.0) * GetIntensityForKind(cfg, true) * 1.2)
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
            SpawnFallingItem(it, rng, precipKind, false, cfg.particleScale, precipVx, true);
            nextFalling.push_back(it);
            ++curP;
        }
        while (curS < targetS) {
            FallingItem it;
            SpawnFallingItem(it, rng, seasonalKind, true, cfg.particleScale, seasonalVx, true);
            nextFalling.push_back(it);
            ++curS;
        }
        g_falling.swap(nextFalling);

        std::vector<std::wstring> excluded = SplitExcluded(cfg.excludedProcesses);
        std::vector<VisibleWindow> windows;
        EnumCtx ctx{&excluded, &windows};
        EnumWindows(EnumWindowsProc, reinterpret_cast<LPARAM>(&ctx));

        int bottomLimitY = ComputeBottomLimitY(cfg);
        float bottomRelY = static_cast<float>(bottomLimitY - g_canvasTop);

        if (static_cast<int>(g_bottomSnowCap.cols.size()) != g_canvasWidth) {
            g_bottomSnowCap.cols.assign(g_canvasWidth, SnowColumn{});
        }
        if (!cfg.enableBottomAccumulation || cfg.precipMaxAccumulated <= 0) {
            for (auto& c : g_bottomSnowCap.cols) c.h = 0.0f;
        }

        float shakeSpeedThreshold = 1350.0f - (cfg.windowShakeSensitivity * 11.0f);
        shakeSpeedThreshold = std::max(140.0f, shakeSpeedThreshold);
        float inertia = static_cast<float>(cfg.windowInertiaFactor);

        for (size_t idx = 0; idx < windows.size(); ++idx) {
            const VisibleWindow& vw = windows[idx];
            HWND h = vw.hwnd;

            auto& cap = g_windowSnowCaps[h];
            cap.hwnd = h;
            if (cap.seed == 0) cap.seed = Hash32(static_cast<uint32_t>(reinterpret_cast<uintptr_t>(h)));
            float dTop = static_cast<float>(vw.rect.top - cap.lastRect.top);
            SyncSnowCapWidth(cap, vw.rect, vw.rect.left, vw.rect.top);

            auto& wm = g_windows[h];
            float cx = (vw.rect.left + vw.rect.right) * 0.5f;
            float cy = (vw.rect.top + vw.rect.bottom) * 0.5f;
            float vx = wm.hasPrev ? ((cx - wm.prevCenterX) / dt) : 0.0f;
            float vy = wm.hasPrev ? ((cy - wm.prevCenterY) / dt) : 0.0f;

            if (cfg.enableWindowAccumulation && cfg.precipMaxAccumulated > 0) {
                UpdateCapPhysics(cap, vw.rect.left, vw.rect.top, vx, vy, dTop,
                                 shakeSpeedThreshold, inertia, s, dt, rng);
            } else {
                for (auto& c : cap.cols) c.h = 0.0f;
            }

            if (wm.hasPrev) {
                wm.shakeTimer += dt;
                if (std::abs(vx) > shakeSpeedThreshold) {
                    float dir = (vx > 0.0f) ? 1.0f : -1.0f;
                    if (wm.shakeDir != 0.0f && dir != wm.shakeDir && wm.shakeTimer < 0.35f) {
                        float tossVx = wm.shakeDir * std::min(650.0f, std::abs(wm.prevVx) * 0.45f) * inertia;
                        for (auto& fo : g_fallen) {
                            if (fo.onWindow && fo.hostWindow == h && !fo.fallingOff && fo.kind != ObjectKind::Rain) {
                                if ((rng() % 100) < 42) {
                                    fo.onWindow = false;
                                    fo.fallingOff = true;
                                    fo.relX = static_cast<float>(vw.rect.left) + fo.relX;
                                    fo.relY = static_cast<float>(vw.rect.top) + fo.relY;
                                    fo.vx = tossVx * (0.4f + 0.4f * ((rng() % 100) * 0.01f));
                                    fo.vy = -80.0f - static_cast<float>(rng() % 140);
                                }
                            }
                        }
                        for (auto& sb : g_snowballs) {
                            if (sb.onWindow && sb.hostWindow == h && !sb.fallingOff) {
                                if ((rng() % 100) < 48) {
                                    sb.onWindow = false;
                                    sb.fallingOff = true;
                                    sb.relX = static_cast<float>(vw.rect.left) + sb.relX;
                                    sb.relY = static_cast<float>(vw.rect.top) - sb.radius;
                                    sb.vx = tossVx * 0.5f;
                                    sb.vy = -90.0f - static_cast<float>(rng() % 120);
                                    sb.squashVel += 1.4f;
                                }
                            }
                        }
                    }
                    wm.shakeDir = dir;
                    wm.shakeTimer = 0.0f;
                    wm.prevVx = vx;
                } else if (wm.shakeTimer > 0.35f) {
                    wm.shakeDir = 0.0f;
                }
            }
            wm.rect = vw.rect;
            wm.prevCenterX = cx;
            wm.prevCenterY = cy;
            wm.hasPrev = true;
        }

        for (auto it = g_windows.begin(); it != g_windows.end();) {
            bool stillExists = false;
            for (const auto& vw : windows) {
                if (vw.hwnd == it->first) { stillExists = true; break; }
            }
            if (!stillExists) {
                HWND closedHwnd = it->first;
                RECT lastRect = it->second.rect;
                auto capIt = g_windowSnowCaps.find(closedHwnd);
                if (capIt != g_windowSnowCaps.end()) {
                    DropCapRangeToChunks(capIt->second, lastRect.left, lastRect.top, 0,
                                         static_cast<int>(capIt->second.cols.size()), nullptr);
                    g_windowSnowCaps.erase(capIt);
                }
                for (auto& fo : g_fallen) {
                    if (fo.onWindow && fo.hostWindow == closedHwnd) {
                        fo.onWindow = false;
                        fo.fallingOff = true;
                        fo.relX = static_cast<float>(lastRect.left) + fo.relX;
                        fo.relY = static_cast<float>(lastRect.top) + fo.relY;
                        fo.vy = 70.0f;
                    }
                }
                for (auto& sb : g_snowballs) {
                    if (sb.onWindow && sb.hostWindow == closedHwnd) {
                        sb.onWindow = false;
                        sb.fallingOff = true;
                        sb.relX = static_cast<float>(lastRect.left) + sb.relX;
                        sb.relY = static_cast<float>(lastRect.top) - sb.radius;
                        sb.vy = 80.0f;
                    }
                }
                g_piles.erase(
                    std::remove_if(g_piles.begin(), g_piles.end(),
                                   [closedHwnd](const FoliagePile& p) { return p.onWindow && p.hostWindow == closedHwnd; }),
                    g_piles.end());
                it = g_windows.erase(it);
            } else {
                ++it;
            }
        }

        if (cfg.precipLifetimeMin >= 0.0) {
            float meltRate = ComputeMaxCapHeightPx(cfg, false) / std::max(3.0f, static_cast<float>(cfg.precipLifetimeMin * 60.0));
            for (auto& c : g_bottomSnowCap.cols) {
                if (c.h > 0.0f) c.h = std::max(0.0f, c.h - meltRate * dt);
            }
            for (auto& kv : g_windowSnowCaps) {
                for (auto& c : kv.second.cols) {
                    if (c.h > 0.0f) c.h = std::max(0.0f, c.h - meltRate * dt);
                }
            }
        }

        auto countAccumulated = [&](bool isS) -> int {
            int c = 0;
            for (const auto& fo : g_fallen) {
                if (fo.isSeasonalLayer == isS) ++c;
            }
            for (const auto& pile : g_piles) {
                if (pile.isSeasonalLayer == isS) c += static_cast<int>(pile.members.size());
            }
            return c;
        };

        bool anyAccumEnabled = cfg.enableBottomAccumulation || cfg.enableWindowAccumulation;

        for (size_t i = 0; i < g_falling.size(); ++i) {
            FallingItem& p = g_falling[i];
            float vx = p.isSeasonalLayer ? seasonalVx : precipVx;
            float vy = p.isSeasonalLayer ? seasonalVy : precipVy;
            p.swayPhase += dt * 3.0f;
            p.angle += p.spin * dt * 20.0f;
            p.flip += p.flipSpeed * dt;

            float prevY = p.y;
            float sway = (p.kind == ObjectKind::Rain) ? 0.0f : std::sin(p.swayPhase) * 18.0f;
            p.x += (vx + sway) * dt;
            p.y += vy * dt;

            int maxAcc = GetMaxAccumulatedForKind(cfg, p.isSeasonalLayer);
            bool landed = false;
            bool isSnowKind = (p.kind == ObjectKind::Snow || p.kind == ObjectKind::ExtraSnow);

            int hitWinIdx = FindTopWindowLanding(windows, p.x, prevY, p.y);
            if (hitWinIdx >= 0) {
                const VisibleWindow& vw = windows[hitWinIdx];
                if (anyAccumEnabled && cfg.enableWindowAccumulation && maxAcc > 0 && p.kind != ObjectKind::Rain) {
                    if (isSnowKind) {
                        auto capIt = g_windowSnowCaps.find(vw.hwnd);
                        if (capIt != g_windowSnowCaps.end() && !capIt->second.cols.empty()) {
                            int maxColIdx = static_cast<int>(capIt->second.cols.size()) - 1;
                            int col = std::clamp(static_cast<int>(p.x) - static_cast<int>(vw.rect.left), 0, maxColIdx);
                            AddSnowToCap(capIt->second, col, 1.8f * s + 0.6f * p.size, ComputeMaxCapHeightPx(cfg, false), s);
                        }
                        landed = true;
                    } else if (countAccumulated(p.isSeasonalLayer) < maxAcc) {
                        FallenItem fo;
                        fo.kind = p.kind;
                        fo.isSeasonalLayer = p.isSeasonalLayer;
                        fo.onWindow = true;
                        fo.hostWindow = vw.hwnd;
                        fo.relX = std::clamp(p.x - vw.rect.left, 2.0f, std::max(3.0f, static_cast<float>(vw.rect.right - vw.rect.left) - 2.0f));
                        fo.relY = -p.size * 0.28f;
                        fo.size = p.size;
                        fo.angle = (rng() % 100 - 50) * 0.01f;
                        fo.flip = 0.65f + (rng() % 30) * 0.01f;
                        fo.alpha = p.alpha;
                        fo.shadeIdx = p.shadeIdx;
                        g_fallen.push_back(fo);
                        landed = true;
                    }
                }
            }

            if (!landed && p.y >= bottomRelY - p.size * 0.30f) {
                bool blockedByWindow = IsPointOccludedAbove(windows, windows.size(), p.x, bottomRelY - 2.0f);
                if (!blockedByWindow && anyAccumEnabled && cfg.enableBottomAccumulation && maxAcc > 0) {
                    if (isSnowKind) {
                        int col = std::clamp(static_cast<int>(p.x), 0, static_cast<int>(g_bottomSnowCap.cols.size()) - 1);
                        AddSnowToCap(g_bottomSnowCap, col, 2.0f * s + 0.7f * p.size, ComputeMaxCapHeightPx(cfg, true), s);
                        landed = true;
                    } else if (countAccumulated(p.isSeasonalLayer) < maxAcc) {
                        FallenItem fo;
                        fo.kind = p.kind;
                        fo.isSeasonalLayer = p.isSeasonalLayer;
                        fo.onWindow = false;
                        fo.hostWindow = nullptr;
                        fo.relX = p.x;
                        fo.relY = (p.kind == ObjectKind::Rain) ? -1.0f : (-p.size * 0.28f);
                        fo.size = p.size;
                        fo.angle = (rng() % 100 - 50) * 0.01f;
                        fo.flip = 0.65f + (rng() % 30) * 0.01f;
                        fo.alpha = p.alpha;
                        fo.shadeIdx = p.shadeIdx;
                        g_fallen.push_back(fo);
                        landed = true;
                    }
                }
            }

            if (landed || p.y > g_canvasHeight + 30.0f || p.x < -140.0f || p.x > g_canvasWidth + 140.0f) {
                SpawnFallingItem(p, rng, p.kind, p.isSeasonalLayer, cfg.particleScale, vx, false);
            }
        }

        for (size_t i = 0; i < g_chunks.size();) {
            SnowChunk& ch = g_chunks[i];
            float prevY = ch.y;
            ch.vy = std::min(ch.vy + kGravity * 0.5f * s * dt, 700.0f * s);
            ch.vx *= std::exp(-2.0f * dt);
            ch.x += ch.vx * dt;
            ch.y += ch.vy * dt;

            bool settled = false;
            int hitIdx = FindTopWindowLanding(windows, ch.x, prevY, ch.y);
            if (hitIdx >= 0 && windows[hitIdx].hwnd != ch.ignoreHwnd && cfg.enableWindowAccumulation) {
                auto capIt = g_windowSnowCaps.find(windows[hitIdx].hwnd);
                if (capIt != g_windowSnowCaps.end() && !capIt->second.cols.empty()) {
                    int maxColIdx = static_cast<int>(capIt->second.cols.size()) - 1;
                    int col = std::clamp(static_cast<int>(ch.x) - static_cast<int>(windows[hitIdx].rect.left), 0, maxColIdx);
                    AddSnowToCap(capIt->second, col, ch.area / kSnowKernelSum, ComputeMaxCapHeightPx(cfg, false), s);
                    settled = true;
                }
            }
            if (!settled && !ch.ignoreBottom && ch.y >= bottomRelY && cfg.enableBottomAccumulation) {
                if (!IsPointOccludedAbove(windows, windows.size(), ch.x, bottomRelY - 2.0f)) {
                    int col = std::clamp(static_cast<int>(ch.x), 0, static_cast<int>(g_bottomSnowCap.cols.size()) - 1);
                    AddSnowToCap(g_bottomSnowCap, col, ch.area / kSnowKernelSum, ComputeMaxCapHeightPx(cfg, true), s);
                    settled = true;
                }
            }
            if (settled || ch.y > g_canvasHeight + 20.0f || ch.x < -80.0f || ch.x > g_canvasWidth + 80.0f) {
                g_chunks.erase(g_chunks.begin() + i);
            } else {
                ++i;
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
        float maxBallR = static_cast<float>(cfg.snowballMaxRadiusPx);
        float maxLeafPileH = static_cast<float>(cfg.leafPileMaxHeightPx);

        if (cfg.cursorAction != CursorActionMode::None && cMoveLen > 0.5f) {
            float dirX = cDx / cMoveLen;
            if (cfg.enableBottomAccumulation && std::abs(cY - bottomRelY) < cRad) {
                int from = std::clamp(static_cast<int>(cX - cRad * 0.6f), 0, static_cast<int>(g_bottomSnowCap.cols.size()) - 1);
                int to = std::clamp(static_cast<int>(cX + cRad * 0.6f), 0, static_cast<int>(g_bottomSnowCap.cols.size()) - 1);
                float scooped = 0.0f;
                for (int c = from; c <= to; ++c) {
                    if (g_bottomSnowCap.cols[c].h > 0.2f) {
                        scooped += g_bottomSnowCap.cols[c].h;
                        g_bottomSnowCap.cols[c].h = 0.0f;
                    }
                }
                if (cfg.cursorAction == CursorActionMode::Move && scooped > 1.5f) {
                    Snowball* bottomBall = nullptr;
                    for (auto& sb : g_snowballs) {
                        if (!sb.onWindow && !sb.fallingOff) { bottomBall = &sb; break; }
                    }
                    if (!bottomBall) {
                        Snowball sb;
                        sb.kind = ObjectKind::Snow;
                        sb.isSeasonalLayer = false;
                        sb.onWindow = false;
                        sb.relX = cX;
                        sb.vx = dirX * 65.0f;
                        sb.radius = std::clamp(std::sqrt(scooped * 0.45f), 6.0f, maxBallR);
                        g_snowballs.push_back(sb);
                    } else if (bottomBall->radius < maxBallR) {
                        bottomBall->radius = std::min(maxBallR, std::sqrt(bottomBall->radius * bottomBall->radius + scooped * 0.35f));
                        bottomBall->vx += dirX * 26.0f;
                    }
                }
            }

            if (cfg.enableWindowAccumulation) {
                for (size_t idx = 0; idx < windows.size(); ++idx) {
                    const VisibleWindow& vw = windows[idx];
                    if (std::abs(cY - static_cast<float>(vw.rect.top)) > cRad) continue;
                    if (cX < vw.rect.left - cRad || cX > vw.rect.right + cRad) continue;
                    if (IsPointOccludedAbove(windows, idx, cX, static_cast<float>(vw.rect.top) - 2.0f)) continue;

                    auto capIt = g_windowSnowCaps.find(vw.hwnd);
                    if (capIt == g_windowSnowCaps.end() || capIt->second.cols.empty()) continue;
                    SnowCap& cap = capIt->second;
                    int maxColIdx = static_cast<int>(cap.cols.size()) - 1;
                    int from = std::clamp(static_cast<int>(cX - cRad * 0.6f) - static_cast<int>(vw.rect.left), 0, maxColIdx);
                    int to = std::clamp(static_cast<int>(cX + cRad * 0.6f) - static_cast<int>(vw.rect.left), 0, maxColIdx);
                    float scooped = 0.0f;
                    for (int c = from; c <= to; ++c) {
                        if (cap.cols[c].h > 0.2f) {
                            scooped += cap.cols[c].h;
                            cap.cols[c].h = 0.0f;
                        }
                    }
                    if (cfg.cursorAction == CursorActionMode::Move && scooped > 1.5f) {
                        Snowball* winBall = nullptr;
                        for (auto& sb : g_snowballs) {
                            if (sb.onWindow && sb.hostWindow == vw.hwnd && !sb.fallingOff) { winBall = &sb; break; }
                        }
                        if (!winBall) {
                            Snowball sb;
                            sb.kind = ObjectKind::Snow;
                            sb.isSeasonalLayer = false;
                            sb.onWindow = true;
                            sb.hostWindow = vw.hwnd;
                            sb.relX = std::clamp(cX - vw.rect.left, 4.0f, std::max(5.0f, static_cast<float>(vw.rect.right - vw.rect.left) - 4.0f));
                            sb.vx = dirX * 55.0f;
                            sb.radius = std::clamp(std::sqrt(scooped * 0.45f), 6.0f, maxBallR);
                            g_snowballs.push_back(sb);
                        } else if (winBall->radius < maxBallR) {
                            winBall->radius = std::min(maxBallR, std::sqrt(winBall->radius * winBall->radius + scooped * 0.35f));
                            winBall->vx += dirX * 22.0f;
                        }
                    }
                }
            }
        }

        for (size_t i = 0; i < g_fallen.size();) {
            FallenItem& fo = g_fallen[i];
            fo.ageSec += dt;

            double lifeMin = GetLifetimeMinForKind(cfg, fo.isSeasonalLayer);
            if (lifeMin >= 0.0) {
                float lifeSec = static_cast<float>(lifeMin * 60.0);
                if (fo.ageSec >= lifeSec) fo.alpha -= dt * 1.5f;
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
                    absX = static_cast<float>(it->second.rect.left) + fo.relX;
                    absY = static_cast<float>(it->second.rect.top) + fo.relY;
                }
            } else if (!fo.fallingOff) {
                absY = bottomRelY + fo.relY;
            }

            float dist = std::hypot(absX - cX, absY - cY);
            if (cfg.cursorAction == CursorActionMode::Clear && dist < cRad) {
                g_fallen.erase(g_fallen.begin() + i);
                continue;
            }

            bool isFoliage = (fo.kind == ObjectKind::AutumnLeaves || fo.kind == ObjectKind::Petals);
            bool isPuddle = (!fo.onWindow && !fo.fallingOff && fo.kind == ObjectKind::Rain);

            if (cfg.cursorAction == CursorActionMode::Move && !isPuddle && isFoliage && dist < cRad && cMoveLen > 0.6f) {
                float dirX = cDx / cMoveLen;
                FoliagePile* surfacePile = nullptr;
                for (auto& pile : g_piles) {
                    if (pile.onWindow == fo.onWindow && pile.hostWindow == fo.hostWindow) {
                        surfacePile = &pile;
                        break;
                    }
                }
                if (!surfacePile) {
                    FoliagePile newPile;
                    newPile.kind = fo.kind;
                    newPile.isSeasonalLayer = fo.isSeasonalLayer;
                    newPile.onWindow = fo.onWindow;
                    newPile.hostWindow = fo.hostWindow;
                    newPile.centerX = fo.relX;
                    newPile.halfWidth = 42.0f;
                    newPile.height = fo.size * 0.6f;
                    g_piles.push_back(newPile);
                    surfacePile = &g_piles.back();
                }
                surfacePile->kind = fo.kind;
                surfacePile->isSeasonalLayer = fo.isSeasonalLayer;
                AddItemToFoliagePile(*surfacePile, fo.relX, fo.size, fo.angle, fo.flip, fo.alpha, fo.shadeIdx, maxLeafPileH, rng);
                surfacePile->vx += dirX * 30.0f;
                g_fallen.erase(g_fallen.begin() + i);
                continue;
            }

            if (fo.fallingOff) {
                fo.vy += 420.0f * dt;
                fo.relX += fo.vx * dt;
                fo.relY += fo.vy * dt;
                fo.angle += 2.5f * dt;
                if (fo.relY >= bottomRelY - fo.size * 0.28f) {
                    if (!cfg.enableBottomAccumulation || IsPointOccludedAbove(windows, windows.size(), fo.relX, bottomRelY - 2.0f)) {
                        g_fallen.erase(g_fallen.begin() + i);
                        continue;
                    }
                    fo.fallingOff = false;
                    fo.onWindow = false;
                    fo.vx = 0.0f;
                    fo.vy = 0.0f;
                    fo.relY = -fo.size * 0.28f;
                }
            }

            ++i;
        }

        for (size_t i = 0; i < g_piles.size();) {
            FoliagePile& pile = g_piles[i];
            pile.ageSec += dt;

            double lifeMin = GetLifetimeMinForKind(cfg, pile.isSeasonalLayer);
            if (lifeMin >= 0.0 && pile.ageSec >= lifeMin * 60.0) {
                for (auto& m : pile.members) m.alpha -= dt * 1.5f;
                if (!pile.members.empty() && pile.members.front().alpha <= 0.03f) {
                    g_piles.erase(g_piles.begin() + i);
                    continue;
                }
            }

            float absCenterX = pile.centerX;
            float absBaseY = bottomRelY;
            if (pile.onWindow) {
                auto it = g_windows.find(pile.hostWindow);
                if (it != g_windows.end()) {
                    absCenterX = static_cast<float>(it->second.rect.left) + pile.centerX;
                    absBaseY = static_cast<float>(it->second.rect.top);
                }
            }

            float dist = std::hypot(absCenterX - cX, (absBaseY - pile.height * 0.3f) - cY);
            if (cfg.cursorAction == CursorActionMode::Clear && dist < cRad + pile.halfWidth * 0.5f) {
                g_piles.erase(g_piles.begin() + i);
                continue;
            }
            if (cfg.cursorAction == CursorActionMode::Move && dist < cRad + pile.halfWidth * 0.5f && cMoveLen > 0.5f) {
                pile.vx += (cDx / cMoveLen) * 160.0f * dt;
            }

            pile.centerX += pile.vx * dt;
            pile.vx *= std::pow(0.14f, dt);

            if (pile.onWindow) {
                auto it = g_windows.find(pile.hostWindow);
                if (it != g_windows.end()) {
                    float w = static_cast<float>(std::max(10L, it->second.rect.right - it->second.rect.left));
                    pile.centerX = std::clamp(pile.centerX, pile.halfWidth * 0.5f, std::max(pile.halfWidth * 0.5f, w - pile.halfWidth * 0.5f));
                }
            } else {
                pile.centerX = std::clamp(pile.centerX, 0.0f, static_cast<float>(g_canvasWidth));
            }

            ++i;
        }

        for (size_t i = 0; i < g_snowballs.size();) {
            Snowball& sb = g_snowballs[i];
            sb.ageSec += dt;

            double lifeMin = GetLifetimeMinForKind(cfg, sb.isSeasonalLayer);
            if (lifeMin >= 0.0 && sb.ageSec >= lifeMin * 60.0) {
                sb.alpha -= dt * 1.5f;
                if (sb.alpha <= 0.03f) {
                    g_snowballs.erase(g_snowballs.begin() + i);
                    continue;
                }
            }

            if (sb.squash != 0.0f || sb.squashVel != 0.0f) {
                sb.squashVel += (-220.0f * sb.squash - 16.0f * sb.squashVel) * dt;
                sb.squash = std::clamp(sb.squash + sb.squashVel * dt, -0.35f, 0.35f);
                if (std::abs(sb.squash) < 0.002f && std::abs(sb.squashVel) < 0.02f) {
                    sb.squash = 0.0f;
                    sb.squashVel = 0.0f;
                }
            }

            if (sb.onWindow) {
                auto it = g_windows.find(sb.hostWindow);
                if (it != g_windows.end()) {
                    int w = it->second.rect.right - it->second.rect.left;
                    float absX = static_cast<float>(it->second.rect.left) + sb.relX;
                    float absY = static_cast<float>(it->second.rect.top) - sb.radius;

                    if (cfg.cursorAction == CursorActionMode::Clear && std::hypot(absX - cX, absY - cY) < cRad) {
                        g_snowballs.erase(g_snowballs.begin() + i);
                        continue;
                    }
                    if (cfg.cursorAction == CursorActionMode::Move && std::hypot(absX - cX, absY - cY) < cRad && cMoveLen > 0.5f) {
                        sb.vx += (cDx / cMoveLen) * 140.0f * dt;
                    }
                    sb.relX += sb.vx * dt;
                    sb.vx *= std::pow(0.15f, dt);

                    if (sb.radius < maxBallR && std::abs(sb.vx) > 2.0f) {
                        auto capIt = g_windowSnowCaps.find(sb.hostWindow);
                        if (capIt != g_windowSnowCaps.end() && !capIt->second.cols.empty()) {
                            int maxColIdx = static_cast<int>(capIt->second.cols.size()) - 1;
                            int cIdx = std::clamp(static_cast<int>(sb.relX), 0, maxColIdx);
                            float h = capIt->second.cols[cIdx].h;
                            if (h > 0.2f) {
                                capIt->second.cols[cIdx].h = 0.0f;
                                sb.radius = std::min(maxBallR, std::sqrt(sb.radius * sb.radius + h * 1.4f));
                            }
                        }
                    }

                    if (sb.relX < 0.0f || sb.relX > static_cast<float>(w)) {
                        sb.onWindow = false;
                        sb.fallingOff = true;
                        sb.relX = absX;
                        sb.relY = absY;
                        sb.vy = 90.0f;
                    }
                }
            } else if (sb.fallingOff) {
                sb.vy += 420.0f * dt;
                sb.relX += sb.vx * dt;
                sb.relY += sb.vy * dt;

                if (sb.relY + sb.radius >= bottomRelY) {
                    if (cfg.enableBottomAccumulation && !IsPointOccludedAbove(windows, windows.size(), sb.relX, bottomRelY - 2.0f)) {
                        int col = std::clamp(static_cast<int>(sb.relX), 0, static_cast<int>(g_bottomSnowCap.cols.size()) - 1);
                        AddSnowToCap(g_bottomSnowCap, col, sb.radius * 0.9f, ComputeMaxCapHeightPx(cfg, true), s);
                    }
                    g_snowballs.erase(g_snowballs.begin() + i);
                    continue;
                }
            } else {
                float absY = bottomRelY - sb.radius;
                if (cfg.cursorAction == CursorActionMode::Clear && std::hypot(sb.relX - cX, absY - cY) < cRad) {
                    g_snowballs.erase(g_snowballs.begin() + i);
                    continue;
                }
                if (cfg.cursorAction == CursorActionMode::Move && std::hypot(sb.relX - cX, absY - cY) < cRad && cMoveLen > 0.5f) {
                    sb.vx += (cDx / cMoveLen) * 190.0f * dt;
                }
                sb.relX = std::clamp(sb.relX + sb.vx * dt, sb.radius, static_cast<float>(std::max(10.0f, g_canvasWidth - sb.radius)));
                sb.vx *= std::pow(0.12f, dt);

                if (sb.radius < maxBallR && std::abs(sb.vx) > 2.0f) {
                    int cIdx = std::clamp(static_cast<int>(sb.relX), 0, static_cast<int>(g_bottomSnowCap.cols.size()) - 1);
                    float h = g_bottomSnowCap.cols[cIdx].h;
                    if (h > 0.2f) {
                        g_bottomSnowCap.cols[cIdx].h = 0.0f;
                        sb.radius = std::min(maxBallR, std::sqrt(sb.radius * sb.radius + h * 1.4f));
                    }
                }
            }

            ++i;
        }

        RenderFrames(cfg, activeFx, windows, bottomLimitY, precipVx, timeSec);

        int frameMs = 1000 / cfg.targetFps;
        std::this_thread::sleep_for(std::chrono::milliseconds(frameMs));
    }

    if (g_desktopOverlayHwnd) {
        DestroyWindow(g_desktopOverlayHwnd);
        g_desktopOverlayHwnd = nullptr;
    }
    if (g_topWindowsOverlayHwnd) {
        DestroyWindow(g_topWindowsOverlayHwnd);
        g_topWindowsOverlayHwnd = nullptr;
    }
    CleanupSurface(g_desktopSurface);
    CleanupSurface(g_topWindowsSurface);
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