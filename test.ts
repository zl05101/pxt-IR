// tests go here; this will not be compiled when this package is used as an extension.
let key = 0;

IR.init(Pins.P2)

IR.onPressEvent(RemoteButton.CH_MINUS, function () {
    serial.writeString("ch-")
})

IR.onPressEvent(RemoteButton.CH, function () {
    serial.writeString("ch")
})

IR.onPressEvent(RemoteButton.CH_ADD, function () {
    serial.writeString("ch+")
})


IR.onPressEvent(RemoteButton.NUM_2, function () {
    serial.writeString("2")
})

basic.forever(function () {
    basic.pause(2000);
})
