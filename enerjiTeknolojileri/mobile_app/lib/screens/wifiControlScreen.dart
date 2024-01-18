import 'dart:async';
import 'dart:convert';
import 'package:flutter/material.dart';
import 'package:mobile_app/utils/button.dart';
import 'package:mobile_app/utils/notification_helper.dart';
import 'package:web_socket_channel/io.dart';

class WiFiControlScreen extends StatefulWidget {
  const WiFiControlScreen({super.key});

  @override
  State<WiFiControlScreen> createState() => _WiFiControlScreenState();
}

class _WiFiControlScreenState extends State<WiFiControlScreen> {
  late StreamSubscription _streamSubscription;
  final IOWebSocketChannel _channel =
      IOWebSocketChannel.connect("ws://192.168.1.111:8080");
  bool led1State = false;
  bool led2State = false;
  bool led3State = false;
  bool led4State = false;
  bool sync = false;
  dynamic data = {};
  @override
  void initState() {
    super.initState();
    _startListening();
  }

  void _startListening() {
    _streamSubscription = _channel.stream.listen((d) {
      setState(() {
        data = jsonDecode(d);
      });
      if (!sync) {
        led1State = data["ledsState"]["1"] == 1 ? true : false;
        led2State = data["ledsState"]["2"] == 1 ? true : false;
        led3State = data["ledsState"]["3"] == 1 ? true : false;
        led4State = data["ledsState"]["4"] == 1 ? true : false;
        sync = true;
      }
      if (data["PIR"] == 1) {
        NotificationHelper.showNotification(
            title: "Güvenlik uyarısı", body: "Hareket algılandı", payload: "a");
      }
    });
  }

  void _stopListening() async {
    await _streamSubscription.cancel();
  }

  @override
  void dispose() {
    _stopListening();
    super.dispose();
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
        appBar: AppBar(
          title: const Text("Kontrol Ekranı(Enes AKTAS)"),
          backgroundColor: Theme.of(context).colorScheme.inversePrimary,
        ),
        backgroundColor: Theme.of(context).colorScheme.primary,
        body: Column(
          children: [
            Row(
              children: [
                buildLedButton(1, led1State, () {
                  led1State = !led1State;
                  wsSend();
                }),
                buildLedButton(2, led2State, () {
                  led2State = !led2State;
                  wsSend();
                }),
              ],
            ),
            Row(
              children: [
                buildLedButton(3, led3State, () {
                  led3State = !led3State;
                  wsSend();
                }),
                buildLedButton(4, led4State, () {
                  led4State = !led4State;
                  wsSend();
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

  wsSend() {
    setState(() {
      _channel.sink.add(jsonEncode({
        "device": 1,
        "led1State": led1State ? 1 : 0,
        "led2State": led2State ? 1 : 0,
        "led3State": led3State ? 1 : 0,
        "led4State": led4State ? 1 : 0
      }));
    });
  }
}
