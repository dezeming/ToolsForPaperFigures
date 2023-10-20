# 功能：




# 开发环境：

Qt5

CUDA

opencv+opencv_contrib

openexr

# 复制Qt环境到当前目录

cmd启动：进入Qt的windeployqt.exe路径，作用于Qt程序，例如：

D:/DevTools/Qt/5.15.2/msvc2019_64/bin/

调用：

windeployqt.exe 你的目录/PaperDrawingTools.exe

切勿进入PaperDrawingTools.exe所在目录调用windeployqt.exe：

D:/DevTools/Qt/5.15.2/msvc2019_64/bin/windeployqt.exe PaperDrawingTools.exe

