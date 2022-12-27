import 'package:crypt_signature/src/models/xml_dsig/algorithm_info/gost_algorithm_info.dart';
import 'package:crypt_signature/src/models/xml_dsig/algorithm_info/gost_sign_algorithm_info.dart';

/// Информация о алгоритмах хеширования по ГОСТу
class GostDigestAlgorithmInfo implements GostAlgorithmInfo {
  const GostDigestAlgorithmInfo._({required this.oid, required this.name, required this.namespace});

  @override
  final String oid;
  @override
  final String name;
  @override
  final String namespace;  

  factory GostDigestAlgorithmInfo.atOID(String oid) {
    final GostDigestAlgorithmInfo? signInfo = _oidAlgorithmMap[oid];
    if(signInfo == null) throw Exception('Неподдерживаемый алгоритм с oid $oid');
    return signInfo;
  }

  /// Возвращает сопряженный с данным алгоритм для подписи
  /// 
  /// *Например, для [GOST_1994] будет возвращен [GostSignAlgorithmInfo.GOST_2001]*
  GostSignAlgorithmInfo getSignAlgorithm() => _digestSignAlgorithmMap[this]!;

  /// Функция хэширования ГОСТ Р 34.11-94
  static const GOST_1994 = GostDigestAlgorithmInfo._(
    oid: _GOST_DIGEST_1994_OID, 
    name: _GOST_DIGEST_1994_NAME,
    namespace: '${GostAlgorithmInfo.XML_PREFIX}:gostr3411',
  );

  /// Функция хэширования ГОСТ Р 34.11-2012 (256)
  static const GOST_2012_256 = GostDigestAlgorithmInfo._(
    oid: _GOST_DIGEST_2012_256_OID, 
    name: _GOST_DIGEST_2012_256_NAME,
    namespace: '${GostAlgorithmInfo.XML_PREFIX}:gostr34112012-256',
  );

  /// Функция хэширования ГОСТ Р 34.11-2012 (512)
  static const GOST_2012_512 = GostDigestAlgorithmInfo._(
    oid: _GOST_DIGEST_2012_512_OID, 
    name: _GOST_DIGEST_2012_512_NAME,
    namespace: '${GostAlgorithmInfo.XML_PREFIX}:gostr34112012-512',
  );

  /// Имя для функции хэширования ГОСТ Р 34.11-94
  static const _GOST_DIGEST_1994_NAME = 'GOST3411';

  /// Имя для функции хэширования ГОСТ Р 34.11-2012 (256)
  static const _GOST_DIGEST_2012_256_NAME = 'GOST3411_12_256';

  /// Имя для функции хэширования ГОСТ Р 34.11-2012 (512)
  static const _GOST_DIGEST_2012_512_NAME = 'GOST3411_12_512';

  /// OID для функции хэширования ГОСТ Р 34.11-94
  static const _GOST_DIGEST_1994_OID = '1.2.643.2.2.9';

  /// OID для функции хэширования ГОСТ Р 34.10-2012 (256)
  static const _GOST_DIGEST_2012_256_OID = '1.2.643.7.1.1.2.2';

  /// OID для функции хэширования ГОСТ Р 34.10-2012 (512)
  static const _GOST_DIGEST_2012_512_OID = '1.2.643.7.1.1.2.3';

  static const _oidAlgorithmMap = <String, GostDigestAlgorithmInfo>{
    _GOST_DIGEST_1994_OID: GOST_1994,
    _GOST_DIGEST_2012_256_OID: GOST_2012_256,
    _GOST_DIGEST_2012_512_OID: GOST_2012_512
  };

  static const _digestSignAlgorithmMap = {
    GOST_1994: GostSignAlgorithmInfo.GOST_2001,
    GOST_2012_256: GostSignAlgorithmInfo.GOST_2012_256,
    GOST_2012_512: GostSignAlgorithmInfo.GOST_2012_512
  };
}
