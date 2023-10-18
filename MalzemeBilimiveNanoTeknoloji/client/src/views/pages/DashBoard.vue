<script setup lang="ts">
import { ref } from "vue";

const data: { value: { open: Array<number>; close: Array<number> } } = ref({
  open: [],
  close: [],
});
setInterval(async () => {
  await fetch("http://localhost:3000/clientRequest").then((e) =>
    e.json().then((d) => (data.value = d))
  );

  data.value.close.forEach((element) => {
    document.querySelector(`.led${element + 1}`)?.classList.remove("led-open");
  });
  data.value.open.forEach((element) => {
    document.querySelector(`.led${element + 1}`)?.classList.add("led-open");
  });
}, 500);
const changeOpenLedState = async (led_id: number) => {
  await fetch(`http://localhost:3000/clientRequest?open=${led_id}`).then((e) =>
    e.json().then((d) => (data.value = d))
  );
};
const changeCloseLedState = async (led_id: number) => {
  await fetch(`http://localhost:3000/clientRequest?close=${led_id}`).then((e) =>
    e.json().then((d) => (data.value = d))
  );
};
const changeState = (led_id: number) => {
  if (data.value.close.includes(led_id - 1)) {
    changeOpenLedState(led_id - 1);
  } else if (data.value.open.includes(led_id - 1)) {
    changeCloseLedState(led_id - 1);
  }
};
</script>
<template>
  <div class="leds-container">
    <div class="left side">
      <div class="led led1" v-on:click="changeState(1)">1</div>
      <div class="led led2" v-on:click="changeState(2)">2</div>
      <div class="led led3" v-on:click="changeState(3)">3</div>
    </div>
    <div class="street">
      <div class="white"></div>
      <div class="white"></div>
      <div class="white"></div>
    </div>
    <div class="right side">
      <div class="led led4" v-on:click="changeState(4)">4</div>
      <div class="led led5" v-on:click="changeState(5)">5</div>
      <div class="led led6" v-on:click="changeState(6)">6</div>
    </div>
  </div>
</template>
<style scoped>
.leds-container {
  margin: auto;
  margin-top: 30px;
  width: 100vw;
  flex-wrap: wrap;
  gap: 20px;
  display: flex;
  justify-content: center;
  color: white;
}
.led {
  color: gray;
  display: flex;
  align-items: center;
  justify-content: center;
  width: 50px;
  height: 50px;
  border-radius: 50%;
  background-color: black;
}
.led-open::before {
  content: "";
  position: absolute;
  width: 100px;
  height: 100px;
  background-color: rgba(254, 207, 0, 0.4);
  border-radius: 50%;
  z-index: 99;
  filter: blur(20px);
}
.side {
  background-color: gray;
  display: flex;
  width: 100%;
  height: 70px;
  justify-content: space-between;
  align-items: center;
}
.led-open {
  background-color: yellow;
}
.street {
  display: flex;
  justify-content: space-around;
  align-items: center;
  width: 100vw;
  height: 200px;
}
.white {
  width: 20%;
  height: 20px;
  background-color: white;
}
</style>
