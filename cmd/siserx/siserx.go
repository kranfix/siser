package main

import (
  "fmt"
  "time"
  //"log"
  //"os"
  "github.com/tarm/serial"
  "github.com/eclipse/paho.mqtt.golang"
  sdf "github.com/kranfix/siser/dataframe"
)

func main(){
  // Reserving memory for SISER Dataframe
  sDt := sdf.NewDataframe("OPEN","CHAU")

  // Opening  Serial Port
  c := &serial.Config{
    Name: "/dev/ttyUSB0",
    Baud: 9600,
    ReadTimeout: 100 * time.Millisecond,
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

  // mqtt client
	//mqtt.DEBUG = log.New(os.Stdout, "", 0)
	//mqtt.ERROR = log.New(os.Stdout, "", 0)
	opts := mqtt.NewClientOptions().AddBroker("tcp://190.90.6.43:1883").SetClientID("")
	opts.SetKeepAlive(2 * time.Second)
	opts.SetPingTimeout(1000 * time.Millisecond)

  mqttClient := mqtt.NewClient(opts)
	if token := mqttClient.Connect(); token.Wait() && token.Error() != nil {
		panic(token.Error())
	}


  // Dataframe Lecture

  Bytes := make([]byte, 128)
  var N int
  for {
    // Reading serialport
    if N, err = s.Read(Bytes); err != nil {
      continue
    }

    readed := false
    for n,k:= 0,0; n < N; n += k {
      k,readed = sDt.Detect(Bytes[n:N])
      if readed {
        //fmt.Printf("% x\n",Dt.Bytes())
        fmt.Println(sDt)
        token := mqttClient.Publish("incuba/peru", 0, false, sDt.String())
        token.Wait()
      }
    }

  }
  fmt.Println("Unexpected infite loop exit.")
}
