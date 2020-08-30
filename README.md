# LVGL2RTT

此项目主要结合RT-Thread的包管理机制，实现LVGL与RT-Thread的适配。

此项目与LittleVGL2RTT相比，主要解决如下问题：

1. 更新LVGL到7.0.1，后续会继续随版本更新。
2. 驱动部分不单独实现，而是依托于rt-thread的显示接口，在drv_lcd.c实现。

**TODO：**

1. 完成touch部分与RTT的对接。
2. 将LVGL的常用配置参数放到menuconfig中进行配置。
3. 增加原生example部分的示例打开选项。
4. 增加lvgl2rtt.c，用于完成系统调用依赖相关的准备工作。
5. 增加文档的完整说明。