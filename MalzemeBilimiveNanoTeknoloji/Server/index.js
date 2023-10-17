import bodyParser from "body-parser";
import Express from "express";
const app = Express();
app.use(bodyParser.json());
const process = { close: [], open: [37] };
app.all("/test", (req, res) => {
  let leds = req.body;
  process.close.forEach((e) => {
    leds[e] = { id: e, isOpen: false };
  });
  process.open.forEach((e) => {
    leds[e] = { id: e, isOpen: true };
  });
  console.log(leds);
  // console.log(req.body);
  res.json(leds);
});
app.all("*", (req, res) => {
  res.send("asss");
});
app.listen(3000, () => console.log("Server started"));
