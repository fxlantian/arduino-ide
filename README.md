<pre><code>
# 文件介绍 
(目前仅限于Linux下使用)  
  |-platform.txt: 描述了ide预处理，编译，链接，上传所用的命令  
  |-boards.txt: 描述了开发板的upload以及build过程所需参数  
  |-ANN_TEST_FINAL.ino: 在Arduino IDE中实现数字识别的代码  
  |-ppulib/
      |-output/    
          |-my.cpp.o: Arduino IDE编译生成的.o文件所存放的位置    
      |-upload/   
          |-run: PhyBoard开发板上传代码所需的可执行程序  
      |-xxx.a: 有五个.a文件 是Arduino_lib下的core_libs和separate_libs以及bench_lib, string_lib, bench_lib编译生成的静态链接库,Arduino IDE链接过程中用到
      |-preprocess: Arduino IDE对编写的ino代码预处理生成.cpp文件 preprocess的作用是在对应的.cpp开头添加四行代码
                      extern "C"{  
                        #include "int.h"  
                      }    
                      #include "main.cpp"  
      |-preprocess.c: preprocess的源代码  
  |-testANN.h: 所有ann内核配置数据、测试数据的头文件  
  |-libs/: PhyBoard所需的库文件  


# 文件使用  
将platform.txt中 工具链, preprocess, run, libs的路径改为 当前系统对应的路径  
用platform.txt和boards.txt 把arduino ide安装目录/hardware/arduino/avr/的同名文件替换掉  
赋予preprocess run 以及串口USB 权限以便其能够正常运行  
在Arduino IDE中tools 下board 选择ICT_PhyBoard port选择/dev/ttyUSB0  
连接好板子，编写好程序后点击上传按钮即可  

# 注意
上传程序的USB 必须是USB0
</code></pre>
