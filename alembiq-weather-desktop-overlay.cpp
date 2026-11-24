// ==WindhawkMod==
// @id              alembiq-weather-desktop-overlay
// @name            Desktop Weather & Particles Overlay
// @description     Weather effects (snow, rain, fog, wind, clear) and seasonal particles (snow, rain, leaves, poplar fluff, sakura) under desktop icons with window accumulation and shake physics.
// @version         0.6.2-fix
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
    int slot = 0; // 0 = база, 1 = тело (руки + пуговица), 2 = голова (глаза + морковка)
    float x = 0.0f;
    float vx = 0.0f;
    float radius = 8.0f;
    float lift = 0.0f;
    float liftVel = 0.0f;
    float squash = 0.0f;
    float squashVel = 0.0f;
    float alpha = 0.96f;
    float ageSec = 0.0f;
    bool stacked = false;
    bool full = false;
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
    float dogPhase = 0.0f;
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
std::vector<BottomSnowball> g_bottomSnowballs;
BottomFoliagePile g_bottomPile;
bool g_hasBottomPile = false;
std::vector<SnowChunk> g_chunks;
SnowCap g_bottomSnowCap;
std::unordered_map<HWND, SnowCap> g_windowSnowCaps;
LightningFlash g_lightning;
std::unordered_map<HWND, WindowMotion> g_windows;

LRESULT CALLBACK LowLevelMouseProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode >= 0 && g_running.load() &&
        (wParam == WM_LBUTTONDOWN || wParam == WM_RBUTTONDOWN)) {
        const auto* ms = reinterpret_cast<const MSLLHOOKSTRUCT*>(lParam);
        if (ms) {
            g_clickScreenX.store(ms->pt.x);
            g_clickScreenY.store(ms->pt.y);
            g_snowmanClickRequested.store(true);
        }
    }
    return CallNextHookEx(nullptr, nCode, wParam, lParam);
}

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

    HINTERNET hSession = InternetOpenW(L"WindhawkWeatherMod/1.3", INTERNET_OPEN_TYPE_PRECONFIG, nullptr, nullptr, 0);
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

bool IsPointOccludedAbove(const std::vector<VisibleWindow>& windows, size_t targetIdx, float x,