# PandaDLL

A DLC unlocker for the EA App written in C++. This was made and published for educational purposes only.

> **Note:** This DLC unlocker does not download DLC content for you. You need to download the DLC files yourself. For Sims 4, you can find DLC-only downloads at: https://anadius.su/sims-4-dlc-only

## Quick Start

### Download
Head to the [Releases](../../releases) page and download the latest `version.dll`.

## How to use

1. Locate your EA App installation directory (usually contains `EADesktop.exe`)
2. Place the `version.dll` file in this directory
3. Create the following folder structure:
   ```
   %appdata%\GlitchedPanda\EA DLC Unlocker V1\
   ```
4. Create `entitlements.ini` in the above directory with the following format:

```ini
[Pretty Name]
IID=itemId
ETG=entitlementTag
GRP=group
TYP=type
```

**Example:**
```ini
[The Sims™ 4 Outdoor Retreat]
IID=SIMS4.OFF.SOLP.0x0000000000011A4B
ETG=GreatOutdoors_0x0000000000011A4B:72267
GRP=THESIMS4PC
TYP=DEFAULT
```

## How to build

### Prerequisites
- Visual Studio 2019 or later
- vcpkg package manager

### Build steps
1. Clone vcpkg if you haven't already: `git clone https://github.com/Microsoft/vcpkg.git`
2. Run `.\vcpkg\bootstrap-vcpkg.bat`
3. Integrate with Visual Studio: `.\vcpkg\vcpkg integrate install`
4. Open the project in Visual Studio
5. Dependencies will be automatically installed via vcpkg.json
6. Build the project (Ctrl+Shift+B)

## License

This project is licensed under the GNU General Public License v3.0 - see the [LICENSE](LICENSE) file for details.