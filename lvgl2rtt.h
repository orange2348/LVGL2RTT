//*****************************************************************************
// file        : lvgl2rtt.h
// LVGL module for rt-thread
//
// Change Logs:
// Date                 Author      Note
// 2020/09/05           Cheney      First draft version
// 2020/09/12           Cheney      Add LVGL task lock interface. If the lv_xx
//                                  function is call in other thread, you should
//                                  lock the LVGL task first.
//
//*****************************************************************************
#ifndef __LVGL2RTT_H__
#define __LVGL2RTT_H__

//*****************************************************************************
//
//! \addtogroup lvgl
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

#include "lvgl/lvgl.h"

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************
void lvgl2rtt_init(const char *lcd_dev_name);
void lvgl2rtt_deinit(void);
void lvgl2rtt_task_lock(void);
void lvgl2rtt_task_unlock(void);

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************

#ifdef __cplusplus
}
#endif

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************
#endif //  __LVGL2RTT_H__