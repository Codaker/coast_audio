import 'dart:ffi';

import 'package:coast_audio/ffi_extension.dart';
import 'package:coast_audio_miniaudio/coast_audio_miniaudio.dart';

class WasapiDeviceInfo extends DeviceInfo<String> {
  const WasapiDeviceInfo({
    required super.id,
    required super.name,
    required super.type,
    required super.isDefault,
  }) : super(backend: MabBackend.wasapi);

  factory WasapiDeviceInfo.fromMabDeviceInfo(MabDeviceInfo info, MabDeviceType type) {
    return WasapiDeviceInfo(
      id: info.id.wasapi,
      name: info.name,
      type: type,
      isDefault: info.isDefault,
    );
  }

  @override
  void fillInfo(MabDeviceInfo info) {
    info.pDeviceInfo.ref.id.wasapi.setString(id);
    info.pDeviceInfo.ref.name.setString(name);
    info.id.stringId = id;
  }
}
