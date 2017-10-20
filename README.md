# hi3531a-gpio
Hi3531A GPIO deiver and test 
# 简介   
Hi3531A GPIO控制实例，LED驱动和测试例程
# 硬件连接
 dev |  chip   | pin  | name  |  func0
-----|---------|------|-------|----------
 led | Hi3531A | AH23 | IR_IN | GPIO20_5
# 文件说明
hi3531a-gpio  <br />
  |----hisi_led_drv.c      // led驱动程序           <br /> 
  |----hisi_led_test.c      // led驱动测试程序        <br />
  |----Makefile             // 同时编译驱动和测试程序  <br />
# 快速体验
这里先使用海思官方himm读写工具体验GPIO的控制，在海思SDK Hi3531A_SDK_V1.0.4.0\osdrv\tools\board\reg-tools-1.0.0\source\tools 下，提供了himm读写工具，这个工具可以在终端用来控制海思寄存器<br>
<pre><code>
在终端输入以下命令对GPIO进行快速操作<br />

* 管脚复用控制，设置为GPIO功能<br />
himm 0x120F0270 0
* 方向控制，GPIO20_5设置为输出<br />
himm 0x12290400 0x20
* 数据寄存器，GPIO20_5输出低<br />
himm 0x12290080 0x00
</code></pre>
# 使用说明
## 编译
将hi3531a-gpio文件夹放到 Hi3531A_SDK_V1.0.4.0\mpp\extdrv 下  <br />
<pre><code>
编译LED驱动程序和测试程序 <br />
cd hi3531a-gpio  <br />
make  <br />
</code></pre>
## 运行
将上面编译生成的hisi_led_drv.ko和hisi_led_test上传到海思单板  <br />
<pre><code>
加载led驱动   <br />
insmod hisi_led_drv.ko   <br />
运行测试程序   <br />
点亮LED   <br />
./hisi_led_test on  <br />
熄灭LED   <br />
./hisi_led_test off  <br />
</code></pre>
