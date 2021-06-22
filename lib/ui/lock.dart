import 'package:flutter/material.dart';

class LockWidget extends StatelessWidget {
  const LockWidget({Key key}) : super(key: key);

  @override
  Widget build(BuildContext context) {
    return Container(
      width: double.infinity,
      height: double.infinity,
      color: Colors.black.withOpacity(0.5),
      child: Center(
        child: Container(
          width: 50,
          height: 50,
          padding: EdgeInsets.all(20),
          child: CircularProgressIndicator(
            valueColor: AlwaysStoppedAnimation<Color>(Colors.white),
            strokeWidth: 1,
          ),
          decoration: BoxDecoration(
            color: Color.fromRGBO(106, 147, 245, 1),
            borderRadius: BorderRadius.circular(10),
          ),
        ),
      ),
    );
  }
}
