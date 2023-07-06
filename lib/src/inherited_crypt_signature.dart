import 'package:crypt_signature/src/models/sign_request.dart';
import 'package:flutter/material.dart';

class InheritedCryptSignature extends InheritedWidget {
  final SignRequest signRequest;
  final BuildContext rootContext;

  const InheritedCryptSignature(this.signRequest, this.rootContext, {required super.child, super.key});

  static InheritedCryptSignature of(BuildContext context) => context.dependOnInheritedWidgetOfExactType<InheritedCryptSignature>()!;

  @override
  bool updateShouldNotify(covariant InheritedWidget oldWidget) => signRequest.runtimeType != oldWidget.runtimeType;
}
