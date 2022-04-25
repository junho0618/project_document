// --------------------------------------------------------------------------
// --------------------------------------------------------------------------
//                                                               Confidential
//                                SK Hynix Co
//
//           Copyright (c) 2020 SKHynix Limited All rights reserved
//
// Project  : ToF(Time of Flight) library
// Filename : skhynix_tof_lib.h
//
// copyright..
// --------------------------------------------------------------------------
// --------------------------------------------------------------------------

#ifndef __SKHYNIX_TOF_LIB_H__
#define __SKHYNIX_TOF_LIB_H__

#include <stdint.h>

#define D_OK				(0)			// Ok value
#define D_ERR_UNKNOWN		(1 << 0)	// Undefined error
#define D_ERR_WIDTH			(1 << 1)	// Invalid width (under 0)
#define D_ERR_HEIGHT		(1 << 2)	// Invalid height (under 0)
#define D_ERR_ENABLE		(1 << 3)	// Invalid enable (under 0)
#define D_ERR_PACKED_BUFFER	(1 << 4)	// Source buffer allocation failed (NULL)
#define D_ERR_SRC_BUFFER	(1 << 5)	// Source buffer allocation failed (NULL)
#define D_ERR_WORK_BUFFER	(1 << 6)	// Work buffer allocation failed (NULL)
#define D_ERR_D_DST_BUFFER	(1 << 7)	// Destination buffer allocation failed (NULL)
#define D_ERR_PC_DST_BUFFER	(1 << 8)	// Destination buffer allocation failed (NULL)
#define D_ERR_EDL_BUFFER	(1 << 9)	// Embedded data line buffer allocation failed (NULL)
#define D_ERR_CAL_BUFFER	(1 << 10)	// Calibration data buffer allocation failed (NULL)

typedef struct _tof_ver_t
{
	int32_t			major;				// if the main algorithm is changed, MajorVersion number should be changed
	int32_t			minor1st;			// if the functions is modified or added, Minor1stVersion number should be changed
	int32_t			minor2nd;			// if the wrong word or variable name is modified, Minor2ndVersion number should be changed
} tof_ver_t;

typedef struct _point_cloud_t
{
	float			x;
	float			y;
	float			z;
} point_cloud_t;

typedef struct _tof_proc_t
{
	int32_t			width;
	int32_t			height;
	int32_t			enable;
	float			cur_vcsel_temp;
	float			cur_sensor_temp;
	int32_t			int_time_current_hex;
	int32_t			*int_time_output_hex;

	uint16_t		*input;
	uint16_t		*input_packed;
	uint16_t		*edl_input;
	uint16_t		*work;
	uint16_t		*output_d;
	point_cloud_t	*output_pc;
} tof_proc_t;

#ifdef __cplusplus
extern "C" {
#endif	// #ifdef __cplusplus

#ifdef TOF_EXPORTS

#if defined(__GNUC__)
#define EXT_TOF
#elif defined(_DLL)
#define EXT_TOF __declspec(dllexport)
#else
#define EXT_TOF
#endif

#else	// #ifdef TOF_EXPORTS

#if defined(__GNUC__)
#define EXT_TOF __attribute__ ((visibility("default")))
#elif defined(_DLL)
#define EXT_TOF __declspec(dllimport)
#else
#define EXT_TOF extern
#endif

#endif	// #ifdef TOF_EXPORTS

EXT_TOF tof_ver_t tof_ver(void);
EXT_TOF int32_t tof_init(uint16_t *_cal_data, uint16_t *work, int32_t width_max, int32_t height_max);
EXT_TOF int32_t tof_proc(tof_proc_t *info);
EXT_TOF void tof_deinit(void);

#ifdef __cplusplus
}
#endif	// #ifdef __cplusplus

#endif // #ifndef __SKHYNIX_TOF_LIB_H__
