# hi3531a-gpio
Hi3531A GPIO deiver and test 
# 简介   
Hi3531A GPIO控制实例，LED驱动和测试例程
# 硬件连接
 dev |  chip   | pin  | name  |  func0
-----|---------|------|-------|----------
 led | Hi3531A | AH23 | IR_IN | GPIO20_5
# 快速体验
使用海思官方himm读写工具体验GPIO的控制<br>
在海思SDK Hi3531A_SDK_V1.0.4.0\osdrv\tools\board\reg-tools-1.0.0\source\tools 下，提供了himm读写工具，这个工具可以在终端用来控制海思寄存器<br>
在终端输入以下命令对GPIO进行快速操作
* 管脚复用控制，设置为GPIO功能
`himm 0x120F0270 0`
* 方向控制，GPIO20_5设置为输出
`himm 0x12290400 0`
* 数据寄存器，GPIO20_5输出高
`himm 0x12290080 1`
# 使用说明
将hi3531a-gpio文件夹放到 Hi3531A_SDK_V1.0.4.0\mpp\extdrv 下

编译LED驱动程序和测试程序
cd hi3531a-gpio
make
