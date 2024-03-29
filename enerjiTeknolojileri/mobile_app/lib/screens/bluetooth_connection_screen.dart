import 'dart:async';
import 'package:flutter/material.dart';
import 'package:flutter_bluetooth_serial/flutter_bluetooth_serial.dart';
import 'package:get/get.dart';
import 'package:mobile_app/screens/bluetooth_control_screen.dart';
import '../utils/bluetooth_device.dart';

class SelectBluettothDevice extends StatefulWidget {
  final bool checkAvailability;

  const SelectBluettothDevice({super.key, this.checkAvailability = true});

  @override
  createState() => _SelectBluettothDevice();
}

class _DeviceWithAvailability {
  BluetoothDevice device;
  int availability;
  int? rssi;

  _DeviceWithAvailability(this.device, this.availability);
}

class _SelectBluettothDevice extends State<SelectBluettothDevice> {
  List<_DeviceWithAvailability> devices =
      List<_DeviceWithAvailability>.empty(growable: true);
  StreamSubscription<BluetoothDiscoveryResult>? _discoveryStreamSubscription;
  @override
  void initState() {
    super.initState();
    _startDiscovery();
    FlutterBluetoothSerial.instance
        .getBondedDevices()
        .then((List<BluetoothDevice> bondedDevices) {
      setState(() {
        devices = bondedDevices
            .map(
              (device) => _DeviceWithAvailability(
                device,
                widget.checkAvailability ? 0 : 1,
              ),
            )
            .toList();
      });
    });
  }

  void _startDiscovery() {
    _discoveryStreamSubscription =
        FlutterBluetoothSerial.instance.startDiscovery().listen((r) {
      setState(() {
        Iterator i = devices.iterator;
        while (i.moveNext()) {
          var device = i.current;
          if (device.device == r.device) {
            device.availability = 1;
            device.rssi = r.rssi;
          }
        }
      });
    });
  }

  @override
  void dispose() {
    _discoveryStreamSubscription?.cancel();
    super.dispose();
  }

  @override
  Widget build(BuildContext context) => Scaffold(
        appBar: AppBar(title: const Text('Senka Bluetooth Bağlantısı')),
        body: ListView(
            children: devices
                .map((device) => DeviceElement(
                      device: device.device,
                      rssi: device.rssi,
                      enabled: device.availability == 1,
                      onTap: () async {
                        await Get.to(
                            BluetoothControlScreen(device: device.device),
                            transition: Transition.fadeIn);

                        // BluetoothConnection connection =
                        //     await BluetoothConnection.toAddress(
                        //         device.device.address);
                        // print('Connected to the device');
                        // setState(() {});
                        // connection.input?.listen((Uint8List data) {
                        //   print('Data incoming: ${ascii.decode(data)}');
                        //   connection.output.add(data); // Sending data

                        //   if (ascii.decode(data).contains('!')) {
                        //     connection.finish(); // Closing connection
                        //     print('Disconnecting by local host');
                        //   }
                        // }).onDone(() {
                        //   print('Disconnected by remote request');
                        // });
                      },
                    ))
                .toList()),
      );
}
