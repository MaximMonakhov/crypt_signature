import 'package:flutter/material.dart';

class InheritedLocker extends InheritedWidget {
  final bool lock;
  final void Function() lockScreen;
  final void Function() unlockScreen;
  const InheritedLocker({Key key, @required this.lock, @required Widget child, this.lockScreen, this.unlockScreen}) : super(key: key, child: child);

  @override
  bool updateShouldNotify(InheritedLocker oldWidget) => lock != oldWidget.lock;

  static InheritedLocker of(BuildContext context) => context.dependOnInheritedWidgetOfExactType<InheritedLocker>();
}
