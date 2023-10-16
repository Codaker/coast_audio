#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"

#include "mab_types.h"
#include "mab_high_pass_filter.h"

mab_high_pass_filter_config mab_high_pass_filter_config_init(mab_format format, uint32_t sampleRate, uint32_t channels, uint32_t order, double cutoffFrequency)
{
  mab_high_pass_filter_config config = {
      .format = format,
      .sampleRate = sampleRate,
      .channels = channels,
      .order = order,
      .cutoffFrequency = cutoffFrequency,
  };
  return config;
}

mab_result mab_high_pass_filter_init(mab_high_pass_filter* pHPF, mab_high_pass_filter_config config)
{
  ma_hpf_config maConfig = ma_hpf_config_init(mab_cast(ma_format, config.format), config.channels, config.sampleRate, config.cutoffFrequency, config.order);
  ma_hpf* pData = MAB_MALLOC(sizeof(ma_hpf));

  ma_result result = ma_hpf_init(&maConfig, NULL, pData);
  if (result != MA_SUCCESS) {
    MAB_FREE(pData);
    return mab_cast(mab_result, result);
  }

  pHPF->pData = (void*)pData;
  return mab_cast(mab_result, result);
}

mab_result mab_high_pass_filter_process(mab_high_pass_filter* pHPF, void* pFramesOut, const void* pFramesIn, uint64_t frameCount)
{
  ma_result result = ma_hpf_process_pcm_frames((ma_hpf*)pHPF->pData, pFramesOut, pFramesIn, frameCount);
  return mab_cast(mab_result, result);
}

mab_result mab_high_pass_filter_reinit(mab_high_pass_filter* pHPF, mab_high_pass_filter_config config)
{
  ma_hpf_config maConfig = ma_hpf_config_init(mab_cast(ma_format, config.format), config.channels, config.sampleRate, config.cutoffFrequency, config.order);
  ma_result result = ma_hpf_reinit(&maConfig, (ma_hpf*)pHPF->pData);
  return mab_cast(mab_result, result);
}

uint32_t mab_high_pass_filter_get_latency(mab_high_pass_filter* pHPF)
{
  return (uint32_t)ma_hpf_get_latency((ma_hpf*)pHPF->pData);
}

void mab_high_pass_filter_uninit(mab_high_pass_filter* hpf)
{
  ma_hpf* pMahpf = (ma_hpf*)hpf->pData;
  ma_hpf_uninit(pMahpf, NULL);
  MAB_FREE(pMahpf);
  hpf->pData = NULL;
}
