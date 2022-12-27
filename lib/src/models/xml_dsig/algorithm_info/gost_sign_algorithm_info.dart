import 'package:crypt_signature/src/models/algorithm.dart';
import 'package:crypt_signature/src/models/xml_dsig/algorithm_info/gost_algorithm_info.dart';
import 'package:crypt_signature/src/models/xml_dsig/algorithm_info/gost_digest_algorithm_info.dart';

/// Информация об алгоритмах подписи по ГОСТу
class GostSignAlgorithmInfo implements GostAlgorithmInfo {
  const GostSignAlgorithmInfo._({required this.oid, required this.name, required this.namespace});
  
  @override
  final String oid;

  @override
  final String name;

  @override
  final String namespace;

  factory GostSignAlgorithmInfo.atOID(String oid) {
    final GostSignAlgorithmInfo? signInfo = _oidAlgorithmMap[oid];
    if(signInfo == null) throw Exception('Неподдерживаемый алгоритм с oid $oid');
    return signInfo;
  }

  /// Возвращает алгоритм по имени в **КриптоПро**
  factory GostSignAlgorithmInfo.atName(String name) {
    final GostSignAlgorithmInfo? signInfo = _nameAlgorithmMap[name];
    if(signInfo == null) throw Exception('Неподдерживаемый алгоритм с именем $name');
    return signInfo;
  }

  factory GostSignAlgorithmInfo.fromAlgorithm(Algorithm algorithm) => GostSignAlgorithmInfo.atOID(algorithm.publicKeyOID);

  /// Возвращает сопряженный с данным алгоритм хеширования
  /// 
  /// *Например, для [GOST_2012_256] будет возвращен [GostDigestAlgorithmInfo.GOST_2012_256]*
  GostDigestAlgorithmInfo getDigestAlgorithm() => _signDigestAlgorithmMap[this]!;

  /// Алгоритм ГОСТ Р 34.10-2001
  static const GOST_2001 = GostSignAlgorithmInfo._(
    oid: _GOST_SIGN_2001_OID,
    name: _GOST_SIGN_2001_NAME,
    namespace: '${GostAlgorithmInfo.XML_PREFIX}:gostr34102001-gostr3411', 
  );

  /// Алгоритм ГОСТ Р 34.10-2012 (256)
  static const GOST_2012_256 = GostSignAlgorithmInfo._(
    oid: _GOST_SIGN_2012_256_OID,
    name: _GOST_SIGN_2012_256_NAME,
    namespace: '${GostAlgorithmInfo.XML_PREFIX}:gostr34102012-gostr34112012-256', 
  );

  /// Алгоритм ГОСТ Р 34.10-2012 (512)
  static const GOST_2012_512 = GostSignAlgorithmInfo._(
    oid: _GOST_SIGN_2012_512_OID,
    name: _GOST_SIGN_2012_512_NAME,
    namespace: '${GostAlgorithmInfo.XML_PREFIX}:gostr34102012-gostr34112012-512', 
  );

  static const _oidAlgorithmMap = {
    _GOST_SIGN_2001_OID: GOST_2001,
    _GOST_SIGN_2012_256_OID: GOST_2012_256,
    _GOST_SIGN_2012_512_OID: GOST_2012_512
  };

  static const _nameAlgorithmMap = {
    _GOST_SIGN_2001_NAME: GOST_2001,
    _GOST_SIGN_2012_256_NAME: GOST_2012_256,
    _GOST_SIGN_2012_512_NAME: GOST_2012_512
  };

  static const _signDigestAlgorithmMap = {
    GOST_2001: GostDigestAlgorithmInfo.GOST_1994,
    GOST_2012_256: GostDigestAlgorithmInfo.GOST_2012_256,
    GOST_2012_512: GostDigestAlgorithmInfo.GOST_2012_512
  };

  /// Имя для алгоритма ГОСТ Р 34.10-2001
  static const _GOST_SIGN_2001_NAME = 'NONEwithGOST3410EL';

  /// Имя для алгоритма ГОСТ Р 34.10-2012 (256)
  static const _GOST_SIGN_2012_256_NAME = 'NONEwithGOST3410_2012_256';

  /// Имя для алгоритма ГОСТ Р 34.10-2012 (512)
  static const _GOST_SIGN_2012_512_NAME = 'NONEwithGOST3410_2012_512';

  /// OID алгоритма ГОСТ 34.10-2001
  static const _GOST_SIGN_2001_OID = '1.2.643.2.2.19';

  /// OID алгоритма ГОСТ Р 34.10-2012 (256)
  static const _GOST_SIGN_2012_256_OID = '1.2.643.7.1.1.1.1';

  /// OID алгоритма ГОСТ Р 34.10-2012 (512)
  static const _GOST_SIGN_2012_512_OID = '1.2.643.7.1.1.1.2';
}
