#include "pxt.h"
#include <map>
#include <vector>
#include "ReceiverIR.h"
using namespace pxt;
typedef vector<Action> vA;

enum class Pins{
    P1=  2,
    P2=  1,
    P3=  4,
    P4=  5,
    P5=  17,
    P6=  12,
    P7=  11,
    P8=  18,
    P9=  10,
    P10= 6,
    P11= 26,
    P12= 20,
    P13= 23,
    P14= 22,
    P15= 21,
    P16= 16
};

//解码接收按低位开始处理 比如实际键值为 0xA2 = 1010 0010
//因是低位先处理所以变为 0100 0101 = 0x45 所以此处填写的键值为反的
enum class RemoteButton {
    NUM_0 = 0x16,
    NUM_1 = 0xc,
    NUM_2 = 0x18,
    NUM_3 = 0x5e,
    NUM_4 = 0x8,
    NUM_5 = 0x1c,
    NUM_6 = 0x5a,
    NUM_7 = 0x42,
    NUM_8 = 0x52,
    NUM_9 = 0x4A,
    CH_MINUS = 0x45,
    CH = 0x46,
    CH_ADD = 0x47,
    PREV = 0x44,
    NEXT = 0x40,
    PLAY = 0x43,
    MINUS_SIGN = 0x7,
    ADD_SIGN = 0x15,
    EQ = 0x9,
    NUM_100 = 0x19,
    NUM_200 = 0xd
};

//% color=0855AA weight=19
//% icon="\uf1eb"
//% block="红外"
namespace IR {
  map<RemoteButton, vA> actions;
  map<RemoteButton, uint32_t> lastact;
  Timer tsb;
  uint8_t buf[32];
  uint32_t now;
  ReceiverIR *rx;
  RemoteIR::Format fmt = RemoteIR::UNKNOWN;

  /**
  * button pushed.
  */
  //% blockId=ir_received_left_event
  //% block="红外遥控 |%btn| 键按下"
  void onPressEvent(RemoteButton btn, Action body) {
    //if(actions.find(btn) == actions.end()) actions[btn] = new vector();
    actions[btn].push_back(body);
  }

  void cA(vA runner){for(int i=0;i<runner.size();i++){runAction0(runner[i]);} }

  void onReceivable(){
    int x = rx->getData(&fmt, buf, 32 * 8);
    if(actions.find((RemoteButton)buf[2]) == actions.end()) return;
    now = tsb.read_ms();
    if(now - lastact[(RemoteButton)buf[2]] < 100) return;
    lastact[(RemoteButton)buf[2]] = now;
    cA(actions[(RemoteButton)buf[2]]);
  }

  void monitorIR(){
    while(1){
      while(rx->getState() != ReceiverIR::Received){
        uBit.sleep(50);
      }
      onReceivable();
    }
  }

  /**
  * initialises local variablesssss
  */
  //% blockId=ir_init
  //% block="设置红外接收引脚 %pin"
  void init(Pins pin){
    rx = new ReceiverIR((PinName)pin);
    tsb.start(); //interrupt timer for debounce
    create_fiber(monitorIR);
  }
#if 0
  /**
  * get key val
  */
  //% blockId=ir_get_key
  //% block="getKey"
  int getKey(){
      return buf[2];
  }
#endif
}
