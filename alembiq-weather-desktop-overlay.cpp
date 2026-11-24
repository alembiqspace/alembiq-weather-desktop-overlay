// ==WindhawkMod==
// @id              alembiq-weather-desktop-overlay
// @name            Desktop Weather & Particles Overlay
// @description     Weather effects (snow, rain, fog, wind, clear) and seasonal particles (snow, rain, leaves, poplar fluff, sakura) under desktop icons with window accumulation and shake physics.
// @version         0.6.1
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
  $description: "Affects fallen objects/snow caps only. clear = erase on touch (default); move = roll up to 3 snowballs into a snowman & 1 leaf/petal pile at bottom; none = ignore cursor."
  $options:
    - clear: Clear (erase on touch)
    - move: Move (up to 3 snowballs -> snowman & 1 pile at bottom)
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
  $description: "Max radius of each of the up to 3 bottom snowballs (8 to 120). Once full, the next snowball starts growing. Invalid/out-of-range resets to 34."
- leafPileMaxHeightPx: 54
  $name: "[Foliage Piles] Max height (px)"
  $description: "Maximum height of the single bottom leaf/petal mound in pixels (8 to 250). Invalid/out-of-range resets to 54."
- windowShakeSensitivity: 55
  $name: "[Windows] Shed sensitivity (1..100)"
  $description: "Sensitivity for detaching snow caps/fallen items when moving/shaking windows (1..100). Invalid/out-of-range resets to 55."
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

struct BottomSnowball {
    ObjectKind kind = ObjectKind::Snow;
    bool isSeasonalLayer = false;
    int slot = 0; // 0 = база, 1 = тело, 2 = голова
    float x = 0.0f;
    float vx = 0.0f;
    float radius = 8.0f;
    float lift = 0.0f;     // подъем при запрыгивании на шар ниже
    float liftVel = 0.0f;
    float squash = 0.0f;
    float squashVel = 0.0f;
    float alpha = 0.96f;
    float ageSec = 0.0f;
    bool stacked = false;  // запрыгнул на предыдущий шар
    bool full = false;     // достиг максимума и больше не растет
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

struct BottomFoliagePile {
    ObjectKind kind = ObjectKind::AutumnLeaves;
    bool isSeasonalLayer = false;
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
HHOOK g_mouseHook = nullptr;
std::atomic<bool> g_snowmanClickRequested{false};
std::atomic<long> g_clickScreenX{0};
std::atomic<long> g_clickScreenY{0};

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
std::vector<BottomSnowball> g_bottomSnowballs; // максимум 3 шара внизу экрана
BottomFoliagePile g_bottomPile;                 // максимум 1 куча листьев/лепестков внизу экрана
bool g_hasBottomPile = false;
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

double ParseDouble