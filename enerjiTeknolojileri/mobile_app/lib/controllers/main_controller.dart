import 'package:get/get.dart';

class MainController extends GetxController {
  var counter = 0.obs;
  void incrementCounter() => counter.value++;
}
