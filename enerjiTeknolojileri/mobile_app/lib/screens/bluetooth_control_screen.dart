import 'dart:async';
import 'dart:convert';
import 'dart:typed_data';
import 'package:flutter/material.dart';
import 'package:flutter_bluetooth_serial/flutter_bluetooth_serial.dart';
import 'package:get/get.dart';
import 'package:mobile_app/utils/button.dart';
import 'package:mobile_app/utils/notification_helper.dart';

class BluetoothControlScreen extends StatefulWidget {
  final BluetoothDevice device;
  const BluetoothControlScreen({super.key, required this.device});

  @override
  State<BluetoothControlScreen> createState() => _BluetoothControlScreenState();
}

class _BluetoothControlScreenState extends State<BluetoothControlScreen> {
  late StreamSubscription _streamSubscription;
  late BluetoothConnection connection;
  bool led1State = false;
  bool led2State = false;
  bool led3State = false;
  bool led4State = false;
  bool doorState = false;
  bool windowState = false;
  bool sync = false;
  dynamic data = {};
  @override
  void initState() {
    super.initState();
    _startListening();
  }

  void _startListening() async {
    if (!widget.device.isConnected) {
      connection = await BluetoothConnection.toAddress(widget.device.address);
    }
    connection.output.add(utf8.encode('0'));
    await connection.output.allSent;
    String dataString = "";
    bool recaiving = false;

    _streamSubscription = connection.input?.listen((Uint8List d) async {
      // print(ascii.decode(d));
      try {
        if (ascii.decode(d).startsWith("{")) {
          dataString += ascii.decode(d);
          recaiving = true;
        } else if (ascii.decode(d).endsWith("}")) {
          recaiving = false;
          dataString += ascii.decode(d);
          if (dataString.split("}").length > 2) {
            dataString = "${dataString.split("}")[0]}}";
          }
          // print(dataString);
          setState(() {
            try {
              print(data);
              data = jsonDecode(dataString);
            } catch (e) {
              print("convert error");
            }

            if (data["PIR"] == 1) {
              NotificationHelper.showNotification(
                  title: "Güvenlik uyarısı",
                  body: "Hareket algılandı",
                  payload: "a");
            }

            // print(data);
          });
          dataString = "";
        } else {
          if (recaiving) {
            dataString += ascii.decode(d);
          }
        }
      } catch (e) {}
    }) as StreamSubscription;
    //   setState(() {
    //     data = jsonDecode(d);
    //   });
    //   led1State = data["ledsState"]["1"] == 1 ? true : false;
    //   led2State = data["ledsState"]["2"] == 1 ? true : false;
    //   led3State = data["ledsState"]["3"] == 1 ? true : false;
    //   led4State = data["ledsState"]["4"] == 1 ? true : false;
    //   doorState = data["doorState"] == 1 ? true : false;
    //   windowState = data["windowState"] == 1 ? true : false;
    //   sync = true;
    //   if (data["PIR"] == 1) {
    //     NotificationHelper.showNotification(
    //         title: "Güvenlik uyarısı", body: "Hareket algılandı", payload: "a");
    //   }
    // });
  }

  void _stopListening() async {
    await _streamSubscription.cancel();
  }

  @override
  void dispose() {
    _stopListening();
    connection.close();

    super.dispose();
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
        appBar: AppBar(
          title: const Text("Kontrol Ekranı(Enes AKTAS)"),
          backgroundColor: Theme.of(context).colorScheme.inversePrimary,
        ),
        body: Column(
          children: [
            Row(
              children: [
                buildLedButton(1, led1State, () {
                  led1State = !led1State;
                  send();
                }),
                buildLedButton(2, led2State, () {
                  led2State = !led2State;
                  send();
                }),
              ],
            ),
            Row(
              children: [
                buildLedButton(3, led3State, () {
                  led3State = !led3State;
                  send();
                }),
                buildLedButton(4, led4State, () {
                  led4State = !led4State;
                  send();
                })
              ],
            ),
            Row(
              children: [
                EButtonContainer.build(
                    element: EIconButton.build(
                        text: "${data["humidity"] ?? "0"}",
                        icon: Icons.water_drop,
                        onPressed: () {},
                        sizedBoxWidth: 1),
                    width: 100,
                    right: 10,
                    left: 10),
                EButtonContainer.build(
                  element: EIconButton.build(
                    text: "${data["temperature"] ?? "0"}°C",
                    icon: Icons.device_thermostat,
                    onPressed: () {},
                    sizedBoxWidth: 1,
                  ),
                  left: 0,
                  right: 10,
                  width: 105,
                ),
                EButtonContainer.build(
                  element: EIconButton.build(
                    text: "${data["smokeValue"] ?? "0"}",
                    icon: Icons.gas_meter_rounded,
                    onPressed: () {},
                    sizedBoxWidth: 1,
                  ),
                  left: 0,
                  right: 10,
                  width: 110,
                ),
              ],
            ),
            Row(
              children: [
                EButtonContainer.build(
                    element: EIconButton.build(
                        text: "Kapı: ${doorState ? "Açık" : "Kapalı"}",
                        icon: doorState
                            ? Icons.door_back_door_sharp
                            : Icons.door_back_door_outlined,
                        onPressed: () {
                          doorState = !doorState;
                          send();
                        },
                        borderRadius: 5,
                        sizedBoxWidth: 5),
                    width: 160),
                EButtonContainer.build(
                    element: EIconButton.build(
                        text: "Cam: ${windowState ? "Açık" : "Kapalı"}",
                        icon: windowState
                            ? Icons.window_sharp
                            : Icons.window_outlined,
                        onPressed: () {
                          windowState = !windowState;
                          send();
                        },
                        borderRadius: 5,
                        sizedBoxWidth: 5),
                    width: 160)
              ],
            )
          ],
        ));
  }

  Widget buildLedButton(int led, ledState, Function onPressed) {
    return EButtonContainer.build(
        element: EIconButton.build(
            text: "Led $led: ${ledState ? "Açık" : "Kapalı"}",
            icon: ledState ? Icons.light_mode : Icons.light_mode_outlined,
            onPressed: () => onPressed(),
            borderRadius: 5,
            sizedBoxWidth: 5),
        width: 160);
  }

  send() {
    setState(() async {
      connection.output.add(utf8.encode(jsonEncode({"as": 1})));
      await connection.output.allSent;
      //   _channel.sink.add(jsonEncode({
      //     "device": 1,
      //     "led1State": led1State ? 1 : 0,
      //     "led2State": led2State ? 1 : 0,
      //     "led3State": led3State ? 1 : 0,
      //     "led4State": led4State ? 1 : 0,
      //     "doorState": doorState ? 1 : 0,
      //     "windowState": windowState ? 1 : 0,
      //   }));
    });
  }
}
