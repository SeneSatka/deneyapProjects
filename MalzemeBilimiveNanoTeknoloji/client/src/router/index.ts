import { createRouter, createWebHistory } from "vue-router";

const router = createRouter({
  history: createWebHistory(import.meta.env.BASE_URL),
  routes: [
    {
      path: "/",
      name: "home",
      component: () => import("../views/pages/HomePage.vue"),
    },
    {
      path: "/dashboard",
      name: "dashboard",
      component: () => import("../views/pages/DashBoard.vue"),
    },
    {
      path: "/about",
      name: "about",
      component: () => import("../views/pages/AboutPage.vue"),
    },
  ],
});

export default router;
