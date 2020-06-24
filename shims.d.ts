// Auto-generated. Do not edit.



    //% color=0855AA weight=19
    //% icon="\uf1eb"
    //% block="红外"
declare namespace IR {

    /**
     * button pushed.
     */
    //% blockId=ir_received_left_event
    //% block="红外遥控 |%btn| 键按下" shim=IR::onPressEvent
    function onPressEvent(btn: RemoteButton, body: () => void): void;

    /**
     * initialises local variablesssss
     */
    //% blockId=ir_init
    //% block="设置红外接收引脚 %pin" shim=IR::init
    function init(pin: Pins): void;
}

// Auto-generated. Do not edit. Really.
