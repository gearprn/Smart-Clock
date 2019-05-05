<template>
  <div id="app">
    <h1>Dashboard</h1>
    <div class="container">
      <div class="row">
        <div class="col">
          <hr>
        </div>
      </div>
      <div class="row">
        <data-card
        v-for="data in dataCollection"
        :key="data.name"
        :name="data.name"
        :value="data.value"
        />
      </div>
      <div class="row">
        <control-card
        @yeah="set()"
        @isClick="triggerState(device)"
        v-for="device in deviceCollection"
        :key="device.name"
        :name="device.name" 
        :isOn="device.isOn" 
        :image="device.image"/>
      </div>
    </div>
  </div>
</template>

<script>
import { database } from 'firebase'
import DataCard from '@/components/DataCard'
import ControlCard from '@/components/ControlCard'

export default {
  name: 'app',
  components: {
    DataCard,
    ControlCard
  },
  data () {
    return {
      dataCollection: [
        {name: 'Status', value: "Connected"}
      ],
      deviceCollection: [
        {name: 'alarm', isOn: true, image: require('./assets/alarm-clock.png')},
      ]
    }
  },
  methods: {
    set () {
      var alarm = document.getElementById('myAlarm')
      var hrs = parseInt(alarm.value[0] + alarm.value[1])
      var min = parseInt(alarm.value[3] + alarm.value[4])
      database().ref('time').set(alarm.value)
      database().ref('hrs').set(hrs)
      database().ref('min').set(min)
      alert("Done Set");
    }
  }
}
</script>

<style lang="scss">
#app {
  font-family: 'Avenir', Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  text-align: center;
  color: #2c3e50;
  margin: 60px 0;
}
</style>
