//*****************************************************************************
// file        : lvgl2rtt.c
// LVGL module for rt-thread
//
// Change Logs:
// Date                 Author      Note
// 2020/09/05           Cheney      First draft version
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup lvgl
//! @{
//
//*****************************************************************************
#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

#include "lvgl.h"
#include "lv_port_disp.h"

static rt_thread_t lvgl_tid;
static rt_timer_t lvgl_tmr;

/**
 * \brief lvgl task handler thread entry
 * 
 * \param parameter: input parameter
 */
static void lvgl_task(void *parameter)
{
    while (true)
    {
        rt_thread_delay(10);
        lv_task_handler();
    }
}

/**
 * \brief lvgl tick
 * 
 * \param parameter: input parameter
 */
static void lvgl_tick(void *parameter)
{
    lv_tick_inc(10);
}

/**
 * \brief start lvgl schedule
 * 
 */
static void lvgl_schedule_start(void)
{
    lvgl_tid = rt_thread_create("lvgl_task", lvgl_task, RT_NULL, 4096, 20, 4);
    if (lvgl_tid != RT_NULL)
        rt_thread_startup(lvgl_tid);

    lvgl_tmr = rt_timer_create("lvgl_tmr", lvgl_tick, RT_NULL, 10, RT_TIMER_FLAG_PERIODIC);
    if (lvgl_tmr != RT_NULL)
        rt_timer_start(lvgl_tmr);
}

/**
 * \brief stop lvgl schedule
 * 
 */
static void lvgl_schedule_stop(void)
{
    if (lvgl_tid != RT_NULL)
        rt_thread_delete(lvgl_tid);

    if (lvgl_tmr != RT_NULL)
        rt_timer_delete(lvgl_tmr);
    
    lvgl_tid = RT_NULL;
    lvgl_tmr = RT_NULL;
}

/**
 * \brief lvgl2rtt init
 * 
 * \param lcd_dev_name: lcd device name
 */
void lvgl2rtt_init(const char *lcd_dev_name)
{
    lv_init();
    lv_port_disp_init(lcd_dev_name);
    lvgl_schedule_start();
}

/**
 * \brief lvgl2rtt deinit
 * 
 */
void lvgl2rtt_deinit(void)
{
    lvgl_schedule_stop();
    lv_port_disp_deinit();
}

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************