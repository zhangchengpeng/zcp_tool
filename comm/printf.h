#ifndef __PRINTF_H__
#define __PRINTF_H__

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "time_utils.h"


/*
格式：\033[显示方式;前景色;背景色m 
\e等同于\033 0m取消颜色设置 
*/
#define RED_PRINT_BEG     "\e[1;31m"
#define RED_PRINT_END     "\e[m"
#define GREEN_PRINT_BEG   "\e[1;32m"
#define GREEN_PRINT_END   "\e[m"
#define YELLOW_PRINT_BEG  "\e[1;33m"
#define YELLOW_PRINT_END  "\e[m"
#define BLUE_PRINT_BEG    "\e[1;34m"
#define BLUE_PRINT_END    "\e[m"

/*
gcc支持的做法，支持arg可变参传入
#define PRINTF_DEBUG(format, args...) \
		printf("[DEBUG] [%s:%d %s()] " format"\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, ##args)
#define PRINTF_DEBUG(format, args...) \
		printf("[DEBUG] [%s:%d %s()] " format"\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, ##args)
*/

#define PRINTF_DEBUG(format, ...) \
{ \
	string time_str; \
	int ret = get_time_now(time_str); \
	if (ret == 0) \
	{ \
		printf("[%s] " GREEN_PRINT_BEG "[DEBUG]" GREEN_PRINT_END " [%s:%d %s()] " format"\n", time_str.c_str(), __FILE__, __LINE__, \
		__FUNCTION__, ##__VA_ARGS__); \
	} \
	else \
	{ \
		printf(GREEN_PRINT_BEG "[DEBUG]" GREEN_PRINT_END " [%s:%d %s()] " format"\n", __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__); \
	} \
	fflush(stdout); \
}

#define PRINTF_ERROR(format, ...) \
{ \
	string time_str; \
	int ret = get_time_now(time_str); \
	if (ret == 0) \
	{ \
		printf("[%s] " RED_PRINT_BEG "[ERROR]" RED_PRINT_END " [%s:%d %s()] [errno:%d err:%s] " format"\n", time_str.c_str(), __FILE__, __LINE__, \
		__FUNCTION__, errno, strerror(errno), ##__VA_ARGS__); \
	} \
	else \
	{ \
		printf(RED_PRINT_BEG "[ERROR]" RED_PRINT_END " [%s:%d %s()] [errno:%d err:%s] " format"\n", __FILE__, __LINE__, \
		__FUNCTION__, errno, strerror(errno), ##__VA_ARGS__); \
	} \
	fflush(stdout); \
}

#endif
