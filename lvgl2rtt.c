//*****************************************************************************
// file        : lvgl2rtt.c
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

static rt_thread_t lvgl_tid = RT_NULL;
static rt_timer_t lvgl_tmr = RT_NULL;
static rt_mutex_t lvgl_mutex = RT_NULL;

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

        rt_mutex_take(lvgl_mutex, RT_WAITING_FOREVER);
        lv_task_handler();
        rt_mutex_release(lvgl_mutex);
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
    lvgl_tid = rt_thread_create("lvgl_task", lvgl_task, RT_NULL, 3072, 20, 4);
    if (lvgl_tid != RT_NULL)
        rt_thread_startup(lvgl_tid);

    lvgl_tmr = rt_timer_create("lvgl_tmr", lvgl_tick, RT_NULL, 10, RT_TIMER_FLAG_PERIODIC);
    if (lvgl_tmr != RT_NULL)
        rt_timer_start(lvgl_tmr);

    lvgl_mutex = rt_mutex_create("lvgl_mutex", RT_IPC_FLAG_FIFO);
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

    if (lvgl_mutex != RT_NULL)
        rt_mutex_delete(lvgl_mutex);

    lvgl_tid = RT_NULL;
    lvgl_tmr = RT_NULL;
    lvgl_mutex = RT_NULL;
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

/**
 * \brief lock lvgl task
 * 
 */
void lvgl2rtt_task_lock(void)
{
    rt_mutex_take(lvgl_mutex, RT_WAITING_FOREVER);
}

/**
 * \brief release lvgl task
 * 
 */
void lvgl2rtt_task_unlock(void)
{
    rt_mutex_release(lvgl_mutex);
}

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************