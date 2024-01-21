import { WebSocketServer } from "ws";
let clients = new Set();
const wss = new WebSocketServer({ port: 8080 });
wss.on("connection", (ws) => {
  console.log("Bağlantı sağlandı");
  clients.add(ws);
  console.log(clients.size);
  ws.on("message", (d) => {
    let data = JSON.parse(d.toString());
    console.log(data);
    if (data.device == 1) {
      clients.forEach((e) => {
        if (e != ws)
          e.send(
            JSON.stringify({
              ledsState: {
                1: data.led1State,
                2: data.led2State,
                3: data.led3State,
                4: data.led4State,
              },
              doorState: data.doorState ?? false,
              windowState: data.windowState ?? false,
            })
          );
      });
    }
    if (data.device == 0) {
      data.humidity = Math.round(data.humidity);
      data.temperature = Math.round(data.temperature);
      clients.forEach((e) => {
        if (e != ws) e.send(JSON.stringify(data));
      });
    }
  });
  ws.on("close", () => {
    clients.delete(ws);
  });
});
wss.once("listening", () => {
  console.log("açık");
});
