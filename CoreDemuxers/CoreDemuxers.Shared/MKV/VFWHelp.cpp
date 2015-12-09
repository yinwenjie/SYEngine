#include "VFWHelp.h"

static const unsigned kRIFFH264FCC[] = {_MK_RIFF_FCC('H264'),_MK_RIFF_FCC('h264'),
_MK_RIFF_FCC('X264'),_MK_RIFF_FCC('x264'),_MK_RIFF_FCC('avc1'),_MK_RIFF_FCC('AVC1')};
static const unsigned kRIFFH263FCC[] = {_MK_RIFF_FCC('H263'),_MK_RIFF_FCC('X263'),
_MK_RIFF_FCC('h263'),_MK_RIFF_FCC('x263')};
static const unsigned kRIFFMPEG4FCC[] = {_MK_RIFF_FCC('FMP4'),_MK_RIFF_FCC('DIVX'),_MK_RIFF_FCC('XVID'),
_MK_RIFF_FCC('DX50'),_MK_RIFF_FCC('MP4S'),_MK_RIFF_FCC('M4S2'),
_MK_RIFF_FCC('DIV1'),_MK_RIFF_FCC('ZMP4'),_MK_RIFF_FCC('UMP4'),
_MK_RIFF_FCC('RMP4'),_MK_RIFF_FCC('BLZO'),_MK_RIFF_FCC('mp4v'),
_MK_RIFF_FCC('3IV2'),_MK_RIFF_FCC('SMP4'),_MK_RIFF_FCC('M4T3'),
_MK_RIFF_FCC('FFDS'),_MK_RIFF_FCC('FVFW'),_MK_RIFF_FCC('MVXM'),
_MK_RIFF_FCC('PM4V'),_MK_RIFF_FCC('G264'),_MK_RIFF_FCC('HDX4'),
_MK_RIFF_FCC('DM4V'),_MK_RIFF_FCC('EM4A'),_MK_RIFF_FCC('M4CC'),
_MK_RIFF_FCC('SIPP'),_MK_RIFF_FCC('SN40'),_MK_RIFF_FCC('WV1F'),
_MK_RIFF_FCC('SEDG'),_MK_RIFF_FCC('WAWV'),_MK_RIFF_FCC('DCOD'),
_MK_RIFF_FCC('DXGM'),_MK_RIFF_FCC('VIDM'),_MK_RIFF_FCC('GEOX')};
static const unsigned kRIFFMPEG4V3FCC[] = {_MK_RIFF_FCC('MP43'),_MK_RIFF_FCC('DIV3'),
_MK_RIFF_FCC('MPG3'),_MK_RIFF_FCC('DIV5'),_MK_RIFF_FCC('DIV6'),_MK_RIFF_FCC('DIV4'),
_MK_RIFF_FCC('DVX3'),_MK_RIFF_FCC('AP41'),_MK_RIFF_FCC('COL1'),_MK_RIFF_FCC('COL0')};
static const unsigned kRIFFMPEG4V2FCC[] = {_MK_RIFF_FCC('MP42'),_MK_RIFF_FCC('DIV2')};
static const unsigned kRIFFMPEG4V1FCC[] = {_MK_RIFF_FCC('MP41'),_MK_RIFF_FCC('MPG4')};
static const unsigned kRIFFMPG1VFCC[] = {_MK_RIFF_FCC('mpg1'),_MK_RIFF_FCC('PIM1'),
_MK_RIFF_FCC('XMPG'),_MK_RIFF_FCC('BW10'),_MK_RIFF_FCC('VCR2')};
static const unsigned kRIFFMPG2VFCC[] = {_MK_RIFF_FCC('mpg2'),_MK_RIFF_FCC('MPEG'),
_MK_RIFF_FCC('PIM2'),_MK_RIFF_FCC('MMES'),_MK_RIFF_FCC('DVR '),_MK_RIFF_FCC('LMP2'),
_MK_RIFF_FCC('mpgv'),_MK_RIFF_FCC('slif'),_MK_RIFF_FCC('EM2V')};
static const unsigned kRIFFMJPEGFCC[] = {_MK_RIFF_FCC('MJPG'),_MK_RIFF_FCC('LJPG'),
_MK_RIFF_FCC('mpga'),_MK_RIFF_FCC('JPGL'),_MK_RIFF_FCC('MJLS'),
_MK_RIFF_FCC('jpeg'),_MK_RIFF_FCC('IJPG'),_MK_RIFF_FCC('IJLV'),
_MK_RIFF_FCC('MVJP'),_MK_RIFF_FCC('AVI1'),_MK_RIFF_FCC('AVI2'),
_MK_RIFF_FCC('MTSJ'),_MK_RIFF_FCC('MMJP'),_MK_RIFF_FCC('dmb1')};
static const unsigned kRIFFWMV1FCC[] = {_MK_RIFF_FCC('WMV1')};
static const unsigned kRIFFWMV2FCC[] = {_MK_RIFF_FCC('WMV2'),_MK_RIFF_FCC('GXVE')};
static const unsigned kRIFFWMV3FCC[] = {_MK_RIFF_FCC('WMV3')};
static const unsigned kRIFFVC1FCC[] = {_MK_RIFF_FCC('WVC1'),_MK_RIFF_FCC('WMVA')};
static const unsigned kRIFFFFV1FCC[] = {_MK_RIFF_FCC('FFV1')};
static const unsigned kRIFFFLV1FCC[] = {_MK_RIFF_FCC('FLV1'),_MK_RIFF_FCC('S263')};
static const unsigned kRIFFTHEORAFCC[] = {_MK_RIFF_FCC('theo')};
static const unsigned kRIFFSNOWFCC[] = {_MK_RIFF_FCC('SNOW')};
static const unsigned kRIFFPRORESFCC[] = {_MK_RIFF_FCC('APCN')};
static const unsigned kRIFFDIRACFCC[] = {_MK_RIFF_FCC('drac')};
static const unsigned kRIFFCAVSFCC[] = {_MK_RIFF_FCC('CAVS')};
static const unsigned kRIFFAMVFCC[] = {_MK_RIFF_FCC('AMVF')};

struct AVI_VFW_RIFF_LISTS
{
	AVI_VFW_RIFF_TYPES result;
	const unsigned* list;
	unsigned count;
};

#define _ARY_COUNT(ary) (sizeof(ary) / sizeof(ary[0]))
#define _LIST_ITEM_DECLARE(list) (list),_ARY_COUNT((list))
static const AVI_VFW_RIFF_LISTS kVFWFCCLIST[] = {
	{VFW_RIFF_H264,_LIST_ITEM_DECLARE(kRIFFH264FCC)},
	{VFW_RIFF_H263,_LIST_ITEM_DECLARE(kRIFFH263FCC)},
	{VFW_RIFF_MPEG4,_LIST_ITEM_DECLARE(kRIFFMPEG4FCC)},
	{VFW_RIFF_MPEG4V3,_LIST_ITEM_DECLARE(kRIFFMPEG4V3FCC)},
	{VFW_RIFF_MPEG4V2,_LIST_ITEM_DECLARE(kRIFFMPEG4V2FCC)},
	{VFW_RIFF_MPEG4V1,_LIST_ITEM_DECLARE(kRIFFMPEG4V1FCC)},
	{VFW_RIFF_MPG1V,_LIST_ITEM_DECLARE(kRIFFMPG1VFCC)},
	{VFW_RIFF_MPG2V,_LIST_ITEM_DECLARE(kRIFFMPG2VFCC)},
	{VFW_RIFF_MJPEG,_LIST_ITEM_DECLARE(kRIFFMJPEGFCC)},
	{VFW_RIFF_WMV1,_LIST_ITEM_DECLARE(kRIFFWMV1FCC)},
	{VFW_RIFF_WMV2,_LIST_ITEM_DECLARE(kRIFFWMV2FCC)},
	{VFW_RIFF_WMV3,_LIST_ITEM_DECLARE(kRIFFWMV3FCC)},
	{VFW_RIFF_VC1,_LIST_ITEM_DECLARE(kRIFFVC1FCC)},
	{VFW_RIFF_FFV1,_LIST_ITEM_DECLARE(kRIFFFFV1FCC)},
	{VFW_RIFF_FLV1,_LIST_ITEM_DECLARE(kRIFFFLV1FCC)},
	{VFW_RIFF_THEORA,_LIST_ITEM_DECLARE(kRIFFTHEORAFCC)},
	{VFW_RIFF_SNOW,_LIST_ITEM_DECLARE(kRIFFSNOWFCC)},
	{VFW_RIFF_PRORES,_LIST_ITEM_DECLARE(kRIFFPRORESFCC)},
	{VFW_RIFF_DIRAC,_LIST_ITEM_DECLARE(kRIFFDIRACFCC)},
	{VFW_RIFF_CAVS,_LIST_ITEM_DECLARE(kRIFFCAVSFCC)},
	{VFW_RIFF_AMV,_LIST_ITEM_DECLARE(kRIFFAMVFCC)}
};

AVI_VFW_RIFF_TYPES SearchVFWCodecIdList(unsigned id)
{
	for (auto list : kVFWFCCLIST)
	{
		for (unsigned i = 0;i < list.count;i++)
			if (list.list[i] == id)
				return list.result;
	}

	return AVI_VFW_RIFF_TYPES::VFW_RIFF_Others;
}

struct WAV_VFW_RIFF_LISTS
{
	WAV_VFW_RIFF_TYPES result;
	unsigned id;
};

static const WAV_VFW_RIFF_LISTS kVFWWAVLIST[] = {
	{VFW_WAV_PCM,0x1},
	{VFW_WAV_ADPCM,0x2},
	{VFW_WAV_FLOAT,0x03},
	{VFW_WAV_PCM_ALAW,0x06},
	{VFW_WAV_PCM_MULAW,0x07},
	{VFW_WAV_PCM_MULAW,0x6C75},
	{VFW_WAV_GSM_MS,0x31},
	{VFW_WAV_GSM_MS,0x32},
	{VFW_WAV_G723_1,0x42},
	{VFW_WAV_G723_1,0x111},
	{VFW_WAV_AMR_NB,0x38},
	{VFW_WAV_AMR_NB,0x57},
	{VFW_WAV_AMR_WB,0x58},
	{VFW_WAV_WMA1,0x160},
	{VFW_WAV_WMA2,0x161},
	{VFW_WAV_WMA3,0x162},
	{VFW_WAV_WMA_LOSSLESS,0x163},
	{VFW_WAV_MP2,0x50},
	{VFW_WAV_MP3,0x55},
	{VFW_WAV_AAC,0xFF},
	{VFW_WAV_AAC_ADTS,0x1600},
	{VFW_WAV_AAC_LATM,0x1602},
	{VFW_WAV_AAC,0x1610},
	{VFW_WAV_AC3,0x2000},
	{VFW_WAV_DTS,0x2001},
	{VFW_WAV_FLAC,0xF1AC},
	{VFW_WAV_SPEEX,0xA109}
};

WAV_VFW_RIFF_TYPES SearchVFWCodecIdList2(unsigned id)
{
	for (auto i : kVFWWAVLIST)
	{
		if (i.id == id)
			return i.result;
	}

	return WAV_VFW_RIFF_TYPES::VFW_WAV_Others;
}