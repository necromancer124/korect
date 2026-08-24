cmake_minimum_required(VERSION 3.20)
project(korect LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_executable(korect WIN32
    main.cpp
    Configuration/SettingsManager.cpp
    Core/CorrectionEngine.cpp
    System/GlobalHotkeyManager.cpp
    System/ForegroundWindowManager.cpp
    System/OverlayManager.cpp
    UI/OverlayWindow.cpp
    UI/OptionsWindow.cpp
)
target_include_directories(korect PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_definitions(korect PRIVATE UNICODE _UNICODE WIN32_LEAN_AND_MEAN NOMINMAX)
target_link_libraries(korect PRIVATE user32 gdi32 comctl32 comdlg32 shell32 shlwapi advapi32 ole32 oleaut32 uuid winhttp ws2_32 msimg32)
if(MINGW)
  target_link_options(korect PRIVATE -municode -static -static-libgcc -static-libstdc++)
endif()
add_custom_command(TARGET korect POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_SOURCE_DIR}/settings.default.json $<TARGET_FILE_DIR:korect>/settings.default.json)
