import 'package:crypt_signature/models/interface_request.dart';
import 'package:flutter/material.dart';

class InheritedCryptSignature extends InheritedWidget {
  final InterfaceRequest interfaceRequest;
  final BuildContext rootContext;

  const InheritedCryptSignature(this.interfaceRequest, this.rootContext, {Key key, @required Widget child}) : super(key: key, child: child);

  static InheritedCryptSignature of(BuildContext context) => context.dependOnInheritedWidgetOfExactType<InheritedCryptSignature>();

  @override
  bool updateShouldNotify(covariant InheritedWidget oldWidget) => interfaceRequest.runtimeType != oldWidget.runtimeType;
}
