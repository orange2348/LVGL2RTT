import os
from building import * 

# get current dir path
cwd = GetCurrentDir()

# init src and inc vars
src = []
inc = []

# add LVGL common include
inc = inc + [cwd]
inc = inc + [cwd + /lvgl]
inc = inc + [cwd + "/lvgl/porting"]
inc = inc + [cwd + "/lvgl/src/lv_core"]
inc = inc + [cwd + "/lvgl/src/lv_draw"]
inc = inc + [cwd + "/lvgl/src/lv_font"]
inc = inc + [cwd + "/lvgl/src/lv_hal"]
inc = inc + [cwd + "/lvgl/src/lv_misc"]
inc = inc + [cwd + "/lvgl/src/lv_themes"]
inc = inc + [cwd + "/lvgl/src/lv_widgets"]

# add LittlevGL basic code
src = src + [cwd + "/lvgl/porting/lv_port_disp.c"]
src = src + Glob(cwd + '/lvgl/src/lv_core/*.c')
src = src + Glob(cwd + '/lvgl/src/lvgl/src/lv_draw/*.c')
src = src + Glob(cwd + '/lvgl/src/lv_fonts/*.c')
src = src + Glob(cwd + '/lvgl/src/lv_hal/*.c')
src = src + Glob(cwd + '/lvgl/src/lv_misc/*.c')
src = src + Glob(cwd + '/lvgl/src/lv_themes/*.c')
src = src + Glob(cwd + '/lvgl/src/lv_widgets/*.c')

# add group to IDE project
objs = DefineGroup('LVGL', src, depend = ['PKG_USING_LVGL'], CPPPATH = inc)
list = os.listdir(cwd)

if GetDepend('PKG_USING_LVGL'):
    for d in list:
        path = os.path.join(cwd, d)
        if os.path.isfile(os.path.join(path, 'SConscript')):
            objs = objs + SConscript(os.path.join(d, 'SConscript'))

Return('objs')
