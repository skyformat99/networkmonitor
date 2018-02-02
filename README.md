# networkmonitor
network monitor tools

无聊时写的一个网络流量监控小工具，可以在winXP,win7,win8系统很好工作。
同时可以配置窗口大小，文字颜色，曲线图颜色

config.ini 配置说明
pos_x，pos_y  流量条起始坐标
pos2_x，pos2_y  窗口起始坐标
TipTextColor tip颜色
height1024kb=30  一m网速占30px一格
width=300  窗口宽高
height=200 
up_R up_G up_B 上传曲线的rgb颜色
download_R=255   下载曲线的rgb颜色
download_G=0
download_B=0

Transparent2=215  两个窗体的透明度 0-255
Transparent=215 

bkimg=logo.bmp  可以自定义流量条样式，文件不存在则使用默认样式

[network]
AdapterIndex=7   记录保存的网卡索引

采用vs2003开发,mfc静态库编译。
下面是运行截图
![image](https://github.com/344717871/networkmonitor/blob/master/screenshot.png)

有问题可以mail我 simawei@qq.com
