# TCP

# Requirements

* ```Windows```
* ```C++ 11 ```

#
```
https://github.com/ptluaan/tcp.git
```

# Build
```g++ RecvFile.cpp -o RecvFile -lws2_32```

```g++ SendFile.cpp -o SendFile -lws2_32```

# Run
Need 2 command line:

Step1: in command line 1:   ```RecvFile --out=< out >```


Step2: in command line 2:  ```SendFile < target > --path=< path > --buffer-size=< size >```

* ```buffer-size <= 512```

EX:

 ```RecvFile --out=./```
 
 ```SendFile 127.0.0.1 --path=C:/data/demo.txt --buffer-size=512```





