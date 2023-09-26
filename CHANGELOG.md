## [5.4.3](https://ntp-gitlab.krista.ru/mobile/utils/crypt_signature/compare/v5.4.2...v5.4.3) (2023-09-26)


### Bug Fixes

* временно сделал ссылку на зависимость публичной ([f3153fc](https://ntp-gitlab.krista.ru/mobile/utils/crypt_signature/commit/f3153fc86b39db1052c66355e20bbbd33d73cc84))

## [5.4.2](https://ntp-gitlab.krista.ru/mobile/utils/crypt_signature/compare/v5.4.1...v5.4.2) (2023-09-26)


### Bug Fixes

* убрал маску у поля ввода лицензии ([b332f2f](https://ntp-gitlab.krista.ru/mobile/utils/crypt_signature/commit/b332f2f6096142e36cd882b7420ecc43f4cbcc39))


### Docs

* поправил неверное название класса ([83efc83](https://ntp-gitlab.krista.ru/mobile/utils/crypt_signature/commit/83efc838078c7dcac09f6e72dd9c47034b8d737c))

## [5.4.1](https://ntp-gitlab.krista.ru/mobile/utils/crypt_signature/compare/v5.4.0...v5.4.1) (2023-08-15)


### Bug Fixes

* после ошибки во время подписи повторно инициализировалось late поле ([8b6a50a](https://ntp-gitlab.krista.ru/mobile/utils/crypt_signature/commit/8b6a50af45a16b2309f5b86570351730332ca67a))


### Code Improvements

* переименовал классы по названию стандарта подписи ([591bf48](https://ntp-gitlab.krista.ru/mobile/utils/crypt_signature/commit/591bf4891cdc8c17b14b58f83c3784ee712d582c))

## [5.4.0](https://ntp-gitlab.krista.ru/mobile/utils/crypt_signature/compare/v5.3.0...v5.4.0) (2023-08-15)


### Features

* добавил возможность прикрепить подписываемые данные к PKCS7 (detached/attached CMS) ([a4d5ba9](https://ntp-gitlab.krista.ru/mobile/utils/crypt_signature/commit/a4d5ba906df3f566dbcac7c09fcbe90612ed2acb))


### Other Changes

* убрал printenv из before_script в .gitlab-ci.yml ([6dd1a75](https://ntp-gitlab.krista.ru/mobile/utils/crypt_signature/commit/6dd1a759426912e5010f9a7fe5eaf2dc16cb18d9))


### Docs

* изменения в документации ([72c683f](https://ntp-gitlab.krista.ru/mobile/utils/crypt_signature/commit/72c683f99852cf01bc878d434cafac6125e86731))
* изменения в документации ([8b63945](https://ntp-gitlab.krista.ru/mobile/utils/crypt_signature/commit/8b639458e8b856a32ff96d1190bf62188a94826f))
* обновил примеры в документации ([be4b961](https://ntp-gitlab.krista.ru/mobile/utils/crypt_signature/commit/be4b9613b11cade0822d1b73b101fba6df2dfae0))
* описал detached pkcs7 в документации ([c3d47a0](https://ntp-gitlab.krista.ru/mobile/utils/crypt_signature/commit/c3d47a04843c38861502ee4caa0940c42368cb98))


### Code Improvements

* изменения дл тестов ([722a774](https://ntp-gitlab.krista.ru/mobile/utils/crypt_signature/commit/722a77416e5d250bdd664f32d93bfc2bb6aa8740))


### Test

* добавил widget тесты для сертификатов и лицензии ([7ec88cc](https://ntp-gitlab.krista.ru/mobile/utils/crypt_signature/commit/7ec88cce7d95742c4ee59c4e6b52ac153ef0d8d2))
* добавил тест на разворот сигнатуры для win32api ([cc5b321](https://ntp-gitlab.krista.ru/mobile/utils/crypt_signature/commit/cc5b321d5042c90760085e12c8fe15ca98eb50ac))
* добавил тесты для attached CMS формата ([66d0ab9](https://ntp-gitlab.krista.ru/mobile/utils/crypt_signature/commit/66d0ab9ea978149bd71b0f27579a2b9322d10bdb))


### Removed

* удалил настройки CI для GitHub ([e6cc01c](https://ntp-gitlab.krista.ru/mobile/utils/crypt_signature/commit/e6cc01c95985e7d39b0cc8dbc27137f6696ad617))
* удалил файл с номером версии КриптоПРО CSP, так как он отображается в AppBar ([1236cd9](https://ntp-gitlab.krista.ru/mobile/utils/crypt_signature/commit/1236cd9a467afe96d984714bc1f09b46e2ed2a76))

## [5.3.0](https://ntp-gitlab.krista.ru/mobile/utils/crypt_signature/compare/v5.2.1...v5.3.0) (2023-07-27)


### Features

* реализовать формирование PKCS7 ([d22d8e7](https://ntp-gitlab.krista.ru/mobile/utils/crypt_signature/commit/d22d8e7c3afda3121288279c63bfc454bb97b7ad))


### Bug Fixes

* hotfix ([a6d11ee](https://ntp-gitlab.krista.ru/mobile/utils/crypt_signature/commit/a6d11ee8b18232e77644671ae1b9352b86ce400a))


### Other Changes

* добавил описание для примера ([543ef14](https://ntp-gitlab.krista.ru/mobile/utils/crypt_signature/commit/543ef14cdb1a2037a163885193938cafc78c39f3))


### Docs

* обновил документацию примером использования через SignRequest ([9b24614](https://ntp-gitlab.krista.ru/mobile/utils/crypt_signature/commit/9b24614c844e8bbabdc567c451954840387a8c37))
* поправил комментарий под новую реализ. PKCS7 ([7ace82a](https://ntp-gitlab.krista.ru/mobile/utils/crypt_signature/commit/7ace82af697a5e7702849a2b436e888fc73e514e))
* убрал устаревшее API ([7e1b05b](https://ntp-gitlab.krista.ru/mobile/utils/crypt_signature/commit/7e1b05bb5c0f02d8a36c955cfc7916ec290a34ae))


### Style

* убрал ненужный конструктор ([ce8ca0f](https://ntp-gitlab.krista.ru/mobile/utils/crypt_signature/commit/ce8ca0fa26960c2ab0c2429ec247bbc5384f5f79))


### Code Improvements

* добавил дженерики на SignResult ([5436c21](https://ntp-gitlab.krista.ru/mobile/utils/crypt_signature/commit/5436c219da57f880c5fb9df97e34ed188892a45d))
* изменения для тестов ([1c3de11](https://ntp-gitlab.krista.ru/mobile/utils/crypt_signature/commit/1c3de11054be2a238b04a9dd685733aff177fb7b))
* переименовал InterfaceRequest в SignRequest, т.к. им будут пользоваться без вызова интерфейса ([77c10e5](https://ntp-gitlab.krista.ru/mobile/utils/crypt_signature/commit/77c10e5df9e000e5f6dc67c4683453f3c03e492f))


### Test

* вторая попытка поправить ошибку с разными временными зонами локально и в CI ([b86d779](https://ntp-gitlab.krista.ru/mobile/utils/crypt_signature/commit/b86d779b49ebc7ca105fce202f9823322928c82b))
* добавил TODO для XMLInterfaceRequest ([6280e46](https://ntp-gitlab.krista.ru/mobile/utils/crypt_signature/commit/6280e46d5def58ec563af3312c8e521a4517cf11))
* добавил тесты для PKCS7 ([fcd350b](https://ntp-gitlab.krista.ru/mobile/utils/crypt_signature/commit/fcd350bbd36297b718231a37aa55e7d43d8fe2e8))
* изменил ошибочное название файла с тестом ([53c7569](https://ntp-gitlab.krista.ru/mobile/utils/crypt_signature/commit/53c75695bd266a7af9199f4fb953f5ce179496ba))
* исключение при добавлении сигнатуры к pkcs7 ([ebb7f7d](https://ntp-gitlab.krista.ru/mobile/utils/crypt_signature/commit/ebb7f7d52731d96203967c557dc6158d0717f5cb))
* исправил ошибку в тесте, связанную с разным временем при локальном выполнении и в CI ([9ae35d4](https://ntp-gitlab.krista.ru/mobile/utils/crypt_signature/commit/9ae35d4d3a31572a9830cd0f4931d16035b3086e))
* поправил тестовые данные ([f309475](https://ntp-gitlab.krista.ru/mobile/utils/crypt_signature/commit/f3094750d7b8601827ef8ecafc49218263fcf54c))
* тест добавления и сохранения сертификата ([553a39c](https://ntp-gitlab.krista.ru/mobile/utils/crypt_signature/commit/553a39c19bb67ba88c650164b8cee30ca3b121f5))
* тесты для InterfaceRequest и потомков ([78338e0](https://ntp-gitlab.krista.ru/mobile/utils/crypt_signature/commit/78338e0118a19fd13a3ddcfac69f7c26c1aba3c2))

## [5.2.1](https://ntp-gitlab.krista.ru/mobile/utils/crypt_signature/compare/v5.2.0...v5.2.1) (2023-07-10)


### Bug Fixes

* добавил padding у заголовка окна с паролем ([b84e938](https://ntp-gitlab.krista.ru/mobile/utils/crypt_signature/commit/b84e93816a4079a34fa940a2c6d371bfec4b0607))
* добавил забытый padding между карточками ([348f663](https://ntp-gitlab.krista.ru/mobile/utils/crypt_signature/commit/348f6631cfb46b1de22287e57bd4f3291dba0d88))
* исправил импорт цвета AppBar из пользовательской темы ([51608b6](https://ntp-gitlab.krista.ru/mobile/utils/crypt_signature/commit/51608b6edd9d2e691f540880e478a4598f36c108))
* исправил ошибку из-за которой не обновлялся список сертификатов при добавлении/удалении ([0d1c6a9](https://ntp-gitlab.krista.ru/mobile/utils/crypt_signature/commit/0d1c6a9eb81eda70e16832ca593bbb5da9644063))


### Other Changes

* вернул https зависимости для возможности работать из дома ([a448f3b](https://ntp-gitlab.krista.ru/mobile/utils/crypt_signature/commit/a448f3b34be7f9aa89a9427379d1c3280402d1d4))
* добавил SSH для клонирование внутренних пакетов с GitLab ([db1d53c](https://ntp-gitlab.krista.ru/mobile/utils/crypt_signature/commit/db1d53c1aa3ca3397d41085d92d93dac492b7b47))
* добавил запуск тестов для CI ([4a390c5](https://ntp-gitlab.krista.ru/mobile/utils/crypt_signature/commit/4a390c503ac79608607d75d63a2969f9b801046c))

## [5.2.0](https://ntp-gitlab.krista.ru/mobile/utils/crypt_signature/compare/v5.1.2...v5.2.0) (2023-07-05)


### Features

* добавил возможность установки темы ([70db840](https://ntp-gitlab.krista.ru/mobile/utils/crypt_signature/commit/70db8401b0bc8e7925153fe3a1c3e8e974634d0f))


### Bug Fixes

* поправил установку темы ([450e6f5](https://ntp-gitlab.krista.ru/mobile/utils/crypt_signature/commit/450e6f52d670760070365824fe860ae2b5871e9b))


### Code Improvements

* изменил систему состояния плагина ([51e9c97](https://ntp-gitlab.krista.ru/mobile/utils/crypt_signature/commit/51e9c977c10b235f948a91e087bbdcaa82e8960d))

## [5.1.2](https://ntp-gitlab.krista.ru/mobile/utils/crypt_signature/compare/v5.1.1...v5.1.2) (2023-07-01)


### Bug Fixes

* тестовый фикс для semver ([c442bc5](https://ntp-gitlab.krista.ru/mobile/utils/crypt_signature/commit/c442bc553b1ccfe06d2e921ca2a6d5e56d95286a))

## [5.1.1](https://ntp-gitlab.krista.ru/mobile/utils/crypt_signature/compare/v5.1.0...v5.1.1) (2023-06-28)


### Bug Fixes

* поправил сломавшийся импорт ([3c135e6](https://ntp-gitlab.krista.ru/mobile/utils/crypt_signature/commit/3c135e6f149f41ea8de3aa9017cd01ea9b904a14))


### Other Changes

* добавил semver ([a2396af](https://ntp-gitlab.krista.ru/mobile/utils/crypt_signature/commit/a2396afb924f5e632e4d51dc8b942bb9db2d09d2))
* добавил semver ([4502fde](https://ntp-gitlab.krista.ru/mobile/utils/crypt_signature/commit/4502fdeaaa09f5d83cec274310ec7a88c8aeab1f))
* переместил файлы по правильным папкам ([60fc9d3](https://ntp-gitlab.krista.ru/mobile/utils/crypt_signature/commit/60fc9d3293a5f2b96c9571f36ffbc5911a2f7fb0))
* убрал неиспользуемые зависимости ([b613ece](https://ntp-gitlab.krista.ru/mobile/utils/crypt_signature/commit/b613ece234e58e841a01138278d794cfbd68687a))


### Docs

* update readme.md ([e473ea5](https://ntp-gitlab.krista.ru/mobile/utils/crypt_signature/commit/e473ea511632db62f752673b9ea55011b47f93e2))


### Code Improvements

* причесал классы для формирования X509 сертификата ([2af0e98](https://ntp-gitlab.krista.ru/mobile/utils/crypt_signature/commit/2af0e9812ad93ebc9e76a3d172e8e7b886118990))


### Test

* добавил проверку на совпадение описаний ([6d7dda3](https://ntp-gitlab.krista.ru/mobile/utils/crypt_signature/commit/6d7dda39f149d462f1927d6228279fb97424fd20))

## crypt_signature
