**①**

WDI窗口不能在case WM_SIZE返回0时存在，原因暂且未知。

**②**

窗口必须声明beginPaint和endPaint，否则不会自动绘制。