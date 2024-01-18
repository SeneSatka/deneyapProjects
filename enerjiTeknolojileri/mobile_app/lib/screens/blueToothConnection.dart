import 'package:flutter/material.dart';
import 'package:flutter_blue_plus/flutter_blue_plus.dart';
import 'package:get/get.dart';
import 'package:mobile_app/controllers/bluetooth_controller.dart';
import 'package:mobile_app/utils/button.dart';

class BlueToothConnection extends StatelessWidget {
  const BlueToothConnection({super.key});

  @override
  Widget build(BuildContext context) {
    return Scaffold(
        appBar: AppBar(
          title: const Text("Bluetooth Bağlantısı"),
          backgroundColor: Theme.of(context).colorScheme.inversePrimary,
        ),
        backgroundColor: Theme.of(context).colorScheme.primary,
        body: GetBuilder<BluetoothController>(
            init: BluetoothController(),
            builder: (controller) {
              return SingleChildScrollView(
                child: Column(
                  children: [
                    Center(
                        child: EButtonContainer.build(
                            element: EButton.build(
                                text: "Tara",
                                onPressed: () => controller.scanDevice(),
                                borderRadius: 5,
                                minimumSize: const MaterialStatePropertyAll(
                                    Size(350, 55))),
                            left: 30,
                            right: 30)),
                    const SizedBox(
                      height: 20,
                    ),
                    StreamBuilder<List<ScanResult>>(
                        stream: controller.scanResult,
                        builder: (context, snapshot) {
                          if (snapshot.hasData) {
                            return ListView.builder(
                                shrinkWrap: true,
                                itemCount: snapshot.data!.length,
                                itemBuilder: (context, index) {
                                  final data = snapshot.data![index];
                                  return Card(
                                    elevation: 2,
                                    child: ListTile(
                                      title: Text(data.device.advName),
                                      subtitle:
                                          Text(data.device.remoteId.toString()),
                                      trailing: Text(data.rssi.toString()),
                                      onTap: () async {
                                        await data.device.connect(
                                            mtu: null, autoConnect: true);
                                      },
                                    ),
                                  );
                                });
                          } else {
                            return const Center(
                              child: Text("No device "),
                            );
                          }
                        })
                  ],
                ),
              );
            }));
  }
}
//  EButtonContainer.build(
//               element: EIconButton.build(
//                   text: "Bluetooth bağlantısı",
//                   icon: Icons.bluetooth,
//                   onPressed: () => Get.toNamed("blueToothConnection"),
//                   borderRadius: 10),
//               left: 90,
//               right: 90)