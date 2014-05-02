#ifndef _LOGGER_H_
#define _LOGGER_H_

#define LOG_DEBUG(format, ...) printf("[%s:%d] " format "\n", __FUNCTION__, __LINE__, ##__VA_ARGS__);

#endif