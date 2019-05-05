import Vue from 'vue'
import App from './App.vue'
import Bootstrap from 'bootstrap/dist/css/bootstrap.min.css'
import firebase from 'firebase'

Vue.config.productionTip = false

const config = {
  apiKey: "AIzaSyD_PEudhRi4vKhnT117IBr4OCwex2iShOo",
  authDomain: "smartclock-iot.firebaseapp.com",
  databaseURL: "https://smartclock-iot.firebaseio.com",
  projectId: "smartclock-iot",
  storageBucket: "smartclock-iot.appspot.com",
  messagingSenderId: "917424523372"
};
firebase.initializeApp(config)

new Vue({
  render: h => h(App),
  Bootstrap,
}).$mount('#app')
