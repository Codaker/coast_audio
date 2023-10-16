#pragma once
#include "mab_enum.h"
#include "mab_types.h"
#include "mab_device_context.h"
#include <stdint.h>

typedef struct {
  mab_format format;
  int sampleRate;
  int channels;
  double gainDb;
  double shelfSlope;
  double frequency;
} mab_low_shelf_filter_config;

mab_low_shelf_filter_config mab_low_shelf_filter_config_init(mab_format format, uint32_t sampleRate, uint32_t channels, double gainDb, double shelfSlope, double frequency);

typedef struct {
  void* pData;
} mab_low_shelf_filter;

mab_result mab_low_shelf_filter_init(mab_low_shelf_filter* pLSF, mab_low_shelf_filter_config config);

mab_result mab_low_shelf_filter_process(mab_low_shelf_filter* pLSF, void* pFramesOut, const void* pFramesIn, uint64_t frameCount);

mab_result mab_low_shelf_filter_reinit(mab_low_shelf_filter* pLSF, mab_low_shelf_filter_config config);

uint32_t mab_low_shelf_filter_get_latency(mab_low_shelf_filter* pLSF);

void mab_low_shelf_filter_uninit(mab_low_shelf_filter* pLSF);
