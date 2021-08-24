# Thank You Cheems

> 一个简单的游戏

## 简介

这是作者在听说小学期有c++大作业之后，心血来潮叫上室友一起做的一个小游戏

本游戏是为了表达对当前yygq的网络环境的不满，希望网络环境变得更加和谐而作\_(:з」∠)\_

引擎使用了==已经过时==的cocos-2dx（

动画使用DragonBonesPro制作(良心软件!!!)

各种素材来源于网络，素材处理使用PS

## 用法

解压后双击[ThankYouCheems.exe](./ThankYouCheems.exe)即可食用。

## 概况

游戏设置界面只有显示帧率这一个选项可用

游戏BGM与音效均未添加至游戏中

如果想要bgm可以手动打开[./Resources/sound/平沢進 - gatts.mp3](./Resources/sound/平沢進 - gatts.mp3)播放

目前地图只有一张〒▽〒

## 问题

Q：应用无法正确启动（0xc000007b）

A：尝试使用以下方法[“0xc000007b无法正常启动”解决方案汇总](https://blog.csdn.net/GoodLi199309/article/details/88999758)



Q：无法定位程序输入点 ChecklsMSIXPackage于动态链接库`xxxx\Thank You Cheems\OPENGL32.dll` 上。

A：可能是dll损坏，尝试在网上重新下载一个覆盖游戏文件夹下的dll文件。



Q：双击exe后无任何响应

A：查看[log.txt](./log.txt)

- 如果报错为`GLFWError #65544 Happen, WGL: Failed to make context current`，尝试使用独立显卡打开游戏，[参考](https://blog.csdn.net/ixgnaz/article/details/105625145)中的python改成游戏应用就行了叭大概qwqq



Q：为何与怪物靠的太近按攻击键无法对怪物照成伤害？

A：游戏引擎限制，在怪物位置生成的攻击范围无法触发监听器，建议先攻击再去碰撞怪物இ௰இ
