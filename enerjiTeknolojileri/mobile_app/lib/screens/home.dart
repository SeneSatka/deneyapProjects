import 'package:flutter/material.dart';
import 'package:get/get.dart';
import 'package:mobile_app/utils/button.dart';

class Home extends StatefulWidget {
  const Home({super.key});
  @override
  State<Home> createState() => _HomeState();
}

class _HomeState extends State<Home> {
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text("Bağlantı Ekranı(Enes AKTAS)"),
      ),
      body: Column(
        mainAxisAlignment: MainAxisAlignment.center,
        crossAxisAlignment: CrossAxisAlignment.center,
        children: [
          EButtonContainer.build(
              element: EIconButton.build(
                  text: "Wi-Fi bağlantısı",
                  icon: Icons.wifi,
                  onPressed: () {
                    Get.toNamed("wiFiControlScreen");
                  },
                  borderRadius: 10),
              left: 70,
              right: 70,
              width: 340),
          EButtonContainer.build(
              element: EIconButton.build(
                text: "Bluetooth bağlantısı",
                icon: Icons.bluetooth,
                onPressed: () => Get.toNamed("bluetoothConnection"),
                borderRadius: 10,
              ),
              left: 70,
              right: 70,
              width: 340),
        ],
      ),
    );
  }
}
