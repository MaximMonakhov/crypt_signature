import 'package:figma_squircle/figma_squircle.dart';
import 'package:flutter/material.dart';

class SmoothButton extends StatelessWidget {
  final String? title;
  final Widget? child;
  final Color color;
  final VoidCallback? onTap;

  const SmoothButton({this.child, this.title, this.color = Colors.transparent, this.onTap, super.key}) : assert(child != null || title != null);

  @override
  Widget build(BuildContext context) => Material(
        shape: SmoothRectangleBorder(borderRadius: SmoothBorderRadius(cornerRadius: 10, cornerSmoothing: 1)),
        color: color,
        child: InkWell(
          customBorder: SmoothRectangleBorder(borderRadius: SmoothBorderRadius(cornerRadius: 10, cornerSmoothing: 1)),
          onTap: onTap,
          child: child ??
              Container(
                padding: const EdgeInsets.symmetric(vertical: 10.0, horizontal: 30.0),
                child: Text(
                  title!,
                  style: TextStyle(
                    color: Theme.of(context).colorScheme.secondary,
                    fontWeight: FontWeight.bold,
                  ),
                ),
              ),
        ),
      );
}
