package main

import (
  "fmt"
  "time"
  "flag"
  //"log"
  //"os"
  "github.com/tarm/serial"
  "github.com/eclipse/paho.mqtt.golang"
  sdf "github.com/kranfix/siser/dataframe"
)

var (
  broker     string = "tcp://190.90.6.43:1883"
  serialPort string = "/dev/ttyUSB0"
  baud       int    = 9600
)

func main(){
  flag.StringVar(&serialPort,"p", serialPort, "Serial port")
  flag.Parse()

  // Reserving memory for SISER Dataframe
  sDt := sdf.NewDataframe("OPEN","CHAU")

  // Opening  Serial Port
  c := &serial.Config{
    Name: serialPort,
    Baud: baud,
    ReadTimeout: 3000 * time.Millisecond,
  }
  s, err := serial.OpenPort(c)
  if err != nil {
    fmt.Println(err)
    return
  }
  fmt.Println("Serialport: Opened")
  defer func() {
    s.Close()
    fmt.Println("Serialport: Closed")
  }()
  /*err = s.Flush()
  if err != nil {
    return
  }*/

  mqttClient := createMqttClient()
	if token := mqttClient.Connect(); token.Wait() && token.Error() != nil {
		panic(token.Error())
	}


  // Dataframe Lecture
  Bytes := make([]byte, 128)
  //var N int
  xbeeBuf := []byte("REQ_")
  xbeeMax := byte(7)

  go func(){
    for {
      N, err := s.Read(Bytes)
      if  err != nil {
        continue
      }

      readed := false
      for n,k:= 0,0; n < N; n += k {
        k,readed = sDt.Detect(Bytes[n:N])
        if readed {
          fmt.Println(sDt)
          token := mqttClient.Publish("incuba/peru", 0, false, sDt.String())
          token.Wait()
        }
      }
    }
  }()

  RequestXbee:
  println("\n\nRequesting data to:")
  for i := byte(1); i <= xbeeMax; i++ {
    // Request of data
    //RequestData:
    println("- Device: ",i)
    xbeeBuf[3] = i
    s.Write(xbeeBuf)
    time.Sleep(500 * time.Millisecond)
  }
  println("waiting 8 seconds ...\n\n")
  time.Sleep(8 * time.Second)
  goto RequestXbee

  fmt.Println("Unexpected infite loop exit.")
}

func createMqttClient() mqtt.Client {
  //mqtt.DEBUG = log.New(os.Stdout, "", 0)
	//mqtt.ERROR = log.New(os.Stdout, "", 0)
  opts := mqtt.NewClientOptions().AddBroker(broker).SetClientID("")
	opts.SetKeepAlive(2 * time.Second)
	opts.SetPingTimeout(3000 * time.Millisecond)

  mqttClient := mqtt.NewClient(opts)
	if token := mqttClient.Connect(); token.Wait() && token.Error() != nil {
		panic(token.Error())
	}

  return mqttClient
}
