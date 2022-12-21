import 'package:flutter/material.dart';

class InheritedLocker extends InheritedWidget {
  final bool lock;
  final void Function() lockScreen;
  final void Function() unlockScreen;

  const InheritedLocker({required this.lock, required super.child, required this.lockScreen, required this.unlockScreen, super.key});

  @override
  bool updateShouldNotify(InheritedLocker oldWidget) => lock != oldWidget.lock;

  static InheritedLocker of(BuildContext context) => context.dependOnInheritedWidgetOfExactType<InheritedLocker>()!;
}
