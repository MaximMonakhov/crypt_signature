# Плагин на Flutter для формирования электронной цифровой подписи с помощью алгоритмов ГОСТ при помощи КриптоПРО

## __Описание__
Плагин принимает сертификаты в формате __PKCS12__ ```.pfx```

Приватный ключ должен быть помечен как экспортируемый

Поддерживаемые алгоритмы для Android: __GOST R 34.10-2001__, __GOST R 34.10-2012__, __GOST R 34.10-2012 Strong__

Поддерживаемые архитектуры для Android: __arm64-v8a__, __armeabi-v7a__

Поддерживаемые алгоритмы для iOS: __GOST R 34.10-2012__


## __Установка__
### __Подключение плагина к Android проекту__
1. Скопировать ```.aar``` библиотеки из ```android/libs``` плагина к себе в проект в ```android\app\libs```

2. Добавить в ```build.gradle```
```gradle
minSdkVersion 24

buildTypes {
        release {
            shrinkResources false
            minifyEnabled false
            proguardFiles getDefaultProguardFile('proguard-android.txt'), 'proguard-rules.pro'
        }
    }

packagingOptions {
    jniLibs {
        useLegacyPackaging = true
    }
}

dependencies {
    implementation fileTree(dir: 'libs', include: '*.aar')
}
```

3. Создать файл ```proguard-rules.pro``` в ```android/app```
```pro
-keep public class ru.CryptoPro.*
```

Библиотеки .aar указаны в плагине как compile-only, так как невозможно к .aar (коим является этот плагин) подключать другие .aar, для этого требуется скопировать их к себе в проект и подключить как implementation. Proguard используется, чтобы запретить обфускацию кода, которая происходить при выполнении релизной сборки.

### __Подключение плагина к iOS проекту__
Добавить папки ```en.lproj, locale, ru.lproj``` и файлы ```kis_1, root.sto, config.ini, license.enc``` из ```ios/Resources``` плагина к себе в проект через Xcode (Add files to Runner...).
Это нужно для того, чтобы эти файлы нашел КриптоПРО для проверки целостности. Это ресурсы копируются в папку с плагином, а КриптоПРО ищет их в корневой папке приложения.

## __Использование__
Работать с плагином можно:
- Используя собственный интерфейс плагина
- Через классы по нужному типу подписи (MessageSignRequest, PKCS7MessageSignRequest, ...)
- Напрямую через методы

Описание режимов работы:
* ```MessageSignRequest```
    * Высчитывает хэш от сообщения, подписывает его и возвращает сигнатуру в формате Base64.
* ```PKCS7MessageSignRequest```
    1. При выборе сертификата пользователем, получает сообщение через функцию ```getMessage```.
    2. Высчитывает хэш от полученного сообщения.
    3. Формирует PKCS7 и атрибуты подписи.
    4. Высчитывает хэш от атрибутов подписи.
    5. Подписывает этот хэш атрибутов.
    6. Вставляет сигнатуру в PKCS7 и возвращает этот его в формате Base64.
* ```PKCS7HASHSignRequest```<br>
    * Работает как и ```PKCS7MessageSignRequest```, но не высчитывает хэш от первоначального сообщения.
    * При выборе сертификата пользователем, получает хэш для подписи через функцию ```getDigest```.
* ```CustomSignRequest```<br>
    * Создан для выполнения собственной логики ЭП.

__Иными словами. ```PKCS7MessageSignRequest``` считает хэш сам, а ```PKCS7HASHSignRequest``` получает его готовый извне.__

Пример работы режимов:
* ```MessageSignRequest```
    <br>
    Применяется, когда у проверяющего есть сертификат пользователя и он хочет только проверить ЭП. Например, аутентификация путем ЭП случайного набора байт.
* ```PKCS7MessageSignRequest```
    <br>
    Применяется, когда у проверяющего нет информации о сертификате пользователя и дополнительной информации. Например, регистрация путем ЭП случайного набора байт.
* ```PKCS7HASHSignRequest```
    <br>
    Применяется, когда с сервера нецелесообразно передавать изначальное сообщение (из-за его большого размера к примеру). Тогда на выполнение ЭП передается уже готовый хэш от этого сообщения. Например, ЭП документов.

### __Использование через интерфейс__
```dart
CryptSignature.interface
```
При вызове данного метода открывается экран с возможностью добавления/выбора/хранения сертификатов.

<br><img src="crypt_signature.jpg" alt="crypt signature example image" width="400"/><br>

### __Методы плагина__
* Инициализировать провайдер
    ```dart
    CryptSignature.initCSP()
    ```
* Установить новую лицензию
    ```dart
    CryptSignature.setLicense(String license)
    ```
* Получить информацию о текущей лицензии
    ```dart
    CryptSignature.getLicense()
    ```
* Добавить сертификат в хранилище
    ```dart
    CryptSignature.addCertificate(File file, String password)
    ```
* Получить список сертификатов, добавленных пользователем
    ```dart
    CryptSignature.getCertificates()
    ```
* Очистить список сертификатов
    ```dart
    CryptSignature.clear()
    ```
* Вычислить хэш сообщения/документа
    ```dart
    CryptSignature.digest(Certificate certificate, String password, String message)
    ```
* Вычислить подпись хэша
    ```dart
    CryptSignature.sign(Certificate certificate, String password, String digest)
    ```

## __Пример__
### Пример использования плагина через интерфейс
```dart
/// MessageSignRequest
CryptSignature crypt = await CryptSignature.getInstance();
SignResult? result = await crypt.interface(context, MessageSignRequest("СООБЩЕНИЕ_В_BASE64"));
print(result?.signature); // Сигнатура в формате Base64
```
```dart
/// PKCS7MessageSignRequest
CryptSignature crypt = await CryptSignature.getInstance();
Future<String> getMessage(Certificate certificate) async => message; // Callback для запроса на сервер с выбранным пользователем сертификатом для формирования сообщения
PKCS7SignResult? result = await crypt.interface(context, PKCS7MessageSignRequest(getMessage));
print(result?.pkcs7.encoded); // PKCS7 в формате Base64
```
```dart
/// PKCS7HASHSignRequest
CryptSignature crypt = await CryptSignature.getInstance();
Future<String> getDigest(Certificate certificate) async => digest; // Callback для запроса на сервер с выбранным пользователем сертификатом для формирования хэша
PKCS7SignResult? result = await crypt.interface(context, PKCS7HASHSignRequest(getDigest));
print(result?.pkcs7.encoded); // PKCS7 в формате Base64
```
### Пример использования плагина через SignRequest

**Рекомендуется**, если не пользуетесь интерфейсом. PKCS7SignRequest сам создаст PKCS7 и подпишет его атрибуты подписи.
```dart
/// MessageSignRequest
CryptSignature crypt = await CryptSignature.getInstance();
// Получение файла .pfx и запрос пароля
MessageSignRequest request = MessageSignRequest("СООБЩЕНИЕ_В_BASE64");
SignResult result = await request.signer(certificate, password);
print(result.signature); // Сигнатура в формате Base64
```
```dart
/// PKCS7MessageSignRequest
CryptSignature crypt = await CryptSignature.getInstance();
// Получение файла .pfx и запрос пароля
Certificate certificate = await crypt.addCertificate(file, password);
Future<String> getMessage(Certificate certificate) async => message; // Callback для запроса на сервер с выбранным пользователем сертификатом для формирования сообщения
PKCS7MessageSignRequest request = PKCS7MessageSignRequest(getMessage);
PKCS7SignResult result = await request.signer(certificate, password);
print(result.pkcs7.encoded); // PKCS7 в формате Base64
```
```dart
/// PKCS7HASHSignRequest
CryptSignature crypt = await CryptSignature.getInstance();
// Получение файла .pfx и запрос пароля
Certificate certificate = await crypt.addCertificate(file, password);
Future<String> getDigest(Certificate certificate) async => digest; // Callback для запроса на сервер с выбранным пользователем сертификатом для формирования сообщения
PKCS7HASHSignRequest request = PKCS7HASHSignRequest(getDigest);
PKCS7SignResult result = await request.signer(certificate, password);
print(result.pkcs7.encoded); // PKCS7 в формате Base64
```

### Пример использования плагина через методы
```dart
/// Стандартная подпись данных
CryptSignature crypt = await CryptSignature.getInstance();
// Получение файла .pfx и запрос пароля
Certificate certificate = await crypt.addCertificate(file, password);
// Получение сообщения для ЭП
DigestResult digestResult = await crypt.digest(certificate, password, message);
SignResult signResult = await crypt.sign(certificate, password, digestResult.digest);
print(signResult.signature);
```
В случае PKCS7 подписи, PKCS7 нужно будет сформировать самому и подписывать атрибуты подписи. Как пример можно посмотреть как работает Signer в PKCS7MessageSignRequest или PKCS7HASHSignRequest.