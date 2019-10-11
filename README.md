# delay_sample

## openFrameworks
[github page](https://github.com/openframeworks/openFrameworks)

## OS

`MacOS Mojave 10.14.5`

## Version

`of_v0.10.1_osx_release`

## Env

openframeworksのディレクトリを  
`~/openframeworks`  
に配置している場合，  
このprojectを  
`~/openframeworks/of_v0.10.1_osx_release/apps/myApps/`  
にclone

## Usage

※ ハウリングするためイヤホン(マイク付き)推奨

```shell
$ make #コンパイル時のみ
$ make RunRelease
```

処理を止めたいときは，ターミナル上で  
`Ctrl + C`  
で終了するのが安全

### Setting

ディレイタイムやDECAY(減衰率)をいじりたいときは  
`src/ofApp.cpp`の  
```cpp
const int DELAYTIME = 400; //delayの感覚
const float DECAYRATE = 0.7; //delay音の減衰率
```
の値をいじる