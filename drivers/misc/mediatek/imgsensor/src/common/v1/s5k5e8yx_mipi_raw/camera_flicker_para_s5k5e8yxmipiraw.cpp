//[Sensor]
//name = s5k5e8yxmipiraw
//bin_ratio = 1,2
//
//[Preview]
//read_freq = 168000000
//pixel_line = 5200
//column_length = 947
//
//[Capture]
//read_freq = 169000000
//pixel_line = 2856
//column_length = 1919
//
//[Video]
//read_freq = 169000000
//pixel_line = 2856
//column_length = 1919
//
//[Video1]
//read_freq = 168000000
//pixel_line = 2816
//column_length = 455
//
//[Video2]
//read_freq = 168000000
//pixel_line = 2896
//column_length = 695
//
#define LOG_TAG "s5k5e8yxmipiraw"

#include <utils/Log.h>
#include <fcntl.h>
#include <math.h>
#include "camera_custom_nvram.h"
#include "camera_custom_sensor.h"
#include "image_sensor.h"
#include "kd_imgsensor_define.h"
#include "camera_AE_PLineTable_s5k5e8yxmipiraw.h"
#include "camera_info_s5k5e8yxmipiraw.h"
#include "camera_custom_AEPlinetable.h"
#include "camera_custom_flicker_para.h"
#include <cutils/log.h>


extern "C" fptrFlicker getFlickerParaFunc(MUINT32 sensorType)
{
    if(sensorType==0)
        return NSFeature::RAWSensorInfo<SENSOR_ID>::getFlickerPara;
    else
        return NSFeature::YUVSensorInfo<SENSOR_ID>::getNullFlickerPara;
}

static void get_flicker_para_by_Preview_Bin1(FLICKER_CUST_PARA* para)
{
    int freq[9] = {80, 90, 100, 120, 130, 140, 170, 210, 230};
    FLICKER_CUST_STATISTICS EV50_L50 = {-194, 4721, 381, -766};
    FLICKER_CUST_STATISTICS EV50_L60 = {1029, 452, 844, -415};
    FLICKER_CUST_STATISTICS EV60_L50 = {1227, 476, 1256, -489};
    FLICKER_CUST_STATISTICS EV60_L60 = {-162, 2898, 247, -642};
    for (int i = 0; i < 9; i++)
        para->flickerFreq[i] = freq[i];
    para->flickerGradThreshold = 1706;
    para->flickerSearchRange = 16;
    para->minPastFrames = 3;
    para->maxPastFrames = 7;
    para->EV50_L50 = EV50_L50;
    para->EV50_L60 = EV50_L60;
    para->EV60_L50 = EV60_L50;
    para->EV60_L60 = EV60_L60;
    para->EV50_thresholds[0] = -30;
    para->EV50_thresholds[1] = 12;
    para->EV60_thresholds[0] = -30;
    para->EV60_thresholds[1] = 12;
    para->freq_feature_index[0] = 3;
    para->freq_feature_index[1] = 2;
}

static void get_flicker_para_by_Preview_Bin2(FLICKER_CUST_PARA* para)
{
    int freq[9] = {80, 90, 100, 120, 130, 140, 170, 210, 230};
    FLICKER_CUST_STATISTICS EV50_L50 = {-194, 4721, 381, -766};
    FLICKER_CUST_STATISTICS EV50_L60 = {1017, 457, 853, -418};
    FLICKER_CUST_STATISTICS EV60_L50 = {1213, 481, 1270, -492};
    FLICKER_CUST_STATISTICS EV60_L60 = {-162, 2898, 247, -642};
    for (int i = 0; i < 9; i++)
        para->flickerFreq[i] = freq[i];
    para->flickerGradThreshold = 2521;
    para->flickerSearchRange = 4;
    para->minPastFrames = 3;
    para->maxPastFrames = 7;
    para->EV50_L50 = EV50_L50;
    para->EV50_L60 = EV50_L60;
    para->EV60_L50 = EV60_L50;
    para->EV60_L60 = EV60_L60;
    para->EV50_thresholds[0] = -30;
    para->EV50_thresholds[1] = 12;
    para->EV60_thresholds[0] = -30;
    para->EV60_thresholds[1] = 12;
    para->freq_feature_index[0] = 3;
    para->freq_feature_index[1] = 2;
}

static void get_flicker_para_by_Capture_Bin1(FLICKER_CUST_PARA* para)
{
    int freq[9] = {70, 80, 100, 110, 120, 140, 170, 210, 230};
    FLICKER_CUST_STATISTICS EV50_L50 = {-194, 4721, 381, -766};
    FLICKER_CUST_STATISTICS EV50_L60 = {1257, 370, 691, -364};
    FLICKER_CUST_STATISTICS EV60_L50 = {1498, 389, 1028, -438};
    FLICKER_CUST_STATISTICS EV60_L60 = {-162, 2898, 247, -642};
    for (int i = 0; i < 9; i++)
        para->flickerFreq[i] = freq[i];
    para->flickerGradThreshold = 1430;
    para->flickerSearchRange = 32;
    para->minPastFrames = 3;
    para->maxPastFrames = 7;
    para->EV50_L50 = EV50_L50;
    para->EV50_L60 = EV50_L60;
    para->EV60_L50 = EV60_L50;
    para->EV60_L60 = EV60_L60;
    para->EV50_thresholds[0] = -30;
    para->EV50_thresholds[1] = 12;
    para->EV60_thresholds[0] = -30;
    para->EV60_thresholds[1] = 12;
    para->freq_feature_index[0] = 4;
    para->freq_feature_index[1] = 2;
}

static void get_flicker_para_by_Capture_Bin2(FLICKER_CUST_PARA* para)
{
    int freq[9] = {70, 80, 90, 100, 120, 130, 140, 160, 170};
    FLICKER_CUST_STATISTICS EV50_L50 = {-194, 4721, 381, -766};
    FLICKER_CUST_STATISTICS EV50_L60 = {1189, 391, 730, -378};
    FLICKER_CUST_STATISTICS EV60_L50 = {1418, 411, 1087, -452};
    FLICKER_CUST_STATISTICS EV60_L60 = {-162, 2898, 247, -642};
    for (int i = 0; i < 9; i++)
        para->flickerFreq[i] = freq[i];
    para->flickerGradThreshold = 1768;
    para->flickerSearchRange = 16;
    para->minPastFrames = 3;
    para->maxPastFrames = 7;
    para->EV50_L50 = EV50_L50;
    para->EV50_L60 = EV50_L60;
    para->EV60_L50 = EV60_L50;
    para->EV60_L60 = EV60_L60;
    para->EV50_thresholds[0] = -30;
    para->EV50_thresholds[1] = 12;
    para->EV60_thresholds[0] = -30;
    para->EV60_thresholds[1] = 12;
    para->freq_feature_index[0] = 4;
    para->freq_feature_index[1] = 3;
}

static void get_flicker_para_by_Video_Bin1(FLICKER_CUST_PARA* para)
{
    int freq[9] = {70, 80, 100, 110, 120, 140, 170, 210, 230};
    FLICKER_CUST_STATISTICS EV50_L50 = {-194, 4721, 381, -766};
    FLICKER_CUST_STATISTICS EV50_L60 = {1257, 370, 691, -364};
    FLICKER_CUST_STATISTICS EV60_L50 = {1498, 389, 1028, -438};
    FLICKER_CUST_STATISTICS EV60_L60 = {-162, 2898, 247, -642};
    for (int i = 0; i < 9; i++)
        para->flickerFreq[i] = freq[i];
    para->flickerGradThreshold = 1430;
    para->flickerSearchRange = 32;
    para->minPastFrames = 3;
    para->maxPastFrames = 7;
    para->EV50_L50 = EV50_L50;
    para->EV50_L60 = EV50_L60;
    para->EV60_L50 = EV60_L50;
    para->EV60_L60 = EV60_L60;
    para->EV50_thresholds[0] = -30;
    para->EV50_thresholds[1] = 12;
    para->EV60_thresholds[0] = -30;
    para->EV60_thresholds[1] = 12;
    para->freq_feature_index[0] = 4;
    para->freq_feature_index[1] = 2;
}

static void get_flicker_para_by_Video_Bin2(FLICKER_CUST_PARA* para)
{
    int freq[9] = {70, 80, 90, 100, 120, 130, 140, 160, 170};
    FLICKER_CUST_STATISTICS EV50_L50 = {-194, 4721, 381, -766};
    FLICKER_CUST_STATISTICS EV50_L60 = {1189, 391, 730, -378};
    FLICKER_CUST_STATISTICS EV60_L50 = {1418, 411, 1087, -452};
    FLICKER_CUST_STATISTICS EV60_L60 = {-162, 2898, 247, -642};
    for (int i = 0; i < 9; i++)
        para->flickerFreq[i] = freq[i];
    para->flickerGradThreshold = 1768;
    para->flickerSearchRange = 16;
    para->minPastFrames = 3;
    para->maxPastFrames = 7;
    para->EV50_L50 = EV50_L50;
    para->EV50_L60 = EV50_L60;
    para->EV60_L50 = EV60_L50;
    para->EV60_L60 = EV60_L60;
    para->EV50_thresholds[0] = -30;
    para->EV50_thresholds[1] = 12;
    para->EV60_thresholds[0] = -30;
    para->EV60_thresholds[1] = 12;
    para->freq_feature_index[0] = 4;
    para->freq_feature_index[1] = 3;
}

static void get_flicker_para_by_Video1_Bin1(FLICKER_CUST_PARA* para)
{
    int freq[9] = {70, 100, 120, 140, 160, 170, 190, 210, 230};
    FLICKER_CUST_STATISTICS EV50_L50 = {-194, 4721, 381, -766};
    FLICKER_CUST_STATISTICS EV50_L60 = {283, 1639, 3062, -745};
    FLICKER_CUST_STATISTICS EV60_L50 = {338, 1726, 4558, -819};
    FLICKER_CUST_STATISTICS EV60_L60 = {-162, 2898, 247, -642};
    for (int i = 0; i < 9; i++)
        para->flickerFreq[i] = freq[i];
    para->flickerGradThreshold = 1474;
    para->flickerSearchRange = 4;
    para->minPastFrames = 3;
    para->maxPastFrames = 7;
    para->EV50_L50 = EV50_L50;
    para->EV50_L60 = EV50_L60;
    para->EV60_L50 = EV60_L50;
    para->EV60_L60 = EV60_L60;
    para->EV50_thresholds[0] = -30;
    para->EV50_thresholds[1] = 12;
    para->EV60_thresholds[0] = -30;
    para->EV60_thresholds[1] = 12;
    para->freq_feature_index[0] = 2;
    para->freq_feature_index[1] = 1;
}

static void get_flicker_para_by_Video1_Bin2(FLICKER_CUST_PARA* para)
{
    int freq[9] = {70, 100, 120, 140, 160, 170, 190, 210, 230};
    FLICKER_CUST_STATISTICS EV50_L50 = {-194, 4721, 381, -766};
    FLICKER_CUST_STATISTICS EV50_L60 = {234, 1982, 3702, -793};
    FLICKER_CUST_STATISTICS EV60_L50 = {279, 2088, 5511, -868};
    FLICKER_CUST_STATISTICS EV60_L60 = {-162, 2898, 247, -642};
    for (int i = 0; i < 9; i++)
        para->flickerFreq[i] = freq[i];
    para->flickerGradThreshold = 1813;
    para->flickerSearchRange = 1;
    para->minPastFrames = 3;
    para->maxPastFrames = 7;
    para->EV50_L50 = EV50_L50;
    para->EV50_L60 = EV50_L60;
    para->EV60_L50 = EV60_L50;
    para->EV60_L60 = EV60_L60;
    para->EV50_thresholds[0] = -30;
    para->EV50_thresholds[1] = 12;
    para->EV60_thresholds[0] = -30;
    para->EV60_thresholds[1] = 12;
    para->freq_feature_index[0] = 2;
    para->freq_feature_index[1] = 1;
}

static void get_flicker_para_by_Video2_Bin1(FLICKER_CUST_PARA* para)
{
    int freq[9] = {70, 100, 120, 140, 160, 170, 190, 210, 230};
    FLICKER_CUST_STATISTICS EV50_L50 = {-194, 4721, 381, -766};
    FLICKER_CUST_STATISTICS EV50_L60 = {546, 851, 1590, -577};
    FLICKER_CUST_STATISTICS EV60_L50 = {651, 897, 2367, -651};
    FLICKER_CUST_STATISTICS EV60_L60 = {-162, 2898, 247, -642};
    for (int i = 0; i < 9; i++)
        para->flickerFreq[i] = freq[i];
    para->flickerGradThreshold = 1462;
    para->flickerSearchRange = 8;
    para->minPastFrames = 3;
    para->maxPastFrames = 7;
    para->EV50_L50 = EV50_L50;
    para->EV50_L60 = EV50_L60;
    para->EV60_L50 = EV60_L50;
    para->EV60_L60 = EV60_L60;
    para->EV50_thresholds[0] = -30;
    para->EV50_thresholds[1] = 12;
    para->EV60_thresholds[0] = -30;
    para->EV60_thresholds[1] = 12;
    para->freq_feature_index[0] = 2;
    para->freq_feature_index[1] = 1;
}

static void get_flicker_para_by_Video2_Bin2(FLICKER_CUST_PARA* para)
{
    int freq[9] = {70, 100, 120, 140, 160, 170, 190, 210, 230};
    FLICKER_CUST_STATISTICS EV50_L50 = {-194, 4721, 381, -766};
    FLICKER_CUST_STATISTICS EV50_L60 = {504, 922, 1722, -597};
    FLICKER_CUST_STATISTICS EV60_L50 = {601, 971, 2563, -672};
    FLICKER_CUST_STATISTICS EV60_L60 = {-162, 2898, 247, -642};
    for (int i = 0; i < 9; i++)
        para->flickerFreq[i] = freq[i];
    para->flickerGradThreshold = 1825;
    para->flickerSearchRange = 4;
    para->minPastFrames = 3;
    para->maxPastFrames = 7;
    para->EV50_L50 = EV50_L50;
    para->EV50_L60 = EV50_L60;
    para->EV60_L50 = EV60_L50;
    para->EV60_L60 = EV60_L60;
    para->EV50_thresholds[0] = -30;
    para->EV50_thresholds[1] = 12;
    para->EV60_thresholds[0] = -30;
    para->EV60_thresholds[1] = 12;
    para->freq_feature_index[0] = 2;
    para->freq_feature_index[1] = 1;
}

// using [Preview_Bin1] parameters for [Custom1_Bin1]
static void get_flicker_para_by_Custom1_Bin1(FLICKER_CUST_PARA* para)
{
    int freq[9] = {80, 90, 100, 120, 130, 140, 170, 210, 230};
    FLICKER_CUST_STATISTICS EV50_L50 = {-194, 4721, 381, -766};
    FLICKER_CUST_STATISTICS EV50_L60 = {1029, 452, 844, -415};
    FLICKER_CUST_STATISTICS EV60_L50 = {1227, 476, 1256, -489};
    FLICKER_CUST_STATISTICS EV60_L60 = {-162, 2898, 247, -642};
    for (int i = 0; i < 9; i++)
        para->flickerFreq[i] = freq[i];
    para->flickerGradThreshold = 1706;
    para->flickerSearchRange = 16;
    para->minPastFrames = 3;
    para->maxPastFrames = 7;
    para->EV50_L50 = EV50_L50;
    para->EV50_L60 = EV50_L60;
    para->EV60_L50 = EV60_L50;
    para->EV60_L60 = EV60_L60;
    para->EV50_thresholds[0] = -30;
    para->EV50_thresholds[1] = 12;
    para->EV60_thresholds[0] = -30;
    para->EV60_thresholds[1] = 12;
    para->freq_feature_index[0] = 3;
    para->freq_feature_index[1] = 2;
}

// using [Preview_Bin1] parameters for [Custom1_Bin2]
static void get_flicker_para_by_Custom1_Bin2(FLICKER_CUST_PARA* para)
{
    int freq[9] = {80, 90, 100, 120, 130, 140, 170, 210, 230};
    FLICKER_CUST_STATISTICS EV50_L50 = {-194, 4721, 381, -766};
    FLICKER_CUST_STATISTICS EV50_L60 = {1029, 452, 844, -415};
    FLICKER_CUST_STATISTICS EV60_L50 = {1227, 476, 1256, -489};
    FLICKER_CUST_STATISTICS EV60_L60 = {-162, 2898, 247, -642};
    for (int i = 0; i < 9; i++)
        para->flickerFreq[i] = freq[i];
    para->flickerGradThreshold = 1706;
    para->flickerSearchRange = 16;
    para->minPastFrames = 3;
    para->maxPastFrames = 7;
    para->EV50_L50 = EV50_L50;
    para->EV50_L60 = EV50_L60;
    para->EV60_L50 = EV60_L50;
    para->EV60_L60 = EV60_L60;
    para->EV50_thresholds[0] = -30;
    para->EV50_thresholds[1] = 12;
    para->EV60_thresholds[0] = -30;
    para->EV60_thresholds[1] = 12;
    para->freq_feature_index[0] = 3;
    para->freq_feature_index[1] = 2;
}

// using [Preview_Bin1] parameters for [Custom2_Bin1]
static void get_flicker_para_by_Custom2_Bin1(FLICKER_CUST_PARA* para)
{
    int freq[9] = {80, 90, 100, 120, 130, 140, 170, 210, 230};
    FLICKER_CUST_STATISTICS EV50_L50 = {-194, 4721, 381, -766};
    FLICKER_CUST_STATISTICS EV50_L60 = {1029, 452, 844, -415};
    FLICKER_CUST_STATISTICS EV60_L50 = {1227, 476, 1256, -489};
    FLICKER_CUST_STATISTICS EV60_L60 = {-162, 2898, 247, -642};
    for (int i = 0; i < 9; i++)
        para->flickerFreq[i] = freq[i];
    para->flickerGradThreshold = 1706;
    para->flickerSearchRange = 16;
    para->minPastFrames = 3;
    para->maxPastFrames = 7;
    para->EV50_L50 = EV50_L50;
    para->EV50_L60 = EV50_L60;
    para->EV60_L50 = EV60_L50;
    para->EV60_L60 = EV60_L60;
    para->EV50_thresholds[0] = -30;
    para->EV50_thresholds[1] = 12;
    para->EV60_thresholds[0] = -30;
    para->EV60_thresholds[1] = 12;
    para->freq_feature_index[0] = 3;
    para->freq_feature_index[1] = 2;
}

// using [Preview_Bin1] parameters for [Custom2_Bin2]
static void get_flicker_para_by_Custom2_Bin2(FLICKER_CUST_PARA* para)
{
    int freq[9] = {80, 90, 100, 120, 130, 140, 170, 210, 230};
    FLICKER_CUST_STATISTICS EV50_L50 = {-194, 4721, 381, -766};
    FLICKER_CUST_STATISTICS EV50_L60 = {1029, 452, 844, -415};
    FLICKER_CUST_STATISTICS EV60_L50 = {1227, 476, 1256, -489};
    FLICKER_CUST_STATISTICS EV60_L60 = {-162, 2898, 247, -642};
    for (int i = 0; i < 9; i++)
        para->flickerFreq[i] = freq[i];
    para->flickerGradThreshold = 1706;
    para->flickerSearchRange = 16;
    para->minPastFrames = 3;
    para->maxPastFrames = 7;
    para->EV50_L50 = EV50_L50;
    para->EV50_L60 = EV50_L60;
    para->EV60_L50 = EV60_L50;
    para->EV60_L60 = EV60_L60;
    para->EV50_thresholds[0] = -30;
    para->EV50_thresholds[1] = 12;
    para->EV60_thresholds[0] = -30;
    para->EV60_thresholds[1] = 12;
    para->freq_feature_index[0] = 3;
    para->freq_feature_index[1] = 2;
}

// using [Preview_Bin1] parameters for [Custom3_Bin1]
static void get_flicker_para_by_Custom3_Bin1(FLICKER_CUST_PARA* para)
{
    int freq[9] = {80, 90, 100, 120, 130, 140, 170, 210, 230};
    FLICKER_CUST_STATISTICS EV50_L50 = {-194, 4721, 381, -766};
    FLICKER_CUST_STATISTICS EV50_L60 = {1029, 452, 844, -415};
    FLICKER_CUST_STATISTICS EV60_L50 = {1227, 476, 1256, -489};
    FLICKER_CUST_STATISTICS EV60_L60 = {-162, 2898, 247, -642};
    for (int i = 0; i < 9; i++)
        para->flickerFreq[i] = freq[i];
    para->flickerGradThreshold = 1706;
    para->flickerSearchRange = 16;
    para->minPastFrames = 3;
    para->maxPastFrames = 7;
    para->EV50_L50 = EV50_L50;
    para->EV50_L60 = EV50_L60;
    para->EV60_L50 = EV60_L50;
    para->EV60_L60 = EV60_L60;
    para->EV50_thresholds[0] = -30;
    para->EV50_thresholds[1] = 12;
    para->EV60_thresholds[0] = -30;
    para->EV60_thresholds[1] = 12;
    para->freq_feature_index[0] = 3;
    para->freq_feature_index[1] = 2;
}

// using [Preview_Bin1] parameters for [Custom3_Bin2]
static void get_flicker_para_by_Custom3_Bin2(FLICKER_CUST_PARA* para)
{
    int freq[9] = {80, 90, 100, 120, 130, 140, 170, 210, 230};
    FLICKER_CUST_STATISTICS EV50_L50 = {-194, 4721, 381, -766};
    FLICKER_CUST_STATISTICS EV50_L60 = {1029, 452, 844, -415};
    FLICKER_CUST_STATISTICS EV60_L50 = {1227, 476, 1256, -489};
    FLICKER_CUST_STATISTICS EV60_L60 = {-162, 2898, 247, -642};
    for (int i = 0; i < 9; i++)
        para->flickerFreq[i] = freq[i];
    para->flickerGradThreshold = 1706;
    para->flickerSearchRange = 16;
    para->minPastFrames = 3;
    para->maxPastFrames = 7;
    para->EV50_L50 = EV50_L50;
    para->EV50_L60 = EV50_L60;
    para->EV60_L50 = EV60_L50;
    para->EV60_L60 = EV60_L60;
    para->EV50_thresholds[0] = -30;
    para->EV50_thresholds[1] = 12;
    para->EV60_thresholds[0] = -30;
    para->EV60_thresholds[1] = 12;
    para->freq_feature_index[0] = 3;
    para->freq_feature_index[1] = 2;
}

// using [Preview_Bin1] parameters for [Custom4_Bin1]
static void get_flicker_para_by_Custom4_Bin1(FLICKER_CUST_PARA* para)
{
    int freq[9] = {80, 90, 100, 120, 130, 140, 170, 210, 230};
    FLICKER_CUST_STATISTICS EV50_L50 = {-194, 4721, 381, -766};
    FLICKER_CUST_STATISTICS EV50_L60 = {1029, 452, 844, -415};
    FLICKER_CUST_STATISTICS EV60_L50 = {1227, 476, 1256, -489};
    FLICKER_CUST_STATISTICS EV60_L60 = {-162, 2898, 247, -642};
    for (int i = 0; i < 9; i++)
        para->flickerFreq[i] = freq[i];
    para->flickerGradThreshold = 1706;
    para->flickerSearchRange = 16;
    para->minPastFrames = 3;
    para->maxPastFrames = 7;
    para->EV50_L50 = EV50_L50;
    para->EV50_L60 = EV50_L60;
    para->EV60_L50 = EV60_L50;
    para->EV60_L60 = EV60_L60;
    para->EV50_thresholds[0] = -30;
    para->EV50_thresholds[1] = 12;
    para->EV60_thresholds[0] = -30;
    para->EV60_thresholds[1] = 12;
    para->freq_feature_index[0] = 3;
    para->freq_feature_index[1] = 2;
}

// using [Preview_Bin1] parameters for [Custom4_Bin2]
static void get_flicker_para_by_Custom4_Bin2(FLICKER_CUST_PARA* para)
{
    int freq[9] = {80, 90, 100, 120, 130, 140, 170, 210, 230};
    FLICKER_CUST_STATISTICS EV50_L50 = {-194, 4721, 381, -766};
    FLICKER_CUST_STATISTICS EV50_L60 = {1029, 452, 844, -415};
    FLICKER_CUST_STATISTICS EV60_L50 = {1227, 476, 1256, -489};
    FLICKER_CUST_STATISTICS EV60_L60 = {-162, 2898, 247, -642};
    for (int i = 0; i < 9; i++)
        para->flickerFreq[i] = freq[i];
    para->flickerGradThreshold = 1706;
    para->flickerSearchRange = 16;
    para->minPastFrames = 3;
    para->maxPastFrames = 7;
    para->EV50_L50 = EV50_L50;
    para->EV50_L60 = EV50_L60;
    para->EV60_L50 = EV60_L50;
    para->EV60_L60 = EV60_L60;
    para->EV50_thresholds[0] = -30;
    para->EV50_thresholds[1] = 12;
    para->EV60_thresholds[0] = -30;
    para->EV60_thresholds[1] = 12;
    para->freq_feature_index[0] = 3;
    para->freq_feature_index[1] = 2;
}

// using [Preview_Bin1] parameters for [Custom5_Bin1]
static void get_flicker_para_by_Custom5_Bin1(FLICKER_CUST_PARA* para)
{
    int freq[9] = {80, 90, 100, 120, 130, 140, 170, 210, 230};
    FLICKER_CUST_STATISTICS EV50_L50 = {-194, 4721, 381, -766};
    FLICKER_CUST_STATISTICS EV50_L60 = {1029, 452, 844, -415};
    FLICKER_CUST_STATISTICS EV60_L50 = {1227, 476, 1256, -489};
    FLICKER_CUST_STATISTICS EV60_L60 = {-162, 2898, 247, -642};
    for (int i = 0; i < 9; i++)
        para->flickerFreq[i] = freq[i];
    para->flickerGradThreshold = 1706;
    para->flickerSearchRange = 16;
    para->minPastFrames = 3;
    para->maxPastFrames = 7;
    para->EV50_L50 = EV50_L50;
    para->EV50_L60 = EV50_L60;
    para->EV60_L50 = EV60_L50;
    para->EV60_L60 = EV60_L60;
    para->EV50_thresholds[0] = -30;
    para->EV50_thresholds[1] = 12;
    para->EV60_thresholds[0] = -30;
    para->EV60_thresholds[1] = 12;
    para->freq_feature_index[0] = 3;
    para->freq_feature_index[1] = 2;
}

// using [Preview_Bin1] parameters for [Custom5_Bin2]
static void get_flicker_para_by_Custom5_Bin2(FLICKER_CUST_PARA* para)
{
    int freq[9] = {80, 90, 100, 120, 130, 140, 170, 210, 230};
    FLICKER_CUST_STATISTICS EV50_L50 = {-194, 4721, 381, -766};
    FLICKER_CUST_STATISTICS EV50_L60 = {1029, 452, 844, -415};
    FLICKER_CUST_STATISTICS EV60_L50 = {1227, 476, 1256, -489};
    FLICKER_CUST_STATISTICS EV60_L60 = {-162, 2898, 247, -642};
    for (int i = 0; i < 9; i++)
        para->flickerFreq[i] = freq[i];
    para->flickerGradThreshold = 1706;
    para->flickerSearchRange = 16;
    para->minPastFrames = 3;
    para->maxPastFrames = 7;
    para->EV50_L50 = EV50_L50;
    para->EV50_L60 = EV50_L60;
    para->EV60_L50 = EV60_L50;
    para->EV60_L60 = EV60_L60;
    para->EV50_thresholds[0] = -30;
    para->EV50_thresholds[1] = 12;
    para->EV60_thresholds[0] = -30;
    para->EV60_thresholds[1] = 12;
    para->freq_feature_index[0] = 3;
    para->freq_feature_index[1] = 2;
}


typedef NSFeature::RAWSensorInfo<SENSOR_ID> SensorInfoSingleton_T;
namespace NSFeature {
template <> UINT32 SensorInfoSingleton_T::
impGetFlickerPara(MINT32 sensorMode, MINT32 binRatio, MVOID* const pDataBuf) const
{
    ALOGD("impGetFlickerPara(): mode(%d), binRatio(%d).", sensorMode, binRatio);

    FLICKER_CUST_PARA* para;
    para = (FLICKER_CUST_PARA *)pDataBuf;

    if (sensorMode == e_sensorModePreview && binRatio == 1)
        get_flicker_para_by_Preview_Bin1(para);
    else if (sensorMode == e_sensorModePreview && binRatio == 2)
        get_flicker_para_by_Preview_Bin2(para);
    else if (sensorMode == e_sensorModeCapture && binRatio == 1)
        get_flicker_para_by_Capture_Bin1(para);
    else if (sensorMode == e_sensorModeCapture && binRatio == 2)
        get_flicker_para_by_Capture_Bin2(para);
    else if (sensorMode == e_sensorModeVideo && binRatio == 1)
        get_flicker_para_by_Video_Bin1(para);
    else if (sensorMode == e_sensorModeVideo && binRatio == 2)
        get_flicker_para_by_Video_Bin2(para);
    else if (sensorMode == e_sensorModeVideo1 && binRatio == 1)
        get_flicker_para_by_Video1_Bin1(para);
    else if (sensorMode == e_sensorModeVideo1 && binRatio == 2)
        get_flicker_para_by_Video1_Bin2(para);
    else if (sensorMode == e_sensorModeVideo2 && binRatio == 1)
        get_flicker_para_by_Video2_Bin1(para);
    else if (sensorMode == e_sensorModeVideo2 && binRatio == 2)
        get_flicker_para_by_Video2_Bin2(para);
    else if (sensorMode == e_sensorModeCustom1 && binRatio == 1)
        get_flicker_para_by_Custom1_Bin1(para);
    else if (sensorMode == e_sensorModeCustom1 && binRatio == 2)
        get_flicker_para_by_Custom1_Bin2(para);
    else if (sensorMode == e_sensorModeCustom2 && binRatio == 1)
        get_flicker_para_by_Custom2_Bin1(para);
    else if (sensorMode == e_sensorModeCustom2 && binRatio == 2)
        get_flicker_para_by_Custom2_Bin2(para);
    else if (sensorMode == e_sensorModeCustom3 && binRatio == 1)
        get_flicker_para_by_Custom3_Bin1(para);
    else if (sensorMode == e_sensorModeCustom3 && binRatio == 2)
        get_flicker_para_by_Custom3_Bin2(para);
    else if (sensorMode == e_sensorModeCustom4 && binRatio == 1)
        get_flicker_para_by_Custom4_Bin1(para);
    else if (sensorMode == e_sensorModeCustom4 && binRatio == 2)
        get_flicker_para_by_Custom4_Bin2(para);
    else if (sensorMode == e_sensorModeCustom5 && binRatio == 1)
        get_flicker_para_by_Custom5_Bin1(para);
    else if (sensorMode == e_sensorModeCustom5 && binRatio == 2)
        get_flicker_para_by_Custom5_Bin2(para);

    else {
        ALOGD("impGetFlickerPara(): failed to find prameters.");
        return -1;
    }

    return 0;
}
}
