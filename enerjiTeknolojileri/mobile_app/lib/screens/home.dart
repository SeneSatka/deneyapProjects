import 'package:flutter/material.dart';
import 'package:get/get.dart';
import 'package:mobile_app/utils/button.dart';
// import 'package:mobile_app/utils/notification_helper.dart';

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
        backgroundColor: Theme.of(context).colorScheme.inversePrimary,
      ),
      backgroundColor: Theme.of(context).colorScheme.primary,
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
                onPressed: () => Get.toNamed("blueToothConnection"),
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
// Row(
//             children: [
//               Container(
//                 margin: const EdgeInsets.all(20),
//                 child: ElevatedButton(
//                   onPressed: () {},
//                   style: ButtonStyle(
//                       padding:
//                           const MaterialStatePropertyAll(EdgeInsets.all(20)),
//                       shape: MaterialStateProperty.all<RoundedRectangleBorder>(
//                           RoundedRectangleBorder(
//                         borderRadius: BorderRadius.circular(18.0),
//                       ))),
//                   child: const Text("İnternet ile Bağlan"),
//                 ),
//               ),
//               Container(
//                 margin: const EdgeInsets.all(20),
//                 child: ElevatedButton(
//                     onPressed: () {}, child: const Text("İnternet ile Bağlan")),
//               ),
//             ],
//           )