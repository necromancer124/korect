# korect

**korect** is a lightweight native Windows desktop utility that provides a system-wide text correction overlay, similar in concept to Steam Overlay. Press **Ctrl + Shift + Space** to open a compact QuickCorrect window over the current application, type or paste text, right-click underlined issues for suggestions, then copy the corrected text.

## Architecture

```text
/Core
  CorrectionEngine      local spelling/grammar/punctuation rules, suggestion cache, optional local LanguageTool client
/Configuration
  SettingsManager       JSON settings, personal dictionary, Windows startup registration
/System
  GlobalHotkeyManager   RegisterHotKey-based global shortcut, no polling
  ForegroundWindowManager remembers/restores previous foreground window
  OverlayManager        show/hide lifecycle; overlay is hidden, not destroyed
/UI
  OverlayWindow         borderless topmost correction overlay, RichEdit text editor, context menus
  OptionsWindow         separate settings/options window with sidebar categories
```

## Technology selection

The implementation uses **C++17 + Win32/RichEdit** rather than Electron. This keeps idle CPU/RAM low, supports native `RegisterHotKey`, uses a hidden background message window, and creates a real topmost borderless overlay without a browser runtime. The app is distributed as a standalone Windows GUI `.exe` when built with MinGW static linking.

WPF/WinUI 3 would also work, but this environment did not have the .NET SDK installed. Native Win32 was the most reliable way to produce and verify a lightweight Windows executable here.

## Overlay behavior

- `RegisterHotKey` listens for the global hotkey without a polling loop.
- When opened, korect records the current foreground `HWND`, shows the borderless topmost overlay, and focuses the RichEdit editor.
- The underlying app is not minimized, closed, injected into, or modified.
- When the overlay closes, korect hides the overlay window and calls `SetForegroundWindow` on the previously captured app.
- The overlay window remains created in memory for fast reopening.

## Exclusive-fullscreen limitation

korect intentionally does **not** use DLL injection, game memory modification, or anti-cheat bypasses. Normal topmost Windows overlays work best with desktop apps and games in **windowed** or **borderless-windowed** mode. True exclusive-fullscreen games may block or cover ordinary desktop windows; use borderless/windowed mode in those cases.

## Correction engine and privacy

korect defaults to **offline/local only**.

1. It first tries a local LanguageTool server at `127.0.0.1:8081` if available.
2. It always has a built-in lightweight local rule engine for common spelling, repeated words, `i` capitalization, multiple spaces, and punctuation spacing.
3. It never sends text to an external service by default.
4. Online processing is an explicit setting and the UI warns that text may be sent externally. This build does not enable any external endpoint by default.

### Real words and auto-correction

korect does **not** automatically replace words by default. Even when the automatic-correction option is enabled later, spelling correction is intentionally conservative: words that are known to the built-in dictionary, the personal dictionary, or an optional `dictionary.txt` file beside the executable are treated as real words and are not spelling-autocorrected. They may still be shown in grammar suggestions if a local LanguageTool server reports a sentence-level grammar issue.

To add more real words, open **Options > Dictionary** or place a plain text file here:

```text
build\dictionary.txt
```

Put one word per line or separate words with spaces, then restart korect.

To run local LanguageTool yourself:

```sh
java -cp languagetool-server.jar org.languagetool.server.HTTPServer --port 8081 --allow-origin "*"
```

## Performance choices

- No foreground-window polling.
- Overlay is hidden rather than destroyed.
- Correction engine is initialized once.
- Debounced checks default to 300 ms after typing stops.
- Checks run asynchronously; the UI thread only applies results.
- Results are cached for repeated text.
- Maximum text length defaults to 12,000 characters.
- The Options window is separate so customization does not inflate the overlay path.

## Build

Requirements: CMake, Ninja, and a MinGW-w64/WinLibs toolchain in PATH.

```sh
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
```

The executable is created at:

```text
build/korect.exe
```

## Run

```sh
./build/korect.exe --minimized
```

Double-click the tray icon or press **Ctrl + Shift + Space**.

## Options menu

Open **Options** from the overlay. Settings are saved automatically as you edit them, and the **Apply button** explicitly writes the current options to disk and confirms they were saved.

Settings are stored at:

```text
%APPDATA%\korect\settings.json
```

Categories include Appearance, Overlay, Hotkeys, Correction, Languages, Dictionary, Privacy, Performance, Advanced, and About. The personal dictionary is stored locally in the same JSON file.

## Troubleshooting

- **Hotkey conflict:** another app may own Ctrl+Shift+Space. Open Options > Hotkeys, change `openHotkeyVk`/modifiers, save, and restart korect.
- **Overlay does not appear over a game:** switch the game to windowed or borderless-windowed mode.
- **No grammar suggestions:** install/run local LanguageTool for advanced grammar; the built-in engine still provides basic local checks.
- **Language missing:** built-in dictionary is English-focused. Other languages are supported when a local LanguageTool server supports them.
- **Settings broke:** delete `%APPDATA%\korect\settings.json`; korect recreates defaults.

## Safety

korect does not inject DLLs, modify game memory, hook games, or bypass anti-cheat systems.
