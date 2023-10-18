import bodyParser from "body-parser";
import Express from "express";
import cors from "cors";
const app = Express();
app.use(bodyParser.json());
app.use(cors());
const process = { close: [0, 1, 2, 3, 4, 5], open: [] };
app.all("/deneyapkartRequest", (req, res) => {
  let leds = req.body;
  process.close.forEach((e) => {
    leds[e] = { id: e, isOpen: false };
  });
  process.open.forEach((e) => {
    leds[e] = { id: e, isOpen: true };
  });

  res.json(leds);
});
app.all("/clientRequest", (req, res) => {
  if (req.query.open == "all") {
    process.close = [];
    process.open = [0, 1, 2, 3, 4, 5];
  } else if (req.query.close == "all") {
    process.close = [0, 1, 2, 3, 4, 5];
    process.open = [];
  } else if (!process.open.includes(Number(req.query.open)) && req.query.open) {
    process.close = process.close.filter((e) => e != Number(req.query.open));
    process.open.push(Number(req.query.open[0]));
  } else if (
    !process.close.includes(Number(req.query.close)) &&
    req.query.close
  ) {
    process.open = process.open.filter((e) => e != Number(req.query.close));
    process.close.push(Number(req.query.close[0]));
  }

  res.json(process);
});
app.all("*", (req, res) => {
  res.send("error");
});
app.listen(3000, () => console.log("Server started"));
