import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';
import 'package:flutter/services.dart';

class ErrorDetailsView extends StatefulWidget {
  final String details;
  const ErrorDetailsView(this.details, {Key key}) : super(key: key);

  @override
  _ErrorDetailsViewState createState() => _ErrorDetailsViewState();
}

class _ErrorDetailsViewState extends State<ErrorDetailsView> {
  bool isDetailsOpen = false;

  @override
  Widget build(BuildContext context) {
    if (widget.details == null || widget.details.isEmpty) return Container();

    return isDetailsOpen
        ? Flexible(
            child: Column(
              crossAxisAlignment: CrossAxisAlignment.start,
              mainAxisSize: MainAxisSize.min,
              children: [
                Row(
                  mainAxisAlignment: MainAxisAlignment.spaceBetween,
                  children: [
                    TextButton(
                      onPressed: () => setState(() {
                        isDetailsOpen = false;
                      }),
                      child: Text("Скрыть", style: TextStyle(color: Colors.blue[700], fontSize: 15.0)),
                    ),
                    TextButton(
                      onPressed: () {
                        Clipboard.setData(ClipboardData(text: widget.details));
                      },
                      child: Text("Скопировать", style: TextStyle(color: Colors.blue[700], fontSize: 15.0)),
                    ),
                  ],
                ),
                Flexible(
                  child: Container(
                    constraints: BoxConstraints(maxHeight: MediaQuery.of(context).size.height * 0.25),
                    padding: const EdgeInsets.symmetric(vertical: 10),
                    margin: const EdgeInsets.only(bottom: 10.0),
                    decoration: BoxDecoration(
                      borderRadius: BorderRadius.circular(10.0),
                      color: Colors.white,
                      boxShadow: [
                        BoxShadow(color: Colors.black.withOpacity(0.1), blurRadius: 0.5, spreadRadius: 0.05),
                        BoxShadow(color: Colors.black.withOpacity(0.1), blurRadius: 2.0),
                      ],
                    ),
                    child: CupertinoScrollbar(
                      isAlwaysShown: true,
                      child: ListView(
                        shrinkWrap: true,
                        padding: const EdgeInsets.symmetric(horizontal: 20.0),
                        physics: const BouncingScrollPhysics(),
                        children: [
                          SelectableText(
                            widget.details,
                            textAlign: TextAlign.left,
                            style: const TextStyle(fontSize: 13),
                          ),
                        ],
                      ),
                    ),
                  ),
                ),
              ],
            ),
          )
        : TextButton(
            onPressed: () {
              setState(() {
                isDetailsOpen = true;
              });
            },
            child: Text(
              "Подробнее",
              style: TextStyle(color: Colors.blue[700], fontSize: 14.0),
            ),
          );
  }
}
