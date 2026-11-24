// ==WindhawkMod==
// @id              alembiq-weather-desktop-overlay
// @name            Desktop Weather & Particles Overlay
// @description     Weather effects (snow, rain, fog, wind, clear) and seasonal particles (snow, rain, leaves, poplar fluff, sakura) under desktop icons with window accumulation and shake physics.
// @version         0.2.0
// @author          Custom
// @github          https://github.com/duschkopf/alembiq-weather-desktop-overlay/
// @include         explorer.exe
// @compilerOptions -ld2d1 -ldwrite -lwininet -luser32 -lgdi32 -lshell32 -lole32
// ==/WindhawkMod==

/* ==WindhawkModSettings==
- layerAttachMode: auto
  $name: Привязка слоя рабочего стола
  $description: Выбор способа размещения слоя над обоями и под иконками рабочего стола
  $options:
    - auto: Авто (под иконками SHELLDLL_DefView)
    - progman_direct: Привязка к окну Progman
    - desktop_bottom: Поверх обоев (HWND_BOTTOM)
- bottomBoundaryMode: above_taskbar
  $name: Нижняя граница накопления
  $description: Где накапливаются осадки в нижней части экрана
  $options:
    - above_taskbar: Над панелью задач (Shell_TrayWnd)
    - screen_bottom: По нижнему краю экрана
    - custom_offset: Ручной отступ снизу (px)
- bottomOffsetPx: 0
  $name: Ручной отступ снизу (px)
- multiMonitorMode: primary
  $name: Мониторы
  $options:
    - primary: Основной монитор
    - all: Все мониторы (виртуальный экран)
- weatherMode: manual
  $name: Режим погоды
  $options:
    - manual: Ручной
    - auto: Автоматический по прогнозу
- manualWeather: snow
  $name: Погода (ручной режим)
  $options:
    - clear: Солнечно
    - rain: Дождь
    - snow: Снег
    - fog: Туман
    - wind: Ветер
- precipitationType: snow
  $name: Тип частиц / осадков
  $options:
    - snow: Снег (зима)
    - rain: Дождь
    - leaves: Падающие листья (осень)
    - poplar_fluff: Тополиный пух (лето)
    - sakura: Лепестки сакуры (весна)
- primarySource: open_meteo
  $name: Основной источник погоды
  $options:
    - open_meteo: Open-Meteo API (без ключа)
    - custom_api: Кастомный HTTP/HTTPS JSON URL
    - local_file: Локальный JSON/текстовый файл
- fallbackSource: manual
  $name: Резервный источник при ошибке
  $options:
    - manual: Ручной режим
    - open_meteo: Open-Meteo API
    - local_file: Локальный файл
- latitude: "44.7866"
  $name: Широта (Open-Meteo)
- longitude: "20.4489"
  $name: Долгота (Open-Meteo)
- customApiUrl: ""
  $name: URL кастомного JSON API
- localWeatherPath: ""
  $name: Путь к локальному файлу погоды
- updateIntervalMin: 30
  $name: Интервал обновления погоды (мин)
- particleDensity: 45
  $name: Плотность частиц (на 1000 px)
- particleScale: "1.0"
  $name: Масштаб частиц (0.5 - 2.5)
- windStrength: 15
  $name: Сила ветра (-100..100)
- atmosphereOpacity: 35
  $name: Интенсивность тумана / света (0..100%)
- enableBottomAccumulation: true
  $name: Накопление внизу экрана
- maxBottomHeightPx: 36
  $name: Макс. высота слоя внизу (px)
- enableWindowAccumulation: true
  $name: Накопление на верхнем крае окон
- maxWindowHeightPx: 14
  $name: Макс. высота слоя на окне (px)
- windowShakeSensitivity: 55
  $name: Чувствительность срыва при движении окна (1..100)
- windowInertiaFactor: "0.65"
  $name: Инерция при срыве с окна (0.0..2.0)
- cursorInteraction: true
  $name: Взаимодействие с курсором
- cursorRadiusPx: 90
  $name: Радиус влияния курсора (px)
- meltSpeed: "1.5"
  $name: Скорость таяния/испарения (px/сек)
- targetFps: 60
  $name: Целевой FPS (30 или 60)
- pauseOnFullscreen: true
  $name: Пауза при полноэкранных окнах
- excludedProcesses: "obs64.exe, ApplicationFrameHost.exe"
  $name: Исключения процессов (через запятую)
==/WindhawkModSettings== */

#include <windows.h>
#include <wininet.h>
#include <d2d1.h>
#include <dwmapi.h>
#include <atomic>
#include <chrono>
#include <cmath>
#include <algorithm>
#include <mutex>
#include <random>
#include <sstream>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

namespace {

enum class WeatherCondition {
    Clear,
    Rain,
    Snow,
    Fog,
    Wind
};

enum class PrecipType {
    Snow,
    Rain,
    Leaves,
    PoplarFluff,
    Sakura
};

struct Settings {
    std::wstring layerAttachMode = L"auto";
    std::wstring bottomBoundaryMode = L"above_taskbar";
    int bottomOffsetPx = 0;
    std::wstring multiMonitorMode = L"primary";

    std::wstring weatherMode = L"manual";
    WeatherCondition manualWeather = WeatherCondition::Snow;
    PrecipType precipType = PrecipType::Snow;

    std::wstring primarySource = L"open_meteo";
    std::wstring fallbackSource = L"manual";
    double latitude = 44.7866;
    double longitude = 20.4489;
    std::wstring customApiUrl;
    std::wstring localWeatherPath;
    int updateIntervalMin = 30;

    int particleDensity = 45;
    double particleScale = 1.0;
    int windStrength = 15;
    int atmosphereOpacity = 35;

    bool enableBottomAccumulation = true;
    int maxBottomHeightPx = 36;
    bool enableWindowAccumulation = true;
    int maxWindowHeightPx = 14;
    int windowShakeSensitivity = 55;
    double windowInertiaFactor = 0.65;

    bool cursorInteraction = true;
    int cursorRadiusPx = 90;
    double meltSpeed = 1.5;

    int targetFps = 60;
    bool pauseOnFullscreen = true;
    std::wstring excludedProcesses = L"obs64.exe, ApplicationFrameHost.exe";
};

struct Particle {
    float x = 0.0f;
    float y = 0.0f;
    float vx = 0.0f;
    float vy = 0.0f;
    float size = 4.0f;
    float angle = 0.0f;
    float spin = 0.0f;
    float swayPhase = 0.0f;
    float alpha = 0.85f;
};

struct TrackedWindow {
    HWND hwnd = nullptr;
    RECT rect = {};
    float prevCenterX = 0.0f;
    float prevCenterY = 0.0f;
    float vx = 0.0f;
    float vy = 0.0f;
    bool hasPrev = false;
    std::vector<float> topHeights;
};

std::mutex g_mutex;
Settings g_settings;
WeatherCondition g_effectiveWeather = WeatherCondition::Snow;
double g_fetchedWindKmh = 0.0;

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

std::vector<Particle> g_particles;
std::vector<float> g_bottomHeights;
std::unordered_map<HWND, TrackedWindow> g_windows;

std::wstring ToLower(std::wstring s) {
    for (auto& ch : s) ch = static_cast<wchar_t>(towlower(ch));
    return s;
}

WeatherCondition ParseWeatherStr(const std::wstring& s) {
    std::wstring v = ToLower(s);
    if (v == L"rain") return WeatherCondition::Rain;
    if (v == L"snow") return WeatherCondition::Snow;
    if (v == L"fog") return WeatherCondition::Fog;
    if (v == L"wind") return WeatherCondition::Wind;
    return WeatherCondition::Clear;
}

PrecipType ParsePrecipStr(const std::wstring& s) {
    std::wstring v = ToLower(s);
    if (v == L"rain") return PrecipType::Rain;
    if (v == L"leaves") return PrecipType::Leaves;
    if (v == L"poplar_fluff") return PrecipType::PoplarFluff;
    if (v == L"sakura") return PrecipType::Sakura;
    return PrecipType::Snow;
}

std::vector<std::wstring> SplitExcluded(const std::wstring& raw) {
    std::vector<std::wstring> result;
    std::wstringstream ss(raw);
    std::wstring item;
    while (std::getline(ss, item, L',')) {
        size_t start = item.find_first_not_of(L" \t\r\n");
        size_t end = item.find_last_not_of(L" \t\r\n");
        if (start != std::wstring::npos && end != std::wstring::npos) {
            result.push_back(ToLower(item.substr(start, end - start + 1)));
        }
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

    next.weatherMode = readStr(L"weatherMode", L"manual");
    next.manualWeather = ParseWeatherStr(readStr(L"manualWeather", L"snow"));
    next.precipType = ParsePrecipStr(readStr(L"precipitationType", L"snow"));

    next.primarySource = readStr(L"primarySource", L"open_meteo");
    next.fallbackSource = readStr(L"fallbackSource", L"manual");

    std::wstring latStr = readStr(L"latitude", L"44.7866");
    std::wstring lonStr = readStr(L"longitude", L"20.4489");
    try { next.latitude = std::stod(latStr); } catch (...) {}
    try { next.longitude = std::stod(lonStr); } catch (...) {}

    next.customApiUrl = readStr(L"customApiUrl", L"");
    next.localWeatherPath = readStr(L"localWeatherPath", L"");
    next.updateIntervalMin = std::max(1, Wh_GetIntSetting(L"updateIntervalMin"));

    next.particleDensity = std::clamp(Wh_GetIntSetting(L"particleDensity"), 0, 200);
    std::wstring scaleStr = readStr(L"particleScale", L"1.0");
    try { next.particleScale = std::clamp(std::stod(scaleStr), 0.3, 4.0); } catch (...) {}

    next.windStrength = std::clamp(Wh_GetIntSetting(L"windStrength"), -100, 100);
    next.atmosphereOpacity = std::clamp(Wh_GetIntSetting(L"atmosphereOpacity"), 0, 100);

    next.enableBottomAccumulation = Wh_GetIntSetting(L"enableBottomAccumulation") != 0;
    next.maxBottomHeightPx = std::clamp(Wh_GetIntSetting(L"maxBottomHeightPx"), 4, 250);

    next.enableWindowAccumulation = Wh_GetIntSetting(L"enableWindowAccumulation") != 0;
    next.maxWindowHeightPx = std::clamp(Wh_GetIntSetting(L"maxWindowHeightPx"), 2, 100);

    next.windowShakeSensitivity = std::clamp(Wh_GetIntSetting(L"windowShakeSensitivity"), 1, 100);
    std::wstring inertiaStr = readStr(L"windowInertiaFactor", L"0.65");
    try { next.windowInertiaFactor = std::clamp(std::stod(inertiaStr), 0.0, 3.0); } catch (...) {}

    next.cursorInteraction = Wh_GetIntSetting(L"cursorInteraction") != 0;
    next.cursorRadiusPx = std::clamp(Wh_GetIntSetting(L"cursorRadiusPx"), 10, 400);

    std::wstring meltStr = readStr(L"meltSpeed", L"1.5");
    try { next.meltSpeed = std::max(0.0, std::stod(meltStr)); } catch (...) {}

    next.targetFps = (Wh_GetIntSetting(L"targetFps") == 30) ? 30 : 60;
    next.pauseOnFullscreen = Wh_GetIntSetting(L"pauseOnFullscreen") != 0;
    next.excludedProcesses = readStr(L"excludedProcesses", L"obs64.exe, ApplicationFrameHost.exe");

    std::lock_guard<std::mutex> lock(g_mutex);
    g_settings = next;
    if (g_settings.weatherMode == L"manual") {
        g_effectiveWeather = g_settings.manualWeather;
    }
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

    HINTERNET hSession = InternetOpenW(L"WindhawkWeatherMod/0.2", INTERNET_OPEN_TYPE_PRECONFIG, nullptr, nullptr, 0);
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

WeatherCondition MapWmoWeatherCode(int code, double windKmh) {
    if (code == 71 || code == 73 || code == 75 || code == 77 || code == 85 || code == 86) {
        return WeatherCondition::Snow;
    }
    if ((code >= 51 && code <= 67) || (code >= 80 && code <= 82) || (code >= 95 && code <= 99)) {
        return WeatherCondition::Rain;
    }
    if (code == 45 || code == 48) {
        return WeatherCondition::Fog;
    }
    if (windKmh >= 35.0) {
        return WeatherCondition::Wind;
    }
    return WeatherCondition::Clear;
}

bool TryParseSimpleJsonWeather(const std::string& json, WeatherCondition& outCond, double& outWind) {
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

    double wind = 0.0;
    extractNumber("windspeed", wind);
    extractNumber("wind_speed_10m", wind);
    outWind = wind;

    double wmo = -1.0;
    if (extractNumber("weathercode", wmo) || extractNumber("weather_code", wmo)) {
        outCond = MapWmoWeatherCode(static_cast<int>(wmo), wind);
        return true;
    }

    std::string condStr;
    if (extractString("condition", condStr) || extractString("weather", condStr)) {
        for (auto& c : condStr) c = static_cast<char>(tolower(c));
        if (condStr.find("snow") != std::string::npos) { outCond = WeatherCondition::Snow; return true; }
        if (condStr.find("rain") != std::string::npos) { outCond = WeatherCondition::Rain; return true; }
        if (condStr.find("fog") != std::string::npos || condStr.find("mist") != std::string::npos) {
            outCond = WeatherCondition::Fog; return true;
        }
        if (condStr.find("wind") != std::string::npos) { outCond = WeatherCondition::Wind; return true; }
        if (condStr.find("clear") != std::string::npos || condStr.find("sun") != std::string::npos) {
            outCond = WeatherCondition::Clear; return true;
        }
    }
    return false;
}

bool FetchFromSource(const std::wstring& src, const Settings& cfg, WeatherCondition& outCond, double& outWind) {
    if (src == L"manual") {
        outCond = cfg.manualWeather;
        outWind = 0.0;
        return true;
    }
    if (src == L"open_meteo") {
        std::wstringstream url;
        url << L"https://api.open-meteo.com/v1/forecast?latitude=" << cfg.latitude
            << L"&longitude=" << cfg.longitude
            << L"¤t_weather=true";
        std::string body = HttpGetUtf8(url.str());
        if (body.empty()) return false;
        return TryParseSimpleJsonWeather(body, outCond, outWind);
    }
    if (src == L"custom_api") {
        if (cfg.customApiUrl.empty()) return false;
        std::string body = HttpGetUtf8(cfg.customApiUrl);
        if (body.empty()) return false;
        return TryParseSimpleJsonWeather(body, outCond, outWind);
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
        if (TryParseSimpleJsonWeather(content, outCond, outWind)) return true;

        std::string lower = content;
        for (auto& c : lower) c = static_cast<char>(tolower(c));
        if (lower.find("snow") != std::string::npos) { outCond = WeatherCondition::Snow; return true; }
        if (lower.find("rain") != std::string::npos) { outCond = WeatherCondition::Rain; return true; }
        if (lower.find("fog") != std::string::npos) { outCond = WeatherCondition::Fog; return true; }
        if (lower.find("wind") != std::string::npos) { outCond = WeatherCondition::Wind; return true; }
        if (lower.find("clear") != std::string::npos) { outCond = WeatherCondition::Clear; return true; }
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

        if (cfg.weatherMode == L"auto") {
            WeatherCondition cond = cfg.manualWeather;
            double wind = 0.0;
            bool ok = FetchFromSource(cfg.primarySource, cfg, cond, wind);
            if (!ok && cfg.fallbackSource != cfg.primarySource) {
                ok = FetchFromSource(cfg.fallbackSource, cfg, cond, wind);
            }
            if (ok) {
                std::lock_guard<std::mutex> lock(g_mutex);
                g_effectiveWeather = cond;
                g_fetchedWindKmh = wind;
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

    if (static_cast<int>(g_bottomHeights.size()) != g_canvasWidth) {
        g_bottomHeights.assign(g_canvasWidth, 0.0f);
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

    HWND owner = GetWindow(hwnd, GW_OWNER);
    if (owner != nullptr) return TRUE;

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
    if (progman) {
        HWND defView = FindWindowExW(progman, nullptr, L"SHELLDLL_DefView", nullptr);
        if (defView) return progman;
    }
    HWND workerW = nullptr;
    while ((workerW = FindWindowExW(nullptr, workerW, L"WorkerW", nullptr)) != nullptr) {
        HWND defView = FindWindowExW(workerW, nullptr, L"SHELLDLL_DefView", nullptr);
        if (defView) return workerW;
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

void SpawnParticle(Particle& p, std::mt19937& rng, PrecipType type, double scale, float windVx, bool randomY) {
    std::uniform_real_distribution<float> xDist(0.0f, static_cast<float>(g_canvasWidth));
    std::uniform_real_distribution<float> yDist(0.0f, static_cast<float>(g_canvasHeight));
    std::uniform_real_distribution<float> phaseDist(0.0f, 6.2831853f);
    std::uniform_real_distribution<float> alphaDist(0.55f, 0.95f);

    p.x = xDist(rng);
    p.y = randomY ? yDist(rng) : -20.0f;
    p.swayPhase = phaseDist(rng);
    p.alpha = alphaDist(rng);
    p.angle = phaseDist(rng);

    float s = static_cast<float>(scale);
    switch (type) {
        case PrecipType::Rain:
            p.size = 10.0f * s;
            p.vx = windVx * 1.4f;
            p.vy = 620.0f * s;
            p.spin = 0.0f;
            break;
        case PrecipType::Snow:
            p.size = (3.0f + (rng() % 40) * 0.1f) * s;
            p.vx = windVx * 0.5f;
            p.vy = (55.0f + (rng() % 35)) * s;
            p.spin = ((rng() % 100) - 50) * 0.02f;
            break;
        case PrecipType::Leaves:
            p.size = (7.0f + (rng() % 50) * 0.1f) * s;
            p.vx = windVx * 0.8f;
            p.vy = (65.0f + (rng() % 40)) * s;
            p.spin = ((rng() % 100) - 50) * 0.05f;
            break;
        case PrecipType::PoplarFluff:
            p.size = (4.0f + (rng() % 30) * 0.1f) * s;
            p.vx = windVx * 0.9f;
            p.vy = (32.0f + (rng() % 25)) * s;
            p.spin = ((rng() % 100) - 50) * 0.03f;
            break;
        case PrecipType::Sakura:
            p.size = (6.0f + (rng() % 35) * 0.1f) * s;
            p.vx = windVx * 0.7f;
            p.vy = (50.0f + (rng() % 30)) * s;
            p.spin = ((rng() % 100) - 50) * 0.04f;
            break;
    }
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
    bmi.bmiHeader.biHeight = -height; // top-down DIB
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

    HRESULT hr = g_d2dFactory->CreateDCRenderTarget(&props, &g_dcRenderTarget);
    if (FAILED(hr) || !g_dcRenderTarget) {
        CleanupSurfaceResources();
        return false;
    }
    return true;
}

void RenderFrame(const Settings& cfg, WeatherCondition cond, PrecipType pType, int bottomLimitY) {
    if (!g_overlayHwnd || !IsWindow(g_overlayHwnd)) return;
    if (!EnsureLayeredSurface(g_canvasWidth, g_canvasHeight)) return;

    RECT bindRect = {0, 0, g_canvasWidth, g_canvasHeight};
    g_dcRenderTarget->BindDC(g_memDC, &bindRect);

    g_dcRenderTarget->BeginDraw();
    g_dcRenderTarget->Clear(D2D1::ColorF(0.0f, 0.0f, 0.0f, 0.0f));

    float atmoAlpha = static_cast<float>(cfg.atmosphereOpacity) / 100.0f * 0.35f;
    if (cond == WeatherCondition::Fog && atmoAlpha > 0.005f) {
        ID2D1SolidColorBrush* fogBrush = nullptr;
        g_dcRenderTarget->CreateSolidColorBrush(D2D1::ColorF(0.85f, 0.88f, 0.92f, atmoAlpha), &fogBrush);
        if (fogBrush) {
            g_dcRenderTarget->FillRectangle(
                D2D1::RectF(0.0f, 0.0f, static_cast<float>(g_canvasWidth), static_cast<float>(g_canvasHeight)),
                fogBrush);
            fogBrush->Release();
        }
    } else if (cond == WeatherCondition::Clear && atmoAlpha > 0.005f) {
        ID2D1SolidColorBrush* sunBrush = nullptr;
        g_dcRenderTarget->CreateSolidColorBrush(D2D1::ColorF(1.0f, 0.92f, 0.65f, atmoAlpha * 0.45f), &sunBrush);
        if (sunBrush) {
            g_dcRenderTarget->FillEllipse(
                D2D1::Ellipse(D2D1::Point2F(g_canvasWidth * 0.85f, g_canvasHeight * 0.12f), 260.0f, 260.0f),
                sunBrush);
            sunBrush->Release();
        }
    }

    D2D1_COLOR_F particleColor = D2D1::ColorF(1.0f, 1.0f, 1.0f, 0.9f);
    switch (pType) {
        case PrecipType::Rain:
            particleColor = D2D1::ColorF(0.55f, 0.78f, 1.0f, 0.65f);
            break;
        case PrecipType::Snow:
            particleColor = D2D1::ColorF(0.96f, 0.98f, 1.0f, 0.9f);
            break;
        case PrecipType::Leaves:
            particleColor = D2D1::ColorF(0.85f, 0.42f, 0.12f, 0.9f);
            break;
        case PrecipType::PoplarFluff:
            particleColor = D2D1::ColorF(1.0f, 1.0f, 0.98f, 0.88f);
            break;
        case PrecipType::Sakura:
            particleColor = D2D1::ColorF(1.0f, 0.72f, 0.82f, 0.88f);
            break;
    }

    ID2D1SolidColorBrush* brush = nullptr;
    g_dcRenderTarget->CreateSolidColorBrush(particleColor, &brush);
    if (brush) {
        for (const auto& p : g_particles) {
            brush->SetOpacity(p.alpha);
            if (pType == PrecipType::Rain) {
                g_dcRenderTarget->DrawLine(
                    D2D1::Point2F(p.x, p.y),
                    D2D1::Point2F(p.x + p.vx * 0.02f, p.y + p.size),
                    brush,
                    1.5f);
            } else if (pType == PrecipType::Leaves || pType == PrecipType::Sakura) {
                g_dcRenderTarget->FillEllipse(
                    D2D1::Ellipse(D2D1::Point2F(p.x, p.y), p.size * 0.65f, p.size * 0.35f),
                    brush);
            } else {
                g_dcRenderTarget->FillEllipse(
                    D2D1::Ellipse(D2D1::Point2F(p.x, p.y), p.size * 0.5f, p.size * 0.5f),
                    brush);
            }
        }

        if (cfg.enableWindowAccumulation) {
            brush->SetOpacity(0.85f);
            for (const auto& kv : g_windows) {
                const TrackedWindow& tw = kv.second;
                int w = tw.rect.right - tw.rect.left;
                int topRel = tw.rect.top - g_canvasTop;
                int leftRel = tw.rect.left - g_canvasLeft;
                for (int x = 0; x < w; x += 2) {
                    float h = tw.topHeights[x];
                    if (h > 0.5f) {
                        g_dcRenderTarget->FillRectangle(
                            D2D1::RectF(
                                static_cast<float>(leftRel + x),
                                static_cast<float>(topRel) - h,
                                static_cast<float>(leftRel + x + 2),
                                static_cast<float>(topRel)),
                            brush);
                    }
                }
            }
        }

        if (cfg.enableBottomAccumulation && !g_bottomHeights.empty()) {
            brush->SetOpacity(0.9f);
            int baseRel = bottomLimitY - g_canvasTop;
            for (int x = 0; x < g_canvasWidth; x += 2) {
                float h = g_bottomHeights[x];
                if (h > 0.5f) {
                    g_dcRenderTarget->FillRectangle(
                        D2D1::RectF(
                            static_cast<float>(x),
                            static_cast<float>(baseRel) - h,
                            static_cast<float>(x + 2),
                            static_cast<float>(baseRel)),
                        brush);
                }
            }
        }

        brush->Release();
    }

    HRESULT hr = g_dcRenderTarget->EndDraw();
    if (hr == D2DERR_RECREATE_TARGET) {
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
        WeatherCondition cond = WeatherCondition::Snow;
        double apiWindKmh = 0.0;
        {
            std::lock_guard<std::mutex> lock(g_mutex);
            cfg = g_settings;
            cond = g_effectiveWeather;
            apiWindKmh = g_fetchedWindKmh;
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

        std::vector<std::wstring> excluded = SplitExcluded(cfg.excludedProcesses);
        std::vector<HWND> activeHwnds;
        EnumCtx ctx{&excluded, &activeHwnds};
        EnumWindows(EnumWindowsProc, reinterpret_cast<LPARAM>(&ctx));

        float shakeThreshold = 1400.0f - (cfg.windowShakeSensitivity * 11.5f);
        shakeThreshold = std::max(120.0f, shakeThreshold);

        for (HWND h : activeHwnds) {
            RECT r = {};
            if (!GetWindowRect(h, &r)) continue;
            int w = std::max(1, static_cast<int>(r.right - r.left));
            auto& tw = g_windows[h];
            tw.hwnd = h;
            tw.rect = r;
            if (static_cast<int>(tw.topHeights.size()) != w) {
                tw.topHeights.assign(w, 0.0f);
            }

            float cx = (r.left + r.right) * 0.5f;
            float cy = (r.top + r.bottom) * 0.5f;
            if (tw.hasPrev) {
                tw.vx = (cx - tw.prevCenterX) / dt;
                tw.vy = (cy - tw.prevCenterY) / dt;
                float speed = std::hypot(tw.vx, tw.vy);
                if (speed > shakeThreshold) {
                    float shedRatio = std::clamp((speed - shakeThreshold) / 2500.0f, 0.05f, 0.65f);
                    for (int x = 0; x < w; ++x) {
                        if (tw.topHeights[x] > 0.2f && ((rng() % 100) < static_cast<int>(shedRatio * 100.0f))) {
                            float amount = tw.topHeights[x] * shedRatio;
                            tw.topHeights[x] -= amount;
                            Particle p;
                            p.x = static_cast<float>(r.left + x - g_canvasLeft);
                            p.y = static_cast<float>(r.top - g_canvasTop) - 2.0f;
                            p.vx = tw.vx * 0.15f * static_cast<float>(cfg.windowInertiaFactor);
                            p.vy = std::max(40.0f, tw.vy * 0.15f);
                            p.size = std::clamp(amount * 1.4f, 3.0f, 12.0f);
                            p.alpha = 0.9f;
                            g_particles.push_back(p);
                        }
                    }
                }
            }
            tw.prevCenterX = cx;
            tw.prevCenterY = cy;
            tw.hasPrev = true;
        }

        for (auto it = g_windows.begin(); it != g_windows.end();) {
            if (std::find(activeHwnds.begin(), activeHwnds.end(), it->first) == activeHwnds.end()) {
                it = g_windows.erase(it);
            } else {
                ++it;
            }
        }

        PrecipType pType = cfg.precipType;
        if (cond == WeatherCondition::Rain) pType = PrecipType::Rain;
        else if (cond == WeatherCondition::Snow && pType == PrecipType::Rain) pType = PrecipType::Snow;

        size_t targetCount = 0;
        if (cond != WeatherCondition::Clear && cond != WeatherCondition::Fog) {
            targetCount = static_cast<size_t>((g_canvasWidth / 1000.0) * cfg.particleDensity);
        } else if (cond == WeatherCondition::Clear && (pType == PrecipType::PoplarFluff || pType == PrecipType::Sakura)) {
            targetCount = static_cast<size_t>((g_canvasWidth / 1000.0) * (cfg.particleDensity * 0.5));
        }

        float effectiveWind = static_cast<float>(cfg.windStrength) * 2.5f;
        if (cfg.weatherMode == L"auto" && apiWindKmh > 1.0) {
            effectiveWind += static_cast<float>(apiWindKmh) * 2.0f;
        }
        if (cond == WeatherCondition::Wind && std::abs(effectiveWind) < 80.0f) {
            effectiveWind = (effectiveWind >= 0.0f) ? 160.0f : -160.0f;
        }

        while (g_particles.size() < targetCount) {
            Particle p;
            SpawnParticle(p, rng, pType, cfg.particleScale, effectiveWind, true);
            g_particles.push_back(p);
        }
        if (g_particles.size() > targetCount + 200) {
            g_particles.resize(targetCount);
        }

        POINT cursorPt = {};
        GetCursorPos(&cursorPt);
        float cX = static_cast<float>(cursorPt.x - g_canvasLeft);
        float cY = static_cast<float>(cursorPt.y - g_canvasTop);
        int bottomLimitY = ComputeBottomLimitY(cfg);
        float bottomRelY = static_cast<float>(bottomLimitY - g_canvasTop);

        float meltDelta = static_cast<float>(cfg.meltSpeed) * dt;
        if (cond == WeatherCondition::Clear) meltDelta *= 2.0f;
        if (meltDelta > 0.0f && !g_bottomHeights.empty()) {
            for (float& h : g_bottomHeights) {
                if (h > 0.0f) h = std::max(0.0f, h - meltDelta);
            }
        }

        for (size_t i = 0; i < g_particles.size(); ++i) {
            Particle& p = g_particles[i];
            p.swayPhase += dt * 3.0f;
            p.angle += p.spin;

            float sway = (pType == PrecipType::Rain) ? 0.0f : std::sin(p.swayPhase) * 25.0f;
            p.x += (p.vx + effectiveWind + sway) * dt;
            p.y += p.vy * dt;

            if (cfg.cursorInteraction) {
                float dx = p.x - cX;
                float dy = p.y - cY;
                float dist = std::hypot(dx, dy);
                float rad = static_cast<float>(cfg.cursorRadiusPx);
                if (dist > 0.1f && dist < rad) {
                    float push = (1.0f - dist / rad) * 320.0f * dt;
                    p.x += (dx / dist) * push;
                    p.y += (dy / dist) * push;
                }
            }

            bool landed = false;
            if (cfg.enableWindowAccumulation && pType != PrecipType::Rain) {
                for (auto& kv : g_windows) {
                    TrackedWindow& tw = kv.second;
                    float wLeft = static_cast<float>(tw.rect.left - g_canvasLeft);
                    float wRight = static_cast<float>(tw.rect.right - g_canvasLeft);
                    float wTop = static_cast<float>(tw.rect.top - g_canvasTop);
                    if (p.x >= wLeft && p.x < wRight && p.y >= wTop - 4.0f && p.y <= wTop + 6.0f && p.vy > 0.0f) {
                        int idx = std::clamp(static_cast<int>(p.x - wLeft), 0, static_cast<int>(tw.topHeights.size()) - 1);
                        if (tw.topHeights[idx] < static_cast<float>(cfg.maxWindowHeightPx)) {
                            tw.topHeights[idx] = std::min(
                                static_cast<float>(cfg.maxWindowHeightPx),
                                tw.topHeights[idx] + p.size * 0.35f);
                            landed = true;
                            break;
                        }
                    }
                }
            }

            if (!landed && cfg.enableBottomAccumulation && p.y >= bottomRelY && pType != PrecipType::Rain) {
                int idx = std::clamp(static_cast<int>(p.x), 0, static_cast<int>(g_bottomHeights.size()) - 1);
                if (g_bottomHeights[idx] < static_cast<float>(cfg.maxBottomHeightPx)) {
                    g_bottomHeights[idx] = std::min(
                        static_cast<float>(cfg.maxBottomHeightPx),
                        g_bottomHeights[idx] + p.size * 0.35f);
                    landed = true;
                }
            }

            if (landed || p.y > g_canvasHeight + 30.0f || p.x < -100.0f || p.x > g_canvasWidth + 100.0f) {
                if (i < targetCount) {
                    SpawnParticle(p, rng, pType, cfg.particleScale, effectiveWind, false);
                } else {
                    p.y = -50.0f;
                }
            }
        }

        RenderFrame(cfg, cond, pType, bottomLimitY);

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