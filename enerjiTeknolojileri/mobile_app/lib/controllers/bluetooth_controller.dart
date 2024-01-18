import 'package:flutter_blue_plus/flutter_blue_plus.dart';
import 'package:get/get.dart';

class BluetoothController extends GetxController {
  Future scanDevice() async {
    FlutterBluePlus.startScan(timeout: const Duration(seconds: 5));
  }

  Stream<List<ScanResult>> get scanResult => FlutterBluePlus.scanResults;
}
