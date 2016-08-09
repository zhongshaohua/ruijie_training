######################################################################
# 变量说明
# ====================================================================
# BLD_LDIR-y: 厍路径
# BLD_DLIB-y: 连接的动态库
# BLD_SLIB-y：连接的静态库
# BLD_LDFLAG-y: 链接选项
# BLD_CFLAG-y: C参数定义
# BLD_CDEF-y: C宏定义
# BLD_CINC-y: 头文件目录
# ROOT_DIR: 由cfg配置文件传下来，当前编译的目录
######################################################################
BLD_LDIR-y += -L /home/zsh/rgosm-build/prj_s57h/images/lib
BLD_LDIR-y += -L /home/zsh/rgosm-build/prj_s57h/images/rootfs/lib
BLD_LDFLAG-y += -lpthread -lcli-client -lrg-thread -lrg_lsm  -lrg_syslog
