# Flutter-плагин для подписания данных с помощью ГОСТ сертификатов

### Форматы сертификатов
Плагин принимает сертификаты формата .pfx

### Настройки
Добавить в ```build.gradle``` модуля ```android``` в проекте
```dart
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