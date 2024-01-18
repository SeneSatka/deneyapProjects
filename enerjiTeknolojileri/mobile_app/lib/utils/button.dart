import 'package:flutter/material.dart';

class EIconButton {
  static Widget build(
      {double borderRadius = 18.0,
      required String text,
      onPressed,
      required IconData icon,
      double sizedBoxWidth = 20}) {
    return ElevatedButton(
        onPressed: onPressed,
        style: ButtonStyle(
            shape: MaterialStateProperty.all<RoundedRectangleBorder>(
                RoundedRectangleBorder(
          borderRadius: BorderRadius.circular(borderRadius),
        ))),
        child: Row(
          children: [
            Icon(icon),
            SizedBox(
              width: sizedBoxWidth,
            ),
            Text(text)
          ],
        ));
  }
}

class EButton {
  static Widget build(
      {double borderRadius = 18.0,
      required String text,
      onPressed,
      required MaterialStateProperty<Size> minimumSize}) {
    return ElevatedButton(
        onPressed: onPressed,
        style: ButtonStyle(
            minimumSize: minimumSize,
            shape: MaterialStateProperty.all<RoundedRectangleBorder>(
                RoundedRectangleBorder(
              borderRadius: BorderRadius.circular(borderRadius),
            ))),
        child: Text(text));
  }
}

class EButtonContainer {
  static Widget build({
    required Widget element,
    double left = 10,
    double right = 10,
    double top = 10,
    double bottom = 10,
    double height = 50,
    double width = 100,
  }) {
    return Container(
        height: height,
        width: width,
        margin:
            EdgeInsets.only(left: left, right: right, top: top, bottom: bottom),
        child: element);
  }
}
