; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

#define MyAppName "TikBew"
#define MyAppVersion "2.0.3"
#define MyAppPublisher "Lambda Centauri"
#define MyAppURL "https://lambdacentauri.com/software_tikbew.htm"
#define MyAppExeName "Tikbew.exe"
#define CodeDir "E:\code\Tikbew"

[Setup]
; NOTE: The value of AppId uniquely identifies this application.
; Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{027A06AA-7EAC-4157-99AE-D8CA213775E2}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
AppVerName={#MyAppName} {#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName={pf}\{#MyAppPublisher}\{#MyAppName}
DisableDirPage=yes
DefaultGroupName={#MyAppPublisher}
DisableProgramGroupPage=yes
LicenseFile={#CodeDir}\License.txt
OutputDir={#CodeDir}\installer
OutputBaseFilename={#MyAppName}{#MyAppVersion}Setup
SetupIconFile={#CodeDir}\TikBew32.ico
UninstallDisplayIcon={app}\TikBew32.ico
Compression=lzma
SolidCompression=yes

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
Source: "{#CodeDir}\installer\D3Dcompiler_47.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "{#CodeDir}\installer\icudt54.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "{#CodeDir}\installer\icuin54.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "{#CodeDir}\installer\icuuc54.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "{#CodeDir}\installer\libeay32.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "{#CodeDir}\installer\libEGL.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "{#CodeDir}\installer\libgcc_s_dw2-1.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "{#CodeDir}\installer\libGLESv2.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "{#CodeDir}\installer\libssl32.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "{#CodeDir}\installer\libstdc++-6.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "{#CodeDir}\installer\libwinpthread-1.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "{#CodeDir}\License.txt"; DestDir: "{app}"; Flags: ignoreversion
Source: "{#CodeDir}\installer\opengl32sw.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "{#CodeDir}\installer\Qt5Core.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "{#CodeDir}\installer\Qt5Gui.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "{#CodeDir}\installer\Qt5Multimedia.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "{#CodeDir}\installer\Qt5MultimediaWidgets.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "{#CodeDir}\installer\Qt5Network.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "{#CodeDir}\installer\Qt5OpenGL.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "{#CodeDir}\installer\Qt5Positioning.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "{#CodeDir}\installer\Qt5PrintSupport.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "{#CodeDir}\installer\Qt5Qml.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "{#CodeDir}\installer\Qt5Quick.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "{#CodeDir}\installer\Qt5Sensors.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "{#CodeDir}\installer\Qt5Sql.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "{#CodeDir}\installer\Qt5Svg.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "{#CodeDir}\installer\Qt5WebChannel.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "{#CodeDir}\installer\Qt5Webkit.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "{#CodeDir}\installer\Qt5WebkitWidgets.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "{#CodeDir}\installer\Qt5Widgets.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "{#CodeDir}\installer\ssl_license.txt"; DestDir: "{app}"; Flags: ignoreversion
Source: "{#CodeDir}\installer\ssleay32.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "{#CodeDir}\installer\Tikbew.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "{#CodeDir}\installer\TikBew32.ico"; DestDir: "{app}"; Flags: ignoreversion
Source: "{#CodeDir}\installer\TikBew32.png"; DestDir: "{app}"; Flags: ignoreversion
Source: "{#CodeDir}\installer\TikBew64.png"; DestDir: "{app}"; Flags: ignoreversion
Source: "{#CodeDir}\installer\audio\*"; DestDir: "{app}\audio"; Flags: ignoreversion
Source: "{#CodeDir}\installer\bearer\*.*"; DestDir: "{app}\bearer"; Flags: ignoreversion
Source: "{#CodeDir}\installer\iconengines\*.*"; DestDir: "{app}\iconengines"; Flags: ignoreversion
Source: "{#CodeDir}\installer\imageformats\*.*"; DestDir: "{app}\imageformats"; Flags: ignoreversion
Source: "{#CodeDir}\installer\mediaservice\*.*"; DestDir: "{app}\mediaservice"; Flags: ignoreversion
Source: "{#CodeDir}\installer\platforms\qwindows.dll"; DestDir: "{app}\platforms"; Flags: ignoreversion
Source: "{#CodeDir}\installer\playlistformats\*.*"; DestDir: "{app}\playlistformats"; Flags: ignoreversion
Source: "{#CodeDir}\installer\position\*.*"; DestDir: "{app}\position"; Flags: ignoreversion
Source: "{#CodeDir}\installer\printsupport\*.*"; DestDir: "{app}\printsupport"; Flags: ignoreversion
;Source: "{#CodeDir}\installer\sensorgestures\*.*"; DestDir: "{app}\sensorgestures"; Flags: ignoreversion
;Source: "{#CodeDir}\installer\sensors\*.*"; DestDir: "{app}\sensors"; Flags: ignoreversion
;Source: "{#CodeDir}\installer\sqldrivers\*.*"; DestDir: "{app}\sqldrivers"; Flags: ignoreversion
;Source: "{#CodeDir}\installer\translations\*.*"; DestDir: "{app}\translations"; Flags: ignoreversion
; NOTE: Don't use "Flags: ignoreversion" on any shared system files
;Source: "{#CodeDir}\installer\vcredist_x86.exe"; DestDir: "{app}"; Flags: ignoreversion deleteafterinstall

[Icons]
Name: "{group}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; WorkingDir: "{app}"
Name: "{group}\TikBew Website"; Filename: "{#MyAppURL}"
;Name: "{commondesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon; WorkingDir: "{app}"

[Run]
;Filename: "{app}\vcredist_x86.exe"; Parameters: "/q /norestart"; WorkingDir: "{app}";  StatusMsg: "Installing Visual C++ 2012 Redistributable..."; Flags: waituntilterminated
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"; Flags: nowait postinstall skipifsilent

