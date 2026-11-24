// ==WindhawkMod==
// @id              alembiq-weather-desktop-overlay
// @name            Desktop Weather & Particles Overlay
// @description     Weather effects (snow, rain, fog, wind, clear) and seasonal particles (snow, rain, leaves, poplar fluff, sakura) under desktop icons with window accumulation and shake physics.
// @version         0.2.2
// @author          alembiq
// @github          https://github.com/duschkopf/alembiq-weather-desktop-overlay/
// @include         explorer.exe
// @compilerOptions -ld2d1 -ldwrite -lwininet -luser32 -lgdi32 -lshell32 -lole32
// ==/WindhawkMod==


// ==WindhawkModSettings==
/*
- layerAttachMode: auto
  $name: Layer attach mode
  $options:
    - auto: Auto (below SHELLDLL_DefView icons)
    - progman_direct: Progman reference
    - desktop_bottom: Bottom of Z-order (HWND_BOTTOM)
- bottomBoundaryMode: above_taskbar
  $name: Bottom accumulation boundary
  $options:
    - above_taskbar: Above taskbar (Shell_TrayWnd)
    - screen_bottom: Bottom edge of screen
    - custom_offset: Custom offset from bottom (px)
- bottomOffsetPx: 0
  $name: Custom bottom offset (px)
- multiMonitorMode: primary
  $name: Monitors
  $options:
    - primary: Primary monitor
    - all: All monitors (virtual screen)

- controlMode: manual
  $name: Control mode (manual / auto)
  $options:
    - manual: Manual (stackable)
    - auto: Automatic from forecast
- primarySource: open_meteo
  $name: Primary weather source
  $options:
    - open_meteo: Open-Meteo API
    - custom_api: Custom JSON URL
    - local_file: Local file
- fallbackSource: manual
  $name: Fallback weather source
  $options:
    - manual: Manual
    - open_meteo: Open-Meteo API
    - local_file: Local file
- latitude: "44.7866"
  $name: Latitude
- longitude: "20.4489"
  $name: Longitude
- customApiUrl: ""
  $name: Custom JSON API URL
- localWeatherPath: ""
  $name: Local weather file path
- updateIntervalMin: 30
  $name: Weather update interval (min)

- enableGroupA: true
  $name: "[A] Weather precipitation enabled"
- manualWeatherPrecip: snow
  $name: "[A] Manual weather precip"
  $options:
    - none: None
    - rain: Rain
    - heavy_rain: Heavy rain
    - snow: Snow
    - sleet: Sleet / wet snow
    - hail: Hail / ice pellets
- precipDensity: 45
  $name: "[A] Precipitation density (per 1000px)"
- particleScale: "1.0"
  $name: "[A/B] Particle scale (0.4 - 3.0)"
- colorRain: ""
  $name: "[A] Rain custom HEX (#RRGGBB, empty = default)"
- colorSnow: ""
  $name: "[A] Snow custom HEX (#RRGGBB, empty = default)"
- colorHail: ""
  $name: "[A] Hail custom HEX (#RRGGBB, empty = default)"

- groupBMode: manual
  $name: "[B] Seasonal layer mode"
  $options:
    - off: Off
    - manual: Manual
    - auto_season: Auto by season
- manualSeasonType: sakura
  $name: "[B] Manual seasonal type"
  $options:
    - sakura: Sakura petals
    - autumn_leaves: Autumn leaves
    - extra_snow: Extra snow layer
- seasonDensity: 25
  $name: "[B] Seasonal density (per 1000px)"
- seasonWindDirection: "left"
  $name: "[B] Seasonal wind direction (left / right / none)"
- seasonWindStrength: 20
  $name: "[B] Seasonal wind strength (0..100)"
- colorSakura: ""
  $name: "[B] Sakura custom HEX (#RRGGBB, empty = default)"
- colorLeaves: ""
  $name: "[B] Autumn leaves custom HEX (#RRGGBB, empty = default)"
- colorExtraSnow: ""
  $name: "[B] Extra snow custom HEX (#RRGGBB, empty = default)"

- manualFog: false
  $name: "[C] Manual: Fog"
- manualRainbow: false
  $name: "[C] Manual: Rainbow"
- manualLightning: false
  $name: "[C] Manual: Lightning"
- manualWindSwirls: false
  $name: "[C] Manual: Wind swirls"
- atmosphereOpacity: 40
  $name: "[C] Effect intensity / opacity (0..100%)"
- swirlDensity: 18
  $name: "[C] Wind swirls count (per 1000px)"
- lightningFrequency: 25
  $name: "[C] Lightning frequency (1..100)"
- colorFog: ""
  $name: "[C] Fog custom HEX (#RRGGBB, empty = default)"
- colorRainbow: ""
  $name: "[C] Rainbow accent HEX (#RRGGBB, empty = default)"
- colorLightning: ""
  $name: "[C] Lightning custom HEX (#RRGGBB, empty = default)"
- colorSwirl: ""
  $name: "[C] Wind swirl custom HEX (#RRGGBB, empty = default)"

- manualWindDirection: "left"
  $name: "Manual wind direction (left / right / none)"
- manualWindSpeed: 25
  $name: "Manual wind speed (0..100)"
- enableBottomAccumulation: true
  $name: "Accumulate fallen objects at bottom"
- enableWindowAccumulation: true
  $name: "Accumulate fallen objects on window tops"
- maxFallenItems: 450
  $name: "Max fallen objects on screen"
- windowShakeSensitivity: 55
  $name: "Fallen shed sensitivity on window move (1..100)"
- windowInertiaFactor: "0.75"
  $name: "Fallen shed inertia factor (0.0..3.0)"
- cursorInteraction: true
  $name: "Cursor affects fallen objects only"
- cursorRadiusPx: 95
  $name: "Cursor influence radius on fallen objects (px)"
- decaySpeed: "0.8"
  $name: "Fallen objects fade/melt speed (items/sec)"
- targetFps: 60
  $name: "Target FPS (30 or 60)"
- pauseOnFullscreen: true
  $name: "Pause on fullscreen apps"
- excludedProcesses: "obs64.exe, ApplicationFrameHost.exe"
  $name: "Excluded processes (comma-separated)"
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

enum class PrecipKind {
    None,
    Rain,
    HeavyRain,
    Snow,
    Sleet,
    Hail,
    Sakura,
    AutumnLeaves,
    ExtraSnow
};

enum class WindDir {
    None,
    Left,
    Right
};

struct EffectFlags {
    bool fog = false;
    bool rainbow = false;
    bool lightning = false;
    bool windSwirls = false;
};

struct Settings {
    std::wstring layerAttachMode = L"auto";
    std::wstring bottomBoundaryMode = L"above_taskbar";
    int bottomOffsetPx = 0;
    std::wstring multiMonitorMode = L"primary";

    std::wstring controlMode = L"manual";
    std::wstring primarySource = L"open_meteo";
    std::wstring fallbackSource = L"manual";
    double latitude = 44.7866;
    double longitude = 20.4489;
    std::wstring customApiUrl;
    std::wstring localWeatherPath;
    int updateIntervalMin = 30;

    bool enableGroupA = true;
    PrecipKind manualWeatherPrecip = PrecipKind::Snow;
    int precipDensity = 45;
    double particleScale = 1.0;

    std::wstring groupBMode = L"manual";
    PrecipKind manualSeasonType = PrecipKind::Sakura;
    int seasonDensity = 25;
    WindDir seasonWindDirection = WindDir::Left;
    int seasonWindStrength = 20;

    bool manualFog = false;
    bool manualRainbow = false;
    bool manualLightning = false;
    bool manualWindSwirls = false;
    int atmosphereOpacity = 40;
    int swirlDensity = 18;
    int lightningFrequency = 25;

    D2D1_COLOR_F colorRain = D2D1::ColorF(0.42f, 0.72f, 1.0f, 0.75f);
    D2D1_COLOR_F colorSnow = D2D1::ColorF(0.96f, 0.98f, 1.0f, 0.92f);
    D2D1_COLOR_F colorHail = D2D1::ColorF(0.76f, 0.90f, 1.0f, 0.95f);
    D2D1_COLOR_F colorSakura = D2D1::ColorF(1.0f, 0.74f, 0.84f, 0.90f);
    D2D1_COLOR_F colorLeaves = D2D1::ColorF(0.88f, 0.44f, 0.12f, 0.92f);
    D2D1_COLOR_F colorExtraSnow = D2D1::ColorF(0.92f, 0.96f, 1.0f, 0.88f);
    D2D1_COLOR_F colorFog = D2D1::ColorF(0.82f, 0.86f, 0.90f, 0.35f);
    D2D1_COLOR_F colorRainbow = D2D1::ColorF(1.0f, 0.85f, 0.45f, 0.35f);
    D2D1_COLOR_F colorLightning = D2D1::ColorF(0.86f, 0.93f, 1.0f, 0.95f);
    D2D1_COLOR_F colorSwirl = D2D1::ColorF(0.85f, 0.92f, 0.98f, 0.45f);

    WindDir manualWindDirection = WindDir::Left;
    int manualWindSpeed = 25;

    bool enableBottomAccumulation = true;
    bool enableWindowAccumulation = true;
    int maxFallenItems = 450;
    int windowShakeSensitivity = 55;
    double windowInertiaFactor = 0.75;
    bool cursorInteraction = true;
    int cursorRadiusPx = 95;
    double decaySpeed = 0.8;

    int targetFps = 60;
    bool pauseOnFullscreen = true;
    std::wstring excludedProcesses = L"obs64.exe, ApplicationFrameHost.exe";
};

struct FallingParticle {
    PrecipKind kind = PrecipKind::Snow;
    bool fromSeasonGroup = false;
    float x = 0.0f;
    float y = 0.0f;
    float vx = 0.0f;
    float vy = 0.0f;
    float size = 6.0f;
    float angle = 0.0f;
    float spin = 0.0f;
    float swayPhase = 0.0f;
    float alpha = 0.9f;
};

struct FallenObject {
    PrecipKind kind = PrecipKind::Snow;
    bool onWindow = false;
    HWND hostWindow = nullptr;
    float relX = 0.0f;      // X относительно hostWindow.left или экрана
    float relY = 0.0f;      // Y относительно hostWindow.top или bottomLimitY
    float vx = 0.0f;
    float vy = 0.0f;
    float size = 6.0f;
    float angle = 0.0f;
    float alpha = 0.92f;
    bool fallingOff = false;
};

struct WindSwirl {
    float x = 0.0f;
    float y = 0.0f;
    float radius = 26.0f;
    float speed = 90.0f;
    float phase = 0.0f;
};

struct LightningBolt {
    float activeTimer = 0.0f;
    float xStart = 0.0f;
    float xEnd = 0.0f;
};

struct WindowMotion {
    RECT rect = {};
    float prevCenterX = 0.0f;
    float prevCenterY = 0.0f;
    float vx = 0.0f;
    float vy = 0.0f;
    bool hasPrev = false;
};

std::mutex g_mutex;
Settings g_settings;

PrecipKind g_autoPrecip = PrecipKind::None;
WindDir g_autoWindDir = WindDir::None;
double g_autoWindSpeedKmh = 0.0;
EffectFlags g_autoEffects;

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

std::vector<FallingParticle> g_falling;
std::vector<FallenObject> g_fallen;
std::vector<WindSwirl> g_swirls;
LightningBolt g_lightning;
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

WindDir ParseWindDir(const std::wstring& s) {
    std::wstring v = ToLower(Trim(s));
    if (v == L"left" || v == L"west" || v == L"north" || v == L"nw" || v == L"sw" || v == L"n" || v == L"w") {
        return WindDir::Left;
    }
    if (v == L"right" || v == L"east" || v == L"south" || v == L"ne" || v == L"se" || v == L"s" || v == L"e") {
        return WindDir::Right;
    }
    return WindDir::None;
}

WindDir WindDirectionDegToDir(double deg) {
    double norm = std::fmod(deg, 360.0);
    if (norm < 0.0) norm += 360.0;
    // Север (0..45, 315..360) и Запад (225..315) -> влево
    // Юг (135..225) и Восток (45..135) -> вправо
    if (norm >= 45.0 && norm < 225.0) {
        return WindDir::Right;
    }
    return WindDir::Left;
}

PrecipKind ParsePrecipKind(const std::wstring& s) {
    std::wstring v = ToLower(Trim(s));
    if (v == L"rain") return PrecipKind::Rain;
    if (v == L"heavy_rain") return PrecipKind::HeavyRain;
    if (v == L"snow") return PrecipKind::Snow;
    if (v == L"sleet") return PrecipKind::Sleet;
    if (v == L"hail") return PrecipKind::Hail;
    if (v == L"sakura") return PrecipKind::Sakura;
    if (v == L"autumn_leaves" || v == L"leaves") return PrecipKind::AutumnLeaves;
    if (v == L"extra_snow") return PrecipKind::ExtraSnow;
    return PrecipKind::None;
}

PrecipKind DetectCurrentSeasonPrecip() {
    std::time_t now = std::time(nullptr);
    std::tm tmLocal = {};
    localtime_s(&tmLocal, &now);
    int m = tmLocal.tm_mon + 1;
    if (m >= 3 && m <= 5) return PrecipKind::Sakura;
    if (m >= 9 && m <= 11) return PrecipKind::AutumnLeaves;
    if (m == 12 || m <= 2) return PrecipKind::ExtraSnow;
    return PrecipKind::None;
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
    next.bottomOffsetPx = Wh_GetIntSetting(L"bottomOffsetPx");
    next.multiMonitorMode = readStr(L"multiMonitorMode", L"primary");

    next.controlMode = readStr(L"controlMode", L"manual");
    next.primarySource = readStr(L"primarySource", L"open_meteo");
    next.fallbackSource = readStr(L"fallbackSource", L"manual");
    try { next.latitude = std::stod(readStr(L"latitude", L"44.7866")); } catch (...) {}
    try { next.longitude = std::stod(readStr(L"longitude", L"20.4489")); } catch (...) {}
    next.customApiUrl = readStr(L"customApiUrl", L"");
    next.localWeatherPath = readStr(L"localWeatherPath", L"");
    next.updateIntervalMin = std::max(1, Wh_GetIntSetting(L"updateIntervalMin"));

    next.enableGroupA = Wh_GetIntSetting(L"enableGroupA") != 0;
    next.manualWeatherPrecip = ParsePrecipKind(readStr(L"manualWeatherPrecip", L"snow"));
    next.precipDensity = std::clamp(Wh_GetIntSetting(L"precipDensity"), 0, 250);
    try { next.particleScale = std::clamp(std::stod(readStr(L"particleScale", L"1.0")), 0.4, 3.0); } catch (...) {}

    next.groupBMode = readStr(L"groupBMode", L"manual");
    next.manualSeasonType = ParsePrecipKind(readStr(L"manualSeasonType", L"sakura"));
    next.seasonDensity = std::clamp(Wh_GetIntSetting(L"seasonDensity"), 0, 200);
    next.seasonWindDirection = ParseWindDir(readStr(L"seasonWindDirection", L"left"));
    next.seasonWindStrength = std::clamp(Wh_GetIntSetting(L"seasonWindStrength"), 0, 100);

    next.manualFog = Wh_GetIntSetting(L"manualFog") != 0;
    next.manualRainbow = Wh_GetIntSetting(L"manualRainbow") != 0;
    next.manualLightning = Wh_GetIntSetting(L"manualLightning") != 0;
    next.manualWindSwirls = Wh_GetIntSetting(L"manualWindSwirls") != 0;
    next.atmosphereOpacity = std::clamp(Wh_GetIntSetting(L"atmosphereOpacity"), 0, 100);
    next.swirlDensity = std::clamp(Wh_GetIntSetting(L"swirlDensity"), 0, 100);
    next.lightningFrequency = std::clamp(Wh_GetIntSetting(L"lightningFrequency"), 1, 100);

    TryParseHexColor(readStr(L"colorRain", L""), 0.75f, next.colorRain);
    TryParseHexColor(readStr(L"colorSnow", L""), 0.92f, next.colorSnow);
    TryParseHexColor(readStr(L"colorHail", L""), 0.95f, next.colorHail);
    TryParseHexColor(readStr(L"colorSakura", L""), 0.90f, next.colorSakura);
    TryParseHexColor(readStr(L"colorLeaves", L""), 0.92f, next.colorLeaves);
    TryParseHexColor(readStr(L"colorExtraSnow", L""), 0.88f, next.colorExtraSnow);
    TryParseHexColor(readStr(L"colorFog", L""), 0.35f, next.colorFog);
    TryParseHexColor(readStr(L"colorRainbow", L""), 0.35f, next.colorRainbow);
    TryParseHexColor(readStr(L"colorLightning", L""), 0.95f, next.colorLightning);
    TryParseHexColor(readStr(L"colorSwirl", L""), 0.45f, next.colorSwirl);

    next.manualWindDirection = ParseWindDir(readStr(L"manualWindDirection", L"left"));
    next.manualWindSpeed = std::clamp(Wh_GetIntSetting(L"manualWindSpeed"), 0, 100);

    next.enableBottomAccumulation = Wh_GetIntSetting(L"enableBottomAccumulation") != 0;
    next.enableWindowAccumulation = Wh_GetIntSetting(L"enableWindowAccumulation") != 0;
    next.maxFallenItems = std::clamp(Wh_GetIntSetting(L"maxFallenItems"), 20, 2000);
    next.windowShakeSensitivity = std::clamp(Wh_GetIntSetting(L"windowShakeSensitivity"), 1, 100);
    try { next.windowInertiaFactor = std::clamp(std::stod(readStr(L"windowInertiaFactor", L"0.75")), 0.0, 3.0); } catch (...) {}
    next.cursorInteraction = Wh_GetIntSetting(L"cursorInteraction") != 0;
    next.cursorRadiusPx = std::clamp(Wh_GetIntSetting(L"cursorRadiusPx"), 15, 450);
    try { next.decaySpeed = std::max(0.0, std::stod(readStr(L"decaySpeed", L"0.8"))); } catch (...) {}

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

    HINTERNET hSession = InternetOpenW(L"WindhawkWeatherMod/0.3", INTERNET_OPEN_TYPE_PRECONFIG, nullptr, nullptr, 0);
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

void ApplyWmoCode(int code, PrecipKind& outPrecip, EffectFlags& outFx) {
    outPrecip = PrecipKind::None;
    outFx = EffectFlags{};

    if (code == 45 || code == 48) {
        outFx.fog = true;
    } else if (code == 71 || code == 85) {
        outPrecip = PrecipKind::Snow;
    } else if (code == 73 || code == 75 || code == 86) {
        outPrecip = PrecipKind::Snow;
    } else if (code == 77) {
        outPrecip = PrecipKind::Sleet;
    } else if (code == 96 || code == 99) {
        outPrecip = PrecipKind::Hail;
        outFx.lightning = true;
    } else if (code == 95) {
        outPrecip = PrecipKind::HeavyRain;
        outFx.lightning = true;
    } else if (code == 65 || code == 82) {
        outPrecip = PrecipKind::HeavyRain;
    } else if ((code >= 51 && code <= 67) || (code >= 80 && code <= 81)) {
        outPrecip = PrecipKind::Rain;
    }
}

bool TryParseWeatherPayload(const std::string& json, PrecipKind& outPrecip, EffectFlags& outFx,
                            double& outWindSpeed, WindDir& outWindDir) {
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

    double speed = 0.0;
    if (extractNumber("wind_speed_10m", speed) || extractNumber("windspeed", speed) || extractNumber("wind_speed", speed)) {
        outWindSpeed = std::max(0.0, speed);
    }

    double deg = -1.0;
    if (extractNumber("wind_direction_10m", deg) || extractNumber("winddirection", deg) || extractNumber("wind_deg", deg)) {
        outWindDir = (outWindSpeed > 0.2) ? WindDirectionDegToDir(deg) : WindDir::None;
    }

    std::string dirStr;
    if (outWindDir == WindDir::None && (extractString("wind_dir", dirStr) || extractString("wind_direction", dirStr))) {
        std::wstring wdir(dirStr.begin(), dirStr.end());
        outWindDir = (outWindSpeed > 0.2) ? ParseWindDir(wdir) : WindDir::None;
    }

    double wmo = -999.0;
    if (extractNumber("weather_code", wmo) || extractNumber("weathercode", wmo)) {
        ApplyWmoCode(static_cast<int>(wmo), outPrecip, outFx);
        if (outWindSpeed >= 35.0) outFx.windSwirls = true;
        return true;
    }

    std::string cond;
    if (extractString("condition", cond) || extractString("weather", cond)) {
        for (auto& c : cond) c = static_cast<char>(tolower(c));
        outFx = EffectFlags{};
        outPrecip = PrecipKind::None;
        if (cond.find("hail") != std::string::npos) outPrecip = PrecipKind::Hail;
        else if (cond.find("sleet") != std::string::npos) outPrecip = PrecipKind::Sleet;
        else if (cond.find("snow") != std::string::npos) outPrecip = PrecipKind::Snow;
        else if (cond.find("heavy_rain") != std::string::npos || cond.find("storm") != std::string::npos) outPrecip = PrecipKind::HeavyRain;
        else if (cond.find("rain") != std::string::npos) outPrecip = PrecipKind::Rain;

        if (cond.find("fog") != std::string::npos || cond.find("mist") != std::string::npos) outFx.fog = true;
        if (cond.find("rainbow") != std::string::npos) outFx.rainbow = true;
        if (cond.find("lightning") != std::string::npos || cond.find("thunder") != std::string::npos) outFx.lightning = true;
        if (cond.find("wind") != std::string::npos || cond.find("swirl") != std::string::npos || outWindSpeed >= 35.0) {
            outFx.windSwirls = true;
        }
        return true;
    }
    return false;
}

bool FetchFromSource(const std::wstring& src, const Settings& cfg, PrecipKind& outPrecip,
                     EffectFlags& outFx, double& outWindSpeed, WindDir& outWindDir) {
    if (src == L"manual") {
        outPrecip = cfg.manualWeatherPrecip;
        outFx.fog = cfg.manualFog;
        outFx.rainbow = cfg.manualRainbow;
        outFx.lightning = cfg.manualLightning;
        outFx.windSwirls = cfg.manualWindSwirls;
        outWindSpeed = cfg.manualWindSpeed;
        outWindDir = cfg.manualWindDirection;
        return true;
    }
    if (src == L"open_meteo") {
        std::wstringstream url;
        url << L"https://api.open-meteo.com/v1/forecast?latitude=" << cfg.latitude
            << L"&longitude=" << cfg.longitude
            << L"¤t=weather_code,wind_speed_10m,wind_direction_10m";
        std::string body = HttpGetUtf8(url.str());
        if (body.empty()) return false;
        return TryParseWeatherPayload(body, outPrecip, outFx, outWindSpeed, outWindDir);
    }
    if (src == L"custom_api") {
        if (cfg.customApiUrl.empty()) return false;
        std::string body = HttpGetUtf8(cfg.customApiUrl);
        if (body.empty()) return false;
        return TryParseWeatherPayload(body, outPrecip, outFx, outWindSpeed, outWindDir);
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
        return TryParseWeatherPayload(content, outPrecip, outFx, outWindSpeed, outWindDir);
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

        if (cfg.controlMode == L"auto") {
            PrecipKind p = PrecipKind::None;
            EffectFlags fx;
            double windSpd = 0.0;
            WindDir windDir = WindDir::None;

            bool ok = FetchFromSource(cfg.primarySource, cfg, p, fx, windSpd, windDir);
            if (!ok && cfg.fallbackSource != cfg.primarySource) {
                ok = FetchFromSource(cfg.fallbackSource, cfg, p, fx, windSpd, windDir);
            }
            if (ok) {
                std::lock_guard<std::mutex> lock(g_mutex);
                g_autoPrecip = p;
                g_autoEffects = fx;
                g_autoWindSpeedKmh = windSpd;
                g_autoWindDir = windDir;
            }
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

D2D1_COLOR_F ResolveKindColor(const Settings& cfg, PrecipKind kind) {
    switch (kind) {
        case PrecipKind::Rain:
        case PrecipKind::HeavyRain: return cfg.colorRain;
        case PrecipKind::Snow:
        case PrecipKind::Sleet: return cfg.colorSnow;
        case PrecipKind::Hail: return cfg.colorHail;
        case PrecipKind::Sakura: return cfg.colorSakura;
        case PrecipKind::AutumnLeaves: return cfg.colorLeaves;
        case PrecipKind::ExtraSnow: return cfg.colorExtraSnow;
        default: return cfg.colorSnow;
    }
}

void SpawnFallingParticle(FallingParticle& p, std::mt19937& rng, PrecipKind kind,
                          bool fromSeasonGroup, double scale, float windVx, bool randomY) {
    std::uniform_real_distribution<float> xDist(-80.0f, static_cast<float>(g_canvasWidth) + 80.0f);
    std::uniform_real_distribution<float> yDist(0.0f, static_cast<float>(g_canvasHeight));
    std::uniform_real_distribution<float> phaseDist(0.0f, 6.2831853f);
    std::uniform_real_distribution<float> alphaDist(0.65f, 0.96f);

    p.kind = kind;
    p.fromSeasonGroup = fromSeasonGroup;
    p.x = xDist(rng);
    p.y = randomY ? yDist(rng) : -24.0f;
    p.swayPhase = phaseDist(rng);
    p.angle = phaseDist(rng);
    p.alpha = alphaDist(rng);

    float s = static_cast<float>(scale);
    p.vx = windVx;

    switch (kind) {
        case PrecipKind::Rain:
            p.size = 12.0f * s;
            p.vy = 640.0f * s;
            p.vx = windVx * 1.4f;
            p.spin = 0.0f;
            break;
        case PrecipKind::HeavyRain:
            p.size = 18.0f * s;
            p.vy = 880.0f * s;
            p.vx = windVx * 1.7f;
            p.spin = 0.0f;
            break;
        case PrecipKind::Snow:
        case PrecipKind::ExtraSnow:
            p.size = (5.0f + (rng() % 45) * 0.1f) * s;
            p.vy = (55.0f + (rng() % 35)) * s;
            p.vx = windVx * 0.6f;
            p.spin = ((rng() % 100) - 50) * 0.02f;
            break;
        case PrecipKind::Sleet:
            p.size = (5.0f + (rng() % 30) * 0.1f) * s;
            p.vy = (210.0f + (rng() % 70)) * s;
            p.vx = windVx * 1.1f;
            p.spin = ((rng() % 100) - 50) * 0.04f;
            break;
        case PrecipKind::Hail:
            p.size = (5.5f + (rng() % 35) * 0.1f) * s;
            p.vy = (440.0f + (rng() % 120)) * s;
            p.vx = windVx * 1.2f;
            p.spin = ((rng() % 100) - 50) * 0.05f;
            break;
        case PrecipKind::Sakura:
            p.size = (8.0f + (rng() % 40) * 0.1f) * s;
            p.vy = (48.0f + (rng() % 28)) * s;
            p.vx = windVx * 0.8f;
            p.spin = ((rng() % 100) - 50) * 0.04f;
            break;
        case PrecipKind::AutumnLeaves:
            p.size = (9.0f + (rng() % 55) * 0.1f) * s;
            p.vy = (62.0f + (rng() % 38)) * s;
            p.vx = windVx * 0.85f;
            p.spin = ((rng() % 100) - 50) * 0.05f;
            break;
        default:
            break;
    }
}

void DrawObjectShape(ID2D1DCRenderTarget* rt, ID2D1SolidColorBrush* brush,
                     PrecipKind kind, float x, float y, float size, float angle, float vx, float alpha) {
    brush->SetOpacity(std::clamp(alpha, 0.05f, 1.0f));
    if (kind == PrecipKind::Rain || kind == PrecipKind::HeavyRain) {
        rt->DrawLine(
            D2D1::Point2F(x, y),
            D2D1::Point2F(x + vx * 0.02f, y + size),
            brush,
            (kind == PrecipKind::HeavyRain) ? 2.0f : 1.4f);
        return;
    }

    D2D1::Matrix3x2F oldXform;
    rt->GetTransform(&oldXform);
    rt->SetTransform(D2D1::Matrix3x2F::Rotation(angle * 57.29578f, D2D1::Point2F(x, y)) * oldXform);

    if (kind == PrecipKind::Sakura) {
        rt->FillEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), size * 0.65f, size * 0.36f), brush);
    } else if (kind == PrecipKind::AutumnLeaves) {
        rt->FillEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), size * 0.75f, size * 0.38f), brush);
    } else if (kind == PrecipKind::Hail) {
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

void RenderFrame(const Settings& cfg, const EffectFlags& fx, int bottomLimitY) {
    if (!g_overlayHwnd || !IsWindow(g_overlayHwnd)) return;
    if (!EnsureLayeredSurface(g_canvasWidth, g_canvasHeight)) return;

    RECT bindRect = {0, 0, g_canvasWidth, g_canvasHeight};
    g_dcRenderTarget->BindDC(g_memDC, &bindRect);

    g_dcRenderTarget->BeginDraw();
    g_dcRenderTarget->Clear(D2D1::ColorF(0.0f, 0.0f, 0.0f, 0.0f));

    float fxStrength = static_cast<float>(cfg.atmosphereOpacity) / 100.0f;

    // [C] Туман
    if (fx.fog && fxStrength > 0.005f) {
        ID2D1SolidColorBrush* fogBrush = nullptr;
        D2D1_COLOR_F fc = cfg.colorFog;
        fc.a = std::clamp(fc.a * (fxStrength * 1.4f), 0.0f, 0.85f);
        g_dcRenderTarget->CreateSolidColorBrush(fc, &fogBrush);
        if (fogBrush) {
            g_dcRenderTarget->FillRectangle(
                D2D1::RectF(0.0f, 0.0f, static_cast<float>(g_canvasWidth), static_cast<float>(g_canvasHeight)),
                fogBrush);
            fogBrush->Release();
        }
    }

    // [C] Радуга
    if (fx.rainbow && fxStrength > 0.005f) {
        const D2D1_COLOR_F bands[6] = {
            D2D1::ColorF(1.0f, 0.25f, 0.25f, 0.22f * fxStrength),
            D2D1::ColorF(1.0f, 0.62f, 0.18f, 0.22f * fxStrength),
            D2D1::ColorF(1.0f, 0.92f, 0.25f, 0.22f * fxStrength),
            D2D1::ColorF(0.28f, 0.85f, 0.38f, 0.22f * fxStrength),
            D2D1::ColorF(0.25f, 0.62f, 1.0f, 0.22f * fxStrength),
            D2D1::ColorF(0.62f, 0.32f, 0.95f, 0.22f * fxStrength)
        };
        float cx = g_canvasWidth * 0.5f;
        float cy = g_canvasHeight * 0.95f;
        float baseR = std::min(g_canvasWidth, g_canvasHeight) * 0.68f;
        for (int b = 0; b < 6; ++b) {
            ID2D1SolidColorBrush* rb = nullptr;
            g_dcRenderTarget->CreateSolidColorBrush(bands[b], &rb);
            if (rb) {
                float r = baseR - b * 14.0f;
                g_dcRenderTarget->DrawEllipse(
                    D2D1::Ellipse(D2D1::Point2F(cx, cy), r, r * 0.72f),
                    rb,
                    13.0f);
                rb->Release();
            }
        }
    }

    // [C] Видимые завихрения ветра
    if (fx.windSwirls && !g_swirls.empty()) {
        ID2D1SolidColorBrush* sb = nullptr;
        D2D1_COLOR_F sc = cfg.colorSwirl;
        sc.a = std::clamp(sc.a * (0.4f + fxStrength), 0.05f, 0.9f);
        g_dcRenderTarget->CreateSolidColorBrush(sc, &sb);
        if (sb) {
            for (const auto& sw : g_swirls) {
                g_dcRenderTarget->DrawEllipse(
                    D2D1::Ellipse(D2D1::Point2F(sw.x, sw.y), sw.radius * 1.4f, sw.radius * 0.45f),
                    sb,
                    1.6f);
            }
            sb->Release();
        }
    }

    // [C] Молнии
    if (fx.lightning && g_lightning.activeTimer > 0.0f) {
        ID2D1SolidColorBrush* lb = nullptr;
        D2D1_COLOR_F lc = cfg.colorLightning;
        lc.a = std::clamp(g_lightning.activeTimer * 3.5f, 0.0f, 1.0f);
        g_dcRenderTarget->CreateSolidColorBrush(lc, &lb);
        if (lb) {
            float curX = g_lightning.xStart;
            float curY = 0.0f;
            int segs = 12;
            float stepY = (bottomLimitY - g_canvasTop) * 0.75f / segs;
            for (int i = 0; i < segs; ++i) {
                float t = static_cast<float>(i + 1) / segs;
                float nextX = g_lightning.xStart + (g_lightning.xEnd - g_lightning.xStart) * t +
                              ((i % 2 == 0) ? 18.0f : -18.0f);
                float nextY = curY + stepY;
                g_dcRenderTarget->DrawLine(D2D1::Point2F(curX, curY), D2D1::Point2F(nextX, nextY), lb, 3.0f);
                curX = nextX;
                curY = nextY;
            }
            lb->Release();
        }
    }

    // Падающие объекты (без влияния курсора и без срыва от окон)
    ID2D1SolidColorBrush* itemBrush = nullptr;
    g_dcRenderTarget->CreateSolidColorBrush(D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.0f), &itemBrush);
    if (itemBrush) {
        for (const auto& p : g_falling) {
            itemBrush->SetColor(ResolveKindColor(cfg, p.kind));
            DrawObjectShape(g_dcRenderTarget, itemBrush, p.kind, p.x, p.y, p.size, p.angle, p.vx, p.alpha);
        }

        // Опавшие объекты на верхнем крае окон и внизу экрана (сохраняют свой размер и форму)
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
            itemBrush->SetColor(ResolveKindColor(cfg, fo.kind));
            DrawObjectShape(g_dcRenderTarget, itemBrush, fo.kind, drawX, drawY, fo.size, fo.angle, fo.vx, fo.alpha);
        }

        itemBrush->Release();
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

float WindToHorizontalSpeed(WindDir dir, double speedVal) {
    if (dir == WindDir::None || speedVal <= 0.1) return 0.0f;
    float mag = static_cast<float>(speedVal) * 3.2f;
    return (dir == WindDir::Left) ? -mag : mag;
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
        PrecipKind autoP;
        EffectFlags autoFx;
        double autoWindSpd;
        WindDir autoWindDir;
        {
            std::lock_guard<std::mutex> lock(g_mutex);
            cfg = g_settings;
            autoP = g_autoPrecip;
            autoFx = g_autoEffects;
            autoWindSpd = g_autoWindSpeedKmh;
            autoWindDir = g_autoWindDir;
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

        // Определяем активные группы A, B, C
        PrecipKind groupAKind = PrecipKind::None;
        EffectFlags activeFx;
        float groupAWindVx = 0.0f;

        if (cfg.controlMode == L"auto") {
            if (cfg.enableGroupA) groupAKind = autoP;
            activeFx = autoFx;
            groupAWindVx = WindToHorizontalSpeed(autoWindDir, autoWindSpd);
        } else {
            if (cfg.enableGroupA) groupAKind = cfg.manualWeatherPrecip;
            activeFx.fog = cfg.manualFog;
            activeFx.rainbow = cfg.manualRainbow;
            activeFx.lightning = cfg.manualLightning;
            activeFx.windSwirls = cfg.manualWindSwirls;
            groupAWindVx = WindToHorizontalSpeed(cfg.manualWindDirection, cfg.manualWindSpeed);
        }

        PrecipKind groupBKind = PrecipKind::None;
        if (cfg.groupBMode == L"manual") {
            groupBKind = cfg.manualSeasonType;
        } else if (cfg.groupBMode == L"auto_season") {
            groupBKind = DetectCurrentSeasonPrecip();
        }
        float groupBWindVx = WindToHorizontalSpeed(cfg.seasonWindDirection, cfg.seasonWindStrength);

        size_t targetA = (groupAKind != PrecipKind::None)
            ? static_cast<size_t>((g_canvasWidth / 1000.0) * cfg.precipDensity)
            : 0;
        size_t targetB = (groupBKind != PrecipKind::None)
            ? static_cast<size_t>((g_canvasWidth / 1000.0) * cfg.seasonDensity)
            : 0;

        // Синхронизируем списки падающих частиц по группам A и B
        std::vector<FallingParticle> nextFalling;
        nextFalling.reserve(targetA + targetB);
        size_t curA = 0, curB = 0;

        for (const auto& p : g_falling) {
            if (!p.fromSeasonGroup && p.kind == groupAKind && curA < targetA) {
                nextFalling.push_back(p);
                ++curA;
            } else if (p.fromSeasonGroup && p.kind == groupBKind && curB < targetB) {
                nextFalling.push_back(p);
                ++curB;
            }
        }
        while (curA < targetA) {
            FallingParticle p;
            SpawnFallingParticle(p, rng, groupAKind, false, cfg.particleScale, groupAWindVx, true);
            nextFalling.push_back(p);
            ++curA;
        }
        while (curB < targetB) {
            FallingParticle p;
            SpawnFallingParticle(p, rng, groupBKind, true, cfg.particleScale, groupBWindVx, true);
            nextFalling.push_back(p);
            ++curB;
        }
        g_falling.swap(nextFalling);

        // Завихрения ветра [C]
        size_t targetSwirls = activeFx.windSwirls
            ? static_cast<size_t>((g_canvasWidth / 1000.0) * cfg.swirlDensity)
            : 0;
        while (g_swirls.size() < targetSwirls) {
            WindSwirl sw;
            sw.x = static_cast<float>(rng() % std::max(1, g_canvasWidth));
            sw.y = static_cast<float>(rng() % std::max(1, g_canvasHeight));
            sw.radius = 18.0f + static_cast<float>(rng() % 28);
            sw.speed = 65.0f + static_cast<float>(rng() % 90);
            sw.phase = static_cast<float>(rng() % 628) * 0.01f;
            g_swirls.push_back(sw);
        }
        if (g_swirls.size() > targetSwirls) g_swirls.resize(targetSwirls);

        float swirlVx = (std::abs(groupAWindVx) > 1.0f) ? groupAWindVx : -110.0f;
        for (auto& sw : g_swirls) {
            sw.phase += dt * 4.5f;
            sw.x += swirlVx * dt;
            sw.y += std::sin(sw.phase) * 28.0f * dt;
            if (sw.x < -80.0f) sw.x = static_cast<float>(g_canvasWidth) + 60.0f;
            if (sw.x > g_canvasWidth + 80.0f) sw.x = -60.0f;
        }

        // Молнии [C]
        if (activeFx.lightning) {
            if (g_lightning.activeTimer > 0.0f) {
                g_lightning.activeTimer = std::max(0.0f, g_lightning.activeTimer - dt);
            } else {
                float chancePerSec = cfg.lightningFrequency * 0.03f;
                if ((static_cast<float>(rng() % 10000) / 10000.0f) < chancePerSec * dt) {
                    g_lightning.activeTimer = 0.24f;
                    g_lightning.xStart = static_cast<float>(100 + rng() % std::max(120, g_canvasWidth - 200));
                    g_lightning.xEnd = g_lightning.xStart + static_cast<float>((rng() % 160) - 80);
                }
            }
        } else {
            g_lightning.activeTimer = 0.0f;
        }

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
                wm.vx = (cx - wm.prevCenterX) / dt;
                wm.vy = (cy - wm.prevCenterY) / dt;
                float speed = std::hypot(wm.vx, wm.vy);
                if (speed > shakeThreshold) {
                    float shedProb = std::clamp((speed - shakeThreshold) / 1800.0f, 0.08f, 0.75f);
                    for (auto& fo : g_fallen) {
                        if (fo.onWindow && fo.hostWindow == h && !fo.fallingOff) {
                            if ((rng() % 100) < static_cast<int>(shedProb * 100.0f)) {
                                fo.onWindow = false;
                                fo.fallingOff = true;
                                fo.relX = static_cast<float>(r.left - g_canvasLeft) + fo.relX;
                                fo.relY = static_cast<float>(r.top - g_canvasTop) + fo.relY;
                                fo.vx = wm.vx * 0.18f * static_cast<float>(cfg.windowInertiaFactor);
                                fo.vy = std::max(60.0f, wm.vy * 0.18f);
                            }
                        }
                    }
                }
            }
            wm.prevCenterX = cx;
            wm.prevCenterY = cy;
            wm.hasPrev = true;
        }

        // Если окно закрыто – опавшие на нем объекты тоже переходят в свободное падение
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

        // Движение ПАДАЮЩИХ частиц (курсор и перемещение окон на них НЕ влияют)
        for (size_t i = 0; i < g_falling.size(); ++i) {
            FallingParticle& p = g_falling[i];
            float baseWind = p.fromSeasonGroup ? groupBWindVx : groupAWindVx;
            p.swayPhase += dt * 3.0f;
            p.angle += p.spin * dt * 20.0f;

            bool isRain = (p.kind == PrecipKind::Rain || p.kind == PrecipKind::HeavyRain);
            float sway = isRain ? 0.0f : std::sin(p.swayPhase) * 22.0f;
            p.x += (baseWind + sway) * dt;
            p.y += p.vy * dt;

            bool caught = false;
            if (!isRain && cfg.enableWindowAccumulation && static_cast<int>(g_fallen.size()) < cfg.maxFallenItems) {
                for (const auto& kv : g_windows) {
                    const RECT& wr = kv.second.rect;
                    float wLeft = static_cast<float>(wr.left - g_canvasLeft);
                    float wRight = static_cast<float>(wr.right - g_canvasLeft);
                    float wTop = static_cast<float>(wr.top - g_canvasTop);
                    if (p.x >= wLeft + 4.0f && p.x <= wRight - 4.0f && p.y >= wTop - 4.0f && p.y <= wTop + 5.0f) {
                        FallenObject fo;
                        fo.kind = p.kind;
                        fo.onWindow = true;
                        fo.hostWindow = kv.first;
                        fo.relX = p.x - wLeft;
                        fo.relY = -p.size * 0.4f;
                        fo.size = p.size;
                        fo.angle = p.angle;
                        fo.alpha = p.alpha;
                        g_fallen.push_back(fo);
                        caught = true;
                        break;
                    }
                }
            }

            if (!caught && !isRain && cfg.enableBottomAccumulation &&
                p.y >= bottomRelY - p.size * 0.4f &&
                static_cast<int>(g_fallen.size()) < cfg.maxFallenItems) {
                FallenObject fo;
                fo.kind = p.kind;
                fo.onWindow = false;
                fo.hostWindow = nullptr;
                fo.relX = p.x;
                fo.relY = -p.size * 0.4f;
                fo.size = p.size;
                fo.angle = p.angle;
                fo.alpha = p.alpha;
                g_fallen.push_back(fo);
                caught = true;
            }

            if (caught || p.y > g_canvasHeight + 30.0f || p.x < -120.0f || p.x > g_canvasWidth + 120.0f) {
                SpawnFallingParticle(p, rng, p.kind, p.fromSeasonGroup, cfg.particleScale, baseWind, false);
            }
        }

        // Взаимодействие с курсором и физика — ТОЛЬКО для опавших объектов
        POINT cursorPt = {};
        GetCursorPos(&cursorPt);
        float cX = static_cast<float>(cursorPt.x - g_canvasLeft);
        float cY = static_cast<float>(cursorPt.y - g_canvasTop);
        float cRad = static_cast<float>(cfg.cursorRadiusPx);

        for (auto& fo : g_fallen) {
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
                            // Если курсор сдвинул объект за край окна – он падает вниз
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
                if (fo.relY >= bottomRelY - fo.size * 0.4f) {
                    fo.fallingOff = false;
                    fo.onWindow = false;
                    fo.vx = 0.0f;
                    fo.vy = 0.0f;
                    fo.relY = -fo.size * 0.4f;
                }
            }
        }

        // Постепенное таяние/исчезновение опавших объектов
        if (cfg.decaySpeed > 0.0 && !g_fallen.empty()) {
            float removeCountFloat = static_cast<float>(cfg.decaySpeed) * dt;
            int toFade = static_cast<int>(removeCountFloat) + (((rng() % 1000) < static_cast<int>((removeCountFloat - static_cast<int>(removeCountFloat)) * 1000.0f)) ? 1 : 0);
            for (int k = 0; k < toFade && !g_fallen.empty(); ++k) {
                size_t idx = rng() % g_fallen.size();
                g_fallen[idx].alpha -= 0.25f;
                if (g_fallen[idx].alpha <= 0.05f) {
                    g_fallen.erase(g_fallen.begin() + idx);
                }
            }
        }

        RenderFrame(cfg, activeFx, bottomLimitY);

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