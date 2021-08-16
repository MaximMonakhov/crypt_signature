# Flutter-плагин для подписания данных с помощью ГОСТ сертификатов

## Форматы сертификатов
Плагин принимает сертификаты формата .pfx
Алгоритмы: ГОСТ 2001, ГОСТ 2012, ГОСТ 2012 Strong

## Настройки для проекта к которому подключается плагин
### 1. Скопировать .aar библиотеки из android/libs плагина к себе в проект в android\app\libs



### 2. ```AndroidManifest.xml``` 
```
<applicationandroid:extractNativeLibs="true"></application>
```

### 3. ```gradle.propeties```
```
android.bundle.enableUncompressedNativeLibs = false
android.enableR8=false
```

### 4. ```build.gradle```
```
minSdkVersion 24

 buildTypes {
        release {
            shrinkResources false
            minifyEnabled false
            useProguard true
            proguardFiles getDefaultProguardFile('proguard-android.txt'), 'proguard-rules.pro'
        }
    }

packagingOptions {
    exclude 'META-INF/Digest.CP'
    exclude 'META-INF/Sign.CP'
    exclude 'META-INF/NOTICE.txt'
    exclude 'META-INF/LICENSE.txt'
    doNotStrip "*/arm64-v8a/*.so"
    doNotStrip "*/armeabi/*.so"
    doNotStrip "*/x86_64/*.so"
    doNotStrip "*/x86/*.so"
}

dependencies {
    implementation 'com.google.android.material:material:1.2.0-alpha03'
    implementation fileTree(dir: 'libs', include: '*.aar')
}
```

### 5. Создать файл ```proguard-rules.pro``` в android/app
```
-keep public class ru.CryptoPro.*
```

### Методы
* Подписать данные
```dart
await CryptSignature.sign(context, data);
```
```dart
@param context - BuildContext приложения
@param data - данные в формате base64 для подписи
@param title - заголовок AppBar
@param hint - подсказка над списком сертификатов
@return возвращает JSON в формате
    {
        "data": - изначальные данные,
        "certificate" - сертификат в формате base64
        "sign" - сигнатура в формате base64
    }
```