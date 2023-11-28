# crypto-algorithm
常见密码学算法实现

## Base64
https://zh.wikipedia.org/wiki/Base64
Java层
```bash
import android.util.Base64;
Base64.encodeToString(data.getBytes(), Base64.DEFAULT);
Base64.decode(encodeString, Base64.DEFAULT);
```
当前应用
```bash
  ~/D/M/crypto-algorithm  main  adb shell dumpsys window|grep -i mcurrentfocus                                                                                    (base) 
  mCurrentFocus=Window{37c2854 u0 com.kuaikan.comic/com.kuaikan.main.MainActivity}
```
