// ==WindhawkMod==
// @id              alembiq-weather-desktop-overlay
// @name            Desktop Weather & Particles Overlay
// @description     Weather effects (snow, rain, fog, wind, clear) and seasonal particles (snow, rain, leaves, poplar fluff, sakura) under desktop icons with window accumulation and shake physics.
// @version         0.3.0
// @author          alembiq
// @github          https://github.com/duschkopf/alembiq-weather-desktop-overlay/
// @include         explorer.exe
// @compilerOptions -ld2d1 -ldwrite -lwininet -luser32 -lgdi32 -lshell32 -lole32
// ==/WindhawkMod==

// ==WindhawkModSettings==
/*
- layerAttachMode: auto
  $name: Layer attach mode
  $description: Controls Z-order placement of the overlay. Allowed values: auto, progman_direct, desktop_bottom. Default: auto.
  $options:
    - auto: Auto (below SHELLDLL_DefView icons)
    - progman_direct: Progman reference
    - desktop_bottom: Bottom of Z-order (HWND_BOTTOM)
- bottomBoundaryMode: above_taskbar
  $name: Bottom accumulation boundary
  $description: Sets the bottom reference line for fallen objects. Allowed values: above_taskbar, screen_bottom, custom_offset. Default: above_taskbar.
  $options:
    - above_taskbar: Above taskbar (Shell_TrayWnd)
    - screen_bottom: Bottom edge of screen
    - custom_offset: Custom offset from bottom (px)
- bottomOffsetPx: 0
  $name: Custom bottom offset (px)
  $description: Vertical offset in pixels above the bottom edge when bottomBoundaryMode is custom_offset. Range: -500 to 1000. Default: 0.
- multiMonitorMode: primary
  $name: Monitors
  $description: Selects primary monitor or full virtual screen across multiple monitors. Allowed values: primary, all. Default: primary.
  $options:
    - primary: Primary monitor
    - all: All monitors (virtual screen)

- primarySource: open_meteo
  $name: Primary weather source
  $description: Primary forecast provider used when any setting is set to auto. Allowed values: open_meteo, custom_api, local_file. Default: open_meteo.
  $options:
    - open_meteo: Open-Meteo API
    - custom_api: Custom JSON URL
    - local_file: Local file
- fallbackSource: off
  $name: Fallback weather source
  $description: Secondary source if primary source fails. Allowed values: off, open_meteo, local_file. Default: off.
  $options:
    - off: Off
    - open_meteo: Open-Meteo API
    - local_file: Local file
- latitude: "44.7866"
  $name: Latitude
  $description: Geographic latitude in decimal degrees for Open-Meteo. Range: -90.0 to 90.0. Default: 44.7866.
- longitude: "20.4489"
  $name: Longitude
  $description: Geographic longitude in decimal degrees for Open-Meteo. Range: -180.0 to 180.0. Default: 20.4489.
- customApiUrl: ""
  $name: Custom JSON API URL
  $description: HTTP/HTTPS endpoint returning weather JSON fields (weather_code, condition, wind_speed_10m, wind_direction_10m). Default: empty.
- localWeatherPath: ""
  $name: Local weather file path
  $description: Local file path containing JSON or weather keywords. Default: empty.
- updateIntervalMin: 30
  $name: Weather update interval (min)
  $description: Forecast polling interval in minutes. Range: 1 to 1440. Out-of-range values clamp to bounds. Default: 30.

- springStart: "01.03"
  $name: Spring start (DD.MM)
  $description: Start date of spring in DD.MM format (01.01 to 31.12). Default: 01.03.
- springEnd: "31.05"
  $name: Spring end (DD.MM)
  $description: End date of spring in DD.MM format (01.01 to 31.12). Default: 31.05.
- summerStart: "01.06"
  $name: Summer start (DD.MM)
  $description: Start date of summer in DD.MM format (01.01 to 31.12). Default: 01.06.
- summerEnd: "31.08"
  $name: Summer end (DD.MM)
  $description: End date of summer in DD.MM format (01.01 to 31.12). Default: 31.08.
- autumnStart: "01.09"
  $name: Autumn start (DD.MM)
  $description: Start date of autumn in DD.MM format (01.01 to 31.12). Default: 01.09.
- autumnEnd: "30.11"
  $name: Autumn end (DD.MM)
  $description: End date of autumn in DD.MM format (01.01 to 31.12). Default: 30.11.
- winterStart: "01.12"
  $name: Winter start (DD.MM)
  $description: Start date of winter in DD.MM format (supports year wrap, e.g. 01.12). Default: 01.12.
- winterEnd: "29.02"
  $name: Winter end (DD.MM)
  $description: End date of winter in DD.MM format (supports year wrap, e.g. 29.02). Default: 29.02.

- precipitationMode: auto
  $name: Precipitation mode
  $description: Controls weather precipitation layer. Allowed values: off, auto, rain, snow, hail. Default: auto.
  $options:
    - off: Off
    - auto: Auto (forecast)
    - rain: Rain
    - snow: Snow
    - hail: Hail
- precipFallDirection: auto
  $name: Precipitation fall direction
  $description: Direction of falling precipitation. Allowed values: auto, down, down_left, down_right. In auto mode, wind direction maps north/west to down_left and south/east to down_right (or down when calm). Default: auto.
  $options:
    - auto: Auto (forecast)
    - down: Down
    - down_left: Down-left
    - down_right: Down-right
- precipFallSpeedMps: "6.5"
  $name: Precipitation fall speed (m/s)
  $description: Vertical fall speed of precipitation in m/s (scaled to screen motion). Range: 0.1 to 50.0. Default: 6.5.
- rainIntensity: 25
  $name: Rain intensity (%)
  $description: Rain intensity percentage. Valid range: 0 to 100. Any value outside 0..100 resets to default 25.
- snowIntensity: 25
  $name: Snow intensity (%)
  $description: Snow intensity percentage. Valid range: 0 to 100. Any value outside 0..100 resets to default 25.
- hailIntensity: 25
  $name: Hail intensity (%)
  $description: Hail intensity percentage. Valid range: 0 to 100. Any value outside 0..100 resets to default 25.
- rainMaxAccumulated: 180
  $name: Rain puddles max count
  $description: Maximum accumulated rain/puddle markers on screen. Range: 0 to 2000 (0 disables accumulation). Default: 180.
- snowMaxAccumulated: 260
  $name: Snow accumulation max count
  $description: Maximum accumulated snow elements on screen. Range: 0 to 2000 (0 disables accumulation). Default: 260.
- hailMaxAccumulated: 220
  $name: Hail accumulation max count
  $description: Maximum accumulated hail stones on screen. Range: 0 to 2000 (0 disables accumulation). Default: 220.
- rainLifetimeMin: "3.0"
  $name: Rain puddles lifetime (min)
  $description: Auto-disappear time for accumulated rain elements in minutes. Range: -1 to 1440 (-1 disables auto-disappear). Default: 3.0.
- snowLifetimeMin: "15.0"
  $name: Snow accumulation lifetime (min)
  $description: Auto-disappear time for accumulated snow elements in minutes. Range: -1 to 1440 (-1 disables auto-disappear). Default: 15.0.
- hailLifetimeMin: "10.0"
  $name: Hail accumulation lifetime (min)
  $description: Auto-disappear time for accumulated hail elements in minutes. Range: -1 to 1440 (-1 disables auto-disappear). Default: 10.0.
- colorRain: ""
  $name: Rain color (#RRGGBB)
  $description: Optional custom HEX color (#RRGGBB). Empty string uses default sky-blue rain color.
- colorSnow: ""
  $name: Snow color (#RRGGBB)
  $description: Optional custom HEX color (#RRGGBB). Empty string uses default white snow color.
- colorHail: ""
  $name: Hail color (#RRGGBB)
  $description: Optional custom HEX color (#RRGGBB). Empty string uses default ice-blue hail color.

- seasonalObjectMode: auto
  $name: Seasonal falling objects mode
  $description: Controls seasonal/general falling objects. Allowed values: off, auto, autumn_leaves, extra_snow, petals. Default: auto.
  $options:
    - off: Off
    - auto: Auto (season)
    - autumn_leaves: Autumn leaves
    - extra_snow: Snow (extra)
    - petals: Petals
- seasonalFallDirection: auto
  $name: Seasonal objects fall direction
  $description: Fall direction for seasonal objects. Allowed values: auto, down, down_left, down_right. Default: auto.
  $options:
    - auto: Auto (forecast)
    - down: Down
    - down_left: Down-left
    - down_right: Down-right
- seasonalFallSpeedMps: "2.2"
  $name: Seasonal objects fall speed (m/s)
  $description: Vertical fall speed of seasonal objects in m/s. Range: 0.1 to 30.0. Default: 2.2.
- autumnLeavesIntensity: 25
  $name: Autumn leaves intensity (%)
  $description: Autumn leaves intensity percentage. Valid range: 0 to 100. Any value outside 0..100 resets to default 25.
- extraSnowIntensity: 25
  $name: Extra snow intensity (%)
  $description: Extra snow layer intensity percentage. Valid range: 0 to 100. Any value outside 0..100 resets to default 25.
- petalsIntensity: 25
  $name: Petals intensity (%)
  $description: Falling petals intensity percentage. Valid range: 0 to 100. Any value outside 0..100 resets to default 25.
- autumnLeavesMaxAccumulated: 220
  $name: Autumn leaves max count
  $description: Maximum accumulated autumn leaves on screen. Range: 0 to 2000 (0 disables accumulation). Default: 220.
- extraSnowMaxAccumulated: 240
  $name: Extra snow max count
  $description: Maximum accumulated extra snow elements on screen. Range: 0 to 2000 (0 disables accumulation). Default: 240.
- petalsMaxAccumulated: 220
  $name: Petals max count
  $description: Maximum accumulated petals on screen. Range: 0 to 2000 (0 disables accumulation). Default: 220.
- autumnLeavesLifetimeMin: "20.0"
  $name: Autumn leaves lifetime (min)
  $description: Auto-disappear time for accumulated autumn leaves in minutes. Range: -1 to 1440 (-1 disables auto-disappear). Default: 20.0.
- extraSnowLifetimeMin: "15.0"
  $name: Extra snow lifetime (min)
  $description: Auto-disappear time for accumulated extra snow in minutes. Range: -1 to 1440 (-1 disables auto-disappear). Default: 15.0.
- petalsLifetimeMin: "12.0"
  $name: Petals lifetime (min)
  $description: Auto-disappear time for accumulated petals in minutes. Range: -1 to 1440 (-1 disables auto-disappear). Default: 12.0.
- colorAutumnLeaves: ""
  $name: Autumn leaves color (#RRGGBB)
  $description: Optional custom HEX color (#RRGGBB). Empty string uses default warm amber/orange leaf color.
- colorExtraSnow: ""
  $name: Extra snow color (#RRGGBB)
  $description: Optional custom HEX color (#RRGGBB). Empty string uses default soft snow-white color.
- colorPetals: ""
  $name: Petals color (#RRGGBB)
  $description: Optional custom HEX color (#RRGGBB). Empty string uses default soft pink petal color.

- effectClear: auto
  $name: "Effect: Clear"
  $description: Controls clear sky glow effect. Allowed values: auto, on, off. Multiple effects can be active simultaneously. Default: auto.
  $options:
    - auto: Auto (forecast)
    - on: On
    - off: Off
- effectPartlyCloudy: auto
  $name: "Effect: Partly cloudy"
  $description: Controls partly cloudy soft cloud tint. Allowed values: auto, on, off. Default: auto.
  $options:
    - auto: Auto (forecast)
    - on: On
    - off: Off
- effectOvercast: auto
  $name: "Effect: Overcast"
  $description: Controls overcast gray sky veil. Allowed values: auto, on, off. Default: auto.
  $options:
    - auto: Auto (forecast)
    - on: On
    - off: Off
- effectDust: auto
  $name: "Effect: Dust"
  $description: Controls airborne dust haze/motes. Allowed values: auto, on, off. Default: auto.
  $options:
    - auto: Auto (forecast)
    - on: On
    - off: Off
- effectFog: auto
  $name: "Effect: Fog"
  $description: Controls soft fog layer. Allowed values: auto, on, off. Default: auto.
  $options:
    - auto: Auto (forecast)
    - on: On
    - off: Off
- effectSmog: auto
  $name: "Effect: Smog"
  $description: Controls dense smog tint. Allowed values: auto, on, off. Default: auto.
  $options:
    - auto: Auto (forecast)
    - on: On
    - off: Off
- effectRainbow: auto
  $name: "Effect: Rainbow"
  $description: Controls rainbow arc overlay. Allowed values: auto, on, off. Default: auto.
  $options:
    - auto: Auto (forecast)
    - on: On
    - off: Off
- effectHalo: auto
  $name: "Effect: Halo"
  $description: Controls atmospheric light halo ring. Allowed values: auto, on, off. Default: auto.
  $options:
    - auto: Auto (forecast)
    - on: On
    - off: Off
- effectThunderstorm: auto
  $name: "Effect: Thunderstorm"
  $description: Controls storm darkening and lightning flashes. Allowed values: auto, on, off. Default: auto.
  $options:
    - auto: Auto (forecast)
    - on: On
    - off: Off
- effectAurora: auto
  $name: "Effect: Aurora"
  $description: Controls aurora ribbons in upper screen area. Allowed values: auto, on, off. Default: auto.
  $options:
    - auto: Auto (forecast)
    - on: On
    - off: Off
- effectMirage: auto
  $name: "Effect: Mirage"
  $description: Controls shimmer/mirage band near lower horizon. Allowed values: auto, on, off. Default: auto.
  $options:
    - auto: Auto (forecast)
    - on: On
    - off: Off
- effectsIntensity: 25
  $name: General effects intensity (%)
  $description: Opacity/strength percentage for general atmospheric effects. Valid range: 0 to 100. Outside 0..100 resets to default 25.
- colorClear: ""
  $name: Clear effect color (#RRGGBB)
  $description: Optional custom HEX color (#RRGGBB). Empty string uses default warm sunlight tint.
- colorPartlyCloudy: ""
  $name: Partly cloudy color (#RRGGBB)
  $description: Optional custom HEX color (#RRGGBB). Empty string uses default soft cloud tint.
- colorOvercast: ""
  $name: Overcast color (#RRGGBB)
  $description: Optional custom HEX color (#RRGGBB). Empty string uses default slate-gray overcast tint.
- colorDust: ""
  $name: Dust color (#RRGGBB)
  $description: Optional custom HEX color (#RRGGBB). Empty string uses default warm sand-dust tint.
- colorFog: ""
  $name: Fog color (#RRGGBB)
  $description: Optional custom HEX color (#RRGGBB). Empty string uses default pale mist color.
- colorSmog: ""
  $name: Smog color (#RRGGBB)
  $description: Optional custom HEX color (#RRGGBB). Empty string uses default brownish-gray smog tint.
- colorRainbow: ""
  $name: Rainbow accent color (#RRGGBB)
  $description: Optional custom HEX color (#RRGGBB). Empty string uses multi-band spectrum colors.
- colorHalo: ""
  $name: Halo color (#RRGGBB)
  $description: Optional custom HEX color (#RRGGBB). Empty string uses default pale solar/lunar halo tint.
- colorThunderstorm: ""
  $name: Thunderstorm flash color (#RRGGBB)
  $description: Optional custom HEX color (#RRGGBB). Empty string uses default electric blue-white lightning color.
- colorAurora: ""
  $name: Aurora color (#RRGGBB)
  $description: Optional custom HEX color (#RRGGBB). Empty string uses default aurora green-cyan color.
- colorMirage: ""
  $name: Mirage color (#RRGGBB)
  $description: Optional custom HEX color (#RRGGBB). Empty string uses default warm shimmer tint.

- particleScale: "1.0"
  $name: Object size scale
  $description: Visual size multiplier for falling and fallen objects. Range: 0.3 to 4.0. Default: 1.0.
- windowShakeSensitivity: 55
  $name: Fallen shed sensitivity on window move (1..100)
  $description: How easily fallen objects on window tops detach when moving/shaking a window. Range: 1 to 100. Default: 55.
- windowInertiaFactor: "0.75"
  $name: Fallen shed inertia factor
  $description: Horizontal velocity transfer to detached fallen objects. Range: 0.0 to 3.0. Default: 0.75.
- cursorInteraction: true
  $name: Cursor affects fallen objects only
  $description: When enabled, moving the cursor pushes/scatters fallen objects only (falling objects are unaffected). Default: true.
- cursorRadiusPx: 95
  $name: Cursor radius (px)
  $description: Radius around cursor in pixels affecting fallen objects. Range: 10 to 500. Default: 95.
- targetFps: 60
  $name: Target FPS (30 or 60)
  $description: Frame rate cap for rendering loop. Allowed values: 30 or 60. Default: 60.
- pauseOnFullscreen: true
  $name: Pause on fullscreen apps
  $description: Pauses animation while a fullscreen application is active. Default: true.
- excludedProcesses: "obs64.exe, ApplicationFrameHost.exe"
  $name: Excluded processes (comma-separated)
  $description: Process executable names (comma-separated) excluded from window accumulation/shedding. Default: obs64.exe, ApplicationFrameHost.exe.
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

struct GeneralEffectsState {
    bool clear = false;
    bool partlyCloudy = false;
    bool overcast = false;
    bool dust = false;
    bool fog = false;
    bool smog = false;
    bool rainbow = false;
    bool halo = false;
    bool thunderstorm = false;
    bool aurora = false;
    bool mirage = false;
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

    TriStateMode effectClear = TriStateMode::Auto;
    TriStateMode effectPartlyCloudy = TriStateMode::Auto;
    TriStateMode effectOvercast = TriStateMode::Auto;
    TriStateMode effectDust = TriStateMode::Auto;
    TriStateMode effectFog = TriStateMode::Auto;
    TriStateMode effectSmog = TriStateMode::Auto;
    TriStateMode effectRainbow = TriStateMode::Auto;
    TriStateMode effectHalo = TriStateMode::Auto;
    TriStateMode effectThunderstorm = TriStateMode::Auto;
    TriStateMode effectAurora = TriStateMode::Auto;
    TriStateMode effectMirage = TriStateMode::Auto;
    int effectsIntensity = 25;

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
    bool hasCustomRainbowColor = false;
    D2D1_COLOR_F colorRainbow = D2D1::ColorF(1.0f, 0.78f, 0.35f, 0.35f);
    bool hasCustomHaloColor = false;
    D2D1_COLOR_F colorHalo = D2D1::ColorF(0.98f, 0.95f, 0.82f, 0.32f);
    bool hasCustomThunderstormColor = false;
    D2D1_COLOR_F colorThunderstorm = D2D1::ColorF(0.84f, 0.92f, 1.0f, 0.95f);
    bool hasCustomAuroraColor = false;
    D2D1_COLOR_F colorAurora = D2D1::ColorF(0.22f, 0.92f, 0.62f, 0.32f);
    bool hasCustomMirageColor = false;
    D2D1_COLOR_F colorMirage = D2D1::ColorF(0.98f, 0.86f, 0.66f, 0.25f);

    double particleScale = 1.0;
    int windowShakeSensitivity = 55;
    double windowInertiaFactor = 0.75;
    bool cursorInteraction = true;
    int cursorRadiusPx = 95;

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
int g_forecastWindDirSign = 0; // -1 left, 0 none, +1 right
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

int SanitizePercent(int rawVal) {
    if (rawVal < 0 || rawVal > 100) return 25;
    return rawVal;
}

DayMonth ParseDayMonth(const std::wstring& raw, DayMonth defVal) {
    std::wstring s = Trim(raw);
    size_t dot = s.find(L'.');
    if (dot == std::wstring::npos) dot = s.find(L'/');
    if (dot == std::wstring::npos) return defVal;
    try {
        int d = std::stoi(s.substr(0, dot));
        int m = std::stoi(s.substr(dot + 1));
        if (m < 1 || m > 12 || d < 1 || d > 31) return defVal;
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
    if (sKey <= eKey) {
        return curKey >= sKey && curKey <= eKey;
    }
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

int WindDegToSign(double deg) {
    double norm = std::fmod(deg, 360.0);
    if (norm < 0.0) norm += 360.0;
    // Север (315..360, 0..45) и Запад (225..315) -> влево (-1)
    // Восток (45..135) и Юг (135..225) -> вправо (+1)
    if (norm >= 45.0 && norm < 225.0) return 1;
    return -1;
}

bool TryParseHexColor(const std::wstring& hexRaw, float defaultAlpha, D2D1_COLOR_F& outColor) {
    std::wstring s = Trim(hexRaw);
    if (s.empty()) return false;
    if (s[0] == L'#') s.erase(0, 1);
    if (s.size() != 6) return false;
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
    next.bottomOffsetPx = std::clamp(Wh_GetIntSetting(L"bottomOffsetPx"), -500, 1000);
    next.multiMonitorMode = readStr(L"multiMonitorMode", L"primary");

    next.primarySource = readStr(L"primarySource", L"open_meteo");
    next.fallbackSource = readStr(L"fallbackSource", L"off");
    try { next.latitude = std::clamp(std::stod(readStr(L"latitude", L"44.7866")), -90.0, 90.0); } catch (...) {}
    try { next.longitude = std::clamp(std::stod(readStr(L"longitude", L"20.4489")), -180.0, 180.0); } catch (...) {}
    next.customApiUrl = readStr(L"customApiUrl", L"");
    next.localWeatherPath = readStr(L"localWeatherPath", L"");
    next.updateIntervalMin = std::clamp(Wh_GetIntSetting(L"updateIntervalMin"), 1, 1440);

    next.springStart = ParseDayMonth(readStr(L"springStart", L"01.03"), DayMonth{1, 3});
    next.springEnd = ParseDayMonth(readStr(L"springEnd", L"31.05"), DayMonth{31, 5});
    next.summerStart = ParseDayMonth(readStr(L"summerStart", L"01.06"), DayMonth{1, 6});
    next.summerEnd = ParseDayMonth(readStr(L"summerEnd", L"31.08"), DayMonth{31, 8});
    next.autumnStart = ParseDayMonth(readStr(L"autumnStart", L"01.09"), DayMonth{1, 9});
    next.autumnEnd = ParseDayMonth(readStr(L"autumnEnd", L"30.11"), DayMonth{30, 11});
    next.winterStart = ParseDayMonth(readStr(L"winterStart", L"01.12"), DayMonth{1, 12});
    next.winterEnd = ParseDayMonth(readStr(L"winterEnd", L"29.02"), DayMonth{29, 2});

    next.precipitationMode = ParsePrecipMode(readStr(L"precipitationMode", L"auto"));
    next.precipFallDirection = ParseFallDir(readStr(L"precipFallDirection", L"auto"));
    try { next.precipFallSpeedMps = std::clamp(std::stod(readStr(L"precipFallSpeedMps", L"6.5")), 0.1, 50.0); } catch (...) {}

    next.rainIntensity = SanitizePercent(Wh_GetIntSetting(L"rainIntensity"));
    next.snowIntensity = SanitizePercent(Wh_GetIntSetting(L"snowIntensity"));
    next.hailIntensity = SanitizePercent(Wh_GetIntSetting(L"hailIntensity"));

    next.rainMaxAccumulated = std::clamp(Wh_GetIntSetting(L"rainMaxAccumulated"), 0, 2000);
    next.snowMaxAccumulated = std::clamp(Wh_GetIntSetting(L"snowMaxAccumulated"), 0, 2000);
    next.hailMaxAccumulated = std::clamp(Wh_GetIntSetting(L"hailMaxAccumulated"), 0, 2000);

    auto readLifetime = [&](LPCWSTR key, double defMin) -> double {
        try {
            double v = std::stod(readStr(key, L""));
            if (v < 0.0) return -1.0;
            return std::clamp(v, 0.05, 1440.0);
        } catch (...) {
            return defMin;
        }
    };
    next.rainLifetimeMin = readLifetime(L"rainLifetimeMin", 3.0);
    next.snowLifetimeMin = readLifetime(L"snowLifetimeMin", 15.0);
    next.hailLifetimeMin = readLifetime(L"hailLifetimeMin", 10.0);

    next.seasonalObjectMode = ParseSeasonalMode(readStr(L"seasonalObjectMode", L"auto"));
    next.seasonalFallDirection = ParseFallDir(readStr(L"seasonalFallDirection", L"auto"));
    try { next.seasonalFallSpeedMps = std::clamp(std::stod(readStr(L"seasonalFallSpeedMps", L"2.2")), 0.1, 30.0); } catch (...) {}

    next.autumnLeavesIntensity = SanitizePercent(Wh_GetIntSetting(L"autumnLeavesIntensity"));
    next.extraSnowIntensity = SanitizePercent(Wh_GetIntSetting(L"extraSnowIntensity"));
    next.petalsIntensity = SanitizePercent(Wh_GetIntSetting(L"petalsIntensity"));

    next.autumnLeavesMaxAccumulated = std::clamp(Wh_GetIntSetting(L"autumnLeavesMaxAccumulated"), 0, 2000);
    next.extraSnowMaxAccumulated = std::clamp(Wh_GetIntSetting(L"extraSnowMaxAccumulated"), 0, 2000);
    next.petalsMaxAccumulated = std::clamp(Wh_GetIntSetting(L"petalsMaxAccumulated"), 0, 2000);

    next.autumnLeavesLifetimeMin = readLifetime(L"autumnLeavesLifetimeMin", 20.0);
    next.extraSnowLifetimeMin = readLifetime(L"extraSnowLifetimeMin", 15.0);
    next.petalsLifetimeMin = readLifetime(L"petalsLifetimeMin", 12.0);

    next.effectClear = ParseTriState(readStr(L"effectClear", L"auto"));
    next.effectPartlyCloudy = ParseTriState(readStr(L"effectPartlyCloudy", L"auto"));
    next.effectOvercast = ParseTriState(readStr(L"effectOvercast", L"auto"));
    next.effectDust = ParseTriState(readStr(L"effectDust", L"auto"));
    next.effectFog = ParseTriState(readStr(L"effectFog", L"auto"));
    next.effectSmog = ParseTriState(readStr(L"effectSmog", L"auto"));
    next.effectRainbow = ParseTriState(readStr(L"effectRainbow", L"auto"));
    next.effectHalo = ParseTriState(readStr(L"effectHalo", L"auto"));
    next.effectThunderstorm = ParseTriState(readStr(L"effectThunderstorm", L"auto"));
    next.effectAurora = ParseTriState(readStr(L"effectAurora", L"auto"));
    next.effectMirage = ParseTriState(readStr(L"effectMirage", L"auto"));
    next.effectsIntensity = SanitizePercent(Wh_GetIntSetting(L"effectsIntensity"));

    TryParseHexColor(readStr(L"colorRain", L""), 0.78f, next.colorRain);
    TryParseHexColor(readStr(L"colorSnow", L""), 0.92f, next.colorSnow);
    TryParseHexColor(readStr(L"colorHail", L""), 0.95f, next.colorHail);
    TryParseHexColor(readStr(L"colorAutumnLeaves", L""), 0.92f, next.colorAutumnLeaves);
    TryParseHexColor(readStr(L"colorExtraSnow", L""), 0.88f, next.colorExtraSnow);
    TryParseHexColor(readStr(L"colorPetals", L""), 0.90f, next.colorPetals);

    next.hasCustomClearColor = TryParseHexColor(readStr(L"colorClear", L""), 0.25f, next.colorClear);
    next.hasCustomPartlyCloudyColor = TryParseHexColor(readStr(L"colorPartlyCloudy", L""), 0.22f, next.colorPartlyCloudy);
    next.hasCustomOvercastColor = TryParseHexColor(readStr(L"colorOvercast", L""), 0.35f, next.colorOvercast);
    next.hasCustomDustColor = TryParseHexColor(readStr(L"colorDust", L""), 0.28f, next.colorDust);
    next.hasCustomFogColor = TryParseHexColor(readStr(L"colorFog", L""), 0.35f, next.colorFog);
    next.hasCustomSmogColor = TryParseHexColor(readStr(L"colorSmog", L""), 0.36f, next.colorSmog);
    next.hasCustomRainbowColor = TryParseHexColor(readStr(L"colorRainbow", L""), 0.35f, next.colorRainbow);
    next.hasCustomHaloColor = TryParseHexColor(readStr(L"colorHalo", L""), 0.32f, next.colorHalo);
    next.hasCustomThunderstormColor = TryParseHexColor(readStr(L"colorThunderstorm", L""), 0.95f, next.colorThunderstorm);
    next.hasCustomAuroraColor = TryParseHexColor(readStr(L"colorAurora", L""), 0.32f, next.colorAurora);
    next.hasCustomMirageColor = TryParseHexColor(readStr(L"colorMirage", L""), 0.25f, next.colorMirage);

    try { next.particleScale = std::clamp(std::stod(readStr(L"particleScale", L"1.0")), 0.3, 4.0); } catch (...) {}
    next.windowShakeSensitivity = std::clamp(Wh_GetIntSetting(L"windowShakeSensitivity"), 1, 100);
    try { next.windowInertiaFactor = std::clamp(std::stod(readStr(L"windowInertiaFactor", L"0.75")), 0.0, 3.0); } catch (...) {}
    next.cursorInteraction = Wh_GetIntSetting(L"cursorInteraction") != 0;
    next.cursorRadiusPx = std::clamp(Wh_GetIntSetting(L"cursorRadiusPx"), 10, 500);

    next.targetFps = (Wh_GetIntSetting(L"targetFps") == 30) ? 30 : 60;
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

    HINTERNET hSession = InternetOpenW(L"WindhawkWeatherMod/0.4", INTERNET_OPEN_TYPE_PRECONFIG, nullptr, nullptr, 0);
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
            return true;
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
        if (cond.find("rainbow") != std::string::npos) fx.rainbow = true;
        if (cond.find("halo") != std::string::npos) fx.halo = true;
        if (cond.find("thunder") != std::string::npos || cond.find("storm") != std::string::npos) fx.thunderstorm = true;
        if (cond.find("aurora") != std::string::npos) fx.aurora = true;
        if (cond.find("mirage") != std::string::npos) fx.mirage = true;
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
                      double scale, float vx, float vy, bool randomY) {
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
    (void)vx;
    (void)vy;
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

void DrawTintRect(ID2D1DCRenderTarget* rt, D2D1_COLOR_F col, float factor) {
    col.a = std::clamp(col.a * factor, 0.0f, 0.85f);
    if (col.a <= 0.004f) return;
    ID2D1SolidColorBrush* b = nullptr;
    rt->CreateSolidColorBrush(col, &b);
    if (b) {
        rt->FillRectangle(D2D1::RectF(0.0f, 0.0f, static_cast<float>(g_canvasWidth), static_cast<float>(g_canvasHeight)), b);
        b->Release();
    }
}

void RenderFrame(const Settings& cfg, const GeneralEffectsState& fx, int bottomLimitY, float precipVx) {
    if (!g_overlayHwnd || !IsWindow(g_overlayHwnd)) return;
    if (!EnsureLayeredSurface(g_canvasWidth, g_canvasHeight)) return;

    RECT bindRect = {0, 0, g_canvasWidth, g_canvasHeight};
    g_dcRenderTarget->BindDC(g_memDC, &bindRect);

    g_dcRenderTarget->BeginDraw();
    g_dcRenderTarget->Clear(D2D1::ColorF(0.0f, 0.0f, 0.0f, 0.0f));

    float k = static_cast<float>(cfg.effectsIntensity) / 25.0f;

    if (fx.clear) {
        DrawTintRect(g_dcRenderTarget, cfg.hasCustomClearColor ? cfg.colorClear : D2D1::ColorF(1.0f, 0.92f, 0.65f, 0.14f), k);
    }
    if (fx.partlyCloudy) {
        DrawTintRect(g_dcRenderTarget, cfg.hasCustomPartlyCloudyColor ? cfg.colorPartlyCloudy : D2D1::ColorF(0.88f, 0.91f, 0.95f, 0.16f), k);
    }
    if (fx.overcast) {
        DrawTintRect(g_dcRenderTarget, cfg.hasCustomOvercastColor ? cfg.colorOvercast : D2D1::ColorF(0.52f, 0.56f, 0.62f, 0.26f), k);
    }
    if (fx.dust) {
        DrawTintRect(g_dcRenderTarget, cfg.hasCustomDustColor ? cfg.colorDust : D2D1::ColorF(0.84f, 0.68f, 0.45f, 0.20f), k);
    }
    if (fx.fog) {
        DrawTintRect(g_dcRenderTarget, cfg.hasCustomFogColor ? cfg.colorFog : D2D1::ColorF(0.82f, 0.86f, 0.90f, 0.28f), k);
    }
    if (fx.smog) {
        DrawTintRect(g_dcRenderTarget, cfg.hasCustomSmogColor ? cfg.colorSmog : D2D1::ColorF(0.54f, 0.48f, 0.40f, 0.30f), k);
    }
    if (fx.mirage) {
        D2D1_COLOR_F mc = cfg.hasCustomMirageColor ? cfg.colorMirage : D2D1::ColorF(0.98f, 0.86f, 0.66f, 0.22f);
        mc.a = std::clamp(mc.a * k, 0.0f, 0.7f);
        ID2D1SolidColorBrush* mb = nullptr;
        g_dcRenderTarget->CreateSolidColorBrush(mc, &mb);
        if (mb) {
            float topBand = (bottomLimitY - g_canvasTop) * 0.78f;
            g_dcRenderTarget->FillRectangle(
                D2D1::RectF(0.0f, topBand, static_cast<float>(g_canvasWidth), static_cast<float>(bottomLimitY - g_canvasTop)),
                mb);
            mb->Release();
        }
    }
    if (fx.aurora) {
        D2D1_COLOR_F ac = cfg.hasCustomAuroraColor ? cfg.colorAurora : D2D1::ColorF(0.22f, 0.92f, 0.62f, 0.24f);
        ac.a = std::clamp(ac.a * k, 0.0f, 0.75f);
        ID2D1SolidColorBrush* ab = nullptr;
        g_dcRenderTarget->CreateSolidColorBrush(ac, &ab);
        if (ab) {
            g_dcRenderTarget->FillRectangle(
                D2D1::RectF(0.0f, 0.0f, static_cast<float>(g_canvasWidth), g_canvasHeight * 0.24f),
                ab);
            ab->Release();
        }
    }
    if (fx.halo) {
        D2D1_COLOR_F hc = cfg.hasCustomHaloColor ? cfg.colorHalo : D2D1::ColorF(0.98f, 0.95f, 0.82f, 0.28f);
        hc.a = std::clamp(hc.a * k, 0.0f, 0.8f);
        ID2D1SolidColorBrush* hb = nullptr;
        g_dcRenderTarget->CreateSolidColorBrush(hc, &hb);
        if (hb) {
            g_dcRenderTarget->DrawEllipse(
                D2D1::Ellipse(D2D1::Point2F(g_canvasWidth * 0.5f, g_canvasHeight * 0.25f), 190.0f, 190.0f),
                hb,
                8.0f);
            hb->Release();
        }
    }
    if (fx.rainbow) {
        const D2D1_COLOR_F bands[6] = {
            D2D1::ColorF(1.0f, 0.24f, 0.24f, 0.22f * k),
            D2D1::ColorF(1.0f, 0.60f, 0.16f, 0.22f * k),
            D2D1::ColorF(1.0f, 0.92f, 0.22f, 0.22f * k),
            D2D1::ColorF(0.25f, 0.85f, 0.36f, 0.22f * k),
            D2D1::ColorF(0.22f, 0.60f, 1.0f, 0.22f * k),
            D2D1::ColorF(0.62f, 0.30f, 0.95f, 0.22f * k)
        };
        float cx = g_canvasWidth * 0.5f;
        float cy = g_canvasHeight * 0.95f;
        float baseR = std::min(g_canvasWidth, g_canvasHeight) * 0.68f;
        for (int b = 0; b < 6; ++b) {
            D2D1_COLOR_F col = cfg.hasCustomRainbowColor ? cfg.colorRainbow : bands[b];
            if (cfg.hasCustomRainbowColor) col.a = std::clamp(col.a * k * (1.0f - b * 0.1f), 0.0f, 0.75f);
            ID2D1SolidColorBrush* rb = nullptr;
            g_dcRenderTarget->CreateSolidColorBrush(col, &rb);
            if (rb) {
                float r = baseR - b * 14.0f;
                g_dcRenderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(cx, cy), r, r * 0.72f), rb, 13.0f);
                rb->Release();
            }
        }
    }
    if (fx.thunderstorm && g_lightning.timer > 0.0f) {
        D2D1_COLOR_F tc = cfg.hasCustomThunderstormColor ? cfg.colorThunderstorm : D2D1::ColorF(0.84f, 0.92f, 1.0f, 0.95f);
        tc.a = std::clamp(g_lightning.timer * 4.0f * std::max(0.2f, k), 0.0f, 1.0f);
        ID2D1SolidColorBrush* tb = nullptr;
        g_dcRenderTarget->CreateSolidColorBrush(tc, &tb);
        if (tb) {
            float curX = g_lightning.xStart;
            float curY = 0.0f;
            int segs = 12;
            float stepY = (bottomLimitY - g_canvasTop) * 0.75f / segs;
            for (int i = 0; i < segs; ++i) {
                float t = static_cast<float>(i + 1) / segs;
                float nextX = g_lightning.xStart + (g_lightning.xEnd - g_lightning.xStart) * t + ((i % 2 == 0) ? 18.0f : -18.0f);
                float nextY = curY + stepY;
                g_dcRenderTarget->DrawLine(D2D1::Point2F(curX, curY), D2D1::Point2F(nextX, nextY), tb, 3.0f);
                curX = nextX;
                curY = nextY;
            }
            tb->Release();
        }
    }

    ID2D1SolidColorBrush* brush = nullptr;
    g_dcRenderTarget->CreateSolidColorBrush(D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.0f), &brush);
    if (brush) {
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
            DrawItemShape(g_dcRenderTarget, brush, fo.kind, drawX, drawY, fo.size, fo.angle, fo.vx, fo.alpha);
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

    // FallDirMode::Auto
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
    auto lastTime = std::chrono::steady_clock::now();
    int zOrderTick = 0;

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
        lastTime = now;
        dt = std::clamp(dt, 0.001f, 0.05f);

        // Определяем осадки
        bool activePrecip = false;
        ObjectKind precipKind = ObjectKind::Rain;
        if (cfg.precipitationMode == PrecipMode::Rain) { activePrecip = true; precipKind = ObjectKind::Rain; }
        else if (cfg.precipitationMode == PrecipMode::Snow) { activePrecip = true; precipKind = ObjectKind::Snow; }
        else if (cfg.precipitationMode == PrecipMode::Hail) { activePrecip = true; precipKind = ObjectKind::Hail; }
        else if (cfg.precipitationMode == PrecipMode::Auto && hasForecastP) { activePrecip = true; precipKind = forecastP; }

        // Определяем сезонные/общие падающие объекты
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

        // Определяем общие эффекты (каждый независимо: auto / on / off)
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
        activeFx.rainbow = resolveEffect(cfg.effectRainbow, forecastFx.rainbow);
        activeFx.halo = resolveEffect(cfg.effectHalo, forecastFx.halo);
        activeFx.thunderstorm = resolveEffect(cfg.effectThunderstorm, forecastFx.thunderstorm);
        activeFx.aurora = resolveEffect(cfg.effectAurora, forecastFx.aurora);
        activeFx.mirage = resolveEffect(cfg.effectMirage, forecastFx.mirage);

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
            SpawnFallingItem(it, rng, precipKind, false, cfg.particleScale, precipVx, precipVy, true);
            nextFalling.push_back(it);
            ++curP;
        }
        while (curS < targetS) {
            FallingItem it;
            SpawnFallingItem(it, rng, seasonalKind, true, cfg.particleScale, seasonalVx, seasonalVy, true);
            nextFalling.push_back(it);
            ++curS;
        }
        g_falling.swap(nextFalling);

        // Отслеживание окон и срыв ОПАВШИХ объектов при перемещении/встряске окна
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
                        if (fo.onWindow && fo.hostWindow == h && !fo.fallingOff) {
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

        // Подсчет текущего накопления по каждому типу
        auto countAccumulated = [&](ObjectKind k, bool isS) -> int {
            int c = 0;
            for (const auto& fo : g_fallen) {
                if (fo.kind == k && fo.isSeasonalLayer == isS) ++c;
            }
            return c;
        };

        // Движение падающих объектов (курсор и перемещение окон на них не влияют)
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

                if (!landed && p.y >= bottomRelY - p.size * 0.35f) {
                    FallenItem fo;
                    fo.kind = p.kind;
                    fo.isSeasonalLayer = p.isSeasonalLayer;
                    fo.onWindow = false;
                    fo.hostWindow = nullptr;
                    fo.relX = p.x;
                    fo.relY = -p.size * 0.35f;
                    fo.size = p.size;
                    fo.angle = p.angle;
                    fo.alpha = p.alpha;
                    g_fallen.push_back(fo);
                    landed = true;
                }
            }

            if (landed || p.y > g_canvasHeight + 30.0f || p.x < -120.0f || p.x > g_canvasWidth + 120.0f) {
                SpawnFallingItem(p, rng, p.kind, p.isSeasonalLayer, cfg.particleScale, vx, vy, false);
            }
        }

        // Взаимодействие с курсором и время жизни — только для опавших объектов
        POINT cursorPt = {};
        GetCursorPos(&cursorPt);
        float cX = static_cast<float>(cursorPt.x - g_canvasLeft);
        float cY = static_cast<float>(cursorPt.y - g_canvasTop);
        float cRad = static_cast<float>(cfg.cursorRadiusPx);

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

            if (cfg.cursorInteraction) {
                float dx = absX - cX;
                float dy = absY - cY;
                float dist = std::hypot(dx, dy);
                if (dist > 0.1f && dist < cRad) {
                    float push = (1.0f - dist / cRad) * 260.0f * dt;
                    float nx = dx / dist;
                    float ny = dy / dist;
                    if (fo.onWindow) {
                        auto it = g_windows.find(fo.hostWindow);
                        if (it != g_windows.end()) {
                            int w = it->second.rect.right - it->second.rect.left;
                            fo.relX = std::clamp(fo.relX + nx * push, 2.0f, static_cast<float>(std::max(3, w - 2)));
                            if (absX + nx * push < it->second.rect.left - g_canvasLeft ||
                                absX + nx * push > it->second.rect.right - g_canvasLeft) {
                                fo.onWindow = false;
                                fo.fallingOff = true;
                                fo.relX = absX + nx * push;
                                fo.relY = absY + ny * push;
                                fo.vx = nx * 90.0f;
                                fo.vy = 80.0f;
                            }
                        }
                    } else if (!fo.fallingOff) {
                        fo.relX = std::clamp(fo.relX + nx * push, 0.0f, static_cast<float>(g_canvasWidth));
                    } else {
                        fo.vx += nx * push * 4.0f;
                        fo.vy += ny * push * 4.0f;
                    }
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

        RenderFrame(cfg, activeFx, bottomLimitY, precipVx);

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