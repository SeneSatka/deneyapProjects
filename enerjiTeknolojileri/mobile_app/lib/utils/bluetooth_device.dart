import 'package:flutter/material.dart';
import 'package:flutter_bluetooth_serial/flutter_bluetooth_serial.dart';

class DeviceElement extends ListTile {
  DeviceElement({
    super.key,
    required BluetoothDevice device,
    int? rssi,
    GestureTapCallback? onTap,
    bool enabled = true,
  }) : super(
          onTap: onTap,
          enabled: enabled,
          leading: Icon(
            Icons.devices,
            color: enabled ? Colors.lightGreenAccent[400] : Colors.grey,
          ),
          tileColor:
              Colors.green.withAlpha(enabled || device.isConnected ? 200 : 100),
          title: Text(device.name ?? ""),
          subtitle: Text(device.address.toString()),
          trailing: Row(
            mainAxisSize: MainAxisSize.min,
            children: <Widget>[
              rssi != null
                  ? Container(
                      margin: const EdgeInsets.all(10.0),
                      child: DefaultTextStyle(
                        style: const TextStyle(color: Colors.white),
                        child: Column(
                          mainAxisSize: MainAxisSize.min,
                          children: <Widget>[
                            Text(rssi.toString()),
                            const Text('dBm'),
                          ],
                        ),
                      ),
                    )
                  : const SizedBox(width: 0, height: 0),
              device.isBonded
                  ? Icon(
                      Icons.bluetooth_searching,
                      color:
                          enabled ? Colors.lightGreenAccent[400] : Colors.grey,
                    )
                  : const SizedBox(width: 0, height: 0),
            ],
          ),
        );
}
