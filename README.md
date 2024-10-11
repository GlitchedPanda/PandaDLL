# PandaDLL
DLC Unlocker for the EA App written in C++. This was made an published for educational purposes only.

## How to use
- Put the built `version.dll` in the directory where you have installed the EA App. There should be an executable called EADesktop.exe in the directory.
- Make a folder in %appdata% called `GlitchedPanda`, inside that make a folder called `EA DLC Unlocker V1`.
- Make a file called entitlements.ini inside this folder. The format is:
```
[Pretty Name]
IID=itemId
ETG=entitlementTag
GRP=group
TYP=type
```

## How to build
- Download the detour library from github and put Detour-main in the root of your c drive.
- Press Build
