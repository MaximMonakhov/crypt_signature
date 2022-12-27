import 'package:crypt_signature/src/models/xml_dsig/algorithm_info/algorithm_info.dart';
import 'package:flutter_c14n/flutter_c14n.dart';

class CanonicalizationAlgorithmInfo extends AlgorithmInfo {
  CanonicalizationAlgorithmInfo(C14nType type) : super(
    name: type.toString(), 
    namespace: canonicalNamespaces[type]!,
  );
}
