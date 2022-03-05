# Flutter-плагин для подписи данных с помощью ГОСТ сертификатов электронной подписи

## Описание
Плагин принимает сертификаты в формате __PKCS12__ ```.pfx```

Приватный ключ должен быть помечен как экспортируемый

Поддерживаемые алгоритмы для Android: __GOST R 34.10-2001__, __GOST R 34.10-2012__, __GOST R 34.10-2012 Strong__

Поддерживаемые архитектуры для Android: __arm64-v8a__, __armeabi-v7a__

Поддерживаемые алгоритмы для iOS: __GOST R 34.10-2012__


## Подключение плагина к Android проекту
1. Скопировать ```.aar``` библиотеки из ```android/libs``` плагина к себе в проект в ```android\app\libs```

2. Добавить в ```AndroidManifest.xml``` 
```xml
<application android:extractNativeLibs="true"></application>
```

3. Добавить в ```gradle.properties``` // Gradle <7
```properties
android.bundle.enableUncompressedNativeLibs = false
android.enableR8=false
```

4. Добавить в ```build.gradle```
```gradle
minSdkVersion 24

 buildTypes {
        release {
            shrinkResources false
            minifyEnabled false
            useProguard true // Gradle <7
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
    // Gradle >7
    jniLibs {
        useLegacyPackaging = true
    }
}

dependencies {
    implementation 'com.google.android.material:material:1.2.0-alpha03'
    implementation fileTree(dir: 'libs', include: '*.aar')
}
```

5. Создать файл ```proguard-rules.pro``` в ```android/app```
```pro
-keep public class ru.CryptoPro.*
```

## Подключение плагина к iOS проекту
Добавить папки ```en.lproj, locale, ru.lproj``` и файлы ```kis_1, root.sto, config.ini, license.enc``` из ```ios/Resources``` плагина к себе в проект через Xcode

## Методы
* __Подписать данные__
    ```dart
    CryptSignature.sign
    ```
    Возможны два сценария работы метода:<br>
    * Если данные известны сразу <br>
        Требуется передать данные в формате Base64 в параметр ```data``` для подписи
    * Если для формирования данных нужен сертификат пользователя <br>
        Требуется передать сallback ```onCertificateSelected```, который отдает вам сертификат, выбранный пользователем, и ожидает данные в формате Base64 для подписи<br>

    Метод возвращает объект класса ```SignResult```, содержащий сертификат, сигнатуру в Base64 и данные, поданные на подпись


* __Получить список сертификатов, добавленных пользователем__
    ```dart
    CryptSignature.getCertificates
    ```
* __Очистить список сертификатов__
    ```dart
    CryptSignature.clear
    ```

## Пример
* Требуется подписать ```0J/Rg9GC0LjQvSDQstC+0YA=```
    ```
    SignResult signResult = await CryptSignature.sign(context, data: "0J/Rg9GC0LjQvSDQstC+0YA=");
    ```

* Требуется сначала получить сертификат, которым будет выполняться подпись, чтобы сформировать хэш
    ```
    SignResult result = await CryptSignature.sign(context, onCertificateSelected: onCertificateSelected);
    ```
    ```
    Future<String> onCertificateSelected(Certificate certificate) async => "0J/Rg9GC0LjQvSDQstC+0YA=";
    ```