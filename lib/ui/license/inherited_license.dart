import 'package:crypt_signature/models/license.dart';
import 'package:flutter/material.dart';

class InheritedLicense extends InheritedWidget {
  final License? license;
  final Future<void> Function() setNewLicenseSheet;
  final Future<void> Function() getLicense;
  final Future<void> Function(String license) setLicense;

  const InheritedLicense({
    required this.license,
    required super.child,
    required this.getLicense,
    required this.setLicense,
    required this.setNewLicenseSheet,
    super.key,
  });

  @override
  bool updateShouldNotify(InheritedLicense oldWidget) => license != oldWidget.license;

  static InheritedLicense of(BuildContext context) => context.dependOnInheritedWidgetOfExactType<InheritedLicense>()!;
}
