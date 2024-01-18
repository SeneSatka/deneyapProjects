import { WebSocketServer } from "ws";
let clients = new Set();
const wss = new WebSocketServer({ port: 8080 });
let ii = 0;
wss.on("connection", (ws) => {
  console.log("Bağlantı sağlandı");
  clients.add(ws);
  console.log(clients.size);
  // ws.send(JSON.stringify({ code: ii }));
  ws.on("message", (d) => {
    // ws.send(JSON.stringify({ code: 1, ));
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
            })
          );
      });
    }
    if (data.device == 0) {
      data.humidity = Math.round(data.humidity);
      data.temperature = Math.round(data.temperature);
      // console.clear();
      console.log(data);
      delete data.device;
      clients.forEach((e) => {
        if (e != ws) e.send(JSON.stringify(data));
      });
    }
    // ws.send(JSON.stringify({ humidity: 12, temperature: 34 }));
    // setTimeout(() => {
    //   ws.send(JSON.stringify({ humidity: 299, temperature: 123 }));
    // }, 10 * 1000);
  });
  ws.on("close", () => {
    clients.delete(ws);
  });
});
wss.once("listening", () => {
  console.log("açık");
});
