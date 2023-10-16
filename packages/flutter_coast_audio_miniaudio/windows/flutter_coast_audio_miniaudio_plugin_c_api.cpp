#include "include/flutter_coast_audio_miniaudio/flutter_coast_audio_miniaudio_plugin_c_api.h"

#include <flutter/plugin_registrar_windows.h>

#include "flutter_coast_audio_miniaudio_plugin.h"

void FlutterCoastAudioMiniaudioPluginCApiRegisterWithRegistrar(
    FlutterDesktopPluginRegistrarRef registrar) {
  flutter_coast_audio_miniaudio::FlutterCoastAudioMiniaudioPlugin::RegisterWithRegistrar(
      flutter::PluginRegistrarManager::GetInstance()
          ->GetRegistrar<flutter::PluginRegistrarWindows>(registrar));
}
