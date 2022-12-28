import 'package:crypt_signature/src/exceptions/xml_sign_exception.dart';
import 'package:crypt_signature/src/models/certificate.dart';
import 'package:crypt_signature/src/models/xml_dsig/operation/xml_canonicalization_operation.dart';
import 'package:crypt_signature/src/models/xml_dsig/operation/xml_digest_operation.dart';
import 'package:crypt_signature/src/models/xml_dsig/operation/xml_operation.dart';
import 'package:crypt_signature/src/models/xml_dsig/operation/xml_sign_operation.dart';
import 'package:crypt_signature/src/models/xml_dsig/request/xml_sign_options.dart';
import 'package:crypt_signature/src/models/xml_dsig/xml_sign_transformer.dart';

/// Хранит операции, необходимые для подписи xml - документа
abstract class XmlOperations {
  XmlCanonicalizationOperation get canonicalization;
  XmlDigestOperation get digest;
  XmlSignOperation get sign;
  XmlSignTransformer get transformer;

  factory XmlOperations.fromOptions(
    XmlSignOptions options, { 
    List<XmlTransformOperation> transforms = const [],
  }) {
    final XmlCanonicalizationOperation canonicalization = XmlCanonicalizationOperation(options.canonicalizationType);
    return XmlOperationsGostImpl(
      canonicalization: canonicalization,
      transformer: options.signatureType.getTransformer(canonicalization, transforms),
    );
  }

  void init(Certificate certificate, String password);
}

class XmlOperationsGostImpl implements XmlOperations {
  @override
  final XmlCanonicalizationOperation canonicalization;

  @override
  final XmlSignTransformer transformer;

  /// В случае ошибки инициализации выбрасывает [XmlInitializeOperationException]
  @override
  XmlDigestOperation get digest {
    if(_digest != null) return _digest!;
    throw XmlInitializeOperationException('Операция вычисления хэша документа не была инициализирована');
  }

  /// В случае ошибки инициализации выбрасывает [XmlInitializeOperationException]
  @override
  XmlSignOperation get sign {
    if(_sign != null) return _sign!;
    throw XmlInitializeOperationException('Операция подписи документа не была инициализирована');
  }

  XmlDigestOperation? _digest;
  XmlSignOperation? _sign;

  XmlOperationsGostImpl({
    required this.canonicalization,
    required this.transformer,
  });

  @override
  void init(Certificate certificate, String password) {
    _digest = XmlGostDigestOperation(certificate, password);
    _sign = XmlGostSignOperation(certificate, password);
  }
}
