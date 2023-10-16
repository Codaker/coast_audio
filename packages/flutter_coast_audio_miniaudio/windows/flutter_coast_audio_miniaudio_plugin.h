#ifndef FLUTTER_PLUGIN_FLUTTER_COAST_AUDIO_MINIAUDIO_PLUGIN_H_
#define FLUTTER_PLUGIN_FLUTTER_COAST_AUDIO_MINIAUDIO_PLUGIN_H_

#include <flutter/method_channel.h>
#include <flutter/plugin_registrar_windows.h>

#include <memory>

namespace flutter_coast_audio_miniaudio {

class FlutterCoastAudioMiniaudioPlugin : public flutter::Plugin {
 public:
  static void RegisterWithRegistrar(flutter::PluginRegistrarWindows *registrar);

  FlutterCoastAudioMiniaudioPlugin();

  virtual ~FlutterCoastAudioMiniaudioPlugin();

  // Disallow copy and assign.
  FlutterCoastAudioMiniaudioPlugin(const FlutterCoastAudioMiniaudioPlugin&) = delete;
  FlutterCoastAudioMiniaudioPlugin& operator=(const FlutterCoastAudioMiniaudioPlugin&) = delete;

  // Called when a method is called on this plugin's channel from Dart.
  void HandleMethodCall(
      const flutter::MethodCall<flutter::EncodableValue> &method_call,
      std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result);
};

}  // namespace flutter_coast_audio_miniaudio

#endif  // FLUTTER_PLUGIN_FLUTTER_COAST_AUDIO_MINIAUDIO_PLUGIN_H_
