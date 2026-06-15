; Script generated and improved for Windows 10/11 file associations

#include "version.iss.inc"

#define MyAppName "NFS-ModscriptViewer"
#define MyAppPublisher "Kevin4e"
#define MyAppURL "https://github.com/Kevin4e/NFS-ModscriptViewer"
#define MyAppExeName "NFS-ModscriptViewer.exe"

#define MyAppAssocKeyNFSMS "NFSModscriptFile"
#define MyAppAssocNameNFSMS "NFS Modscript File"

#define MyAppAssocKeyEND "NFSEndscriptFile"
#define MyAppAssocNameEND "NFS Endscript File"

#define SourceDir "C:\Users\Kevin\source\repos\NFS-ModscriptViewer\NFS-ModscriptViewer"

[Setup]
AppId={{082B3D9B-294C-4C69-A93B-673E8F565ECD}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
AppVerName={#MyAppName}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}

DefaultDirName={autopf}\{#MyAppName}
UninstallDisplayIcon={app}\{#MyAppExeName}

ArchitecturesAllowed=x64compatible
ArchitecturesInstallIn64BitMode=x64compatible

ChangesAssociations=yes
DisableProgramGroupPage=yes

LicenseFile=C:\Users\Kevin\source\repos\NFS-ModscriptViewer\LICENSE

OutputBaseFilename=NFS-ModscriptViewer_v{#MyAppVersion}_win-x64_setup
OutputDir=C:\Users\Kevin\source\repos\NFS-ModscriptViewer\NFS-ModscriptViewer\setup\output
SolidCompression=yes
WizardStyle=modern

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
Source: "{#SourceDir}\build\release-windows-x64\{#MyAppExeName}"; DestDir: "{app}"; Flags: ignoreversion
Source: "{#SourceDir}\deploy\release-windows-x64\*"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs

[Registry]
; =========================
; FILE ASSOCIATIONS (.nfsms)
; =========================

; Extension -> ProgID
Root: HKA; Subkey: "Software\Classes\.nfsms"; ValueType: string; ValueName: ""; ValueData: "{#MyAppAssocKeyNFSMS}"; Flags: uninsdeletevalue
Root: HKA; Subkey: "Software\Classes\.nfsms"; ValueType: string; ValueName: "PerceivedType"; ValueData: "text"
Root: HKA; Subkey: "Software\Classes\.nfsms\OpenWithProgids"; ValueType: string; ValueName: "{#MyAppAssocKeyNFSMS}"; ValueData: ""; Flags: uninsdeletevalue

; ProgID (.nfsms)
Root: HKA; Subkey: "Software\Classes\{#MyAppAssocKeyNFSMS}"; ValueType: string; ValueName: ""; ValueData: "{#MyAppAssocNameNFSMS}"; Flags: uninsdeletekey
Root: HKA; Subkey: "Software\Classes\{#MyAppAssocKeyNFSMS}"; ValueType: string; ValueName: "FriendlyTypeName"; ValueData: "{#MyAppAssocNameNFSMS}"
Root: HKA; Subkey: "Software\Classes\{#MyAppAssocKeyNFSMS}\DefaultIcon"; ValueType: string; ValueName: ""; ValueData: "{app}\{#MyAppExeName},0"
Root: HKA; Subkey: "Software\Classes\{#MyAppAssocKeyNFSMS}\shell\open\command"; ValueType: string; ValueName: ""; ValueData: """{app}\{#MyAppExeName}"" ""%1"""

; =========================
; FILE ASSOCIATIONS (.end)
; =========================

; Extension -> ProgID
Root: HKA; Subkey: "Software\Classes\.end"; ValueType: string; ValueName: ""; ValueData: "{#MyAppAssocKeyEND}"; Flags: uninsdeletevalue
Root: HKA; Subkey: "Software\Classes\.end"; ValueType: string; ValueName: "PerceivedType"; ValueData: "text"
Root: HKA; Subkey: "Software\Classes\.end\OpenWithProgids"; ValueType: string; ValueName: "{#MyAppAssocKeyEND}"; ValueData: ""; Flags: uninsdeletevalue

; ProgID (.end)
Root: HKA; Subkey: "Software\Classes\{#MyAppAssocKeyEND}"; ValueType: string; ValueName: ""; ValueData: "{#MyAppAssocNameEND}"; Flags: uninsdeletekey
Root: HKA; Subkey: "Software\Classes\{#MyAppAssocKeyEND}"; ValueType: string; ValueName: "FriendlyTypeName"; ValueData: "{#MyAppAssocNameEND}"
Root: HKA; Subkey: "Software\Classes\{#MyAppAssocKeyEND}\DefaultIcon"; ValueType: string; ValueName: ""; ValueData: "{app}\{#MyAppExeName},0"
Root: HKA; Subkey: "Software\Classes\{#MyAppAssocKeyEND}\shell\open\command"; ValueType: string; ValueName: ""; ValueData: """{app}\{#MyAppExeName}"" ""%1"""

[Icons]
Name: "{autoprograms}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
Name: "{autodesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon

[Run]
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#MyAppName}}"; Flags: nowait postinstall skipifsilent