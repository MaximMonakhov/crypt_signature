import 'package:figma_squircle/figma_squircle.dart';
import 'package:flutter/material.dart';

class SmoothCard extends StatelessWidget {
  final Widget child;
  final VoidCallback? onTap;
  final EdgeInsets? padding;
  const SmoothCard({required this.child, this.onTap, this.padding = const EdgeInsets.only(left: 10.0, right: 10.0, top: 10.0), super.key});

  @override
  Widget build(BuildContext context) => Container(
        decoration: ShapeDecoration(
          shape: SmoothRectangleBorder(borderRadius: SmoothBorderRadius(cornerRadius: 10, cornerSmoothing: 1)),
          shadows: [
            BoxShadow(color: Colors.black.withOpacity(0.2), blurRadius: 0.1, spreadRadius: 0.05),
            BoxShadow(color: Colors.black.withOpacity(0.2), blurRadius: 0.5),
          ],
        ),
        child: Material(
          color: Theme.of(context).colorScheme.background,
          shape: SmoothRectangleBorder(borderRadius: SmoothBorderRadius(cornerRadius: 10, cornerSmoothing: 1)),
          child: InkWell(
            onTap: onTap,
            customBorder: SmoothRectangleBorder(borderRadius: SmoothBorderRadius(cornerRadius: 10, cornerSmoothing: 1)),
            child: Container(
              padding: padding,
              decoration: ShapeDecoration(
                shape: SmoothRectangleBorder(borderRadius: SmoothBorderRadius(cornerRadius: 10, cornerSmoothing: 1)),
              ),
              child: child,
            ),
          ),
        ),
      );
}
