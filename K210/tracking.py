THRESHOLD = (30, 45, -10, 10, -5, 4)

# edge = (-1,-1,-1,-1,8,-1,-1,-1,-1)  #边缘化
# sharp = (-1,-1,-1,-1,9,-1,-1,-1,-1) #锐化
# relievo = (2,0,0,0,-1,0,0,0,-1)     #浮雕化
import sensor, image, time, lcd
from fpioa_manager import fm
from machine import UART

lcd.init(freq=15000000)
sensor.reset(dual_buff=1)
sensor.set_pixformat(sensor.RGB565) # Set pixel format to RGB565 (or GRAYSCALE)
sensor.set_framesize(sensor.QVGA)   # Set frame size to QVGA (320x240)
sensor.skip_frames(time = 2000)     # Wait for settings take effect.
sensor.set_auto_whitebal(False)     # close auto whitebal
sensor.set_hmirror(1)
sensor.set_vflip(1)
sensor.set_windowing((224, 224))
sensor.set_brightness(0)            # 设置亮度
sensor.set_auto_gain(0)
sensor.run(1)                       # run automatically, call sensor.run(0) to stop

#串口初始化
fm.register(10,fm.fpioa.UART2_TX)
fm.register(11,fm.fpioa.UART2_RX)
uart_1 = UART(UART.UART1, 115200, 8, None, 1, timeout=1000, read_buf_len=4096)

clock = time.clock()                # Create a clock object to track the FPS.

#发送打包函数
def send_data_packet(rho_err, theta_err):                                #距离左边的距离rho_err范围0—210，角度theta_err范围0-180
    checkout=(rho_err+theta_err)                                 #校验位,为x坐标+y坐标 的低八位
    data = bytearray([0xAA,0x55,rho_err,theta_err,checkout,0x54])#转成16进制
    uart_1.write(data)                                       #通过串口发送给stm32


while(True):
    clock.tick()                    # Update the FPS clock.

    img = sensor.snapshot().binary([THRESHOLD])        # Take a picture and return the image.
    #img.conv3(edge)
    #img.conv3(relievo)
    line = img.get_regression([(100,100,0,0,0,0)], robust = True)
    if (line):
        rho_err = int(abs(line.rho()))
        magnitude = line.magnitude()
        #if magnitude >
        if line.theta()<90:         #角度的范围0-180°
            theta_err = int(line.theta()+90)
        else:
            theta_err = int(line.theta()-90)
        img.draw_line(line.line(), color = 127)
        print(magnitude,rho_err,theta_err)
        send_data_packet(theta_err,rho_err)
    else:
        rho_err = 0
        theta_err = 0
        #print(rho_err,theta_err)
       # send_data_packet(theta_err,rho_err)
    fps =clock.fps()
    img.draw_string(18,2, ("GaHo's tracking car"), color=(255, 255, 0), scale=2)
    img.draw_string(2,26, ("%2.1ffps" %(fps)), color=(0,255,0), scale=2)
    img.draw_string(2,50, ("R:%d" %(rho_err)), color=(255, 105, 180), scale=2)
    img.draw_string(2,74, ("T:%d" %(theta_err)), color=(0, 238, 238), scale=2)
    img.draw_string(2,96, ("M:%d" %(magnitude)), color=(255, 0, 0), scale=2)
    lcd.display(img)

    #print(fps)
