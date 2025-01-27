import 'dart:ffi';

import 'package:coast_audio/coast_audio.dart';
import 'package:coast_audio_miniaudio/coast_audio_miniaudio.dart';
import 'package:coast_audio_miniaudio/generated/ma_bridge_bindings.dart';
import 'package:coast_audio_miniaudio/src/ma_extension.dart';
import 'package:ffi/ffi.dart';

class MabDeviceContext extends MabBase {
  static MabDeviceContext? _instance;

  static MabDeviceContext get sharedInstance {
    if (_instance == null) {
      throw Exception('MabDeviceContext.enabledSharedInstance() was not called');
    }
    return _instance!;
  }

  static void enableSharedInstance({
    required List<MabBackend> backends,
  }) {
    _instance = MabDeviceContext(backends: backends);
  }

  MabDeviceContext({
    required List<MabBackend> backends,
    Memory? memory,
  }) : super(memory: memory) {
    final pBackends = allocate<Int32>(sizeOf<Int32>() * backends.length);
    for (var i = 0; backends.length > i; i++) {
      pBackends.elementAt(i).value = backends[i].value;
    }
    library.mab_device_context_init(pDeviceContext, pBackends, backends.length).throwMaResultIfNeeded();
  }

  late final pDeviceContext = allocate<mab_device_context>(sizeOf<mab_device_context>());

  MabBackend get activeBackend => MabBackend.fromRawValue(pDeviceContext.ref.backend);

  List<DeviceInfo> getDevices(MabDeviceType type) {
    final devices = <DeviceInfo>[];
    final pCount = malloc.allocate<Int>(sizeOf<Int>());
    try {
      library.mab_device_context_get_device_count(pDeviceContext, type.value, pCount).throwMaResultIfNeeded();

      for (var i = 0; pCount.value > i; i++) {
        final info = MabDeviceInfo(backend: activeBackend, memory: memory);
        library.mab_device_context_get_device_info(pDeviceContext, type.value, i, info.pDeviceInfo).throwMaResultIfNeeded();
        devices.add(info.getDeviceInfo(type));
        info.dispose();
      }

      return devices;
    } finally {
      malloc.free(pCount);
    }
  }

  @override
  void uninit() {
    library.mab_device_context_uninit(pDeviceContext).throwMaResultIfNeeded();
  }
}
