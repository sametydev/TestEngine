#pragma once
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <string_view>
#include <algorithm>
#include <memory>
#include <variant>
#include <Windows.h>
#include "PCH.h"
#pragma warning( disable : 4018 )
#pragma warning( disable : 4267 )
#pragma warning( disable : 4251 )
#pragma warning( disable : 26495 )


#define RETURN_IF_COOKED if (IS_COOKED) {return;};

#include "Core/HWInfo.h"

#ifdef ENGINE_EXPORTS
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)
#endif


enum GameState {
    NONE = 0,
    PLAYING,
    PAUSED
};

enum class RenderTextureCreateFlags
{
    None = 0,
    Depth = 1,
    UAV = 2,
    Linear = 4,
    RenderTarget = 8
};

class ENGINE_API PathMaker {
public:
    inline static std::string Make(std::string p1, std::string p2) {
        return p1 + p2;
    }
    inline static std::wstring MakeW(std::string p1, std::string p2) {
        std::string str = (p1 + p2);
        return std::wstring(str.begin(),str.end());
    }
};

//inline size_t StrToSZT(std::string_view str)
//{
//    static std::hash<std::string_view> hash;
//    return hash(str);
//}

template <size_t S> struct ENUM_TO_INT;
template <> struct ENUM_TO_INT<1> { typedef char  type; };
template <> struct ENUM_TO_INT<2> { typedef short type; };
template <> struct ENUM_TO_INT<4> { typedef int  type; };
template <> struct ENUM_TO_INT<8> { typedef long type; };

template <class T> struct UnderlyingType {
    typedef typename ENUM_TO_INT<sizeof(T)>::type type;
};

inline constexpr RenderTextureCreateFlags operator | (RenderTextureCreateFlags a, RenderTextureCreateFlags b) noexcept {
    return RenderTextureCreateFlags(((UnderlyingType < RenderTextureCreateFlags > ::type) a) | ((UnderlyingType < RenderTextureCreateFlags > ::type) b));
}
inline RenderTextureCreateFlags& operator |= (RenderTextureCreateFlags& a, RenderTextureCreateFlags b) noexcept {
    return (RenderTextureCreateFlags&)(((UnderlyingType < RenderTextureCreateFlags > ::type&) a) |= ((UnderlyingType < RenderTextureCreateFlags > ::type) b));
}
inline constexpr RenderTextureCreateFlags operator & (RenderTextureCreateFlags a, RenderTextureCreateFlags b) noexcept {
    return RenderTextureCreateFlags(((UnderlyingType < RenderTextureCreateFlags > ::type) a) & ((UnderlyingType < RenderTextureCreateFlags > ::type) b));
}
inline RenderTextureCreateFlags& operator &= (RenderTextureCreateFlags& a, RenderTextureCreateFlags b) noexcept {
    return (RenderTextureCreateFlags&)(((UnderlyingType < RenderTextureCreateFlags > ::type&) a) &= ((UnderlyingType < RenderTextureCreateFlags > ::type) b));
}
inline constexpr RenderTextureCreateFlags operator~(RenderTextureCreateFlags a) noexcept {
    return RenderTextureCreateFlags(~((UnderlyingType < RenderTextureCreateFlags > ::type) a));
}
inline constexpr RenderTextureCreateFlags operator ^ (RenderTextureCreateFlags a, RenderTextureCreateFlags b) noexcept {
    return RenderTextureCreateFlags(((UnderlyingType < RenderTextureCreateFlags > ::type) a) ^ ((UnderlyingType < RenderTextureCreateFlags > ::type) b));
}
inline RenderTextureCreateFlags& operator ^= (RenderTextureCreateFlags& a, RenderTextureCreateFlags b) noexcept {
    return (RenderTextureCreateFlags&)(((UnderlyingType < RenderTextureCreateFlags > ::type&) a) ^= ((UnderlyingType < RenderTextureCreateFlags > ::type) b));
}


constexpr int SLATE_GAMEPAD_DPAD_UP        = 0x0001;
constexpr int SLATE_GAMEPAD_DPAD_DOWN      = 0x0002;
constexpr int SLATE_GAMEPAD_DPAD_LEFT      = 0x0004;
constexpr int SLATE_GAMEPAD_DPAD_RIGHT     = 0x0008;
constexpr int SLATE_GAMEPAD_START          = 0x0010;
constexpr int SLATE_GAMEPAD_BACK           = 0x0020;
constexpr int SLATE_GAMEPAD_LEFT_THUMB     = 0x0040;
constexpr int SLATE_GAMEPAD_RIGHT_THUMB    = 0x0080;
constexpr int SLATE_GAMEPAD_LEFT_SHOULDER  = 0x0100;
constexpr int SLATE_GAMEPAD_RIGHT_SHOULDER = 0x0200;
constexpr int SLATE_GAMEPAD_A              = 0x1000;
constexpr int SLATE_GAMEPAD_B              = 0x2000;
constexpr int SLATE_GAMEPAD_X              = 0x4000;
constexpr int SLATE_GAMEPAD_Y              = 0x8000;

#define _NULL_CHECK     if (this == nullptr) {return;};


inline static wchar_t* charToWChar(const char* text)
{
    const size_t size = strlen(text) + 1;
    wchar_t* wText = new wchar_t[size];
    size_t outsize;
    mbstowcs_s(&outsize, wText, size, text, size - 1);
    return wText;
}

inline void convertWStringToCharPtr(_In_ std::wstring input, _Out_ char* outputString)
{
    size_t outputSize = input.length() + 1;
    outputString = new char[outputSize];
    size_t charsConverted = 0;
    wcstombs_s(&charsConverted, outputString, outputSize, input.c_str(), input.length());
}

inline std::wstring s2ws(const std::string& str)
{
    int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
    std::wstring wstrTo(size_needed, 0);
    MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
    return wstrTo;
}

inline std::string removeQuotesFromStartAndBack(std::string str) {
    if (!str.empty() && str.front() == '"' && str.back() == '"') {
        str = str.substr(1, str.size() - 2);
    }

    return str;
}

inline static int iota(bool reset = false) {
    static int counter = 0; 
    if (reset) {
        counter = 0;
        return counter;
    }
    return counter++;
}