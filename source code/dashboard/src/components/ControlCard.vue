<template>
  <div @click="handleClick" class="control-card col-12 p-1">
    <div :class="['row wrapper', {'isOff': !isOn}]">
      <div class="col-4">
        <img class="w-100" :src="image" alt="">
      </div>
      <div class="col-8 center">
          <div class="col-12">
            <h5>Set Alarm</h5>
            <input class="form-control" type="text" value="" placeholder="e.g. 09:30" id="myAlarm">
            <hr>
            <button class="btn btn-primary" @click="Click"> SET </button>
          </div>
      </div>
    </div>
  </div>
</template>

<script>
export default {
  name: 'ControlCard',
  props: ['name', 'isOn', 'image'],
  methods: {
    handleClick () {
      this.$emit('isClick')
    },
    Click () {
      this.$emit('yeah')
    }
  }
}
</script>

<style lang="scss" scoped>
.control-card {
  .wrapper {
    padding: 10px 3px;
    background: rgb(230, 230, 230);
    margin: 1px;
  }
  p {
    margin-bottom: 0;
  }
}
.center {
  display: flex;
  justify-content: center;
  align-items: center;
}
.isOff {
  background: #777777!important;
  color: #fff;
}
</style>

