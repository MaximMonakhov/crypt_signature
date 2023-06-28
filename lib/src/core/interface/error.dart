import 'package:crypt_signature/src/core/interface/smooth_button.dart';
import 'package:crypt_signature/src/providers/crypt_signature_provider.dart';
import 'package:figma_squircle/figma_squircle.dart';
import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';
import 'package:flutter/services.dart';
import 'package:provider/provider.dart';

class ErrorViewWidget extends StatelessWidget {
  const ErrorViewWidget(
    this.error, {
    this.stackTrace,
    this.showStackTrace = true,
    super.key,
    this.repeatTry,
    this.showIcon = true,
    this.buttonTitle = "Повторить попытку",
  });

  final Object? error;
  final StackTrace? stackTrace;
  final VoidCallback? repeatTry;
  final bool showIcon;
  final bool showStackTrace;
  final String buttonTitle;

  void onRepeatButtonTap() => repeatTry?.call();

  Object _resolveError(Object? error) {
    switch (error.runtimeType) {
      case Null:
        return "Неизвестная ошибка";
      default:
        return error!;
    }
  }

  @override
  Widget build(BuildContext context) {
    Object resolvedError = _resolveError(error);
    StackTrace resolvedStackTrace = resolvedError is Error ? resolvedError.stackTrace ?? stackTrace ?? StackTrace.current : stackTrace ?? StackTrace.current;

    return Center(
      child: Column(
        mainAxisSize: MainAxisSize.min,
        children: <Widget>[
          if (showIcon)
            const Padding(
              padding: EdgeInsets.symmetric(vertical: 5.0),
              child: Image(
                image: AssetImage('assets/error.png', package: "crypt_signature"),
                width: 50,
                gaplessPlayback: true,
              ),
            ),
          Padding(
            padding: const EdgeInsets.symmetric(vertical: 5.0),
            child: Text(
              resolvedError.toString(),
              textAlign: TextAlign.center,
              style: const TextStyle(
                fontSize: 14,
                fontWeight: FontWeight.w600,
              ),
            ),
          ),
          if (showStackTrace)
            Padding(
              padding: const EdgeInsets.symmetric(horizontal: 10.0),
              child: ErrorDetailsView(resolvedStackTrace),
            ),
          const Padding(padding: EdgeInsets.symmetric(vertical: 5.0)),
          if (repeatTry != null)
            SmoothButton(
              onTap: onRepeatButtonTap,
              child: Container(
                padding: const EdgeInsets.symmetric(vertical: 10.0, horizontal: 30.0),
                child: Text(
                  buttonTitle,
                  style: TextStyle(
                    color: Theme.of(context).colorScheme.secondary,
                    fontWeight: FontWeight.bold,
                  ),
                ),
              ),
            ),
        ],
      ),
    );
  }
}

class ErrorDetailsView extends StatefulWidget {
  final StackTrace? stackTrace;
  const ErrorDetailsView(this.stackTrace, {super.key});

  @override
  _ErrorDetailsViewState createState() => _ErrorDetailsViewState();
}

class _ErrorDetailsViewState extends State<ErrorDetailsView> {
  bool isDetailsOpen = false;

  @override
  Widget build(BuildContext context) {
    if (widget.stackTrace == null) return Container();

    return isDetailsOpen
        ? Column(
            crossAxisAlignment: CrossAxisAlignment.start,
            mainAxisSize: MainAxisSize.min,
            children: [
              Row(
                mainAxisAlignment: MainAxisAlignment.spaceBetween,
                children: [
                  SmoothButton(
                    onTap: () {
                      setState(() {
                        isDetailsOpen = false;
                      });
                    },
                    title: "Скрыть",
                  ),
                  SmoothButton(
                    onTap: () {
                      Clipboard.setData(ClipboardData(text: widget.stackTrace.toString()));
                    },
                    title: "Скопировать",
                  ),
                ],
              ),
              const Padding(padding: EdgeInsets.symmetric(vertical: 5.0)),
              Flexible(
                child: Container(
                  constraints: BoxConstraints(maxHeight: MediaQuery.of(context).size.height * 0.25),
                  padding: const EdgeInsets.symmetric(vertical: 10),
                  margin: const EdgeInsets.only(bottom: 10.0),
                  decoration: ShapeDecoration(
                    shape: SmoothRectangleBorder(borderRadius: SmoothBorderRadius(cornerRadius: 15, cornerSmoothing: 1)),
                    color: Theme.of(context).colorScheme.background,
                    shadows: [
                      BoxShadow(color: Colors.black.withOpacity(0.2), blurRadius: 0.1, spreadRadius: 0.05),
                      BoxShadow(color: Colors.black.withOpacity(0.2), blurRadius: 0.5),
                    ],
                  ),
                  child: CupertinoScrollbar(
                    thumbVisibility: true,
                    child: ListView(
                      shrinkWrap: true,
                      padding: const EdgeInsets.symmetric(horizontal: 20.0),
                      physics: context.read<CryptSignatureProvider>().theme.scrollPhysics,
                      children: [
                        SelectableText(
                          widget.stackTrace.toString(),
                          textAlign: TextAlign.left,
                          style: const TextStyle(fontSize: 13),
                        ),
                      ],
                    ),
                  ),
                ),
              ),
            ],
          )
        : Material(
            color: Colors.transparent,
            child: InkWell(
              customBorder: SmoothRectangleBorder(borderRadius: SmoothBorderRadius(cornerRadius: 10, cornerSmoothing: 1)),
              onTap: () {
                setState(() {
                  isDetailsOpen = true;
                });
              },
              child: Container(
                padding: const EdgeInsets.symmetric(vertical: 10.0, horizontal: 30.0),
                child: Text(
                  "Подробнее",
                  style: TextStyle(
                    color: Theme.of(context).colorScheme.secondary,
                    fontWeight: FontWeight.bold,
                  ),
                ),
              ),
            ),
          );
  }
}
