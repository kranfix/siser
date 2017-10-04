package main

import (
  "fmt"
  "time"
  "log"
  "os"
  "bytes"
  "encoding/binary"
  "github.com/tarm/serial"
  "github.com/eclipse/paho.mqtt.golang"
  "github.com/kranfix/siser/siser"
)

func main(){
  // Reserving memory for SISER Dataframe
  sDt := siser.SiserDataframe{}//  // Opening Serial Port

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
	mqtt.DEBUG = log.New(os.Stdout, "", 0)
	mqtt.ERROR = log.New(os.Stdout, "", 0)
	opts := mqtt.NewClientOptions().AddBroker("tcp://190.90.6.43:1883").SetClientID("")
	opts.SetKeepAlive(2 * time.Second)
	opts.SetPingTimeout(1 * time.Second)

  mqttClient := mqtt.NewClient(opts)
	if token := mqttClient.Connect(); token.Wait() && token.Error() != nil {
		panic(token.Error())
	}


  // Dataframe Lecture
  initialDataframe := []byte("OPEN")
  onebyte := make([]byte, 1)

  // Counts the number of blocks to read
  Limit := 4
  for count := 0; count < Limit; count++ { // loop
    // Initial dataframe detection
    for i := 0; i < 4;  {
      _, err := s.Read(onebyte)
      if err != nil {
        continue
      } else if onebyte[0] == initialDataframe[i] {
        i++
        fmt.Printf("%s",onebyte)
      } else {
        i = 0
      }
    }

    fmt.Print(":")
    // Dataframe
    n := binary.Size(sDt)
    B := make([]byte, n)
    n, err := s.Read(B)
    buf := bytes.NewBuffer(B[:])
    //fmt.Printf("% x",B[:n])
    err = binary.Read(buf, binary.LittleEndian, &sDt)
    fmt.Print(sDt)
    if err == nil {
      token := mqttClient.Publish("incuba/peru", 0, false, sDt.String())
      token.Wait()
    }

    /*for i:=0; i < 4; i++ {
      _, err := s.Read(onebyte)
      if err == nil {
        fmt.Printf("%s",onebyte)
      }
    }*/ // Now works well without this section of code

    if count == Limit-1 {
      count = 0
      time.Sleep(4 * time.Second)
    }

  }
  fmt.Println("Unexpected infite loop exit.")
}
