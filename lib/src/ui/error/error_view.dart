import 'package:crypt_signature/src/ui/error/error_details_view.dart';
import 'package:crypt_signature/src/utils/exceptions/api_response_exception.dart';
import 'package:flutter/material.dart';

class ErrorView extends StatelessWidget {
  const ErrorView(this.state, {super.key, this.onRepeat});

  final ApiResponseException state;
  final void Function()? onRepeat;

  @override
  Widget build(BuildContext context) => Center(
        child: Padding(
          padding: const EdgeInsets.all(20),
          child: Column(
            mainAxisSize: MainAxisSize.min,
            children: <Widget>[
              const Padding(
                padding: EdgeInsets.symmetric(vertical: 15.0),
                child: Image(
                  width: 50,
                  image: AssetImage('assets/error.png', package: "crypt_signature"),
                ),
              ),
              Padding(
                padding: const EdgeInsets.symmetric(vertical: 15.0),
                child: Text(
                  state.message ?? "Ошибка",
                  textAlign: TextAlign.center,
                  style: const TextStyle(
                    fontSize: 14,
                    fontWeight: FontWeight.w600,
                  ),
                ),
              ),
              ErrorDetailsView(state.details),
              if (onRepeat != null)
                TextButton(
                  onPressed: onRepeat,
                  child: Text(
                    "Повторить попытку",
                    style: TextStyle(color: Colors.blue[700], fontSize: 14.0),
                  ),
                ),
            ],
          ),
        ),
      );
}
