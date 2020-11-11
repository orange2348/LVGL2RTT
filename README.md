# LVGL2RTT

此项目主要结合RT-Thread的包管理机制，实现LVGL与RT-Thread的适配。

此项目参考了LittleVGL2RTT，但是与LittleVGL2RTT相比，其主要有如下优化：

1. 更新LVGL到7.7.1，后续会继续随版本更新。
2. 驱动部分不单独实现，而是依托于rt-thread的显示接口，在drv_lcd.c实现，因此需要提前实现好lcd的驱动部分。

**TODO：**

- [ ] 完成touch、按键、旋编与RTT的对接。
- [x] 增加lvgl2rtt.c，用于完成系统调用依赖相关的准备工作。**（完成）**
- [ ] 增加文档的完整说明。