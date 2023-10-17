<script setup lang="ts">
const deneyapkartwebsites = () => {
  window.location.href = "https://deneyapkart.org/";
};
const changeLocation = (location: string) => {
  window.location.href = location;
};
</script>
<template>
  <header>
    <div v-on:click="deneyapkartwebsites" class="deneyap">
      <img src="https://cdnv2.t3vakfi.org/media/images/12.png" alt="" />
    </div>
    <div class="items">
      <div class="item" v-on:click="changeLocation('/')">Ana Sayfa</div>
      <div class="item" v-on:click="changeLocation('dashboard')">
        Yönetim Paneli
      </div>
      <div class="item" v-on:click="changeLocation('about')">Hazırlayanlar</div>
    </div>
  </header>
</template>
<style scoped>
header {
  display: flex;
  align-items: center;
  padding: 0 10px;
  width: auto;
  background-color: rgb(49, 49, 49);
  height: 50px;
  font-size: larger;
  font-family: "Franklin Gothic Medium", "Arial Narrow", Arial, sans-serif;
  color: whitesmoke;
}
.deneyap img {
  width: 70px;
  cursor: pointer;
}
.items {
  display: flex;
  justify-content: center;
  align-items: center;
  gap: 20px;
  margin: auto;
}
.item {
  text-align: center;
  cursor: pointer;
  color: rgb(245, 245, 245);
  transition: all 0.4s;
}
.item:hover {
  color: rgb(200, 200, 200);
}
</style>
