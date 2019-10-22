# delay_sample

## openFrameworks
[github page](https://github.com/openframeworks/openFrameworks)

基本いじるのは`src/`配下のファイルのみです

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

## Usage(遊び方)

※ ハウリングするためイヤホン(マイク付き)推奨

```shell
$ make #コンパイル時のみ
$ make RunRelease
```

画面が立ち上がったら，

* ボタンタップ

'd': ディレイエフェクトを起動
'z': ディレイエフェクトを止める

* マウス移動

横の移動: delayTimeの長さを変更(現状,あまり早く動かすとノイズでます)
たての移動: decayRateを変更(現状,あまり早く動かすとノイズでます)

処理を止めたいときは，ターミナル上で  
`Ctrl + C`  
で終了するのが安全
